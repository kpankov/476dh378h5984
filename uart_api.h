//
// Write a public API to interact with a hardware UART (USART) block, which should include:
// 1. Initialization of the module;
// 2. Setting the baud rate;
// 3. Setting the parity bit;
// 4. Setting the duration of the stop bit;
// 5. Setting the callback function for the receiver / transmitter;
// 6. Data array transfer function. Data array will be sent by the transmitter;
// If the requirements described above are not enough to ensure the functionality of the module, then other parameters can be passed at your discretion.
// Additionally:
// 1. The hardware block only works with interrupts;
// 2. The software module must be able to work with several hardware blocks (USART1, USART2, etc.);
// 3. Public API should consist of only one header file (platform-specific source files are not needed);
//

#include "stdio.h"

#define UART_API_UARTS_NUM 4

enum UART_API_UARTS {
  UART_API_UART0,
  UART_API_UART1,
  UART_API_UART2,
  UART_API_UART3
};

enum UART_API_BAUD {
  UART_API_BAUD_9600,
  UART_API_BAUD_115200
};

enum UART_API_PARITY {
  UART_API_PARITY_NONE,
  UART_API_PARITY_EVEN,
  UART_API_PARITY_ODD
};

enum UART_API_STOP_BIT {
  UART_API_STOP_BIT_1,
  UART_API_STOP_BIT_1_5,
  UART_API_STOP_BIT_2
};

typedef void (*rx_callback_t)(char byte);

static rx_callback_t rx_callbacks[UART_API_UARTS_NUM];


void uart_api_init(enum UART_API_UARTS uart, enum UART_API_BAUD baud, enum UART_API_PARITY parity, enum UART_API_STOP_BIT stop_duration) {
  //
}

void uart_api_set_rx_callback(enum UART_API_UARTS uart, rx_callback_t rx_callback) {
  rx_callbacks[uart] = rx_callback;
}

void uart_api_send_array(enum UART_API_UARTS uart, char buff_128[128]) { // To avoid byte lost :)
  printf("\n\nUART%d TX: [%.128s]\n\n", uart, buff_128);
}

void uart_api_test_rx(enum UART_API_UARTS uart, char byte) {
  // Test function for emulate receiving
  rx_callbacks[uart](byte);
}