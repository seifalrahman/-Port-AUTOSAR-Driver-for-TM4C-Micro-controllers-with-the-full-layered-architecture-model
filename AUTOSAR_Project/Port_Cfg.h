/*
 * Port_Cfg.h
 *
 *  Created on: Feb 9, 2024
 *      Author: seif alrahman
 */

#ifndef PORT_CFG_H_
#define PORT_CFG_H_


/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

#define Port_Number_Of_Port_Pins (43U)
/*Switches the Development Error Detection and Notification on or off. true: Enabled. false: Disabled. */
#define PORT_DEV_ERROR_DETECT STD_ON
/*Pre-processor switch to enable / disable the use of the function Port_SetPinDirection().
 *TRUE: Enabled - Function Port_SetPinDirection() is available.
 *FALSE: Disabled - Function Port_SetPinDirection() is not available. */
#define PORT_SET_PIN_DIRECTION_API STD_ON
/*Pre-processor switch to enable / disable the use of the function Port_SetPinMode().
 * true: Enabled - Function Port_SetPinMode() is available.
 * false: Disabled - Function Port_SetPinMode() is not available. */
#define PORT_SET_PIN_MODE_API STD_ON
/*Pre-processor switch to enable / disable the API to read out the modules version information.
 * true: Version info API enabled.
 * false: Version info API disabled. */
#define PORT_VERSION_INFO_API  STD_ON
/*The initial direction of the pin (IN or OUT). If the direction is not changeable,
the value configured here is fixed. The direction must match the pin mode.
E.g. a pin used for an ADC must be configured to be an in port. */
#define PORT_PIN_DIRECTION PORT_PIN_IN
/*Parameter to indicate if the direction is changeable on a port pin during runtime.
 * true: Port Pin direction changeable enabled.
 * false: Port Pin direction changeable disabled. */
#define PORT_PIN_DIRECTION_CHANGEABLE STD_ON
/*Parameter to indicate if the mode is changeable on a port pin during runtime.
 * True: Port Pin mode changeable allowed.
 * False: Port Pin mode changeable not permitted.*/
#define PORT_PIN_MODE_CHANGEABLE     STD_ON


#define PORT_PIN_MODE_ADC       (Port_PinModeType)0
#define PORT_PIN_MODE_CAN       (Port_PinModeType)1
#define PORT_PIN_MODE_DIO       (Port_PinModeType)2
#define PORT_PIN_MODE_I2C       (Port_PinModeType)3
#define PORT_PIN_MODE_DIO_WDG   (Port_PinModeType)4
#define PORT_PIN_MODE_FLEXRAY   (Port_PinModeType)5
#define PORT_PIN_MODE_ICU       (Port_PinModeType)6
#define PORT_PIN_MODE_LIN       (Port_PinModeType)7
#define PORT_PIN_MODE_MEM       (Port_PinModeType)8
#define PORT_PIN_MODE_PWM       (Port_PinModeType)9
#define PORT_PIN_MODE_GPT       (Port_PinModeType)10
#define PORT_PIN_MODE_UART      (Port_PinModeType)11
#define PORT_PIN_MODE_SSI       (Port_PinModeType)12
#define PORT_PIN_MODE_USB       (Port_PinModeType)13

#define PORT_PIN_INITIAL_MODE   PORT_PIN_MODE_DIO



#define PORT_A     ((uint8)0)
#define PORT_B     ((uint8)1)
#define PORT_C     ((uint8)2)
#define PORT_D     ((uint8)3)
#define PORT_E     ((uint8)4)
#define PORT_F     ((uint8)5)

#define PORT_PIN0               (Port_PinType)0
#define PORT_PIN1               (Port_PinType)1
#define PORT_PIN2               (Port_PinType)2
#define PORT_PIN3               (Port_PinType)3
#define PORT_PIN4               (Port_PinType)4
#define PORT_PIN5               (Port_PinType)5
#define PORT_PIN6               (Port_PinType)6
#define PORT_PIN7               (Port_PinType)7

#define PORT_A_PIN_0    (Port_PinType)0
#define PORT_A_PIN_1    (Port_PinType)1
#define PORT_A_PIN_2    (Port_PinType)2
#define PORT_A_PIN_3    (Port_PinType)3
#define PORT_A_PIN_4    (Port_PinType)4
#define PORT_A_PIN_5    (Port_PinType)5
#define PORT_A_PIN_6    (Port_PinType)6
#define PORT_A_PIN_7    (Port_PinType)7

