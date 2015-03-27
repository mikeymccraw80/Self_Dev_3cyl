from PyDevice import *

def Get_InjectAngle(i):
    if i*2.8125 <=32:
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
    
Set(SIMULATOR, 0, "Battery Control State", 1)
Wait(100)
#Set(SIMULATOR, 0, "Key Switch State", 1)
Wait(2000)
Set(SIMULATOR, 0, "Key Switch State", 3)
Set(SIMULATOR, 0, "RPM", 800)
error_min =0.95
error_max =1.05
Test_times =20
    
#############################################
######Inject relevant Test
########Inject enable
Table = (
           ("INJ1 PW", "KT_InjA.enable", (0,1), "Injector_A"), \
           ("INJ3 PW", "KT_InjB.enable", (0,1), "Injector_B"), \
           ("INJ4 PW", "KT_InjC.enable", (0,1), "Injector_C"), \
           ("INJ2 PW", "KT_InjD.enable", (0,1), "Injector_D"), \

         )
for AliasName, symbol_name, Set_State, Injector in Table:
    for i in range(0,2):
        WriteMemValue(PROCESSOR, 0, symbol_name, Set_State[i])
        Wait(3000)
        for times in range(0, Test_times):
            SimOut = Get(SIMULATOR, 0, AliasName)# get the relavant port's frequency whether is zero
            
            if Set_State[i] ==1:
                msg = ("Desc: \"Enable the injector and read the actual state\" Actual: %d Low: %d High: %d " % (SimOut, 0, 1))
            elif Set_State[i] ==0:
                msg = ("Desc: \"Disable the injector and read the actual state\" Actual: %d Low: %d High: %d " % (SimOut, 1, 1))

            caseid = "%s_state(%d)_%d" % (Injector, i, times)
            TTB_Results(caseid, 0, msg)
            Wait(1000)

        
########Inject end angle
Table = (
           #("INJ1 D","INJ1 A", "KT_InjA.enable", "KT_InjA.B_post_inj", "KT_InjA.inj_time", "KT_InjA.inj_end_angle", 288,320), \
           #("INJ3 D","INJ3 A", "KT_InjB.enable", "KT_InjB.B_post_inj", "KT_InjB.inj_time", "KT_InjB.inj_end_angle", 468,550 ), \
           #("INJ4 D","INJ4 A", "KT_InjC.enable", "KT_InjC.B_post_inj", "KT_InjC.inj_time", "KT_InjC.inj_end_angle", 648,700 ), \
           #("INJ2 D","INJ2 A", "KT_InjD.enable", "KT_InjD.B_post_inj", "KT_InjD.inj_time", "KT_InjD.inj_end_angle", 108,150 ), \
           ("INJ1 D","INJ1 A", "KT_InjA.enable", "KT_InjA.B_post_inj", "KT_InjA.inj_time", "KT_InjA.inj_end_angle", 378,378, "Injector_A"), \
           ("INJ3 D","INJ3 A", "KT_InjB.enable", "KT_InjB.B_post_inj", "KT_InjB.inj_time", "KT_InjB.inj_end_angle", 558,558, "Injector_B"), \
           ("INJ4 D","INJ4 A", "KT_InjC.enable", "KT_InjC.B_post_inj", "KT_InjC.inj_time", "KT_InjC.inj_end_angle", 18,18, "Injector_C"), \
           ("INJ2 D","INJ2 A", "KT_InjD.enable", "KT_InjD.B_post_inj", "KT_InjD.inj_time", "KT_InjD.inj_end_angle", 198,198 , "Injector_D"), \

         )
Set(SIMULATOR, 0, "RPM", 0)

