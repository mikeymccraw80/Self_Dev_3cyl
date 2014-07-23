#ifndef IO_CONFIG_SIU_H
#define IO_CONFIG_SIU_H

#include"dd_siu.h"
#include"io_config_qadc.h"

#define SIU_TBC_FREQUENCY_HZ  SYSTEM_FREQUENCY_HZ




//=============================================================================
// SIU_ECCR_INITIAL
//=============================================================================
//The SIU_ECCR controls the timing relationship between the system clock and the external clock
//CLKOUT. All bits and fields in the SIU_ECCR are read/write and are reset by the IP Green-Line
//asynchronous reset signal.
extern const SIU_ECCR_T SIU_INITIAL_ECCR;

extern const SIU_SYSDIV_T SIU_INITIAL_SYSDIV;

//=============================================================================
// SIU_INITIAL_DISR
//=============================================================================
//The DSPI Input Select Register (SIU_DISR) register specifies the source of each DSPI data input, slave
//select, clock input, and trigger input to allow serial and parallel chaining of the DSPI blocks.
//DSPI_B,DSPI_C
extern const SIU_DISR_T SIU_INITIAL_DISR ;

//=============================================================================
// SIU_INITIAL_ISEL3
//=============================================================================
//The SIU_ISEL3 register selects the source for the external eQADC trigger inputs.
extern const SIU_ISEL3_T SIU_ISEL3_INITIAL ;

//=============================================================================
// SIU_INITIAL_ETISR
//=============================================================================
//The eQADC Trigger Input Select Register (SIU_ETISR) selects the source for the eQADC trigger inputs.
extern const SIU_ETISR_T SIU_ETISR_INITIAL;


//=============================================================================
// SIU_INITIAL_ISEL8
//=============================================================================
//The SIU_ISEL 8 register is used to multiplex the ETPU[24:29] inputs. These six eTPU channels can come
//from the output of the DSPI or the corresponding pad.
extern const SIU_ISEL8_T SIU_INITIAL_ISEL8;


//=============================================================================
// SIU_INITIAL_ISEL9
//=============================================================================
//The eQADC has a new mode of operation called ｡ｮStreaming｡ｯ. This mode requires a second trigger for
//queue0. The source pin for this trigger can come from eTPU, eMIOS or PIT channels. A mux select
//register is required to select the source of this new queue0 trigger.
extern const SIU_ISEL9_T SIU_INITIAL_ISEL9;

//=============================================================================
// SIU_INITIAL_CCR
//=============================================================================

extern const SIU_CCR_T SIU_INITIAL_CCR;



//The SIU_PCR83 register controls the pin function, direction, and static electrical attributes of the
//CAN_A_TX_SCI_A_TX_GPIO[83] pin.
extern const SIU_PCR_T SIU_INITIAL_PCR_83;

//The SIU_PCR84 register controls the function, direction, and static electrical attributes of the
//CAN_A_RX_SCI_A_RX_GPIO[84] pin.
extern const SIU_PCR_T SIU_INITIAL_PCR_84;

//The SIU_PCR87 register controls the function, direction, and static electrical attributes of the
//CAN_C_TX_GPIO[87] pin. This register allows selection of the CAN_C_TX and GPIO functions.

extern const SIU_PCR_T SIU_INITIAL_PCR_87;

//The SIU_PCR88 register controls the function, direction, and static electrical attributes of the
//CAN_C_RX_GPIO[88] pin. This register allows selection of the CAN_C_RX and GPIO functions.

extern const SIU_PCR_T SIU_INITIAL_PCR_88;

//The SIU_PCR89 register controls the function, direction, and static electrical attributes of the
//SCI_A_TX_eMIOS[13]_GPIO[89] pin.

extern const SIU_PCR_T SIU_INITIAL_PCR_89;

//The SIU_PCR90 register controls the function, direction, and static electrical attributes of the
//SCI_A_RX_eMIOS[15]_GPIO[90] pin.

extern const SIU_PCR_T SIU_INITIAL_PCR_90;

//The SIU_PCR91 register controls the function, direction, and static electrical attributes of the
//SCI_B_TX_GPIO[91] pin. This register allows selection of the SCI_TX_B and GPIO functions.

extern const SIU_PCR_T SIU_INITIAL_PCR_91;

//The SIU_PCR92 register controls the function, direction, and static electrical attributes of the
//SCI_B_RX_GPIO[92] pin. This register allows selection of the SCI_B_RX and GPIO functions.
extern const SIU_PCR_T SIU_INITIAL_PCR_92;

