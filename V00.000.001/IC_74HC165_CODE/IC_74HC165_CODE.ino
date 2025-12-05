#include "ic_74hc165_switch.h"

void setup() {
  Serial.begin(115200);
  ic_74hc165_setup();
}

void loop()
{
  ic_74hc165_loop();
  ic_74hc165_switch_loop();

  Serial.print("\nINPUT_data : ");
  for(int i = 0 ; i < numBits ; i++ )
  {
   //  Serial.print(input_data[i]);
   bool status = get_switch_status(i+1) ;
   Serial.print( status );
  }

  delay(300); // test parpose only
}

