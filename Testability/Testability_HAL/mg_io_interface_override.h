#ifndef MG_IO_INTERFACE_OVERRIDE_H
#define MG_IO_INTERFACE_OVERRIDE_H

#include "discrete.h"
#include "Pulse_width_modulation.h"
#include "com_sci_port.h"


extern const IO_Discrete_T MG_MTSA_D_OUT_EST1;
extern const IO_Discrete_T MG_MTSA_D_OUT_ESTSYNC;

extern const IO_Discrete_T MG_MTSA_D_OUT_INJ1;
extern const IO_Discrete_T MG_MTSA_D_OUT_INJ2;
extern const IO_Discrete_T MG_MTSA_D_OUT_INJ3;
extern const IO_Discrete_T MG_MTSA_D_OUT_INJ4;

extern const IO_Input_Capture_T MG_MTSA_IC_VSS;
extern const IO_Input_Capture_T MG_MTSA_IC_ENS;
extern const IO_Input_Capture_T MG_MTSA_IC_58XPOS;
extern const IO_Input_Capture_T MG_MTSA_IC_CAM1;
extern const IO_Input_Capture_T MG_MTSA_IC_CAM2;

extern const IO_Pulse_Width_Modulation_With_Fault_T MG_MTSA_PWM_FUEL_CONSUM;
extern const IO_Pulse_Width_Modulation_T MG_MTSA_PWM_ETCCTLPWM;
extern const IO_Pulse_Width_Modulation_T MG_MTSA_PWM_FP_IN;

extern const IO_Discrete_T MG_MTSA_D_OUT_FPO1;
extern const IO_Discrete_T MG_MTSA_D_OUT_FPO2;
extern const IO_Discrete_T MG_MTSA_D_OUT_FPO3;
extern const IO_Discrete_T MG_MTSA_D_OUT_FPO4;
extern const IO_Discrete_T MG_MTSA_D_OUT_FPO5;
extern const IO_Discrete_T MG_MTSA_D_OUT_FPO6;
extern const IO_Discrete_T MG_MTSA_D_OUT_FPO7;



void MG_SIU_GPIO_DISCRETE_Initialize_Device_Override(void);
void MG_SIU_GPIO_PWM_Initialize_Device_Override(void);

extern void MG_Reset_SCI(const CommPort_T * in_port);
extern void MG_Init_SCI(const CommPort_T * in_port);


#endif /* end of include guard: MG_IO_INTERFACE_OVERRIDE_H */
