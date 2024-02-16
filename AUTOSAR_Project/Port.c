 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Mohamed Tarek
 ******************************************************************************/

#include "Port.h"
#include "tm4c123gh6pm_registers.h"
#include "Port_Regs.h"
#include "Det.h"
/************************************************************************************
* Service Name: Port_Init
* Sync/Async: Synchronous
* Reentrancy: non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the Port Driver module.
************************************************************************************/
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED    ;
STATIC const  Port_ConfigType_Pin * PortConf = NULL_PTR;

void Port_Init(const Port_ConfigType * ConfigPtr )
{
	      volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */

      const Port_ConfigType_Pin * pins =ConfigPtr->pins ;
uint8 i =0 ;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    if(ConfigPtr==NULL_PTR){
       Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_Init_SID, PORT_E_PARAM_CONFIG_ID);
   }else
#endif
   
      Port_Status = PORT_INITIALIZED;


      PortConf = ConfigPtr->pins;

      for(;i<Port_Number_Of_Port_Pins;i++){

      switch(pins[i].port_num)
      {
          case  PORT_A: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                   break;
          case  PORT_B: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                   break;
          case  PORT_C: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                   break;
          case  PORT_D: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                   break;
          case  PORT_E: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                   break;
          case  PORT_F: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                   break;
      }

      if( ((pins[i].port_num == 3) && (pins[i].pin_num == 7)) || ((pins[i].port_num == 5) && (pins[i].pin_num == 0)) ) /* PD7 or PF0 */
      {

          *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */

          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , pins[i].pin_num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
      }
      else if( (pins[i].port_num == 2) && (pins[i].pin_num <= 3) ) /* PC0 to PC3 */
      {
          /* Do Nothing ...  this is the JTAG pins */
      }
      else
      {
          /* Do Nothing ... No need to unlock the commit register for this pin */
      }

      if(pins[i].direction == PORT_PIN_OUT)
      {
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , pins[i].pin_num);               /* Set the corresponding bit in the GPIODIR register to configure it as output pin */


          if(pins[i].pin_level_init_value == STD_HIGH)

          {

              SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , pins[i].pin_num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */

          }

          else

          {

              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , pins[i].pin_num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */

          }
      }
      else if(pins[i].direction == PORT_PIN_IN)
      {

          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , pins[i].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */


          if(pins[i].resistor == PULL_UP)

          {

              SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , pins[i].pin_num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */

          }

          else if(pins[i].resistor == PULL_DOWN)

          {

              SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , pins[i].pin_num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */

          }

          else

          {

              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , pins[i].pin_num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */

              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , pins[i].pin_num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */

          }
      }
      else
      {
          /* Do Nothing */
      }

      if(pins[i].pin_mode==PORT_PIN_MODE_DIO){


          /* Setup the pin mode as GPIO */

      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , pins[i].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */

      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , pins[i].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */

      *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (pins[i].pin_num * 4));     /* Clear the PMCx bits for this pin */

      SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , pins[i].pin_num);/* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */


      }else if (pins[i].pin_mode==PORT_PIN_MODE_CAN){



          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , pins[i].pin_num);/* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */

          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , pins[i].pin_num);/* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */

          if(i==38 ||i==41)/*PF0,PF3*/

          {

              *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000003 << (PortConf[i].pin_num * 4));

            }

          else

            {

                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000008 << (PortConf[i].pin_num * 4));

            }

          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , pins[i].pin_num);/* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */



      }else if(PortConf[i].pin_mode==PORT_PIN_MODE_PWM){


          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , pins[i].pin_num);/* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */

          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , pins[i].pin_num);/* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */


          if(i>=12 &&i<=17)

          {

              *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000004 << (PortConf[i].pin_num * 4));

              }

          else

              {

                  *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000005 << (PortConf[i].pin_num * 4));

              }

          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , pins[i].pin_num);/* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */


      }else if(PortConf[i].pin_mode == PORT_PIN_MODE_UART){


          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , pins[i].pin_num);/* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */

          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , pins[i].pin_num);/* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */

          *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000001 << (PortConf[i].pin_num * 4));/* Set the PMCx bits for this pin to support uart */

          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , pins[i].pin_num);/* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */




      }else if(PortConf[i].pin_mode == PORT_PIN_MODE_SSI){


          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , pins[i].pin_num);/* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */

          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , pins[i].pin_num);/* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */

          *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000002 << (PortConf[i].pin_num * 4));

          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , pins[i].pin_num);/* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */



      }else if(PortConf[i].pin_mode == PORT_PIN_MODE_USB){


          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , pins[i].pin_num);/* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */

          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , pins[i].pin_num);/* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */

          *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000008<< (PortConf[i].pin_num * 4));

          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , pins[i].pin_num);/* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */


      }else if (PortConf[i].pin_mode == PORT_PIN_MODE_I2C){

          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortConf[i].pin_num);

          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortConf[i].pin_num);

          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OPEN_DRAIN) , PortConf[i].pin_num);

          *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000003 << (PortConf[i].pin_num * 4));


      }else if(PortConf[i].pin_mode==PORT_PIN_MODE_GPT)
          {

          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortConf[i].pin_num);               /* ENable Alternative function for this pin*/

          *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000007<< (PortConf[i].pin_num * 4));

          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortConf[i].pin_num);

          }
    }

   

    }





