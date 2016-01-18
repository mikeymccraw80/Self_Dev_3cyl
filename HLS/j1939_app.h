#ifndef J1939_APP_H
#define J1939_APP_H

/******************************************************************************
 *
 * Filename:          j1939_app.h
 *
 * Description:       j1939 app header file for APPLICATION
 *
 * Global Functions Defined:
 *                    None
 * Static Functions Defined:
 *                    None
 * Inline Functions Defined:
 *                    None
 *
 * Forward Engine Management Systems
 *
 * Copyright 2015 , Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************/
#include "reuse.h"

extern  bool B_Ign0Req;
extern  bool B_Ign1Req;
extern  bool B_Ign2Req;

#define J1939_ECUID_BUFFER_SIZE (16)
uint16_t GetJ939_ECUID_Size(void);
uint8_t * GetJ1939_ECUID_MsgPtr(void);

#define J1939_SOFT_BUFFER_SIZE (16)
uint16_t GetJ1939_SoftID_Size(void);
uint8_t * GetJ1939_SoftID_MsgPtr(void);

uint8_t*GetJ1939_DM1_MsgPtr (void);
uint16_t GetJ1939_DM1_ActiveDTC_NUMBER (void);

uint8_t *GetJ1939_PGN_65251_MsgPtr (void);
uint8_t *GetJ1939_PGN_65249_MsgPtr (void);

uint16_t GetJ1939_PGN_65251_BYTE_NUMBER (void);
uint16_t GetJ1939_PGN_65249_BYTE_NUMBER (void);


uint8_t *GetJ1939_DM2_MsgPtr (void);
uint16_t GetJ1939_DM2_PreActiveDTC_NUMBER (void);

bool ClrJ1939_DM3_PreActive_Dtcs(void);

uint8_t *GetJ1939_DM4_MsgPtr (void);

bool ClrJ1939_DM11_Active_Dtcs (void);

uint8_t *GetJ1939_DM12_MsgPtr (void);
uint16_t GetJ1939_DM12_EmissionsRelated_ActiveDTCs_Number (void);

typedef struct {
	uint8_t data[8];
}J1939_DATA_T;

/* j1939 pgn TSC1 (0x000000) parameters structure define */
typedef struct {
	struct {
		uint8_t spn_res		:2;
		uint8_t spn_897		:2;
		uint8_t spn_696		:2;
		uint8_t spn_695		:2;
	}byte1;
	struct {
		uint16_t spn_898	:16;
	}byte23;
	struct {
		uint8_t spn_518 	:8;
	}byte4;
	struct {
		uint8_t spn_3350	:4;
		uint8_t spn_3349	:4;
	}byte5;
	struct {
		uint8_t spn_res 	:4;
		uint8_t spn_4191	:4;
	}byte6;
	struct {
		uint8_t spn_res		:8;
	}byte7;
	struct {
		uint8_t spn_4207	:4;
		uint8_t spn_4206	:4;
	}byte8;
}J1939_PGN_TSC1_00000_T;
extern J1939_PGN_TSC1_00000_T pgn_tsc1_00000;


/* j1939 pgn CM1 (0x00E000) parameters structure define */
typedef struct {
	struct {
		uint8_t spn_986 	:8;
	}byte1;
	struct {
		uint16_t spn_1691	:16;
	}byte23;
	struct {
		uint8_t spn_1856 	:2;
		uint8_t spn_1714 	:2;
		uint8_t spn_1682 	:2;
		uint8_t spn_1684 	:2;
	}byte4;
	struct {
		uint8_t spn_1653	:2;
		uint8_t spn_1654	:2;
		uint8_t spn_1655	:2;
		uint8_t spn_5630	:2;
	}byte5;
	struct {
		uint8_t spn_1656 	:2;
		uint8_t spn_1666 	:2;
		uint8_t spn_3696 	:2;
		uint8_t spn_3695 	:2;
	}byte6;
	struct {
		uint8_t spn_1686	:2;
		uint8_t spn_1685	:2;
		uint8_t spn_1683	:4;
	}byte7;
	struct {
		uint8_t spn_2596	:8;
	}byte8;
}J1939_PGN_CM1_57344_T;
extern J1939_PGN_CM1_57344_T pgn_cm1_57344;

