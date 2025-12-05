#ifndef _IC_74HC165_H
#define _IC_74HC165_H

#include "PIN_CONFIG.h"


#define IC_74HC165_COUNT 1 // connected ic count number ( number of shift registers )

const int dataPin = IC_74HC_165_DATA_PIN;   /* D */
const int clockPin = IC_74HC_165_CLOCK_PIN;  /* CP */
const int latchPin = IC_74HC_165_LATCH_PIN;  /* PL */
/* IC_74HC_165_CE pin will connect to GND */

const int numBits = 8 * IC_74HC165_COUNT ;   /* Set to 8 * number of shift registers */

bool input_data[numBits] = {0};

void ic_74hc165_setup() {
  
  pinMode(dataPin, INPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
}


void get_ic_74hc165_inputs()
{
    // Step 1: Sample
  digitalWrite(latchPin, LOW);
  digitalWrite(latchPin, HIGH);
 
  // Step 2: Shift
  for (int i = ( numBits - 1) ; i >= 0 ; i--) {
    input_data[i] = digitalRead(dataPin);
  
    digitalWrite(clockPin, HIGH); // Shift out the next bit
    digitalWrite(clockPin, LOW);
  }
}
 
void ic_74hc165_loop() {

get_ic_74hc165_inputs();

}

bool get_74hc165_pin_state(int pin)
{
  int pin_number = pin - 1;
  bool pin_state = 0;
  if(pin_number < numBits)
  {
    pin_state = input_data[pin_number];
  }
  return pin_state ;
}

int get_74hc165_max_pins()
{
  return numBits ;
}




/*********************************************************************/
#if 0

void setup() {
  Serial.begin(115200);
  ic_74hc165_setup();
}

void loop()
{
  ic_74hc165_loop();
  Serial.print("\nINPUT_data : ");
  for(int i = 0 ; i < numBits ; i++ )
  {
    Serial.print(input_data[i]);
  }

  delay(300);
}

#endif



#endif // _IC_74HC165_H