/************************************************************************************
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin- Port Pin ID number
*                  Direction - Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction
************************************************************************************/
#if (PORT_PIN_DIRECTION_CHANGEABLE==STD_ON)

void Port_SetPinDirection(
 Port_PinType Pin,
 Port_PinDirection Direction
){

#if (PORT_DEV_ERROR_DETECT == STD_ON)
    if (Port_Status == PORT_NOT_INITIALIZED)
        {
            Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SetPinDirection_SID,
                            PORT_E_UNINIT_ID);
        }
    else if(Pin>=43  ){

        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_API, PORT_E_PARAM_CONFIG_ID);

    }else if(PortConf[Pin].pin_direction_changeable == STD_OFF){

       Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SetPinDirection_SID,
                        PORT_E_DIRECTION_UNCHANGEABLE_ID);
    }else
#endif
    {   volatile uint32 * PortGpio_Ptr = NULL_PTR;
        switch(PortConf[Pin].port_num)
            {
            case  PORT_A: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                 break;
            case  PORT_B: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                 break;
            case  PORT_C: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                 break;
            case  PORT_D: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                 break;
            case  PORT_E: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                 break;
            case  PORT_F: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                 break;
            }
        if(Direction == PORT_PIN_IN){

            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PortConf[Pin].pin_num);

        }else if(Direction == PORT_PIN_OUT){

            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PortConf[Pin].pin_num);

        }

}


}
#endif

#if ( PORT_SET_PIN_MODE_API==STD_ON)
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode ){

#if (PORT_DEV_ERROR_DETECT == STD_ON)

    if( Port_Status== PORT_NOT_INITIALIZED ){

        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_SetPinMode_SID, PORT_E_UNINIT_ID);

    }else if (Pin >=43){

        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_SetPinMode_SID, PORT_E_PARAM_CONFIG_ID);

    }else if (PORT_E_MODE_UNCHANGEABLE_ID==STD_OFF){

        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_SetPinMode_SID, PORT_E_MODE_UNCHANGEABLE_ID);

    }else if ( Mode >13){

        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_SetPinMode_SID, PORT_E_PARAM_INVALID_MODE_ID);

    }else

