from PyDevice import *

def Get_InjectAngle(end_ang):
    if end_ang*2.8125 <=90:
        j = 90
    else:
        j = end_ang*2.8125
    #if (j +  width) >=720+refen_ang-refen_start:
     #   j= (refen_ang +720) -(refen_start +width)
        
    return j

#####convert the angle to width
def convert_angle_to_time(angle, rpm_n):  # units:angle->dgree  rpm_n ->r/min  time_width->us

    time_width = angle*1000000 / (rpm_n*6)

    return time_width

def Inject_end_angle(real_ang, refen_ang, zore_ang):
   
    
    if refen_ang < real_ang:
        return refen_ang + 720 - real_ang
    else:
        return refen_ang  - real_ang
    
Set(SIMULATOR, 0, "Battery Control State", 1)
Wait(100)
#Set(SIMULATOR, 0, "Key Switch State", 1)
Wait(2000)
Set(SIMULATOR, 0, "Key Switch State", 3)
Set(SIMULATOR, 0, "Dateset", 1)
Set(SIMULATOR, 0, "RPM", 800)
error_min =0.95
error_max =1.05
Test_times =1

#############################################
######Inject relevant Test
########Inject enable
TTB_Results("Test case 1", 0, "Inject enable test; enable and disable the injector, and read it actual state captured by OPAL-RT", " ")  
Table = (
           ("INJ1 PW", "KT_InjA.enable", (0,1), "Injector_A"), \
           ("INJ3 PW", "KT_InjB.enable", (0,1), "Injector_B"), \
           ("INJ4 PW", "KT_InjC.enable", (0,1), "Injector_C"), \
           ("INJ2 PW", "KT_InjD.enable", (0,1), "Injector_D"), \

         )
Set(SIMULATOR, 0, "RPM", 800)
for AliasName, symbol_name, Set_State, Injector in Table:
    for i in range(0,2):
        WriteMemValue(PROCESSOR, 0, symbol_name, Set_State[i])
        Wait(3000)
        for times in range(1, Test_times+1):
            SimOut = Get(SIMULATOR, 0, AliasName)# get the relavant port's frequency whether is zero
            
            if Set_State[i] ==1:
                state ="Enable"
                msg = ("Desc: \"Enable the %s and read the actual state\" Actual: %d Low: %d High: %d " % (Injector, SimOut, 0, 1))
            elif Set_State[i] ==0:
                state ="Disable"
                msg = ("Desc: \"Disable the %s and read the actual state\" Actual: %d Low: %d High: %d " % (Injector, SimOut, 1, 1))

            caseid = "%s_state=%s" % (Injector, state)
            TTB_Results(caseid, 0, msg)
            Wait(1000)


########Inject end angle
#TTB_Results("Test case 2", 0, "Inject end angle test; set injector inject time is 1ms, and set the injector a target inject end angle and read the actual inject end angle captured by OPAL-RT", " ")

Table = (
           #("INJ1 D","INJ1 A", "KT_InjA.enable", "KT_InjA.B_post_inj", "KT_InjA.inj_time", "KT_InjA.inj_end_angle", 288,320), \
           #("INJ3 D","INJ3 A", "KT_InjB.enable", "KT_InjB.B_post_inj", "KT_InjB.inj_time", "KT_InjB.inj_end_angle", 468,550 ), \
           #("INJ4 D","INJ4 A", "KT_InjC.enable", "KT_InjC.B_post_inj", "KT_InjC.inj_time", "KT_InjC.inj_end_angle", 648,700 ), \
           #("INJ2 D","INJ2 A", "KT_InjD.enable", "KT_InjD.B_post_inj", "KT_InjD.inj_time", "KT_InjD.inj_end_angle", 108,150 ), \
           ("INJ1 D","INJ1 A", "KT_InjA.enable", "KT_InjA.B_post_inj", "KT_InjA.inj_time", "KT_InjA.inj_end_angle", 402,378, "Injector_A"), \
           ("INJ3 D","INJ3 A", "KT_InjB.enable", "KT_InjB.B_post_inj", "KT_InjB.inj_time", "KT_InjA.inj_end_angle", 582,558, "Injector_B"), \
           ("INJ4 D","INJ4 A", "KT_InjC.enable", "KT_InjC.B_post_inj", "KT_InjC.inj_time", "KT_InjA.inj_end_angle", 42,18, "Injector_C"), \
           ("INJ2 D","INJ2 A", "KT_InjD.enable", "KT_InjD.B_post_inj", "KT_InjD.inj_time", "KT_InjA.inj_end_angle", 222,198 , "Injector_D"), \

         )
