#include "bx/bigfile_mount.h"
#include "eac/real/file/filesys.h"
#include "libc/string.h"

cBigfileMount::cBigfileMount()
{
	reset();
}

INCLUDE_ASM("bx/main/bigfile_mount", _$_13cBigfileMount);

INCLUDE_ASM("bx/main/bigfile_mount", reset__13cBigfileMount);

i32 cBigfileMount::mount(const char* bigfileName, int memFlags)
{
	strcpy(&this->mBigfileName[0], bigfileName);
	int res = FILESYS_existssync(mBigfileName, 100);
	mBigStatus = static_cast<i32>(res != 0);
    if(res != 0) {
        res = FILESYS_addbigsync(mBigfileName, memFlags, 100, &mBigHandle);
        mBigStatus = static_cast<i32>(res != 0);
    }

    return mBigStatus;
}

INCLUDE_ASM("bx/main/bigfile_mount", unmount__13cBigfileMount);
