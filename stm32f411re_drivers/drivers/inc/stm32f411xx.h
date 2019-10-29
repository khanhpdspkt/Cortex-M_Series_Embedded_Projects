/*
 * stm32f411xx.h
 *
 *  Created on: 2019¦~9¤ë24¤é
 *      Author: LinYuChien
 */
// This is MCU specific header file

#ifndef INC_STM32F411XX_H_
#define INC_STM32F411XX_H_

#include <stdint.h>
#define __vo volatile

/*
 * base addresses of Flash and SRAM memories
 */

#define FLASH_BASEADDR       0x08000000U
#define SRAM1_BASEADDR       0x20000000U
#define ROM_BASEADDR         0x1FFF0000U
#define SRAM                 SRAM1_BASEADDR

/*
 * AHBx and APBx Bus Peripheral base addresses
 */

#define PERIPH_BASEADDR      0x40000000U
#define APB1PERIPH_BASEADDR  PERIPH_BASE
#define APB2PERIPH_BASEADDR  0x40010000U
#define AHB1PERIPH_BASEADDR  0x40020000U
#define AHB2PERIPH_BASEADDR  0x50000000U

/*
 * Base address of peripherals which are hanging on AHB1 bus
 */

#define GPIOA_BASEADDR  (AHB1PERIPH_BASEADDR + 0x0000UL)
#define GPIOB_BASEADDR  (AHB1PERIPH_BASEADDR + 0x0400UL)
#define GPIOC_BASEADDR  (AHB1PERIPH_BASEADDR + 0x0800UL)
#define GPIOD_BASEADDR  (AHB1PERIPH_BASEADDR + 0x0C00UL)
#define GPIOE_BASEADDR  (AHB1PERIPH_BASEADDR + 0x1000UL)
#define GPIOH_BASEADDR  (AHB1PERIPH_BASEADDR + 0x1C00UL)
#define RCC_BASEADDR    (AHB1PERIPH_BASEADDR + 0x3800UL)
/*
 * Base address of peripherals which are hanging on APB1 bus
 */

#define I2C1_BASEADDR       (AHB1PERIPH_BASEDDR + 0x5400)
#define I2C2_BASEADDR       (AHB1PERIPH_BASEDDR + 0x5800)
#define I2C3_BASEADDR       (AHB1PERIPH_BASEDDR + 0x5C00)

#define SPI2_BASEADDR       (AHB1PERIPH_BASEDDR + 0x3800)
#define SPI3_BASEADDR       (AHB1PERIPH_BASEDDR + 0x3C00)

#define USART2_BASEADDR     (AHB1PERIPH_BASEDDR + 0x4400)

/*
 * Base address of peripherals which are hanging on APB2 bus
 */

#define USART1_BASEADDR     (APB2PERIPH_BASEDDR + 0x1000)
#define USART6_BASEADDR     (APB2PERIPH_BASEDDR + 0x1400)
#define EXTI_BASEADDR       (APB2PERIPH_BASEDDR + 0x3C00)
#define SYSCFG_BASEADDR     (APB2PERIPH_BASEDDR + 0x3800)
#define SPI1_BASEADDR       (APB2PERIPH_BASEDDR + 0x3000)


/*** peripheral register definition structure ***/

typedef struct
{
  __vo uint32_t MODER;    /* GPIO port mode register                   */
  __vo uint32_t OTYPER;   /* GPIO port output type register            */
  __vo uint32_t OSPEEDR;  /* GPIO port output speed register           */
  __vo uint32_t PUPDR;    /* GPIO port pull-up/pull-down register      */
  __vo uint32_t IDR;      /* GPIO port input data register             */
  __vo uint32_t ODR;      /* GPIO port output data register            */
  __vo uint32_t BSRR;     /* GPIO port bit set/reset register          */
  __vo uint32_t LCKR;     /* GPIO port configuration lock register     */
  __vo uint32_t AFR[2];   /* GPIO alternate function low/high register */
} GPIO_RegDef_t;


