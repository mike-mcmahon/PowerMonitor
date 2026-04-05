/**
  ******************************************************************************
  * Project:    Power Monitor
  * @file    	  battery.h
  * @author  	  Mike McMahon, Cypress Embedded Systems
  * @brief   	  This header file provides function and variable declarations for battery
  *           	status monitoring.
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

//Battery status
extern bool systemOnBattery;
extern bool batteryCharging;
extern bool batteryCharged;
extern bool batUnknown;
extern bool batNotCharging;
extern bool batFaulted;
extern bool batDisconnected;
extern bool defaultDoOnce;

//Used for battery alarms and faults
extern int unknownCount;
extern int notChargingCount;
extern int faultCount;
extern int disconnectCount;

//Status LED's
extern int batCharged;
extern int batCharging;
extern int batFlt;

//Function prototype
void batteryStatus(void);