#ifndef IO_INTERFACE_ETC_H
#define IO_INTERFACE_ETC_H

//=============================================================================
// IO_ETC_Init, called in hal os
//=============================================================================
void IO_ETC_Init(void);

//=============================================================================
// IO_ETC_Update_1msTimeBase, called in 1ms TimeBase
//=============================================================================
void IO_ETC_Update_1msTimeBase(void);

//=============================================================================
// IO_ETC_PWM_INT_Handler, called in etc pwm match B interrupt
//=============================================================================
void IO_ETC_PWM_INT_Handler(void);

#endif
