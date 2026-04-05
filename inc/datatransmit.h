/**
  ******************************************************************************
  * Project:    Power Monitor
  * @file    	  datatransmit.h
  * @author  	  Mike McMahon, Cypress Embedded Systems
  * @brief   	  This header file provides function and variable declarations for
  *          	  transmitting push notifications.
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

//Push notification strings
extern String str1;
extern String str2;

//To publish data to Particle cloud
extern bool publishFlag;

//Function prototypes
void sendData(void);