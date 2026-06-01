#ifndef _BUZZER_ALARM_H
#define _BUZZER_ALARM_H



#define BUZZER_PIN 8
void alarmOilOvertemp(void);
void alarmOilLevel(void);
void alarmOilSensorTO(void);

void resetalarmOvertemp(void);
void resetalarmOilLevel(void);
void resetalarmOilSensorTO(void);

#endif