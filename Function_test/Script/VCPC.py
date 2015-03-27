from PyDevice import *
Set(SIMULATOR, 0, "Battery Control State", 1)
Wait(100)
#Set(SIMULATOR, 0, "Key Switch State", 1)
Wait(2000)
Set(SIMULATOR, 0, "Key Switch State", 3)
Set(SIMULATOR, 0, "RPM", 800)
Test_times =20
error_max =1.05
error_min =0.95
###CAM_IN
for i in range(1,7):
    speed_set = i*1000
    Set(SIMULATOR, 0, "RPM", speed_set)
    Wait(3000)
    
    for j in range(-18,11):
        phase_set = j*(-5)
        Set(SIMULATOR, 0, "CAM B", phase_set*(-1)) ##the axiasname should be distributed
        for times in range(0, Test_times):
            Wait(2000)
            (retc,phase) = ReadMemValue(PROCESSOR, 0, "CAMPHIN0")
            cam_phase = 120-phase 
            Phase_Low = phase_set*error_min
            Phase_up  = phase_set*error_min
            msg = ("Desc: \"Set the CAM1 phase is %d degrees and engine speed is %d rpm, read the actual CAM1 phase and compare it with the expected phase \" Actual: %d Low: %d High: %d " % ( phase_set, speed_set, cam_phase, Phase_Low, Phase_up))
            caseid = "%s_RPM(%d)_phase(%d)_%d" % ("CAM1",speed_set, phase_set, times )
            TTB_Results(caseid, 0, msg)
        
        
Set(SIMULATOR, 0, "CAM B", 0)            
Set(SIMULATOR, 0, "RPM", 0)
###CAM_OUT
for i in range(1,7):
    speed_set = i*1000
    Set(SIMULATOR, 0, "RPM", speed_set)
    Wait(3000)
    
    for j in range(-10,19):
        phase_set = j*(-5)
        Set(SIMULATOR, 0, "CAM C", phase_set*(-1)) ##the axiasname should be distributed
        for times in range(0, Test_times):
            Wait(2000)
            (retc,phase) = ReadMemValue(PROCESSOR, 0, "CAMPHOUT0")
            cam_phase = phase - 60
            Phase_Low = phase_set*0.95
            Phase_up  = phase_set*1.05
            msg = ("Desc: \"Set CAM2 phase is %d degrees and engine speed is %d rpm, read the actual CAM2 phase and compare it with expected phase\" Actual: %d Low: %d High: %d " % ( phase_set,speed_set, cam_phase, Phase_Low, Phase_up))
            caseid = "%s_RPM(%d)_phase(%d)_%d" % ("CAM2",speed_set, phase_set, times )
            TTB_Results(caseid, 0, msg)
    
Set(SIMULATOR, 0, "CAM C", 0)
Set(SIMULATOR, 0, "RPM", 0)
