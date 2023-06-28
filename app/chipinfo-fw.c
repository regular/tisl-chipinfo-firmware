#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>

#include "Board.h"
#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(driverlib/chipinfo.h)

/*
#include DeviceFamily_constructPath(inc/hw_fcfg1.h)
#include DeviceFamily_constructPath(inc/hw_ccfg.h)
#include DeviceFamily_constructPath(inc/hw_ccfg_simple_struct.h)
*/

extern const char *chip_type_names[];
extern int num_chip_types;

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

  const ChipType_t ct = ChipInfo_GetChipType();
  const char* ct_name;
  if (ct >= num_chip_types || ct < 0) {
    ct_name = "n/a";
  } else {
    ct_name = chip_type_names[ct];
  }

  const char  echoPrompt[] = "Chip type is:\r\n";
  UART_write(uart, echoPrompt, sizeof(echoPrompt));
  UART_write(uart, ct_name, strlen(ct_name));

  /* Loop forever echoing */
  char input;
  while (1) {
    UART_read(uart, &input, 1);
    UART_write(uart, &input, 1);
  }
}
