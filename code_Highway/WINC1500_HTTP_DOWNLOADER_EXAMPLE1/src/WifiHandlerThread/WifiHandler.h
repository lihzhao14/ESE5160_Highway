/**************************************************************************/ /**
 * @file      WifiHandler.h
 * @brief     File to handle HTTP Download and MQTT support
 * @author    Eduardo Garcia
 * @date      2020-01-01

 ******************************************************************************/

#pragma once

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * Includes
 ******************************************************************************/
#include "asf.h"

#include "MQTTClient/Wrapper/mqtt.h"
#include "SerialConsole.h"
#include "asf.h"
#include "driver/include/m2m_wifi.h"
#include "iot/http/http_client.h"
#include "main.h"
#include "socket/include/socket.h"
#include "stdio_serial.h"
/******************************************************************************
 * Defines
 ******************************************************************************/

#define WIFI_MQTT_INIT 0        ///< State for Wifi handler to Initialize MQTT Connection
#define WIFI_MQTT_HANDLE 1      ///< State for Wifi handler to Handle MQTT Connection
#define WIFI_DOWNLOAD_INIT 2    ///< State for Wifi handler to Initialize Download Connection
#define WIFI_DOWNLOAD_HANDLE 3  ///< State for Wifi handler to Handle Download Connection

#define WIFI_TASK_SIZE 1500
#define WIFI_PRIORITY (configMAX_PRIORITIES - 2)

/** Wi-Fi AP Settings. */
//#define MAIN_WLAN_SSID "a"             /**< Destination SSID. Change to your WIFI SSID */
//#define MAIN_WLAN_AUTH M2M_WIFI_SEC_WPA_PSK /**< Security manner */
//#define MAIN_WLAN_PSK "aWt1234567"            /**< Password for Destination SSID. Change to your password. Please dont hack my WiFi router */
#define MAIN_WLAN_SSID "z"             /**< Destination SSID. Change to your WIFI SSID */
#define MAIN_WLAN_AUTH M2M_WIFI_SEC_WPA_PSK /**< Security manner */
#define MAIN_WLAN_PSK "z12345678"            /**< Password for Destination SSID. Change to your password. Please dont hack my WiFi router

/** IP address parsing. */
#define IPV4_BYTE(val, index) ((val >> (index * 8)) & 0xFF)

/** Content URI for download. */
#define MAIN_HTTP_FILE_URL "https://74.235.175.41/TestA.bin"  ///< Change me to the URL to download your OTAU binary file from!

/** Maximum size for packet buffer. */
#define MAIN_BUFFER_MAX_SIZE (512)
/** Maximum file name length. */
#define MAIN_MAX_FILE_NAME_LENGTH (64)
/** Maximum file extension length. */
#define MAIN_MAX_FILE_EXT_LENGTH (8)
/** Output format with '0'. */
#define MAIN_ZERO_FMT(SZ) (SZ == 4) ? "%04d" : (SZ == 3) ? "%03d" : (SZ == 2) ? "%02d" : "%d"
#define GAME_SIZE 20  ///< Number of plays in game

typedef enum {
    NOT_READY = 0,         /*!< Not ready. */
    STORAGE_READY = 0x01,  /*!< Storage is ready. */
    WIFI_CONNECTED = 0x02, /*!< Wi-Fi is connected. */
    GET_REQUESTED = 0x04,  /*!< GET request is sent. */
    DOWNLOADING = 0x08,    /*!< Running to download. */
    COMPLETED = 0x10,      /*!< Download completed. */
    CANCELED = 0x20        /*!< Download canceled. */
} download_state;


// Structure to hold a test packet
struct TestPacket {
	uint8_t test;
};

struct NauPacket {
	uint16_t nau_i;
	uint16_t nau_f;
	//uint32_t nau_i;
	//uint32_t nau_f;
};

/* Max size of UART buffer. */
#define MAIN_CHAT_BUFFER_SIZE 64

/* Max size of MQTT buffer. */
#define MAIN_MQTT_BUFFER_SIZE 512

/* Limitation of user name. */
#define MAIN_CHAT_USER_NAME_SIZE 64




#define PLAYER1 1  ///< Comment me to compile for player 2. Uncomment me to define for player 1.

#ifdef PLAYER1
/* Chat MQTT topic. */
#define LED_TOPIC "P1_LED_ESE516_T9"            // Students to change to an unique identifier for each device! LED Data
#define IMU_TOPIC "P1_IMU_ESE516_T9"            // Students to change to an unique identifier for each device! IMU Data
#define DISTANCE_TOPIC "P1_DISTANCE_ESE516_T9"  // Students to change to an unique identifier for each device! Distance Data
#define TEMPERATURE_TOPIC "P1_TEMPERATURE_ESE516_T9" // Students to change to an unique identifier for each device! Distance Data
#define TEST_TOPIC "TEST_TOPIC_516_T9"          // used to test whether MQTT can properly work
#define NAU_TOPIC "NAU_TOPIC_516_T9"          // used to test whether MQTT can properly work
#define SERVO_TOPIC "SERVO_TOPIC_516_T9"          // used to test whether MQTT can properly work
#define TOTALCHARGE_TOPIC "TOTALCHARGE_TOPIC_516_T9" 

#else
/* Chat MQTT topic. */
#define LED_TOPIC "P2_LED_ESE516_T9"            // Students to change to an unique identifier for each device! LED Data
#define IMU_TOPIC "P2_IMU_ESE516_T9"            // Students to change to an unique identifier for each device! IMU Data
#define DISTANCE_TOPIC "P2_DISTANCE_ESE516_T9"  // Students to change to an unique identifier for each device! Distance Data
#define TEMPERATURE_TOPIC "P2_TEMPERATURE_ESE516_T9" // Students to change to an unique identifier for each device! Distance Data

#endif

#define LED_TOPIC_LED_OFF "false"
#define LED_TOPIC_LED_ON "true"

// Cloud MQTT User
#define CLOUDMQTT_USER_ID "Highway"

// Cloud MQTT pASSWORD
#define CLOUDMQTT_USER_PASSWORD "highway15"

#define CLOUDMQTT_PORT 1883

/*
 * A MQTT broker server which was connected.
 * m2m.eclipse.org is public MQTT broker.
 */
static const char main_mqtt_broker[] = "broker.hivemq.com";

#define STRING_EOL "\r\n"
#define STRING_HEADER                                                                 \
    "-- HTTP file downloader example --" STRING_EOL "-- " BOARD_NAME " --" STRING_EOL \
    "-- Compiled: "__DATE__                                                           \
    " "__TIME__                                                                       \
    " --" STRING_EOL

/******************************************************************************
 * Structures and Enumerations
 ******************************************************************************/

/******************************************************************************
 * Global Function Declaration
 ******************************************************************************/
void vWifiTask(void *pvParameters);
void init_storage(void);
void WifiHandlerSetState(uint8_t state);
int WifiAddTestDataToQueue(struct TestPacket *test);
int WifiAddNauDataToQueue(struct NauPacket *nau);
void SubscribeHandlerLedTopic(MessageData *msgData);
void SubscribeHandlerServo(MessageData *msgData);
void configure_extint_channel(void);
void configure_extint_callbacks(void);

#ifdef __cplusplus
}
#endif
