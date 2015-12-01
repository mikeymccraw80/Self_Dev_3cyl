from PyDevice import *

def Get_InjectAngle(i):
    if i*2.8125 <=90:
        j = 90
    else:
        j = i*2.8125

    return j

#####convert the angle to width
def convert_angle_to_time(angle, rpm_n):  # units:angle->dgree  rpm_n ->r/min  time_width->us

    time_width = angle*1000000 / (rpm_n*6)

    return time_width

def Inject_end_angle(real_ang, refen_ang, zore_ang):
    if refen_ang < real_ang:
        return zore_ang + 720 - real_ang
    else:
        return zore_ang  - real_ang

####caculate the max dwell time at the rpm
def dwell_time_max(rpm_real):
    time_max =(60*1000000/2*0.8)/rpm_real
    return time_max

Set(SIMULATOR, 0, "Battery Control State", 1)
Wait(100)
#Set(SIMULATOR, 0, "Key Switch State", 1)
Wait(2000)
Set(SIMULATOR, 0, "Key Switch State", 3)
Set(SIMULATOR, 0, "Dataset", 1)
Set(SIMULATOR, 0, "RPM", 0)
Wait(2000)
Set(SIMULATOR, 0, "RPM", 800)
error_min =0.95
error_max =1.05
Test_times =1

##########################################################################################
##########################################################################################
######Spark relevant Test

Table = (
           ("KT_IgnA.dwell_time", "KT_IgnA.ign_angle", "KT_IgnA.follow_up_sparks", ), \
           ("KT_IgnB.dwell_time", "KT_IgnB.ign_angle", "KT_IgnB.follow_up_sparks", ), \
           ("KT_IgnC.dwell_time", "KT_IgnC.ign_angle", "KT_IgnC.follow_up_sparks", ), \
#           ("KT_IgnD.dwell_time", "KT_IgnD.ign_angle", "KT_IgnD.follow_up_sparks", ), \

         )
###Inital the spark relavant parameter
for symbol_name1, symbol_name2, symbol_name3 in Table:
     WriteMemValue(PROCESSOR, 0, symbol_name1, 4000)#inital the dewell time  
     WriteMemValue(PROCESSOR, 0, symbol_name2, 128) #inital the ign_angle that make the advance ignition angle is 0
     WriteMemValue(PROCESSOR, 0, symbol_name3, 0)   #inital the follow_up_sparks with 0 that disable multiple spark

####################Spark enable#########################
TTB_Results("Test case 1", 0, "Spark enable test; enable or disable the spark channel, and read the actual state.", " ") 
Table = (
           ("EST1 PW", "KT_IgnA.enable", (0,1), "Spark_A"), \
           ("EST2 PW", "KT_IgnB.enable", (0,1), "Spark_B"), \
           ("EST3 PW", "KT_IgnC.enable", (0,1), "Spark_C"), \
         )

for AliasName, symbol_name1, Set_State, Spark_chanel in Table:
    for i in range(0,2):
        WriteMemValue(PROCESSOR, 0, symbol_name1, Set_State[i])
        Wait(3000)
        for times in range(1, Test_times+1):
            SimOut = Get(SIMULATOR, 0, AliasName)# get the relavant port's frequency whether is zero
            
            if Set_State[i] ==1:
                state ="Enable"
                msg = ("Desc: \"Enable the state of the Spark A&C, and read the state of the spark\" Actual: %d Low: %d High: %d " % (SimOut, 0, 1))
            elif Set_State[i] ==0:
                state ="Disable"
                msg = ("Desc: \"Disable the state of the Spark B&D, and read the state of the spark\" Actual: %d Low: %d High: %d " % (SimOut, 1, 1))

            caseid = "%s_state=%s_%dth" % (Spark_chanel, state, times)
            TTB_Results(caseid, 0, msg)
            Wait(1000)

