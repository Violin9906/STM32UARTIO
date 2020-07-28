/*
 * uartio.c
 *
 *  Created on: Jun 21, 2020
 *      Author: Violin
 */

#include "uartio.h"

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#define GETCHAR_PROTOTYPE int __io_getchar(void)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#define GETCHAR_PROTOTYPE int fgetc(FILE * f)
#endif /* __GNUC__ */

PUTCHAR_PROTOTYPE {
  extern UART_HandleTypeDef huart4;
  if (HAL_UART_Transmit(&huart4, (uint8_t*) &ch, 1, 0xFFFF) != HAL_OK) {
    Error_Handler();
  }
  return ch;
}

GETCHAR_PROTOTYPE {
  extern UART_HandleTypeDef huart4;
  uint8_t ch = 0;
  HAL_UART_Receive(&huart4, (uint8_t*) &ch, 1, 0xFFFF);

  if (ch == '\r') {
    __io_putchar('\r');
    ch = '\n';
  }

  return __io_putchar(ch);
}

int _read(int file, char *ptr, int len) {
  int DataIdx;

  for (DataIdx = 0; DataIdx < len; DataIdx++) {
    *ptr = __io_getchar();
    if (*ptr++ == '\n')
      break;
  }
  return ++DataIdx;
}
