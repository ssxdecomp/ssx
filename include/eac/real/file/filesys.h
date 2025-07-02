#ifndef EAC_REALFILE_FILESYS_H
#define EAC_REALFILE_FILESYS_H

#if __cplusplus
extern "C" {
#endif

// FIXME: Add the non-sync versions when we import more filesys stuff :(
bool FILESYS_addbigsync(const char* filename, int memflags, int priority, int* retbigptr);
bool FILESYS_delbigsync(int bighandle, int priority);


#if __cplusplus
};
#endif