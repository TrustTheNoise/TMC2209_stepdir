#include "tmc2209_itf_in.h"


/********************************************************/
/*														*/
/*			Static functions declaration				*/
/*														*/
/********************************************************/

static uint8_t tmc_check_declaration(tmc2209 *tmc_instance);


/********************************************************/
/*														*/
/*			Static functions implementation				*/
/*														*/
/********************************************************/

static uint8_t tmc_check_declaration(tmc2209 *tmc_instance){
	if(tmc_instance->setup_peripherals == 0){
		return 1;
	}
	if(tmc_instance->set_velocity == 0){
		return 1;
	}
	if(tmc_instance->set_steps == 0){
		return 1;
	}
	if(tmc_instance->turn_pwm_off == 0){
		return 1;
	}
	if(tmc_instance->turn_pwm_on == 0){
		return 1;
	}
	if(tmc_instance->set_dir_high == 0){
		return 1;
	}
	if(tmc_instance->set_dir_low == 0){
		return 1;
	}
	return 0;
}


/********************************************************/
/*														*/
/*			Global functions implementation				*/
/*														*/
/********************************************************/

uint8_t tmc2209_init(tmc2209 *tmc_instance){
	if(tmc_check_declaration(tmc_instance)){
		return 1;
	}
	tmc_instance->setup_peripherals();
	tmc_instance->velocity = 0;
	tmc_instance->directory = TMC_DIRECTORY_FORWARD;
	tmc_instance->was_initialized = 1;
	return 0;
}

uint8_t tmc2209_set_velocity(tmc2209 *tmc_instance, uint32_t velocity){
	if (tmc_instance->was_initialized == 0 ){
		return 1;
	}
	if(tmc_instance->set_velocity(velocity)){
		return 1;
	}
	tmc_instance->velocity = velocity;
	return 0;
}

uint8_t tmc2209_start_motor(tmc2209 *tmc_instance){
	if (tmc_instance->was_initialized == 0 ){
		return 1;
	}
	if  (tmc_instance->velocity == 0){
		return 1;
	}
	tmc_instance->turn_pwm_on();
	return 0;
}

uint8_t tmc2209_stop_motor(tmc2209 *tmc_instance){
	if (tmc_instance->was_initialized == 0 ){
		return 1;
	}
	tmc_instance->turn_pwm_off();
	return 0;
}

uint8_t tmc2209_start_motor_steps(tmc2209 *tmc_instance, uint32_t steps){
	if (tmc_instance->was_initialized == 0 ){
		return 1;
	}
	if (tmc_instance->velocity == 0){
		return 1;
	}
	tmc_instance->set_steps(steps);
	tmc_instance->turn_pwm_on();
	return 0;
}

uint8_t tmc2209_switch_direction(tmc2209 *tmc_instance){
	if (tmc_instance->was_initialized == 0 ){
		return 1;
	}
	if (tmc_instance->directory == TMC_DIRECTORY_FORWARD){
		tmc_instance->set_dir_high();
		tmc_instance->directory = TMC_DIRECTORY_BACKWARD;
		return 0;
	}
	tmc_instance->set_dir_low();
	tmc_instance->directory = TMC_DIRECTORY_FORWARD;
	return 0;
}
