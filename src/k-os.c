#include <stdint.h>
#include "reg.h"

#define USART_FLAG_TXE	((uint16_t) 0x0080)

void usart_init() {
	*(RCC_APB2ENR) |= (uint32_t) (0x00000001 | 0x00000004);
	*(RCC_APB1ENR) |= (uint32_t) (0x00020000);

	/* USART2 Configuration, Rx->PA3, Tx->PA2 */
	*(GPIOA_CRL) = 0x00004B00;
	*(GPIOA_CRH) = 0x44444444;
	*(GPIOA_ODR) = 0x00000000;
	*(GPIOA_BSRR) = 0x00000000;
	*(GPIOA_BRR) = 0x00000000;

	*(USART2_CR1) = 0x0000000C;
	*(USART2_CR2) = 0x00000000;
	*(USART2_CR3) = 0x00000000;
	*(USART2_CR1) |= 0x2000;
}

char send_char(char ch) {
		while (!(*(USART2_SR) & USART_FLAG_TXE));
		*(USART2_DR) = ch & 0xFF;
		return ch;
}

int send_string(const char *str)
{
	while (*str) {
		send_char(*str++);
	}
	return 0;
}

void usertask(void)
{
	send_string("User Task #1\n");
	while (1); /* Never terminate the task */
}

extern void activate(unsigned int *stack);

void main(void)
{
	/* Initialization of process stack.
	 * r4, r5, r6, r7, r8, r9, r10, r11, lr */
	unsigned int usertask_stack[256];
	unsigned int *usertask_stack_start = usertask_stack + 256 - 16;
	usertask_stack_start[8] = (unsigned int) &usertask;

	usart_init();

	send_string("KOS Starting...\n");

	activate(usertask_stack_start);

	send_string("Hello World!\n");

	while (1);
}
