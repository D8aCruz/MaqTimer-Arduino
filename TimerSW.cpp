#include "TimerSW.h"

volatile   unsigned int TmrRun[ N_TIMERS ];
volatile  unsigned char  TmrEvents[ N_TIMERS ];
void    (* Tmr_handlers [N_TIMERS]) (void);
volatile  unsigned char  TmrStandBy[ N_TIMERS ];
volatile  unsigned char  TmrBase[ N_TIMERS ];

TimerSW::TimerSW(){
}

void TimerSW::AnalizarTimers(void){
    unsigned char i;
    for( i=0; i<N_TIMERS; i++ ){
        if(TmrRun[i]){
            if(!TmrStandBy[i]){
                TmrRun[i]--;
                if(!TmrRun[i]){
                    TmrEvents[i] = 1;
                }
            }
        }
    }  

}

void TimerSW::TimerEvent(void){
  unsigned char i;
  for( i=0; i<N_TIMERS; i++ ){
      if(TmrEvents[i]){
          TmrEvents[i] = 0;
          Tmr_handlers[i]();
      }
  }   
}

void TimerSW::TimerStart(unsigned char event, unsigned int tiempo, Timer_Handler handler, unsigned char base){
  TmrBase[event] = base;
  switch(base){
      case DEC:   tiempo *= DECIMAS;    break;
      case SEG:   tiempo *= SEGUNDOS;   break;
      case MIN:   tiempo *= MINUTOS;    break;
  }
  
  Tmr_handlers[event] = handler;
  if(tiempo != 0){
      TmrRun[event] = tiempo;
      TmrEvents[event] = 0;
      TmrStandBy[event]= RUN;
  } else {
      TmrRun[event] = 0;
      TmrEvents[event] = 1;
  }
}

void TimerSW::SetTimer(unsigned char event, unsigned int tiempo){
    TmrRun[event] += tiempo;
}

unsigned int TimerSW::GetTimer(unsigned char event){
    return TmrRun[event];
}

void TimerSW::StandByTimer(unsigned char event, unsigned char accion){
    TmrStandBy[event] = accion;
}

void TimerSW::TimerStop(unsigned char event){
  TmrRun[event] = 0;
  TmrStandBy[event] = 0;
  Tmr_handlers[event] = NULL;
}

void TimerSW::TimerClose(void){
  unsigned char i;
  for( i=0; i<N_TIMERS; i++ ){
      TmrRun[i] = 0;
      TmrStandBy[i] = 0;
      Tmr_handlers[i] = NULL;
  }
}
