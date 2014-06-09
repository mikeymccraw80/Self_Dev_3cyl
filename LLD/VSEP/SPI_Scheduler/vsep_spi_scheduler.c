#include "io_type.h"
#include "vsep_spi_scheduler.h"
#include "dd_vsep_msg_config.h"
#include "dd_vsep.h"
#include "hal_eng.h"

extern const SPI_Message_Definition_T * VSEP_MESSAGE[VSEP_MESSAGE_MAX+7];
extern const SPI_Message_Definition_T VSEP_SOH_STATUS_MESSAGE_DEFINITION;
extern const SPI_Message_Definition_T VSEP_PWM_MESSAGE_DEFINITION[8];
extern const SPI_Message_Definition_T VSEP_PCH_MESSAGE_DEFINITION;
extern const SPI_Message_Definition_T VSEP_FAULT_MESSAGE_DEFINITION;

typedef struct
{
    bitfield8_t Number_Of_Periodical_Messages : 7;
    bitfield8_t Running                       : 1;
}SPI_SCHEDULER_DATA_T;

static SPI_SCHEDULER_DATA_T SPI_SCHEDULER_Data = { 0, 0 };

static SPI_Message_Queue_T msg_queue_soh = {
    &VSEP_SOH_STATUS_MESSAGE_DEFINITION,
    10,
};

static SPI_Message_Queue_T msg_queue_pwm1 = {
    &VSEP_PWM_MESSAGE_DEFINITION[0],
    10,
};

static SPI_Message_Queue_T msg_queue_pwm2 = {
    &VSEP_PWM_MESSAGE_DEFINITION[1],
    10,
};

static SPI_Message_Queue_T msg_queue_pwm3 = {
    &VSEP_PWM_MESSAGE_DEFINITION[2],
    10,
};

static SPI_Message_Queue_T msg_queue_pwm4 = {
    &VSEP_PWM_MESSAGE_DEFINITION[3],
    10,
};

static SPI_Message_Queue_T msg_queue_pwm5 = {
    &VSEP_PWM_MESSAGE_DEFINITION[4],
    10,
};

static SPI_Message_Queue_T msg_queue_pwm6 = {
    &VSEP_PWM_MESSAGE_DEFINITION[5],
    10,
};

static SPI_Message_Queue_T msg_queue_pwm7 = {
    &VSEP_PWM_MESSAGE_DEFINITION[6],
    10,
};

static SPI_Message_Queue_T msg_queue_pwm8 = {
    &VSEP_PWM_MESSAGE_DEFINITION[7],
    10,
};

static SPI_Message_Queue_T msg_queue_pch_mpio = {
    &VSEP_PCH_MESSAGE_DEFINITION,
    10,
};

static SPI_Message_Queue_T msg_queue_fault = {
    &VSEP_FAULT_MESSAGE_DEFINITION,
    10,
};

static LIST_HEAD(msg_queue);


//=============================================================================
// SPI_SCHEDULER_Initialize
//=============================================================================
void VSEP_SPI_SCHEDULER_Initialize(void)
{
    SPI_SCHEDULER_Data.Number_Of_Periodical_Messages     = 0;
    SPI_SCHEDULER_Data.Running                           = false;

    VSEP_SPI_SCHEDULER_Set_Enable( true );

    list_add(&msg_queue_soh.list, &msg_queue);
    list_add(&msg_queue_pwm1.list, &msg_queue);
    list_add(&msg_queue_pwm2.list, &msg_queue);
    list_add(&msg_queue_pwm3.list, &msg_queue);
    list_add(&msg_queue_pwm4.list, &msg_queue);
    list_add(&msg_queue_pwm5.list, &msg_queue);
    list_add(&msg_queue_pwm6.list, &msg_queue);
    list_add(&msg_queue_pwm7.list, &msg_queue);
    list_add(&msg_queue_pwm8.list, &msg_queue);
    list_add(&msg_queue_pch_mpio.list, &msg_queue);
    list_add(&msg_queue_fault.list, &msg_queue);
}

//=============================================================================
// SPI_SCHEDULER_Set_Enable
//=============================================================================
 bool VSEP_SPI_SCHEDULER_Set_Enable( bool in_enable)
{
	bool previous_status = (bool)(SPI_SCHEDULER_Data.Running);

	SPI_SCHEDULER_Data.Running = in_enable;

	return previous_status;
}

//=============================================================================
// SPI_SCHEDULER_Get_Status
//=============================================================================
bool VSEP_SPI_SCHEDULER_Get_Status( void )
{
	return (bool)(SPI_SCHEDULER_Data.Running);
}

//=============================================================================
// VSEP_SPI_SCHEDULER_10MS
//=============================================================================
void VSEP_SPI_SCHEDULER_10MS(void)
{
    struct list_head *pos;
    SPI_Message_Queue_T *q;
    uint32_t cs;

    list_for_each(pos, &msg_queue) {
        q = list_entry(pos, SPI_Message_Queue_T, list);
        q -> time += 10;
        if ((q->time >= q->interval) && SPI_SCHEDULER_Data.Running){
            q->time = 0;
            cs = Enter_Critical_Section();
            VSEP_SPI_Port_Transfer(q->spi_msg);
            Leave_Critical_Section(cs);
        }
    }
}
