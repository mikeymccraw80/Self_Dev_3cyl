from PyDevice import *
Set(SIMULATOR, 0, "Battery Control State", 1)
Wait(100)
#Set(SIMULATOR, 0, "Key Switch State", 1)
Wait(2000)
Set(SIMULATOR, 0, "Key Switch State", 3)
Set(SIMULATOR, 0, "RPM", 800)
Set(SIMULATOR, 0, "Dataset", 1)
Test_times =1
error_max =1.1
error_min =0.9
phase =0
(retc,phase) = ReadMemValue(PROCESSOR, 0, "CAMPHIN0")
###CAM_IN
TTB_Results("Test case 1", 0, "CAM1 phase test; change cam1 signal angle output of OPAL-RT and read the actual cam angle captured by ECU, and compare it with the expected phase angle.", " ")
for i in range(1,7):
    speed_set = i*1000
    Set(SIMULATOR, 0, "RPM", speed_set)
    TTB_Results("Test case 1.%d"%(i), 0, "Test condition: rpm =%d"%(speed_set), " ")  
    Wait(3000)
    
    for j in range(-12,1):
        phase_set = j*(-5)
        Set(SIMULATOR, 0, "CAM B", phase_set*(-1)) ##the axiasname should be distributed
        for times in range(1, Test_times+1):
            Wait(2000)
            (retc,phase) = ReadMemValue(PROCESSOR, 0, "CAMPHIN0")
            cam_phase = 120-phase
            if cam_phase >=0:
                Phase_Low = phase_set*error_min
                Phase_up  = phase_set*error_max
            else:
                Phase_Low = phase_set*error_max
                Phase_up  = phase_set*error_min
            msg = ("Desc: \"Set the CAM1 target phase angle is %d degrees and engine speed is %d rpm, read the actual CAM1 phase angle\" Actual: %d Low: %d High: %d " % ( phase_set, speed_set, cam_phase, Phase_Low, Phase_up))
            caseid = "%s_%dCrA_%drpm" % ("CAM1",phase_set, speed_set )
            TTB_Results(caseid, 0, msg)
        
TTB_Results("Test case 2", 0, "CAM2 phase test; change cam2 signal angle output of OPAL-RT and read the actual cam angle, and compare it with the expected phase angle.", " ")
Set(SIMULATOR, 0, "CAM B", 0)            
Set(SIMULATOR, 0, "RPM", 0)

###CAM_OUT
for i in range(1,7):
    speed_set = i*1000
    Set(SIMULATOR, 0, "RPM", speed_set)
    TTB_Results("Test case 2.%d"%(i), 0, "Test condition: rpm =%d"%(speed_set), " ")  
    Wait(3000)
    
    for j in range(0,13):
        phase_set = j*(-5)
        Set(SIMULATOR, 0, "CAM C", phase_set*(-1)) ##the axiasname should be distributed
        for times in range(1, Test_times+1):
            Wait(2000)
            (retc,phase) = ReadMemValue(PROCESSOR, 0, "CAMPHOUT0")
            cam_phase =  60 - phase
            if cam_phase >=0:
                Phase_Low = phase_set*error_min
                Phase_up  = phase_set*error_max
            else:
                Phase_Low = phase_set*error_max
                Phase_up  = phase_set*error_min
            msg = ("Desc: \"Set CAM2 target phase angle is %d degrees and engine speed is %d rpm, read the actual CAM2 phase angle\" Actual: %d Low: %d High: %d " % ( phase_set,speed_set, cam_phase, Phase_Low, Phase_up))
            caseid = "%s_%dCrA_%drpm" % ("CAM2",phase_set, speed_set )
            TTB_Results(caseid, 0, msg)
    
Set(SIMULATOR, 0, "CAM C", 0)
Set(SIMULATOR, 0, "RPM", 0)
