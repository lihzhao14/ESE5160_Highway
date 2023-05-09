/**************************************************************************/ /**
 * @file      ControlThread.c
 * @brief     Thread code for the ESE516 Online game control thread
 * @author    You!
 * @date      2020-04-015

 ******************************************************************************/

/******************************************************************************
 * Includes
 ******************************************************************************/
#include "ControlThread/ControlThread.h"

#include <errno.h>

#include "SerialConsole.h"
#include "UiHandlerThread/UiHandlerThread.h"
#include "WifiHandlerThread/WifiHandler.h"
#include "asf.h"
#include "main.h"
#include "shtc3.h"
#include "stdio_serial.h"

/******************************************************************************
 * Defines
 ******************************************************************************/

/******************************************************************************
 * Variables
 ******************************************************************************/
QueueHandle_t xQueueRgbColorBuffer = NULL;  ///< Queue to receive an LED Color packet


/******************************************************************************
 * Forward Declarations
 ******************************************************************************/

/******************************************************************************
 * Callback Functions
 ******************************************************************************/

/******************************************************************************
 * Task Functions
 ******************************************************************************/

/**
 * @fn		void vControlHandlerTask( void *pvParameters )
 * @brief	STUDENT TO FILL THIS
 * @details 	student to fill this

 * @param[in]	Parameters passed when task is initialized. In this case we can ignore them!
 * @return		Should not return! This is a task defining function.
 * @note
 */
void vControlHandlerTask(void *pvParameters)
{
    

    while (1) {
        

            
        vTaskDelay(40);
    }
}