for AliasName1,AliasName2, symbol_name1, symbol_name2, symbol_name3, symbol_name4, Zore_Ang,refen_ang, Injector in Table:
    WriteMemValue(PROCESSOR, 0, symbol_name1, 1)#enable the inject
    WriteMemValue(PROCESSOR, 0, symbol_name2, 0)#disable the post inject
    WriteMemValue(PROCESSOR, 0, symbol_name3, 1000)#Set inject time is 1000us
    Wait(2000)
    for i in range(1,7):
         speed_set = i *1000
         Set(SIMULATOR, 0, "RPM", speed_set)
         
         for j in range(1,26):
             inj_end_angle = j *10
             WriteMemValue(PROCESSOR, 0, symbol_name4, inj_end_angle)
             Wait(4000)
             for times in range(0, Test_times):
                 SimOut_width = Get(SIMULATOR, 0, AliasName1)
                 SimOut_angle = Get(SIMULATOR, 0, AliasName2)
                 simOut = Inject_end_angle(SimOut_angle + SimOut_width,refen_ang,Zore_Ang)
                 Set_ang = Get_InjectAngle(inj_end_angle)
                 Set_ang_low = Set_ang*error_min
                 Set_ang_up  = Set_ang*error_max
                 msg = ("Desc: \"Set the end of inject angle is %d, read the actual end of inject angle and compare it with the expected angle \" Actual: %d Low: %d High: %d " % (Set_ang, simOut, Set_ang_low, Set_ang_up))
                 caseid = "%s_Rpm(%d)_Inject_end_angle(%d)_%d" % (Injector, speed_set, inj_end_angle,times)
                 TTB_Results(caseid, 0, msg)
                 Wait(1000)
             
    WriteMemValue(PROCESSOR, 0, symbol_name4, 0)
    break

#retc = TTB_Results("Test1", 0, "Test 1", "DSFS")  comment
              
########Inject time

Set(SIMULATOR, 0, "RPM", 0)
for AliasName1,AliasName2, symbol_name1, symbol_name2, symbol_name3, symbol_name4, Zore_Ang,refen_ang in Table:
    WriteMemValue(PROCESSOR, 0, symbol_name1, 1)#enable the inject
    WriteMemValue(PROCESSOR, 0, symbol_name2, 0)#disable the post inject
    WriteMemValue(PROCESSOR, 0, symbol_name4, 0)#Set inject end angle is 0
    Wait(2000)
    for i in range(1,7):
         speed_set = i *1000
         Set(SIMULATOR, 0, "RPM", speed_set)
         
         for j in range(0,21):
             dwell_time_set = j*500
             WriteMemValue(PROCESSOR, 0, symbol_name3, dwell_time_set)
             Wait(3000)
             for times in range(0, Test_times):
                 SimOut_width = Get(SIMULATOR, 0, AliasName1)
                 SimOut_width = convert_angle_to_time(SimOut_width, speed_set);
                 
                 Set_time_low = dwell_time_set*error_min
                 Set_time_up  = dwell_time_set*error_max
                 msg = ("Desc: \"Set the inject time is %d us, read the inject actual dwell time and compare it with expected time\" Actual: %d Low: %d High: %d " % (dwell_time_set, SimOut_width, Set_time_low, Set_time_up))
                 caseid = "%s_Rpm(%d)_dwell_time(%d)_%d" % (AliasName1, speed_set, dwell_time_set, times)
                 TTB_Results(caseid, 0, msg)
                 Wait(1000)
             
    WriteMemValue(PROCESSOR, 0, symbol_name3, 1000)

#####Test the inject time and inject end angle at low RPM
for AliasName1,AliasName2, symbol_name1, symbol_name2, symbol_name3, symbol_name4, Zore_Ang,refen_ang in Table:
    WriteMemValue(PROCESSOR, 0, symbol_name1, 1)#enable the inject
    WriteMemValue(PROCESSOR, 0, symbol_name2, 0)#disable the post inject
    for i in range(1,4):
        speed_set =i*100
        Set(SIMULATOR, 0, "RPM", i*100)
        Wait(1000)
        for j in range(1,11):###set the dwell time for 1*20ms to 10*20ms
            dwell_time_set = j *20000
            WriteMemValue(PROCESSOR, 0, symbol_name3, dwell_time_set)
            Wait(2000)
            for k in range(0,26):# set the inject end angle for 0*10*2.8125 to 0*25*2.8125
                Inject_end_angle_set = k*10
                WriteMemValue(PROCESSOR, 0, symbol_name4, Inject_end_angle_set)
                Wait(4000)
                for times in range(0, Test_times):
                    SimOut_width = Get(SIMULATOR, 0, AliasName1)
                    SimOut_angle = Get(SIMULATOR, 0, AliasName2)
                    simOut = Inject_end_angle(SimOut_angle + SimOut_width,refen_ang,Zore_Ang)
                    Set_ang = Get_InjectAngle(Inject_end_angle_set)
                    Set_ang_low = Set_ang*error_min
                    Set_ang_up  = Set_ang*error_max
                    msg = ("Desc: \"Set the inject dwell time is %d ms, engine speed is %d rpm, inject end angle is %d CrA degree, read the actual inject end angle and compare it with the expected angle \" Actual: %d Low: %d High: %d " % (dwell_time_set/1000, speed_set, Set_ang, simOut, Set_ang_low, Set_ang_up))
                    caseid = "%s(%d)_dwell_time(%d)_Rpm(%d)_%d" % ("End_angle",Set_ang, dwell_time_set, speed_set, times)
                    TTB_Results(caseid, 0, msg)
                    
                    SimOut_width = convert_angle_to_time(SimOut_width, speed_set);
                    
                    Set_time_low = dwell_time_set*error_min   
                    Set_time_up  = dwell_time_set*error_max
                    msg = ("Desc: \"Set the inject end angle is %d CrA degrees, engine speed is %d rpm, inject dwell time is %d ms, read the actual inject dwell time and compare it with the expected time\" Actual: %d Low: %d High: %d " % (Set_ang, speed_set, dwell_time_set/1000, SimOut_width, Set_time_low, Set_time_up))
                    caseid = "%s(%d)_end_angle(%d)_Rpm(%d)_%d" % ("dwell_time",dwell_time_set, simOut, speed_set, times)
                    TTB_Results(caseid, 0, msg)
                    Wait(1000)
                
