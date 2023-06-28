#include <stdint.h>
#include <stddef.h>

#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>

#include "Board.h"

void *mainThread(void *arg0)
{
  GPIO_init();
  UART_init();

  // LED
  GPIO_setConfig(Board_GPIO_LED0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
  GPIO_write(Board_GPIO_LED0, Board_GPIO_LED_ON);

  /* Create UART with data processing off. */
  UART_Params uartParams;
  UART_Params_init(&uartParams);
  uartParams.writeDataMode = UART_DATA_BINARY;
  uartParams.readDataMode = UART_DATA_BINARY;
  uartParams.readReturnMode = UART_RETURN_FULL;
  uartParams.readEcho = UART_ECHO_OFF;
  uartParams.baudRate = 115200;

  UART_Handle uart = UART_open(Board_UART0, &uartParams);

  if (uart == NULL) {
    /* UART_open() failed */
    while (1);
  }

  const char  echoPrompt[] = "Echoing characters:\r\n";
  UART_write(uart, echoPrompt, sizeof(echoPrompt));

  /* Loop forever echoing */
  char input;
  while (1) {
    UART_read(uart, &input, 1);
    UART_write(uart, &input, 1);
  }
}
