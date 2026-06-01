#ifndef OILSENSOR_H
#define OILSENSOR_H
#include <Preferences.h>


#define SENSOR_OilLevelEmpty      0x4041
#define SENSOR_OilLevel_10        0x4243
#define SENSOR_OilLevel_20        0x4445
#define SENSOR_OilLevel_30        0x4647
#define SENSOR_OilLevel_40        0x4849
#define SENSOR_OilLevel_50        0x4A4B
#define SENSOR_OilLevel_60        0x4C4D
#define SENSOR_OilLevel_70        0x4E4F
#define SENSOR_OilLevel_80        0x5051
#define SENSOR_OilLevel_90        0x5253
#define SENSOR_OilLevelFull       0x5455


#define SENSOR_Temperature_30     0x5051
#define SENSOR_Temperature_40     0x5253
#define SENSOR_Temperature_50     0x5455
#define SENSOR_Temperature_55     0x5657
#define SENSOR_Temperature_60     0x5859
#define SENSOR_Temperature_65     0x5A5B
#define SENSOR_Temperature_70     0x5C5D
#define SENSOR_Temperature_75     0x5e5f
#define SENSOR_Temperature_80     0x6061
#define SENSOR_Temperature_85     0x6263
#define SENSOR_Temperature_90     0x6465
#define SENSOR_Temperature_95     0x6667
#define SENSOR_Temperature_100    0x6869
#define SENSOR_Temperature_105    0x7071
#define SENSOR_Temperature_110    0x7273
#define SENSOR_Temperature_115    0x7475
                    
                                        

#define OilLevelPercentageErrorValue                  0xFF
#define OilTemperaturePercentageErrorValue            0xFF

#define OilLevelPercentageInitValue                   0xFE
#define OilTemperaturePercentageInitValue             0xFE


#define OilLevelPercentageDebugValue                  0xFD
#define OilTemperaturePercentageDebugValue            0xFD


extern bool TimeoutSensorDetected;

extern uint8_t oilTemperature;
extern uint8_t oilLevelPercentage ;



extern uint8_t testValue_oilTemperature;
extern uint8_t testValue_oilLevelPercentage;
extern uint16_t OilTempCompValues[16];
extern uint16_t OilLevelCompValues[11];
extern uint16_t NewOilTempCompValues[16];
extern uint16_t NewOilLevelCompValues[11];
void convertImpulseToPercentage(uint16_t cntRawData_Temp, uint16_t cntRawData_Level,uint8_t session,bool newData,bool TimeoutSensorDetected);

#endif /* OILSENSOR_COMMON_H */