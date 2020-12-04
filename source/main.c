#include <stdio.h>
#include <wm8731.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK66F18.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include "freertos_i2c.h"
#include "task.h"
#include "semphr.h"
#include "fsl_uart.h"
#include "filters.h"

/* TODO: insert other definitions and declarations here. */
/*
 * @brief   Application entry point.
 */
#define DEMO_UART_CLK_FREQ CLOCK_GetFreq(SYS_CLK)
#define DEMO_UART          UART0
#define DATA_SIZE		   3U

SemaphoreHandle_t i2c_sem;

const char * enable_LP = "LPE";
const char * disable_LP = "LPD";
const char * enable_HP = "HPE";
const char * disable_HP = "HPD";
const char * enable_BP = "BPE";
const char * disable_BP ="BPD";
static uint32_t Buffer[4 * 1024];
static uint32_t rxBuffer = 0;
static char filter_data[DATA_SIZE];
static uart_config_t config;

void init_codec(void *parameters)
{
	uint8_t g_codec_sucess = freertos_i2c_fail;
	g_codec_sucess = wm8731_init();
	if(freertos_i2c_sucess == g_codec_sucess)
	{
		PRINTF("Codec configured\n\r");
	}
	wm8731_i2s_config();
	//wm8731_Activate();
	init_Buffer(&Buffer[0]);

	xSemaphoreGive(i2c_sem);

	vTaskSuspend(NULL);
}

void codec_audio(void *parameters)
{
	xSemaphoreTake(i2c_sem, portMAX_DELAY);

	for(;;)
	{
		wm8731_getData((uint8_t*) (Buffer+rxBuffer), 1024);
		rxBuffer++;
		if(rxBuffer>= 4)
		{
			rxBuffer = 0U;
		}
		vTaskDelay(pdMS_TO_TICKS(300));
	}
}

void init_uart(void *parameters)
{
	uint8_t txbuff[] = "Codec audio practice 4\r\nChoose your filter\r\n\r\nLow pass (LP)\n\rHigh pass (HP)\n\rBand Pass (BP)\r\n";
	uint8_t index;
	uint8_t ch;

	UART_GetDefaultConfig(&config);

	config.baudRate_Bps = 115200;
	config.enableTx     = true;
	config.enableRx     = true;

	UART_Init(DEMO_UART, &config, DEMO_UART_CLK_FREQ);
	UART_WriteBlocking(DEMO_UART, txbuff, sizeof(txbuff) - 1);

	while(1)
	{
		index = 0;
		/* Tomar datos de la uart*/
		do{
			UART_ReadBlocking(DEMO_UART, &ch, 1);
			UART_WriteBlocking(DEMO_UART,&ch, 1);
			filter_data[index] = ch;
			index++;
		} while(3 > DATA_SIZE);

		if(strcmp(enable_LP,filter_data))
		{
			do_filter(LP);
		}
		else if(strcmp(enable_HP,filter_data))
		{
			do_filter(HP);
		}
		else if(strcmp(enable_BP,filter_data))
		{
			do_filter(BP);
		}
		else if(strcmp(disable_LP,filter_data) || strcmp(disable_HP,filter_data) || strcmp(disable_BP,filter_data))
		{
			do_filter(DISABLE);
		}
		UART_WriteBlocking(DEMO_UART,"\r   \r", 5);
	}

}

int main(void)
{
	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
#endif

	i2c_sem = xSemaphoreCreateBinary();

	xTaskCreate(init_codec, "init_codec", 110, NULL, 1, NULL);
	xTaskCreate(codec_audio, "codec_audio", 110, NULL, 1, NULL);
	xTaskCreate(init_uart, "init_uart", 110, NULL, 1, NULL);

	vTaskStartScheduler();

	while(1)
	{

	}
	return 0 ;
}
