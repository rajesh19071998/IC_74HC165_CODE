#ifndef _IC_74HC165_SWITCH_H
#define _IC_74HC165_SWITCH_H

#include "ic_74hc165.h"

/* select only one macro  */
#define BUTTON_TOGGLE_HIGH  /* when button give high signal it will togle the switch storage */
//#define BUTTON_TOGGLE_LOW
//#define SWITCH_HIGH
//#define SWITCH_LOW   


/* define switches Names with pin numbers */
#if 0
#define MOTOR_ON_SWITCH   1
#define MOTOR_OFF_SWITCH  2
#define AUTOMATIC_SWITCH  3
#define STATUS_SWITCH     4
#endif

extern const int numBits ; // from ic_74hc165.h file
const int max_switch = numBits ;

bool switch_state[max_switch];
bool switch_state_old[max_switch];
bool switch_state_new[max_switch];
bool switch_state_request[max_switch];

#ifdef BUTTON_TOGGLE_HIGH 

static void button_status_toggle_high_monitor() // when you press vcc from button 
{
  bool ic_pin_state = 0;
  for(int i = 0 ; i < max_switch ; i++ )
  {
    ic_pin_state = get_74hc165_pin_state(i+1);
    if(ic_pin_state == 1 ) { // button pressed
      switch_state_new[i] = 1 ;
    }
    if(ic_pin_state == 0 ) // button released
    {
      if(switch_state_new[i] == 1 )
      {
        bool state = switch_state[i] ;
        if(state == 1){ switch_state[i] = 0 ; }
        else { switch_state[i] = 1; }
        switch_state_new[i] = 0 ;
      } 
    }

  }
}
#endif


#ifdef BUTTON_TOGGLE_LOW

static void button_status_toggle_low_monitor() // when you press gnd from button 
{
  bool ic_pin_state = 0;
  for(int i = 0 ; i < max_switch ; i++ )
  {
    ic_pin_state = get_74hc165_pin_state(i+1);
    if(ic_pin_state == 0 ) { // button pressed
      switch_state_new[i] = 1 ;
    }
    if(ic_pin_state == 1 ) // button released
    {
      if(switch_state_new[i] == 1 )
      {
        bool state = switch_state[i] ;
        if(state == 1){ switch_state[i] = 0 ; }
        else { switch_state[i] = 1; }
        switch_state_new[i] = 0 ;
      } 
    }

  }
}

#endif


#ifdef SWITCH_HIGH 

static void switch_status_high_monitor() // switch on state , it will give VCC
{
  bool ic_pin_state = 0;
  for(int i = 0 ; i < max_switch ; i++ )
  {
    ic_pin_state = get_74hc165_pin_state(i+1);
    if(ic_pin_state == 1 ) { // switch on state
     switch_state_new[i] = 1 ; // on
    }
    else if(ic_pin_state == 0 ) { // switch off state
     switch_state_new[i] = 0 ; // off
    }

    if( switch_state_new[i] != switch_state_old[i] )
    {
      switch_state[i] = switch_state_new[i] ;
      switch_state_old[i] = switch_state_new[i];
    }
  }

}

#endif

#ifdef SWITCH_LOW 

static void switch_status_low_monitor() // switch on state , it will give GND
{
  bool ic_pin_state = 0;
  for(int i = 0 ; i < max_switch ; i++ )
  {
    ic_pin_state = get_74hc165_pin_state(i+1);
    if(ic_pin_state == 0 ) { // switch on state
     switch_state_new[i] = 1 ; // on
    }
    else if(ic_pin_state == 1 ) { // switch off state
     switch_state_new[i] = 0 ; //off
    }

    if( switch_state_new[i] != switch_state_old[i] )
    {
      switch_state[i] = switch_state_new[i] ;
      switch_state_old[i] = switch_state_new[i];
    }
  }

}

#endif

void clear_switch_status(int button)  // for application
{
  switch_state[button] = 0 ; // 1 on ; 0 off
}

void set_switch_status(int button)  // for application
{
  switch_state[button] = 1 ; // 1 on ; 0 off
}


bool get_switch_status(int pin)  // for application
{
  bool switch_status = 0 ; // off state
  int switch_number = pin - 1;

  if( switch_number < max_switch )
  {
    switch_status = switch_state[switch_number];
  }
return switch_status;
}

byte is_switch_state_changed(int pin)
{
  int pin_num = pin - 1;
  int status = 255 ; // invalid state or switch status not changed.
  if(switch_state_request[pin_num] != switch_state[pin_num])
  {
    status = switch_state[pin_num] ;
    switch_state_request[pin_num] = switch_state[pin_num];
  }

  return status ;
}




void ic_74hc165_switch_loop()
{
 
#ifdef BUTTON_TOGGLE_HIGH 
  button_status_toggle_high_monitor();
#endif

#ifdef BUTTON_TOGGLE_LOW
  button_status_toggle_low_monitor();
#endif

#ifdef SWITCH_HIGH
  switch_status_high_monitor();
#endif

#ifdef SWITCH_LOW
  switch_status_low_monitor();
#endif

}












#endif // _IC_74HC165_SWITCH_H