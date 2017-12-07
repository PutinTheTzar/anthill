#include <stdint.h>

#include "board.h"
#include "uart.h"
#include "urv_time.h"

void main()
{
  uart_init_hw();

  while(1)
  {
    urv_sleep_us(200000);

    uart_write_byte('H');
    uart_write_byte('e');
    uart_write_byte('l');
    uart_write_byte('l');
    uart_write_byte('o');
    uart_write_byte('\r');
    uart_write_byte('\n');
  }
}
