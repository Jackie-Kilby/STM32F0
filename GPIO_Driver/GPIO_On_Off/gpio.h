#include <stm32f0xx.h>
#include <stdint.h>

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


void gpio_init(char port, uint8_t pin, uint8_t io_put);
void gpio_set_up(char port, uint8_t pin);
void gpio_set_down(char port, uint8_t pin);