Set(SIMULATOR, 0, "RPM", 0)

for AliasName1,AliasName2, symbol_name1, symbol_name2, symbol_name3, symbol_name4, Zore_Ang,refen_ang, Injector in Table:
    WriteMemValue(PROCESSOR, 0, symbol_name1, 1)#enable the inject
    WriteMemValue(PROCESSOR, 0, symbol_name2, 0)#disable the post inject
    WriteMemValue(PROCESSOR, 0, symbol_name3, 5000)#Set inject time is 5000us
    WriteMemValue(PROCESSOR, 0, symbol_name4, 0)#Set inject end angle is 0 
    Wait(1000)





#####Test the inject time and inject end angle at different rpm
TTB_Results("Test case 2", 0, "Inject time and end angle test at different rpm(1000, 3000, 5000rpm);"," ")
Inject_angle_Table=(30, 50, 100, 150,200, 250)
Inject_time_Table=(2000, 5000, 10000)
for i in range(0,3): #1000, 3000, 5000
    speed_set =i*2000+1000
    Set(SIMULATOR, 0, "RPM", speed_set)
    TTB_Results("Test case 2.%d"%(i+1), 0, "Test condition: rpm =%d"%(speed_set)," ")
    Wait(1000)
    for AliasName1,AliasName2, symbol_name1, symbol_name2, symbol_name3, symbol_name4, Zore_Ang,refen_ang, Injector in Table:
        WriteMemValue(PROCESSOR, 0, symbol_name1, 1)#enable the inject
        WriteMemValue(PROCESSOR, 0, symbol_name2, 0)#disable the post inject
        m =0   
        for j in range(0,3):###set the dwell time for 2ms 5ms 10ms
            dwell_time_set = Inject_time_Table[j]
            WriteMemValue(PROCESSOR, 0, symbol_name3, dwell_time_set)
            
            for k in range(0,6):# set the inject end angle for 0*10*2.8125 to 0*25*2.8125
                Inject_end_angle_set = Inject_angle_Table[k]
                WriteMemValue(PROCESSOR, 0, symbol_name4, Inject_end_angle_set)
                Wait(2000)
                for times in range(1, Test_times+1):
                    m =m + 1
                    SimOut_width = Get(SIMULATOR, 0, AliasName1)
                    SimOut_angle = Get(SIMULATOR, 0, AliasName2)
                    simOut = Inject_end_angle(SimOut_angle + SimOut_width,refen_ang,Zore_Ang)
                    Set_ang = Get_InjectAngle(Inject_end_angle_set)
                    Set_ang_low = Set_ang*error_min
                    Set_ang_up  = Set_ang*error_max
                    
                    msg = ("Desc: \"Set the %s target inject end angle is %dCrA, inject time is %dms, engine speed is %drpm, fall_edge =%3.1fdegree, read the actual inject end angle \" Actual: %3.1f Low: %3.1f High: %3.1f " % (Injector, Set_ang, dwell_time_set/1000, speed_set, SimOut_angle, simOut, Set_ang_low, Set_ang_up))
                    caseid = "%s_Inject_end_angle=%3.1f_Inject_time=%dms_%drpm_%dth" % (Injector,Set_ang, dwell_time_set/1000, speed_set, m)
                    TTB_Results(caseid, 0, msg)

                    fall_to_raise_edge =SimOut_width
                    SimOut_width = convert_angle_to_time(SimOut_width, speed_set);
                    
                    Set_time_low = dwell_time_set*error_min/1000   
                    Set_time_up  = dwell_time_set*error_max/1000
                    
                    msg = ("Desc: \"Set the %s target inject time is %dms, inject end angle is %dCrA, engine speed is %drpm, fall_to_raise_edge=%3.1fdegree, read the actual inject time\" Actual: %2.2f Low: %2.2f High: %2.2f " % (Injector, dwell_time_set/1000, Set_ang, speed_set, fall_to_raise_edge, SimOut_width/1000, Set_time_low, Set_time_up))
                    caseid = "%s_Inject_time=%dms_end_angle=%3.1f_%drpm_%dth" % (Injector, dwell_time_set/1000, Set_ang, speed_set, m)
                    TTB_Results(caseid, 0, msg)
                    #Wait(1000)
