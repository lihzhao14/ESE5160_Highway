/**
* @file      UiHandlerThread.c
* @brief     File that contains the task code and supporting code for the UI
Thread for ESE516 Spring (Online) Edition
* @author    You! :)
* @date      2020-04-09

******************************************************************************/

/******************************************************************************
 * Includes
 ******************************************************************************/
#include "UiHandlerThread/UiHandlerThread.h"

#include <errno.h>

#include "DistanceDriver/DistanceSensor.h"
#include "IMU/lsm6dso_reg.h"
#include "SeesawDriver/Seesaw.h"
#include "SerialConsole.h"
#include "WifiHandlerThread/WifiHandler.h"
#include "asf.h"
#include "gfx_mono.h"
#include "main.h"
#include "servo/servo.h"
#include "nau7802/nau7802.h"

/******************************************************************************
 * Defines
 ******************************************************************************/
#define BUTTON_PRESSES_MAX 16  ///< Number of maximum button presses to analize in one go

/******************************************************************************
 * Variables
 ******************************************************************************/
uiStateMachine_state uiState;         ///< Holds the current state of the UI
struct GameDataPacket gamePacketIn;   ///< Holds the game packet to show
struct GameDataPacket gamePacketOut;  ///< Holds the game packet to send back
volatile uint8_t red = 0;             ///< Holds the color of the red LEDs. Can be set by MQTT
volatile uint8_t green = 100;         ///< Holds the color of the green LEDs. Can be set by MQTT
volatile uint8_t blue = 50;           ///< Holds the color of the blue LEDs. Can be set by MQTT

uint8_t pressedKeys = 0;              ///< Variable to count how many presses the player has done
uint8_t keysToPress = 0;              ///< Variable that holds the number of new keypresses the user should do
bool playIsDone = false;              ///< Boolean flag to indicate if the player has finished moving.
                                      ///< Useful for COntrol to determine when to send back a play.
uint8_t buttons[BUTTON_PRESSES_MAX];  ///< Array to hold button presses
/******************************************************************************
 * Forward Declarations
 ******************************************************************************/

/******************************************************************************
 * Callback Functions
 ******************************************************************************/

/******************************************************************************
 * Task Function
 ******************************************************************************/

/**
 * @fn		void vUiHandlerTask( void *pvParameters )
 * @brief	STUDENT TO FILL THIS
 * @details 	student to fill this
 * @param[in]	Parameters passed when task is initialized. In this case we can ignore them!
 * @return		Should not return! This is a task defining function.
 * @note
 */
