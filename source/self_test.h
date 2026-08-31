/******************************************************************************
* File Name:   self_test.h
*
* Description: This file is the public interface of self_test.c source file.
*
*
* Related Document: See README.md
*
*
*******************************************************************************
* $ Copyright 2026 Infineon Technologies AG $
*******************************************************************************/

/*******************************************************************************
* Include guard
*******************************************************************************/
#ifndef SELF_TEST_H_
#define SELF_TEST_H_

#include "SelfTest.h"

/*******************************************************************************
* Global Variables
*******************************************************************************/

/*******************************************************************************
* Macros
*******************************************************************************/
/* Expected voltage in mV */
#define ANALOG_ADC_SAR_RESULT_BG    (900)

/* Channel 1 is the VBG normalizer channel (isGroupEnd=true).
 * SelfTests_ADC waits for GRP_DONE on this channel and uses its result
 * to normalise the channel 0 reading: adc_res = (ch0 * 900) / ch1. */
#define VBG_CHANNEL    (1u)

/*******************************************************************************
* Function Prototypes
*******************************************************************************/
void adc_test(void);

#endif /* SELF_TEST_H_ */

/* [] END OF FILE */
