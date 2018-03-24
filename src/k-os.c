#include <stdint.h>
#include "usart.h"

extern void activate_task(unsigned int *stack_ptr);

/*
https://armengineer.com/arm-cortex-m-context-switching-part-1/

1 SysTick exception is triggered
2 The CPU pushes registers psr, pc, lr, r12, r3-r0 onto the process stack
3 The task list is searched to find a task that is runnable
4 If a task is found save the current task state, i.e. the remaining unsaved
  registers {r4-r11} are pushed onto the task stack and the stack pointer is
  saved
5 Restore the state of the next task , using that tasks stack, i.e.
  pop registers off the stack that are not handled by the exception
  handler {r4-r11}
6 Instruct the CPU to use the new tasks stack when returning from exception
7 Return from exception into Thread Mode
8 The CPU restores registers  psr, pc, lr, r12, r3-r0 from the task stack,
  which means the execution of the process continues from the newly loaded program counter (pc)
*/

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
	usart_send_string("K-OS Starting...\n");

	activate_task(user_task_1_stack_start);

	while (1);
}
