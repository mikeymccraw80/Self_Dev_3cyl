#include "io_type.h"
#include "vsep_spi_scheduler.h"


typedef struct
{
    bitfield8_t Number_Of_Periodical_Messages : 7;
    bitfield8_t Running                       : 1;
}SPI_SCHEDULER_DATA_T;

static SPI_SCHEDULER_DATA_T SPI_SCHEDULER_Data = { 0, 0 };

static SPI_Message_Queue_T msg_queue_soh = {
    .spi_msg = &VSEP_MESSAGE[VSEP_MESSAGE_SOH_STATUS],
    .interval = 10,
};

static SPI_Message_Queue_T msg_queue_pwm1 = {
    .spi_msg = &VSEP_MESSAGE[VSEP_MESSAGE_PWM + 0],
    .interval = 10,
};

static SPI_Message_Queue_T msg_queue_pwm2 = {
    .spi_msg = &VSEP_MESSAGE[VSEP_MESSAGE_PWM + 1],
    .interval = 10,
};

static SPI_Message_Queue_T msg_queue_pwm3 = {
    .spi_msg = &VSEP_MESSAGE[VSEP_MESSAGE_PWM + 2],
    .interval = 10,
};

static SPI_Message_Queue_T msg_queue_pwm4 = {
    .spi_msg = &VSEP_MESSAGE[VSEP_MESSAGE_PWM + 3],
    .interval = 10,
};

static SPI_Message_Queue_T msg_queue_pwm5 = {
    .spi_msg = &VSEP_MESSAGE[VSEP_MESSAGE_PWM + 4],
    .interval = 10,
};

static SPI_Message_Queue_T msg_queue_pwm6 = {
    .spi_msg = &VSEP_MESSAGE[VSEP_MESSAGE_PWM + 5],
    .interval = 10,
};

static SPI_Message_Queue_T msg_queue_pwm7 = {
    .spi_msg = &VSEP_MESSAGE[VSEP_MESSAGE_PWM + 6],
    .interval = 10,
};

static SPI_Message_Queue_T msg_queue_pwm8 = {
    .spi_msg = &VSEP_MESSAGE[VSEP_MESSAGE_PWM + 7],
    .interval = 10,
};

static SPI_Message_Queue_T msg_queue_pch_mpio = {
    .spi_msg = &VSEP_MESSAGE[VSEP_MESSAGE_PCH_MPIO],
    .interval = 10,
};

static SPI_Message_Queue_T msg_queue_fault = {
    .spi_msg = &VSEP_MESSAGE[VSEP_MESSAGE_FAULT],
    .interval = 10,
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

    list_add(&msg_queue_soh.list, &can_queue);
    list_add(&msg_queue_pwm1.list, &can_queue);
    list_add(&msg_queue_pwm2.list, &can_queue);
    list_add(&msg_queue_pwm3.list, &can_queue);
    list_add(&msg_queue_pwm4.list, &can_queue);
    list_add(&msg_queue_pwm5.list, &can_queue);
    list_add(&msg_queue_pwm6.list, &can_queue);
    list_add(&msg_queue_pwm7.list, &can_queue);
    list_add(&msg_queue_pwm8.list, &can_queue);
    list_add(&msg_queue_pch_mpio.list, &can_queue);
    list_add(&msg_queue_fault.list, &can_queue);
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
    struct can_queue_s *q;
    time_t over_time;

    list_for_each(pos, &msg_queue) {
        q = list_entry(pos, SPI_Message_Queue_T, list);
        q -> time += 10;
        if ((q->time > q->interval) & SPI_SCHEDULER_Data.Running){
            q->time = 0;
            VSEP_SPI_Port_Transfer( q->spi_msg);
        }
    }
}
