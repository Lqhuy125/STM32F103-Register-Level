#ifndef INC_ADC_H_
#define INC_ADC_H_

#include "main.h"

//ADC Single channel select

/*
 *  @brief ADC GPIO pins PA5-POT, PA4-X, PA3-Y
 */
typedef enum{
  Potemtionmeter = 5,
  Joystick_x = 4,
  Joystick_y = 3,
} ADC_SingleSelect;

/*
 *  @brief ADC GPIO pins PA5-POT, PA4-X, PA3-Y
 */
void adc_GPIO_config();

/*
 *  #brief ADC SIGNLE CHANNEL CONFI
 */
void adc_single_config(ADC_SingleSelect channel);

/*
 * #brief SWSTART
 */
void adc_Start();

void adc_Stop();

/*
 * @brief adc poll for end of conservation
 */
bool adc_poll_For_End_of_Conservation(uint32_t timeOut );

/*
 * @brief adc value
 */
uint16_t adc_readValue();

void adc_enableEOC();
void adc_disableEOC();

#endif /* INC_ADC_H_ */
