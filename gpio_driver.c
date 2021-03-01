#include "gpio_driver.h"

void GPIO_PeriClockControl(Gpio_RegDef_t *pGPIOx,uint8_t EnorDi) //EnorDi- Enable or disable
{
	if(EnorDi==ENABLE)
	{
		if(pGPIOx == GPIOA)
			{
				GPIOA_PCLK_EN();
			}
		else if(pGPIOx == GPIOB)
			{
				GPIOB_PCLK_EN();
			}
		else if(pGPIOx == GPIOC)
			{
				GPIOC_PCLK_EN();
			}
		else if(pGPIOx == GPIOD)
			{
				GPIOD_PCLK_EN();
			}
		else if(pGPIOx == GPIOE)
			{
				GPIOE_PCLK_EN();
			}
	}
  else
	{
		if(pGPIOx == GPIOA)
			{
				GPIOA_PCLK_DIS();
			}
		else if(pGPIOx == GPIOB)
			{
				GPIOB_PCLK_DIS();
			}
		else if(pGPIOx == GPIOC)
			{
				GPIOC_PCLK_DIS();
			}
		else if(pGPIOx == GPIOD)
			{
				GPIOD_PCLK_DIS();
			}
		else if(pGPIOx == GPIOE)
			{
				GPIOE_PCLK_DIS();
			}
	}
}

//Initialization of GPIOx registers

void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	//1. Configuration of the MODE of GPIOx

	uint32_t temp=0;

	temp=(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode<< (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->MODER&=~(0x3<<(2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));  //~(0x3) = ~(11) -> 00  : resetting the value.
	pGPIOHandle->pGPIOx->MODER|=temp;  //set the value

	//2. Configuration of the speed

	temp= ((pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed<<2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR&=~(0x3<<(2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR|=temp;

	//3. Configuration of the GPIO port pull-up/pull-down register

	temp=(pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl<<(2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR&=~(0x3<<(2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR|=temp;

	//4.Configuration of the GPIO port output type register

	temp=(pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType<<(pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OTYPER&=~(0x1<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER|=temp;

	//5. Configuration of the GPIO alternate function low register

	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode== GPIO_MODE_ALTFN)
	{
	uint8_t temp1,temp2;
	temp1= pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber/8;
	temp2= pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber%8;
	pGPIOHandle->pGPIOx->AFR[temp1] &=~(0xf<<(4*temp2));
	pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFuncMode<<(4*temp2));
	}
}

//De-initialization of GPIOx


void GPIO_DeInit(Gpio_RegDef_t *pGPIOx)
{

	if(pGPIOx == GPIOA)
	{
		GPIOA_REG_RESET();
	}
	if(pGPIOx == GPIOB)
	{
		GPIOB_REG_RESET();
	}
	if(pGPIOx == GPIOC)
	{
		GPIOC_REG_RESET();
	}
	if(pGPIOx == GPIOD)
	{
		GPIOD_REG_RESET();
	}
	if(pGPIOx == GPIOE)
	{
		GPIOE_REG_RESET();
	}
}

//Function to read from Input Pin

uint8_t GPIO_ReadFromInputPin(Gpio_RegDef_t *pGPIOx,uint8_t PinNumber)
{
    uint8_t value;
    value = ( uint8_t)((pGPIOx->IDR>>PinNumber)& 0x0000001); //masking technique
    return value;
}

//Function to read from Input Port

uint16_t GPIO_ReadFromInputPort(Gpio_RegDef_t *pGPIOx)
{
	uint16_t value;
	value = pGPIOx->IDR;
	return value;
}

//Function to write to output Pin

void GPIO_WriteToOutputPin(Gpio_RegDef_t *pGPIOx,uint8_t PinNumber, uint8_t value)
{
  if(value == GPIO_PIN_SET)
  {
	  pGPIOx ->ODR |= (1<<PinNumber);
  }
  else
  {
	  pGPIOx ->ODR &= ~(1<<PinNumber);
  }
}

//Function to write to output Pin

void GPIO_WriteToOutputPort(Gpio_RegDef_t *pGPIOx,uint16_t value)
{
	pGPIOx->ODR = value;
}

//Function to toggle output Pin

void GPIO_ToggleOutputPin(Gpio_RegDef_t *pGPIOx,uint8_t PinNumber)
{
	pGPIOx->ODR^=(1<<PinNumber);
}
