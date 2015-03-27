from PyDevice import *


Set(SIMULATOR, 0, "Battery Control State", 1)
#Wait(100)
#Set(SIMULATOR, 0, "Key Switch State", 1)
Wait(2000)
Set(SIMULATOR, 0, "Key Switch State", 3)
Set(SIMULATOR, 0, "RPM", 800)
error_min =0.95
error_max =1.05
Test_times =20

TTB_Results("Analog input signal test", 0, " ", " ")  
#define test varible
                        #Alias Name,   Symbolic Name, normal,        k,      b
Analog_Inputs_Table = (
                        ("MAP",        "VMAP",        0.2,           5,      0), \
                        ("O2A",        "OXYGEN_1",    0.2,           5,      0), \
                        ("O2B",        "OXYGEN_2",    0.2,           5,      0), \
                        ("TPSPD",       "TPS1",       0.2,           5,      0), \
                        ("TPSPU",       "TPS2",       0.2,           5,      0), \
                        ("PPS1",        "PEDAL_1",    0.2,           5,      0), \
                        ("PPS1",        "PEDAL_2",    0.2,           5,      0), \
                        ("ACPRS",       "AC_Pre",     0.2,           5,      0), \
                    
                     )

for AliasName, symbol_name, normal, k, b in Analog_Inputs_Table:

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
            msg = ("Desc: \"Set the output of %s is %4.2fV, read the sensor actual output and compare it with the expected value\" Actual: %4.2fv Low: %4.2fv High: %4.2fv " % ( AliasName, DataE, Data, LLimit, ULimit))
            caseid = "AI_%s_%2.2fV_%d" % (AliasName, j, times)
            TTB_Results(caseid, 0, msg)

    Set(SIMULATOR, 0, AliasName, normal) 

Table = (
         ("MAT",  "TA",     (450,1200,2700,7200,200000)), \
         ("CTS",  "ECT",    (680,1820,4100,10920,200000)), \
         ("FEVAP",  "EVAP_T",(1100,2800,6000,16000,200000)), \
      
               )

for AliasName, symbol_name, INPUTDATA in Table:
  
   for j in range(1, 6):
       
      Set(SIMULATOR, 0, AliasName, INPUTDATA[j-1])
      for times in range(1,Test_times+1):
          Wait(1000)
          SimIn = Get(SIMULATOR, 0, AliasName)
          Wait(2000)
          (retc, Data) = ReadMemValue(PROCESSOR, 0, symbol_name,2,0,1)

          DataE =j
       
          ULimit = DataE*error_max
          LLimit = DataE*error_min
          
          msg = ("Desc: \"Set the output of %s is %4.2f ohm, read the sensor actual output and compared it with the expected value\" Actual: %4.2fv Low: %4.2fv High: %4.2fv " % ( AliasName, SimIn, Data, LLimit, ULimit))
          caseid = "AI_%s_%2.2fV_%d" % (AliasName, j,times)
          TTB_Results(caseid, 0, msg)

   Set(SIMULATOR, 0, AliasName, 2000)


#######################DI
TTB_Results("Discrete input signal test", 0, " ", " ")
Table = (
         ("ACREQ",  "AC_REQUEST", (0, 1),(0, 1)), \
         ("MIDAC",  "ACP_SWH",    (0, 1),(0, 1)), \
         ("ELOAD2",  "HEAD_LAMP", (0, 1),(0, 1)), \
         ("PSPS",   "P_STEER",    (1, 0),(0, 1)), \
         ("BRKSW",  "BRK_SWITCH", (0, 1),(0, 1)), \
         ("PSPS",  "CLUTCH_TOP",  (1, 0),(0, 1)), \
         ("ELOAD1",  "CRANK_REQ", (0, 1),(0, 1)), \
            )
for AliasName, symbol_name, Act,Ac_state in Table:
    for i in range(0,2):
        Set(SIMULATOR, 0, AliasName, Act[i])
        
        for times in range(1,Test_times+1):
            Wait(1500)
            (retc, State) = ReadMemValue(PROCESSOR, 0, symbol_name)
            msg = ("Desc: \"Set the output of %s is %2.0f, read the sensor actual output and compare it with the expected state \" Actual: %d Low: %d High: %d " % ( AliasName, Act[i]*12, State, Ac_state[i], Ac_state[i]))
            caseid = "DI_%s_%d_%d" % (AliasName, i, times)
            TTB_Results(caseid, 0, msg)

    Set(SIMULATOR, 0, AliasName, Act[0])

#######################Disceret output####
TTB_Results("Discrete output signal test", 0, " ", " ")
Table = (
           ( "FANLO PW", "K_DO_T.FAN1", (0, 1), (1, 0),"FAN1"), \
           ( "FANHI PW", "K_DO_T.FAN2", (0, 1), (1, 0), "FAN2"), \
           ( "FPR PW", "K_DO_T.FUEL_PUMP", (0, 1), (1, 0), "Fuel_pump"), \
           ( "MIL PW", "K_DO_T.MIL_LAMP", (0, 1), (1, 0), "MIL_lamp"), \
           ( "SVS PW", "K_DO_T.SVS_LAMP", (0, 1), (1, 0), "SVS_lamp"), \
           ( "ACCLUTCH PW", "K_DO_T.AC_CLUTCH", (0, 1), (1, 0), "AC_clutch"), \
          # ( "TURLF PW", "K_DO_T.R_LINE", (0, 1), (1, 0), "R_line"), \
           #( "FAN", "DO_T.START_MOTR_RLY", (0, 1), (0, 1)), \
           #( "FAN", "DO_T.VIS_SWITCH", (0, 1), (0, 1)), \
           ( "MPR PW", "K_DO_T.MAIN_RELAY", (0, 1), (1, 0), "Main_relay"), \

        )
        
