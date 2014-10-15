#ifndef IMMO_FEXI_H
#define IMMO_FEXI_H
/*===========================================================================*/
/* FILE: immo_fexi.h                                                         */
/*===========================================================================*/
/* COPYRIGHT, 2004, DELPHI ELECTRONICS & SAFETY SYSTEMS, All Rights reserved */
/* Delphi Confidential                                                       */
/*===========================================================================*/
/* %name:             immo_fexi.h %                                          */
/*                                                                           */
/* created_by:       LiuZheng                                                */
/*                                                                           */
/* date_created:     5 Jan 2005                                              */
/*                                                                           */
/* %derived_by:       vzp48z %                                             */
/*                                                                           */
/* %date_modified:   %                                                       */
/*                                                                           */
/* %version:         2 %                                                     */
/*                                                                           */
/*===========================================================================*/
/* DESCRIPTION:                                                              */
/*   This file contains executive called during power On for Immobiliser.    */
/*                                                                           */
/* ABBREVIATIONS:                                                            */
/* None.                                                                     */
/*                                                                           */
/* TRACEABILITY INFO:                                                        */
/*   Design Document:                                                        */
/*                                                                           */
/*   Requirements Document(s):                                               */
/*                                                                           */
/*   Applicable Standards:                                                   */
/*   C Coding Standards:        SW_REF 264.15D.                              */
/*                                                                           */
/* DEVIATIONS FROM STANDARDS:                                                */
/* None.                                                                     */
/*                                                                           */
/*===========================================================================*/
/* REUSE: DO NOT MODIFY THIS FILE.                                           */
/* Co-ordinate any desired changes with the Software Forward Engineering and */
/* Building Blocks group                                                     */
/*===========================================================================*/
#include "reuse.h"
#include "types.h"
/* ============================================================================ *\
 * Other header files.
\* ============================================================================ */
#include "immo_cal.h"
#include "immo_exec.h"
#include "os_kernel.h"    /* For FastPitLoopCounter */
#include "intr_ems.h"	 /* for MT20 EMS interface.    
/* ============================================================================ *\
 * Exported preprocessor #define commands.
\* ============================================================================ */
#define ImmoEnableEngine()    ( ImmoInhibitEngine = false )
#define ImmoDisableEngine()   ( ImmoInhibitEngine = true )

#define ClearAuthenticationResult()     (AuthenticationResultState=CbFALSE)
#define ValidateAuthenticationResult()  (AuthenticationResultState=CbTRUE)
#define AuthenticationResultLost()      (AuthenticationResultState==CbFALSE)

/* ==========================================================================*/
/* File revision history (top to bottom, first revision to last revision     */
/* ==========================================================================*/
/*                                                                           */
/* Date         user id     SCR       (description on following lines)       */
/* ----------   -------     ---                                              */
/* 
/* ==========================================================================*/
 
#endif /* IMMO_FEXI_H */
