
/* This file includes some methods that are very similar to stdlib calls but avoids the
 * need to execute a syscall as we are already in kernel mode and there are times when
 * interrupts are unnecessary and wastefull*/

#ifndef CSWK_KERNEL_KSTD_H
#define CSWK_KERNEL_KSTD_H

void kprintf(const char *format, ...);
void kprintf_c(char colour, const char *format, ...);

#endif //CSWK_KERNEL_KSTD_H