//The SIU_PCR102 register controls the function, direction, and static electrical attributes of the
//DSPI_B_SCK_DSPI_C_PCS[1]_GPIO[102] pin. This register allows selection of the DSPI_B_SCK,
//DSPI_C_PCS[1] and GPIO functions.
extern const SIU_PCR_T SIU_INITIAL_PCR_102;

//The SIU_PCR103 register controls the function, direction, and static electrical attributes of the
//DSPI_B_SIN_DSPI_C_PCS[2]_GPIO[103] pin. This register allows selection of the DSPI_B_SIN,
//DSPI_C_PCS[2] and GPIO functions.
extern const SIU_PCR_T SIU_INITIAL_PCR_103;

//The SIU_PCR104 register controls the function, direction, and static electrical attributes of the
//DSPI_B_SOUT_DSPI_C_PCS[5]_GPIO[104] pin. This register allows selection of the DSPI_B_SOUT,
//DSPI_C_PCS[5] and GPIO functions.

extern const SIU_PCR_T SIU_INITIAL_PCR_104;

//The SIU_PCR105 register controls the function, direction, and static electrical attributes of the
//DSPI_B_PCS[0]_GPIO[105] pin. This register allows selection of the DSPI_B_PCS[0] and GPIO
//functions.

extern const SIU_PCR_T SIU_INITIAL_PCR_105;

//The SIU_PCR106 register controls the function, direction, and static electrical attributes of the
//DSPI_B_PCS[1]_GPIO[106] pin. This register allows selection of the DSPI_B_PCS and GPIO functions.

extern const SIU_PCR_T SIU_INITIAL_PCR_106;

//The SIU_PCR107 register controls the function, direction, and static electrical attributes of the
//DSPI_B_PCS[2]_DSPI_C_SOUT_GPIO[107] pin. This register allows selection of the DSPI_B_PCS,
//DSPI_C_SOUT and GPIO functions.
extern const SIU_PCR_T SIU_INITIAL_PCR_107;

//The SIU_PCR108 register controls the function, direction, and static electrical attributes of the
//DSPI_B_PCS[3]_DSPI_C_SIN_GPIO[108] pin. This register allows selection of the DSPI_B_PCS,
//DSPI_C_SIN and GPIO functions.

extern const SIU_PCR_T SIU_INITIAL_PCR_108;

//The SIU_PCR109 register controls the function, direction, and static electrical attributes of the
//DSPI_B_PCS[4]_DSPI_C_SCK_GPIO[109] pin. This register allows selection of the DSPI_B_PCS,
//DSPI_C_SCK and GPIO functions.

extern const SIU_PCR_T SIU_INITIAL_PCR_109;

//The SIU_PCR110 register controls the function, direction, and static electrical attributes of the
//DSPI_B_PCS[5]_DSPI_C_PCS[0]_GPIO[110] pin. This register allows selection of the DSPI_B_PCS,
//DSPI_C_PCS[0] and GPIO functions.

extern const SIU_PCR_T SIU_INITIAL_PCR_110;
//etpu00
//The SIU_PCR114 register controls the function, direction, and static electrical attributes of the
//eTPU_A[0]_eTPU_A[12]_eTPU_A[19]_GPIO[114] pin.
//58XPOS
extern const SIU_PCR_T SIU_INITIAL_PCR_114;
//etpu01
//The SIU_PCR115 ｨC SIU_PCR118 registers control the functions, directions, and static electrical attributes
//of the eTPU_A[1:4]_eTPU_A[13:16]_GPIO[115:118] pins. Only the output channels of eTPU_A[13:16]
//are connected to pins. Both the input and output channels of eTPU_A[1:4] are connected to pins.
//CAM1FIVO
extern const SIU_PCR_T SIU_INITIAL_PCR_115;
#define  HAL_GPIO_CAM1_CHANNEL         SIU_GPIO_CHANNEL_115
//etpu02
//ETCDIR
extern const SIU_PCR_T SIU_INITIAL_PCR_116;
#define  HAL_GPIO_ETCDIR_CHANNEL       SIU_GPIO_CHANNEL_116

//etpu03
//TODO
extern const SIU_PCR_T SIU_INITIAL_PCR_117;
#define  HAL_GPIO_TODO_CHANNEL       SIU_GPIO_CHANNEL_117

