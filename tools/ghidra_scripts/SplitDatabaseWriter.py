#!/bin/env python3
import csv
from SplitDatabaseTypes import SplitKind, SplitLanguage, SplitRecord

### Adapter to insulate writing the split database in SyncGhidraScripts.
class SplitDatabaseWriter():
    def __init__(self, csvFile):
        self._csvWriter = csv.writer(csvFile)
        self._csvWriter.writerow(['Name', 'Language', 'Kind', 'StartAddr', 'EndAddr'])
    def writeRecord(self, record: SplitRecord):
        self._csvWriter.writerow([record.name, SplitLanguage.stringify(record.language), SplitKind.stringify(record.kind), f'0x{record.start:08x}', f'0x{record.end:08x}'])
