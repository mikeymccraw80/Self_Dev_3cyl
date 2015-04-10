from PyDevice import *


Set(SIMULATOR, 0, "Battery Control State", 1)
#Wait(100)
#Set(SIMULATOR, 0, "Key Switch State", 1)
Wait(2000)
Set(SIMULATOR, 0, "Key Switch State", 3)
Set(SIMULATOR, 0, "RPM", 800)
error_min =0.95
error_max =1.05
Test_times =1

TTB_Results("Test case 1", 0, "Analog input signal test; change the output of analog channel from 0v to 5v, read the actual value acquired by ECU and compare it with expected value ", " ")  
#define test varible
                        #Alias Name,   Symbolic Name, normal,        k,      b
Analog_Inputs_Table = (
                        ("MAP",        "VMAP",        0.2,           5,      0), \
                        ("O2A",        "OXYGEN_1",    0.2,           5,      0), \
                        ("O2B",        "OXYGEN_2",    0.2,           5,      0), \
                        ("TPSPD",       "TPS1",       0.2,           5,      0), \
                        ("TPSPU",       "TPS2",       0.2,           5,      0), \
                        ("PPS1",        "PEDAL_1",    0.2,           5,      0), \
                        ("PPS2",        "PEDAL_2",    0.2,           5,      0), \
                        ("ACPRS",       "AC_Pre",     0.2,           5,      0), \
                    
                     )
n =0
for AliasName, symbol_name, normal, k, b in Analog_Inputs_Table:
    n = n +1
    TTB_Results("Test case 1.%d"%(n), 0, "%s signal test"%(AliasName), " ")  

    for j in range(0, 6):
        Set(SIMULATOR, 0, AliasName, j*0.2)
        
        for times in range(1,Test_times+1):
            Wait(1000)
            SimIn = Get(SIMULATOR, 0, AliasName)
            Wait(1000)
            (retc, Data) = ReadMemValue(PROCESSOR, 0, symbol_name,2,0,1)
            DataE = SimIn*k+b
            ULimit = DataE*error_max
            LLimit = DataE*error_min
            msg = ("Desc: \"Set the target output of %s is %4.2fV, read the sensor actual output\" Actual: %4.2f Low: %4.2f High: %4.2f " % ( AliasName, DataE, Data, LLimit, ULimit))
            caseid = "AI_%s_%2.2fV" % (AliasName, j)
            TTB_Results(caseid, 0, msg)

    Set(SIMULATOR, 0, AliasName, normal) 

Table = (
         ("MAT",  "TA",     (450,1200,2700,7200,200000)), \
         ("CTS",  "ECT",    (680,1820,4100,10920,200000)), \
         ("FEVAP",  "EVAP_T",(1100,2800,6000,16000,200000)), \
      
               )

for AliasName, symbol_name, INPUTDATA in Table:
    n = n +1
    TTB_Results("Test case 1.%d"%(n), 0, "%s signal test"%(AliasName), " ")  
    for j in range(1, 6):

        Set(SIMULATOR, 0, AliasName, INPUTDATA[j-1])
        for times in range(1,Test_times+1):
            Wait(1000)
            SimIn = Get(SIMULATOR, 0, AliasName)
            Wait(1000)
            (retc, Data) = ReadMemValue(PROCESSOR, 0, symbol_name,2,0,1)

            DataE =j

            ULimit = DataE*error_max
            LLimit = DataE*error_min

            msg = ("Desc: \"Set the target output of %s is %4.2f ohm, read the sensor actual output\" Actual: %4.2f Low: %4.2f High: %4.2f " % ( AliasName, SimIn, Data, LLimit, ULimit))
            caseid = "AI_%s_%2.2fV" % (AliasName, j)
            TTB_Results(caseid, 0, msg)

    Set(SIMULATOR, 0, AliasName, 2000)


#######################DI
TTB_Results("Test case 2", 0, "Discrete input signal test; set the discrete input channel to the expected state, read the actual state acquired by ECU, and compare it with expected state", " ")
Table = (
         ("ACREQ",  "AC_REQUEST", (0, 1),(0, 1)), \
         ("MIDAC",  "ACP_SWH",    (0, 1),(0, 1)), \
         ("ELOAD2",  "HEAD_LAMP", (0, 1),(0, 1)), \
         ("PSPS",   "P_STEER",    (1, 0),(0, 1)), \
         ("BRKSW",  "BRK_SWITCH", (0, 1),(0, 1)), \
         ("PSPS",  "CLUTCH_TOP",  (1, 0),(0, 1)), \
         ("ELOAD1",  "CRANK_REQ", (0, 1),(0, 1)), \
     )