//etpu04
//WD
extern const SIU_PCR_T SIU_INITIAL_PCR_118;
#define  HAL_GPIO_WD_CHANNEL       SIU_GPIO_CHANNEL_118

//etpu05
//The SIU_PCR119 register controls the function, direction, and static electrical attributes of the
//eTPU_A[5]_eTPU_A[17]_DSPI_B_SCK_LVDSボ_GPIO[119] pin.
//It is required to program the PA field of both registers, SIU_PCR119 and SIU_PCR120, to select the
//SCK_LVDS alternate function, and then use the register SIU_PCR120 to program the SCK_LVDS
//characteristics (drive strength using the slew rate field).
//O2APUMP
extern const SIU_PCR_T SIU_INITIAL_PCR_119;



//etpu06
//O2BPUMP
//The SIU_PCR120 register controls the function, direction, and static electrical attributes of the
//eTPU_A[6]_eTPU_A[18]_DSPI_B_SCK_LVDS+_GPIO[120] pin.
extern const SIU_PCR_T SIU_INITIAL_PCR_120;

//etpu07
//BRKSWDI 
//The SIU_PCR120 register controls the function, direction, and static electrical attributes of the
//eTPU_A[7]_eTPU_A[19]_DSPI_B_SOUT_LVDSボ_eTPU_A[6]_GPIO[121] pin.
extern const SIU_PCR_T SIU_INITIAL_PCR_121;

#define  HAL_GPIO_BRKSWDI_CHANNEL       SIU_GPIO_CHANNEL_121

//etpu08
//DRTRNDI
//The SIU_PCR122 register controls the function, direction, and static electrical attributes of the
//eTPU_A[8]_eTPU_A[20]_DSPI_B_SOUT_LVDS+_GPIO[122] pin.
extern const SIU_PCR_T SIU_INITIAL_PCR_122;

//etpu09
//ETCDIS
//The SIU_PCR123 ｨC SIU_PCR125 registers control the function, direction, and static electrical attributes
//of the eTPU_A[9:11]_eTPU_A[21:23]_GPIO[123:125] pins.
extern const SIU_PCR_T SIU_INITIAL_PCR_123;

#define  HAL_GPIO_ETCDIS_CHANNEL       SIU_GPIO_CHANNEL_123

//etpu10
//do not active tempoary
//The SIU_PCR123 ｨC SIU_PCR125 registers control the function, direction, and static electrical attributes
//of the eTPU_A[9:11]_eTPU_A[21:23]_GPIO[123:125] pins.
extern const SIU_PCR_T SIU_INITIAL_PCR_124;

//etpu11
//not active tempoary
//The SIU_PCR123 ｨC SIU_PCR125 registers control the function, direction, and static electrical attributes
//of the eTPU_A[9:11]_eTPU_A[21:23]_GPIO[123:125] pins.
extern const SIU_PCR_T SIU_INITIAL_PCR_125;

//etpu12
//not active tempoary
//The SIU_PCR126 register controls the function, direction, and static electrical attributes of the
//eTPU_A[12]_DSPI_B_PCS[1]_GPIO[126] pin.
extern const SIU_PCR_T SIU_INITIAL_PCR_126;

//etpu13
//IMMOREQCTL
//The SIU_PCR127 register controls the function, direction, and static electrical attributes of the
//eTPU_A[13]_DSPI_B_PCS[3]_GPIO[127] pin.
extern const SIU_PCR_T SIU_INITIAL_PCR_127;

#define  HAL_GPIO_IMMOREQCTL_CHANNEL       SIU_GPIO_CHANNEL_127

//VGIS2CTL
//etpu14
//The SIU_PCR128 register controls the function, direction, and static electrical attributes of the
//eTPU_A[14]_DSPI_B_PCS[4]_eTPU_A[9]_GPIO[128] pin.
extern const SIU_PCR_T SIU_INITIAL_PCR_128;

#define  HAL_GPIO_VGIS2CTL_CHANNEL       SIU_GPIO_CHANNEL_128

//VGIS1CTL
//etpu15
//The SIU_PCR129 register controls the function, direction, and static electrical attributes of the
//eTPU_A[15]_DSPI_B_PCS[5]_GPIO[129] pin.
extern const SIU_PCR_T SIU_INITIAL_PCR_129 ;

#define  HAL_GPIO_VGIS1CTL_CHANNEL       SIU_GPIO_CHANNEL_129



