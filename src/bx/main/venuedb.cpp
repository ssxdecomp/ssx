#include "bx/venuedb.h"

cVenueDB::cVenueDB()
{
	purge();
}

cVenueDB::~cVenueDB() 
{
    purge();
}

INCLUDE_ASM("bx/main/venuedb", initOnce__8cVenueDB);

void cVenueDB::purge()
{
	mVenueCount = 0;
	mUnk = 0;
}

#if 0
// not matching :( but REALLY close
// (literally one wrong register off)
const char* cVenueDB::getName(i32 venueId) 
{
    if(venueId >= 0)
    {
        venueId = mVenueCount > venueId;
    }
    return mVenues[venueId].alternateName;
}
#else
INCLUDE_ASM("bx/main/venuedb", getName__8cVenueDBi);
#endif

#if 0
const char* cVenueDB::getBigfileName(i32 venueId) 
{
    if(venueId >= 0) 
    {
        venueId = mVenueCount > venueId;
    }
    return mVenues[venueId].bigFilename;
}
#else
INCLUDE_ASM("bx/main/venuedb", getBigfileName__8cVenueDBi);
#endif

#if 0
i32 cVenueDB::findVenueIndex(const char* pszName) 
{
    i32 i = 0;
    tListEntry* pVenue = &mVenues[0];
    while(true) 
    {
        if(mVenueCount <= i)
            break;
        
        if(strcmp(pszName, pVenue->bigFilename) == 0)
            break;
        
        pVenue++;
        i++;
    }

    return i;
}
#else
INCLUDE_ASM("bx/main/venuedb", findVenueIndex__8cVenueDBPCc);
#endif

#if 0
i32 cVenueDB::checkId(i32 id)
{
	for (i32 i = 0; i < mVenueCount; i++)
	{
		if (mVenues[i].venueId == id)
			return id;
	}
	return -1;
}
#else
INCLUDE_ASM("bx/main/venuedb", checkId__8cVenueDBi);
#endif

i32 cVenueDB::clampId(i32 id)
{
	i32 venueId = mVenues[id].venueId;
	// static_cast<> is needed here since arraysize() returns a unsigned integer.
	if (static_cast<i32>(arraysize(mVenues) - 1) < venueId)
		venueId = (arraysize(mVenues) - 1);
	return venueId;
}