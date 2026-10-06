#!/bin/env python3
# Shared types for the split database

from enum import IntEnum

# The kind of split
class SplitKind(IntEnum):
	TEXT = 0
	DATA = 1
	SDATA = 2
	RODATA = 3
	BSS = 4
	SBSS = 5
	LIT4 = 6
	VUTEXT = 7
	VUDATA = 8
	VUBSS = 9

	def parse(sectionName: str) -> int:
		match sectionName:
			case ".text":
				return SplitKind.TEXT
			case ".data":
				return SplitKind.DATA
			case ".sdata":
				return SplitKind.SDATA
			case ".rodata":
				return SplitKind.RODATA
			case ".bss":
				return SplitKind.BSS
			case ".sbss":
				return SplitKind.SBSS
			case ".lit4":
				return SplitKind.LIT4
			case ".vutext":
				return SplitKind.VUTEXT
			case ".vudata":
				return SplitKind.VUDATA
			case ".vubss":
				return SplitKind.VUBSS
			case _:
				raise RuntimeError(f'Unknown section {sectionName}')

	def stringify(kind: int) -> str:
		match kind:
			case SplitKind.TEXT:
				return 'text'
			case SplitKind.DATA:
				return 'data'
			case SplitKind.SDATA:
				return 'sdata'
			case SplitKind.RODATA:
				return 'data'
			case SplitKind.BSS:
				return 'bss'
			case SplitKind.SBSS:
				return 'sbss'
			case SplitKind.LIT4:
				return 'lit4'
			case SplitKind.VUTEXT:
				return 'vutext'
			case SplitKind.VUDATA:
				return 'vudata'
			case SplitKind.VUBSS:
				return 'vubss'


class SplitLanguage(IntEnum):
	C = 0
	CXX = 1
	ASM = 2
	# ?
	VUDSM = 3
	VUVSM = 4

	def parse(extension: str) -> int:
		match extension:
			case ".c":
				return SplitLanguage.C
			case ".cpp":
				return SplitLanguage.CXX
			case ".s":
				return SplitLanguage.ASM
			# I forget exactly the direct meaning of these,
			# but they contain dmatag/giftags which have vu-asm code in them
			# (from what I remember)
			case ".dsm":
				return SplitLanguage.VUDSM
			case ".vsm":
				return SplitLanguage.VUVSM
			case _:
				raise RuntimeError(f'Unknown source file extension {extension}')

	def stringify(lang: int) -> str:
		match lang:
			case SplitLanguage.C:
				return 'c'
			case SplitLanguage.CXX:
				return 'cpp'
			case SplitLanguage.ASM:
				return 'asm'
			case SplitLanguage.VUDSM:
				return 'dsm'
			case SplitLanguage.VUVSM:
				return 'vsm'


class SplitRecord():
	def __init__(self):
		self.kind = SplitKind.TEXT
		self.name = ''
		self.language = SplitLanguage.C
		self.start = 0x0
		self.end = 0x0
