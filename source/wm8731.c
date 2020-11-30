#include <wm8731.h>

#define I2C_SCL		2U
#define I2C_SDA		3U
#define BAUD_RATE	100000
#define I2C_DELAY	100//(ms)

/*Global declaratios*/
static freertos_i2c_config_t WM8731_i2c_config;
freertos_i2c_flag_t wm8731_sucess = freertos_i2c_fail;

freertos_i2c_flag_t wm8731_init(void)
{
	/*Start port and freertos i2c inicialization */
	WM8731_i2c_config.baudrate = BAUD_RATE;
	WM8731_i2c_config.i2c_number = 	freertos_i2c0;
	WM8731_i2c_config.port = freertos_i2c_portB;
	WM8731_i2c_config.scl_pin = I2C_SCL;
	WM8731_i2c_config.sda_pin = I2C_SDA;
	WM8731_i2c_config.pin_mux = kPORT_MuxAlt2;

	/*Init configuration for freertos i2c*/
	wm8731_sucess = freertos_i2c_init(WM8731_i2c_config);
	vTaskDelay(pdMS_TO_TICKS(10));

	if(freertos_i2c_sucess == wm8731_sucess)
	{
		wm8731_sucess = freertos_i2c_fail;

		/*Initial configuration of bmi160*/
		uint8_t data[2] = {WM8731_REG_RESET, _WM8731_RESET};
		/*Acc config*/
		wm8731_sucess = freertos_i2c_transmit(WM8731_i2c_config.i2c_number, data , 2, WM8731_SLAVE_ADDRESS);
		vTaskDelay(pdMS_TO_TICKS(I2C_DELAY));

		data[0] = WM8731_REG_LLINE_IN;
		data[1] = _WM8731_LEFT_LINEIN;
		wm8731_sucess = freertos_i2c_transmit(WM8731_i2c_config.i2c_number, data , 2, WM8731_SLAVE_ADDRESS);
		vTaskDelay(pdMS_TO_TICKS(I2C_DELAY));

		data[0] = WM8731_REG_RLINE_IN;
		data[1] = _WM8731_RIGHT_LINEIN;
		wm8731_sucess = freertos_i2c_transmit(WM8731_i2c_config.i2c_number, data , 2, WM8731_SLAVE_ADDRESS);
		vTaskDelay(pdMS_TO_TICKS(I2C_DELAY));


		data[0] = WM8731_REG_LHPHONE_OUT;
		data[1] = _WM8731_LEFT_HP;
		wm8731_sucess = freertos_i2c_transmit(WM8731_i2c_config.i2c_number, data , 2, WM8731_SLAVE_ADDRESS);
		vTaskDelay(pdMS_TO_TICKS(I2C_DELAY));

		data[0] = WM8731_REG_RHPHONE_OUT;
		data[1] = _WM8731_RIGHT_HP;
		wm8731_sucess = freertos_i2c_transmit(WM8731_i2c_config.i2c_number, data , 2, WM8731_SLAVE_ADDRESS);
		vTaskDelay(pdMS_TO_TICKS(I2C_DELAY));

		data[0] = WM8731_REG_ANALOG_PATH;
		data[1] = _WM8731_ANALOGAUDIO;
		wm8731_sucess = freertos_i2c_transmit(WM8731_i2c_config.i2c_number, data , 2, WM8731_SLAVE_ADDRESS);
		vTaskDelay(pdMS_TO_TICKS(I2C_DELAY));

		data[0] = WM8731_REG_DIGITAL_PATH;
		data[1] = _WM8731_DIGITALAUDIO;
		wm8731_sucess = freertos_i2c_transmit(WM8731_i2c_config.i2c_number, data , 2, WM8731_SLAVE_ADDRESS);
		vTaskDelay(pdMS_TO_TICKS(I2C_DELAY));

		data[0] = WM8731_REG_PDOWN_CTRL;
		data[1] = _WM8731_POWER;
		wm8731_sucess = freertos_i2c_transmit(WM8731_i2c_config.i2c_number, data , 2, WM8731_SLAVE_ADDRESS);
		vTaskDelay(pdMS_TO_TICKS(I2C_DELAY));

		data[0] = WM8731_REG_DIGITAL_IF;
		data[1] = _WM8731_DAIF;
		wm8731_sucess = freertos_i2c_transmit(WM8731_i2c_config.i2c_number, data , 2, WM8731_SLAVE_ADDRESS);
		vTaskDelay(pdMS_TO_TICKS(I2C_DELAY));

		data[0] = WM8731_REG_SAMPLING_CTRL;
		data[1] = _WM8731_SAMPLING;
		wm8731_sucess = freertos_i2c_transmit(WM8731_i2c_config.i2c_number, data , 2, WM8731_SLAVE_ADDRESS);
		vTaskDelay(pdMS_TO_TICKS(I2C_DELAY));


	}
	return wm8731_sucess;
}

uint8_t aux_data[2] = {0};

void wm8731_play_audio(void)
{

	/* Deactive module*/
	aux_data[0] = WM8731_REG_ACTIVE_CTRL;
	aux_data[1] = _WM8731_DEACTIVATE;
	freertos_i2c_transmit(WM8731_i2c_config.i2c_number, aux_data , 2, WM8731_SLAVE_ADDRESS);
	vTaskDelay(pdMS_TO_TICKS(I2C_DELAY));
}


void wm8731_SamplingAudio(void)
{

	/* Set i2s interface*/
	aux_data[0] = WM8731_REG_DIGITAL_INTERFACE;
	aux_data[1] = 0x12;
	freertos_i2c_transmit(WM8731_i2c_config.i2c_number, aux_data , 2, WM8731_SLAVE_ADDRESS);
	vTaskDelay(pdMS_TO_TICKS(I2C_DELAY));
	/* Activate module*/

	aux_data[0] = WM8731_REG_ACTIVE_CTRL;
	aux_data[1] = _WM8731_ACTIVATE;
	freertos_i2c_transmit(WM8731_i2c_config.i2c_number, aux_data , 2, WM8731_SLAVE_ADDRESS);
	vTaskDelay(pdMS_TO_TICKS(I2C_DELAY));

}

