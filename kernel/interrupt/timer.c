
#include "timer.h"
#include "../low_level.h"
#include "idt.h"

#include "../process/process_scheduler.h"

/*
 *  Timer & Counter: this implementation acts as both
 *
  * References:
  *     https://wiki.osdev.org/Programmable_Interval_Timer
  *     http://www.osdever.net/bkerndev/Docs/pit.htm
  */

// Random num can be increased
#define MAX_PERIODIC 25
#define MAX_FUNCTIONS 10

struct periodic_functions {
  uint32_t remaining;
  uint32_t needed_count;
  void (*function)();
};

// Using this instead of list (for now)
int index = 0;
struct periodic_functions functions[MAX_FUNCTIONS];

static unsigned long count;

unsigned int seconds_to_tick(unsigned int seconds) {
    return seconds * TIMER_FREQUENCY;
}

// TODO: check what will happen when count reaches the int limit
void timer_handler() {
    count++;
    scheduler_timer_handler();
    for (int i = 0; i < index; i++) {
        if (functions[i].remaining) {
            functions[i].remaining--;
        } else {
            functions[i].remaining = functions[i].needed_count;
            functions[i].function();
        }
    }
}

void init_timer() {
    // Set the frequency and timer mode
    port_byte_out(TIMER_CMD_PORT, 0x36);
    port_byte_out(TIMER_CHANNEL_0, TIMER_DIVISOR & 0xFF); // High
    port_byte_out(TIMER_CHANNEL_0, TIMER_DIVISOR >> 8); // Low

    // Add handler to deal with interrupts
    add_handler(32, timer_handler);
}

void set_periodic_func(unsigned int millis, void (*function)()) {
    uint32_t value = index++;
    if (value == MAX_FUNCTIONS - 1) {
        print_string("PANIC not working");
    }
    functions[value].function = function;
    functions[value].needed_count = functions[value].remaining
        = MILLIS_TO_TICKS(millis);
}
