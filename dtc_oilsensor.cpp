#include "dtc_oilsensor.h"
#include <Preferences.h>


extern Preferences preferences;

uint32_t DTC_Storage;

void deleteDTC (void)
{
    uint32_t temp =  preferences.getUInt("DTC_Storage",0xFFFFFFFF);
    if(temp != 0)
    {
        DTC_Storage = 0x00000000;
        preferences.putUInt("DTC_Storage",DTC_Storage);
    }
}

void setDTC(uint32_t DTCBit)
{
    DTC_Storage |= DTCBit;
    uint32_t temp =  preferences.getUInt("DTC_Storage",0xFFFFFFFF);
    if(((temp & DTCBit) != 1))
    {
          preferences.putUInt("DTC_Storage",DTC_Storage);
    }
    
}


bool readDTC(uint32_t DTCBit)
{
    bool returnval = false;
    uint32_t temp =  preferences.getUInt("DTC_Storage",0xFFFFFFFF);
    if(((temp & DTCBit) == 1))
    {
        returnval = true;
    }
    return returnval;
}

uint32_t readFullDTC(void)
{
    return preferences.getUInt("DTC_Storage",0xFFFFFFFF);
}

void update_DTCStorage(void)
{
    DTC_Storage = preferences.getUInt("DTC_Storage",0x0);
}

uint8_t numberOfDTCEntries(void)
{   uint8_t retval = 0;
     
    for(int i =0;i<32;i++)
    {
        if(DTC_Storage & ( 1 << i ))
        {
            retval++;
        }
    }
    
    return retval;
}

void setDTCStorageObject(uint32_t storage)
{
    DTC_Storage = storage;
}

uint32_t getDTCStorageObject(void)
{
    return DTC_Storage;
}