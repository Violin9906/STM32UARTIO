/*
 * uartio.c
 *
 *  Created on: Jun 21, 2020
 *      Author: Violin
 */

#include "uartio.h"

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#define PUTCHAR __io_putchar
#define GETCHAR_PROTOTYPE int __io_getchar(void)
#define GETCHAR __io_getchar
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#define PUTCHAR fputc
#define GETCHAR_PROTOTYPE int fgetc(FILE * f)
#define GETCHAR fgetc
#endif /* __GNUC__ */

PUTCHAR_PROTOTYPE {
  extern UART_HandleTypeDef __UART_HANDLE_UARTIO;
  if (HAL_UART_Transmit(&__UART_HANDLE_UARTIO, (uint8_t*) &ch, 1, 0xFFFF) != HAL_OK) {
    Error_Handler();
  }
  return ch;
}

GETCHAR_PROTOTYPE {
  extern UART_HandleTypeDef __UART_HANDLE_UARTIO;
  uint8_t ch = 0;
  HAL_UART_Receive(&__UART_HANDLE_UARTIO, (uint8_t*) &ch, 1, 0xFFFF);

  if (ch == '\r') {
#ifdef __GNUC__
    PUTCHAR('\r');
#else
    PUTCHAR('\r', NULL);
#endif
    ch = '\n';
  }
#ifdef __GNUC__
  return PUTCHAR(ch);
#else
  return PUTCHAR(ch, NULL);
#endif
}

int _read(int file, char *ptr, int len) {
  int DataIdx;

  for (DataIdx = 0; DataIdx < len; DataIdx++) {
#ifdef __GNUC__
    *ptr = GETCHAR();
#else
    *ptr = GETCHAR(NULL);
#endif
    if (*ptr++ == '\n')
      break;
  }
  return ++DataIdx;
}
