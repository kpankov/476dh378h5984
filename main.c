//
// Based on the first step, write a software module that uses the public API UART (USART) software module to receive and send messages between two UART hardware blocks (USART).
// Data for hardware block 1 (USART1):
// 1. Baud rate is 9600;
// 2. Receives data only (RX line is active);
// Data for hardware block 2 (USART2):
// 1. Baud rate is 115200;
// 2. Transmits data only (TX line is active);
// General data for the second task:
// 1. After receiving data via USART1, they must be saved and sent via USART2;
// 2. Transmission via USART2 is carried out in blocks of 128 bytes, so enough data must be accumulated before sending via USART2;
// 3. At the moment of transmission of the data block via USART2, it is possible to receive new data via USART1, so new / transmitted data should not be lost or damaged;
// 4. To check the functionality, a test should be created (the type of the test is at your discretion);
//

#include "uart_api.h"

// This is for getting single character rom console (linux/osx)
#include <unistd.h>
#include <termios.h>
char getch(void);


void uart1_rx_callback (char byte) {
  static char buff[128];
  static unsigned char num = 0;
  
  buff[num] = byte;

  if (num == 127) {
    uart_api_send_array(UART_API_UART2, buff);
    num = 0;
  } else {
    num += 1;
  }
}

int main() {
  char input_char;

  printf("UART_API\n");

  uart_api_init(UART_API_UART1, UART_API_BAUD_9600, UART_API_PARITY_NONE, UART_API_STOP_BIT_1);
  uart_api_init(UART_API_UART2, UART_API_BAUD_115200, UART_API_PARITY_NONE, UART_API_STOP_BIT_1);

  uart_api_set_rx_callback(UART_API_UART1, &uart1_rx_callback);

  // Test
  // You should print 128 symbols (it's UART1 RX line) and they will be sent by UART2.
  do {
    input_char = getch();
    uart_api_test_rx(UART_API_UART1, input_char);
  } while (1);
}






// Just for testing porposes
char getch(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    printf("%c", buf);
    return buf;
 }