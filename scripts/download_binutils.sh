TOP=$(dirname $(dirname $0))

[[ -d "$TOP/tools/binutils" ]] && {
	echo "Decompals binutils seems to already exist. However, if you're trying to redownload it,"
	echo "run \"rm -rvf tools/binutils\" and run this script again."
	exit 0;
}

mkdir $TOP/tools/binutils
curl -Lo - https://github.com/decompals/binutils-mips-ps2-decompals/releases/latest/download/binutils-mips-ps2-decompals-linux-x86-64.tar.gz | tar -C $TOP/tools/binutils -xzvf -
