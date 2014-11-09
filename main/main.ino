#include "dynamixel.h"

#define NEWID 2
using namespace std;

void setup()
{
  Serial.begin(MEGABIT);
}


// Variables for demo
int led = 0;
int pos = 0;
int ID = 1;

// Variables for state machine
typedef enum{
  MovingUp = 0,
  MovingDown
} State;

void loop()
{
  State state = MovingUp;
  
 #ifdef NEWID
   // old ID = 1, ID address = 3, ID = NEWID
   // Note: you must specify the old ID to set the new ID..
   sendPacketByte(1, 3, NEWID);
 #endif 
  while(1){
    delay(5);
    switch(state)
    {
      case MovingUp:
        // ID = 1, LED address = 25, blue = 4
        sendPacket(ID, 25, 4);
        pos++;
        if (pos > 1022)
        {
          state = MovingDown;
        }
      break;
      
      case MovingDown:
        // ID = 1, LED address = 25, yellow = 3
        sendPacket(ID, 25, 3);
        pos--;
        if (pos < 2)
        {
          state = MovingUp;
        }
      break;
      default:
        // ID = 1, LED address = 25, red = 1 (ERROR!)
        sendPacket(ID, 25, 1);
      break;
    }
    delay(1);
    // ID = 1, goal position address = 30, pos = pos
    sendPacket(ID, 30, pos);
  }
  
  
}
