#ifndef INTERFACING_H_
#define INTERFACING_H_

#include "stm32g474xx.h"

#ifndef SYSTEM_MAIN_FREQUENCY
    #define SYSTEM_CLOCK_FREQUENCY_HZ        16000000U // Hz
#endif /* SYSTEM_MAIN_FREQUENCY */

/*! Proper definitions of GPIO setup. */
#define GPIO_MODER_Msk              (3U)    // 0b11
#define GPIO_DIGITAL_IN_Mode        (0U)    // 0b00
#define GPIO_DIGITAL_OUT_Mode       (1U)    // 0b01
#define GPIO_ALTERNATE_Mode         (2U)    // 0b10
#define GPIO_ANALOG_IN_Mode         (3U)    // 0b11

#endif /* INTERFACING_H_ */
