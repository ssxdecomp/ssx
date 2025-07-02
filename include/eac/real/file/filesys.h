#ifndef EAC_REALFILE_FILESYS_H
#define EAC_REALFILE_FILESYS_H

#if __cplusplus
extern "C" {
#endif

int FILESYS_existssync(const char* filename, int priority);

// FIXME: Add the non-sync versions when we import more filesys stuff :(
int FILESYS_addbigsync(const char* filename, int memflags, int priority, int* retbigptr);
int FILESYS_delbigsync(int bighandle, int priority);


#if __cplusplus
};
#endif

#endif