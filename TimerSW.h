#ifndef TIMERSW_H_
#define TIMERSW_H_

#define   N_TIMERS  10
#define   NULL    (( void *) 0)

typedef void (*Timer_Handler)(void);
extern volatile   unsigned int TmrRun[ N_TIMERS ];
extern volatile   unsigned char  TmrEvents[ N_TIMERS ];
extern void     (* Tmr_handlers [N_TIMERS]) (void);
extern volatile   unsigned char  TmrStandBy[ N_TIMERS ];
extern volatile   unsigned char TmrBase[ N_TIMERS ];

#define   DEC     0
#define   SEG     1
#define   MIN     2

#define   RUN       0
#define   PAUSE     1

#define   DECIMAS     1
#define   SEGUNDOS    100
#define   MINUTOS     6000

class TimerSW{
  public:
    TimerSW( );
    void AnalizarTimers(void);
    void TimerEvent(void);

    void TimerStart(unsigned char event, unsigned int tiempo, Timer_Handler handler, unsigned char base);
    void SetTimer(unsigned char event, unsigned int tiempo);
    unsigned int GetTimer(unsigned char event);
    void StandByTimer(unsigned char event, unsigned char accion);
    void TimerStop(unsigned char event);
    void TimerClose(void);
};


#endif /* TIMERSW_H_ */
