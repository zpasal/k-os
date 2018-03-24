#include <stdint.h>
#include "reg.h"
#include "usart.h"

// Thanks to https://github.com/jserv/mini-arm-os for init routines!

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

char usart_send_char(char ch) {
    while (!(*(USART2_SR) & USART_FLAG_TXE));
    *(USART2_DR) = ch & 0xFF;
    return ch;
}

int usart_send_string(const char *str)
{
  while (*str) {
    usart_send_char(*str++);
  }
  return 0;
}