#define PORT_B_PIN_0    (Port_PinType)8
#define PORT_B_PIN_1    (Port_PinType)9
#define PORT_B_PIN_2    (Port_PinType)10
#define PORT_B_PIN_3    (Port_PinType)11
#define PORT_B_PIN_4    (Port_PinType)12
#define PORT_B_PIN_5    (Port_PinType)13
#define PORT_B_PIN_6    (Port_PinType)14
#define PORT_B_PIN_7    (Port_PinType)15

#define PORT_C_PIN_0    (Port_PinType)16
#define PORT_C_PIN_1    (Port_PinType)17
#define PORT_C_PIN_2    (Port_PinType)18
#define PORT_C_PIN_3    (Port_PinType)19
#define PORT_C_PIN_4    (Port_PinType)20
#define PORT_C_PIN_5    (Port_PinType)21
#define PORT_C_PIN_6    (Port_PinType)22
#define PORT_C_PIN_7    (Port_PinType)23

#define PORT_D_PIN_0    (Port_PinType)24
#define PORT_D_PIN_1    (Port_PinType)25
#define PORT_D_PIN_2    (Port_PinType)26
#define PORT_D_PIN_3    (Port_PinType)27
#define PORT_D_PIN_4    (Port_PinType)28
#define PORT_D_PIN_5    (Port_PinType)29
#define PORT_D_PIN_6    (Port_PinType)30
#define PORT_D_PIN_7    (Port_PinType)31

#define PORT_E_PIN_0    (Port_PinType)32
#define PORT_E_PIN_1    (Port_PinType)33
#define PORT_E_PIN_2    (Port_PinType)34
#define PORT_E_PIN_3    (Port_PinType)35
#define PORT_E_PIN_4    (Port_PinType)36
#define PORT_E_PIN_5    (Port_PinType)37

#define PORT_F_PIN_0    (Port_PinType)38
#define PORT_F_PIN_1    (Port_PinType)39
#define PORT_F_PIN_2    (Port_PinType)40
#define PORT_F_PIN_3    (Port_PinType)41
#define PORT_F_PIN_4    (Port_PinType)42


//*************************************************************************************//

#define PORT_A_PIN_0_DIRECTION    PORT_PIN_DIRECTION
#define PORT_A_PIN_1_DIRECTION    PORT_PIN_DIRECTION
#define PORT_A_PIN_2_DIRECTION    PORT_PIN_DIRECTION
#define PORT_A_PIN_3_DIRECTION    PORT_PIN_DIRECTION
#define PORT_A_PIN_4_DIRECTION    PORT_PIN_DIRECTION
#define PORT_A_PIN_5_DIRECTION    PORT_PIN_DIRECTION
#define PORT_A_PIN_6_DIRECTION    PORT_PIN_DIRECTION
#define PORT_A_PIN_7_DIRECTION    PORT_PIN_DIRECTION

#define PORT_B_PIN_0_DIRECTION    PORT_PIN_DIRECTION
#define PORT_B_PIN_1_DIRECTION    PORT_PIN_DIRECTION
#define PORT_B_PIN_2_DIRECTION    PORT_PIN_DIRECTION
#define PORT_B_PIN_3_DIRECTION    PORT_PIN_DIRECTION
#define PORT_B_PIN_4_DIRECTION    PORT_PIN_DIRECTION
#define PORT_B_PIN_5_DIRECTION    PORT_PIN_DIRECTION
#define PORT_B_PIN_6_DIRECTION    PORT_PIN_DIRECTION
#define PORT_B_PIN_7_DIRECTION    PORT_PIN_DIRECTION

#define PORT_C_PIN_0_DIRECTION    PORT_PIN_DIRECTION
#define PORT_C_PIN_1_DIRECTION    PORT_PIN_DIRECTION
#define PORT_C_PIN_2_DIRECTION    PORT_PIN_DIRECTION
#define PORT_C_PIN_3_DIRECTION    PORT_PIN_DIRECTION
#define PORT_C_PIN_4_DIRECTION    PORT_PIN_DIRECTION
#define PORT_C_PIN_5_DIRECTION    PORT_PIN_DIRECTION
#define PORT_C_PIN_6_DIRECTION    PORT_PIN_DIRECTION
#define PORT_C_PIN_7_DIRECTION    PORT_PIN_DIRECTION

