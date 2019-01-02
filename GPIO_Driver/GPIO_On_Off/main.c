#include <stm32f0xx.h>

#define GPIO_LED	(4)

#define GPIO_MODER_INPUT											(0x0U)
#define GPIO_MODER_OUTPUT											(0x1U)
#define GPIO_MODER_ALT_FUNC										(0x2U)
#define GPIO_MODER_ANALOG											(0x3U)
#define GPIO_MODER_MASK												(0x3U)

#define GPIO_OTYPER_OUTPUT_PUSH_PULL					(0x0U)
#define GPIO_OSPEEDR_HIGH											(0x3U)

#define GPIO_ODR_SET_BIT											(0x1U)

#define GPIO_A_SET_MODE_OUTPUT(x)	(GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MASK << 2*x)) | GPIO_MODER_OUTPUT << 2*x)
#define GPIO_A_SET_SPEED_HIGH(x)	(GPIOA->OSPEEDR |= GPIO_OSPEEDR_HIGH << 2*x)
#define GPIO_A_SET_UP(x)					(GPIOA->ODR |= GPIO_ODR_SET_BIT << x)
#define GPIO_A_SET_DOWN(x)				(GPIOA->ODR &= ~(GPIO_ODR_SET_BIT << x))

int main(void)
{
	//Set RCC to enable GPIOA
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	
	//Set GPIO register
	//GPIOA->MODER = (GPIOA->MODER & ~(0x3U << 2*GPIO_LED)) | 0x1U << 2*GPIO_LED;
	GPIO_A_SET_MODE_OUTPUT(GPIO_LED);
	//GPIOA->OSPEEDR |= 0x3U << 2*GPIO_LED;	
	GPIO_A_SET_SPEED_HIGH(GPIO_LED);
	
	//Set GPIO Up
	//GPIOA->ODR |= 0x1U << GPIO_LED;
	GPIO_A_SET_UP(GPIO_LED);
	//Set GPIO Down
	//GPIOA->ODR &= ~(0x1U << GPIO_LED); 
	GPIO_A_SET_DOWN(GPIO_LED);

	while(1);
}

