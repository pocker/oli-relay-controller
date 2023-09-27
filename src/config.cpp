#include "config.h"

#include <EEPROM.h>

void initConfig()
{
    EEPROM.begin(sizeof(Config));
}

bool loadConfig(Config *config)
{
    EEPROM.readBytes(0, config, sizeof(Config));
    unsigned int sum = checksum(config);

    Serial.print("Calculated: ");
    Serial.println(sum);
    Serial.print("Cofnig checksum: ");
    Serial.println(config->checksum);

    bool valid = sum == config->checksum;

    if (!valid)
    {
        memcpy(config, &DEFAULT_CONFIG, sizeof(Config));
    }

    return valid;
}

Config *loadConfig()
{
    Config *config = (Config *)malloc(sizeof(Config));
    loadConfig(config);
    return config;
}

void writeConfig(Config *config)
{
    config->checksum = checksum(config);
    EEPROM.writeBytes(0, config, sizeof(Config));
    EEPROM.commit();
}

unsigned int checksum(void *ptr, int size, int skipp)
{
    unsigned int sum = 0;
    for (int i = skipp; i < size; i++)
    {
        sum += *((char *)ptr + i);
    }
    return sum;
}

unsigned int checksum(Config *config)
{
    return checksum(config, sizeof(Config), sizeof(int));
}

void wipeConfig()
{
    EEPROM.writeBytes(0, &DEFAULT_CONFIG, sizeof(Config));
    EEPROM.commit();
}