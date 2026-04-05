/**
  ******************************************************************************
  * Project:    Power Monitor
  * @file    	  power.h
  * @author  	  Mike McMahon, Cypress Embedded Systems
  * @brief   	  This header file provides function and variable declarations for
  *          	  monitoring AC line voltage and related parameters.
  * 
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2025 Mike McMahon, Cypress Embedded Systems.  All rights reserved.</center></h2>
  *	
  * <h3><center>This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.</center></h3>
  * <h3><center>You should have received a copy of the license along with this work.</center></h3>
  * <h3><center>If not, see http://creativecommons.org/licenses/by-nc-sa/4.0/.</center></h3>
  *	
  ******************************************************************************
  */

//This device is intended to be powered by a DC adaptor plugged into a standard 120Vac receptacle.
//The device should not be plugged into a UPS or other battery backed up source of power.
extern bool onAC;

//This device has a built in battery backup to keep the application running in the event of a loss of AC line voltage.
extern bool onBattery;

//Digital I/O
extern int onAcPwr;
extern int onBatPwr;

//Function prototype
void checkACLineVoltage(void);