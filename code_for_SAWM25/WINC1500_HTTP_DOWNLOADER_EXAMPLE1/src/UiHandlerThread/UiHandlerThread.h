/**************************************************************************/ /**
 * @file      UiHandlerThread.h
 * @brief     File that contains the task code and supporting code for the UI Thread for ESE516 Spring (Online) Edition
 * @author    You! :)
 * @date      2020-04-09

 ******************************************************************************/

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * Includes
 ******************************************************************************/
#include "WifiHandlerThread/WifiHandler.h"
/******************************************************************************
 * Defines
 ******************************************************************************/
#define UI_TASK_SIZE 400  //<Size of stack to assign to the UI thread. In words
#define UI_TASK_PRIORITY (configMAX_PRIORITIES - 1)
/******************************************************************************
 * Structures and Enumerations
 ******************************************************************************/

/******************************************************************************
 * Global Function Declaration
 ******************************************************************************/
void vUiHandlerTask(void *pvParameters);


#ifdef __cplusplus
}
#endif
