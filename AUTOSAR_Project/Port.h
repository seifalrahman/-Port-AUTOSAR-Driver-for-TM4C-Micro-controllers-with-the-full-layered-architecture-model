 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Mohamed Tarek
 ******************************************************************************/


#ifndef PORT_H
#define PORT_H

#define PORT_VENDOR_ID    (1000U)

/* Port Module Id */
#define PORT_MODULE_ID    (124U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Non AUTOSAR files */
#include "Common_Macros.h"


#include "Std_Types.h"

#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif


#include "Port_Cfg.h"

/* AUTOSAR Version checking between Dio_Cfg.h and Dio.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Dio_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Dio_Cfg.h and Dio.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Dio_Cfg.h does not match the expected version"
#endif
/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for Port Init  */
#define PORT_Init_SID                   (uint8)0x00
/* Service ID for Port_SetPinDirection */
#define PORT_SetPinDirection_SID        (uint8)0x01
/*Service ID for Port_RefreshPortDirection*/
#define Port_RefreshPortDirection_SID   (uint8)0x02
/*Service ID for Port_GetVersionInfo*/
#define Port_GetVersionInfo_SID         (uint8)0x03
/*Service ID for Port_SetPinMode*/
#define Port_SetPinMode_SID             (uint8)0x04

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/*Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN_ID               (uint8)0x0A
/*Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE_ID  (uint8)0x0B
/*API Port_Init service called with wrong parameter. */
#define PORT_E_PARAM_CONFIG_ID            (uint8)0x0C
/*API Port_SetPinMode service called when mode is unchangeable. */
#define PORT_E_PARAM_INVALID_MODE_ID      (uint8)0x0D
#define PORT_E_MODE_UNCHANGEABLE_ID       (uint8)0x0E
/*API service called without module initialization*/
#define PORT_E_UNINIT_ID                  (uint8)0x0F
/*APIs called with a Null Pointer*/
#define PORT_E_PARAM_POINTER_ID           (uint8)0x10



/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/


typedef uint8 Port_PinType;

typedef uint8 Port_PinModeType ;  //8 modes


/* Description: Enum to hold PIN direction */
typedef enum
{
    PORT_PIN_IN,PORT_PIN_OUT
}Port_PinDirection;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,PULL_UP,PULL_DOWN
}Port_InternalResistor;

/* Description: Structure to configure each individual PIN:
 *	1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *	2. the number of the pin in the PORT.
 *      3. the direction of pin --> INPUT or OUTPUT
 *      4. the internal resistor --> Disable, Pull up or Pull down
 */
typedef struct 
{
    uint8 port_num; 
    Port_PinType pin_num;
    Port_PinDirection direction;
    uint8 pin_direction_changeable ;
    Port_InternalResistor resistor;
    uint8 pin_level_init_value ;
    Port_PinModeType pin_mode ;

    uint8 pin_mode_changeable ;

}Port_ConfigType_Pin;

/* Data Structure required for initializing the Port Driver */
typedef struct {
    Port_ConfigType_Pin pins[Port_Number_Of_Port_Pins ]  ;
}Port_ConfigType ;
/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

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

void Port_Init(
 const Port_ConfigType* ConfigPtr
);

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


void Port_SetPinDirection(
 Port_PinType Pin,
 Port_PinDirection Direction
) ;

/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Sync/Async: Synchronous
* Reentrancy: non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction.
************************************************************************************/



void Port_RefreshPortDirection(
 void
) ;

/************************************************************************************
* Service Name: Port_GetVersionInfo
* Sync/Async: Synchronous
* Reentrancy: non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): versioninfo Pointer to where to store the version information of this module.
* Return value: None
* Description: Returns the version information of this module.
************************************************************************************/


void Port_GetVersionInfo(
 Std_VersionInfoType* versioninfo
) ;
extern const Port_ConfigType Port_Configuration ;
#endif /* PORT_H */
