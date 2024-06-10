#include "tmc2209_itf.h"
#include "tmc2209_itf_in.h"

int main(void)
{
	tmc2209 first_motor = {
			.setup_peripherals = setup_peripherals,

			.set_velocity = set_velocity,
			.set_steps = set_steps,

			.set_dir_high = set_dir_high,
			.set_dir_low = set_dir_low,

			.turn_pwm_on = turn_pwm_on,
			.turn_pwm_off = turn_pwm_off,
	};

	tmc2209_init(&first_motor);

	tmc2209_switch_direction(&first_motor);

	// infinite motor movement
	tmc2209_set_velocity(&first_motor, 5);
	tmc2209_start_motor(&first_motor);

	// movement up to a certain step
	tmc2209_stop_motor(&first_motor);
	tmc2209_start_motor_steps(&first_motor, 300);
}
