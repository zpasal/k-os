#ifndef __USART_H
#define __USART_H

#define USART_FLAG_TXE  ((uint16_t) 0x0080)

void usart_init();
char usart_send_char(char ch);
int usart_send_string(const char *str);

#endif
