#include <stm32f0xx.h>
#include <stdint.h>




#define GPIO_ENABLE(port)				(RCC->AHBENR |= RCC_AHBENR_GPIO##port##EN)
#define GPIO_SET_MODE_OUTPUT(port,pin)	(GPIO##port->MODER = (GPIO##port->MODER & ~GPIO_MODER_MODER##pin##_Msk) | GPIO_MODER_MODER##pin##_0);\
																(GPIO##port->OTYPER &= ~GPIO_OTYPER_OT_##pin);\
																(GPIO##port->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR##pin);\
																(GPIO##port->PUPDR &= ~GPIO_PUPDR_PUPDR##pin##_Msk)
																				
#define GPIO_SET_MODE_INPUT(port,pin)	(GPIO##port->MODER &= ~GPIO_MODER_MODER##pin##_Msk);\
																(GPIO##port->PUPDR &= ~GPIO_PUPDR_PUPDR##pin##_Msk)
																				
#define GPIO_MODER_ALT_FUNC										(0x2U)			//Jack-fut: Upgrade to GPIO_SET_MODE_ALTFUNC
#define GPIO_MODER_ANALOG										(0x3U)			//Jack-fut: Upgrade to GPIO_SET_MODE_ANALOG

#define GPIO_SET_UP(port, pin)			(GPIO##port->ODR |= GPIO_ODR_##pin)
#define GPIO_SET_DOWN(port, pin)		(GPIO##port->ODR &= ~GPIO_ODR_##pin)

