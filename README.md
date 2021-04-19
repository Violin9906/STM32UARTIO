# STM32UARTIO
STM32 UART IO Redirect

## 描述

本库用于STM32重定向`printf()`和`scanf()`到UART串口（代码中为UART1），使用HAL库编写。

## 示例

```c
/* ----main.c---- */
#include "uartio.h"
// ......
UART_HandleTypeDef huart1;

int main() {
    // ......
    int x;
    scanf("%d", &x);
    printf("%d\r\n", x);
}
```

更多示例，请参看[Violin9906/STM32F413MiniSys/EXAMPLES](https://github.com/Violin9906/STM32F413MiniSys/tree/master/EXAMPLES)

