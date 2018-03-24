#include <stdint.h>
#include "usart.h"

extern void activate_task(unsigned int *stack_ptr);

void user_task_1(void)
{
	usart_send_string("User Task 1\n");
	while (1);
}

void main(void)
{
	unsigned int user_task_1_stack[256];
	// 16 make room for registers
	unsigned int *user_task_1_stack_start = user_task_1_stack + 256 - 16;
	// setup entry point (PC)
	user_task_1_stack_start[8] = (unsigned int) &user_task_1;

	usart_init();
	usart_send_string("KOS Starting...\n");

	activate_task(user_task_1_stack_start);

	while (1);
}
