#ifndef MG_HAL_FAULT_H
#define MG_HAL_FAULT_H

/*----------------------------------------------------------------------------*/
/*   Declear of Complex IO Channel Maximom                                              */
/*----------------------------------------------------------------------------*/
extern const uint8_t MG_COMPLEXIO_CHANNEL_MAX;

/*----------------------------------------------------------------------------*/
/*   Declear of Complex IO Fault Value                                              */
/*----------------------------------------------------------------------------*/
extern const uint8_t MG_COMPLEXIO_FAULT_OPEN;
extern const uint8_t MG_COMPLEXIO_FAULT_SHORT_TO_GROUND;
extern const uint8_t MG_COMPLEXIO_FAULT_SHORT_TO_BATTERY;

void mg_HAL_Fault_ETC_Open_Test_Configure(void);
void mg_HAL_Fault_ETC_STB_STG_Test_Configure(void);
void mg_HAL_Fault_ETC_Over_Current_Test_Configure(uint8_t slew_rate);
void mg_HAL_ComplexIO_Fault_Read(void);
void mg_HAL_PowerDevice_Fault_Read(void);
void mg_HAL_ETC_Fault_Read(void);
void mg_HAL_BARO_Fault_Read(void);
void mg_HAL_ComplexIO_Fault_Clear(void);
void mg_HAL_PowerDevice_Fault_Clear(void);
void mg_HAL_ETC_Fault_Clear(void);
void mg_HAL_BARO_Fault_Clear(void);
uint8_t mg_HAL_ComplexIO_Fault_Get(uint8_t index);
uint8_t mg_HAL_PowerDevice_Fault_Get(uint8_t index);
uint8_t mg_HAL_ETC_Fault_Get(uint8_t index);
uint8_t mg_HAL_BARO_Fault_Get(uint8_t index);

#endif