#endif
    {

        const Port_ConfigType_Pin * pins =PortConf ;

        volatile uint32 * PortGpio_Ptr = NULL_PTR;
        switch(PortConf[Pin].port_num)
            {
            case  PORT_A: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                 break;
            case  PORT_B: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                 break;
            case  PORT_C: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                 break;
            case  PORT_D: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                 break;
            case  PORT_E: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                 break;
            case  PORT_F: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                 break;
            }


        if(Mode==PORT_PIN_MODE_DIO){


                  /* Setup the pin mode as GPIO */
              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , pins[Pin].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */

              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , pins[Pin].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */

              *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (pins[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin */

              SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , pins[Pin].pin_num);/* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */


              }else if (Mode==PORT_PIN_MODE_CAN){



                  CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , pins[Pin].pin_num);/* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */

                  SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , pins[Pin].pin_num);/* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */

                  if(Pin==38 ||Pin==41)/*PF0,PF3*/
                    {
                      *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000003 << (PortConf[Pin].pin_num * 4));
                    }

                  else
                    {
                     *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000008 << (PortConf[Pin].pin_num * 4));
                    }

                  SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , pins[Pin].pin_num);/* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */



              }else if(Mode==PORT_PIN_MODE_PWM){


                  CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , pins[Pin].pin_num);/* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */

                  SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , pins[Pin].pin_num);/* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */

                  if(Pin>=12 &&Pin<=17)
                      {
                        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000004 << (PortConf[Pin].pin_num * 4));
                      }
                      else
                      {
                       *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000005 << (PortConf[Pin].pin_num * 4));
                      }

                  SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , pins[Pin].pin_num);/* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */


              }else if(Mode == PORT_PIN_MODE_UART){


                  CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , pins[Pin].pin_num);/* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */

                  SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , pins[Pin].pin_num);/* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */

                  *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000001 << (PortConf[Pin].pin_num * 4));/* Set the PMCx bits for this pin to support uart */

                  SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , pins[Pin].pin_num);/* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */




              }else if(Mode == PORT_PIN_MODE_SSI){


                  CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , pins[Pin].pin_num);/* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */

                  SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , pins[Pin].pin_num);/* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */

                  *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000002 << (PortConf[Pin].pin_num * 4));

                  SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , pins[Pin].pin_num);/* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */



              }else if(Mode == PORT_PIN_MODE_USB){


                  CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , pins[Pin].pin_num);/* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */

                  SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , pins[Pin].pin_num);/* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */

                  *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000008<< (PortConf[Pin].pin_num * 4));

                  SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , pins[Pin].pin_num);/* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */


              }else if (Mode == PORT_PIN_MODE_I2C){

                  SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortConf[Pin].pin_num);

                  SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortConf[Pin].pin_num);

                  SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OPEN_DRAIN) , PortConf[Pin].pin_num);


                  *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000003 << (PortConf[Pin].pin_num * 4));



              }else if(Mode==PORT_PIN_MODE_GPT)
                  {
                     SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortConf[Pin].pin_num);               /* ENable Alternative function for this pin*/
                    *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000007<< (PortConf[Pin].pin_num * 4));
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortConf[Pin].pin_num);
                  }





    }
}
#endif



//typedef struct
//{
//  uint16  vendorID;
//  uint16  moduleID;
//  uint8 sw_major_version;
//  uint8 sw_minor_version;
//  uint8 sw_patch_version;
//} Std_VersionInfoType;
//

#if (PORT_VERSION_INFO_API==STD_ON)
void Port_GetVersionInfo(
 Std_VersionInfoType* versioninfo
) {
#if (PORT_DEV_ERROR_DETECT == STD_ON)
if( Port_Status== PORT_NOT_INITIALIZED )

    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_GetVersionInfo_SID, PORT_E_UNINIT_ID);

else if (NULL_PTR==versioninfo)
    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_GetVersionInfo_SID, PORT_E_PARAM_CONFIG_ID);
else
#endif
{
    versioninfo->sw_major_version = STD_TYPES_SW_MAJOR_VERSION ;

    versioninfo->sw_minor_version = STD_TYPES_SW_MINOR_VERSION ;

    versioninfo->sw_patch_version = STD_TYPES_SW_PATCH_VERSION ;

    versioninfo->moduleID         = PORT_MODULE_ID             ;

    versioninfo->vendorID         = PORT_VENDOR_ID             ;

}
}
#endif


void Port_RefreshPortDirection(
        void
        )
{
  #if (PORT_DEV_ERROR_DETECT == STD_ON)
  /* check if the Port driver is initialized*/
    if (Port_Status == PORT_NOT_INITIALIZED)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_RefreshPortDirection_SID,
                        PORT_E_UNINIT_ID);

    }
    else
#endif
    {

        volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
        uint8 Pin_Index;              /* index to configure each pin (43)*/
            for (Pin_Index = 0; Pin_Index < 43 ; Pin_Index++)
            {
              if(PortConf[Pin_Index].pin_direction_changeable == STD_OFF)     /*Check that if POrt pin is UNchangable in RunTime*/
              {

            switch(PortConf[Pin_Index].port_num)
           {
               case  PORT_A: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                break;
               case  PORT_B: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                break;
               case  PORT_C: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                break;
               case  PORT_D: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                break;
               case  PORT_E: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                break;
               case  PORT_F: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                break;

           }


                                  /*Read Pin Direction */
           if(BIT_IS_SET(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PortConf[Pin_Index].pin_num))
           {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PortConf[Pin_Index].pin_num);
           }
          else
            if(BIT_IS_CLEAR(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PortConf[Pin_Index].pin_num))
           {
           CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PortConf[Pin_Index].pin_num);
           }
           else {/* No Action Required */}

              }

              else if(PortConf[Pin_Index].pin_direction_changeable == STD_ON)
                {
                  /* shall exclude those port
                  pins from refreshing that are configured as
                  ‘pin direction changeable during runtime*/
                  continue;
                }

            }

    }
}








