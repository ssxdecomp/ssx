#include "common.h"

// Forward declarations. These will be removed once the functions match.
void systemInit();
void bxInit();
void bxMain(const char* pszExe);
void bxRestore();

void bxUnk(int argc, char** argv);

INCLUDE_ASM("asm/nonmatchings/bx/main/main", bxInit__Fv);

INCLUDE_ASM("asm/nonmatchings/bx/main/main", bxMain__FPCc);

INCLUDE_ASM("asm/nonmatchings/bx/main/main", bxRestore__Fv);

// Fun trivia: In an interview with Scott Henshaw (lead director for SSX OG), he says:
// <QUOTE>
// Getting there, like spending your entire Christmas break trying to get a CD to simply boot working with Our lead SE Jon Spencer was a challenge.
// We had a hand-soldered PS2 direct from Sony, but no docs were written yet.
// Jon had to guess at using the same boot sequence as a PS1. 
// To debug it we added a screen clear to a different color after each line of code (there was no debugger).
// each time he compiled and built I had to create a bootable disc with the sony PS1 tools (think 1 hr per disk).
// Then try and boot it and figure out which colour we got stuck at.
// Took the two of us 5 days just to get that working.  
// The challenge was fun.
// </QUOTE>
//
// The one paramater passed to this function looks *suspiciously* like 
// a GS BGCOLOR. In other words: This function probably did exactly this.
// It's kind of funny that it was never removed.
void __NullFunc(u32) {
    return;
}

INCLUDE_ASM("asm/nonmatchings/bx/main/main", systemInit__Fv);

INCLUDE_ASM("asm/nonmatchings/bx/main/main", main);

#if 0
int main(int argc, char** argv) {
    __NullFunc(0x2080ff);
    systemInit();
    bxUnk(argc, argv);
    bxInit();
    bxMain(argv[0]);
    bxRestore();
    return 0;
}
#endif