/* j1939 pgn CCVS1 (0x00FEF1) parameters structure define */
typedef struct {
	struct {
		uint8_t spn_3807	:2;
		uint8_t spn_1633	:2;
		uint8_t spn_70  	:2;
		uint8_t spn_69  	:2;
	}byte1;
	struct {
		uint16_t spn_84	:16;
	}byte23;
	struct {
		uint8_t spn_598 	:2;
		uint8_t spn_597 	:2;
		uint8_t spn_596 	:2;
		uint8_t spn_595 	:2;
	}byte4;
	struct {
		uint8_t spn_602 	:2;
		uint8_t spn_601 	:2;
		uint8_t spn_600 	:2;
		uint8_t spn_599 	:2;
	}byte5;
	struct {
		uint8_t spn_86  	:8;
	}byte6;
	struct {
		uint8_t spn_527 	:3;
		uint8_t spn_976 	:5;
	}byte7;
	struct {
		uint8_t spn_1237	:2;
		uint8_t spn_966 	:2;
		uint8_t spn_967 	:2;
		uint8_t spn_968 	:2;
	}byte8;
}J1939_PGN_CCVS_65265_T;
extern J1939_PGN_CCVS_65265_T pgn_ccvs_65265;

/* j1939 pgn OHECS (0x00FDCB) parameters structure define */
typedef struct {
	struct {
		uint8_t spn_res 	:2;
		uint8_t spn_2883	:2;
		uint8_t spn_1377	:2;
		uint8_t spn_2884	:2;
	}byte1;
	struct {
		uint8_t spn_2882	:8;
	}byte2;
	struct {
		uint8_t spn_2879	:4;
		uint8_t spn_2881	:4;
	}byte3;
	struct {
		uint8_t spn_2885	:4;
		uint8_t spn_2886	:4;
	}byte4;
	struct {
		uint32_t spn_res	:32;
	}byte5678;
}J1939_PGN_OHECS_64971_T;
extern J1939_PGN_OHECS_64971_T pgn_ohecs_64971;

/* j1939 pgn EEC1 (0x00F004) parameters structure define */
typedef struct {
	struct {
		uint8_t spn_res     :4;
		uint8_t spn_899     :4;
	}byte1;
	struct {
		uint8_t spn_512     :8;
	}byte2;
	struct {
		uint8_t spn_513     :8;
	}byte3;
	struct {
		uint16_t spn_190    :16;
	}byte45;
	struct {
		uint8_t spn_1483    :8;
	}byte6;
	struct {
		uint8_t spn_res     :4;
		uint8_t spn_1675    :4;
	}byte7;
	struct {
		uint8_t spn_2432	:8;
	}byte8;
}J1939_PGN_ECC1_61444_T;
extern J1939_PGN_ECC1_61444_T pgn_ecc1_61444;

/* j1939 pgn EEC2 (0x00F003) parameters structure define */
typedef struct {
	struct {
		uint8_t spn_2970    :2;
		uint8_t spn_1437    :2;
		uint8_t spn_559     :2;
		uint8_t spn_558     :2;
	}byte1;
	struct {
		uint8_t spn_91      :8;
	}byte2;
	struct {
		uint8_t spn_92      :8;
	}byte3;
	struct {
		uint8_t spn_974     :8;
	}byte4;
	struct {
		uint8_t spn_29      :8;
	}byte5;
	struct {
		uint8_t spn_5400    :2;
		uint8_t spn_5399    :2;
		uint8_t spn_5021    :2;
		uint8_t spn_2979    :2;
	}byte6;
	struct {
		uint8_t spn_3357    :8;
	}byte7;
	struct {
		uint8_t spn_5398    :8;
	}byte8;
}J1939_PGN_ECC2_61443_T;
extern J1939_PGN_ECC2_61443_T pgn_ecc2_61443;

/* j1939 pgn MVS (0x00FDE5) parameters structure define */
typedef struct {
	struct {
		uint8_t spn_2588    :8;
	}byte1;
	struct {
		uint8_t spn_2589    :8;
	}byte2;
	struct {
		uint8_t spn_2590    :8;
	}byte3;
	struct {
		uint8_t spn_2591    :8;
	}byte4;
	struct {
		uint8_t spn_2592    :8;
	}byte5;
	struct {
		uint8_t spn_2593    :8;
	}byte6;
	struct {
		uint8_t spn_2594    :8;
	}byte7;
	struct {
		uint8_t spn_2595    :8;
	}byte8;
}J1939_PGN_MVS_64997_T;
extern J1939_PGN_MVS_64997_T pgn_mvs_64997;

