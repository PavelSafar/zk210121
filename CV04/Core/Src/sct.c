/*
 * sct.c
 *
 *  Created on: 16. 10. 2020
 *      Author: Pavel
 */
#include "STM32F0xx.h"
#include "sct.h"
#define sct_nla(x) do { if (x) GPIOB->BSRR = (1 << 5); else GPIOB->BRR = (1 << 5); } while (0)
#define sct_sdi(x) do { if (x) GPIOB->BSRR = (1 << 4); else GPIOB->BRR = (1 << 4); } while (0)
#define sct_clk(x) do { if (x) GPIOB->BSRR = (1 << 3); else GPIOB->BRR = (1 << 3); } while (0)
#define sct_noe(x) do { if (x) GPIOB->BSRR = (1 << 10); else GPIOB->BRR = (1 << 10); } while (0)


void sct_led(uint32_t value)
{
	for (uint8_t j = 0; j<32; j++)
	{
		sct_sdi(value&1);
		value=value>>1;
		sct_clk(1);
		sct_clk(0);
	}
	sct_nla(1);
	sct_nla(0);
}

void sct_init(void)
{

	sct_led(0);
}

void sct_value(uint16_t value, uint16_t bargraph)
{
	value = value%1000;
	uint32_t out = reg_values[2][value%10];
	value = value /10;
	if(value>0)
	{
		out |= reg_values[1][value%10];
		value = value /10;
		if(value>0)
		{
			out |= reg_values[0][value%10];
		}
	}
	out |= reg_values[3][bargraph%10];
	sct_led(out);
}
