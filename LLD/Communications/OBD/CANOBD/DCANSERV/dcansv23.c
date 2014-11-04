/***********************************************************************
*  DELCO ELECTRONICS CORPORATION, INC.                                 *
*  COPYRIGHT 1999 DELCO ELECTRONICS CORPORATION, INC.                  *
*  ALL RIGHTS RESERVED                                                 *
*  This program may not be reproduced, in whole or in part in any form *
*  or by any means whatsoever without the written permission of:       *
*                                                                      *
*         DELCO ELECTRONICS CORPORATION                                *
*         One Corporate Center                                         *
*         Kokomo, Indiana  46904-9005                                  *
*         USA                                                          *
*                                                                      *
************************************************************************
* Filename     : dcansv23.c                                            *
* Project Name : Reusable KW2K                                         *
*                                                                      *
* Applicable   : CANOBD                                *
* Documents      2000 Implementation of Diagnostic                     *
*                Service 10 Recommended Practice  Vers. 1.1   1-31-97  *
*                                                                      *
* Description  : This module contains the Keyword 2000 Diagnostic      *
*                Service 10 as the defined by the above applicable doc.*
*                                                                      *
*                Set the keyword 2000 diagnostic mode to be the        *
*                Standard Diagnostitic State or to be the              *
*                ECU Programming State by the request message.         *
*                In the ECU Programming State, this service can change *
*                the communication baud rate to be the desired baud    *
*                rate.                                                 *
*                                                                      *
* $Source: ems_project@brigh...:daewoo_2002:kw2srv10.c $              *
* $Revision$                                                     *
* $Author: brighton.tcb:/users/sa..._2002_MathLib:safayyad $          *
*                                                                      *
************************************************************************
*                                                                      *
* Change Log:                                                          *
*                                                                      *
* Rev.    Date    User    Description of Changes                       *
* ----  --------  ----    ---------------------------------------------*
* 1   11-12-98  JZha    Initial file creation                        *
* 2   02-28-11  cjqq    Change function LnReadMemoryByAddress        *
* 2   12-13-12  mzh1qz  Add new memory section(CAL) to read CAL      *
*                       data for CANOBD $23                          *
* 3   05-09-13  xll     Change function GetEndAddress()              *
***********************************************************************/
#include "dcansv23.h"
#if (XeDCAN_SID_23_Supported == CeDCAN_Supported)
/******************************************************************************
* APP Include Files
******************************************************************************/
/******************************************************************************
* OBD Lib Service Include Files
******************************************************************************/
#include "obdlfsrv.h"/*CyEEPROM_SectionStart*/
/******************************************************************************
* CANOBD Service Include Files
******************************************************************************/
#include "dcanserv.h"
#include "dcancomm.h"
/***********************************************************************
* Functions in this file:                                              *
************************************************************************

***********************************************************************/
/*********************************************************************/
/*           CONSTANT and ENUMERATION DECLARATIONS                   */
/*********************************************************************/

/***************************************************************/
/*** function needed for LnDiag service ReadMemoryByAddress: ***/
/*** UpdateLnReadMemoryByAddress       (SID23)                      ***/
/***************************************************************/
void UpdateLnReadMemoryByAddress (void)
{
   if (LnReadMemByAddrNbBytesToRead > PacketNbOfBytesToTransfer)
   {
      if (GetLnServNbOfFreeBytesInRingBuffer () >= PacketNbOfBytesToTransfer)
      {
         StoreLnServNbBytesInRingBuffer (PacketNbOfBytesToTransfer,
                                        (uint8_t *) LnReadMemByAddrMemToReadPtr);
         LnReadMemByAddrMemToReadPtr = LnReadMemByAddrMemToReadPtr + PacketNbOfBytesToTransfer;
         LnReadMemByAddrNbBytesToRead = LnReadMemByAddrNbBytesToRead - PacketNbOfBytesToTransfer;
      }
   }
   else
   {
      if (GetLnServNbOfFreeBytesInRingBuffer () >= LnReadMemByAddrNbBytesToRead)
      {
         StoreLnServNbBytesInRingBuffer (LnReadMemByAddrNbBytesToRead,
                                        (uint8_t *) LnReadMemByAddrMemToReadPtr);
      }
      LnReadMemByAddrNbBytesToRead = 0;
      LnDiagSvFlags.ReadMemoryByAddressActive = (bitfield16_t) false;
   }
} /*** End of UpdateLnReadMemoryByAddress ***/

/*--- Functions to substract 1 to get real end-address ---*/
/*--- this is necessary as no address calculations in table are allowed after compile time.     ---*/
static uint32_t GetStartAddress (const MemoryMapType *Addr) { return (Addr->StartAddress);}
static uint32_t GetVirtualAddress (const MemoryMapType *Addr) { return (Addr->VirtualAddressConversion);}
static uint32_t GetEndAddress (const MemoryMapType *Addr) { return ((Addr->EndAddress));}

