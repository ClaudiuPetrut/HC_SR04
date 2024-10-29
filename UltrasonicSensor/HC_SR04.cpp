#include <Arduino.h>
#include <HC_SR04.h>

volatile uint8_t last_value;
volatile uint32_t timer_1, current_time;
volatile uint16_t value;
uint16_t distance_cm;

// Connect pin D6 from arduino to ultrasonic sensor trig pin
// Connect pin D7 from arduino to ultrasonic sensor echo pin

void initUltrasoundSensor(void)
{
    PCICR |= (1 << PCIE2);    // Set PCIE2 to enable PCMSK2 scan.
    PCMSK2 |= (1 << PCINT23); // Set PCINT23 (digital input 7) to trigger an interrupt on state change.
    // Set as input pin 7
    DDRD &= ~(1 << DDD7);
    // Activate pull-up resistors
    PORTD |= (1 << PORTD7);
    // Set as output pin 6
    DDRD |= (1 << DDD6);
    PORTD &= ~(1 << PORTD6);
    sei();
}

ISR(PCINT2_vect)
{
    current_time = micros();

    if (PIND & B10000000)
    { // Is input 7 high?
        if (last_value == 0)
        {                           // Input 7 changed from 0 to 1.
            last_value = 1;         // Remember current input state.
            timer_1 = current_time; // Set timer_1 to current_time.
        }
    }
    else if (last_value == 1)
    {                                   // Input 7 is not high and changed from 1 to 0.
        last_value = 0;                 // Remember current input state.
        value = current_time - timer_1; // Channel 7 is current_time - timer_1.
    }
}

uint16_t getUltrasonicDistance(void)
{
    // Send trigger pulse of 15 us
    PORTD |= (1 << PORTD6);
    delayMicroseconds(15);
    PORTD &= ~(1 << PORTD6);
    // Wait for sensor to read data
    delay(50);
    // Calculate distance
    distance_cm = value * 0.017;
    if (distance_cm > 200)
    {
        distance_cm = 200;
    }
    return (uint16_t)(distance_cm);
}