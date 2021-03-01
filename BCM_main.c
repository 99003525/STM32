/*
 * BCM_main.c
 *
 *  Created on: Feb 24, 2021
 *      Author: Training
 */


#include "BCM_main.h"

#define BTN_PRESSED SET
void delay(void)
{
	for (uint32_t i=0;i<500000;i++);
}

int main(void)
{
   GPIO_Handle_t Gpioled1,Gpioled2,Gpioled3,Gpioled4,GpioBTN,GpioBTN2;


/*
 *
 * for GREEN led
 *
 */


   Gpioled1.pGPIOx = GPIOD;
   Gpioled1.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
   Gpioled1.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
   Gpioled1.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
   Gpioled1.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PD;
   Gpioled1.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;

   GPIO_PeriClockControl(GPIOD,ENABLE);
   GPIO_Init(&Gpioled1);

   /*
    *
    * for RED led
    *
    */

   Gpioled2.pGPIOx = GPIOD;
   Gpioled2.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
   Gpioled2.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
   Gpioled2.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
   Gpioled2.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PD;
   Gpioled2.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;

   GPIO_PeriClockControl(GPIOD,ENABLE);
   GPIO_Init(&Gpioled2);

   /*
    *
    * for BLUE led
    *
    */

   Gpioled3.pGPIOx = GPIOD;
   Gpioled3.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
   Gpioled3.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
   Gpioled3.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
   Gpioled3.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PD;
   Gpioled3.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;

   GPIO_PeriClockControl(GPIOD,ENABLE);
   GPIO_Init(&Gpioled3);

   /*
    *
    * for ORANGE led
    *
    */

   Gpioled4.pGPIOx = GPIOD;
   Gpioled4.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
   Gpioled4.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
   Gpioled4.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
   Gpioled4.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PD;
   Gpioled4.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;

   GPIO_PeriClockControl(GPIOD,ENABLE);
   GPIO_Init(&Gpioled4);

	/*
	 * for internal switch
	 *
	 */
   GpioBTN.pGPIOx = GPIOA;
   GpioBTN.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
   GpioBTN.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
   GpioBTN.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
   GpioBTN.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PD;

   GPIO_PeriClockControl(GPIOA,ENABLE);
   GPIO_Init(&GpioBTN);

   /*
    * for EXternal switch
    *
    */

   GpioBTN2.pGPIOx = GPIOC;
   GpioBTN2.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
   GpioBTN2.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
   GpioBTN2.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
   GpioBTN2 .GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PD;


   GPIO_PeriClockControl(GPIOC,ENABLE);
   GPIO_Init(&GpioBTN2);

   /*
    * PORTABLE KEY FUNCTIONALITY
    *
    */

   while(1)
      {
      	if(GPIO_ReadFromInputPin(GPIOA,GPIO_PIN_NO_0)==BTN_PRESSED)
      	  {
      		   GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_12, 1);
      		   GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_13, 1);
      		   GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_14, 1);
      		   GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_15, 1);
      		   delay();
      	   }

      	   else if(GPIO_ReadFromInputPin(GPIOC,GPIO_PIN_NO_0)==(BTN_PRESSED))
      	   {
      		   // When the external button gets pressed , all the four doors gets locked.
      	   }
      	   else
      	   {
      		   GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_12, 0);
      		   GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_13, 0);
      		   GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_14, 0);
      		   GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_15, 0);
      	   }
         }

	return 0;
}
