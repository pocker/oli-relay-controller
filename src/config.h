#pragma once

#define INPUTS 3
#define OUTPUTS 3
#define MAX_PROFILE 2

struct Wifi
{
    char ssid[16];
    char password[16];
};

struct User
{
    char username[10];
    char password[10];
};

struct Profile
{
    int active;
    unsigned int configuration[MAX_PROFILE][OUTPUTS];
    unsigned int *getActiveProfile(){
        return this->configuration[this->active];
    };
};

struct Config
{
    unsigned int checksum;
    struct Profile profile;
    struct Wifi wifi;
    struct User user;
};

const Config DEFAULT_CONFIG = {
    0,
    {0, {0b000000, 0b000000, 0b000000, 0b000000, 0b000000, 0b000000}},
    {"", ""},
    {"admin", "admin"}};

typedef struct Config Config;

Config *loadConfig();

void initConfig();

bool loadConfig(Config *config);

void writeConfig(Config *config);

void wipeConfig();

unsigned int checksum(Config *config);

unsigned int checksum(void *ptr, int size, int skipp = 0);
