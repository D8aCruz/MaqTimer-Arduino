#include <TimerOne.h>
#include "TimerSW.h"
TimerSW maqTimer;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);
  Timer1.initialize(10000);
  Timer1.attachInterrupt(blink);
  maqTimer.TimerStart(1,1,toggle,SEG);
}

void blink(void)
{
  maqTimer.AnalizarTimers();
}

void toggle()
{
  digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
  maqTimer.TimerStart(1,50,toggle,DEC);
}
void loop() {
  maqTimer.TimerEvent();
}