//etpu16
//CAM2FIVO
//The SIU_PCR130 ｨC SIU_PCR133 registers control the function, direction, and static electrical attributes
//of the eTPU_A[16:19]_GPIO[130:133] pins. This registers allow selection of the eTPU_A and GPIO
//functions.
extern const SIU_PCR_T SIU_INITIAL_PCR_130 ;
#define  HAL_GPIO_CAM2_CHANNEL         SIU_GPIO_CHANNEL_130

//etpu17
//EST1
//The SIU_PCR130 ｨC SIU_PCR133 registers control the function, direction, and static electrical attributes
//of the eTPU_A[16:19]_GPIO[130:133] pins. This registers allow selection of the eTPU_A and GPIO
//functions.
extern const SIU_PCR_T SIU_INITIAL_PCR_131;


//etpu18
//EST SYNC
//The SIU_PCR130 ｨC SIU_PCR133 registers control the function, direction, and static electrical attributes
//of the eTPU_A[16:19]_GPIO[130:133] pins. This registers allow selection of the eTPU_A and GPIO
//functions.
extern const SIU_PCR_T SIU_INITIAL_PCR_132;


#define  HAL_GPIO_ESTSYNC_CHANNEL       SIU_GPIO_CHANNEL_132

//etpu19
//INJ1
//The SIU_PCR130 ｨC SIU_PCR133 registers control the function, direction, and static electrical attributes
//of the eTPU_A[16:19]_GPIO[130:133] pins. This registers allow selection of the eTPU_A and GPIO
//functions.
extern const SIU_PCR_T SIU_INITIAL_PCR_133;

//etpu20
//INJ2
//The SIU_PCR134 ｨC SIU_PCR135 registers control the functions, directions, and static electrical attributes
//of the eTPU_A[20:21]_IRQ[8:9]_GPIO[134:135] pins.
extern const SIU_PCR_T SIU_INITIAL_PCR_134;

//etpu21
//INJ3
//The SIU_PCR134 ｨC SIU_PCR135 registers control the functions, directions, and static electrical attributes
//of the eTPU_A[20:21]_IRQ[8:9]_GPIO[134:135] pins.
extern const SIU_PCR_T SIU_INITIAL_PCR_135 ;

//etpu22
//INJ4
//The SIU_PCR136 register controls the function, direction, and static electrical attributes of the
//eTPU_A[22]_IRQ[10]_eTPU_A[17]_GPIO[136] pin. The eTPU_A[17] is an output only function.
extern const SIU_PCR_T SIU_INITIAL_PCR_136 ;


//etpu23
//not active
//The SIU_PCR137 register controls the function, direction, and static electrical attributes of the
//eTPU_A[23]_IRQ[11]_eTPU_A[21]_GPIO[137] pin.
extern const SIU_PCR_T SIU_INITIAL_PCR_137;


//etpu24
//ELOAD2DI
//The SIU_PCR138 register controls the function, direction, and static electrical attributes of the
//eTPU_A[24]_IRQ[12]_DSPI_C_SCK_LVDSボ_GPIO[138] pin.
extern const SIU_PCR_T SIU_INITIAL_PCR_138;

#define  HAL_GPIO_ELOAD2DI_CHANNEL       SIU_GPIO_CHANNEL_138

//etpu25
//ELOAD1DI
//The SIU_PCR139 register controls the function, direction, and static electrical attributes of the
//eTPU_A[25]_IRQ[13]_DSPI_C_SCK_LVDS+_GPIO[139] pin.
extern const SIU_PCR_T SIU_INITIAL_PCR_139;


#define  HAL_GPIO_ELOAD1DI_CHANNEL       SIU_GPIO_CHANNEL_139

//etpu26
//SPFI
//The SIU_PCR140 register controls the function, direction, and static electrical attributes of the
//eTPU_A[26]_IRQ[14]_DSPI_C_SOUT_LVDSボ_GPIO[140] pin.
extern const SIU_PCR_T SIU_INITIAL_PCR_140;

//etpu27
//VSSFI
//The SIU_PCR141 register controls the function, direction, and static electrical attributes of the
//eTPU_A[27]_IRQ[15]_DSPI_C_SOUT_LVDS+_DSPI_B_SOUT_GPIO[141] pin.
extern const SIU_PCR_T SIU_INITIAL_PCR_141 ;

