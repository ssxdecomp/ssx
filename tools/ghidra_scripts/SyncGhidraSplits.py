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

from ghidra.program.model.listing import CodeUnit
import shlex

# Shared database stuff
from SplitDatabaseTypes import SplitKind, SplitLanguage, SplitRecord
from SplitDatabaseWriter import SplitDatabaseWriter

import GhidraHelpers

knownSplitRecords : list[SplitRecord] = []

### The last queued split record.
queuedSplitRecord = None

### Parses a single split comment from Ghidra.
def parseSplitComment(address: int, comment: str):
	global queuedSplitRecord
	split = shlex.split(comment)
	splitPath = PurePath(split[2])
	splitFileName = str(splitPath.with_suffix(""))

	if len(split) > 3:
		# end record
		assert len(split) == 5 # Only valid amount of fields
		assert split[3] == 'END'

		# An end record can also be the only seen record if only one function/data member
		# is actually part of the split, so make sure to handle that.
		if queuedSplitRecord is None:
			queuedSplitRecord = SplitRecord()
			queuedSplitRecord.name = splitFileName
			queuedSplitRecord.start = address
			queuedSplitRecord.kind = SplitKind.parse(split[1])
			queuedSplitRecord.language = SplitLanguage.parse(splitPath.suffix)
		queuedSplitRecord.end = int(split[4], 16)

		assert queuedSplitRecord.end >= queuedSplitRecord.start # Make sure splits are entered correcly

		knownSplitRecords.append(queuedSplitRecord)
		queuedSplitRecord = None
	else:
		# Start record
		if queuedSplitRecord is None:
			queuedSplitRecord = SplitRecord()
			queuedSplitRecord.name = splitFileName
			queuedSplitRecord.start = address
			queuedSplitRecord.kind = SplitKind.parse(split[1])
			queuedSplitRecord.language = SplitLanguage.parse(splitPath.suffix)

# Go through all plate comments, and process known split record comments.
# This will populate knownSplitRecords[] with all the splits that are in the project.
listing = currentProgram.getListing()
addressSet = currentProgram.getAddressFactory().getAddressSet()
for addr in listing.getCommentAddressIterator(addressSet, True):
	plateComment = listing.getComment(CodeUnit.PLATE_COMMENT, addr)
	if plateComment and plateComment.startswith('SPLIT'):
		parseSplitComment(addr.getOffset(), plateComment)

# Write the records to the split database file
with GhidraHelpers.askCsvFilePython(askFile, 'Select splits.csv file to sync', 'w') as csvFile:
	dbWriter = SplitDatabaseWriter(csvFile)
	for record in knownSplitRecords:
		dbWriter.writeRecord(record)
