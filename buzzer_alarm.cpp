
#include <arduino.h>
#include "buzzer_alarm.h"
#include <stdio.h>


uint8_t counterAlarmOilTemp;
uint8_t counterAlarmOilLevel;
uint8_t counterAlarmOilSensorTO;

void alarmOilOvertemp(void)
{
    if(counterAlarmOilTemp<=1){
        tone(BUZZER_PIN, 2500, 1500); 
        counterAlarmOilTemp++;
    }  
}


void alarmOilLevel(void)
{
    if(counterAlarmOilLevel<=3){
        tone(BUZZER_PIN, 1000, 500); 
        tone(BUZZER_PIN, 700, 300); 
        counterAlarmOilLevel++;
    }
}

void alarmOilSensorTO(void){
    if(counterAlarmOilSensorTO<=3){
        tone(BUZZER_PIN, 1000, 500); 
        tone(BUZZER_PIN, 700, 300); 
        counterAlarmOilSensorTO++;
    }
}
void resetalarmOvertemp(void){
    counterAlarmOilTemp=0;
}

void resetalarmOilLevel(void){
    counterAlarmOilLevel=0;
}

void resetalarmOilSensorTO(void){
    counterAlarmOilSensorTO=0;
}