//etpu28
//WSSFI
//The SIU_PCR142 ｨC SIU_PCR143 registers control the functions, directions, and static electrical attributes
//of the eTPU_A[28:29]_DSPI_C_PCS[1:2]_GPIO[142:143] pins. Only the output channel of
//eTPU_A[28:29] is connected to the pin. This register allows selection of the eTPU_A and GPIO functions.
extern const SIU_PCR_T SIU_INITIAL_PCR_142 ;

//etpu29
//ENSFI
//The SIU_PCR142 ｨC SIU_PCR143 registers control the functions, directions, and static electrical attributes
//of the eTPU_A[28:29]_DSPI_C_PCS[1:2]_GPIO[142:143] pins. Only the output channel of
//eTPU_A[28:29] is connected to the pin. This register allows selection of the eTPU_A and GPIO functions.
extern const SIU_PCR_T SIU_INITIAL_PCR_143;

//etpu30
//WINGATE 
//inactive tempoary
//The SIU_PCR144 register controls the function, direction, and static electrical attributes of the
//eTPU_A[30]_DSPI_C_PCS[3]_eTPU_A[11]_GPIO[144] pin. This register allows selection of the
//eTPU_A, DSPI_C_PCS and GPIO functions. The eTPU_A[11] is an output only function.
extern const SIU_PCR_T SIU_INITIAL_PCR_144;

#define  HAL_RQOME_Wingate_CHANNEL       SIU_GPIO_CHANNEL_144

//etpu31
//not active  
//The SIU_PCR145 register controls the function, direction, and static electrical attributes of the
//eTPU_A[31]_DSPI_C_PCS[4]_eTPU_A[13]_GPIO[145] pin. This register allows selection of the
//eTPU_A, DSPI_C_PCS and GPIO functions. The eTPU_A[13] is an output only function.
extern const SIU_PCR_T SIU_INITIAL_PCR_145 ;

//emios00
//VSEPCLK
//The SIU_PCR179 register controls the function, direction, and static electrical attributes of the
//eMIOS[0]_eTPU_A[0]_eTPU_A[25]_GPIO[179] pin. This register allows selection of the eMIOS,
//eTPU_A and GPIO functions. The eTPU_A[25] is an output only function.
extern const SIU_PCR_T SIU_INITIAL_PCR_179 ;

//emios01
//configured as input 
//The SIU_PCR180 register controls the function, direction, and static electrical attributes of the
//eMIOS[1]_eTPU_A[1]_GPIO[180] pin. This register allows selection of the eTPU_A and GPIO
//functions.
/*extern const SIU_PCR_T SIU_INITIAL_PCR_180;*/

//emios02
//GEN_ENABLE
//The SIU_PCR181 register controls the function, direction, and static electrical attributes of the
//eMIOS[2]_eTPU_A[2]_GPIO[181] pin. This register allows selection of the eTPU_A and GPIO
//functions.
extern const SIU_PCR_T SIU_INITIAL_PCR_181;

#define  HAL_GPIO_GEN_ENABLE_CHANNEL       SIU_GPIO_CHANNEL_181

//emios04
//SOHCLK 
//The SIU_PCR183 register controls the function, direction, and static electrical attributes of the
//eMIOS[4]_eTPU_A[4]_GPIO[183] pin. This register allows selection of the eTPU_A and GPIO
//functions.
extern const SIU_PCR_T SIU_INITIAL_PCR_183;

//emios08
//ETCCTLPWM 
//The SIU_PCR187 register controls the functions, directions, and static electrical attributes of the
//eMIOS[8]_eTPU_A[8]_SCI_B_TX_GPIO[187] pin. Both the input and output functions of eMIOS[8:9]
//are connected to pins. Only the output channels of eTPU_A[8:9] are connected to pins.
extern const SIU_PCR_T SIU_INITIAL_PCR_187;

//emios09
//CLTPUMPCTL 
//The SIU_PCR188 register controls the functions, directions, and static electrical attributes of the
//eMIOS[9]_eTPU_A[9]_SCI_B_RX_GPIO[188] pin. Both the input and output functions of eMIOS[8:9]
//are connected to pins. Only the output channels of eTPU_A[8:9] are connected to pins.
extern const SIU_PCR_T SIU_INITIAL_PCR_188;

//emios10
//CRUISICTL
//The SIU_PCR189 ｨC SIU_PCR190 registers control the pin functions, directions, and static electrical
//attributes of the eMIOS[10:11]_GPIO[189:190] pins. Both the input and output functions of
//eMIOS[10:11] are connected to pins.
extern const SIU_PCR_T SIU_INITIAL_PCR_189;

