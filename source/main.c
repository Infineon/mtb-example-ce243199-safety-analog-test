/******************************************************************************
* File Name:   main.c
*
* Description: This is the source code for the MTB STL Safety Analog Test
*              for XMC5000 MCUs.
*
*              Runs the SAR ADC self-test once at startup using the
*              internal bandgap (VBG ~900 mV) as reference, prints the result,
*              and halts.
*
* Related Document: See README.md
*
*
*******************************************************************************
* $ Copyright 2026 Infineon Technologies AG $
*******************************************************************************/

/*******************************************************************************
* Header Files
*******************************************************************************/
#include "cybsp.h"
#include "cy_pdl.h"
#include "mtb_hal.h"
#include "cy_retarget_io.h"
#include "self_test.h"

/******************************************************************************
* Global Variables
*******************************************************************************/
/* For the Retarget-IO (Debug UART) usage */
static cy_stc_scb_uart_context_t  DEBUG_UART_context;   /* Debug UART context */
static mtb_hal_uart_t DEBUG_UART_hal_obj;               /* Debug UART HAL object */

/*******************************************************************************
* Function Definitions
*******************************************************************************/

/*******************************************************************************
* Function Name: main
*********************************************************************************
* Summary:
* This is the main function. It does...
*    1. Initialize the device and board peripherals and retarget-io for prints
*    2. Initialize the SAR ADC and enable the EPASS reference buffer
*    3. Run the ADC self-test once
*    4. Print PASS/FAIL result and halt
*
* Parameters:
*  void
*
* Return:
*  int
*
*******************************************************************************/
int main(void)
{
    cy_rslt_t result;

    /* Initialize the device and board peripherals */
    result = cybsp_init();
    /* Board init failed. Stop program execution */
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* Initialize the debug UART */
    result = Cy_SCB_UART_Init(CYBSP_DEBUG_UART_HW, &CYBSP_DEBUG_UART_config, &DEBUG_UART_context);
    /* UART init failed. Stop program execution */
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }
    Cy_SCB_UART_Enable(CYBSP_DEBUG_UART_HW);

    /* Setup the HAL UART */
    result = mtb_hal_uart_setup(&DEBUG_UART_hal_obj, &CYBSP_DEBUG_UART_hal_config, &DEBUG_UART_context, NULL);
    /* HAL UART init failed. Stop program execution */
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* Initialize retarget-io to use the debug UART port */
    result = cy_retarget_io_init(&DEBUG_UART_hal_obj);
    /* retarget-io init failed. Stop program execution */
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* Initialize ADC */
    if(CY_SAR2_SUCCESS != Cy_SAR2_Init(USER_ADC_HW, &USER_ADC_config))
    {
        CY_ASSERT(0);
    }

    /* Enable EPASS reference buffer — mandatory for internal VBG channel */
    Cy_SAR2_SetReferenceBufferMode(PASS0_EPASS_MMIO, CY_SAR2_REF_BUF_MODE_ON);

    /* Enable global interrupts */
    __enable_irq();

    /* \x1b[2J\x1b[;H - ANSI ESC sequence for clear screen */
    printf("\x1b[2J\x1b[;H");

    printf("****************** "
           "MTB STL: ADC Safety Test"
           "****************** \r\n\n");

    /* Run the ADC self-test once at startup */
    adc_test();

    printf("\r\nTest complete.\r\n");

    /* Halt — test is done */
    for (;;)
    {
    }
}

/* [] END OF FILE */
