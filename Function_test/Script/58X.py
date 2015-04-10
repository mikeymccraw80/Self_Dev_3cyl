from PyDevice import *

Set(SIMULATOR, 0, "Battery Control State", 1)
#Set(SIMULATOR, 0, "Key Switch State", 1)
Wait(2000)
Set(SIMULATOR, 0, "Dateset", 1)
Set(SIMULATOR, 0, "Key Switch State", 3)
Set(SIMULATOR, 0, "RPM", 800)
error_min =0.95
error_max =1.05
Test_times =1

#############Check the cam status 
TTB_Results("Test case 1", 0, "Cam status test; Set the cam output no signal at different rpm, and read the cam status that the flag cam_fail and cam limphome will be set.", " ")
for i in range(1, 7):
    speed_set = i*1000
    Set(SIMULATOR, 0, "RPM", speed_set)
    Set(SIMULATOR, 0, "Dateset", 1)
    TTB_Results("Test case 1.%d"%(i), 0, "Test condition: rpm =%d"%(speed_set), " ")  
    Wait(2000)
    for times in range(1, Test_times+1):
        for j in range(1, 3):
            if j ==1 :

                Set(SIMULATOR, 0, "Dateset", 8)# set the cam1 signal is not work

                Wait(3000)
                (retc,cam_fail) = ReadMemValue(PROCESSOR, 0, "CAM1_SF")
                msg = ("Desc: \" Set engine speed is %d rpm, and make the cam1 no signal output, read the cam1 fail status flag\" Actual: %d Low: %d High: %d " % (speed_set, cam_fail, 1,1))
                caseid = "%s_%drpm_%dth" % ("cam1_failed", speed_set, j)
                TTB_Results(caseid, 0, msg)

                (retc,cam_limphome) = ReadMemValue(PROCESSOR, 0, "CAM1_SLH")
                msg = ("Desc: \"Set engine speed is %d rpm, and make the cam1 no signal output, and read the cam1 limp home flag\" Actual: %d Low: %d High: %d " % (speed_set, cam_limphome, 1, 1))
                caseid = "%s_%drpm_%dth" % ("cam1_limphome", speed_set, j)
                TTB_Results(caseid, 0, msg)
                
                Set(SIMULATOR, 0, "Dateset", 9)# set the cam1 signal is not work

                Wait(5000)
                (retc,cam_fail) = ReadMemValue(PROCESSOR, 0, "CAM2_SF")
                msg = ("Desc: \"Set engine speed is %d rpm, and make the cam2 no signal output, and read the cam2 fail status flag \" Actual: %d Low: %d High: %d " % (speed_set, cam_fail, 1, 1))
                caseid = "%s_%drpm_%dth" % ("cam2_failed", speed_set,j)
                TTB_Results(caseid, 0, msg)

                (retc,cam_limphome) = ReadMemValue(PROCESSOR, 0, "CAM2_SLH")
                msg = ("Desc: \"Set engine speed is %d rpm, and make the cam2 no signal output, and read the cam2 limp home flag\" Actual: %d Low: %d High: %d " % (speed_set, cam_limphome, 1, 1))
                caseid = "%s_%drpm_%dth" % ("cam2_limphome", speed_set, j)
                TTB_Results(caseid, 0, msg)
                
            else:
                Set(SIMULATOR, 0, "Dateset", 1)# set the cam1 signal is  work

                Wait(3000)
                (retc,cam_fail) = ReadMemValue(PROCESSOR, 0, "CAM1_SF")
                msg = ("Desc: \" Set engine speed is %d rpm, and make the cam1 signal output normally, read the cam1 fail status flag\" Actual: %d Low: %d High: %d " % (speed_set, cam_fail, 0,0))
                caseid = "%s_%drpm_%dth" % ("cam1_failed", speed_set, j)
                TTB_Results(caseid, 0, msg)

                (retc,cam_limphome) = ReadMemValue(PROCESSOR, 0, "CAM1_SLH")
                msg = ("Desc: \"Set engine speed is %d rpm, and make the cam1 signal output normally, and read the cam1 limp home flag\" Actual: %d Low: %d High: %d " % (speed_set, cam_limphome, 0, 0))
                caseid = "%s_%drpm_%dth" % ("cam1_limphome", speed_set, j)
                TTB_Results(caseid, 0, msg)

                (retc,cam_fail) = ReadMemValue(PROCESSOR, 0, "CAM2_SF")
                msg = ("Desc: \"Set engine speed is %d rpm, and make the cam2 signal output normally, and read the cam2 fail status flag \" Actual: %d Low: %d High: %d " % (speed_set, cam_fail, 0, 0))
                caseid = "%s_%drpm_%dth" % ("cam2_failed", speed_set,j)
                TTB_Results(caseid, 0, msg)

                (retc,cam_limphome) = ReadMemValue(PROCESSOR, 0, "CAM2_SLH")
                msg = ("Desc: \"Set engine speed is %d rpm, and make the cam2 signal output normally, and read the cam2 limp home flag\" Actual: %d Low: %d High: %d " % (speed_set, cam_limphome, 0, 0))
                caseid = "%s_%drpm_%dth" % ("cam2_limphome", speed_set, j)
                TTB_Results(caseid, 0, msg)

