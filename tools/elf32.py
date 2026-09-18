#!/usr/bin/env python3
"""Minimal big-endian ELF32 relocatable-object reader/writer.

Just enough to support ``coalesce_splice.py``'s narrow need: read a MIPS
``.o``, replace one named function's ``.text`` bytes and ``.rel.text``
entries, and write a new, valid ``.o`` back out. This is deliberately not a
general-purpose ELF library -- no program headers, no non-REL relocations, no
section insertion/removal, since object files produced by this toolchain
never need any of that.
"""
from __future__ import annotations

import struct
from dataclasses import dataclass, field

_EHDR = struct.Struct(">16sHHIIIIIHHHHHH")
_SHDR = struct.Struct(">10I")
_SYM = struct.Struct(">3I2BH")
_REL = struct.Struct(">2I")

SHN_UNDEF = 0
SHT_NOBITS = 8
SHT_SYMTAB = 2
SHT_REL = 9
SHT_MIPS_DEBUG = 0x70000005


@dataclass
class Section:
    name: str
    type: int
    flags: int
    addr: int
    link: int
    info: int
    addralign: int
    entsize: int
    data: bytes
    # SHT_NOBITS (.bss) sections have no file content -- `data` is always
    # empty for them -- but do have a real, meaningful sh_size (how much
    # zeroed space the loader reserves). That size lives here instead, since
    # it cannot be recovered from `len(data)` the way every other section's
    # size can. Ignored for every other section type.
    nobits_size: int = 0
    # File offset this section had when parsed (0 for sections built from
    # scratch). ``build`` keeps a section at this offset whenever the layout
    # still allows it, so that anything in the file holding *absolute file
    # offsets* into another section survives a rewrite. IRIX ``.mdebug``
    # does exactly that -- its header's cbFdOffset/cbSymOffset/cbSsOffset
    # are absolute file offsets, and asm-processor reads them back out of
    # the object (``--convert-statics``) after this module has rewritten it.
    # Letting a shrunk .text slide every later section down leaves those
    # pointers aimed at the wrong bytes: silently mis-named converted
    # statics, or a bare ``symbol_name_offset_end != -1`` assert inside
    # asm_processor.
    file_offset: int = 0


@dataclass
class Symbol:
    name: str
    value: int
    size: int
    info: int
    other: int
    shndx: int


@dataclass
class Relocation:
    offset: int
    sym_index: int
    type: int

    def r_info(self) -> int:
        return (self.sym_index << 8) | (self.type & 0xFF)


