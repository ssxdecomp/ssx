# Sync Split Progress
#
# @category SSXDecomp
# @runtime PyGhidra
#
# This script syncs/creates data/splits.csv, which is
# the intermediate between the decomp and Ghidra database
# for the currently known source file splits. This CSV file
# is meant to be updated by this Ghidra script every time
# a new split is identified, without human modification.
#
# Splits in the Ghidra database are communicated via Plate Comments
# on code or data which first line start with "SPLIT", and follow the following format:
#
# SPLIT [section] [source file name] [END] [END address]
#
# SPLIT [section] [source file name] END marks the end of a split. If only an
# END exists, then the split is assumed to start and end with the marked data.
#
# The end address must exist in a END item.

from pathlib import PurePath
from enum import IntEnum
from ghidra.program.model.listing import CodeUnit
import shlex
import csv

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

class SplitLanguage(IntEnum):
	C = 0
	CXX = 1
	ASM = 2
	# ?
	VUDSM = 3
	VUVSM = 4

def parseSplitLanguage(extension: str) -> int:
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

def stringifySplitLanguage(lang: int) -> str:
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

def parseSplitKind(sectionName: str) -> int:
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

def stringifySplitKind(kind: int) -> str:
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

class SplitRecord():
	def __init__(self):
		self.kind = SplitKind.TEXT
		self.name = ''
		self.language = SplitLanguage.C
		self.start = 0x0
		self.end = 0x0

knownSplitRecords : list[SplitRecord] = []

queuedSplitRecord = None

def handleSplitComment(address: int, comment: str):
	global queuedSplitRecord

	split = shlex.split(comment)

	splitPath = PurePath(split[2])
	splitFileName = str(splitPath.with_suffix(""))

	if len(split) > 3:
		# end record
		assert len(split) == 5 # Only valid amount of fields
		assert split[3] == 'END'

		if queuedSplitRecord is None:
			queuedSplitRecord = SplitRecord()
			queuedSplitRecord.name = splitFileName
			queuedSplitRecord.start = address
			queuedSplitRecord.kind = parseSplitKind(split[1])
			queuedSplitRecord.language = parseSplitLanguage(splitPath.suffix)
		queuedSplitRecord.end = int(split[4], 16)

		knownSplitRecords.append(queuedSplitRecord)
		queuedSplitRecord = None
	else:
		# Start record
		if queuedSplitRecord is None:
			queuedSplitRecord = SplitRecord()
			queuedSplitRecord.name = splitFileName
			queuedSplitRecord.start = address
			queuedSplitRecord.kind = parseSplitKind(split[1])
			queuedSplitRecord.language = parseSplitLanguage(splitPath.suffix)

def askFilePython():
	javaFile = askFile("Select splits.csv file to sync", "Open")
	path = javaFile.getAbsolutePath()
	return open(path, 'w', newline='')


# Go through all plate comments, and process split record comments
listing = currentProgram.getListing()
addressSet = currentProgram.getAddressFactory().getAddressSet()
for addr in listing.getCommentAddressIterator(addressSet, True):
	plateComment = listing.getComment(CodeUnit.PLATE_COMMENT, addr)
	if plateComment and plateComment.startswith('SPLIT'):
		handleSplitComment(addr.getOffset(), plateComment)


with askFilePython() as csvFile:
	csvWriter = csv.writer(csvFile)
	csvWriter.writerow(['Name', 'Language', 'Kind', 'StartAddr', 'EndAddr'])
	for record in knownSplitRecords:
		csvWriter.writerow([record.name, stringifySplitLanguage(record.language), stringifySplitKind(record.kind), f'0x{record.start:08x}', f'0x{record.end:08x}'])
		#print(f'{record.name} {record.kind} {record.language} s {record.start:08x}-{record.end:08x}')