##########################################################################################
##########################################################################################
######Spark relevant Test

Table = (
           ("KT_IgnA.dwell_time", "KT_IgnA.ign_angle", "KT_IgnA.follow_up_sparks", ), \
           ("KT_IgnB.dwell_time", "KT_IgnB.ign_angle", "KT_IgnB.follow_up_sparks", ), \
           ("KT_IgnC.dwell_time", "KT_IgnC.ign_angle", "KT_IgnC.follow_up_sparks", ), \
           ("KT_IgnD.dwell_time", "KT_IgnD.ign_angle", "KT_IgnD.follow_up_sparks", ), \

         )
###Inital the spark relavant parameter
for symbol_name1, symbol_name2, symbol_name3 in Table:
     WriteMemValue(PROCESSOR, 0, symbol_name1, 4000)#inital the dewell time  
     WriteMemValue(PROCESSOR, 0, symbol_name2, 128) #inital the ign_angle that make the advance ignition angle is 0
     WriteMemValue(PROCESSOR, 0, symbol_name3, 0)   #inital the follow_up_sparks with 0 that disable multiple spark
     

####################Spark enable#########################
Table = (
           ("EST1 PW", "KT_IgnA.enable", "KT_IgnC.enable", (0,1), "Spark_A"), \
           ("EST2 PW", "KT_IgnB.enable", "KT_IgnD.enable", (0,1), "Spark_B"), \

         )

for AliasName, symbol_name1, symbol_name2, Set_State, Spark_chanel in Table:
    for i in range(0,2):
        WriteMemValue(PROCESSOR, 0, symbol_name1, Set_State[i])
        WriteMemValue(PROCESSOR, 0, symbol_name2, Set_State[i])
        Wait(3000)
        for times in range(0, Test_times):
            SimOut = Get(SIMULATOR, 0, AliasName)# get the relavant port's frequency whether is zero
            
            if Set_State[i] ==1:
                msg = ("Desc: \"Enable the state of the Spark A&C, and read the state of the spark\" Actual: %d Low: %d High: %d " % (SimOut, 0, 1))
            elif Set_State[i] ==0:
                msg = ("Desc: \"Disable the state of the Spark B&D, and read the state of the spark\" Actual: %d Low: %d High: %d " % (SimOut, 1, 1))

            caseid = "%s_state(%d)_%d" % (Spark_chanel, i, times)
            TTB_Results(caseid, 0, msg)
            Wait(1000)

####################main Spark dwell time#########################
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
    Wait(2000)
    #for i in range(1,7):
    Set(SIMULATOR, 0, "RPM", 1000)  ##in different rpm
    for j in range(1,21):
        dwell_time_set =j*500
        WriteMemValue(PROCESSOR, 0, symbol_name2, dwell_time_set)
        Wait(2000)
        for times in range(0, Test_times):
            SimOut_width = Get(SIMULATOR, 0, AliasName)
            SimOut_width = convert_angle_to_time(SimOut_width, 1000);
            
            Set_time_low = dwell_time_set * error_min
            Set_time_up  = dwell_time_set * error_max
            msg = ("Desc: \"Set the spark dwell time is %4.2f ms, engine speed is %d rpm, read the actual dwell time and compare it with the expectd time\" Actual: %d Low: %d High: %d " % (dwell_time_set/1000, speed_set,SimOut_width, Set_time_low, Set_time_up))
            caseid = "%s_dwell_time(%d)_%d" % (spark_chanel, dwell_time_set, times)
            TTB_Results(caseid, 0, msg)
            Wait(1000)
             
    WriteMemValue(PROCESSOR, 0, symbol_name2, 4000) #reset the dwell time is 4000us after finish test