Set(SIMULATOR, 0, "Dateset", 1)

#####check engine speed 
TTB_Results("Test case 2", 0, "Engine speed test; change the rpm signal from 1000 to 6000, and read the actual engine speed that captured by the ECU", " ")  
Set(SIMULATOR, 0, "RPM", 0)
Wait(1000)
for i in range(1,7):
    Speed_set = i*1000
    Set(SIMULATOR, 0, "RPM", Speed_set)
    Wait(2000)
    for times in range(0, Test_times):
        
        (retc,engine_speed) = ReadMemValue(PROCESSOR, 0, "CRANK_RPM")
        ULimit = Speed_set*error_max
        LLimit = Speed_set*error_min
        msg = ("Desc: \"Set engine speed is %drpm, read the actual engine speed \" Actual: %d Low: %d High: %d " % ( Speed_set, engine_speed, LLimit,ULimit))
        caseid = "RPM=%d" % (Speed_set)
        TTB_Results(caseid, 0, msg)
        Wait(1000)


###58X synchronization
TTB_Results("Test case 3", 0, "Crank tooth test; Set the KyHWIO_MaxErrorTeethMore =3 and  KyHWIO_MaxErrorTeethLess =3, set the bench output the expected crank signal, and read the crank state", " ")  
Set(SIMULATOR, 0, "RPM", 0)
WriteMemValue(PROCESSOR, 0, "KyHWIO_MaxErrorTeethMore", 3)
WriteMemValue(PROCESSOR, 0, "KyHWIO_MaxErrorTeethLess", 3)
Wait(2000)
Table = (1, 2, 3,4, 5, 6, 7)
for i in range(1,7):
    Speed_set = i *1000
    Set(SIMULATOR, 0, "RPM", Speed_set)
    TTB_Results("Test case 3.%d"%(i), 0, "Test condition: rpm =%d"%(Speed_set), " ")  
    Wait(1000)
    for j in range(0,7):
        Pattern_RPG = Table[j]
        if j == 3 or j== 6:
            (retc,CRANK_Error_Counter_L)  = ReadMemValue(PROCESSOR, 0, "Sync_EC")
        Set(SIMULATOR, 0, "Dateset", Pattern_RPG)
        Wait(4000)
        for times in range(1, Test_times+1):
            (retc,CRANK_Error_Count_Less) = ReadMemValue(PROCESSOR, 0, "CRANK_ECL")
            (retc,CRANK_Error_Count_More) = ReadMemValue(PROCESSOR, 0, "CRANK_ECM")
            (retc,CRANK_Error_Counter_N)  = ReadMemValue(PROCESSOR, 0, "Sync_EC")
            if j==0:
                
                msg = ("Desc: \"The crank signal should working normally at %drpm \" Actual: %d Low: %d High: %d " % ( Speed_set, CRANK_Error_Count_Less, 0, 0))
                caseid = "CRANK_Teeth_Count_Less_%drpm_Less_%dtooth" % (Speed_set, j)
                TTB_Results(caseid, 0, msg)

                msg = ("Desc: \"The crank signal should working normally at %drpm \" Actual: %d Low: %d High: %d " % ( Speed_set, CRANK_Error_Count_More, 0, 0))
                caseid = "CRANK_Teeth_Count_More_%drpm_Less_%dtooth" % ( Speed_set, j)
                TTB_Results(caseid, 0, msg)
            elif j ==1 or j==2:
               # msg = ("Desc: \"The crank signal should working abnormally at %d \" Actual: %d Low: %d High: %d " % ( Speed_set, CRANK_Error_Count_More, 0, 0))
               # caseid = "CRANK_Teeth_Count_More(%d)_RPM=%d_%d" % ( times, Speed_set,j)
               # TTB_Results(caseid, 0, msg)
                
                msg = ("Desc: \"The crank signal should working abnormally at %drpm \" Actual: %d Low: %d High: %d " % (Speed_set, CRANK_Error_Count_Less, j, j))
                caseid = "CRANK_Teeth_Count_Less_%drpm_Less_%dtooth" % ( Speed_set, j)
                TTB_Results(caseid, 0, msg)
            elif j ==3:
                if CRANK_Error_Counter_N != CRANK_Error_Counter_L:
                    reset = "resync"
                else:
                    reset = "false"

                msg = ("Desc: \"The crank signal should working abnormally at %drpm, and the ECU will be resync \" Actual: %s Low: %s High: %s " % (Speed_set, reset, "resync", "resync"))
                caseid = "CRANK_Teeth_Count_Less_%drpm_Less_%dtooth" % ( Speed_set, j)
                TTB_Results(caseid, 0, msg)
            elif j ==4 or j==5:
                msg = ("Desc: \"The crank signal should working abnormally at %drpm \" Actual: %d Low: %d High: %d " % (Speed_set, CRANK_Error_Count_More, j-3, j-3))
                caseid = "CRANK_Teeth_Count_More_%drpm_More_%dtooth" % (Speed_set, j-3)
                TTB_Results(caseid, 0, msg)
                
                msg = ("Desc: \"The crank signal should working abnormally at %drpm, read the couter of less teeth \" Actual: %d Low: %d High: %d " % (Speed_set, CRANK_Error_Count_Less, 0, 0))
                caseid = "CRANK_Teeth_Count_Less_%drpm_More_%dtooth" % (Speed_set, j-3)
                TTB_Results(caseid, 0, msg)
            elif j ==6:
                if CRANK_Error_Counter_N != CRANK_Error_Counter_L:
                    reset = "resync"
                else:
                    reset = "false"

                msg = ("Desc: \"The crank signal should working abnormally at %drpm, and the ECU will be resync \" Actual: %s Low: %s High: %s " % (Speed_set, reset, "resync", "resync"))
                caseid = "CRANK_Teeth_Count_More_%drpm_More_%dtooth" % ( Speed_set, j-3)
                TTB_Results(caseid, 0, msg)

                msg = ("Desc: \"The crank signal should working abnormally at %drpm, read the couter of less teeth \" Actual: %d Low: %d High: %d " % (Speed_set, CRANK_Error_Count_Less, 0, 0))
                caseid = "CRANK_Teeth_Count_Less_%drpm_More_%dtooth" % (Speed_set, j-3)
                TTB_Results(caseid, 0, msg)
            Wait(1000)