#####Test the inject time and inject end angle at low RPM
TTB_Results("Test case 3", 0, "Inject time and end angle test at low rpm(100, 200, 300rpm);", " ")
for i in range(1,4):
    speed_set =i*100
    Set(SIMULATOR, 0, "RPM", speed_set)
    TTB_Results("Test case 3.%d"%(i), 0, "Test condition: rpm =%d"%(speed_set)," ")
    Wait(1000)
    for AliasName1,AliasName2, symbol_name1, symbol_name2, symbol_name3, symbol_name4, Zore_Ang,refen_ang, Injector in Table:
        WriteMemValue(PROCESSOR, 0, symbol_name1, 1)#enable the inject
        WriteMemValue(PROCESSOR, 0, symbol_name2, 0)#disable the post inject
        m =0
        for j in range(1,5):###set the dwell time for 1*50ms to 4*50ms
            dwell_time_set = j *50000
            WriteMemValue(PROCESSOR, 0, symbol_name3, dwell_time_set)
           
            for k in range(0,6):# set the inject end angle for 30*2.8125 to 250*2.8125
                Inject_end_angle_set =Inject_angle_Table[k]
                WriteMemValue(PROCESSOR, 0, symbol_name4, Inject_end_angle_set)
                
                Wait(3500)
                for times in range(1, Test_times+1):
                    m =m + 1
                    SimOut_width = Get(SIMULATOR, 0, AliasName1)
                    SimOut_angle = Get(SIMULATOR, 0, AliasName2)
                    simOut = Inject_end_angle(SimOut_angle + SimOut_width,refen_ang,Zore_Ang)
                    Set_ang = Get_InjectAngle(Inject_end_angle_set)
                    Set_ang_low = Set_ang*error_min
                    Set_ang_up  = Set_ang*error_max
                    
                    msg = ("Desc: \"Set the %s target inject end angle is %dCrA, inject time is %dms, engine speed is %drpm, fall_edge =%3.1fdegree, read the actual inject end angle \" Actual: %3.1f Low: %3.1f High: %3.1f " % (Injector, Set_ang, dwell_time_set/1000, speed_set, SimOut_angle,  simOut, Set_ang_low, Set_ang_up))
                    caseid = "%s_Inject_end_angle=%3.1f_Inject_time=%dms_%drpm_%dth" % (Injector,Set_ang, dwell_time_set/1000, speed_set, m)
                    TTB_Results(caseid, 0, msg)

                    fall_to_raise_edge =SimOut_width
                    SimOut_width = convert_angle_to_time(SimOut_width, speed_set);
                    
                    Set_time_low = dwell_time_set*error_min/1000   
                    Set_time_up  = dwell_time_set*error_max/1000
                    
                    msg = ("Desc: \"Set the %s target time is %dms, inject end angle is %dCrA degrees, engine speed is %drpm, fall_to_raise_edge=%3.1fdegree, read the actual inject time\" Actual: %d Low: %d High: %d " % (Injector, dwell_time_set/1000, Set_ang, speed_set, fall_to_raise_edge, SimOut_width/1000, Set_time_low, Set_time_up))
                    caseid = "%s_Inject_time=%dms_end_angle=%3.1f_%drpm_%dth" % (Injector, dwell_time_set/1000, Set_ang, speed_set, m)
                    TTB_Results(caseid, 0, msg)
                    #Wait(1000)
          