//emios11
//FSE_ENABLE
//The SIU_PCR189 ｨC SIU_PCR190 registers control the pin functions, directions, and static electrical
//attributes of the eMIOS[10:11]_GPIO[189:190] pins. Both the input and output functions of
//eMIOS[10:11] are connected to pins.
extern const SIU_PCR_T SIU_INITIAL_PCR_190 ;

#define  HAL_GPIO_FSE_ENABLE_CHANNEL       SIU_GPIO_CHANNEL_190

//emios12
//VVT2CTL
//The SIU_PCR191 register controls the function, direction, and static electrical attributes of the
//eMIOS[12]_DSPI_C_SOUT_eTPU_A[27]_GPIO[191] pin. This register allows selection of the eMIOS
//and GPIO functions.
extern const SIU_PCR_T SIU_INITIAL_PCR_191;


//emios13
//no pin in 144 package
//The SIU_PCR192 register controls the function, direction, and static electrical attributes of the
//eMIOS[13]_GPIO[192] pin. This register allows selection of the eMIOS and GPIO functions.
/*extern const SIU_PCR_T SIU_INITIAL_PCR_192;*/


//emios14
//VVT1CTL
//The SIU_PCR193 register controls the function, direction, and static electrical attributes of the
//eMIOS[14]_IRQ[0]_eTPU_A[29]_GPIO[193] pin. Only the output functions of eMIOS[14] are
//connected to this pin.
extern const SIU_PCR_T SIU_INITIAL_PCR_193;

//emios15
//no pin in 144 package
//The SIU_PCR194 register controls the function, direction, and static electrical attributes of the
//eMIOS[15]_IRQ[1]_GPIO[194] pin. This register allows selection of the eMIOS and GPIO functions.
/*extern const SIU_PCR_T SIU_INITIAL_PCR_194;*/

//emios23
//FUELCONCTL
//The SIU_PCR202 register controls the function, direction, and static electrical attributes of the
//eMIOS[23]_GPIO[202] pin. Both the input and output functions of eMIOS[23] are connected to the pin.
//The eTPU_B function is not available on this device.
extern const SIU_PCR_T SIU_INITIAL_PCR_202;




//The SIU_PCR206 ｨC SIU_PCR207 registers control the function, direction, and static electrical attributes
//of the GPIO[206:207] pins.

//The SIU_PCR208 register controls the function, direction, and static electrical attributes of the
//PLLREF_IRQ[4]_ETRIG[2]_GPIO[208] pin.


//The SIU_PCR212 register controls the function, direction, and static electrical attributes of the
//BOOTCFG1_IRQ[3]_ETRIG[3]_GPIO[212] pin.

//The SIU_PCR213 register controls the function, direction, and static electrical attributes of the
//WKPCFG_NMI_DSPI_B_SOUT_GPIO[213] pin.

//The SIU_PCR215 register controls the function, direction, and static electrical attributes of the
//AN[12]_MA[0]_eTPU_A[19]_SDS pin. The AN[12] function is an analog pin on this device. This
//register allows selection of the MA[0] and SDS functions.
extern const SIU_PCR_T SIU_INITIAL_PCR_215;

//The SIU_PCR216 register controls the function, direction, and static electrical attributes of the
//AN[13]_MA[1]_eTPU_A[21]_SDO pin. The AN[13] function is not available on this device. This register
//allows selection of the MA[1] and SDO functions.

extern const SIU_PCR_T SIU_INITIAL_PCR_216;

//The SIU_PCR217 register controls the function, direction, and static electrical attributes of the
//AN[14]_MA[2]_eTPU_A[27]_SDI pin. The AN[14] function is an analog pin on this device. This register
//allows selection of the MA[2] and SDI functions.
extern const SIU_PCR_T SIU_INITIAL_PCR_217;


//The SIU_PCR218 register controls the function, direction, and static electrical attributes of the
//AN[15]_FCK_eTPU_A[29] pin. The AN[15] function is an analog pin on this device. This register allows
//selection of the FCK function.

extern const SIU_PCR_T SIU_INITIAL_PCR_218;


//The SIU_PCR219 register controls the drive strength of the MCKO_GPIO[219] pin.
//not active
extern const SIU_PCR_T SIU_INITIAL_PCR_219;


//The SIU_PCR220 register controls the drive strength of the MDO[0]_eTPU_A[13]_GPIO[220] pin.
//not active
extern const SIU_PCR_T SIU_INITIAL_PCR_220;

