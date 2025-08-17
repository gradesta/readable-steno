#ifndef _TUSB_CONFIG_H_
#define _TUSB_CONFIG_H_

// Common configuration
#define CFG_TUSB_MCU              OPT_MCU_RP2040
#ifndef CFG_TUSB_OS
    #define CFG_TUSB_OS   OPT_OS_NONE
#endif
#define CFG_TUSB_RHPORT0_MODE     (OPT_MODE_DEVICE | OPT_MODE_FULL_SPEED)
#define CFG_TUSB_MEM_SECTION
#define CFG_TUSB_MEM_ALIGN        __attribute__ ((aligned(4)))

// Device configuration
#define CFG_TUD_ENDPOINT0_SIZE    64

// ------------ CDC ------------- //
#define CFG_TUD_CDC               1   // Enable CDC interface
#define CFG_TUD_CDC_RX_BUFSIZE    64
#define CFG_TUD_CDC_TX_BUFSIZE    64
#define CFG_TUD_CDC_EP_BUFSIZE    64   // Endpoint size

#endif