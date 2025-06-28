# SSX (2000)

This is a work-in-progress decompilation of SSX (2000) for the PlayStation 2.

This project builds the NTSC-U version of the game (`SLUS_200.95`, sha1 `72d85fcefffc2bcaa1eeacbc02a8965ababb6e92`). Other regions and versions may be considered once NTSC-U has been completed and matched.

## Setup

You will need:

- a Linux system that can run 32 bit applications. WSL2 should work as well.
- Python (with pipenv)
- A NTSC-U disc image (obtained legally)

### Arch Linux

`# pacman -S lib32-gcc-libs`

### Debian/Ubuntu

`# apt install -y binutils-mips-linux-gnu ninja-build`


Make a `disc` directory in the root of this repository, and copy the files from the NTSC-U game disc.

Download required tools:

```bash
$ ./download.sh
```

Setup a venv for splat:

```bash
$ pipenv install
```

`pipenv run ./configure.py` ultimately does the setup.

## Building

`ninja` should do the trick.
