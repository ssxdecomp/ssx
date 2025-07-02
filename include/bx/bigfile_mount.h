#ifndef BX_BIGFILE_MOUNT_H
#define BX_BIGFILE_MOUNT_H

#include "common.h"

// A class which mounts a bigfile.
class cBigfileMount {
    i32 mBigStatus;
    char mBigfileName[129];
    i32 mBigHandle;
public:
    cBigfileMount();
    ~cBigfileMount();

    i32 mount(const char* bigfileName, int memFlags);
    i32 unmount();
    void reset();
};


#endif