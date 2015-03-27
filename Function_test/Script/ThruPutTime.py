from PyDevice import *

Set(SIMULATOR, 0, "Battery Control State", 1)
Wait(100)
#Set(SIMULATOR, 0, "Key Switch State", 1)
Wait(2000)
Set(SIMULATOR, 0, "Key Switch State", 3)
####Inital the engine working condition and the fellow parameter should be adjust to the better
Set(SIMULATOR, 0, "RPM", 500)
Set(SIMULATOR, 0, "MAP", 0.8)
Set(SIMULATOR, 0, "CTS", 4100)
Set(SIMULATOR, 0, "MAT", 2700)
Set(SIMULATOR, 0, "TPSPD", 0.4)
Set(SIMULATOR, 0, "TPSPU", 0.2)

Test_times =20
####change the rpm form 500 to 6000 and back to 500 in every 3s
Wait(2000)
for i in range(1, 13):
    Set(SIMULATOR, 0, "RPM", 500*i)
    Wait(3000)
for i in range(1, 12):
    Set(SIMULATOR, 0, "RPM", 6000 - 500*i)
    Wait(3000)
####Reading the time in different timebase


#VaOSTK_ThruPutData[x].
#       t_MaxExecTime ,  t_MinExecTime, t_AvgExecTime, (min,max)(us),descri
Table = (
          ("TP1LPMXET",    "TP1LPMIET",    "TP1LPAET",  (0, 1000), "1ms loop"), \
          ("TP2LPMXET",    "TP2LPMIET",    "TP2LPAET",  (0, 2000), "2ms loop"), \
          ("TP5LPMXET",    "TP5LPMIET",    "TP5LPAET",  (0, 5000), "5ms loop"), \
          ("TP10LPMXET",   "TP10LPMIET",   "TP10LPAET", (0, 10000, "10ms loop")), \
          ("TP1HPMXET",    "TP1HPMIET",    "TP1HLPAET", (0, 100000), "100ms loop"), \
          ("TP1TBMXET",    "TP1TBMIET",    "TP1TBPAET", (0, 1000), "1ms time base"), \
          ("TP2TBMXET",    "TP2TBMIET",    "TP2TBPAET", (0, 2000), "2ms time base"), \
          ("TP5TBMXET",    "TP5TBMIET",    "TP5TBPAET", (0, 5000), "5ms time base"), \
          ("TP10TBMXET",   "TP10TBMIET",   "TP10TBPAET",(0, 10000), "10ms time base"), \
          ("TPCLYMXET",    "TPCLYMIET",    "TPCLYAET",  (0, 5000), "cylinder event"), \
          ("WDGFDMAFT",    "WDGFDMIFT",    "WDGFDAVFT",  (0, 1000), "feed dog update event"), \

            )
for times in range(0, Test_times):
    for A2lName1, A2lName2, A2lName3, Scope, Descri in Table:
        i =1
        (retc, ExecuTime) = ReadMemValue(PROCESSOR, 0, A2lName1)
        msg = ("Desc: \"%s, max execution time test\" Actual: %d Low: %d High: %d " % (Descri, ExecuTime, Scope[0], Scope[1]))
        caseid = "%s(%d)_%d" % (Descri, times, i)
        TTB_Results(caseid, 0, msg)
        Wait(500)
        i = i+1
        (retc, ExecuTime) = ReadMemValue(PROCESSOR, 0, A2lName2)
        msg = ("Desc: \"%s, min execution time test\" Actual: %d Low: %d High: %d " % (Descri, ExecuTime, Scope[0], Scope[1]))
        caseid = "%s(%d)_%d" % (Descri, times, i)
        TTB_Results(caseid, 0, msg)
        Wait(500)
        i = i+1
        (retc, ExecuTime) = ReadMemValue(PROCESSOR, 0, A2lName3)
        msg = ("Desc: \"%s, avg execution time test\" Actual: %d Low: %d High: %d " % (Descri, ExecuTime, Scope[0], Scope[1]))
        caseid = "%s(%d)_%d" % (Descri, times, i)
        TTB_Results(caseid, 0, msg)
        Wait(500)

