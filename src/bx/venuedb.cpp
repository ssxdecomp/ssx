#include "bx/venuedb.h"

cVenueDB::cVenueDB()
{
	purge();
}

INCLUDE_ASM("bx/venuedb", _$_8cVenueDB);
#if 0
cVenueDB::~cVenueDB() 
{
    purge();
}
#endif

INCLUDE_ASM("bx/venuedb", initOnce__8cVenueDB);

void cVenueDB::purge()
{
	mVenueCount = 0;
	mUnk = 0;
}

INCLUDE_ASM("bx/venuedb", getName__8cVenueDBi);
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
#endif

INCLUDE_ASM("bx/venuedb", getBigfileName__8cVenueDBi);
#if 0
const char* cVenueDB::getBigfileName(i32 venueId) 
{
    if(venueId >= 0) 
    {
        venueId = mVenueCount > venueId;
    }
    return mVenues[venueId].bigFilename;
}
#endif

INCLUDE_ASM("bx/venuedb", findVenueIndex__8cVenueDBPCc);
#if 0
i32 cVenueDB::findVenueIndex(const char* pszName) 
{
    i32 i = 0;
    tListEntry* pVenue = &mVenues[0];
    while(true) 
    {
        if(mVenueCount <= i)
            break;
        
        if(strcmp(pszName, pVenue->bigFileName) == 0)
            break;
        
        pVenue++;
        i++;
    }

    return i;
}
#endif

INCLUDE_ASM("bx/venuedb", checkId__8cVenueDBi);

i32 cVenueDB::clampId(i32 id)
{
	i32 venueId = mVenues[id].venueId;
	// static_cast<> is needed here since arraysize() returns a unsigned integer.
	if (static_cast<i32>(arraysize(mVenues) - 1) < venueId)
		venueId = (arraysize(mVenues) - 1);
	return venueId;
}