#ifndef UDS_STATEMACHINE_COMMON_H
#define UDS_STATEMACHINE_COMMON_H

#define EEPROMNameSpace               "my_variables"
#define OutputPin                     38
#define Buffersize                    35

extern bool  newBTData;      
extern bool  statusOfExtraOutputPin;
extern uint8_t brandSelector;
extern char SoftwareVersion[];
extern String Modulename;
void analyse_BT_Protocol(char receive_BT_Array[]);
void delete_BT_buffer(void);


#endif /* UDS_STATEMACHINE_H */