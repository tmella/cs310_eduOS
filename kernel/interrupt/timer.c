
#include "timer.h"

#include "idt.h"
#include "../low_level.h"
#include "../process/process_scheduler.h"

#include "../../stdlib/stdlib.h"

/*
 *  Timer & Counter: this implementation acts as both
 *
  * References:
  *     https://wiki.osdev.org/Programmable_Interval_Timer
  *     http://www.osdever.net/bkerndev/Docs/pit.htm
  */

// Random num can be increased
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

unsigned int ticks_to_seconds(unsigned long ticks) {
    return ticks/TIMER_FREQUENCY;
}

unsigned int seconds_to_tick(unsigned int seconds) {
    return seconds * TIMER_FREQUENCY;
}

void timer_handler() {
    // No issue with counter as it should take ~7 years to overflow
    count++;
    scheduler_timer_handler();

    // Runs periodic functions (potentially unreachable)
    // not used for now though
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

unsigned long get_current_count() {
    return count;
}
