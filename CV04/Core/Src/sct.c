/*
 * sct.c
 */
#include "STM32F0xx.h"
#include "sct.h"
#define sct_nla(x) do { if (x) GPIOB->BSRR = (1 << 5); else GPIOB->BRR = (1 << 5); } while (0)
#define sct_sdi(x) do { if (x) GPIOB->BSRR = (1 << 4); else GPIOB->BRR = (1 << 4); } while (0)
#define sct_clk(x) do { if (x) GPIOB->BSRR = (1 << 3); else GPIOB->BRR = (1 << 3); } while (0)
#define sct_noe(x) do { if (x) GPIOB->BSRR = (1 << 10); else GPIOB->BRR = (1 << 10); } while (0)


static const uint32_t reg_values[4][10] = {
	 {
	 //PCDEpcdegfabGFAB @ DIS1
	 0b0001000000000010 << 16,
	 0b0000000000000011 << 16,
	 0b0001000000000010 << 16,
	 0b0110000000001011 << 16,
	 0b0100000000001101 << 16,
	 0b0110000000001110 << 16,
	 0b0111000000001110 << 16,
	 0b0100000000000011 << 16,
	 0b0111000000001111 << 16,
	 0b0110000000001111 << 16,
	 },
	 {
	 //----PCDEGFAB---- @ DIS2
	 0b0000011101110000 << 0,
	 0b0000010000010000 << 0,
	 0b0000001110110000 << 0,
	 0b0000011010110000 << 0,
	 0b0000010011010000 << 0,
	 0b0000011011100000 << 0,
	 0b0000011111100000 << 0,
	 0b0000010000110000 << 0,
	 0b0000011111110000 << 0,
	 0b0000011011110000 << 0,
	 },
	 {
	 //PCDE--------GFAB @ DIS3
	 0b0111000000000111 << 0,
	 0b0100000000000001 << 0,
	 0b0011000000001011 << 0,
	 0b0110000000001011 << 0,
	 0b0100000000001101 << 0,
	 0b0110000000001110 << 0,
	 0b0111000000001110 << 0,
	 0b0100000000000011 << 0,
	 0b0111000000001111 << 0,
	 0b0110000000001111 << 0,
	 },
	 {
	 //----43215678---- @ LED
     0b0000000000000000 << 16,
	 0b0000000100000000 << 16,
	 0b0000001100000000 << 16,
	 0b0000011100000000 << 16,
	 0b0000111100000000 << 16,
	 0b0000111110000000 << 16,
	 0b0000111111000000 << 16,
	 0b0000111111100000 << 16,
	 0b0000111111110000 << 16,
	 0b0000000000000000 << 0
	 	 },
	 };




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