typedef struct
{
  __vo uint32_t CR;            /*!< RCC clock control register,                                  Address offset: 0x00 */
  __vo uint32_t PLLCFGR;       /*!< RCC PLL configuration register,                              Address offset: 0x04 */
  __vo uint32_t CFGR;          /*!< RCC clock configuration register,                            Address offset: 0x08 */
  __vo uint32_t CIR;           /*!< RCC clock interrupt register,                                Address offset: 0x0C */
  __vo uint32_t AHB1RSTR;      /*!< RCC AHB1 peripheral reset register,                          Address offset: 0x10 */
  __vo uint32_t AHB2RSTR;      /*!< RCC AHB2 peripheral reset register,                          Address offset: 0x14 */
  __vo uint32_t AHB3RSTR;      /*!< RCC AHB3 peripheral reset register,                          Address offset: 0x18 */
  uint32_t      RESERVED0;     /*!< Reserved, 0x1C                                                                    */
  __vo uint32_t APB1RSTR;      /*!< RCC APB1 peripheral reset register,                          Address offset: 0x20 */
  __vo uint32_t APB2RSTR;      /*!< RCC APB2 peripheral reset register,                          Address offset: 0x24 */
  uint32_t      RESERVED1[2];  /*!< Reserved, 0x28-0x2C                                                               */
  __vo uint32_t AHB1ENR;       /*!< RCC AHB1 peripheral clock register,                          Address offset: 0x30 */
  __vo uint32_t AHB2ENR;       /*!< RCC AHB2 peripheral clock register,                          Address offset: 0x34 */
  __vo uint32_t AHB3ENR;       /*!< RCC AHB3 peripheral clock register,                          Address offset: 0x38 */
  uint32_t      RESERVED2;     /*!< Reserved, 0x3C                                                                    */
  __vo uint32_t APB1ENR;       /*!< RCC APB1 peripheral clock enable register,                   Address offset: 0x40 */
  __vo uint32_t APB2ENR;       /*!< RCC APB2 peripheral clock enable register,                   Address offset: 0x44 */
  uint32_t      RESERVED3[2];  /*!< Reserved, 0x48-0x4C                                                               */
  __vo uint32_t AHB1LPENR;     /*!< RCC AHB1 peripheral clock enable in low power mode register, Address offset: 0x50 */
  __vo uint32_t AHB2LPENR;     /*!< RCC AHB2 peripheral clock enable in low power mode register, Address offset: 0x54 */
  __vo uint32_t AHB3LPENR;     /*!< RCC AHB3 peripheral clock enable in low power mode register, Address offset: 0x58 */
  uint32_t      RESERVED4;     /*!< Reserved, 0x5C                                                                    */
  __vo uint32_t APB1LPENR;     /*!< RCC APB1 peripheral clock enable in low power mode register, Address offset: 0x60 */
  __vo uint32_t APB2LPENR;     /*!< RCC APB2 peripheral clock enable in low power mode register, Address offset: 0x64 */
  uint32_t      RESERVED5[2];  /*!< Reserved, 0x68-0x6C                                                               */
  __vo uint32_t BDCR;          /*!< RCC Backup domain control register,                          Address offset: 0x70 */
  __vo uint32_t CSR;           /*!< RCC clock control & status register,                         Address offset: 0x74 */
  uint32_t      RESERVED6[2];  /*!< Reserved, 0x78-0x7C                                                               */
  __vo uint32_t SSCGR;         /*!< RCC spread spectrum clock generation register,               Address offset: 0x80 */
  __vo uint32_t PLLI2SCFGR;    /*!< RCC PLLI2S configuration register,                           Address offset: 0x84 */
  uint32_t      RESERVED7[1];  /*!< Reserved, 0x88                                                                    */
  __vo uint32_t DCKCFGR;       /*!< RCC Dedicated Clocks configuration register,                 Address offset: 0x8C */
} RCC_RegDef_t;

/*
 * Peripheral definition (Peripheral base addresses typecasted to xxx_RegDef_t)
 */
