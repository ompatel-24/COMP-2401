#define MAX_STR 16
#define MAX_READINGS 16

#define ERR_OK 0
#define ERR_MAX_CAPACITY -1
#define ERR_INVALID_VALUE -2
#define ERR_NOT_IMPLEMENTED -3

struct Device {
    char name[MAX_STR];
    float max;
    float min;
};

struct Reading {
    struct Device  *device;
    float           value;
    char            room[MAX_STR];
};

struct ReadingCollection {
    int size;
    struct Reading elements[MAX_READINGS];
};


int init_device(struct Device *device, char *name, float max, float min);
int init_reading(struct Reading *reading, struct Device *device, float value, char const* room);

int init_reading_collection(struct ReadingCollection *readings);

int valid_device_reading(struct Device *device, float value);

int add_reading(struct ReadingCollection *readings, struct Reading reading);

int print_reading(const struct Reading *reading);
int print_reading_collection(struct ReadingCollection *readings);

// For side quest
int remove_duplicates(struct ReadingCollection *readings);