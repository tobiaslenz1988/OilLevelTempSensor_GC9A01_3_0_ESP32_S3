#include "esp32-hal.h"
#include <Arduino.h>
#include <stdio.h>
#include <string.h>
#include <Preferences.h>
#include "uds_statemachine_common.h"
#include "bus_common.h"
#include "oilsensor.h"
#include "nrc_uds_protocol.h"
#include "brand_defines_common.h"
#include "softwareversion.h"
#include "sensors/sensors.h"
#include "dtc_oilsensor.h"


extern Preferences preferences;

extern uint8_t session;
extern String oemPartNumberOilTempSensor;
extern String supplierPartNumberOilTempSensor;
extern String oemPartNumberWaterTempSensor;
extern String supplierPartNumberWaterTempSensor;
extern String HWModelleName;


void delete_BT_buffer(void) { /*
  for(int z=0;z<Buffersize;z++)
  {
    BT_rx_buffer[z]=0xFF;  
  }*/
}

void analyse_BT_Protocol(char receive_BT_Array[]) {
  //Serial.println(receive_BT_Array[]);
  if (newBTData == true) {
    /*Command to read something*/
      if (receive_BT_Array[0] == UDS_READ_DATA_BY_IDENTIFIER) {
        uint8_t posResponse = (UDS_READ_DATA_BY_IDENTIFIER + 0x40);
          /* 0x22 0xF1 0xAB */
          /* Get SW Version*/
          if ((receive_BT_Array[1] == 0xF1) && (receive_BT_Array[2] == 0xAB)) {
            uint8_t data[3];
            data[0] = posResponse;
            data[1] = 0xF1;
            data[2] = 0xAB;
            data[3]=(uint8_t)SOFTWAREVERSION[0];
            data[4]=(uint8_t)SOFTWAREVERSION[1];
            data[5]=(uint8_t)SOFTWAREVERSION[2];
            data[6]=(uint8_t)SOFTWAREVERSION[3];
            BUS_output(data, 7);
          } else

          /* 0x22 0xF1 0x86 */
          /* Get actual Sesion */
          if ((receive_BT_Array[1] == 0xF1) && (receive_BT_Array[2] == 0x86)) {
            uint8_t data[4];
            data[0] = posResponse;
            data[1] = 0xF1;
            data[2] = 0x86;
            data[3] = session;
            BUS_output(data, 4);
          } else

          /* 0x22 0xF1 0x90 */
          /* Get Name of Central Chip */
          if ((receive_BT_Array[1] == 0xF1) && (receive_BT_Array[2] == 0x90)) {
            uint8_t len = sizeof(HWModelleName) / sizeof(HWModelleName[0]);
            uint8_t data[len+3];
            data[0] = posResponse;
            data[1] = 0xF1;
            data[2] = 0x90;
            for(int i=0;i<len;i++)
            {
              data[3+i] = (uint8_t)HWModelleName[i];
            }
            BUS_output(data, len);
          } else

          /* 0x22 0xF1 0x91 */
          /* Get OEMPartNumber of OilTempSensor */
          if ((receive_BT_Array[1] == 0xF1) && (receive_BT_Array[2] == 0x91)) {
            uint8_t len = sizeof(oemPartNumberOilTempSensor) / sizeof(oemPartNumberOilTempSensor[0]);
            uint8_t data[len+3];
            data[0] = posResponse;
            data[1] = 0xF1;
            data[2] = 0x91;
            for(int i=0;i<len;i++)
            {
              data[3+i] = (uint8_t)oemPartNumberOilTempSensor[i];
            }
            BUS_output(data, len);
          } else
              
          /* 0x22 0xF1 0x92 */
          /* Get OEMPartNumber of WaterTempSensor */
          if ((receive_BT_Array[1] == 0xF1) && (receive_BT_Array[2] == 0x92)) {
            uint8_t len = sizeof(oemPartNumberWaterTempSensor) / sizeof(oemPartNumberWaterTempSensor[0]);
            uint8_t data[len+3];
            data[0] = posResponse;
            data[1] = 0xF1;
            data[2] = 0x92;
            for(int i=0;i<len;i++)
            {
              data[3+i] = (uint8_t)oemPartNumberWaterTempSensor[i];
            }
            BUS_output(data, len);

          } else

          /* 0x22 0xF1 0x93 */
          /* get SupplierPartNumber of OilTempSensor */
          if ((receive_BT_Array[1] == 0xF1) && (receive_BT_Array[2] == 0x93)) {
            uint8_t len = sizeof(supplierPartNumberOilTempSensor) / sizeof(supplierPartNumberOilTempSensor[0]);
            uint8_t data[len+3];
            data[0] = posResponse;
            data[1] = 0xF1;
            data[2] = 0x93;
            for(int i=0;i<len;i++)
            {
              data[3+i] = (uint8_t)supplierPartNumberOilTempSensor[i];
            }
            BUS_output(data, len);
          } else


          /* 0x22 0xF1 0x94 */
          /* get SupplierPartNumber of WaterTempSensor */
          if ((receive_BT_Array[1] == 0xF1) && (receive_BT_Array[2] == 0x94)) {
            uint8_t len = sizeof(supplierPartNumberWaterTempSensor) / sizeof(supplierPartNumberWaterTempSensor[0]);
            uint8_t data[len+3];
            data[0] = posResponse;
            data[1] = 0xF1;
            data[2] = 0x94;
            for(int i=0;i<len;i++)
            {
              data[3+i] = (uint8_t)supplierPartNumberWaterTempSensor[i];
            }
            BUS_output(data, len);
          } else


          /* 0x22 0xF1 0x97 */
          /* get Systemname */
          if ((receive_BT_Array[1] == 0xF1) && (receive_BT_Array[2] == 0x97)) {
            uint8_t len = sizeof(Modulename) / sizeof(Modulename[0]);
            uint8_t data[len+3];
            data[0] = posResponse;
            data[1] = 0xF1;
            data[2] = 0x97;
            for(int i=0;i<len;i++)
            {
              data[3+i] = (uint8_t)Modulename[i];
            }
            BUS_output(data, len);
          } else

          /* This part should read the coding
          /* 0x22 0x06 0x00 ......*/
          if ((receive_BT_Array[1] == 0x06) && (receive_BT_Array[2] == 0x00)) {
            uint8_t data[5];
            data[0] = posResponse;
            data[1] = 0x06;
            data[2] = 0x00;
            data[3] = brandSelector;
            data[4] = 0x00;//reserved
            BUS_output(data, 5);
          } else
            
          /* 0x22 0x06 0x01 */
          /* This part should get the Debugvalue for the OilTemperature */
          if ((receive_BT_Array[1] == 0x06) && (receive_BT_Array[2] == 0x01)) {          
            uint8_t data[4];
            data[0] = posResponse;
            data[1] = 0x06;
            data[2] = 0x01;
            data[3] = testValue_oilTemperature;
            BUS_output(data, 4);
          } else

          /* 0x22 0x06 0x02 */
          /* This part should get the Debugvalue for the OilLevel */
          if ((receive_BT_Array[1] == 0x06) && (receive_BT_Array[2] == 0x02)) {
            uint8_t data[4];
            data[0] = posResponse;
            data[1] = 0x06;
            data[2] = 0x02;
            data[3] = testValue_oilLevelPercentage;
            BUS_output(data, 4);
          } else

          /* 0x22 0x06 0x03 */
          /* Returns the OilTemperature  in Degree Celsius which is used by the SW*/
          if ((receive_BT_Array[1] == 0x06) && (receive_BT_Array[2] == 0x03)) {
            uint8_t data[4];
            data[0] = posResponse;
            data[1] = 0x06;
            data[2] = 0x03;
            data[3] = oilTemperature;
            BUS_output(data, 4);
          } else

          /* 0x22 0x06 0x04 */
          /* Returns the Oillevel in percent which is used by the SW*/
          if ((receive_BT_Array[1] == 0x06) && (receive_BT_Array[2] == 0x04)) {
            uint8_t data[4];
            data[0] = posResponse;
            data[1] = 0x06;
            data[2] = 0x04;
            data[3] = oilLevelPercentage;
            BUS_output(data, 4);
          } else

          /* 0x22 0x06 0x0A */
          /* get the Brandvalue */
          if ((receive_BT_Array[1] == 0x06) && (receive_BT_Array[2] == 0x0A)) {
            uint8_t data[4];
            data[0] = posResponse;
            data[1] = 0x06;
            data[2] = 0x0A;
            data[3] = brandSelector;
            BUS_output(data, 4);
          } else

          /* 0x22 0x06 0x0B */
          /* get ExtraOutputPin flag*/
          if ((receive_BT_Array[1] == 0x06) && (receive_BT_Array[2] == 0x0B)) {
            uint8_t data[4];
            data[0] = posResponse;
            data[1] = 0x06;
            data[2] = 0x0B;
            data[3] = statusOfExtraOutputPin;
            BUS_output(data, 4);
          } else

          /* 0x22 0x07 0x00 */
          /* get Oiltemperature compare values for Sensor */
          if ((receive_BT_Array[1] == 0x07) && (receive_BT_Array[2] == 0x00)) {    
            uint8_t i = 0;
            uint8_t tempvar;
            uint8_t sizeOfArr = sizeof(OilTempCompValues) / sizeof(OilTempCompValues[0]);
            uint8_t data[(3+(sizeOfArr*2))];
            data[0] = posResponse;
            data[1] = 0x07;
            data[2] = 0x00;
              
            for (i = 0; i < (sizeOfArr); i+2){
                data[3+i] = (OilTempCompValues[i] >> 8);
                data[4+i] = (OilTempCompValues[i] & 0xFF);
            }
            BUS_output(data, 3+(sizeOfArr*2));
          } else

          /* 0x22 0x07 0x01 */
          /* get Oillevel compare values for Sensor*/
          if ((receive_BT_Array[1] == 0x07) && (receive_BT_Array[2] == 0x01)) {
            uint8_t i = 0;
            uint8_t tempvar;
            uint8_t sizeOfArr = sizeof(OilLevelCompValues) / sizeof(OilLevelCompValues[0]);
            uint8_t data[3+(sizeOfArr*2)];
            data[0] = posResponse;
            data[1] = 0x07;
            data[2] = 0x01;
            for (i = 0; i < (sizeOfArr*2); i+2) 
            {
              data[3+i] = (OilLevelCompValues[i] >> 8);
              data[4+i] = (OilLevelCompValues[i] & 0xFF);
            }
            BUS_output(data, 3+(sizeOfArr*2));
          } else
              
          
          /* 0x22 0x07 0x02 */
          /* Number of DTC Entries */
          if ((receive_BT_Array[1] == 0x07) && (receive_BT_Array[2] == 0x02)) {
            uint8_t data[4];
            data[0] = posResponse;
            data[1] = 0x07;
            data[2] = 0x02;
            data[3] = numberOfDTCEntries();
            BUS_output(data, 4);
          } else

          /* 0x22 0x07 0x03 */
          /* get Status of DTC Storage */
          if ((receive_BT_Array[1] == 0x07) && (receive_BT_Array[2] == 0x03)) {
            uint8_t data[3];
            uint32_t dtcstatus = getDTCStorageObject();
              //uint32_t dtcstatus = 0x12345678;
            data[0] = posResponse;
            data[1] = 0x07;
            data[2] = 0x03;
            data[3] = dtcstatus & 0xFF;                  // Niedrigstes Byte (0x78)
            data[4] = (dtcstatus >> 8) & 0xFF;           // Zweites Byte (0x56)
            data[5] = (dtcstatus >> 16) & 0xFF;          // Drittes Byte (0x34)
            data[6] = (dtcstatus >> 24) & 0xFF;          // Höchstes Byte (0x12)
            BUS_output(data, 7);
          } else 

          /* 0x22 0x07 0x04 */
          /* Reserved */
          if ((receive_BT_Array[1] == 0x07) && (receive_BT_Array[2] == 0x04)) {
            uint8_t data[3];
            data[0] = posResponse;
            data[1] = 0x07;
            data[2] = 0x04;
            BUS_output(data, 3);
          } else {
            /* For the case that the requested RDID is not implemented */
            uint8_t data[3];
            data[0] = UDS_NRC_CODE;
            data[1] = UDS_READ_DATA_BY_IDENTIFIER;
            data[2] = UDS_NRC_requestOutOfRange;
            BUS_output(data, 3);
          }
      } else

        /*Command to write something*/
        if (receive_BT_Array[0] == UDS_WRITE_DATA_BY_IDENTIFIER) {
        uint8_t posResponse = (UDS_WRITE_DATA_BY_IDENTIFIER + 0x40);


          /* 0x2E 0xf1 0x90 */
          /* set Name of central chip */
          if ((receive_BT_Array[1] == 0xF1) && (receive_BT_Array[2] == 0x90)) 
          {
            if((session == UDS_Session_Control_Extended_Session )|| (session == UDS_Session_Control_Development_Session ) )
            {
              uint8_t i;
              String tempStr;
              HWModelleName = DEFAULT_HWMODELLNAME;
              uint8_t length_of_name = receive_BT_Array[3];
              if(length_of_name<=15){
                for (i = 0; i < length_of_name; i++) 
                {
                  tempStr.concat((char)receive_BT_Array[4 + i]);
                  HWModelleName[i] = receive_BT_Array[4 + i];
                }

                preferences.begin(EEPROMNameSpace, false);
                preferences.putString("HWModuleName", tempStr);
                preferences.end();

                uint8_t data[3];
                data[0] = posResponse;
                data[1] = 0xF1;
                data[2] = 0x90;
                BUS_output(data, 3);
              }else{
                /* if Length of HWModellname of Chip is more than 15 Character */
                uint8_t data[3];
                data[0] = UDS_NRC_CODE;
                data[1] = UDS_WRITE_DATA_BY_IDENTIFIER;
                data[2] = UDS_NRC_incorrectMessageLengthOrInvalidFormat;
                BUS_output(data, 3);
              }
            }else{
              /* Session not correct for writing the Modelname*/
              uint8_t data[3];
              data[0] = UDS_NRC_CODE;
              data[1] = UDS_WRITE_DATA_BY_IDENTIFIER;
              data[2] = UDS_NRC_subFunctionNotSupportedInActiveSession;
              BUS_output(data, 3);
            }
          } else

          
          /* 0x2E 0xf1 0x91 */
          /* set VWPartNumber of OilTempSensor */
          if ((receive_BT_Array[1] == 0xF1) && (receive_BT_Array[2] == 0x91)) {
            uint8_t i;
            String tempStr;
            oemPartNumberOilTempSensor = DEFAULT_OEM_PARTNUMBER_OIL_TEMPSENSOR;
            uint8_t length_of_name = receive_BT_Array[3];
            for (i = 0; i < length_of_name; i++) {
              //Modulename[i] =  (char) receive_BT_Array[4+i];
              tempStr.concat((char)receive_BT_Array[4 + i]);
              oemPartNumberOilTempSensor[i] = receive_BT_Array[4 + i];
            }

            preferences.begin(EEPROMNameSpace, false);
            preferences.putString("PartNumberOilTempSensor", tempStr);
            preferences.end();


            uint8_t data[3];
            data[0] = posResponse;
            data[1] = 0xF1;
            data[2] = 0x91;
            BUS_output(data, 3);
          } else

          /* 0x2E 0xf1 0x92 */
          /* set VWPartNumber of WaterTempSensor */
          if ((receive_BT_Array[1] == 0xF1) && (receive_BT_Array[2] == 0x92)) {
            uint8_t i;
            String tempStr;
            oemPartNumberWaterTempSensor = DEFAULT_OEM_PARTNUMBER_WATER_TEMPSENSOR;
            uint8_t length_of_name = receive_BT_Array[3];
            for (i = 0; i < length_of_name; i++) 
            {
              tempStr.concat((char)receive_BT_Array[4 + i]);
              oemPartNumberWaterTempSensor[i] = receive_BT_Array[4 + i];
            }

            preferences.begin(EEPROMNameSpace, false);
            preferences.putString("PartNumberWaterTempSensor", tempStr);
            preferences.end();

            uint8_t data[3];
            data[0] = posResponse;
            data[1] = 0xF1;
            data[2] = 0x92;
            BUS_output(data, 3);
          } else

          /* 0x2E 0xf1 0x93 */
          /* set SupplierPartNumber of OilTempSensor */
          if ((receive_BT_Array[1] == 0xF1) && (receive_BT_Array[2] == 0x93)) {
            uint8_t i;
            String tempStr;
            supplierPartNumberOilTempSensor = DEFAULT_SUPPLIER_PARTNUMBER_OIL_TEMPSENSOR;
            uint8_t length_of_name = receive_BT_Array[3];
            for (i = 0; i < length_of_name; i++) 
            {
              tempStr.concat((char)receive_BT_Array[4 + i]);
              supplierPartNumberOilTempSensor[i] = receive_BT_Array[4 + i];
            }

              preferences.begin(EEPROMNameSpace, false);
              preferences.putString("supplierPartNumberOilTempSensor", tempStr);
              preferences.end();

              uint8_t data[3];
              data[0] = posResponse;
              data[1] = 0xF1;
              data[2] = 0x93;
               BUS_output(data, 3);
          } else
          /* 0x2E 0xf1 0x94 */
          /* set SupplierPartNumber of Water Tempsensor */
          if ((receive_BT_Array[1] == 0xF1) && (receive_BT_Array[2] == 0x94)) {
            uint8_t i;
            String tempStr;
            supplierPartNumberWaterTempSensor = DEFAULT_SUPPLIER_PARTNUMBER_WATER_TEMPSENSOR;
            uint8_t length_of_name = receive_BT_Array[3];
            for (i = 0; i < length_of_name; i++) 
            {
              tempStr.concat((char)receive_BT_Array[4 + i]);
              supplierPartNumberWaterTempSensor[i] = receive_BT_Array[4 + i];
            }

            preferences.begin(EEPROMNameSpace, false);
            preferences.putString("supplierPartNumberWaterTempSensor", tempStr);
            preferences.end();
            uint8_t data[3];
            data[0] = posResponse;
            data[1] = 0xF1;
            data[2] = 0x94;
            BUS_output(data, 3);
          } else
          /* This part should change the name of the BT Module*/
          /* 0x2E 0xF1 0x97 0x?? 0x!!  0x!! 0x!! 0x!!......*/
          if ((receive_BT_Array[1] == 0xF1) && (receive_BT_Array[2] == 0x97)) 
          {
            uint8_t length_of_name = receive_BT_Array[3];
            if ((0 < length_of_name) && (length_of_name <= 20)) {
              uint8_t i;
              String tempStr;
              Modulename = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
              for (i = 0; i < length_of_name; i++) 
              {
                tempStr.concat((char)receive_BT_Array[4 + i]);
                Modulename[i] = receive_BT_Array[4 + i];
              }

              preferences.begin(EEPROMNameSpace, false);
              preferences.putString("Modulename", tempStr);
              preferences.end();
              //SerialBT.begin(tempStr);
              uint8_t data[3];
              data[0] = posResponse;
              data[1] = 0xF1;
              data[2] = 0x97;
              BUS_output(data, 3);
            } else {
              uint8_t data[3];
              data[0] = UDS_NRC_CODE;
              data[1] = UDS_WRITE_DATA_BY_IDENTIFIER;
              data[2] = UDS_NRC_incorrectMessageLengthOrInvalidFormat;
              BUS_output(data, 3);
            }
          } else

          /* This part should set the coding
          /* 0x2E 0x06 0x00 0x??......*/
          if ((receive_BT_Array[1] == 0x06) && (receive_BT_Array[2] == 0x00)) {

            if ((receive_BT_Array[3] != NULL) && (receive_BT_Array[4] != NULL) && (receive_BT_Array[5] != NULL)) {
              brandSelector = receive_BT_Array[3];
              brandSelector = receive_BT_Array[3];
              brandSelector = receive_BT_Array[3];

              uint8_t data[3];
              data[0] = posResponse;
              data[1] = 0x06;
              data[2] = 0x00;
              BUS_output(data, 3);
            } else {
              uint8_t data[3];
              data[0] = posResponse;
              data[1] = UDS_WRITE_DATA_BY_IDENTIFIER;
              data[2] = UDS_NRC_incorrectMessageLengthOrInvalidFormat;
              BUS_output(data, 3);
            }
          } else


          /* This part should set the Debugvalue for the OilTemperature
          /* 0x2E 0x06 0x01 0x??......*/
          if ((receive_BT_Array[1] == 0x06) && (receive_BT_Array[2] == 0x01)) {
            uint8_t val = NULL;
            val = receive_BT_Array[3];
            if (val == NULL) {
              uint8_t data[3];
              data[0] = UDS_NRC_CODE;
              data[1] = UDS_WRITE_DATA_BY_IDENTIFIER;
              data[2] = UDS_NRC_incorrectMessageLengthOrInvalidFormat;
              BUS_output(data, 3);
            } else {
              testValue_oilTemperature = val;
              uint8_t data[3];
              data[0] = posResponse;
              data[1] = 0x06;
              data[2] = 0x01;
              BUS_output(data, 3);
            }
          } else
          /* This part should set the Debugvalue for the OilLevel
          /* 0x2E 0x06 0x02 0x!! 0x!!  0x!! 0x!! 0x!!......*/
          if ((receive_BT_Array[1] == 0x06) && (receive_BT_Array[2] == 0x02)) {
            uint8_t val = NULL;
            val = receive_BT_Array[3];
            if (val == NULL) 
            {
              uint8_t data[3];
              data[0] = UDS_NRC_CODE;
              data[1] = UDS_WRITE_DATA_BY_IDENTIFIER;
              data[2] = UDS_NRC_incorrectMessageLengthOrInvalidFormat;
              BUS_output(data, 3);
            } else {
              testValue_oilLevelPercentage = val;
              uint8_t data[3];
              data[0] = posResponse;
              data[1] = 0x06;
              data[2] = 0x02;
              BUS_output(data, 3);
            }
          } else

          /* This part should set brand for the startuplogo
          /* 0x2E 0x06 0x0A 0x!! */
          if ((receive_BT_Array[1] == 0x06) && (receive_BT_Array[2] == 0x0A)) {
            uint8_t val = NULL;
            val = receive_BT_Array[3];
            if (val == NULL) {
              uint8_t data[3];
              data[0] = UDS_NRC_CODE;
              data[1] = UDS_WRITE_DATA_BY_IDENTIFIER;
              data[2] = UDS_NRC_incorrectMessageLengthOrInvalidFormat;
              BUS_output(data, 3);
            } else {
              if ((val == BRAND_AUDI) || (val == BRAND_VW) || (val == BRAND_CHEVY) || (val == BRAND_DODGE) || (val == BRAND_NISSAN_GTT)|| (val == BRAND_BMW) || (val == BRAND_MERCEDES_OLD)) {
                brandSelector = val;
                preferences.begin(EEPROMNameSpace, false);
                preferences.putUChar("Brand", val);
                preferences.end();

                uint8_t data[3];
                data[0] = posResponse;
                data[1] = 0x06;
                data[2] = 0x0A;
                BUS_output(data, 3);
              } else {
                uint8_t data[3];
                data[0] = UDS_NRC_CODE;
                data[1] = UDS_WRITE_DATA_BY_IDENTIFIER;
                data[2] = UDS_NRC_requestOutOfRange;
                BUS_output(data, 3);
              }
            }
          } else

          /* This part should set the value of an Output Pin
          /* 0x2E 0x06 0x0B 0x!! 0x!!  0x!! 0x!! 0x!!......*/
          if ((receive_BT_Array[1] == 0x06) && (receive_BT_Array[2] == 0x0B)) {
            uint8_t val = NULL;
            val = receive_BT_Array[3];
            if (val == NULL) {
              uint8_t data[3];
              data[0] = UDS_NRC_CODE;
              data[1] = UDS_WRITE_DATA_BY_IDENTIFIER;
              data[2] = UDS_NRC_incorrectMessageLengthOrInvalidFormat;
              BUS_output(data, 3);
            } else {
              statusOfExtraOutputPin = val;
              digitalWrite(OutputPin, statusOfExtraOutputPin);
              uint8_t data[3];
              data[0] = posResponse;
              data[1] = 0x06;
              data[2] = 0x0B;
              BUS_output(data, 3);
            }
          } else
          /* This part should set the compare values for OilTemperature of old Sensor
          /* 0x2E 0x07 0x00 0x!! 0x!!  0x!! 0x!! 0x!!......*/
          if ((receive_BT_Array[1] == 0x07) && (receive_BT_Array[2] == 0x00)) {
            uint8_t val = NULL;
            val = receive_BT_Array[3];
            if (val == NULL) {
              uint8_t data[3];
              data[0] = UDS_NRC_CODE;
              data[1] = UDS_WRITE_DATA_BY_IDENTIFIER;
              data[2] = UDS_NRC_incorrectMessageLengthOrInvalidFormat;
              BUS_output(data, 3);
            } else {
              preferences.begin(EEPROMNameSpace, false);
              uint16_t temp = ((uint16_t)receive_BT_Array[3] << 8) | receive_BT_Array[4];
              preferences.putShort("SENSOR_Temperature_30", temp);
              temp = ((uint16_t)receive_BT_Array[5] << 8) | receive_BT_Array[6];
              preferences.putShort("SENSOR_Temperature_40", temp);
              temp = ((uint16_t)receive_BT_Array[7] << 8) | receive_BT_Array[8];
              preferences.putShort("SENSOR_Temperature_50", temp);
              temp = ((uint16_t)receive_BT_Array[9] << 8) | receive_BT_Array[10];
              preferences.putShort("SENSOR_Temperature_55", temp);
              temp = ((uint16_t)receive_BT_Array[11] << 8) | receive_BT_Array[12];
              preferences.putShort("SENSOR_Temperature_60", temp);
              temp = ((uint16_t)receive_BT_Array[13] << 8) | receive_BT_Array[14];
              preferences.putShort("SENSOR_Temperature_65", temp);
              temp = ((uint16_t)receive_BT_Array[15] << 8) | receive_BT_Array[16];
              preferences.putShort("SENSOR_Temperature_70", temp);
              temp = ((uint16_t)receive_BT_Array[17] << 8) | receive_BT_Array[18];
              preferences.putShort("SENSOR_Temperature_75", temp);
              temp = ((uint16_t)receive_BT_Array[19] << 8) | receive_BT_Array[20];
              preferences.putShort("SENSOR_Temperature_80", temp);
              temp = ((uint16_t)receive_BT_Array[21] << 8) | receive_BT_Array[22];
              preferences.putShort("SENSOR_Temperature_85", temp);
              temp = ((uint16_t)receive_BT_Array[23] << 8) | receive_BT_Array[24];
              preferences.putShort("SENSOR_Temperature_90", temp);
              temp = ((uint16_t)receive_BT_Array[25] << 8) | receive_BT_Array[26];
              preferences.putShort("SENSOR_Temperature_95", temp);
              temp = ((uint16_t)receive_BT_Array[27] << 8) | receive_BT_Array[28];
              preferences.putShort("SENSOR_Temperature_100", temp);
              temp = ((uint16_t)receive_BT_Array[29] << 8) | receive_BT_Array[30];
              preferences.putShort("SENSOR_Temperature_105", temp);
              temp = ((uint16_t)receive_BT_Array[31] << 8) | receive_BT_Array[32];
              preferences.putShort("SENSOR_Temperature_110", temp);
              temp = ((uint16_t)receive_BT_Array[33] << 8) | receive_BT_Array[34];
              preferences.putShort("SENSOR_Temperature_115", temp);
              preferences.end();
              uint8_t data[3];
              data[0] = posResponse;
              data[1] = 0x07;
              data[2] = 0x00;
              BUS_output(data, 3);
            }
          } else
          /* This part should set the compare values for Oillevel old sensor
          /* 0x2E 0x07 0x01 0x!! 0x!!  0x!! 0x!! 0x!!......*/
          if ((receive_BT_Array[1] == 0x07) && (receive_BT_Array[2] == 0x01)) {
            uint8_t val = NULL;
            val = receive_BT_Array[3];
            if (val == NULL) {
              uint8_t data[3];
              data[0] = UDS_NRC_CODE;
              data[1] = UDS_WRITE_DATA_BY_IDENTIFIER;
              data[2] = UDS_NRC_incorrectMessageLengthOrInvalidFormat;
              BUS_output(data, 3);
            } else {
              preferences.begin(EEPROMNameSpace, false);
              uint16_t temp = ((uint16_t)receive_BT_Array[3] << 8) | receive_BT_Array[4];
              preferences.putShort("SENSOR_OilLevelEmpty", temp);
              temp = ((uint16_t)receive_BT_Array[5] << 8) | receive_BT_Array[6];
              preferences.putShort("SENSOR_OilLevel_10", temp);
              temp = ((uint16_t)receive_BT_Array[7] << 8) | receive_BT_Array[8];
              preferences.putShort("SENSOR_OilLevel_20", temp);
              temp = ((uint16_t)receive_BT_Array[9] << 8) | receive_BT_Array[10];
              preferences.putShort("SENSOR_OilLevel_30", temp);
              temp = ((uint16_t)receive_BT_Array[11] << 8) | receive_BT_Array[12];
              preferences.putShort("SENSOR_OilLevel_40", temp);
              temp = ((uint16_t)receive_BT_Array[13] << 8) | receive_BT_Array[14];
              preferences.putShort("SENSOR_OilLevel_50", temp);
              temp = ((uint16_t)receive_BT_Array[15] << 8) | receive_BT_Array[16];
              preferences.putShort("SENSOR_OilLevel_60", temp);
              temp = ((uint16_t)receive_BT_Array[17] << 8) | receive_BT_Array[18];
              preferences.putShort("SENSOR_OilLevel_70", temp);
              temp = ((uint16_t)receive_BT_Array[19] << 8) | receive_BT_Array[20];
              preferences.putShort("SENSOR_OilLevel_80", temp);
              temp = ((uint16_t)receive_BT_Array[21] << 8) | receive_BT_Array[22];
              preferences.putShort("SENSOR_OilLevel_90", temp);
              temp = ((uint16_t)receive_BT_Array[23] << 8) | receive_BT_Array[24];
              preferences.putShort("SENSOR_OilLevelFull", temp);

              preferences.end();
              uint8_t data[3];
              data[0] = posResponse;
              data[1] = 0x07;
              data[2] = 0x01;
              BUS_output(data, 3);
            }
          } else
          
          /* tbd */
          /* 0x2E 0x07 0x03 0x!!......*/
          if ((receive_BT_Array[1] == 0x07) && (receive_BT_Array[2] == 0x03)) {
            uint8_t val = NULL;
            val = (uint8_t)receive_BT_Array[3];
            if (val == NULL) {
              uint8_t data[3];
              data[0] = UDS_NRC_CODE;
              data[1] = UDS_WRITE_DATA_BY_IDENTIFIER;
              data[2] = UDS_NRC_incorrectMessageLengthOrInvalidFormat;
              BUS_output(data, 3);
            } else {
              uint8_t data[3];
              data[0] = posResponse;
              data[1] = 0x07;
              data[2] = 0x03;
              BUS_output(data, 3);
            }
          } else{
            uint8_t data[3];
            data[0] = UDS_NRC_CODE;
            data[1] = UDS_WRITE_DATA_BY_IDENTIFIER;
            data[2] = UDS_NRC_requestOutOfRange;
            BUS_output(data, 3);
          }
        } else

          /* Session Control */
          if (receive_BT_Array[0] == UDS_Session_Control) {
            if ((receive_BT_Array[1] == UDS_Session_Control_Default_Session) || (receive_BT_Array[1] == UDS_Session_Control_Extended_Session) || (receive_BT_Array[1] == UDS_Session_Control_Development_Session)) {
              if (session != receive_BT_Array[1]) {
                session = receive_BT_Array[1];
                preferences.begin(EEPROMNameSpace, false);
                preferences.putUChar("session", receive_BT_Array[1]);
                preferences.end();
              }
              uint8_t data[1];
              data[0] = 0x50;
              BUS_output(data, 1);
            } else {
            uint8_t data[3];
            data[0] = UDS_NRC_CODE;
            data[1] = UDS_Session_Control;
            data[2] = UDS_NRC_subFunctionNotSupported;
            BUS_output(data, 3);
          }
        } else

          if (receive_BT_Array[0] == UDS_ECU_Reset) {
            if (receive_BT_Array[1] == UDS_ECU_Reset_KeyOnOffReset) {
              uint8_t data[1];
              data[0] = 0x51;
              BUS_output(data, 1);
              delay(1000);
              ESP.restart();
            }
          }else{
            uint8_t data[3];
            data[0] = UDS_NRC_CODE;
            data[1] = receive_BT_Array[0];
            data[2] = UDS_NRC_serviceNotSupported;
            BUS_output(data, 3);
          }
          delete_BT_buffer();
        }
        newBTData = false;
      }
