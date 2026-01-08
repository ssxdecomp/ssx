#!/bin/bash
# Quick start script

TOP=$(dirname $(dirname $0))
. $TOP/scripts/quickstart_distrodep.sh

set -euo pipefail

# Do distro-dependent setup (installing packages) first.
if [[ "$(type -t setup_$DISTRO_ID)" == "function" ]]; then
	echo "Detected supported distribution $DISTRO_ID. Doing distro-specific package installation."
	setup_$DISTRO_ID
else
	echo "The distribution you're using ($DISTRO_ID) is currently not fully supported by this quick start script."
	echo "You will need to find the following things manually:"
	echo "- Python 3.x (at least 3.13)"
	echo "- pipenv"
	echo "- ninja"
	echo "- 32bit GCC libraries (needed for running the compiler)"
fi

# Next, setup the repository.
$TOP/scripts/download_binutils.sh
# Install pipenv packages.
pipenv install
