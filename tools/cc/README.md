# Compiler tools

The following compilers were known to be used for SSX OG:

| Compiler                | Description                                                                                                          |
| ----------------------- | -------------------------------------------------------------------------------------------------------------------- |
| ee-gcc 2.9-ee-990721    | From the Pre-release toolchain 0.5.0 (EB-S8220) for the EE. Used presumably from release of TC 0.5 to TC 2.0 release |
| ee-gcc 2.9-ee-991111-01 | Used from Toolchain 2.0 Release date (August 20, 2000) to gold builds                                                |

We have been able to recover important compiler flags (for at least C) from a makefile fragment that was pressent in a US demo build. They are:

| Type                    | Flags                                    | Notes                                                              |
| ----------------------- | ---------------------------------------- | ------------------------------------------------------------------ |
| Debug                   | `-g -G0 -O0`                             | Interestingly also disables usage of gp register..                 |
| Test                    | `-g -O2 -fno-edge-lcm`                   | Close to release flags but with -g (debug info) and no fp-omission |
| Release (and ReleaseCD) | `-O2 -fno-edge-lcm -fomit-frame-pointer` | Adds fp-omission.                                                  |

It is surmised that `-fno-rtti` and possibly `-fno-exceptions` were also given for C++ compilation

`-fno-edge-lcm` does not exist in ee-990721, which is how it has been figured out that ee-991111-01 was used for the final builds.