
#include "../low_level.h"
#include "timer.h"
#include "../inter.h"

static unsigned int count;

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

void timer_wait(unsigned int millis) {
    unsigned int waitCount = count + millis/1000 * TIMER_FREQUENCY;
    while(count < waitCount);
}




