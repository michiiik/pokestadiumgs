"""Diagnostic-only quotient-class patch; NOT an accepted C replacement.

Requires decomp_workbench in the invoking Python environment. Input is the
retained optimizer output for the documented quotient seed. Guarded record
anchors refuse another stream. The result is for stock-pass replay only;
never install it as a production object or count it as decompiled source.
"""
import argparse
import hashlib
import json
import struct
from pathlib import Path


def transform(records):
    if len(records) <= 154:
        raise ValueError('stream is too short for the documented anchors')
    expected = {
        142: ('lod', (0x52600000, 0, 4, 3)),
        150: ('div', (0x1d660000, 0)),
        151: ('str', (0x7b660000, 0, 4, 2)),
        153: ('lod', (0x52600000, 0, 4, 4)),
        154: ('lod', (0x52680000, 0, 4, 2)),
    }
    for index, (name, words) in expected.items():
        if records[index].name != name or records[index].words != words:
            raise ValueError(f'record {index} differs from the documented seed')
    result = []
    for index, record in enumerate(records):
        if index == 142:
            result.append(records[153].words)
        if index not in (151, 153, 154):
            result.append(record.words)
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('stream', type=Path)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    if args.stream.resolve() == args.output.resolve():
        parser.error('input must remain intact; choose a distinct output')
    if args.output.exists():
        parser.error('output already exists; choose a fresh diagnostic path')
    from decomp_workbench.ucode import parse_ucode
    before = args.stream.read_bytes()
    records = parse_ucode(before)
    transformed = transform(records)
    words = [word for record in transformed for word in record]
    after = struct.pack('>' + 'I' * len(words), *words)
    parsed = parse_ucode(after)
    if len(parsed) != len(records) - 2:
        raise ValueError('decode-back record count differs')
    args.output.write_bytes(after)
    print(json.dumps({
        'status': 'diagnostic-only-not-source-accepted',
        'input_sha256': hashlib.sha256(before).hexdigest(),
        'output_sha256': hashlib.sha256(after).hexdigest(),
        'input_records': len(records), 'output_records': len(parsed),
        'source_reachability': 'unproven', 'rom_gate': 'NOT RUN',
    }, indent=2))


if __name__ == '__main__':
    main()
