#!/bin/env python3
# Misc. Ghidra helpers. The Python Ghidra API can be a bit wonky
# since some script helpers project out Java types, and need some
# adaptation to get back to something that's sane/Pythonic.

def askFilePython(askFile, title, mode):
	javaFile = askFile(title, "File")
	path = javaFile.getAbsolutePath()
	return open(path, mode)

def askCsvFilePython(askFile, title, mode):
	javaFile = askFile(title, "File")
	path = javaFile.getAbsolutePath()
	return open(path, mode, newline='')
