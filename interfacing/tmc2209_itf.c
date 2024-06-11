#include "tmc2209_itf.h"

/********************************************************/
/*														*/
/*					Static variables					*/
/*														*/
/********************************************************/

static uint32_t _how_many_steps = 0;
static uint32_t _steps_now = 0;

/********************************************************/
/*														*/
/*			Static functions declaration				*/
/*														*/
/********************************************************/

static void setup_gpio();

static void setup_tim();

static void turn_interrupt_on();

static void turn_interrupt_off();
/********************************************************/
/*														*/
/*			Static functions implementation				*/
/*														*/
/********************************************************/

static void setup_gpio(){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN;

	GPIOD->MODER &= ~(GPIO_MODER_MODE3_Msk | GPIO_MODER_MODE2);
	GPIOD->MODER |= (2 << GPIO_MODER_MODE3_Pos | 1 << GPIO_MODER_MODE2_Pos);
	GPIOD->AFR[0] |= 2 << GPIO_AFRL_AFSEL3_Pos;
}

static void setup_tim(){
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;

	TIM2->CCMR1 |= TIM_CCMR1_OC1PE | 6 << TIM_CCMR1_OC1M_Pos;
	TIM2->CCER |= TIM_CCER_CC1E;
	TIM2->CR1 |= TIM_CR1_ARPE;
}

static void turn_interrupt_on(){
	TIM2->DIER |= TIM_DIER_CC1IE;
	NVIC_EnableIRQ(TIM2_IRQn);
}

static void turn_interrupt_off(){
	TIM2->DIER &= ~TIM_DIER_CC1IE;
	NVIC_DisableIRQ(TIM2_IRQn);
}

/********************************************************/
/*														*/
/*			Global functions implementation				*/
/*														*/
/********************************************************/

void setup_peripherals(){
	setup_gpio();
	setup_tim();
}

void set_dir_high(){
	GPIOD->BSRR = GPIO_BSRR_BS2;
}
void set_dir_low(){
	GPIOD->BSRR = GPIO_BSRR_BR2;
}

uint8_t set_velocity(uint32_t velocity){
	if (velocity == 0 || velocity > SYSTEM_CLOCK_FREQUENCY_HZ) {
		return 1;
	}

	uint32_t max_arr = 0xFFFF;

	for (uint32_t prescaler = 0; prescaler <= max_arr; prescaler+=1) {
		uint32_t auto_reload = (SYSTEM_CLOCK_FREQUENCY_HZ / (velocity * (prescaler + 1)));
		if (auto_reload-1 <= max_arr && auto_reload % 2 == 0) {
			TIM2->PSC = prescaler;
			TIM2->ARR = auto_reload-1;
			TIM2->CCR1 = TIM2->ARR/2;
			return 0;
		}
	}

	return 1;
}

void turn_pwm_on(){
	TIM2->CR1 |= TIM_CR1_CEN;
}
void turn_pwm_off(){
	TIM2->CR1 &= ~TIM_CR1_CEN;
	if(_how_many_steps != 0){
		turn_interrupt_off();
	}
}

void set_steps(uint32_t steps){
	_how_many_steps = steps;
	turn_interrupt_on();
}

void TIM2_IRQHandler(void){
	if(TIM2->SR & TIM_SR_CC1IF){
		TIM2->SR &= ~TIM_SR_CC1IF;
		_steps_now+=1;
		if(_steps_now >= _how_many_steps){
			turn_pwm_off();
			_how_many_steps = 0;
			_steps_now = 0;
		}
	}
}
