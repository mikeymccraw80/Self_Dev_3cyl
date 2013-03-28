#ifndef IO_INIT_H
#define IO_INIT_H
//=============================================================================
//
//       COPYRIGHT, 2006, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:            io_initialize.h~2:incl:ctc_pt3#1 %
//
// created_by:       fz3pdz
//
// date_created:     Wed Apr 12 22:14:31 2006
//
// %derived_by:      zzrfyj %
//
// %date_modified:      %
//
// %version:         2 %
//
//=============================================================================


//=============================================================================
// InitializeHardwareRegisters                                               
//                                                                           
// Initialize all hardware related registers.  It is assumed that            
// the processor has just come out of reset.                                 
//                                                                           
// Parameters:    none                                                       
// Returns:       none                                                       
//                                                                           
//=============================================================================
void InitializeHardwareRegisters(void);


//=============================================================================
// RefreshHardwareRegisters                                                  
//                                                                           
// Refreshes all the hardware related registers.                             
//                                                                           
// Parameters:    none                                                       
// Returns:       none                                                       
//                                                                           
//=============================================================================
void RefreshHardwareRegisters(void);


//=============================================================================
// InitializeHardwareFirst                                                   
//                                                                           
// This procedure is the very first to be called after processor             
// reset.  It is assumed that all the hardware registers have been           
// initialized.                                                              
//                                                                           
// Parameters:    none                                                       
// Returns:       none                                                       
//                                                                           
//=============================================================================
void InitializeHardwareFirst(void);


//=============================================================================
// InitializeHardwareLast                                                    
//                                                                           
// This procedure is the very last to be called after processor              
// reset.  It is assumed that the scheduler will be the next to run.         
//                                                                           
// Parameters:    none                                                       
// Returns:       none                                                       
//                                                                           
//=============================================================================
void InitializeHardwareLast(void);

//=============================================================================
// InitializeIllegalConditionCheck
//                                                                           
// This procedure is to check the illegal condition to brach into testability
// software
//                                                                           
// Parameters:    none                                                       
// Returns:       bool
//                                                                           
//=============================================================================
//bool InitializeIllegalConditionCheck(void);

#endif // IO_INIT_H