/* j1939 pgn Engine Cylinder #1 Ignition Timing (0x00FE82) parameters structure define */
typedef struct {
	struct {
		uint16_t spn_1413   :16;
	}byte12;
	
	struct {
		uint16_t spn_1414   :16;
	}byte34;

	struct {
		uint16_t spn_1415   :16;
	}byte56;
	
	struct {
		uint16_t spn_1416   :16;
	}byte78;
}J1939_PGN_IT1_65154_T;
extern J1939_PGN_IT1_65154_T pgn_IT1_65154;

/* j1939 pgn LFE (0x00FEF2) parameters structure define */
typedef struct {
	struct {
		uint16_t spn_183	:16;
	}byte12;
	struct {
		uint16_t spn_184	:16;
	}byte34;
	struct {
		uint16_t spn_186	:16;
	}byte56;
	struct {
		uint8_t spn_51		:8;
	}byte7;
	struct {
		uint8_t spn_3673	:8;
	}byte8;
}J1939_PGN_LFE_65266_T;
extern J1939_PGN_LFE_65266_T pgn_lfe_65266;

/* j1939 pgn ET1 (0x00FEEE) parameters structure define */
typedef struct {
	struct {
		uint8_t spn_110		:8;
	}byte1;
	struct {
		uint8_t spn_174		:8;
	}byte2;
	struct {
		uint16_t spn_175	:16;
	}byte34;
	struct {
		uint16_t spn_176	:16;
	}byte56;
	struct {
		uint8_t spn_52		:8;
	}byte7;
	struct {
		uint8_t spn_1134	:8;
	}byte8;
}J1939_PGN_ET1_65262_T;
extern J1939_PGN_ET1_65262_T pgn_et1_65262;

/* j1939 pgn EFL/P1 (0x00FEEF) parameters structure define */
typedef struct {
	struct {
		uint8_t spn_94		:8;
	}byte1;
	struct {
		uint8_t spn_22		:8;
	}byte2;
	struct {
		uint8_t spn_98		:8;
	}byte3;
	struct {
		uint8_t spn_100		:8;
	}byte4;
	struct {
		uint16_t spn_101	:16;
	}byte56;
	struct {
		uint8_t spn_109		:8;
	}byte7;
	struct {
		uint8_t spn_111		:8;
	}byte8;
}J1939_PGN_EFL_P1_65263_T;
extern J1939_PGN_EFL_P1_65263_T pgn_efl_p1_65263;

/* j1939 pgn IC1 (0x00FEF6) parameters structure define */
typedef struct {
	struct {
		uint8_t spn_81      :8;
	}byte1;
	struct {
		uint8_t spn_102     :8;
	}byte2;
	struct {
		uint8_t spn_105     :8;
	}byte3;
	struct {
		uint8_t spn_106     :8;
	}byte4;
	struct {
		uint8_t spn_107     :8;
	}byte5;
	struct {
		uint16_t spn_173    :16;
	}byte67;
	struct {
		uint8_t spn_112     :8;
	}byte8;
}J1939_PGN_IC1_65270_T;
extern J1939_PGN_IC1_65270_T pgn_ic1_65270;

/* j1939 pgn VEP1 (0x00FEF7) parameters structure define */
typedef struct {
	struct {
		uint8_t spn_114     :8;
	}byte1;
	struct {
		uint8_t spn_115     :8;
	}byte2;
	struct {
		uint16_t spn_167    :16;
	}byte34;
	struct {
		uint16_t spn_168    :16;
	}byte56;
	struct {
		uint16_t spn_158    :16;
	}byte78;
}J1939_PGN_VEP1_65271_T;
extern J1939_PGN_VEP1_65271_T pgn_vep1_65271;

/* j1939 pgn FD (0x00FEBD) parameters structure define */
typedef struct {
	struct {
		uint8_t spn_975     :8;
	}byte1;
	struct {
		uint8_t spn_res     :4;
		uint8_t spn_977     :4;
	}byte2;
	struct {
		uint16_t spn_1639   :16;
	}byte34;
	struct {
		uint16_t spn_4211   :16;
	}byte56;
	struct {
		uint8_t spn_4212    :8;
	}byte7;
	struct {
		uint8_t spn_res     :8;
	}byte8;
}J1939_PGN_FD_65213_T;
extern J1939_PGN_FD_65213_T pgn_fd_65213;

