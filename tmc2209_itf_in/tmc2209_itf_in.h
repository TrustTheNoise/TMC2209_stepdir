#ifndef TCM2209_ITF_IN_H_
#define TCM2209_ITF_IN_H_

#include "stm32g474xx.h"

/********************************************************/
/*														*/
/*						  ENUMs							*/
/*														*/
/********************************************************/

typedef enum {
	TMC_DIRECTORY_FORWARD,
	TMC_DIRECTORY_BACKWARD
} tmc_directory;

/********************************************************/
/*														*/
/*						Structure						*/
/*														*/
/********************************************************/

typedef struct {
	void (*const setup_peripherals) (void);

	uint8_t (*const set_velocity) (uint32_t);
	void (*const set_steps) (uint32_t);

	void (*const turn_pwm_on) (void);
	void (*const turn_pwm_off) (void);

	void (*const set_dir_high) (void);
	void (*const set_dir_low) (void);

	uint32_t velocity;
	uint8_t was_initialized;

	tmc_directory directory;
} tmc2209;


/********************************************************/
/*														*/
/*					Initialization						*/
/*														*/
/********************************************************/

uint8_t tmc2209_init(tmc2209 *tmc_instance);

uint8_t tmc2209_set_velocity(tmc2209 *tmc_instance, uint32_t velocity);

uint8_t tmc2209_switch_direction(tmc2209 *tmc_instance);

/********************************************************/
/*														*/
/*				Control motors by tmc2209				*/
/*														*/
/********************************************************/

uint8_t tmc2209_start_motor(tmc2209 *tmc_instance);
uint8_t tmc2209_stop_motor(tmc2209 *tmc_instance);

uint8_t tmc2209_start_motor_steps(tmc2209 *tmc_instance, uint32_t steps);

#endif /* TCM2209_ITF_IN_H_ */
