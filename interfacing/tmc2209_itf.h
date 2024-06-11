#ifndef TMC2209_ITF_H_
#define TMC2209_ITF_H_

#ifndef SYSTEM_CLOCK_FREQUENCY_HZ
    #define SYSTEM_CLOCK_FREQUENCY_HZ        16000000U // Hz
#endif /* SYSTEM_MAIN_FREQUENCY */

#include "stm32g474xx.h"


void setup_peripherals();

void set_dir_high();
void set_dir_low();

uint8_t set_velocity(uint32_t velocity);

void turn_pwm_on();
void turn_pwm_off();

void set_steps(uint32_t steps);

void TIM2_IRQHandler(void);

#endif /* TMC2209_ITF_H_ */
