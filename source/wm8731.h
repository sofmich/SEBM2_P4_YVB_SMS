/*
 * BMI160.h
 *
 */

#ifndef WM8731_H_
#define WM8731_H_

#include "freertos_i2c.h"
#include "fsl_clock.h"
#include "fsl_port.h"
#include "stdint.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "i2s.h"

/*bmi160 registers*/
#define WM8731_SLAVE_ADDRESS		0x1A//0x1A /*If csb on 0*/


/**************************************************************************************************
* WM8731 sound chip register addresses
**************************************************************************************************/

#define WM8731_REG_LLINE_IN         0x00       // Left Channel Line Input Volume Control
#define WM8731_REG_RLINE_IN         0x01       // Right Channel Line Input Volume Control
#define WM8731_REG_LHPHONE_OUT      0x02       // Left Channel Headphone Output Volume Control
#define WM8731_REG_RHPHONE_OUT      0x03       // Right Channel Headphone Output Volume Control
#define WM8731_REG_ANALOG_PATH      0x04       // Analog Audio Path Control
#define WM8731_REG_DIGITAL_PATH     0x05       // Digital Audio Path Control

#define WM8731_REG_DIGITAL_INTERFACE 0x06

#define WM8731_REG_PDOWN_CTRL       0x0C       // Power Down Control Register



#define WM8731_REG_DIGITAL_IF       0x07       // Digital Audio Interface Format
#define WM8731_REG_SAMPLING_CTRL    0x08       // Sampling Control Register
#define WM8731_REG_ACTIVE_CTRL      0x09       // Active Control
#define WM8731_REG_RESET            0x0F       // Reset register

/**************************************************************************************************
* WM8731 sound chip #defineants (for default set up)
**************************************************************************************************/
#define _WM8731_LEFT_LINEIN         0X18     // MIC SETTINGS: ENABLE MUTE, ENABLE SIMULTANEOUS LOAD TO LEFT AND RIGHT CHANNELS
#define _WM8731_RIGHT_LINEIN        0X10     // MIC SETTINGS: ENABLE MUTE, ENABLE SIMULTANEOUS LOAD TO LEFT AND RIGHT CHANNELS
#define _WM8731_LEFT_HP             0XF0     // HEADPHONE SETTINGS : -9DB OUTPUT
#define _WM8731_RIGHT_HP            0XF0     // HEADPHONE SETTINGS : -9DB OUTPUT
#define _WM8731_ANALOGAUDIO         0XD0       // DAC SELECT
#define _WM8731_DIGITALAUDIO        0X00
#define _WM8731_POWER               0X00       // DISABLE POWER DOWN
#define _WM8731_DAIF                0X42       // ENABLE MASTER MODE AND 16BIT DATA
#define _WM8731_SAMPLING            0X18       // 32000HZ,12.288MHz oscillator.
#define _WM8731_ACTIVATE            0X01       // MODULE IS ON
#define _WM8731_DEACTIVATE          0X00       // MODULE IS OFF
#define _WM8731_RESET               0X00       // RESET VALUE




freertos_i2c_flag_t wm8731_init(void);

void wm8731_play_audio(void);

void wm8731_SamplingAudio(void);



#endif /* WM8731_H_ */
