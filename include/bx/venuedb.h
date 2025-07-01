typedef enum {
    kVenueID_Snowdream,
    kVenueID_Mesablanca,
    kVenueID_Ramstein,
    kVenueID_Pipedream,
    kVenueID_Elysium,
    kVenueID_Aloha,
    kVenueID_BigAirDome,
    kVenueID_Merqury,
    kVenueID_Circuit, // Actually warmum
    kVenueID_Frontend3D = 0xffffffff
} eVenueId;

typedef struct {
    eVenueId id;
    const char* name; // The full name. E.g: "Snow Dream"
    const char* displayName;
    int showoffTimeLimit; // In game ticks (60hz)
    const char* alternateName;
    const char* bigFileName;
} tVenueDBEntry;

class cVenueDB {
    typedef struct {
        char bigFileName[64];
        char alternateName[64];
        eVenueId venueId;
    } tListEntry;

public:
    cVenueDB();
    ~cVenueDB();

    void initOnce();
    void purge();

    const char* getName(eVenueId id);
    const char* getBigfileName(eVenueId id);

    int findVenueIndex(const char* name);

    eVenueId checkId(eVenueId id);

    static tVenueDBEntry venueDB[12];
};
