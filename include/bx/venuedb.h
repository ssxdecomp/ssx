#include "common.h"

typedef enum {
    kVenueID_Snowdream,
    kVenueID_Mesablanca,
    kVenueID_Ramstein,
    kVenueID_Pipedream,
    kVenueID_Elysium,
    kVenueID_Aloha,
    kVenueID_BigAirDome,
    kVenueID_Merqury,
    kVenueID_Circuit, // Actually warmup
    kVenueID_Frontend3D = 0xffffffff
} eVenueId;

typedef struct {
    i32 id;
    const char* name; // The full name. E.g: "Snow Dream"
    const char* displayName;
    int showoffTimeLimit; // In game ticks (60hz)
    const char* alternateName;
    const char* bigFileName;
} tVenueDBEntry;

// There are external references to this, so I imagine it's either
// an extern like so, or a public static inside of cVenueDB.
extern tVenueDBEntry venueDB[12];

class cVenueDB {
    typedef struct {
        char bigFilename[64];
        char alternateName[64];
        i32 venueId;
    } tListEntry;

public:
    cVenueDB();
    ~cVenueDB();

    // Initalizes the venue database.
    void initOnce();

    // purges the database.
    void purge();

    const char* getName(i32 id);
    const char* getBigfileName(i32 id);

    int findVenueIndex(const char* name);

    i32 checkId(i32 id);
    i32 clampId(i32 id);

private:
    int mVenueCount;
    tListEntry mVenues[12];
    int mUnk;
};
