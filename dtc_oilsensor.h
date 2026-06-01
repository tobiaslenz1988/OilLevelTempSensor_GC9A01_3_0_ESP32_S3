#ifndef DTC_OILSENSOR_H
#define DTC_OILSENSOR_H


#include <arduino.h>
#include <string.h>
#include "sensors/sensors.h"

void update_DTCStorage(void);
void deleteDTC (void);
void setDTC(uint32_t DTCBit);
bool readDTC(uint32_t DTCBit);
uint32_t readFullDTC(void);
uint8_t numberOfDTCEntries(void);
void setDTCStorageObject(uint32_t storage);
uint32_t getDTCStorageObject(void);
void checkCoding();

#endif /* DTC_OILSENSOR_H */