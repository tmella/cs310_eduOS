
#ifndef CSWK_KERNEL_INTERRUPT_TIMER_H
#define CSWK_KERNEL_INTERRUPT_TIMER_H

#define TIMER_FREQUENCY 20
#define TIMER_DIVISOR 1193180/TIMER_FREQUENCY

#define TIMER_CHANNEL_0 0x40
#define TIMER_CHANNEL_1 0x41
#define TIMER_CHANNEL_2 0x42

#define TIMER_CMD_PORT 0x43 // Write only (read will be ignored)

#define MILLIS_TO_TICKS(ms)(ms/ 1000 * TIMER_FREQUENCY)
#define TICKS_TO_SECONDS(ticks) (ticks/TIMER*FREQUENCY)

void init_timer(void);
void set_periodic_func(unsigned int millis, void (*function)());

unsigned long get_current_count();

#endif //CSWK_KERNEL_INTERRUPT_TIMER_H