//not active LCI for GPIO 220
extern const SIU_PCR_T SIU_INITIAL_PCR_180_LCI;

//The SIU_PCR221 register controls the drive strength of the MDO[1]_eTPU_A[19]_GPIO[221] pin.
//not active
extern const SIU_PCR_T SIU_INITIAL_PCR_221;

//not active LCI for GPIO221
extern const SIU_PCR_T SIU_INITIAL_PCR_192_LCI ;

//The SIU_PCR222 register controls the drive strength of the MDO[2]_eTPU_A[21]_GPIO[222] pin.
//VBATT_Det_Reset_DIO
extern const SIU_PCR_T SIU_INITIAL_PCR_222;

#define  HAL_GPIO_Reset_DIO_CHANNEL       SIU_GPIO_CHANNEL_222

//VBATT_Det_Reset_DIO LCI for GPIO222
extern const SIU_PCR_T SIU_INITIAL_PCR_194_LCI ;

#define  HAL_GPIO_Reset_DIO_CHANNEL_LCI       SIU_GPIO_CHANNEL_194

//The SIU_PCR223 register controls the drive strength of the MDO[3]_eTPU_A[25]_GPIO[223] pin.
//not active
extern const SIU_PCR_T SIU_INITIAL_PCR_223;

//not active LCI for GPIO223
extern const SIU_PCR_T SIU_INITIAL_PCR_80_LCI;


//The SIU_PCR224 register controls the drive strength of the MSEO[0]_eTPU_A[27]_GPIO[224] pin.
//BRKLMPDI
extern const SIU_PCR_T SIU_INITIAL_PCR_224;

#define  HAL_GPIO_BRKLMPDI_CHANNEL       SIU_GPIO_CHANNEL_224

//LCI for GPIO224
extern const SIU_PCR_T SIU_INITIAL_PCR_81_LCI;

#define  HAL_GPIO_BRKLMPDI_CHANNEL_LCI       SIU_GPIO_CHANNEL_RESERVED_81

//The SIU_PCR225 register controls the drive strength of the MSEO[1]_eTPU_A[29]_GPIO[225] pin.
//ELOAD1DICTL
extern const SIU_PCR_T SIU_INITIAL_PCR_225;

#define  HAL_GPIO_ELOAD1DICTL_CHANNEL       SIU_GPIO_CHANNEL_225

//LCI for GPIO225
extern const SIU_PCR_T SIU_INITIAL_PCR_82_LCI ;

#define  HAL_GPIO_ELOAD1DICTL_CHANNEL_LCI       SIU_GPIO_CHANNEL_RESERVED_82

//The SIU_PCR227 register controls the drive strength of the EVTO_eTPU_A[4]_GPIO[227] pin.
//ELOAD2DICTL
extern const SIU_PCR_T SIU_INITIAL_PCR_227;

#define  HAL_GPIO_ELOAD2DICTL_CHANNEL       SIU_GPIO_CHANNEL_227

//LCI for GPIO227
extern const SIU_PCR_T SIU_INITIAL_PCR_99_LCI;

#define  HAL_GPIO_ELOAD2DICTL_CHANNEL_LCI       SIU_GPIO_CHANNEL_99

//The SIU_PCR228 register controls the drive strength of the TDO_eMIOS[6]_GPIO[228] pin.

//The SIU_PCR228 register controls the drive strength of the TDO_eMIOS[6]_GPIO[228] pin.

//The SIU_PCR229 register controls the enabling/disabling and drive strength of the CLKOUT pin. The
//CLKOUT pin is enabled and disabled by setting and clearing the OBE bit. The CLKOUT pin is enabled
//during reset.

//The SIU_PCR230 register controls the slew rate of the RSTOUT pin.

//The SIU_PCR231 register controls the function and drive strength of the EVTI_eTPU_A[2]_GPIO[231]
//pin.
//BRKLMPDICTL
extern const SIU_PCR_T SIU_INITIAL_PCR_231;

#define  HAL_GPIO_BRKLMPDICTL_CHANNEL       SIU_GPIO_CHANNEL_231

//LCI for GPIO98
extern const SIU_PCR_T SIU_INITIAL_PCR_98_LCI ;

#define  HAL_GPIO_BRKLMPDICTL_CHANNEL_LCI       SIU_GPIO_CHANNEL_98

//The SIU_PCR232 register controls the drive strength of the TDI_eMIOS[5]_GPIO[232] pin.

