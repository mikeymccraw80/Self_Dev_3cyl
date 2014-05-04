

//=============================================================================
//Include
//=============================================================================
#include "dd_spark_interface.h"



//=============================================================================
// Spark Control and Feedback (Fault Detection)
//=============================================================================
const Spark_Control_Select_T MTSA_SPARK_CONTROL_SELECT_MAP[] =
{//A                  B                  C                  D                  E                  F                  G                  H
// 
// 4 Cyl no overlapping dwell, Waste Spark
   SPARK_CONTROL_0,   SPARK_CONTROL_0,   SPARK_CONTROL_0,   SPARK_CONTROL_0
// 4 Cyl no overlapping dwell, Waste Spark
// SPARK_CONTROL_0,   SPARK_CONTROL_0,   SPARK_CONTROL_1,   SPARK_CONTROL_1
// 4 Cyl overlapping dwell, No Waste Spark
// SPARK_CONTROL_0,   SPARK_CONTROL_1,   SPARK_CONTROL_0,   SPARK_CONTROL_1
// 
// 6 Cyl no overlapping dwell, Waste Spark
// SPARK_CONTROL_0,   SPARK_CONTROL_0,   SPARK_CONTROL_0,   SPARK_CONTROL_0,   SPARK_CONTROL_0,   SPARK_CONTROL_0
// 6 Cyl overlapping dwell, No Waste Spark
// SPARK_CONTROL_0,   SPARK_CONTROL_1,   SPARK_CONTROL_0,   SPARK_CONTROL_1,   SPARK_CONTROL_0,   SPARK_CONTROL_1,
// 
// 8 Cyl no overlapping dwell, Waste Spark
// SPARK_CONTROL_0,   SPARK_CONTROL_0,   SPARK_CONTROL_0,   SPARK_CONTROL_0,   SPARK_CONTROL_1,   SPARK_CONTROL_1,   SPARK_CONTROL_1,   SPARK_CONTROL_1
// 8 Cyl overlapping dwell, No Waste Spark
// SPARK_CONTROL_0,   SPARK_CONTROL_1,   SPARK_CONTROL_0,   SPARK_CONTROL_1,   SPARK_CONTROL_0,   SPARK_CONTROL_1,   SPARK_CONTROL_0,   SPARK_CONTROL_1
};

const IO_Spark_Initialization_Parameters_T MTSA_SPARK_INITIALIZATION_PARAMETERS =
{
   (Spark_Control_Select_T *)MTSA_SPARK_CONTROL_SELECT_MAP,
   SPARK_SEQUENTIAL_MODE,
   SPARK_SELECT_MAX
};