/* j1939 pgn HOURS (0x00FEE5) parameters structure define */
typedef union {
	struct {
		uint32_t spn_247       :32;
		uint32_t spn_249       :32;
    }udword;
	struct{
		uint16_t spn_247_H     :16;
		uint16_t spn_247_L     :16;
		uint16_t spn_249_H     :16;
		uint16_t spn_249_L     :16;
	}uword;
}J1939_PGN_HOURS_65253_T;
extern J1939_PGN_HOURS_65253_T pgn_hours_65253;

/* j1939 PGN 65289 (0x00FF09) parameters structure define */
typedef struct {
	struct {
		uint8_t TLA1    :8;
	}byte1;
	struct {
		uint8_t TLA2    :8;
	}byte2;
	struct {
		uint8_t TLA3   :8;
	}byte3;
	struct {
		uint8_t  RES1   :8;
	}byte4;
	struct {
		uint16_t RES2   :16;
	}byte56;
	struct {
		uint16_t RES3   :16;
	}byte78;
}J1939_pgn_65289_T;
extern J1939_pgn_65289_T     J1939_pgn_65289;

/* j1939 73 dm4 (0x00FECD) parameters structures define */ 
#define Max_Freeze_Frame_Num   3
typedef struct{
	uint8_t spn_1217         :8; //freeze frame length
	uint8_t spn_1214_l       :8; //low 8 bits of spn1214
	uint8_t spn_1214_m       :8; //middle 8 bits of spn1214
	uint8_t spn_1214_h       :3; //high 3 bits of spn1214
	uint8_t spn_1215         :5;
	uint8_t spn_1706         :1;
	uint8_t spn_1216         :7;  
	uint8_t spn_899          :8;
	uint8_t spn_102          :8;
 
	struct{
		uint8_t spn_190_l    :8;
		uint8_t spn_190_h    :8;
 
	}spn_190;

	uint8_t spn_92           :8;
	uint8_t spn_110          :8; 

	struct{
		uint8_t spn_86_l     :8;
		uint8_t spn_86_h     :8; 
	}spn_86;
	
	/********manufacturer specific information****/
	uint8_t spn_105          :8;

	uint8_t spn_51           :8;
	 
	struct{
		uint8_t spn_158_l    :8;
		uint8_t spn_158_h    :8;
 
	}spn_158;
	 
	struct{
		uint8_t spn_1413_l   :8;
		uint8_t spn_1413_h   :8;
 
	}spn_1413;
 
}J1939_DM4_FreezeFrame_T;

typedef struct{ 
	J1939_DM4_FreezeFrame_T Freeze_Frame[Max_Freeze_Frame_Num];
}J1939_73_DM4_T;
extern J1939_73_DM4_T J1939_73_dm4;

/* j1939 73 dm7 (0x00E300) parameters structure define */
typedef union {
	uint8_t Buffer[8];
	struct {
		uint8_t spn_1224     :8;
		uint8_t spn_4148_l   :8;
		uint8_t spn_4148_m   :8;
		uint8_t spn_4148_h   :3;
		uint8_t spn_4149     :5;
		uint16_t spn_res1    :16;
		uint16_t spn_res2    :16;
	}bytes;
}J1939_73_dm7_58112_T;
extern J1939_73_dm7_58112_T     J1939_73_dm7;

