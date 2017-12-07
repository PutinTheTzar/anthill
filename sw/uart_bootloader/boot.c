#include <stdint.h>

#include "board.h"
#include "uart.h"
#define USER_START 0x00000800

#define __get_uint32_t(source) (\
     (*((uint8_t *)source + 0) << 0 ) |\
     (*((uint8_t *)source + 1) << 8 ) |\
     (*((uint8_t *)source + 2) << 16) |\
     (*((uint8_t *)source + 3) << 24))

void main()
{
  uint8_t buffer[4];

  int i;
  uint8_t *ptr;
  uint32_t size;

  uart_init_hw();

  uart_write_byte('B');
  uart_write_byte('o');
  uart_write_byte('o');
  uart_write_byte('t');
  uart_write_byte('?');

  while(1)
  {
    while(uart_read_byte () != 'Y')
    {
    }

    uart_write_byte('O');
    uart_write_byte('K');

    for (i=0;i<4;i++)
    {
      buffer[i] = uart_read_byte();
    }
    size = __get_uint32_t(buffer);

    // read code
    for (ptr = (uint8_t *)(USER_START);
         ptr < (uint8_t *)(USER_START+size);
         ptr++)
    {
      *ptr = uart_read_byte();
    }

    uart_write_byte('G');
    uart_write_byte('o');
    uart_write_byte('!');

    ((int(*)(void))(USER_START))();
  }
}