#define PORT_D_PIN_0_DIRECTION    PORT_PIN_DIRECTION
#define PORT_D_PIN_1_DIRECTION    PORT_PIN_DIRECTION
#define PORT_D_PIN_2_DIRECTION    PORT_PIN_DIRECTION
#define PORT_D_PIN_3_DIRECTION    PORT_PIN_DIRECTION
#define PORT_D_PIN_4_DIRECTION    PORT_PIN_DIRECTION
#define PORT_D_PIN_5_DIRECTION    PORT_PIN_DIRECTION
#define PORT_D_PIN_6_DIRECTION    PORT_PIN_DIRECTION
#define PORT_D_PIN_7_DIRECTION    PORT_PIN_DIRECTION

#define PORT_E_PIN_0_DIRECTION    PORT_PIN_DIRECTION
#define PORT_E_PIN_1_DIRECTION    PORT_PIN_DIRECTION
#define PORT_E_PIN_2_DIRECTION    PORT_PIN_DIRECTION
#define PORT_E_PIN_3_DIRECTION    PORT_PIN_DIRECTION
#define PORT_E_PIN_4_DIRECTION    PORT_PIN_DIRECTION
#define PORT_E_PIN_5_DIRECTION    PORT_PIN_DIRECTION

#define PORT_F_PIN_0_DIRECTION    0
#define PORT_F_PIN_1_DIRECTION    1
#define PORT_F_PIN_2_DIRECTION    1
#define PORT_F_PIN_3_DIRECTION    1
#define PORT_F_PIN_4_DIRECTION    0


//******************************************************************************************************************************************//
#define PORT_A_PIN_0_DIR_CHANG         STD_OFF
#define PORT_A_PIN_1_DIR_CHANG         STD_OFF
#define PORT_A_PIN_2_DIR_CHANG         STD_OFF
#define PORT_A_PIN_3_DIR_CHANG         STD_OFF
#define PORT_A_PIN_4_DIR_CHANG         STD_OFF
#define PORT_A_PIN_5_DIR_CHANG         STD_OFF
#define PORT_A_PIN_6_DIR_CHANG         STD_OFF
#define PORT_A_PIN_7_DIR_CHANG         STD_OFF

#define PORT_B_PIN_0_DIR_CHANG         STD_OFF
#define PORT_B_PIN_1_DIR_CHANG         STD_OFF
#define PORT_B_PIN_2_DIR_CHANG         STD_OFF
#define PORT_B_PIN_3_DIR_CHANG         STD_OFF
#define PORT_B_PIN_4_DIR_CHANG         STD_OFF
#define PORT_B_PIN_5_DIR_CHANG         STD_OFF
#define PORT_B_PIN_6_DIR_CHANG         STD_OFF
#define PORT_B_PIN_7_DIR_CHANG         STD_OFF

#define PORT_C_PIN_0_DIR_CHANG         STD_OFF
#define PORT_C_PIN_1_DIR_CHANG         STD_OFF
#define PORT_C_PIN_2_DIR_CHANG         STD_OFF
#define PORT_C_PIN_3_DIR_CHANG         STD_OFF
#define PORT_C_PIN_4_DIR_CHANG         STD_OFF
#define PORT_C_PIN_5_DIR_CHANG         STD_OFF
#define PORT_C_PIN_6_DIR_CHANG         STD_OFF
#define PORT_C_PIN_7_DIR_CHANG         STD_OFF

#define PORT_D_PIN_0_DIR_CHANG         STD_OFF
#define PORT_D_PIN_1_DIR_CHANG         STD_OFF
#define PORT_D_PIN_2_DIR_CHANG         STD_OFF
#define PORT_D_PIN_3_DIR_CHANG         STD_OFF
#define PORT_D_PIN_4_DIR_CHANG         STD_OFF
#define PORT_D_PIN_5_DIR_CHANG         STD_OFF
#define PORT_D_PIN_6_DIR_CHANG         STD_OFF
#define PORT_D_PIN_7_DIR_CHANG         STD_OFF

#define PORT_E_PIN_0_DIR_CHANG         STD_OFF
#define PORT_E_PIN_1_DIR_CHANG         STD_OFF
#define PORT_E_PIN_2_DIR_CHANG         STD_OFF
#define PORT_E_PIN_3_DIR_CHANG         STD_OFF
#define PORT_E_PIN_4_DIR_CHANG         STD_OFF
#define PORT_E_PIN_5_DIR_CHANG         STD_OFF

