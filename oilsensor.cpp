#include <Arduino.h>
#include <stdio.h>
#include "oilsensor.h"
#include "nrc_uds_protocol.h"

extern bool TimeoutSensorDetected;
extern bool NewOilSensorEquipped; 

extern uint8_t oilTemperature;
extern uint8_t oilLevelPercentage;


extern uint8_t testValue_oilTemperature;
extern uint8_t testValue_oilLevelPercentage;

extern uint16_t OilTempCompValues[16];
extern uint16_t OilLevelCompValues[11];



/* This methods converts the received impulses to an Percentage for OilLevel and Oil Temperature*/
void convertImpulseToPercentage(uint16_t cntRawData_Temp, uint16_t cntRawData_Level,uint8_t session) {
  if (session == UDS_Session_Control_Default_Session) 
  { /* Debug of... normal Operation*/
    if(TimeoutSensorDetected == false)
	{
      if(NewOilSensorEquipped==true)
	  {

      }else{
        if (cntRawData_Level > OilLevelCompValues[10]) { oilLevelPercentage = 253; }else
        if (cntRawData_Level = OilLevelCompValues[10]) { oilLevelPercentage = 100; }else
        if (cntRawData_Level >= OilLevelCompValues[9]) { oilLevelPercentage = 90; }else
        if (cntRawData_Level >= OilLevelCompValues[8]) { oilLevelPercentage = 80; }else
        if (cntRawData_Level >= OilLevelCompValues[7]) { oilLevelPercentage = 70; }else
        if (cntRawData_Level >= OilLevelCompValues[6]) { oilLevelPercentage = 60; }else
        if (cntRawData_Level >= OilLevelCompValues[5]) { oilLevelPercentage = 50; }else
        if (cntRawData_Level >= OilLevelCompValues[4]) { oilLevelPercentage = 40; }else
        if (cntRawData_Level >= OilLevelCompValues[3]) { oilLevelPercentage = 30; }else
        if (cntRawData_Level >= OilLevelCompValues[2]) { oilLevelPercentage = 20; }else
        if (cntRawData_Level >= OilLevelCompValues[1]) { oilLevelPercentage = 10; }else
        if (cntRawData_Level >= OilLevelCompValues[0]) {oilLevelPercentage = 0; }
      }


      if(NewOilSensorEquipped==true){
        if (oilLevelPercentage > 0) {
         
        }else{ oilTemperature = OilTemperaturePercentageErrorValue;}
      }else{
        if (oilLevelPercentage > 0) {
          
          if (cntRawData_Temp > OilTempCompValues[15]) { oilTemperature = 253; }else
          if (cntRawData_Temp =  OilTempCompValues[15]) { oilTemperature = 115; }else
          if (cntRawData_Temp >= OilTempCompValues[14]) { oilTemperature = 110; }else
          if (cntRawData_Temp >= OilTempCompValues[13]) { oilTemperature = 105; }else
          if (cntRawData_Temp >= OilTempCompValues[12]) { oilTemperature = 100; }else
          if (cntRawData_Temp >= OilTempCompValues[11]) { oilTemperature = 95; }else
          if (cntRawData_Temp >= OilTempCompValues[10]) { oilTemperature = 90; }else
          if (cntRawData_Temp >= OilTempCompValues[9]) { oilTemperature = 85; }else
          if (cntRawData_Temp >= OilTempCompValues[8]) { oilTemperature = 80; }else
          if (cntRawData_Temp >= OilTempCompValues[7]) { oilTemperature = 75; }else
          if (cntRawData_Temp >= OilTempCompValues[6]) { oilTemperature = 70; }else
          if (cntRawData_Temp >= OilTempCompValues[5]) { oilTemperature = 65; }else
          if (cntRawData_Temp >= OilTempCompValues[4]) { oilTemperature = 60; }else
          if (cntRawData_Temp >= OilTempCompValues[3]) { oilTemperature = 55; }else
          if (cntRawData_Temp >= OilTempCompValues[2]) { oilTemperature = 50; }else
          if (cntRawData_Temp >= OilTempCompValues[1]) { oilTemperature = 40; }else
          if (cntRawData_Temp >= OilTempCompValues[0]) { oilTemperature = 30; }
        }else{ oilTemperature = OilLevelPercentageErrorValue;}
      }


    }else{
      /* if Oil Sensor is disconnected  */
      oilTemperature      = OilTemperaturePercentageErrorValue;
      oilLevelPercentage  = OilLevelPercentageErrorValue;
    }
  } else {
    /*Debug On*/
    oilTemperature      = testValue_oilTemperature;
    oilLevelPercentage  = testValue_oilLevelPercentage;
  }
}