n =0
for AliasName, symbol_name, Act,Ac_state in Table:

    n = n +1
    TTB_Results("Test case 2.%d"%(n), 0, "%s signal test"%(AliasName), " ")  
    for i in range(0,2):
        Set(SIMULATOR, 0, AliasName, Act[i])

        for times in range(1,Test_times+1):
            Wait(1500)
            (retc, State) = ReadMemValue(PROCESSOR, 0, symbol_name)
            msg = ("Desc: \"Set the target output of %s is %2.0fv, read the sensor actual output  \" Actual: %d Low: %d High: %d " % ( AliasName, Act[i]*12, State, Ac_state[i], Ac_state[i]))
            caseid = "DI_%s_%dv" % (AliasName, Act[i]*12)
            TTB_Results(caseid, 0, msg)

    Set(SIMULATOR, 0, AliasName, Act[0])

#######################Disceret output####
TTB_Results("Test case 3", 0, "Discrete output signal test; set the channel output the expected state by modify the relevant calibration vars and read the actual state.", " ")
Table = (
           ( "FANLO PW", "KT_DO.FAN1", (0, 1), (1, 0),"FAN1"), \
           ( "FANHI PW", "KT_DO.FAN2", (0, 1), (1, 0), "FAN2"), \
           ( "FPR PW", "KT_DO.FUEL_PUMP", (0, 1), (1, 0), "FUEL_PUMP"), \
           ( "MIL PW", "KT_DO.MIL_LAMP", (0, 1), (1, 0), "MIL_LAMP"), \
           ( "SVS PW", "KT_DO.SVS_LAMP", (0, 1), (1, 0), "SVS_LAMP"), \
           ( "ACCLUTCH PW", "KT_DO.AC_CLUTCH", (0, 1), (1, 0), "AC_CLUTCH"), \
           ( "TURLF PW", "KT_DO.R_LINE", (0, 1), (1, 0), "R_line"), \
           ( "CRSMLP PW", "KT_DO.START_MOTR_RLY", (0, 1), (1, 0), "START_MOTR_RLY"), \
           #( "FAN", "DO_T.VIS_SWITCH", (0, 1), (0, 1)), \
           ( "MPR PW", "KT_DO.MAIN_RELAY", (0, 1), (1, 0), "MAIN_RELAY"), \

        )
n =0
for AliasName, symbol_name, Set_State,R_state, Sensor_name in Table:
    n = n +1
    TTB_Results("Test case 3.%d"%(n), 0, "%s signal test"%(Sensor_name), " ")  
    for i in range(0,2):

        WriteMemValue(PROCESSOR, 0, symbol_name, Set_State[i])
        if i==1:
            state ="On"
        else:
            state ="Off"
            
        for times in range(1,Test_times+1):
            Wait(1000)
            SimOut = Get(SIMULATOR, 0, AliasName)
            msg = ("Desc: \"Set the state of %s is %s, read the actual output state \" Actual: %d Low: %d High: %d " % ( Sensor_name, state, SimOut, R_state[i], R_state[i]))
            caseid = "DO_%s_%s" % (Sensor_name, state)
            TTB_Results(caseid, 0, msg)


#######################PWM output####
TTB_Results("Test case 4", 0, "PWM output signal frequency and duty test; change the frequency and duty of PWM output channel and read the actual duty and frequency.", " ")
Table=(
         ("O2AHTR PW","O2AHTR PE", "KT_PO_O2_heater_1.duty", "KT_PO_O2_heater_1.period", "KT_PO_O2_heater_1.B_enable", "O2A_HEATER"),\
         ("O2BHTR PW", "O2BHTR PE", "KT_PO_O2_heater_2.duty", "KT_PO_O2_heater_2.period", "KT_PO_O2_heater_2.B_enable", "O2B_HEATER"),\
         ("CCP PW", "CCP PE", "KT_PO_PURGE.duty", "KT_PO_PURGE.period", "KT_PO_PURGE.B_enable", "CCP"),\
         ("CLTOUT PW", "CLTOUT PE", "KT_PO_ECT.duty", "KT_PO_ECT.period", "KT_PO_ECT.B_enable", "TUAWG"),\
         ("VVT1 PW", "VVT1 PE", "KT_PO_VVT1.duty", "KT_PO_VVT1.period", "KT_PO_VVT1.B_enable", "VVT1"),\
         ("VVT2 PW", "VVT2 PE", "KT_PO_VVT2.duty", "KT_PO_VVT2.period", "KT_PO_VVT2.B_enable", "VVT2"),\
         ("LEGR PW", "LEGR PE", "KT_PO_FUEL_CSP.duty", "KT_PO_FUEL_CSP.period", "KT_PO_FUEL_CSP.B_enable", "FUEL_CSP"),\

       )
