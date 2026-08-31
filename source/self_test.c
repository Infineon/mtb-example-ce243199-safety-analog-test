/******************************************************************************
* File Name:   self_test.c
*
* Description: This file provides the helper functions for executing
*              safety self-tests for XMC5000 MCUs.
*
*              Implements SAR ADC self-test using the internal bandgap (VBG)
*              reference channel for normalization.
*
* Related Document: See README.md
*
*
*******************************************************************************
* $ Copyright 2026 Infineon Technologies AG $
*******************************************************************************/

#include "cybsp.h"
#include "cy_retarget_io.h"
#include "self_test.h"


/*******************************************************************************
* Global Variables
*******************************************************************************/

/*******************************************************************************
* Function Name: adc_test
********************************************************************************
* Summary:
* Performs the SAR ADC self-test using the on-board potentiometer as
* the analog input. Channel 0 is routed to the potentiometer (CYBSP_POT, P6.0)
* and channel 1 is routed to the internal bandgap voltage reference (VBG, ~900 mV).
* The library normalises the potentiometer reading against the VBG reading:
*   adc_res = (ch0_counts * 900) / ch1_counts  → result in mV
* The test passes when the normalised result is within the accuracy window of
* 900 mV. Adjust the potentiometer to ~900 mV before running.
*
* Parameters:
*  none
*
* Return:
*  void
*
*******************************************************************************/
void adc_test(void)
{
    printf("Running ADC Safety test: Expected input voltage is ~900 mV.\r\n");
    if (OK_STATUS != SelfTests_ADC(USER_ADC_HW, 0x00u, ANALOG_ADC_SAR_RESULT_BG,
            ANALOG_ADC_ACURACCY, VBG_CHANNEL, 1))
    {
        printf("Error: ADC Safety test failed.\r\n");
    }
    else
    {
        printf("SUCCESS: ADC Safety test passed.\r\n");
    }
}

/* [] END OF FILE */
