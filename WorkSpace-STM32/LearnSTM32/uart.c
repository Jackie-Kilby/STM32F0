#include "uart.h"
#include "string.h"

#define TX_BUFFER_SIZE	64
int tx_buffer[TX_BUFFER_SIZE];
int * tx_ps;			//pointer for saving
int * tx_pt;			//pointer for transfer

extern uint32_t g_sys_clock;

void usart_init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	RCC->CFGR3 |= RCC_CFGR3_USART1SW_0;				//select sysclock(default HSI) as USART1 clock
	
	//Set GPIO PA9 Alternative func. 
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER &= ~GPIO_MODER_MODER9_Msk;
	GPIOA->MODER |= GPIO_MODER_MODER9_1;
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_9;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR9;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR9_Msk;
	GPIOA->AFR[1] |= (0x01 << GPIO_AFRH_AFRH1_Pos);
	
	//Step1. Set Data WordLength = 8
	USART1->CR1 &= ~USART_CR1_M_Msk;			//default
	USART1->CR1 &= ~(1 << 28);					//default
	//Step2. Set Baud Rate
	USART1->CR1 &= ~USART_CR1_OVER8_Msk;		//default = oversampling by 16

	USART1->BRR = g_sys_clock*1000/9600;
	//Step3. Set stop bits
	USART1->CR2 &= ~USART_CR2_STOP_Msk;			//default = 1 stop bit
	//Step4. Enable USART
	USART1->CR1 |= USART_CR1_UE;
	//Step5. Enable Tx, send Idle Frame
	USART1->CR1 |= USART_CR1_TE;
	
	memset(tx_buffer, -1, sizeof tx_buffer);
	tx_ps = &tx_buffer[0];
	tx_pt = &tx_buffer[0];
}

void usart_tx_char(int* ch)
{
	USART1->TDR = *ch;
	while(!(USART1->ISR & USART_ISR_TXE_Msk));
}

void usart_write(const char * string, int num)
{
	int i=0;
	for(i=0 ; i<num ; i++)
	{
		if(tx_ps == tx_buffer + TX_BUFFER_SIZE)
		{
			tx_ps = tx_buffer;
		}
		if(*tx_ps == -1)
		{
			*tx_ps = *string;
			tx_ps++;
			string++;
			if(tx_ps == tx_pt)
			{
				//buffer full
				return;
			}
		}
	}
}

void usart_Task(void)
{
	if(*tx_pt == -1)
		return;
	else
	{
		usart_tx_char(tx_pt);
		*tx_pt = -1;
		tx_pt++;
		if(tx_pt == tx_buffer + TX_BUFFER_SIZE)
		{
			tx_pt = tx_buffer;
		}
	}
}
