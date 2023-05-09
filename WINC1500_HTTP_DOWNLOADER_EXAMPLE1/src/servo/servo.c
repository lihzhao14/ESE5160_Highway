/*
 * servo.c
 *
 * Created: 4/20/2023 8:48:45 AM
 *  Author: 60267
 */ 
#include "servo.h"
struct tcc_module tcc_instance;
void configure_tcc(void)
{
	struct tcc_config config_tcc;
	tcc_get_config_defaults(&config_tcc, CONF_PWM_MODULE);
	config_tcc.counter.clock_prescaler = TCC_CLOCK_PRESCALER_DIV4;
	config_tcc.counter.period = 0xBA2E;
	config_tcc.compare.wave_generation = TCC_WAVE_GENERATION_SINGLE_SLOPE_PWM;
	config_tcc.compare.match[CONF_PWM_CHANNEL] = (0xBA2E / 2);
	config_tcc.pins.enable_wave_out_pin[CONF_PWM_OUTPUT] = true;
	config_tcc.pins.wave_out_pin[CONF_PWM_OUTPUT]        = CONF_PWM_OUT_PIN;
	config_tcc.pins.wave_out_pin_mux[CONF_PWM_OUTPUT]    = CONF_PWM_OUT_MUX;
	tcc_init(&tcc_instance, CONF_PWM_MODULE, &config_tcc);
	tcc_enable(&tcc_instance);
}


void servo_setDuty(int dutyCycle)
{
	uint32_t compareValue = 0xBA2E / dutyCycle;
	tcc_set_compare_value(&tcc_instance, CONF_PWM_CHANNEL, compareValue);
}