Set(SIMULATOR, 0, "Dateset", 1)
Set(SIMULATOR, 0, "RPM", 0)

##### cam backup mode test
TTB_Results("Test case 4", 0, "Cam backup mode test; break out the crank signal but cam signal is ok, so the ECU will be be cam backup mode, and set the cam backup flag", " ")  
for i in range(1, 4):
    speed_set = i*1000
    
    Set(SIMULATOR, 0, "RPM", speed_set)
    TTB_Results("Test case 4.%d"%(i), 0, "Test condition: rpm =%d"%(speed_set), " ")  
    Wait(3000)
    (retc,cam_backup) = ReadMemValue(PROCESSOR, 0, "CRANK_Bkup")
    msg = ("Desc: \"The crank signal is work normally, read the cam backup flag and it should be false\" Actual: %d Low: %d High: %d " % ( cam_backup, 0, 0))
    caseid = "Cam_backup=false_%drpm" % (speed_set)
    TTB_Results(caseid, 0, msg)
    Set(SIMULATOR, 0, "Dateset", 10)
    Wait(3000)
    (retc,cam_backup) = ReadMemValue(PROCESSOR, 0, "CRANK_Bkup")
    msg = ("Desc: \"Set the crank signal no work, read the cam backup flag and it should be true\" Actual: %d Low: %d High: %d " % ( cam_backup, 1, 1))
    caseid = "Cam_backup=true_%drpm" % (speed_set)
    TTB_Results(caseid, 0, msg)
    Set(SIMULATOR, 0, "Dateset", 1)
    Set(SIMULATOR, 0, "RPM", 0)
    Wait(2000)