####################Spark advanct angle#########################
Table = (
           ("EST1 A", "EST1 D","KT_IgnA.enable", "KT_IgnA.dwell_time", "KT_IgnA.ign_angle", "Spark_A" ), \
           ("EST2 A", "EST2 D","KT_IgnB.enable", "KT_IgnB.dwell_time", "KT_IgnB.ign_angle", "Spark_B" ), \
           ("EST1 A", "EST1 D","KT_IgnC.enable", "KT_IgnC.dwell_time", "KT_IgnC.ign_angle", "Spark_C" ), \
           ("EST2 A", "EST2 D","KT_IgnD.enable", "KT_IgnD.dwell_time", "KT_IgnD.ign_angle", "Spark_D" ), \

         )###the AliasName should be renamed

Set(SIMULATOR, 0, "RPM", 0)

for AliasName1,AliasName2,symbol_name1, symbol_name2, symbol_name3, Spark_chanel in Table:
    if symbol_name1 == "KT_IgnA.enable":
        WriteMemValue(PROCESSOR, 0, "KT_IgnA.enable", 1)#enable the sparkA
        WriteMemValue(PROCESSOR, 0, "KT_IgnC.enable", 0)#disenable the sparkC
        TDC_angle = 360+ 20*6
    elif symbol_name1 == "KT_IgnB.enable":
        WriteMemValue(PROCESSOR, 0, "KT_IgnB.enable", 1)#enable the sparkB
        WriteMemValue(PROCESSOR, 0, "KT_IgnD.enable", 0)#disenable the sparkD
        TDC_angle = 360 + 50*6
    elif symbol_name1 == "KT_IgnC.enable":
        WriteMemValue(PROCESSOR, 0, "KT_IgnA.enable", 0)#disenable the sparkA
        WriteMemValue(PROCESSOR, 0, "KT_IgnC.enable", 1)#enable the sparkC
        TDC_angle = 20*6
    elif symbol_name1 == "KT_IgnD.enable":
        WriteMemValue(PROCESSOR, 0, "KT_IgnB.enable", 0)#enable the sparkD
        WriteMemValue(PROCESSOR, 0, "KT_IgnD.enable", 1)#disenable the sparkB
        TDC_angle = 50*6

    WriteMemValue(PROCESSOR, 0, symbol_name2, 4000)#Set the main spark dwell time is 4000us
    Wait(2000)
    
    for i in range(1,7):
         speed_set = i*1000
         Set(SIMULATOR, 0, "RPM", speed_set)
         
         for j in range(0,17): ##The spark advance angle is from -60degree to 60degree
             WriteMemValue(PROCESSOR, 0, symbol_name3, 128 - 80 + j*10)
             Wait(4000)
             for times in range(0, Test_times):
                 
                 SimOut_width = Get(SIMULATOR, 0, AliasName2)
                 SimOut_angle = Get(SIMULATOR, 0, AliasName1)
                 temp = SimOut_angle + SimOut_width
                 if temp >=TDC_angle +100:
                     temp = temp -720
                     
                 simOut =temp  - TDC_angle #captured advance angle
                 Set_ang = (j*10-80)*-0.75# the set advance angle
                 Set_ang_low = Set_ang*error_min
                 Set_ang_up  = Set_ang *error_max
                 msg = ("Desc: \"Set the spark dwell time is 4ms, engine speed is %d rpm, spark advance angle is %d CrA degrees, read the actual spark advance angle and compare it with expected angle\" Actual: %d Low: %d High: %d " % (speed_set,Set_ang, simOut, Set_ang_low, Set_ang_up))
                 caseid = "%s_Rpm(%d)_Spark_angle(%d)_%d" % (Spark_chanel, speed_set, (j*10-80)*0.75, times)
                 TTB_Results(caseid, 0, msg)
                 Wait(1000)
             
    WriteMemValue(PROCESSOR, 0, symbol_name3, 128) #reset the spark advance angle 0 degree

