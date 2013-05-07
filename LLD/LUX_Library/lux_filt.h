#ifndef LUX_FILT
#define LUX_FILT
/*-------------------------------------------------------------------*/
/* Filename -  FILTER.H                                              */
/*                                                                   */
/* Purpose:                                                          */
/*                                                                   */
/* This module provides general purpose filter utilities.            */
/*                                                                   */
/* Filters are normally used to filter out unwanted transients from  */
/* input values.  An interpolation is done between the new value and */
/* the old value.  The equation for this is:                         */
/*                                                                   */
/*    Result = OldValue + Coefficient * ( NewValue - OldValue )      */
/*                                                                   */
/* The filter coefficient is a fraction (0.XXXX) from 0.0 to < 1.0   */
/* with either 16 or 8 bit resolution that can be calculated from    */
/* the time constant equation:                                       */
/*                                                                   */
/*                              -Loop / Tau                          */
/*    Coefficient = N * ( 1 - E             )                        */
/*                                                                   */
/* Where:                                                            */
/*                                                                   */
/*       N  = 256 for 8 bit coefficient                              */
/*       E  = 2.71828182845                                          */
/*    Loop  = Time between calls to this function                    */
/*     Tau  = Desired time constant                                  */
/*                                                                   */
/*                                                                   */
/* List of Function(s):                                              */
/*  Proto:  Lag_Filter_B                                             */
/*          Slow_Lag_Filter_B                                        */
/*          Lag_Filter_W                                             */
/*          Lag_Filter_Approx_W                                      */
/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/
/* SASD C Engine Management Software                                 */
/* (c) Copyright Delco Electronics Europe 1999                       */
/* Origin: 06-Dec-1997 from rev 1.2 partition : math                 */
/* Written by: Craig Rolfe                                           */
/*-------------------------------------------------------------------*/


#include "lux_type.h" /* for CARDINAL, SHORTCARD, Filter_Coefficient */


/************************************************************/
/***                                                      ***/
/************************************************************/

CARDINAL Lag_Filter_B (register SHORTCARD NewValue,
                       register CARDINAL  OldValue,
                       register Filter_Coefficient Coefficient);


/************************************************************/
/***                                                      ***/
/************************************************************/

CARDINAL Slow_Lag_Filter_B (register SHORTCARD NewValue,
                            register CARDINAL  OldValue,
                            register Filter_Coefficient_W Coefficient);


/************************************************************/
/***                                                      ***/
/************************************************************/

CARDINAL Lag_Filter_W (register CARDINAL NewValue,
                       register CARDINAL OldValue,
                       register Filter_Coefficient Coefficient);


/************************************************************/
/***                                                      ***/
/************************************************************/

CARDINAL Lag_Filter_Approx_W (register CARDINAL NewValue,
                              register CARDINAL OldValue,
                              register Filter_Coefficient Coefficient);


#endif

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1     040506 woz 3990 Implemented changes required for TCL TORQ integration.
*
******************************************************************************/
