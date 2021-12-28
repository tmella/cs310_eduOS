
#ifndef CSWK_KERNEL_INTERRUPT_TIMER_H
#define CSWK_KERNEL_INTERRUPT_TIMER_H

#define TIMER_FREQUENCY 20
#define TIMER_DIVISOR 1193180/TIMER_FREQUENCY

#define TIMER_CHANNEL_0 0x40
#define TIMER_CHANNEL_1 0x41
#define TIMER_CHANNEL_2 0x42

#define TIMER_CMD_PORT 0x43 // Write only (read will be ignored)

void init_timer(void);
void set_periodic_func(unsigned int millis, void (*function)());

unsigned int millis_to_ticks(unsigned int millis);


#endif //CSWK_KERNEL_INTERRUPT_TIMER_H