"""
####################main Spark dwell time#########################
TTB_Results("Test case 2", 0, "spark dwell time test; set the spark advance angle is 0degree, set the target spark dwell time and read the actual dwell time that captured by OPAL-RT", " ") 
Table = (
           ("EST1 D", "KT_IgnA.enable", "KT_IgnA.dwell_time", "KT_IgnA.ign_angle" ,"Spark_A"), \
           ("EST2 D", "KT_IgnB.enable", "KT_IgnB.dwell_time", "KT_IgnB.ign_angle", "Spark_B" ), \
           ("EST1 D", "KT_IgnC.enable", "KT_IgnC.dwell_time", "KT_IgnC.ign_angle", "Spark_C" ), \
           ("EST2 D", "KT_IgnD.enable", "KT_IgnD.dwell_time", "KT_IgnD.ign_angle", "Spark_D" ), \

         )
Set(SIMULATOR, 0, "RPM", 0)

for AliasName,symbol_name1, symbol_name2, symbol_name3, spark_chanel in Table:
    if symbol_name1 == "KT_IgnA.enable":
        WriteMemValue(PROCESSOR, 0, "KT_IgnA.enable", 1)#enable the sparkA
        WriteMemValue(PROCESSOR, 0, "KT_IgnC.enable", 0)#disenable the sparkC
    elif symbol_name1 == "KT_IgnB.enable":
        WriteMemValue(PROCESSOR, 0, "KT_IgnB.enable", 1)#enable the sparkB
        WriteMemValue(PROCESSOR, 0, "KT_IgnD.enable", 0)#disenable the sparkD
    elif symbol_name1 == "KT_IgnC.enable":
        WriteMemValue(PROCESSOR, 0, "KT_IgnA.enable", 0)#disenable the sparkA
        WriteMemValue(PROCESSOR, 0, "KT_IgnC.enable", 1)#enable the sparkC
    elif symbol_name1 == "KT_IgnD.enable":
        WriteMemValue(PROCESSOR, 0, "KT_IgnB.enable", 0)#enable the sparkD
        WriteMemValue(PROCESSOR, 0, "KT_IgnD.enable", 1)#disenable the sparkB
    

    WriteMemValue(PROCESSOR, 0, symbol_name3, 128)#Set spark advance angle is 0
   
    
    for i in range(1,7):
        Speed_set =i*1000
       
        Set(SIMULATOR, 0, "RPM", Speed_set)  ##in different rpm
        for j in range(0,11):
            dwell_time_set =j*1000
            WriteMemValue(PROCESSOR, 0, symbol_name2, dwell_time_set)
            Wait(2000)
            for times in range(1, Test_times+1):
                SimOut_width = Get(SIMULATOR, 0, AliasName)
                SimOut_width = convert_angle_to_time(SimOut_width, Speed_set)

                dwell_time_max_set =dwell_time_max(Speed_set)
                if dwell_time_set >= dwell_time_max_set:
                    
                    Set_time_low = dwell_time_max_set * error_min
                    Set_time_up  = dwell_time_max_set * error_max
                else:
                    Set_time_low = dwell_time_set * error_min
                    Set_time_up  = dwell_time_set * error_max
                msg = ("Desc: \"Set the %s target dwell time is %dus, engine speed is %drpm, read the actual dwell time \" Actual: %d Low: %d High: %d " % (spark_chanel, dwell_time_set,Speed_set, SimOut_width, Set_time_low, Set_time_up))
                caseid = "%s_dwell_time=%dus_%drpm_%dth" % (spark_chanel, dwell_time_set, Speed_set, times)
                TTB_Results(caseid, 0, msg)
                Wait(1000)
             
    WriteMemValue(PROCESSOR, 0, symbol_name2, 4000) #reset the dwell time is 4000us after finish test
"""

####################Spark dwell time and advance angle test #########################
TTB_Results("Test case 2", 0, "Spark dwell time and advance angle test; test condition: spark dwell time=2, 5, 10ms; advance angle=-60, -30, -10, 10, 30, 60CrA; rpm =1000, 3000, 5000; ", " ") 
Table = (
           ("EST1 A", "EST1 D","KT_IgnA.enable", "KT_IgnA.dwell_time", "KT_IgnA.ign_angle", "Spark_A" ), \
           ("EST2 A", "EST2 D","KT_IgnB.enable", "KT_IgnB.dwell_time", "KT_IgnB.ign_angle", "Spark_B" ), \
           ("EST3 A", "EST3 D","KT_IgnC.enable", "KT_IgnC.dwell_time", "KT_IgnC.ign_angle", "Spark_C" ), \
#           ("EST2 A", "EST2 D","KT_IgnD.enable", "KT_IgnD.dwell_time", "KT_IgnD.ign_angle", "Spark_D" ), \

         )###the AliasName should be renamed

Set(SIMULATOR, 0, "RPM", 0)
Spark_angle_Table=(48, 88, 128, 168, 208) #-60, -30, -10, 10, 30, 60degree
Spark_dwell_time_Table=(2000, 5000, 10000)

