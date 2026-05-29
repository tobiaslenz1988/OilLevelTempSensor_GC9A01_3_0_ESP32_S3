#ifndef BUS_COMMON_H
#define BUS_COMMON_H
#include <cstdint>
#include <string.h>
void BUS_output(uint8_t data[],uint8_t len);

void initBTConnection(String name);
String bus_getReceiveString();
bool bus_AreNewDataThere();
void loopfunction();

#endif /* BUS_COMMON_H */