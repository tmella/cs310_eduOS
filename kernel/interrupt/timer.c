
#include "timer.h"
#include "../low_level.h"
#include "idt.h"

/*
  * References:
  *     https://wiki.osdev.org/Programmable_Interval_Timer
  *     http://www.osdever.net/bkerndev/Docs/pit.htm
  */

// Random num can be increased
#define MAX_PERIODIC 25

static unsigned int count;

/* ticks = f * millis/1000 */
unsigned int millis_to_ticks(unsigned int millis) {
    return millis/1000 * TIMER_FREQUENCY;
}

// TODO: check what will happen when count reaches the int limit
void timer_handler() {
    count++;
}


void init_timer() {
    // Set the frequency and timer mode
    port_byte_out(TIMER_CMD_PORT, 0x36);
    port_byte_out(TIMER_CHANNEL_0, TIMER_DIVISOR & 0xFF); // High
    port_byte_out(TIMER_CHANNEL_0, TIMER_DIVISOR >> 8); // Low

    // Add handler to deal with interrupts
    add_handler(32, timer_handler);
}

void set_periodic_func(unsigned int seconds) {

}
