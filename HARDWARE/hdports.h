//////////////////////////////////////////////////////////////////////////////////////
// By Rob F. / Entire Group
//////////////////////////////////////////////////////////////////////////////////////

#ifndef __HDPORTS_H
#define __HDPORTS_H

#include "SysType.h"


#define isDefinedSTM32FXX    ( defined (STM32F10X_LD)       ||  \
                               defined (STM32F10X_LD_VL)    ||  \
                               defined (STM32F10X_MD)       ||  \
                               defined (STM32F10X_MD_VL)    ||  \
                               defined (STM32F10X_HD)       ||  \
                               defined (STM32F10X_HD_VL)    ||  \
                               defined (STM32F10X_XL)       ||  \
                               defined (STM32F10X_CL) )

#define isDefinedSTM32LXX    ( defined (STM32L1XX_MD)       ||  \
                               defined (STM32L1XX_MDP)      ||  \
                               defined (STM32L1XX_HD)       ||  \
                               defined (STM32L1XX_XL) )

#if isDefinedSTM32FXX
 #include "stm32f10x_rcc.h"
 #include "stm32f10x_gpio.h"
#else
 #include "stm32l1xx_rcc.h"
 #include "stm32l1xx_gpio.h"
#endif


#define dH_BITV(_p_, _v_)     ((u32)(_v_)<<(_p_))
#define dH_BIT(_p_)           dH_BITV((_p_), 1)
#define dH_PORT_BSSR(_p_, _v_)  dH_BITV(_p_, _v_) | dH_BIT((_p_) | 16)

#define dH_PORT_BSSR_R(_p_)  dH_BIT((_p_) | 16)
#define dH_PORT_BSSR_S(_p_)  dH_BIT((_p_))
#define dH_PORT_CFG_MD(_name_, _p_, _v_)  _name_ = (_name_ & (~( 0xF<<(4*(_p_) ))) ) | ((u32)(_v_)<<(4*(_p_)))

#define hdPin_O_DefineSetup(_name, _port, _pin, _mode, _def)                                                                                                  \
hdPin_Define(_name, _port, _pin, _mode);                                                                                                                      \
static __forceinline void GpioInit_##_name(void) { hdGPIO_Setup((GPIO_TypeDef *)_name##wp_port, _name##wp_pin, _name##wp_mode, _def); }                       \

#define hdPin_Define(_name, _port, _pin, _mode)                                                                                             \
enum { _name##wp_port         = (u32)(GPIO##_port)        ,                                                                                 \
       _name##wp_pin          = (u32)(_pin)               ,                                                                                 \
       _name##wp_bit          = (s32)(dH_BIT(_pin))       ,                                                                                 \
       _name##wp_mode         = (u16)(_mode)              ,                                                                                 \
}

#if isDefinedSTM32FXX
  #define GPIO_PortWrite(_port,_pin,_v)     uu32(((GPIO_TypeDef *)(void *)_port)->BSRR) = dH_PORT_BSSR((_pin),(_v))
#else
  #define GPIO_PortWrite(_port,_pin,_v)     uu32(((GPIO_TypeDef *)(void *)_port)->BSRRL) = dH_PORT_BSSR((_pin),(_v))
#endif  
#define dH_PORT_Write(_name,_v)           GPIO_PortWrite(_name##wp_port, (_name##wp_pin), (_v))

#define GPIO_PortRead(_port,_pin)         ((uu16(((GPIO_TypeDef *)(void *)_port)->IDR)>>(_pin))&1)
#define dH_PORT_Read(_name)               GPIO_PortRead(_name##wp_port, (_name##wp_pin))

#define dHmPRTN(_n, _o, _v)       dHmPRT_##_n = (u16)((u16)(_v))<<((_o)*4)
#define dHmPRT(_o, _v)            dHmPRTN(_v, _o, _v)