void vUiHandlerTask(void *pvParameters)
{
    // Do initialization code here
	SerialConsoleWriteString("UI Task Started!");
    uiState = UI_STATE_IGNORE_PRESSES;  // Initial state
	configure_tcc();
	servo_setDuty(2);

	
    // Graphics Test - Students to uncomment to test out the OLED driver if you are using it! 
	
    gfx_mono_init();
    gfx_mono_draw_string("ESE516", 0, 8, &sysfont);
    gfx_mono_draw_string("HIGHWAY", 0, 18, &sysfont);
	uint8_t count = 0;
	uint8_t count_nau = 0;
	uint16_t nau_i_total = 0;
	uint16_t nau_f_total = 0;
	char oled_display[64];
	bool servo_flag = false;
	I2cInitializeDriver();
	ADCchip_Init();
	

    // Here we start the loop for the UI State Machine
    while (1) {
		ADC_StartConversion();
		struct NauPacket nauvar;
		
		while ((ADC_ReadReg(PU_CTRL_ADDR)&CR_Msk) != CR_DATA_RDY);
		uint32_t ADC_value=ADC_Read_Conversion_Data();
		uint16_t ADC_Array[2];
		//int ADC_Array[2];
		Value_conversion(ADC_value,ADC_Array);
		char help[64];
		//snprintf(help, 64, "input vol = VIN1P - VIN1N = %d\r\n",ADC_Array[0]);
		nauvar.nau_i = ADC_Array[0];
		nauvar.nau_f = ADC_Array[1];
		//nau_i_total = ADC_Array[0] + nau_i_total;
		//nau_f_total = ADC_Array[1] + nau_f_total;
		
		int error = WifiAddNauDataToQueue(&nauvar);
		//if(count_nau!=3)
		//{
			//count_nau = count_nau + 1;
		//}
		//else
		//{
			//count_nau = 0;
			//nauvar.nau_i = nau_i_total/3;
			//nauvar.nau_f = nau_f_total/3;
			//nau_i_total = 0;
			//nau_i_total = 0;
			//int error = WifiAddNauDataToQueue(&nauvar);
		//}
		//
		
		
		if(count!=100)
		{
			count = count + 1;
		}
		else
		{
			count = 0;
			gfx_mono_init();
			sprintf(oled_display, "%d.%d", ADC_Array[0], ADC_Array[1]);
			gfx_mono_draw_string(oled_display, 0, 8, &sysfont);
		}
		
		
        //switch (uiState) {
            //case (UI_STATE_IGNORE_PRESSES): {
                //// Ignore any presses until we receive a command from the control thread
                //// to go to UI_STATE_SHOW_MOVES Will be changed by control with the
                //// function void UiOrderShowMoves(struct GameDataPacket *packetIn) which
                //// gets called when a valid MQTT Package comes in!
                //break;
            //}
//
            //case (UI_STATE_SHOW_MOVES): {
                //// Set initial state variable that will be used on the
                //// UI_STATE_Handle_Buttons and need to be initialized once
                //pressedKeys = 0;  // Set number of keys pressed by player to 0.
                //keysToPress = 1;  // Set as an example to 1. STUDENTS should change this
                                  //// to the number of key presses needed.
                //memset(gamePacketOut.game, 0xff,
                       //sizeof(gamePacketOut.game));  // Erase gamePacketOut to an initial state
                //playIsDone = false;                  // Set play to false
                //uint8_t presses = SeesawGetKeypadCount();
                //if (presses >= BUTTON_PRESSES_MAX) presses = BUTTON_PRESSES_MAX;
                //if (presses != 0)
                    //SeesawReadKeypad(buttons,
                                     //presses);  // Empty Seesaw buffer just in case
                                                //// it has latent presses on it!
                //memset(buttons, 0, BUTTON_PRESSES_MAX);
                //// STUDENTS: Make this function show the moves of the gamePacketIn.
                //// You can use a static delay to show each move but a quicker delay as
                //// the message gets longer might be more fun! After you finish showing
                //// the move should go to state UI_STATE_HANDLE_BUTTONS
//
                //// In the beginner example we turn LED0 and LED15 will turn on for 500
                //// ms then we go to UI_STATE_HANDLE_BUTTONS
                //SeesawSetLed(0, red, green, blue);  // Turn button 1 on
                //SeesawOrderLedUpdate();
                //vTaskDelay(1000);
                //SeesawSetLed(0, 0, 0, 0);            // Turn button 0 off
                //SeesawSetLed(15, red, green, blue);  // Turn button 15 on
                //SeesawOrderLedUpdate();
                //vTaskDelay(1000);
                //SeesawSetLed(15, 0, 0, 0);  // Turn button 15 off
                //SeesawOrderLedUpdate();
                //vTaskDelay(1000);
                //uiState = UI_STATE_HANDLE_BUTTONS;
//
                //break;
            //}
//
            //case (UI_STATE_HANDLE_BUTTONS): {
                //// This state should accept (gamePacketIn length + 1) moves from the
                //// player (capped to maximum 19 + new move) The moves by the player
                //// should be stored on "gamePacketOut". The keypresses that should count
                //// are when the player RELEASES the button.
//
                //// In this example, we return after only one button press!
//
                //uint8_t numPresses = SeesawGetKeypadCount();
                //memset(buttons, 0, BUTTON_PRESSES_MAX);
//
                //if (numPresses >= BUTTON_PRESSES_MAX) {
                    //numPresses = BUTTON_PRESSES_MAX;
                //}
                //if (numPresses != 0 && ERROR_NONE == SeesawReadKeypad(buttons, numPresses)) {
                    //// Process Buttons
                    //for (int iter = 0; iter < numPresses; iter++) {
                        //uint8_t keynum = NEO_TRELLIS_SEESAW_KEY((buttons[iter] & 0xFD) >> 2);
                        //uint8_t actionButton = buttons[iter] & 0x03;
                        //if (actionButton == 0x03) {
                            //SeesawSetLed(keynum, red, green, blue);
                        //} else {
                            //SeesawSetLed(keynum, 0, 0, 0);
                            //// Button released! Count this into the buttons pressed by user.
                            //gamePacketOut.game[pressedKeys] = keynum;
                            //pressedKeys++;
                        //}
                    //}
                    //SeesawOrderLedUpdate();
                //}
//
                //// Check if we are done!
                //if (pressedKeys >= keysToPress || pressedKeys >= GAME_SIZE) {
                    //// Tell control gamePacketOut is ready to be send out AND go back to
                    //// UI_STATE_IGNORE_PRESSES
                    //playIsDone = true;
                    //uiState = UI_STATE_IGNORE_PRESSES;
                //}
//
                //break;
            //}
//
            //default:  // In case of unforseen error, it is always good to sent state
                      //// machine to an initial state.
                //uiState = UI_STATE_HANDLE_BUTTONS;
                //break;
        //}
		
        // After execution, you can put a thread to sleep for some time.
        vTaskDelay(50);
    }
}

/******************************************************************************
 * Functions
 ******************************************************************************/
void UiOrderShowMoves(struct GameDataPacket *packetIn)
{
    memcpy(&gamePacketIn, packetIn, sizeof(gamePacketIn));
    uiState = UI_STATE_SHOW_MOVES;
    playIsDone = false;  // Set play to false
}

bool UiPlayIsDone(void)
{
    return playIsDone;
}

struct GameDataPacket *UiGetGamePacketOut(void)
{
    return &gamePacketOut;
}

/**
 int UIChangeColors(uint8_t r, uint8_t g, uint8_t b);
 * @brief	Changes the LED colors
 * @param [in]
 * @return
 * @note

*/
void UIChangeColors(uint8_t r, uint8_t g, uint8_t b)
{
    red = r;
    green = g;
    blue = b;
}