for i in range(0,3):
    speed_set = i*2000+1000
    Set(SIMULATOR, 0, "RPM", speed_set)
    TTB_Results("Test case 2.%d"%(i+1), 0, "Test condition: rpm = %d"%(speed_set)," ")
    for AliasName1,AliasName2,symbol_name1, symbol_name2, symbol_name3, Spark_chanel in Table:
        if symbol_name1 == "KT_IgnA.enable":
            WriteMemValue(PROCESSOR, 0, "KT_IgnA.enable", 1)#enable the sparkA
            TDC_angle = 361 + 15*6#inorder to match the signal of opal-rt
        elif symbol_name1 == "KT_IgnB.enable":
            WriteMemValue(PROCESSOR, 0, "KT_IgnB.enable", 1)#enable the sparkB
            TDC_angle = 361 + 55*6
        elif symbol_name1 == "KT_IgnC.enable":
            WriteMemValue(PROCESSOR, 0, "KT_IgnB.enable", 1)#enable the sparkC
            TDC_angle = 35*6
        m =0
        for j in range(0,5): ##The spark advance angle is from -60degree to 60degree
            
            WriteMemValue(PROCESSOR, 0, symbol_name3, Spark_angle_Table[j])
            Set_ang = (Spark_angle_Table[j]-128)*0.75# the set advance angle
            
            for k in range(0,3):
                dwell_time_set =Spark_dwell_time_Table[k]
                WriteMemValue(PROCESSOR, 0, symbol_name2, dwell_time_set)
                Wait(3000)
                for times in range(1, Test_times+1):
                    m = m+1
                    

                    SimOut_width = Get(SIMULATOR, 0, AliasName2)
                    fall_to_raise_edge =SimOut_width
                    SimOut_width = convert_angle_to_time(SimOut_width, speed_set)

                    #dwell_time_max_set =dwell_time_max(speed_set)
                    #if dwell_time_set >= dwell_time_max_set:

                    #    Set_time_low = dwell_time_max_set * error_min
                    #    Set_time_up  = dwell_time_max_set * error_max
                    #else:
                    Set_time_low = dwell_time_set * error_min
                    Set_time_up  = dwell_time_set * error_max

                    msg = ("Desc: \"Set the %s target dwell time is %dms, spark advance angle is %dCrA, engine speed is %drpm, fall_to_raise_edge=%3.1fdegree, read the actual dwell time \" Actual: %2.2f Low: %2.2f High: %2.2f " % (Spark_chanel, dwell_time_set/1000, Set_ang, speed_set, fall_to_raise_edge, SimOut_width/1000, Set_time_low/1000, Set_time_up/1000))
                    caseid = "%s_dwell_time=%dms_advance=%d_%drpm_%dth" % (Spark_chanel, dwell_time_set/1000, Set_ang, speed_set, m)
                    TTB_Results(caseid, 0, msg)
                    Wait(1000)

                    SimOut_width = Get(SIMULATOR, 0, AliasName2)
                    SimOut_angle = Get(SIMULATOR, 0, AliasName1)
                    temp = SimOut_angle + SimOut_width
                    if temp >=TDC_angle +100:
                        temp = temp -720
                     
                    simOut =  TDC_angle - temp #captured advance angle
                    if Set_ang >=0:
                        Set_ang_low = Set_ang*error_min
                        Set_ang_up  = Set_ang *error_max
                    else:
                        Set_ang_low = Set_ang*error_max
                        Set_ang_up  = Set_ang *error_min
                     
                    msg = ("Desc: \"Set the %s target spark advance angle is %2.1fCrA, dwell time is %dms, engine speed is %drpm, fall_edge =%3.1fdegree, read the actual spark advance angle\" Actual: %2.1f Low: %2.1f High: %2.1f " % (Spark_chanel, Set_ang, dwell_time_set/1000, speed_set, SimOut_angle, simOut, Set_ang_low, Set_ang_up))
                    caseid = "%s_advance=%2.1f_dwell_time=%dms_%drpm_%dth" % (Spark_chanel, Set_ang, dwell_time_set/1000, speed_set,  m)
                    TTB_Results(caseid, 0, msg)
                     
             
    WriteMemValue(PROCESSOR, 0, symbol_name3, 128) #reset the spark advance angle 0 degree
    WriteMemValue(PROCESSOR, 0, symbol_name2, 1000)


