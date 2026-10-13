"""Candidate identity that preserves compiler-relevant logical line groups.

IDO's normal -O2 pipeline emits .loc tags consumed by as1's scheduler. Token-
identical statements on the same line and on separate lines can produce
different objects. Ignore indentation, comments and empty-line padding, but
never collapse distinct token-bearing logical lines into one identity.
"""
from __future__ import annotations

import hashlib
import json
import re

_LEXEME = re.compile(
    r'(?P<comment>/\*.*?\*/|//[^\n]*)'
    r'|(?P<space>\s+)'
    r'|(?P<token>"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\''
    r'|[A-Za-z_$][A-Za-z0-9_$]*'
    r'|(?:0[xX][0-9A-Fa-f]+|(?:[0-9]+(?:\.[0-9]*)?|\.[0-9]+)(?:[eE][+-]?[0-9]+)?)[uUlLfF]*'
    r'|>>=|<<=|->|\+\+|--|&&|\|\||<=|>=|==|!=|\*=|/=|%=|\+=|-=|<<|>>|&=|\^=|\|=|##|\.\.\.'
    r'|\S)',
    re.DOTALL,
)


def candidate_identity(candidate: str) -> str:
    """Hash C tokens and their same-line relation, not absolute line numbers.

    Translation-phase backslash/newline splicing occurs before tokenization.
    Comments cannot eat quoted literals. Operator boundaries and whitespace
    inside literals remain significant. This is a conservative cache key,
    not a claim that every distinct identity produces a distinct object.
    """
    text = re.sub(r'\\\r?\n', '', candidate)
    line = 0
    previous_token_line = None
    group = -1
    tokens = []
    for match in _LEXEME.finditer(text):
        if match.lastgroup == 'token':
            if line != previous_token_line:
                group += 1
                previous_token_line = line
            tokens.append((group, match.group()))
        line += match.group().count('\n')
    encoded = json.dumps(tokens, ensure_ascii=True, separators=(',', ':'))
    return hashlib.sha256(encoded.encode('utf-8')).hexdigest()