/* j1939 73 dm5 (0x00FECE) parameters structure define */
typedef struct {

	uint8_t spn_1218             :8;
	uint8_t spn_1219             :8;
	uint8_t spn_1220             :8;
	
	 union {
		uint8_t data;
		struct{
			uint8_t res1         :1;
			uint8_t ccmst        :1;
			uint8_t fsmst        :1;
			uint8_t mmst         :1;
			uint8_t res2         :1;
			uint8_t ccmspt       :1;
			uint8_t fsmspt       :1;
			uint8_t mmspt        :1;
		}bits;
	}spn_1221;
	 
	 union {
	 	struct{
			uint8_t spn_1222_h   :8;
			uint8_t spn_1222_l   :8;
 		}ubyte;
		struct{
			uint8_t res          :3;
			uint8_t nmhccc       :1;
			uint8_t noxcc        :1;
			uint8_t dpf          :1;
			uint8_t bpcs         :1;
			uint8_t csasms       :1;
			uint8_t egrsmspt     :1;
			uint8_t oxyshmspt    :1;
			uint8_t oxysmspt     :1;
			uint8_t acsrmspt     :1;
			uint8_t sasmspt      :1;
			uint8_t evapsmspt    :1;
			uint8_t hcmspt       :1;
			uint8_t catmspt      :1;
		}bits;
	}spn_1222;
	 
	 union{
	 	struct{
			uint8_t spn_1223_h   :8;
			uint8_t spn_1223_l   :8;
 		}ubyte;
		struct{
			uint8_t res          :3;
			uint8_t nmhccc       :1;
			uint8_t noxcc        :1;
			uint8_t dpf          :1;
			uint8_t bpcs         :1;
			uint8_t csasms       :1;
			uint8_t egrsms       :1;
			uint8_t oxyshms      :1;
			uint8_t oxysms       :1;
			uint8_t acsrms       :1;
			uint8_t sasms        :1;
			uint8_t evapsms      :1;
			uint8_t hcms         :1;
			uint8_t catms        :1;
		}bits;
	}spn_1223;
	
}J1939_73_dm5_65230_T;
extern J1939_73_dm5_65230_T     J1939_73_dm5;

/* j1939 73 dm8 (0x00FED0) parameters structure define */
typedef struct {

	uint8_t spn_1224    :8;

	uint8_t spn_1225    :8;

	uint16_t spn_1226   :16;

	uint16_t spn_1227   :16;

	uint16_t spn_1228   :16;
}J1939_73_dm8_65232_T;
extern J1939_73_dm8_65232_T     J1939_73_dm8;

/* j1939 pgn HOURS (0x00FEE5) parameters structure define */
typedef struct {
	struct {
		uint8_t spn_1213     :2;
		uint8_t spn_623      :2;
		uint8_t spn_624      :2;
		uint8_t spn_987      :2;
	}byte1;
	struct {
		uint8_t spn_3038     :2;
		uint8_t spn_3039     :2;
		uint8_t spn_3040     :2;
		uint8_t spn_3041     :2;
	}byte2;
}J1939_DM1_Header_T;

typedef union {
	uint32_t dtc;
	struct {
		uint8_t spn_1214_l   :8; //low 8 bits of spn1214
		uint8_t spn_1214_m   :8; //middle 8 bits of spn1214
		uint8_t spn_1214_h   :3; //high 3 bits of spn1214
		uint8_t spn_1215     :5;
		uint8_t spn_1706     :1;
		uint8_t spn_1216     :7;
	}byte1234;
}J1939_DM1_DTC_T;

#define MAX_SIZE_OF_J1939_DTC 5
typedef struct {
	J1939_DM1_Header_T header;
	J1939_DM1_DTC_T    dtc[MAX_SIZE_OF_J1939_DTC];
} J1939_PGN_DM1_T;
extern J1939_PGN_DM1_T   pgn_dm1, pgn_dm2;

/* j1939 73 dm13 (0x00DFD0) parameters structure define */
typedef union {
    uint8_t Data[8];
	struct{
		struct {
			uint8_t spn_1230     :2;
			uint8_t spn_608      :2;
			uint8_t spn_622      :2;
			uint8_t spn_639      :2;
		}byte1;
		struct {
			uint8_t spn_1231     :2;
			uint8_t spn_1232     :2;
			uint8_t spn_1233     :2;
			uint8_t spn_1234     :2;
		}byte2;
		struct {
			uint8_t spn_1235     :2;
			uint8_t spn_res1     :2;
			uint8_t spn_res2     :2;
			uint8_t spn_res3     :2;
		}byte3;
		struct {
			uint8_t spn_1236     :4;
			uint8_t spn_2618     :4;
		}byte4;
		struct {
			uint16_t spn_2619    :16;
		}byte56;
		struct {
			uint16_t spn_res     :16;
		}byte78;
	}spn;
}J1939_73_dm13_57088_T;
extern J1939_73_dm13_57088_T     J1939_73_dm13;


#endif /* End of J1939_APP_H */