@dataclass
class Elf32Object:
    e_type: int
    e_machine: int
    e_version: int
    e_entry: int
    e_flags: int
    sections: list[Section] = field(default_factory=list)  # index 0 is the null section

    def section_index(self, name: str) -> int | None:
        for i, sec in enumerate(self.sections):
            if sec.name == name:
                return i
        return None

    def section(self, name: str) -> Section | None:
        idx = self.section_index(name)
        return None if idx is None else self.sections[idx]

    def symbols(self) -> list[Symbol]:
        symtab = self.section(".symtab")
        strtab = self.section(".strtab")
        if symtab is None or strtab is None:
            return []
        out = []
        for offset in range(0, len(symtab.data), _SYM.size):
            st_name, st_value, st_size, st_info, st_other, st_shndx = _SYM.unpack_from(
                symtab.data, offset
            )
            out.append(
                Symbol(
                    name=_read_cstr(strtab.data, st_name),
                    value=st_value,
                    size=st_size,
                    info=st_info,
                    other=st_other,
                    shndx=st_shndx,
                )
            )
        return out

    def relocations(self, section_name: str) -> list[Relocation]:
        rel = self.section(section_name)
        if rel is None:
            return []
        out = []
        for offset in range(0, len(rel.data), _REL.size):
            r_offset, r_info = _REL.unpack_from(rel.data, offset)
            out.append(
                Relocation(offset=r_offset, sym_index=r_info >> 8, type=r_info & 0xFF)
            )
        return out

    def set_symbols(self, symbols: list[Symbol]) -> None:
        """Rewrite ``.symtab`` in place, keeping the same order (== indices).

        Relocations reference symbols purely by index, so callers must never
        reorder, insert, or remove entries here -- only mutate ``value``/
        ``size``/``shndx`` in place on the list from :meth:`symbols`.
        """
        idx = self.section_index(".symtab")
        if idx is None:
            raise KeyError(".symtab")
        strtab = self.section(".strtab")
        if strtab is None:
            raise KeyError(".strtab")
        name_offset = {}
        # Every name here must already exist in .strtab (this module never
        # adds symbols), so look up each one's existing offset rather than
        # growing the string table.
        text = strtab.data
        for sym in symbols:
            if sym.name in name_offset:
                continue
            needle = sym.name.encode("latin1") + b"\x00"
            # A name can appear as a non-boundary substring of an unrelated,
            # longer name before its own real occurrence (confirmed on this
            # repo's own build/src/95C0.o: looking up "_Printf" finds it
            # first as a suffix of "HAL_Printf", which is not NUL-preceded
            # and is not this symbol's own entry) -- keep searching past
            # every such false hit instead of bailing out on the first one.
            pos = -1
            search_from = 0
            while True:
                pos = text.find(needle, search_from)
                if pos == -1:
                    break
                if pos == 0 or text[pos - 1] == 0:
                    break  # a real entry boundary, not a substring match
                search_from = pos + 1
            if pos == -1:
                raise ValueError(f"symbol name {sym.name!r} not found in .strtab")
            name_offset[sym.name] = pos
        blob = b"".join(
            _SYM.pack(name_offset[s.name], s.value, s.size, s.info, s.other, s.shndx)
            for s in symbols
        )
        old = self.sections[idx]
        self.sections[idx] = Section(
            name=old.name,
            type=old.type,
            flags=old.flags,
            addr=old.addr,
            link=old.link,
            info=old.info,
            addralign=old.addralign,
            entsize=old.entsize,
            nobits_size=old.nobits_size,
            file_offset=old.file_offset,
            data=blob,
        )

    def set_relocations(self, section_name: str, relocations: list[Relocation]) -> None:
        idx = self.section_index(section_name)
        if idx is None:
            raise KeyError(section_name)
        blob = b"".join(_REL.pack(r.offset, r.r_info()) for r in relocations)
        old = self.sections[idx]
        self.sections[idx] = Section(
            name=old.name,
            type=old.type,
            flags=old.flags,
            addr=old.addr,
            link=old.link,
            info=old.info,
            addralign=old.addralign,
            entsize=old.entsize,
            nobits_size=old.nobits_size,
            file_offset=old.file_offset,
            data=blob,
        )

    def set_section_data(self, section_name: str, data: bytes) -> None:
        idx = self.section_index(section_name)
        if idx is None:
            raise KeyError(section_name)
        old = self.sections[idx]
        self.sections[idx] = Section(
            name=old.name,
            type=old.type,
            flags=old.flags,
            addr=old.addr,
            link=old.link,
            info=old.info,
            addralign=old.addralign,
            entsize=old.entsize,
            nobits_size=old.nobits_size,
            file_offset=old.file_offset,
            data=data,
        )


def _read_cstr(data: bytes, offset: int) -> str:
    end = data.index(b"\x00", offset)
    return data[offset:end].decode("latin1")


def parse(data: bytes) -> Elf32Object:
    (
        e_ident,
        e_type,
        e_machine,
        e_version,
        e_entry,
        e_phoff,
        e_shoff,
        e_flags,
        e_ehsize,
        e_phentsize,
        e_phnum,
        e_shentsize,
        e_shnum,
        e_shstrndx,
    ) = _EHDR.unpack_from(data, 0)
    if e_ident[:4] != b"\x7fELF":
        raise ValueError("not an ELF file")
    if e_ident[4] != 1:
        raise ValueError("only ELF32 is supported")
    if e_ident[5] != 2:
        raise ValueError("only big-endian ELF is supported")

    raw_headers = []
    for i in range(e_shnum):
        off = e_shoff + i * e_shentsize
        raw_headers.append(_SHDR.unpack_from(data, off))

    shstr_off = raw_headers[e_shstrndx][4]
    shstr_size = raw_headers[e_shstrndx][5]
    shstrtab = data[shstr_off : shstr_off + shstr_size]

    sections = []
    for (
        sh_name,
        sh_type,
        sh_flags,
        sh_addr,
        sh_offset,
        sh_size,
        sh_link,
        sh_info,
        sh_addralign,
        sh_entsize,
    ) in raw_headers:
        name = _read_cstr(shstrtab, sh_name) if sh_type != 0 or sh_name != 0 else ""
        if sh_type == SHT_NOBITS:
            body = b""
        else:
            body = data[sh_offset : sh_offset + sh_size]
        sections.append(
            Section(
                name=name,
                type=sh_type,
                flags=sh_flags,
                addr=sh_addr,
                link=sh_link,
                info=sh_info,
                addralign=sh_addralign or 1,
                entsize=sh_entsize,
                data=body,
                nobits_size=sh_size if sh_type == SHT_NOBITS else 0,
                file_offset=sh_offset,
            )
        )

    return Elf32Object(
        e_type=e_type,
        e_machine=e_machine,
        e_version=e_version,
        e_entry=e_entry,
        e_flags=e_flags,
        sections=sections,
    )