"""
Set(SIMULATOR, 0, "RPM", 1000)
Wait(2000)
TTB_Results("Test case 3", 0, "Inject time and end angle test at cam backup mode in different rpm(1000, 2000, 3000rpm);", " ")
WriteMemValue(PROCESSOR, 0, "KyHWIO_Delta_Angle_From_Edge_To_Tooth_1", 48)
Set(SIMULATOR, 0, "Dataset", 10)
error_max = 1.1
error_min = 0.9
Wait(5000)
for i in range(0,3):
    speed_set = i*1000+1000
    Set(SIMULATOR, 0, "RPM", speed_set)
    TTB_Results("Test case 3.%d"%(i+1), 0, "Test condition: rpm = %d"%(speed_set)," ")
    for AliasName1,AliasName2,symbol_name1, symbol_name2, symbol_name3, Spark_chanel in Table:
        if symbol_name1 == "KT_IgnA.enable":
            WriteMemValue(PROCESSOR, 0, "KT_IgnA.enable", 1)#enable the sparkA
            WriteMemValue(PROCESSOR, 0, "KT_IgnC.enable", 0)#disenable the sparkC
            TDC_angle = 361 + 20*6
        elif symbol_name1 == "KT_IgnB.enable":
            WriteMemValue(PROCESSOR, 0, "KT_IgnB.enable", 1)#enable the sparkB
            WriteMemValue(PROCESSOR, 0, "KT_IgnD.enable", 0)#disenable the sparkD
            TDC_angle = 361 + 50*6
        elif symbol_name1 == "KT_IgnC.enable":
            WriteMemValue(PROCESSOR, 0, "KT_IgnA.enable", 0)#disenable the sparkA
            WriteMemValue(PROCESSOR, 0, "KT_IgnC.enable", 1)#enable the sparkC
            TDC_angle = 20*6+1
        elif symbol_name1 == "KT_IgnD.enable":
            WriteMemValue(PROCESSOR, 0, "KT_IgnB.enable", 0)#enable the sparkD
            WriteMemValue(PROCESSOR, 0, "KT_IgnD.enable", 1)#disenable the sparkB
            TDC_angle = 50*6+1
        m =0
        for j in range(0,5): ##The spark advance angle is from -60degree to 60degree
            
            WriteMemValue(PROCESSOR, 0, symbol_name3, Spark_angle_Table[j])
            Set_ang = (Spark_angle_Table[j]-128)*0.75# the set advance angle
            
            for k in range(0,3):
                dwell_time_set =Spark_dwell_time_Table[k]
                WriteMemValue(PROCESSOR, 0, symbol_name2, dwell_time_set)
                Wait(3000)
                for times in range(1, Test_times+1):
                    m = m+1
                    

                    SimOut_width = Get(SIMULATOR, 0, AliasName2)
                    fall_to_raise_edge =SimOut_width
                    SimOut_width = convert_angle_to_time(SimOut_width, speed_set)

                    #dwell_time_max_set =dwell_time_max(speed_set)
                    
                    if dwell_time_set >= dwell_time_max_set:

                        Set_time_low = dwell_time_max_set * error_min
                        Set_time_up  = dwell_time_max_set * error_max
                    else:
                    Set_time_low = dwell_time_set * error_min
                    Set_time_up  = dwell_time_set * error_max

                    msg = ("Desc: \"Set the %s target dwell time is %dms, spark advance angle is %dCrA, engine speed is %drpm, fall_to_raise_edge=%3.1fdegree, read the actual dwell time \" Actual: %2.2f Low: %2.2f High: %2.2f " % (Spark_chanel, dwell_time_set/1000, Set_ang, speed_set, fall_to_raise_edge, SimOut_width/1000, Set_time_low/1000, Set_time_up/1000))
                    caseid = "%s_dwell_time=%dms_advance=%d_%drpm_backup_%dth" % (Spark_chanel, dwell_time_set/1000, Set_ang, speed_set, m)
                    TTB_Results(caseid, 0, msg)
                    Wait(1000)

                    SimOut_width = Get(SIMULATOR, 0, AliasName2)
                    SimOut_angle = Get(SIMULATOR, 0, AliasName1)
                    temp = SimOut_angle + SimOut_width
                    if temp >=TDC_angle +100:
                        temp = temp -720
                     
                    simOut =  TDC_angle - temp #captured advance angle
                    if Set_ang >=0:
                        Set_ang_low = Set_ang*error_min
                        Set_ang_up  = Set_ang *error_max
                    else:
                        Set_ang_low = Set_ang*error_max
                        Set_ang_up  = Set_ang *error_min
                     
                    msg = ("Desc: \"Set the %s target spark advance angle is %2.1fCrA, dwell time is %dms, engine speed is %drpm, fall_edge =%3.1fdegree, read the actual spark advance angle\" Actual: %2.1f Low: %2.1f High: %2.1f " % (Spark_chanel, Set_ang, dwell_time_set/1000, speed_set, SimOut_angle, simOut, Set_ang_low, Set_ang_up))
                    caseid = "%s_advance=%2.1f_dwell_time=%dms_%drpm__backup_%dth" % (Spark_chanel, Set_ang, dwell_time_set/1000, speed_set,  m)
                    TTB_Results(caseid, 0, msg)
                     
             
    WriteMemValue(PROCESSOR, 0, symbol_name3, 128) #reset the spark advance angle 0 degree
    WriteMemValue(PROCESSOR, 0, symbol_name2, 1000)
Set(SIMULATOR, 0, "Dataset", 1)
Set(SIMULATOR, 0, "RPM", 0)

"""

