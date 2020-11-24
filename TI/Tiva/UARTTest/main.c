#include "tm4c123gh6pm.h"
#include <stdint.h>

void UART_Init()
{
    SYSCTL_RCGC1_R |= 0x00000001;  // activate UART0
    SYSCTL_RCGC2_R |= 0x00000001;  // activate port A
    UART0_CTL_R &= ~0x00000001;    // disable UART
    UART0_IBRD_R = 8;              // IBRD = int(16,000,000/(16*115,200)) = int(8.6806)
    UART0_FBRD_R = 44;             // FBRD = round(0.6806 * 64) = 44
    UART0_LCRH_R = 0x00000070;     // 8 bit, no parity bits, one stop, FIFOs
    UART0_CTL_R |= 0x00000001;     // enable UART
    GPIO_PORTA_AFSEL_R |= 0x03;    // enable alt funct on PA[1:0]
    GPIO_PORTA_DEN_R |= 0x03;      // configure PA[1:0] as UART0
//    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011;    // GPIO A[1:0]의 기능은 기본이 UART0 이다.
    GPIO_PORTA_AMSEL_R &= ~0x03;   // disable analog on PA[1:0]
}

unsigned char UART_InChar(void)
{
  while((UART0_FR_R&0x0010) != 0);      // wait until RXFE is 0
  return((unsigned char)(UART0_DR_R&0xFF));
}

// Wait for buffer to be not full, then output
void UART_OutChar(unsigned char data)
{
  while((UART0_FR_R&0x0020) != 0);      // wait until TXFF is 0
  UART0_DR_R = data;
}

/**
 * main.c
 */
int main(void)
{
    unsigned char buff;

    UART_Init();

    while(1)
    {
        buff = UART_InChar();
        UART_OutChar(buff);
    }
	return 0;
}
