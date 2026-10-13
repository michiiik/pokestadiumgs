"""Fingerprint stock routes, without changing production compiler settings.

Linux container example:
  python3 docs/regions/fragments/26/frontend_fingerprint.py \
    --repo /work --output /work/build/fragment26-frontend-fingerprint-reviewed

Outputs contain only synthetic objects and diagnostics. A calibrated result
does not establish an owner match, ROM match, or frontend impossibility.
"""
import argparse
import hashlib
import json
import re
import subprocess
from pathlib import Path


CALIBRATION = ['afa40000', '03e00008', 'afa50004']


def functions(disassembly):
    result = {}
    current = None
    for line in disassembly.splitlines():
        match = re.match(r'^[0-9a-f]+ <([^>]+)>:', line)
        if match:
            current = match.group(1).split('__')[0]
            result[current] = []
        elif current:
            match = re.match(r'^\s*[0-9a-f]+:\s+([0-9a-f]{8})\s+(.*)', line)
            if match:
                result[current].append((match.group(1), match.group(2)))
    return result


def dispatch_shape(rows):
    return 'table' if any(re.match(r'jr\s+(?!ra\b)\w+', asm) for _, asm in rows) else 'chain'


def measurement(disassembly):
    rows = functions(disassembly)
    control = [word for word, _ in rows.get('calibrated', [])]
    result = {'calibration_words': control, 'calibration': 'PASS' if control == CALIBRATION else 'FAIL'}
    result['status'] = 'measured' if result['calibration'] == 'PASS' else 'invalid_control'
    if result['calibration'] == 'PASS':
        result['noops'] = {name: [word for word, _ in rows[name]] for name in ['noop_if', 'noop_switch', 'noop_goto']}
        result['dispatch'] = {name: dispatch_shape(rows[name]) for name in ['dense_four', 'dense_five']}
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--repo', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--objdump', default='mips-linux-gnu-objdump')
    args = parser.parse_args()
    repo = args.repo.resolve()
    output = args.output.resolve()
    output.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).with_suffix('.c').resolve()
    results = []
    for version, driver, opt in [('7.1', 'cc', '-O2'), ('7.1', 'NCC', '-O2'), ('5.3', 'cc', '-O2'), ('7.1', 'cc', '-O1')]:
        compiler = repo / 'tools' / 'ido' / 'linux' / version / driver
        cell = f'{version}-{driver}-{opt[1:]}'
        obj = output / (cell + '.o')
        argv = [str(compiler), '-c', '-G', '0', '-non_shared', '-mips2', '-EB', opt, str(source), '-o', str(obj)]
        result = {'cell': cell, 'argv': argv, 'cwd': str(repo), 'source_sha256': hashlib.sha256(source.read_bytes()).hexdigest()}
        if not compiler.is_file():
            result.update(status='unavailable', calibration='NOT RUN')
            results.append(result)
            continue
        result['compiler_sha256'] = hashlib.sha256(compiler.read_bytes()).hexdigest()
        try:
            built = subprocess.run(argv, cwd=repo, text=True, capture_output=True, timeout=60)
            (output / (cell + '.stderr')).write_text(built.stderr)
            result['compile_exit_code'] = built.returncode
            if built.returncode:
                result.update(status='compile_failed', calibration='NOT RUN')
            else:
                dis = subprocess.run([args.objdump, '-dr', str(obj)], text=True, capture_output=True, timeout=30, check=True)
                (output / (cell + '.disasm')).write_text(dis.stdout)
                result.update(measurement(dis.stdout))
                result['object_sha256'] = hashlib.sha256(obj.read_bytes()).hexdigest()
        except (OSError, subprocess.SubprocessError, KeyError) as exc:
            result.update(status='diagnostic_failed', error=str(exc))
        results.append(result)
        print(json.dumps(result), flush=True)
    (output / 'results.json').write_text(json.dumps(results, indent=2) + '\n')
    return 0 if all(row['status'] == 'measured' for row in results) else 1


if __name__ == '__main__':
    raise SystemExit(main())
