#include "tm4c123gh6pm.h"
#include <stdint.h>

unsigned long now;
unsigned long last;
unsigned long elapsed;

void SysTick_Init()
{
    NVIC_ST_CTRL_R = 0;
    NVIC_ST_RELOAD_R = 0x0FFFFFF;
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_CTRL_R = 0x00000005;
}

void Action()
{
    now = NVIC_ST_CURRENT_R;
    elapsed = (last - now) & 0x00FFFFFF;
    last = now;
}

/**
 * main.c
 */
int main(void)
{
    SysTick_Init();

    while(1)
    {
        Action();
    }
	return 0;
}
