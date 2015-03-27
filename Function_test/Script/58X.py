from PyDevice import *

Set(SIMULATOR, 0, "Battery Control State", 1)
Wait(100)
#Set(SIMULATOR, 0, "Key Switch State", 1)
Wait(2000)
Set(SIMULATOR, 0, "Key Switch State", 3)
Set(SIMULATOR, 0, "RPM", 800)
error_min =0.95
error_max =1.05
Test_times =20

#############Check the cam status
"""
Set(SIMULATOR, 0, "Dataset", 7)# set the cam signal is not work
Wait(5000)
cam_fail = ReadMemValue(PROCESSOR, 0, "CAM1_SF")
msg = ("Desc: \"Set cam1_sig.status.B_cam_failed is true\" Actual: %d Low: %d High: %d " % ( cam_fail, 1, 1))
caseid = "%s_%d" % ("B_cam_failed", 0)
TTB_Results(caseid, 0, msg)

cam_limphome = ReadMemValue(PROCESSOR, 0, "cam1_sig.status.B_cam_limp_home")
msg = ("Desc: \"Set cam1_sig.status.B_cam_limp_home is true\" Actual: %d Low: %d High: %d " % ( cam_limphome, 1, 1))
caseid = "%s_%d" % ("cam_limphome", 0)

Set(SIMULATOR, 0, "cam_no_signal", 3)# set the cam signal is working normal
Wait(5000)
cam_fail = ReadMemValue(PROCESSOR, 0, "cam1_sig.status.B_cam_failed")
msg = ("Desc: \"Set cam1_sig.status.B_cam_failed is false\" Actual: %d Low: %d High: %d " % ( cam_fail, 0, 0))
caseid = "%s_%d" % ("B_cam_failed", 1)
TTB_Results(caseid, 0, msg)

cam_limphome = ReadMemValue(PROCESSOR, 0, "cam1_sig.status.B_cam_limp_home")
msg = ("Desc: \"Set cam1_sig.status.B_cam_limp_home is false\" Actual: %d Low: %d High: %d " % ( cam_limphome, 0, 0))
caseid = "%s_%d" % ("cam_limphome", 1)
"""
#####check engine speed 

Set(SIMULATOR, 0, "RPM", 0)
Wait(1000)
for i in range(0,14):
    Speed_set = i*500
    Set(SIMULATOR, 0, "RPM", Speed_set)
    Wait(2000)
    for times in range(0, Test_times):
        
        (retc,engine_speed) = ReadMemValue(PROCESSOR, 0, "CRANK_RPM")
        ULimit = Speed_set*error_max
        LLimit = Speed_set*error_min
        msg = ("Desc: \"Set engine speed is %d rpm, read the actual engine speed and compare it with the expected speed\" Actual: %d Low: %d High: %d " % ( Speed_set, engine_speed, LLimit,ULimit))
        caseid = "RPM(%d)_%d" % (i, Test_times)
        TTB_Results(caseid, 0, msg)
        Wait(1000)


###58X synchronization
Set(SIMULATOR, 0, "RPM", 0)
Wait(1000)
Table = (1, 2, 3,5,6)
for i in range(1,14):
    Speed_set = i *500
    Set(SIMULATOR, 0, "RPM", Speed_set)
    Wait(1000)
    for j in range(0,5):
        Pattern_RPG = j
        Set(SIMULATOR, 0, "Dataset", Pattern_RPG)
        Wait(5000)
        for times in range(0, Test_times):
            (retc,CRANK_Error_Count_Less) = ReadMemValue(PROCESSOR, 0, "CRANK_ECL")
            (retc,CRANK_Error_Count_More) = ReadMemValue(PROCESSOR, 0, "CRANK_ECM")
            if j==0:
                msg = ("Desc: \"The crank signal should working normally at %d rpm\" Actual: %d Low: %d High: %d " % ( Speed_set, CRANK_Error_Count_Less, 0, 0))
                caseid = "%s(%d)_RPM=%d_%d" % ("CRANK_Teeth_Count_Less",Test_times, Speed_set)
                TTB_Results(caseid, 0, msg)

                msg = ("Desc: \"The crank signal should working normally at %d rpm\" Actual: %d Low: %d High: %d " % ( Speed_set, CRANK_Error_Count_More, 0, 0))
                caseid = "%s(%d)_RPM=%d" % ("CRANK_Teeth_Count_More", Test_times, Speed_set)
                TTB_Results(caseid, 0, msg)
            elif j ==1 or j==2:
                
                msg = ("Desc: \"The crank signal should working abnormally at %d rpm\" Actual: %d Low: %d High: %d " % ( CRANK_Error_Count_Less, j, j))
                caseid = "%s(%d)_RPM=%d_%d" % ("CRANK_Error_Count_Less", Test_times, Speed_set, j)
                TTB_Results(caseid, 0, msg)
            elif j ==3 or j==4:
                msg = ("Desc: \"The crank signal should working abnormally at %d rpm\" Actual: %d Low: %d High: %d " % ( CRANK_Error_Count_More, j-2, j-2))
                caseid = "%s(%d)_RPM=%d_%d" % ("CRANK_Error_Count_More",Test_times, Speed_set, j-2)
                TTB_Results(caseid, 0, msg)

            Wait(1000)

