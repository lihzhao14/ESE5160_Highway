/*
 * servo.h
 *
 * Created: 4/20/2023 8:48:59 AM
 *  Author: 60267
 */ 


#include <FreeRTOS.h>
#include <asf.h>
#include <semphr.h>
#include <task.h>
#include <tcc.h>



#ifndef SERVO_H_
#define SERVO_H_
#define PWM_MODULE    EXT1_PWM_MODULE
#define PWM_OUT_PIN    EXT1_PWM_0_PIN
#define PWM_OUT_MUX     EXT1_PWM_0_MUX



#define CONF_PWM_MODULE      TCC0
#define CONF_PWM_CHANNEL     TCC_MATCH_CAPTURE_CHANNEL_2
#define CONF_PWM_OUTPUT      2



#define CONF_PWM_OUT_PIN     PIN_PA10F_TCC0_WO2
#define CONF_PWM_OUT_MUX     MUX_PA10F_TCC0_WO2



void configure_tcc(void);
void servo_setDuty(int dutyCycle);


#endif /* SERVO_H_ */