#include <stdint.h>
#include "tm4c123gh6pm.h"

#define RED (1 << 1)
#define BLUE (1 << 2)
#define GREEN (1 << 3)
#define SW1 (1 << 4)
#define SW2 (1 << 0)
#define ENABLE (1 << 0)
#define CLK_SRC (1 << 2)
#define COUNT_FLAG (1 << 16)

#define STCTRL_R    (*((volatile uint32_t *)0xE000E010))
#define STRELOAD_R  (*((volatile uint32_t *)0xE000E014))
#define STCURRENT_R (*((volatile uint32_t *)0xE000E018))

int main(void)
{
    SYSCTL_RCGC2_R |= 0x00000020;

    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R = 0x1F;

    GPIO_PORTF_DIR_R = 0x0E;
    GPIO_PORTF_DEN_R = 0x1F;
    GPIO_PORTF_PUR_R = 0x11;

    GPIO_PORTF_DATA_R = 0x00;

    STCTRL_R = 0;
    STRELOAD_R = 16000000 - 1;
    STCTRL_R |= ENABLE | CLK_SRC;

    while (1)
    {
        while ((STCTRL_R & COUNT_FLAG) == 0)
        {
            if (!(GPIO_PORTF_DATA_R & SW1)) {GPIO_PORTF_DATA_R |= BLUE;}
            else {GPIO_PORTF_DATA_R &= ~BLUE;}
        }

        GPIO_PORTF_DATA_R ^= RED;

    }
}
