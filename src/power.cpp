/**
  ******************************************************************************
  * Project:    Power Monitor
  * @file    	power.cpp
  * @author  	Mike McMahon, Cypress Embedded Systems
  * @brief   	This file implements the functions in power.h
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

#include "Particle.h"
#include "power.h"
#include "datatransmit.h"
#include "cellular.h"

//This device is intended to be powered by a DC adaptor plugged into a standard 120Vac receptacle.
//The device should not be plugged into a UPS or other battery backed up source of power.
bool onAC;

//This device has a built in battery backup to keep the application running in the event of a loss of AC line voltage.
bool onBattery;

//Digital I/O
int onAcPwr;
int onBatPwr;

/*
 *  @brief  Check and monitor AC line voltage.
 *  @param  none
 *  @retval none
 */
void checkACLineVoltage(void) {
    
    //Monitor AC line voltage every 1 second unless cellular connectivity is lost; then
    //signal user by flashing cellular connection status LED indicator on/off every 1 second.

	//Control cellular connection status LED on module.
	//Cellular or Particle Cloud is lost, turn off indicator
	
	//NOTE:  	This logic is in this file and not in cellular.cpp as the LED's need to blink at 2Hz
	//			and the functionality won't work on a function called only once a minute.
	if (!systemConnected && !LTEindicatorFlash) {
		digitalWrite(onCell, LOW);
		digitalWrite(cellSearch, LOW);
		LTEindicatorFlash = true;
	}
	//Cellular or Particle Cloud is lost, turn on indicator
	else if(!systemConnected && LTEindicatorFlash) {
		digitalWrite(onCell, LOW);
		digitalWrite(cellSearch, HIGH);
		LTEindicatorFlash = false;
	}
	//Cellular is restored
	else if (systemConnected) {
			LTEindicatorFlash = false;
			digitalWrite(onCell, HIGH);
			digitalWrite(cellSearch, LOW);
	}

	// Check status of AC line voltage only if connected to cellular and Particle cloud.
	if(systemConnected) {
		int powerSource = System.powerSource();
		
		//If on battery backup
		if (powerSource == POWER_SOURCE_BATTERY) {
			//Changed from AC line to battery
			if(!onBattery && onAC){
				onBattery = true;
				onAC = false;

				//set LED indicators on module
				digitalWrite(onBatPwr, HIGH);
				digitalWrite(onAcPwr, LOW);

				//send push notification
				str1 = "Power Monitor";
				str2 = "AC POWER LOST";
				publishFlag = true;
			}
		}   
		//If on AC line power
		else if (onBattery && !onAC) {
			onBattery = false;
			onAC = true;

			//set LED indicators on module
			digitalWrite(onBatPwr, LOW);
			digitalWrite(onAcPwr, HIGH);

			//send push notification
			str1 = "Power Monitor";
			str2 = "AC POWER IS ON";
			publishFlag = true;
		}
	}
}