#define PORT_F_PIN_0_DIR_CHANG         STD_OFF
#define PORT_F_PIN_1_DIR_CHANG         STD_OFF
#define PORT_F_PIN_2_DIR_CHANG         STD_OFF
#define PORT_F_PIN_3_DIR_CHANG         STD_OFF
#define PORT_F_PIN_4_DIR_CHANG         STD_OFF

//********************************************************************************************//
#define PORT_A_PIN_0_MODE    PORT_PIN_INITIAL_MODE
#define PORT_A_PIN_1_MODE    PORT_PIN_INITIAL_MODE
#define PORT_A_PIN_2_MODE    PORT_PIN_INITIAL_MODE
#define PORT_A_PIN_3_MODE    PORT_PIN_INITIAL_MODE
#define PORT_A_PIN_4_MODE    PORT_PIN_INITIAL_MODE
#define PORT_A_PIN_5_MODE    PORT_PIN_INITIAL_MODE
#define PORT_A_PIN_6_MODE    PORT_PIN_INITIAL_MODE
#define PORT_A_PIN_7_MODE    PORT_PIN_INITIAL_MODE

#define PORT_B_PIN_0_MODE    PORT_PIN_INITIAL_MODE
#define PORT_B_PIN_1_MODE    PORT_PIN_INITIAL_MODE
#define PORT_B_PIN_2_MODE    PORT_PIN_INITIAL_MODE
#define PORT_B_PIN_3_MODE    PORT_PIN_INITIAL_MODE
#define PORT_B_PIN_4_MODE    PORT_PIN_INITIAL_MODE
#define PORT_B_PIN_5_MODE    PORT_PIN_INITIAL_MODE
#define PORT_B_PIN_6_MODE    PORT_PIN_INITIAL_MODE
#define PORT_B_PIN_7_MODE    PORT_PIN_INITIAL_MODE

#define PORT_C_PIN_0_MODE    PORT_PIN_INITIAL_MODE
#define PORT_C_PIN_1_MODE    PORT_PIN_INITIAL_MODE
#define PORT_C_PIN_2_MODE    PORT_PIN_INITIAL_MODE
#define PORT_C_PIN_3_MODE    PORT_PIN_INITIAL_MODE
#define PORT_C_PIN_4_MODE    PORT_PIN_INITIAL_MODE
#define PORT_C_PIN_5_MODE    PORT_PIN_INITIAL_MODE
#define PORT_C_PIN_6_MODE    PORT_PIN_INITIAL_MODE
#define PORT_C_PIN_7_MODE    PORT_PIN_INITIAL_MODE

#define PORT_D_PIN_0_MODE    PORT_PIN_INITIAL_MODE
#define PORT_D_PIN_1_MODE    PORT_PIN_INITIAL_MODE
#define PORT_D_PIN_2_MODE    PORT_PIN_INITIAL_MODE
#define PORT_D_PIN_3_MODE    PORT_PIN_INITIAL_MODE
#define PORT_D_PIN_4_MODE    PORT_PIN_INITIAL_MODE
#define PORT_D_PIN_5_MODE    PORT_PIN_INITIAL_MODE
#define PORT_D_PIN_6_MODE    PORT_PIN_INITIAL_MODE
#define PORT_D_PIN_7_MODE    PORT_PIN_INITIAL_MODE

#define PORT_E_PIN_0_MODE    PORT_PIN_INITIAL_MODE
#define PORT_E_PIN_1_MODE    PORT_PIN_INITIAL_MODE
#define PORT_E_PIN_2_MODE    PORT_PIN_INITIAL_MODE
#define PORT_E_PIN_3_MODE    PORT_PIN_INITIAL_MODE
#define PORT_E_PIN_4_MODE    PORT_PIN_INITIAL_MODE
#define PORT_E_PIN_5_MODE    PORT_PIN_INITIAL_MODE

#define PORT_F_PIN_0_MODE    PORT_PIN_MODE_DIO
#define PORT_F_PIN_1_MODE    PORT_PIN_MODE_DIO
#define PORT_F_PIN_2_MODE    PORT_PIN_MODE_DIO
#define PORT_F_PIN_3_MODE    PORT_PIN_MODE_DIO
#define PORT_F_PIN_4_MODE    PORT_PIN_MODE_DIO



#endif /* PORT_CFG_H_ */
