/*! ----------------------------------------------------------------------------
 * @file    port.h
 * @brief   HW specific definitions and functions for portability
 *
 * @attention
 *
 * Copyright 2015 - 2021 (c) DecaWave Ltd, Dublin, Ireland.
 *
 * All rights reserved.
 *
 * @author DecaWave
 */

#ifndef PORT_H_
#define PORT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <boards.h>
#include <sdk_config.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include "deca_spi.h"
#include <nrf_delay.h>
#include <nrf_drv_gpiote.h>
#include <nrf_error.h>

/* ENABLE_USB_PRINT Macro is uncommented then Segger RTT Print will be enabled*/
#define ENABLE_USB_PRINT

/* DW IC IRQ handler type. */
typedef void (*port_dwic_isr_t)(void);

/*****************************************************************************************************************/ /*
                                                                                                                        **/

/****************************************************************************
    *
    *                                 Types definitions
    *
    *******************************************************************************/

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

/* @fn    Sleep
    * @brief Sleep delay in ms using SysTick timer
    * */
void Sleep(uint32_t x);

/* @fn    peripherals_init
    * No perifpherals used in this port.
    * */
int peripherals_init(void);

/* @fn    gpio_init
 * @brief Initialises the GPIOs of nRF52840-DK board
 * */
void gpio_init(void);

/* @fn      reset_DW IC
    * @brief   DW_RESET pin on DW IC has 2 functions
    *          In general it is output, but it also can be used to reset the digital
    *          part of DW IC by driving this pin low.
    *          Note, the DW_RESET pin should not be driven high externally.
    * */
void reset_DWIC(void);

/*! ------------------------------------------------------------------------------------------------------------------
    * @fn wakeup_device_with_io()
    *
    * @brief This function wakes up the device by toggling io with a delay.
    *
    * input None
    *
    * output -None
    *
    */
void wakeup_device_with_io(void);

/*! ------------------------------------------------------------------------------------------------------------------
    * @fn make_very_short_wakeup_io()
    *
    * @brief This will toggle the wakeup pin for a very short time. The device should not wakeup
    *
    * input None
    *
    * output -None
    *
    */
void make_very_short_wakeup_io(void);

/* @fn      process_deca_irq
    * @brief   main call-back for processing of DW3000 IRQ
    *          it re-enters the IRQ routing and processes all events.
    *          After processing of all events, DW3000 will clear the IRQ line.
    * */
void process_deca_irq(void);

/* @fn      port_DisableEXT_IRQ
    * @brief   wrapper to disable DW_IRQ pin IRQ
    * */
void port_DisableEXT_IRQ(void);

/* @fn      port_EnableEXT_IRQ
    * @brief   wrapper to enable DW_IRQ pin IRQ
    * */
void port_EnableEXT_IRQ(void);

/* @fn      port_GetEXT_IRQStatus
    * @brief   wrapper to read a DW_IRQ pin IRQ status
    * */
uint32_t port_GetEXT_IRQStatus(void);

/* @fn      port_CheckEXT_IRQ
    * @brief   wrapper to read DW_IRQ input pin state
    * */
uint32_t port_CheckEXT_IRQ(void);

/* @fn      dw_irq_init
    * @brief   wrapper to configure IRQ
    * */
void dw_irq_init(void);

/*! ------------------------------------------------------------------------------------------------------------------
    * @fn port_set_dwic_isr()
    *
    * @brief This function is used to install the handling function for DW IC IRQ.
    *
    * NOTE:
    *   - The user application shall ensure that a proper handler is set by calling this function before any DW IC IRQ occurs.
    *   - This function deactivates the DW IC IRQ line while the handler is installed.
    *
    * @param deca_isr function pointer to DW IC interrupt handler to install
    *
    * @return none
    */
void port_set_dwic_isr(port_dwic_isr_t dwic_isr);

#ifdef __cplusplus
}
#endif

#endif /* PORT_H_ */
