#include "dtc_oilsensor.h"
#include "dtc_oilsensor_defines.h"
#include "brand_defines_common.h"
#include <Preferences.h>




extern Preferences preferences;
extern uint8_t oilSensorSelector;
extern uint8_t waterSensorSelector;
extern uint8_t brandSelector;


extern String  oemPartNumberWaterTempSensor;                    //         =  DEFAULT_OEM_PARTNUMBER_WATER_TEMPSENSOR;
extern String  supplierPartNumberWaterTempSensor;               //         =  DEFAULT_SUPPLIER_PARTNUMBER_WATER_TEMPSENSOR;
uint32_t DTC_Storage;



void checkCoding()
{
    if(
       ((oilSensorSelector == SENSOR_OILTEMPSENSOR_VW_COMBISENSOR_G266_03C_907_660_C_D_H_M_T) && (brandSelector != BRAND_VW))
    || ((oilSensorSelector == SENSOR_OILTEMPSENSOR_VW_COMBISENSOR_G266_07P_907_660) && (brandSelector != BRAND_VW))
    || ((oilSensorSelector == SENSOR_OILTEMPSENSOR_VW_COMBISENSOR_G266_1J0_907_660_C_F) && (brandSelector != BRAND_VW))
    || ((oilSensorSelector == SENSOR_OILTEMPSENSOR_BMW_RESERVED) && (brandSelector != BRAND_BMW))
    || ((oilSensorSelector == SENSOR_OILTEMPSENSOR_MERCEDES_RESERVED) && (brandSelector != BRAND_MERCEDES_OLD))
    )
    {
      setDTC(DTC_BIT_01_WRONG_CODING_BRAND);
    }

    if(
    ((waterSensorSelector == SENSOR_WATERTEMPSENSOR_VW_COMBISENSOR_G62_G2_GREEN_ROUND_4_PINS) && (brandSelector != BRAND_VW))
    || ((waterSensorSelector == SENSOR_WATERTEMPSENSOR_VW_COMBISENSOR_G62_G2_BLUE_QUARTER_4_PINS) && (brandSelector != BRAND_VW))
    || ((waterSensorSelector == SENSOR_WATERTEMPSENSOR_BMW_RESERVED) && (brandSelector != BRAND_BMW))
    || ((waterSensorSelector == SENSOR_WATERTEMPSENSOR_MERCEDES_RESERVED) && (brandSelector != BRAND_MERCEDES_OLD))
    )
    {
      setDTC(DTC_BIT_01_WRONG_CODING_BRAND);
    }

    if(
    ((waterSensorSelector == SENSOR_WATERTEMPSENSOR_NO_WATER_TEMPSENSOR) && (brandSelector != BRAND_VW))
    ||(waterSensorSelector == SENSOR_WATERTEMPSENSOR_UNDEFINED)
    )
    {
      setDTC(DTC_BIT_03_WRONG_CODING_WATER_SENSOR);
    }

    if(
    ((oilSensorSelector == SENSOR_OILTEMPSENSOR_NO_OILTEMPSENSOR) && (brandSelector != BRAND_VW))
    || (oilSensorSelector == SENSOR_OILTEMPSENSOR_UNDEFINED)
    )
    {
      setDTC(DTC_BIT_02_WRONG_CODING_OIL_SENSOR);
    }
}



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