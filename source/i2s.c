/*
 * i2s.c
 *
 *  Created on: Nov 28, 2020
 *      Author: Momo
 */
#include "i2s.h"

static  sai_transceiver_t config;
sai_master_clock_t mclkConfig;

void I2S_init()
{
	SAI_Init(DEMO_SAI);

	/*Check if DMA should be included here*/

	/* I2S mode configurations */
	SAI_GetClassicI2SConfig(&config, DEMO_AUDIO_BIT_WIDTH, kSAI_Stereo, 1U << DEMO_SAI_CHANNEL);
	config.syncMode    = DEMO_SAI_TX_SYNC_MODE;
	config.masterSlave = DEMO_SAI_MASTER_SLAVE;

	/* set bit clock divider */
	SAI_TxSetBitClockRate(DEMO_SAI, DEMO_AUDIO_MASTER_CLOCK, DEMO_AUDIO_SAMPLE_RATE, DEMO_AUDIO_BIT_WIDTH,
	  DEMO_AUDIO_DATA_CHANNEL);

	/*Rx Config*/
	config.syncMode = DEMO_SAI_RX_SYNC_MODE;
	SAI_RxSetConfig(DEMO_SAI, &config);
	SAI_RxSetBitClockRate(DEMO_SAI, DEMO_AUDIO_MASTER_CLOCK, DEMO_AUDIO_SAMPLE_RATE, DEMO_AUDIO_BIT_WIDTH,
			DEMO_AUDIO_DATA_CHANNEL);

	/*Master Clock Config*/
	mclkConfig.mclkOutputEnable = true, mclkConfig.mclkHz = DEMO_AUDIO_MASTER_CLOCK;
	mclkConfig.mclkSourceClkHz = DEMO_SAI_CLK_FREQ;
	SAI_SetMasterClockConfig(DEMO_SAI, &mclkConfig);

}

void I2S_stopTransfer()
{
	/* Once transfer finish, disable SAI instance. */
	/* DEINIT THE I2S*/
	SAI_Deinit(DEMO_SAI);
}


