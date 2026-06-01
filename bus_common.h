#ifndef BUS_COMMON_H
#define BUS_COMMON_H
#include <cstdint>
#include <string.h>

void BUS_output(uint8_t data[],uint8_t len);
void BUS_outputUint16_t(uint16_t data);
void BUS_outputStr(String data);

void initBTConnection(String name);
String bus_getReceiveString();
bool bus_AreNewDataThere();
void loopfunction();

#endif /* BUS_COMMON_H */