#if isDefinedSTM32FXX
  enum{

    
    GPIO_OType_PP     = 0,
    GPIO_OType_OD     = 1,
    
    GPIO_Mode_AN      = 0,
    GPIO_Mode_IN      = 2,
    GPIO_Mode_OUT     = 0,
    GPIO_Mode_AF      = 2,
    
    GPIO_PuPd_NOPULL  = 0,
    GPIO_PuPd_UP      = 3,
    GPIO_PuPd_DOWN    = 2,

    dHmPRT(0, GPIO_Mode_IN),
    dHmPRT(0, GPIO_Mode_OUT),     //+speed mhz
    dHmPRT(0, GPIO_Mode_AF),      //+speed mhz
    dHmPRT(0, GPIO_Mode_AN),
  //CNF0
    dHmPRT(0, GPIO_OType_PP),
    dHmPRT(0, GPIO_OType_OD),
    
    dHmPRT(1, GPIO_Speed_2MHz),
    dHmPRT(1, GPIO_Speed_10MHz),
    dHmPRT(1, GPIO_Speed_50MHz),
    
    dHmPRT(2, GPIO_PuPd_NOPULL),
    dHmPRT(2, GPIO_PuPd_UP),
    dHmPRT(2, GPIO_PuPd_DOWN),
  };
  enum {
    hd_gptp_IN_OD     = dHmPRT_GPIO_Mode_AN  | dHmPRT_GPIO_OType_OD | dHmPRT_GPIO_PuPd_NOPULL                               ,
    hd_gptp_IN_PPU    = dHmPRT_GPIO_Mode_IN  | dHmPRT_GPIO_OType_PP | dHmPRT_GPIO_PuPd_UP                                   ,
    hd_gptp_IN_PPD    = dHmPRT_GPIO_Mode_IN  | dHmPRT_GPIO_OType_PP | dHmPRT_GPIO_PuPd_DOWN                                 ,
    hd_gptp_OUT_OD    = dHmPRT_GPIO_Mode_OUT | dHmPRT_GPIO_OType_OD | dHmPRT_GPIO_PuPd_NOPULL   | dHmPRT_GPIO_Speed_50MHz   ,
    hd_gptp_OUT_PP    = dHmPRT_GPIO_Mode_OUT | dHmPRT_GPIO_OType_PP                             | dHmPRT_GPIO_Speed_50MHz   ,
    hd_gptp_OUT_PPU   = dHmPRT_GPIO_Mode_OUT | dHmPRT_GPIO_OType_PP | dHmPRT_GPIO_PuPd_UP       | dHmPRT_GPIO_Speed_50MHz   ,
    hd_gptp_OUT_PPD   = dHmPRT_GPIO_Mode_OUT | dHmPRT_GPIO_OType_PP | dHmPRT_GPIO_PuPd_DOWN     | dHmPRT_GPIO_Speed_50MHz   ,
    hd_gptp_AF_OD     = dHmPRT_GPIO_Mode_AF  | dHmPRT_GPIO_OType_OD | dHmPRT_GPIO_PuPd_NOPULL   | dHmPRT_GPIO_Speed_50MHz   ,
    hd_gptp_AF_PPU    = dHmPRT_GPIO_Mode_AF  | dHmPRT_GPIO_OType_PP | dHmPRT_GPIO_PuPd_UP       | dHmPRT_GPIO_Speed_50MHz   ,
    hd_gptp_AF_PPD    = dHmPRT_GPIO_Mode_AF  | dHmPRT_GPIO_OType_PP | dHmPRT_GPIO_PuPd_DOWN     | dHmPRT_GPIO_Speed_50MHz   ,
    hd_gptp_FFFFFFFF  = (u16)0xFFFF,
  };
#else
  enum{
    dHmPRT(0, GPIO_Mode_IN),
    dHmPRT(0, GPIO_Mode_OUT),
    dHmPRT(0, GPIO_Mode_AF),
    dHmPRT(0, GPIO_Mode_AN),

    dHmPRT(1, GPIO_OType_PP),
    dHmPRT(1, GPIO_OType_OD),

    dHmPRT(2, GPIO_Speed_400KHz),
    dHmPRT(2, GPIO_Speed_2MHz),
    dHmPRT(2, GPIO_Speed_10MHz),
    dHmPRT(2, GPIO_Speed_40MHz),

    dHmPRT(3, GPIO_PuPd_NOPULL),
    dHmPRT(3, GPIO_PuPd_UP),
    dHmPRT(3, GPIO_PuPd_DOWN),
  };
  enum {
    hd_gptp_IN_OD     = dHmPRT_GPIO_Mode_IN  | dHmPRT_GPIO_OType_OD | dHmPRT_GPIO_PuPd_NOPULL                               ,
    hd_gptp_IN_PPU    = dHmPRT_GPIO_Mode_IN  | dHmPRT_GPIO_OType_PP | dHmPRT_GPIO_PuPd_UP                                   ,
    hd_gptp_IN_PPD    = dHmPRT_GPIO_Mode_IN  | dHmPRT_GPIO_OType_PP | dHmPRT_GPIO_PuPd_DOWN                                 ,
    hd_gptp_OUT_OD    = dHmPRT_GPIO_Mode_OUT | dHmPRT_GPIO_OType_OD | dHmPRT_GPIO_PuPd_NOPULL                               ,
    hd_gptp_OUT_PP    = dHmPRT_GPIO_Mode_OUT | dHmPRT_GPIO_OType_PP                             | dHmPRT_GPIO_Speed_40MHz   ,
    hd_gptp_OUT_PPU   = dHmPRT_GPIO_Mode_OUT | dHmPRT_GPIO_OType_PP | dHmPRT_GPIO_PuPd_UP                                   ,
    hd_gptp_OUT_PPD   = dHmPRT_GPIO_Mode_OUT | dHmPRT_GPIO_OType_PP | dHmPRT_GPIO_PuPd_DOWN                                 ,
    hd_gptp_AF_OD     = dHmPRT_GPIO_Mode_AF  | dHmPRT_GPIO_OType_OD | dHmPRT_GPIO_PuPd_NOPULL   | dHmPRT_GPIO_Speed_40MHz   ,
    hd_gptp_AF_PPU    = dHmPRT_GPIO_Mode_AF  | dHmPRT_GPIO_OType_PP | dHmPRT_GPIO_PuPd_UP       | dHmPRT_GPIO_Speed_40MHz   ,
    hd_gptp_AF_PPD    = dHmPRT_GPIO_Mode_AF  | dHmPRT_GPIO_OType_PP | dHmPRT_GPIO_PuPd_DOWN     | dHmPRT_GPIO_Speed_40MHz   ,
    hd_gptp_FFFFFFFF  = (u16)0xFFFF,
  };
#endif


//////////////////////////////////////////////////////////////////////
extern void hdGPIO_Setup(GPIO_TypeDef* GPIOx, u8 pin, u16 mode, u8 def);
//////////////////////////////////////////////////////////////////////


#endif