TTB_Results("Test case 4", 0, "Inject time and end angle test at cam backup mode in different rpm(1000, 2000, 3000rpm);", " ")
Set(SIMULATOR, 0, "RPM", 1000)
Inject_angle_Table=(30, 50, 100, 150)
Inject_time_Table=(2000, 5000, 10000)
WriteMemValue(PROCESSOR, 0, "KyHWIO_Delta_Angle_From_Edge_To_Tooth_1", 48)
Wait(2000)
Set(SIMULATOR, 0, "Dateset", 10)
error_max =1.1
error_min =0.9
Wait(5000)
for i in range(0,3): #1000, 2000, 3000
    speed_set =i*1000+1000
    Set(SIMULATOR, 0, "RPM", speed_set)
    TTB_Results("Test case 4.%d"%(i+1), 0, "Test condition: rpm =%d"%(speed_set)," ")
    Wait(1000)
    for AliasName1,AliasName2, symbol_name1, symbol_name2, symbol_name3, symbol_name4, Zore_Ang,refen_ang, Injector in Table:
        WriteMemValue(PROCESSOR, 0, symbol_name1, 1)#enable the inject
        WriteMemValue(PROCESSOR, 0, symbol_name2, 0)#disable the post inject
        m =0    
        for j in range(0,3):###set the dwell time for 2ms 5ms 10ms
            dwell_time_set = Inject_time_Table[j]
            WriteMemValue(PROCESSOR, 0, symbol_name3, dwell_time_set)
            
            for k in range(0,4):# set the inject end angle for 30*2.8125 to 20*2.8125
                Inject_end_angle_set = Inject_angle_Table[k]
                WriteMemValue(PROCESSOR, 0, symbol_name4, Inject_end_angle_set)
                Wait(2000)
                for times in range(1, Test_times+1):
                    m =m + 1
                    SimOut_width = Get(SIMULATOR, 0, AliasName1)
                    SimOut_angle = Get(SIMULATOR, 0, AliasName2)
                    simOut = Inject_end_angle(SimOut_angle + SimOut_width,refen_ang,Zore_Ang)
                    Set_ang = Get_InjectAngle(Inject_end_angle_set)
                    Set_ang_low = Set_ang*error_min
                    Set_ang_up  = Set_ang*error_max
                    
                    msg = ("Desc: \"Set the %s target inject end angle is %dCrA, inject time is %dms, engine speed is %drpm, fall_edge =%3.1fdegree, read the actual inject end angle \" Actual: %3.1f Low: %3.1f High: %3.1f " % (Injector, Set_ang, dwell_time_set/1000, speed_set, SimOut_angle, simOut, Set_ang_low, Set_ang_up))
                    caseid = "%s_Inject_end_angle=%3.1f_Inject_time=%dms_%drpm__backup_%dth" % (Injector,Set_ang, dwell_time_set/1000, speed_set, m)
                    TTB_Results(caseid, 0, msg)
                    
                    fall_to_raise_edge =SimOut_width
                    SimOut_width = convert_angle_to_time(SimOut_width, speed_set);
                    
                    Set_time_low = dwell_time_set*error_min/1000   
                    Set_time_up  = dwell_time_set*error_max/1000
                    
                    msg = ("Desc: \"Set the %s target inject time is %dms, inject end angle is %dCrA degrees, engine speed is %drpm, fall_to_raise_edge=%3.1fdegree, read the actual inject time\" Actual: %2.2f Low: %2.2f High: %2.2f " % (Injector, dwell_time_set/1000, Set_ang, speed_set, fall_to_raise_edge, SimOut_width/1000, Set_time_low, Set_time_up))
                    caseid = "%s_Inject_time=%dms_end_angle=%3.1f_%drpm_backup_%dth" % (Injector, dwell_time_set/1000, Set_ang, speed_set, m)
                    TTB_Results(caseid, 0, msg)

Set(SIMULATOR, 0, "Dateset", 1)
Set(SIMULATOR, 0, "RPM", 0)
Wait(5000)
Set(SIMULATOR, 0, "RPM", 1000)