Set(SIMULATOR, 0, "Dateset", 1)
Set(SIMULATOR, 0, "RPM", 0)
Wait(2000)
"""
###engine state test
TTB_Results("Test case 4", 0, "engine state test; the engine state is relevant with engine speed, so change the engine speed and read the engine state", " ")  
for times in range(1, Test_times+1):
    i =0
    Set(SIMULATOR, 0, "Battery Control State", 1)
    Set(SIMULATOR, 0, "Key Switch State", 1)
    Set(SIMULATOR, 0, "RPM", 0)
    Wait(2000)
    Set(SIMULATOR, 0, "Key Switch State", 3)
    Wait(5000)
    
    (retc,engine_state) = ReadMemValue(PROCESSOR, 0, "VeVIOS_EngSt")
    msg = ("Desc: \"Keyon and engine speed is 0rpm, and the engine state should change from KeyOff to KeyOn\" Actual: %d Low: %d High: %d " % ( engine_state, 1, 1))
    caseid = "engine_state_%d_%dth" % (i,times)
    TTB_Results(caseid, 0, msg)
    i = i+1

    Set(SIMULATOR, 0, "RPM", 200)
    Wait(2000)

    (retc,engine_state) = ReadMemValue(PROCESSOR, 0, "VeVIOS_EngSt")
    msg = ("Desc: \"Set the engine speed more than 60rpm, and the engine state should change from KeyOn to CRANK\" Actual: %d Low: %d High: %d " % ( engine_state, 2, 2))
    caseid = "engine_state_%d_%dth" % (i, times)
    TTB_Results(caseid, 0, msg)
    i = i+1

    Set(SIMULATOR, 0, "RPM", 0)
    Wait(2000)

    (retc,engine_state) = ReadMemValue(PROCESSOR, 0, "VeVIOS_EngSt")
    msg = ("Desc: \"Set the engine speed is less than 60rpm, and the engine state should change from CRANK to STALL\" Actual: %d Low: %d High: %d " % ( engine_state, 4, 4))
    caseid = "engine_state_%d_%dth" % ( i,times)
    TTB_Results(caseid, 0, msg)
    i = i+1

    Set(SIMULATOR, 0, "RPM", 200)
    Wait(2000)

    (retc,engine_state) = ReadMemValue(PROCESSOR, 0, "VeVIOS_EngSt")
    msg = ("Desc: \"Set the engine speed more than 60rpm, and the engine state should change from STALL to CRANK\" Actual: %d Low: %d High: %d " % ( engine_state, 2, 2))
    caseid = "engine_state_%d_%dth" % ( i, times)
    TTB_Results(caseid, 0, msg)
    i = i+1

    Set(SIMULATOR, 0, "RPM", 600)
    Wait(2000)

    (retc,engine_state) = ReadMemValue(PROCESSOR, 0, "VeVIOS_EngSt")
    msg = ("Desc: \"Set the engine speed more than 450rpm, and the engine state should change from CRANK to RUN\" Actual: %d Low: %d High: %d " % ( engine_state, 3, 3))
    caseid = "engine_state_%d_%dth" % (i,times)
    TTB_Results(caseid, 0, msg)
    i = i+1

    Set(SIMULATOR, 0, "RPM", 100)
    Wait(2000)

    (retc,engine_state) = ReadMemValue(PROCESSOR, 0, "VeVIOS_EngSt")
    msg = ("Desc: \"Set the engine speed less than 150rpm, and the engine state should change from RUN to CRANK\" Actual: %d Low: %d High: %d " % ( engine_state, 2, 2))
    caseid = "engine_state_%d_%dth" % ( i, times)
    TTB_Results(caseid, 0, msg)
    i = i+1
"""
