#ifndef HC_SR04_H
#define HC_SR04_H

#include <stdint.h>

// Connect pin D6 from arduino to ultrasonic sensor trig pin
// Connect pin D7 from arduino to ultrasonic sensor echo pin
void initUltrasoundSensor(void);
uint16_t getUltrasonicDistance(void);

#endif