/*
 * References:
 *     https://wiki.osdev.org/Programmable_Interval_Timer
 *     http://www.osdever.net/bkerndev/Docs/pit.htm
 */

#ifndef KERNEL_INTERRUPTS_TIMER_H
#define KERNEL_INTERRUPTS_TIMER_H

#define TIMER_FREQUENCY 20
#define TIMER_DIVISOR 1193180/TIMER_FREQUENCY

#define TIMER_CHANNEL_0 0x40
#define TIMER_CHANNEL_1 0x41
#define TIMER_CHANNEL_2 0x42

#define TIMER_CMD_PORT 0x43 // Write only (read will be ignored)

void init_timer();
void timer_wait(unsigned int millis);

#endif //KERNEL_INTERRUPTS_TIMER_H