/**********************************************************************/
/* Table defining the different readable memory zones and the real    */
/* address conversion if the transmitted addresses are virtual.       */
/* The table also indicates the attributes (Read-Only, Read-Protected */
/* Write-Protected). Memory areas may be overlapping (for example     */
/* EEPNVM area inside of RAM area), but in that case the start-       */
/* addresses of those areas must be in increasing order. The virtual  */
/* address conversion will be the one of the last found matching area.*/
/* Start & end addresses may be in different areas, but the virtual   */
/* addresses of both areas must be the same, otherwise a neg. resp.   */
/* "Out of range" is issued.                                          */
/* The protections are OR-ed between start-, end- and included areas, */
/* meaning if a protected area is included between start and end,     */
/* then the access will be denied.                                    */
/* NOTE: End-Address in table is EXCLUDED of the respective area (-1) */
/* The Hidden Attribute table is EXCLUDED of the respective area (-1) */
/**********************************************************************/

const MemoryMapType EcuMemoryMap [] =
{
/*Start-Address              EndAddress                 VirtualAddrConversion       R-only R-prot W-Prot Hidden */
  BootBaseL                  , BootEndL                 , C_NoVirtualAddress        , true , true,  true,  false, /* Boot-ROM   */
  CyEEPROM_SectionStart      , CyEEPROM_SectionEnd      , C_NoVirtualAddress        , true, true,  true,  false,  /* EEP-ROM */
  FlashBaseL                  , FlashEndL                 , C_NoVirtualAddress       , true , true,  true,  false, /* Flash-ROM   */
  CyRAM_SectionStart         , CyRAM_SectionEnd        , C_NoVirtualAddress       , true, false, true,  false,  /* complete RAM */
  CyCal_SectionStart         , CyCal_SectionEnd        , C_NoVirtualAddress       , true, true, true,  false  /* Cal-ROM   */
};

#define C_NumberOfAreas (sizeof(EcuMemoryMap)/sizeof(MemoryMapType))

/**********************************************************************/
/*** Look for a matching memory range for Start&End Address         ***/
/**********************************************************************/
bool FindMatchingMemoryArea (uint32_t StartPtr, uint32_t  EndPtr, uint32_t *VirtualConversion, uint32_t *StartAddr,
                                bool *ReadOnly, bool *ReadProt,bool *WriteProt, bool *Hidden)
{
   uint8_t i, StartArea, EndArea;
   bool Found;

  /* Look for best matching memory area for both Start- and EndPtr */
  /* If Start- and End-Pointer- Areas do not have the same virtual */
  /* address- conversion, the request will be denied.              */
  /* The highest protection of all matching areas will be applied  */
   *ReadOnly = false;
   *ReadProt = false;
   *WriteProt = false;
   *Hidden = false;
   StartArea = C_NumberOfAreas;
   EndArea = C_NumberOfAreas;

   for (i=0; i < C_NumberOfAreas; i++)
   {
      if ((StartPtr >= GetStartAddress (&EcuMemoryMap[i])) &&
        (StartPtr <= GetEndAddress (&EcuMemoryMap[i])))
      { /*--- find start-area ---*/
         StartArea = i;
      }
      if ((EndPtr >= GetStartAddress (&EcuMemoryMap[i])) &&
        (EndPtr <= GetEndAddress (&EcuMemoryMap[i])))
      { /*--- find end-area ---*/
         EndArea = i;
      }
      if ((StartPtr <= GetStartAddress (&EcuMemoryMap[i])) &&
        (EndPtr >= GetStartAddress (&EcuMemoryMap[i])))
      { /*--- check if another area is located between desired start and end address ---*/
         *ReadOnly |= (EcuMemoryMap[i].MemoryAccess.ReadOnly) ? true : false;
         *ReadProt |= (!IsSecurityAccessUnlocked () && EcuMemoryMap[i].MemoryAccess.ReadProtected) ? true : false;
         *WriteProt |= (!IsSecurityAccessUnlocked () && EcuMemoryMap[i].MemoryAccess.WriteProtected) ? true : false;
         *Hidden |= (IsSecurityAccessActivated () && EcuMemoryMap[i].MemoryAccess.Hidden) ? true : false;
      }
   }

   if ((StartArea < C_NumberOfAreas && EndArea < C_NumberOfAreas) &&
      (EcuMemoryMap[StartArea].VirtualAddressConversion == EcuMemoryMap[EndArea].VirtualAddressConversion))
   { /*--- found valid area, virtual addresses match, determine attributes ---*/
      *VirtualConversion = EcuMemoryMap[StartArea].VirtualAddressConversion;
      *StartAddr = EcuMemoryMap[StartArea].StartAddress;
      /* Attributes: -OR- between start, end and included areas */
      *ReadOnly |= (EcuMemoryMap[StartArea].MemoryAccess.ReadOnly ||
                    EcuMemoryMap[EndArea].MemoryAccess.ReadOnly) ? true : false;
      *ReadProt |= (!IsSecurityAccessUnlocked () &&
                    (EcuMemoryMap[StartArea].MemoryAccess.ReadProtected ||
                     EcuMemoryMap[EndArea].MemoryAccess.ReadProtected)) ? true : false;
      *WriteProt |= (!IsSecurityAccessUnlocked () &&
                     (EcuMemoryMap[StartArea].MemoryAccess.WriteProtected ||
                      EcuMemoryMap[EndArea].MemoryAccess.WriteProtected)) ? true : false;
      /* area is "hidden" when security access activated, even if seed&key correct! */
      *Hidden |= (IsSecurityAccessActivated () &&
                  (EcuMemoryMap[StartArea].MemoryAccess.Hidden ||
                   EcuMemoryMap[EndArea].MemoryAccess.Hidden)) ? true : false;
      Found = true;
   }
   else
   {
      Found = false;
   }
   return Found;
} /*** End of FindMatchingMemoryArea ***/

