#include <stdint.h>
#include "usart.h"

extern void activate(unsigned int *stack);

void usertask(void)
{
	usart_send_string("User Task #1\n");
	while (1);
}

void main(void)
{
	unsigned int usertask_stack[256];
	unsigned int *usertask_stack_start = usertask_stack + 256 - 16;
	usertask_stack_start[8] = (unsigned int) &usertask;

	usart_init();

	usart_send_string("KOS Starting...\n");

	activate(usertask_stack_start);

	usart_send_string("Hello World!\n");
	while (1);
}
