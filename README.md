# SSX (2000)

This is a work-in-progress matching decompilation of SSX (2000) for the PlayStation 2.

This project builds the NTSC-U version of the game (`SLUS_200.95`, SHA1 `72d85fcefffc2bcaa1eeacbc02a8965ababb6e92`). 

Other regions and versions may be considered once NTSC-U has been completed.

## Setup

You will need:

- a Linux system that can run 32 bit applications. (WSL2 works in a pinch, but won't be as fast.)
- Python (and pipenv)
- A NTSC-U disc image (obtained legally)

Make a `disc` directory in the root of this repository, and copy the files from the NTSC-U game disc.

Run the quick start script. On supported distributions (feel free to PR support), the script will install all of the dependencies for you automatically and run all of the setup steps.

```bash
$ ./scripts/quickstart.sh
```

Once the quickstart script finishes, run the following commands:

```bash
$ pipenv shell
(ssx) $ ./configure.py
```

## Building

Simply run `ninja`.
