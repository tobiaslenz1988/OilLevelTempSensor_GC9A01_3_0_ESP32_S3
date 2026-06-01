#include <Arduino.h>
#include <stdio.h>
#include "oilsensor.h"
#include "nrc_uds_protocol.h"


extern uint8_t oilTemperature;
extern uint8_t oilLevelPercentage;


extern uint8_t testValue_oilTemperature;
extern uint8_t testValue_oilLevelPercentage;

extern uint16_t OilTempCompValues[16];
extern uint16_t OilLevelCompValues[11];


/* This methods converts the received impulses to an Percentage for OilLevel and Oil Temperature*/
void convertImpulseToPercentage(uint16_t TemperatureImpulses, uint16_t LevelImpulses,uint8_t session,bool newData,bool TimeoutSensorDetected) {
  if (session == UDS_Session_Control_Default_Session) 
  { /* Debug of... normal Operation*/
    if(TimeoutSensorDetected == false)
    {
        if(newData){
            //if (LevelImpulses > OilLevelCompValues[10]) { oilLevelPercentage = OilLevelPercentageErrorValue; }else
            if (LevelImpulses > OilLevelCompValues[10]) { oilLevelPercentage = 78; }else
            if (LevelImpulses = OilLevelCompValues[10]) { oilLevelPercentage = 100; }else
            if (LevelImpulses >= OilLevelCompValues[9]) { oilLevelPercentage = 90; }else
            if (LevelImpulses >= OilLevelCompValues[8]) { oilLevelPercentage = 80; }else
            if (LevelImpulses >= OilLevelCompValues[7]) { oilLevelPercentage = 70; }else
            if (LevelImpulses >= OilLevelCompValues[6]) { oilLevelPercentage = 60; }else
            if (LevelImpulses >= OilLevelCompValues[5]) { oilLevelPercentage = 50; }else
            if (LevelImpulses >= OilLevelCompValues[4]) { oilLevelPercentage = 40; }else
            if (LevelImpulses >= OilLevelCompValues[3]) { oilLevelPercentage = 30; }else
            if (LevelImpulses >= OilLevelCompValues[2]) { oilLevelPercentage = 20; }else
            if (LevelImpulses >= OilLevelCompValues[1]) { oilLevelPercentage = 10; }else
            if (LevelImpulses >= OilLevelCompValues[0]) {oilLevelPercentage = 0; }
          
            if (oilLevelPercentage > 0) {        
              if (TemperatureImpulses > OilTempCompValues[15]) { oilTemperature = OilTemperaturePercentageErrorValue; }else
              if (TemperatureImpulses =  OilTempCompValues[15]) { oilTemperature = 115; }else
              if (TemperatureImpulses >= OilTempCompValues[14]) { oilTemperature = 110; }else
              if (TemperatureImpulses >= OilTempCompValues[13]) { oilTemperature = 105; }else
              if (TemperatureImpulses >= OilTempCompValues[12]) { oilTemperature = 100; }else
              if (TemperatureImpulses >= OilTempCompValues[11]) { oilTemperature = 95; }else
              if (TemperatureImpulses >= OilTempCompValues[10]) { oilTemperature = 90; }else
              if (TemperatureImpulses >= OilTempCompValues[9]) { oilTemperature = 85; }else
              if (TemperatureImpulses >= OilTempCompValues[8]) { oilTemperature = 80; }else
              if (TemperatureImpulses >= OilTempCompValues[7]) { oilTemperature = 75; }else
              if (TemperatureImpulses >= OilTempCompValues[6]) { oilTemperature = 70; }else
              if (TemperatureImpulses >= OilTempCompValues[5]) { oilTemperature = 65; }else
              if (TemperatureImpulses >= OilTempCompValues[4]) { oilTemperature = 60; }else
              if (TemperatureImpulses >= OilTempCompValues[3]) { oilTemperature = 55; }else
              if (TemperatureImpulses >= OilTempCompValues[2]) { oilTemperature = 50; }else
              if (TemperatureImpulses >= OilTempCompValues[1]) { oilTemperature = 40; }else
              if (TemperatureImpulses >= OilTempCompValues[0]) { oilTemperature = 30; }
            }else{ oilTemperature = OilTemperaturePercentageInitValue;}
        }
    }else{
      /* if Oil Sensor is disconnected  and TO is detected */
      //oilTemperature      = OilTemperaturePercentageErrorValue;
      oilTemperature      = 81;
      oilLevelPercentage  = 81;
    }
  } else if (session == UDS_Session_Control_Development_Session || session == UDS_Session_Control_Extended_Session){
    /*Debug On*/
    oilTemperature      = testValue_oilTemperature;
    oilLevelPercentage  = testValue_oilLevelPercentage;
  }
}