//The SIU_PCR336 register controls the drive strength of the CAL_CS[0] pin.

// The SIU_PCR338 ｨC SIU_PCR339 registers control the functions and drive strength of the
//CAL_CS[2:3]_CAL_ADDR[10:11] pins.


//The SIU_PCR340 register controls the drive strength of the CAL_ADDR[12:15] pins. Multiple pins are
//controlled by this PCR.

//The SIU_PCR341 register controls the drive strength of the CAL_DATA[0:15] pins. Multiple pins are
//controlled by this PCR.

//The SIU_PCR342 register controls the drive strength of the CAL_RD_WR, CAL_WE[0:1] and CAL_OE
//pins. Multiple pins are controlled by this one PCR. The WEBS bit in the EBI Base Register selects between
//the write enable and byte enable functions.


//The SIU_PCR343 register controls the drive strength of the CAL_TS_ALE pin.

//The SIU_PCR344 register controls the drive strength of the ALT_MCKO and ALT_EVTO pins. Multiple
//pins are controlled by this PCR.


//The SIU_PCR345 register controls the drive strength of the CAL_ADDR[16:27]_ALT_MDO[0:11],
//CAL_ADDR[28:29]_CAL_MSEO[0:1] and CAL_ADDR[30]_ALT_EVTI pins. Multiple pins are
//controlled by this PCR.


//The SIU_PCR350 ｨC SIU_PCR381 registers control the muxing of the signals to the DSPI. PA field values
//are shown in Table 138.

//The SIU_PCR382 ｨC SIU_PCR389 registers control the muxing of the signals to the DSPI. PA field values
//are shown in Table 139.

//The SIU_PCR390 ｨC SIU_PCR413 registers control the muxing of the signals to the DSPI. PA field values
//are shown in Table 140.



// configure for DSPI DSI mode
//=============================================================================
// SIU_GPIO_382 - EMIOS12
//=============================================================================
extern const SIU_PCR_T SIU_INITIAL_PCR_382;

//=============================================================================
// SIU_GPIO_383 - ETPU13
//=============================================================================

extern const SIU_PCR_T SIU_INITIAL_PCR_383;


//=============================================================================
// SIU_GPIO_384 - EMIOS14
//=============================================================================
extern const SIU_PCR_T SIU_INITIAL_PCR_384;


//=============================================================================
// SIU_GPIO_385 - EMIOS15
//=============================================================================
extern const SIU_PCR_T SIU_INITIAL_PCR_385;
//=============================================================================
// SIU_GPIO_386 - EMIOS23
//=============================================================================
extern const SIU_PCR_T SIU_INITIAL_PCR_386 ;

//=============================================================================
// SIU_GPIO_387 - EMIOS00
//=============================================================================
extern const SIU_PCR_T SIU_INITIAL_PCR_387;

//=============================================================================
// SIU_GPIO_388 - ETPU02
//=============================================================================

extern const SIU_PCR_T SIU_INITIAL_PCR_388 ;

//=============================================================================
// SIU_GPIO_389 - ETPU03
//=============================================================================
extern const SIU_PCR_T SIU_INITIAL_PCR_389;


//=============================================================================
// SIU_GPIO_390 - ETPU04
//=============================================================================
extern const SIU_PCR_T SIU_INITIAL_PCR_390;

//=============================================================================
// SIU_GPIO_391 - GPIO
//=============================================================================
extern const SIU_PCR_T SIU_INITIAL_PCR_391;

//=============================================================================
// SIU_GPIO_392 - GPIO
//=============================================================================
extern const SIU_PCR_T SIU_INITIAL_PCR_392 ;


//=============================================================================
// SIU_GPIO_393 - GPIO
//=============================================================================
extern const SIU_PCR_T SIU_INITIAL_PCR_393 ;


//=============================================================================
// SIU_GPIO_394 - GPIO
//=============================================================================
extern const SIU_PCR_T SIU_INITIAL_PCR_394;


//=============================================================================
// SIU_GPIO_395 - GPIO
//=============================================================================
extern const SIU_PCR_T SIU_INITIAL_PCR_395;


//=============================================================================
// SIU_GPIO_396 - EMIOS10
//=============================================================================

extern const SIU_PCR_T SIU_INITIAL_PCR_396;

//=============================================================================
// SIU_GPIO_397 - GPIO
//=============================================================================
extern const SIU_PCR_T SIU_INITIAL_PCR_397;



#endif // IO_CONFIG_SIU_H