n =0
for AliasName_duty, AliasName_period, symbol_duty, symbol_period, set_enable, sensor_name in Table:
    n = n +1
    TTB_Results("Test case 4.%d"%(n), 0, "%s signal test"%(sensor_name), " ")  
    WriteMemValue(PROCESSOR, 0, set_enable, 1) # enable the pwm output
    Wait(500)
    m =0
    for j in range(1,6):
        period_temp =j*20
        period_set =1000/period_temp
        WriteMemValue(PROCESSOR, 0, symbol_period, period_temp)
        
        for i in range(1,6):  ###duty is range form 20% to 100% (example:duty = 50% -> 0.5*255)
            Duty_set = i*20
            duty_temp =Duty_set*255/100
            WriteMemValue(PROCESSOR, 0, symbol_duty, duty_temp)
            for times in range(1,Test_times+1):
                Wait(2000)
                m =m+1
                SimOut = Get(SIMULATOR, 0, AliasName_period)
                ULimit = period_set*error_max
                LLimit = period_set*error_min
                msg = ("Desc: \"Set the target frequency of %s PWM output is %2.2fHz, read the actual frequency of pwm output \" Actual: %2.2f  Low: %2.2f High: %2.2f " % ( sensor_name, period_set, SimOut, LLimit, ULimit))
                caseid = "PO_%s_frequency=%dHz_duty=%d_%dth" % (sensor_name, period_set, Duty_set, m)
                TTB_Results(caseid, 0, msg)
                
                SimOut = Get(SIMULATOR, 0, AliasName_duty)
                ULimit = Duty_set*error_max
                LLimit = Duty_set*error_min
                msg = ("Desc: \"Set the target duty of %s PWM output is %2.2f precent, read the actual duty of pwm output \" Actual: %2.2f  Low: %2.2f High: %2.2f " % ( sensor_name, Duty_set, 100 - 100*SimOut, LLimit, ULimit))
                caseid = "PO_%s_duty=%d_frequency=%dHz_%dth" % (sensor_name, Duty_set, period_set, m)
                TTB_Results(caseid, 0, msg)
    WriteMemValue(PROCESSOR, 0, set_enable, 0)

#######################etc output####
TTB_Results("Test case 5", 0, "ETC output signal frequency and direction test;", " ")
Table=(
         ("PWTT PE","BANK_A", (2000, 0)),\
         ("BIP1 PE", "BANK_B", (0, 2000)),\

       )
duty_set =50*65535/100
WriteMemValue(PROCESSOR, 0, "KT_etc.enable", 1) # enable the etc output
WriteMemValue(PROCESSOR, 0, "KT_etc.duty", duty_set)# set the etc PWM duty to 50%
Wait(1000)
for i in range(0,2):
    WriteMemValue(PROCESSOR, 0, "KT_etc.direction", i)
    Wait(5000)
    for AliasName, signal_name, Frequence_set in Table:

        SimOut = Get(SIMULATOR, 0, AliasName)  # get the chanel frequency is 2000hz
        ULimit = Frequence_set[i]*error_max
        LLimit = Frequence_set[i]*error_min
        msg = ("Desc: \"Set the etc output direction is %d, the %s output frequency is %d Hz, read the actual output frequency and compare it with the expected frequency\" Actual: %d  Low: %d  High: %d " % (i, signal_name, Frequence_set[i], SimOut, LLimit, ULimit)) #direction and frequency test
        caseid = "%s_Direction=%d" % (signal_name, i)
        TTB_Results(caseid, 0, msg)
#########etc duty test ##############
TTB_Results("Test case 6", 0, "ETC output signal duty test; set the etc output signal duty from 0% to 100%, and read the etc actual output duty", " ")
WriteMemValue(PROCESSOR, 0, "KT_etc.direction", 0)
WriteMemValue(PROCESSOR, 0, "KT_etc.enable", 1) # enable the etc output
for i in range(0,6):
    Duty_set = i*20
    WriteMemValue(PROCESSOR, 0, "KT_etc.duty", Duty_set*65535/100)# set the etc PWM duty from 0% to 100%
    for times in range(1,Test_times+1):
        Wait(2000)
        SimOut = Get(SIMULATOR, 0, "PWTT PW")*100 ###should be renamed
        ULimit = Duty_set*error_max
        LLimit = Duty_set*error_min
        msg = ("Desc: \"Set the target etc duty is %d precent, read the actual etc output signal duty\" Actual: %2.2f  Low: %d High: %d " % (Duty_set, SimOut, LLimit, ULimit)) #duty test
        caseid = "ETC_duty=%d" % (Duty_set)
        TTB_Results(caseid, 0, msg)