def build(obj: Elf32Object) -> bytes:
    """Serialize an :class:`Elf32Object`, laying out sections sequentially.

    Section names, ordering, and every field except file offsets/sizes are
    kept as given; ``.shstrtab`` is reused unchanged (this module never
    renames or adds sections), so no string-table bookkeeping is needed here.
    """
    shstrndx = obj.section_index(".shstrtab")
    if shstrndx is None:
        raise ValueError("object has no .shstrtab section")

    # Section offsets in the header are file-absolute, but `body` is only
    # the part of the file that comes *after* the ELF header -- every offset
    # written out below must add the header's own size back in.
    header_size = _EHDR.size

    body = bytearray()
    offsets = [0] * len(obj.sections)
    for i, sec in enumerate(obj.sections):
        if i == 0:
            offsets[i] = 0
            continue
        if sec.type == SHT_NOBITS:
            # NOBITS occupies no file space, so its offset is conventional
            # only; keep whatever it had rather than inventing a new one.
            offsets[i] = sec.file_offset or header_size + len(body)
            continue
        align = sec.addralign or 1
        pad = (-(header_size + len(body))) % align
        target = header_size + len(body) + pad
        # Keep the section where it was if the (only ever shrinking) sections
        # ahead of it left room -- see Section.file_offset.
        if sec.file_offset >= target and sec.file_offset % align == 0:
            target = sec.file_offset
        body.extend(b"\x00" * (target - header_size - len(body)))
        offsets[i] = target
        body.extend(sec.data)

    # IRIX .mdebug stores absolute file offsets in its Symbolic HDRR.  A
    # function-size transform can move this section even though its own
    # contents are unchanged; keep those pointers valid for asm-processor's
    # static-symbol conversion.
    for i, sec in enumerate(obj.sections):
        if sec.type != SHT_MIPS_DEBUG or not sec.file_offset or offsets[i] == sec.file_offset:
            continue
        shift = offsets[i] - sec.file_offset
        if len(sec.data) < 0x60:
            raise ValueError("truncated .mdebug symbolic header")
        fields = list(struct.unpack(">HH" + "I" * 23, sec.data[:0x60]))
        max_offset_pairs = ((3, 4), (5, 6), (7, 8), (9, 10), (11, 12),
                            (13, 14), (15, 16), (17, 18), (19, 20),
                            (21, 22), (23, 24))
        for max_index, offset_index in max_offset_pairs:
            if fields[max_index] and fields[offset_index]:
                fields[offset_index] += shift
        relocated = struct.pack(">HH" + "I" * 23, *fields)
        start = offsets[i] - header_size
        body[start : start + 0x60] = relocated

    align = 4
    pad = (-(header_size + len(body))) % align
    body.extend(b"\x00" * pad)
    shoff = header_size + len(body)

    header = _EHDR.pack(
        b"\x7fELF\x01\x02\x01" + b"\x00" * 9,
        obj.e_type,
        obj.e_machine,
        obj.e_version,
        obj.e_entry,
        0,  # e_phoff
        shoff,
        obj.e_flags,
        _EHDR.size,
        0,  # e_phentsize
        0,  # e_phnum
        _SHDR.size,
        len(obj.sections),
        shstrndx,
    )

    shdrs = bytearray()
    shstrtab = obj.sections[shstrndx].data
    for i, sec in enumerate(obj.sections):
        if i == 0:
            shdrs.extend(_SHDR.pack(0, 0, 0, 0, 0, 0, 0, 0, 0, 0))
            continue
        sh_name = shstrtab.index((sec.name + "\x00").encode("latin1"))
        size = sec.nobits_size if sec.type == SHT_NOBITS else len(sec.data)
        shdrs.extend(
            _SHDR.pack(
                sh_name,
                sec.type,
                sec.flags,
                sec.addr,
                offsets[i],
                size,
                sec.link,
                sec.info,
                sec.addralign,
                sec.entsize,
            )
        )

    return bytes(header) + bytes(body) + bytes(shdrs)