/**********************************************************************/
/*** LnDiag service: ReadMemoryByAddress                            ***/
/**********************************************************************/
void LnReadMemoryByAddress (void)
{
   uint32_t  LnReadMemByAddrMemToReadEndPtr;
   uint32_t  StartAddress, VirtualConversion;
   bool   ReadOnly,ReadProtected, WriteProtected, Hidden, Found;
   
   if (GetLnServiceDataLength () != 7)
   {
      SendLnStandardNegativeAnswer (IncorrectMessageLength);
   } 
   else if ((GetLnServiceData ()) [1] == 0x14 )
   {
      LnReadMemByAddrMemToReadPtr = (((uint32_t) (GetLnServiceData ()) [2] << 24) |
                                 ((uint32_t) (GetLnServiceData ()) [3] << 16) |
                                 ((uint32_t) (GetLnServiceData ()) [4] << 8) |
                                 (GetLnServiceData ()) [5]);
      LnReadMemByAddrNbBytesToRead = (uint16_t)((GetLnServiceData ()) [6]);


      if (LnReadMemByAddrNbBytesToRead > MaxRMemSize)
      {
    /*--- case desired Size > than max. message length ---*/
         SendLnStandardNegativeAnswer (RequestOutOfRange);
      }
      else
      {
         LnReadMemByAddrMemToReadEndPtr = LnReadMemByAddrMemToReadPtr + (uint32_t) (LnReadMemByAddrNbBytesToRead - 1);

         Found = FindMatchingMemoryArea (LnReadMemByAddrMemToReadPtr, LnReadMemByAddrMemToReadEndPtr,
                                    &VirtualConversion, &StartAddress,
                                    &ReadOnly, &ReadProtected,
                                    &WriteProtected, &Hidden);
         if (!Found || Hidden)
         { /* no matching area found or area "hidden" through activated security access */
            SendLnStandardNegativeAnswer (RequestOutOfRange);
            return; /*--- exit function ---*/
         }
         else if (ReadProtected)
         { /*--- Inside area with Security Access not obtained ---*/
            SendLnStandardNegativeAnswer (SecurityAccessDenied);
            return; /*--- exit function ---*/
         }
         else
         {
            if (VirtualConversion != C_NoVirtualAddress)
            { /*--- calculate StartAddress from Virtual-Address ---*/
               LnReadMemByAddrMemToReadPtr = LnReadMemByAddrMemToReadPtr + (VirtualConversion - StartAddress);
            }

        /*--- the use of the ring buffer allows the Read Memory By Address
                      to read a number of bytes bigger than the size of the buffer
                      of the transport layer ---*/
            StoreLnServNbBytesInRingBuffer (1, (uint8_t *) (GetLnServiceData ()));

            WriteLnMessageDataLength (LnReadMemByAddrNbBytesToRead + 1);

            if (LnReadMemByAddrNbBytesToRead > PacketNbOfBytesToTransfer)
            { /*--- response will be filled by block
            of PacketNbOfBytesToTransfer bytes ---*/
               LnDiagSvFlags.ReadMemoryByAddressActive = (bitfield16_t) true;
               StoreLnServNbBytesInRingBuffer (PacketNbOfBytesToTransfer,
                          (uint8_t *) LnReadMemByAddrMemToReadPtr);
               SendLnStandardPositiveAnswer (LnReadMemByAddrNbBytesToRead + 1);
               LnReadMemByAddrMemToReadPtr = LnReadMemByAddrMemToReadPtr
                                            + PacketNbOfBytesToTransfer;
               LnReadMemByAddrNbBytesToRead = LnReadMemByAddrNbBytesToRead
                                        - PacketNbOfBytesToTransfer;
            }
            else
            {
               StoreLnServNbBytesInRingBuffer (LnReadMemByAddrNbBytesToRead,
                            (uint8_t *) LnReadMemByAddrMemToReadPtr);
               SendLnStandardPositiveAnswer (LnReadMemByAddrNbBytesToRead + 1);
            }
         }
      }
   }
   else 
   {
      SendLnStandardNegativeAnswer (RequestOutOfRange);
   }
} /*** End of LnReadMemoryByAddress ***/
#endif