for AliasName, symbol_name, Set_State,R_state, Sensor_name in Table:
    for i in range(0,2):

        WriteMemValue(PROCESSOR, 0, symbol_name, Set_State[i])
        for times in range(1,Test_times+1):
            Wait(1000)
            SimOut = Get(SIMULATOR, 0, AliasName)
            msg = ("Desc: \"Set the state of %s is %d, read the actual output state and compare it with the expected state\" Actual: %d Low: %d High: %d " % ( Sensor_name, Set_State[i], SimOut, R_state[i], R_state[i]))
            caseid = "DO_%s_%d_%d" % (Sensor_name, i, times)
            TTB_Results(caseid, 0, msg)


#######################PWM output####
TTB_Results("PWM output signal test", 0, " ", " ")
Table=(
         ("O2AHTR PW","KT_PO_O2_heater_1.duty","KT_PO_O2_heater_1.B_enable", "O2A_heater"),\
         ("O2BHTR PW","KT_PO_O2_heater_2.duty","KT_PO_O2_heater_2.B_enable", "O2B_heater"),\
         ("CCP PW","KT_PO_PURGE.duty","KT_PO_PURGE.B_enable", "CCP"),\
         ("CLTOUT PW","KT_PO_ECT.duty","KT_PO_ECT.B_enable", "TUAWG"),\
         ("VVT1 PW","KT_PO_VVT1.duty","KT_PO_VVT1.B_enable", "VVT1"),\
         ("VVT2 PW","KT_PO_VVT2.duty","KT_PO_VVT2.B_enable", "VVT2"),\
         ("FLVPWM PW","KT_PO_FUEL_CSP.duty","KT_PO_FUEL_CSP.B_enable", "FUEL_CSP"),\

       )
error_min
for AliasName, symbol_name,set_enable, sensor_name in Table:
    WriteMemValue(PROCESSOR, 0, set_enable, 1) # enable the pwm output
    Wait(500)
    for i in range(0,6):  ###duty is range form 0% to 100% (example:duty = 50% -> 0.5*255)
        Duty_set = i*20
        WriteMemValue(PROCESSOR, 0, symbol_name, Duty_set/100*255)
        for times in range(1,Test_times+1):
            Wait(2000)
            SimOut = Get(SIMULATOR, 0, AliasName)
            ULimit = Duty_set*error_max
            LLimit = Duty_set*error_min
            msg = ("Desc: \"Set the duty of %s PWM output is %2.0f %, read the actual duty of pwm output and compare it with the expected duty \" Actual: %4.2f  Low: %d High: %d " % ( sensor_name, i*20, (1- SimOut)*100, LLimit, ULimit))
            caseid = "PO_%s_%d_%d" % (sensor_name, i*20, times)
            TTB_Results(caseid, 0, msg)
    WriteMemValue(PROCESSOR, 0, symbol_name, 0)
    
#######################etc output####
TTB_Results("ETC output signal test", 0, " ", " ")
Table=(
         ("ETCA_PE","ETC_BANK_A", 2000),\
         ("ETCB_PE","ETC_BANK_B", 2000),\

       )
WriteMemValue(PROCESSOR, 0, "KT_etc.enable", 1) # enable the etc output
Wait(1000)
i =0
for AliasName, signal_name, Frequence_set in Table:

    WriteMemValue(PROCESSOR, 0, "KT_etc.direction", i)
    Wait(4000)
    for times in range(1,Test_times+1):
        Wait(1500)
        SimOut = Get(SIMULATOR, 0, AliasName)  # get the chanel frequency is 2000hz
        ULimit = Frequence_set*error_max
        LLimit = Frequence_set*error_min
        msg = ("Desc: \"Read the frequence of etc pwm output %s and compare it with the expected frequence \" Actual: %d  Low: %d High: %d " % ( signal_name, SimOut, LLimit, ULimit)) #direction and frequency test
        caseid = "%s_%d" % (sensor_name, times)
        TTB_Results(caseid, 0, msg)
    i = i +1

#########etc duty test ##############
WriteMemValue(PROCESSOR, 0, "KT_etc.direction", 0)
for i in range(0,6):
    Duty_set = i*20
    WriteMemValue(PROCESSOR, 0, "KT_etc.duty", Duty_set/100*65536)# set the etc PWM duty from 0% to 100%
    for times in range(1,Test_times+1):
        Wait(1500)
        SimOut = Get(SIMULATOR, 0, "ETCA PW")*100 ###should be renamed
        ULimit = Duty_set*error_max
        LLimit = Duty_set*error_min
        msg = ("Desc: \"Set the etc duty is %d %, read the actual duty and compare it with the expected duty\" Actual: %d  Low: %d High: %d " % (Duty_set, SimOut, LLimit, ULimit)) #duty test
        caseid = "ETC_duty_%d_%d" % (i*20, times)
        TTB_Results(caseid, 0, msg)

