/*
 * stm32f411xx_gpio_driver.c
 *
 *  Created on: 2019¦~9¤ë25¤é
 *      Author: LinYuChien
 */


/*************************************************************************
 * @fn         -
 *
 * @brief      -
 *
 * @param[in]  -
 * @param[in]  -
 *
 * @return     -
 *
 * @Note       -
 */

#include "stm32f411xx_gpio_driver.h"


/*******************************************************
 * APIs supported by this driver
 * For more information about the APIs check the function definition
 ******************************************************/

/*************************************************************************
 * @fn         - GPIO_PeriClockControl
 *
 * @brief      - This function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]  - base address of the GPIO peripheral
 * @param[in]  - ENABLE or DISABLE macro
 *
 * @return     - none
 *
 * @Note       - none
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t En_or_Di) {
	if(En_or_Di == ENABLE) {
		if(pGPIOx == GPIOA) {
			GPIOA_PCLK_EN();
		}
		else if (pGPIOx == GPIOB) {
			GPIOB_PCLK_EN();
		}
		else if (pGPIOx == GPIOC) {
			GPIOC_PCLK_EN();
		}
		else if (pGPIOx == GPIOD) {
			GPIOD_PCLK_EN();
		}
		else if (pGPIOx == GPIOE) {
			GPIOE_PCLK_EN();
		}
		else if (pGPIOx == GPIOH) {
			GPIOH_PCLK_EN();
		}
	} else {
		if(pGPIOx == GPIOA) {
			GPIOA_PCLK_DN();
		}
		else if (pGPIOx == GPIOB) {
			GPIOB_PCLK_DN();
		}
		else if (pGPIOx == GPIOC) {
			GPIOC_PCLK_DN();
		}
		else if (pGPIOx == GPIOD) {
			GPIOD_PCLK_DN();
		}
		else if (pGPIOx == GPIOE) {
			GPIOE_PCLK_DN();
		}
		else if (pGPIOx == GPIOH) {
			GPIOH_PCLK_DN();
		}
	}
}

/*************************************************************************
 * @fn         - GPIO_Init
 *
 * @brief      -
 *
 * @param[in]  -
 *
 * @return     -
 *
 * @Note       -
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle) {

	uint32_t temp = 0;

	// 1. configure the mode of gpio pin
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG) {
		// the non interrupt mode
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER &= ~( 0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ); // clearning
		pGPIOHandle->pGPIOx->MODER |= temp;	// setting
	} else {
		// the interrupt mode
	}

	temp = 0;

	// 2. configure the speed
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR &= ~( 0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ); // clearning
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;

	temp = 0;

	// 3. configure the pull-up/pull-down settings
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR &= ~( 0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ); // clearning
	pGPIOHandle->pGPIOx->PUPDR |= temp;

	temp = 0;

	// 4. configure the optype
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OTYPER &= ~( 0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ); // clearning
	pGPIOHandle->pGPIOx->OTYPER |= temp;

	temp = 0;

	// 5. configure the alt functionality
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN) {
		// configure the alt function
		uint32_t temp1, temp2;
		temp1  = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2)); // clearing
		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2));
	}
}

/*************************************************************************
 * @fn         - GPIO_DeInit
 *
 * @brief      -
 *
 * @param[in]  -
 *
 * @return     -
 *
 * @Note       -
 */

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx) {
	if(pGPIOx == GPIOA) {
		GPIOA_REG_RESET();
	}
	else if (pGPIOx == GPIOB) {
		GPIOB_REG_RESET();
	}
	else if (pGPIOx == GPIOC) {
		GPIOC_REG_RESET();
	}
	else if (pGPIOx == GPIOD) {
		GPIOD_REG_RESET();
	}
	else if (pGPIOx == GPIOE) {
		GPIOE_REG_RESET();
	}
	else if (pGPIOx == GPIOH) {
		GPIOH_REG_RESET();
	}
}

/*************************************************************************
 * @fn         - GPIO_ReadFromInputPin
 *
 * @brief      -
 *
 * @param[in]  -
 * @param[in]  -
 *
 * @return     - 0 or 1
 *
 * @Note       -
 */

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber) {

	uint8_t value;
	value = (pGPIOx->IDR >> PinNumber) & 0x000000001;

	return value;

}

/*************************************************************************
 * @fn         - GPIO_ReadFromInputPort
 *
 * @brief      -
 *
 * @param[in]  -
 * @param[in]  -
 *
 * @return     -
 *
 * @Note       -
 */

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx) {

	return (uint16_t)pGPIOx->IDR;

}

/*************************************************************************
 * @fn         - GPIO_WriteToOutputPin
 *
 * @brief      -
 *
 * @param[in]  -
 * @param[in]  -
 *
 * @return     -
 *
 * @Note       -
 */

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value) {

	if(Value == GPIO_PIN_SET) {
		pGPIOx->ODR |= (1 << PinNumber);
	} else {
		pGPIOx->ODR &= ~(1 << PinNumber);
	}

}

/*************************************************************************
 * @fn         - GPIO_WriteToOutputPort
 *
 * @brief      -
 *
 * @param[in]  -
 * @param[in]  -
 *
 * @return     -
 *
 * @Note       -
 */

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint8_t Value) {

	pGPIOx->ODR = Value;

}

/*************************************************************************
 * @fn         - GPIO_ToggleOutputPin
 *
 * @brief      -
 *
 * @param[in]  -
 * @param[in]  -
 *
 * @return     -
 *
 * @Note       -
 */

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber) {

	pGPIOx->ODR ^= (1 << PinNumber);

}

/*************************************************************************
 * @fn         - GPIO_IRQConfig
 *
 * @brief      -
 *
 * @param[in]  -
 * @param[in]  -
 *
 * @return     -
 *
 * @Note       -
 */

void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t En_or_Di);

/*************************************************************************
 * @fn         - GPIO_IRQHandling
 *
 * @brief      -
 *
 * @param[in]  -
 * @param[in]  -
 *
 * @return     -
 *
 * @Note       -
 */

void GPIO_IRQHandling(uint8_t PinNumber);