Set(SIMULATOR, 0, "RPM", 0)

###engine state test
for times in range(0, Test_times):
    i =0
    Set(SIMULATOR, 0, "Battery Control State", 1)
    Set(SIMULATOR, 0, "Key Switch State", 1)
    Set(SIMULATOR, 0, "RPM", 0)
    Wait(3000)
    Set(SIMULATOR, 0, "Key Switch State", 3)

    (retc,engine_state) = ReadMemValue(PROCESSOR, 0, "VeVIOS_EngSt")
    msg = ("Desc: \"Keyon and engine speed is 0rpm, and the engine state should change from KeyOff to KeyOn\" Actual: %d Low: %d High: %d " % ( engine_state, 1, 1))
    caseid = "engine_state(%d)_%d" % (Test_times, i)
    TTB_Results(caseid, 0, msg)
    i = i+1

    Set(SIMULATOR, 0, "RPM", 200)
    Wait(2000)

    (retc,engine_state) = ReadMemValue(PROCESSOR, 0, "VeVIOS_EngSt")
    msg = ("Desc: \"Set the engine speed more than 60rpm, and the engine state should change from KeyOn to CRANK\" Actual: %d Low: %d High: %d " % ( engine_state, 2, 2))
    caseid = "engine_state(%d)_%d" % (Test_times, i)
    TTB_Results(caseid, 0, msg)
    i = i+1

    Set(SIMULATOR, 0, "RPM", 0)
    Wait(2000)

    (retc,engine_state) = ReadMemValue(PROCESSOR, 0, "VeVIOS_EngSt")
    msg = ("Desc: \"Set the engine speed is less than 60rpm, and the engine state should change from CRANK to STALL\" Actual: %d Low: %d High: %d " % ( engine_state, 4, 4))
    caseid = "engine_state(%d)_%d" % (Test_times, i)
    TTB_Results(caseid, 0, msg)
    i = i+1

    Set(SIMULATOR, 0, "RPM", 200)
    Wait(2000)

    (retc,engine_state) = ReadMemValue(PROCESSOR, 0, "VeVIOS_EngSt")
    msg = ("Desc: \"Set the engine speed more than 60rpm, and the engine state should change from STALL to CRANK\" Actual: %d Low: %d High: %d " % ( engine_state, 2, 2))
    caseid = "engine_state(%d)_%d" % (Test_times, i)
    TTB_Results(caseid, 0, msg)
    i = i+1

    Set(SIMULATOR, 0, "RPM", 600)
    Wait(2000)

    (retc,engine_state) = ReadMemValue(PROCESSOR, 0, "VeVIOS_EngSt")
    msg = ("Desc: \"Set the engine speed more than 450rpm, and the engine state should change from CRANK to RUN\" Actual: %d Low: %d High: %d " % ( engine_state, 3, 3))
    caseid = "engine_state(%d)_%d" % (Test_times, i)
    TTB_Results(caseid, 0, msg)
    i = i+1

    Set(SIMULATOR, 0, "RPM", 100)
    Wait(2000)

    (retc,engine_state) = ReadMemValue(PROCESSOR, 0, "VeVIOS_EngSt")
    msg = ("Desc: \"Set the engine speed less than 150rpm, and the engine state should change from RUN to CRANK\" Actual: %d Low: %d High: %d " % ( engine_state, 2, 2))
    caseid = "engine_state(%d)_%d" % (Test_times, i)
    TTB_Results(caseid, 0, msg)
    i = i+1
