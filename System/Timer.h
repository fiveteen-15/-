#ifndef __TIMER_H
#define __TIMER_H

void Timer_Init(void);
void TIM3_IRQHandler(void);
void My_get_ms(unsigned long *count);

#endif