#define GPIOA      ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB      ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC      ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD      ((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE      ((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOH      ((GPIO_RegDef_t*)GPIOH_BASEADDR)

#define RCC        ((RCC_RegDef_t*)RCC_BASEADDR)

/*
 * Clock Enable Macros for GPIOx peripherals
 */

#define GPIOA_PCLK_EN()   (RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()   (RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()   (RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()   (RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()   (RCC->AHB1ENR |= (1 << 4))
#define GPIOH_PCLK_EN()   (RCC->AHB1ENR |= (1 << 7))


/*
 * Clock Enable Macros for I2Cx peripherals
 */

#define I2C1_PCLK_EN()    (RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()    (RCC->APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN()    (RCC->APB1ENR |= (1 << 23))

/*
 * Clock Enable Macros for SPIx peripherals
 */

#define SPI1_PCLK_EN()    (RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()    (RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()    (RCC->APB1ENR |= (1 << 15))

/*
 * Clock Enable Macros for USARTx peripherals
 */

#define USART1_PCLK_EN()  (RCC->APB2ENR |= (1 << 4))
#define USART2_PCLK_EN()  (RCC->APB1ENR |= (1 << 17))
#define USART6_PCLK_EN()  (RCC->APB2ENR |= (1 << 5))

/*
 * Clock Disable Macros for GPIOx peripherals
 */

#define GPIOA_PCLK_DN()   (RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DN()   (RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DN()   (RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DN()   (RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DN()   (RCC->AHB1ENR &= ~(1 << 4))
#define GPIOH_PCLK_DN()   (RCC->AHB1ENR &= ~(1 << 7))

/*
 * Clock Disable Macros for I2Cx peripherals
 */

#define I2C1_PCLK_DN()    (RCC->APB1ENR &= ~(1 << 21))
#define I2C2_PCLK_DN()    (RCC->APB1ENR &= ~(1 << 22))
#define I2C3_PCLK_DN()    (RCC->APB1ENR &= ~(1 << 23))

/*
 * Clock Disable Macros for SPIx peripherals
 */

#define SPI1_PCLK_DN()    (RCC->APB2ENR &= ~(1 << 12))
#define SPI2_PCLK_DN()    (RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DN()    (RCC->APB1ENR &= ~(1 << 15))

/*
 * Clock Disable Macros for USARTx peripherals
 */

#define USART1_PCLK_DN()  (RCC->APB2ENR &= ~(1 << 4))
#define USART2_PCLK_DN()  (RCC->APB1ENR &= ~(1 << 17))
#define USART6_PCLK_DN()  (RCC->APB2ENR &= ~(1 << 5))

/*
 * Macros to reset GPIOx peripheral
 */

#define GPIOA_REG_RESET()     do{ (RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &= !(1 << 0)); } while(0)
#define GPIOB_REG_RESET()     do{ (RCC->AHB1RSTR |= (1 << 1)); (RCC->AHB1RSTR &= !(1 << 1)); } while(0)
#define GPIOC_REG_RESET()     do{ (RCC->AHB1RSTR |= (1 << 2)); (RCC->AHB1RSTR &= !(1 << 2)); } while(0)
#define GPIOD_REG_RESET()     do{ (RCC->AHB1RSTR |= (1 << 3)); (RCC->AHB1RSTR &= !(1 << 3)); } while(0)
#define GPIOE_REG_RESET()     do{ (RCC->AHB1RSTR |= (1 << 4)); (RCC->AHB1RSTR &= !(1 << 4)); } while(0)
#define GPIOH_REG_RESET()     do{ (RCC->AHB1RSTR |= (1 << 7)); (RCC->AHB1RSTR &= !(1 << 7)); } while(0)

//
// some generic macros
//

#define ENABLE          1
#define DISABLE         0
#define SET             ENABLE
#define RESET           DISABLE
#define GPIO_PIN_SET    SET
#define GPIO_PIN_RESET  RESET


//
#include "stm32f411xx_gpio_driver.h"

#endif /* INC_STM32F411XX_H_ */

