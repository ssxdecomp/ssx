#ifndef BX_INPUT_PADCACHE_H
#define BX_INPUT_PADCACHE_H

#include "common.h"

// TODO: this is defined in this source file..?
class cPadDevice;

class cPadCache
{
	// The input cache buffer. This is internally implemented as a
	// circular buffer of records that consist of each joypad's data (in its own format), that
    // it is responsible for converting to a BX-shared format once the game actually
    // wants to use it.
    // 
    // It is probably possible for different joypad implementations
    // to work with this setup, however BX itself uses a single subclass.
	u8* pInputCache;

    // The size of a single input cache element in bytes.
	u32 cacheElemByteSize;

    // The amount of entires in the input cache buffer.
	u32 cacheNumRecords;

	// The read pointer of the input cache buffer.
	u32 cacheReadPtr;

    // The write pointer of the input cache buffer.
    u32 cacheWritePtr;

    // Joypads.
    cPadDevice* joypads[4];
public:
    void init();
    void purge();
};

#endif