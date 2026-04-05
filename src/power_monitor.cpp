/**
  ******************************************************************************
  * Project:    Power Monitor
  * @file    	power_monitor.cpp
  * @author  	Mike McMahon, Cypress Embedded Systems
  * @brief   	This file provides firmware functions that implement the
  *          	power monitoring system.
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


/*
 *  I/O MAPPING
 *  NO.     I/O         DESCRIPTION             SYMBOL          LED COLOR 
 *  D2  -   P1.01   -   ON AC POWER         -   onAcPwr     -   (SOLID) GREEN  
 *  D3  -   P1.02   -   ON BATTERY BACKUP   -   onBatPwr    -   (SOLID) RED   
 *  D4  -   P1.08   -   BATTERY CHARGED     -   batCharged  -   (SOLID) GREEN 
 *  D5  -   P1.10   -   BATTERY CHARGING    -   batCharging -   (FLASHING) YELLOW
 *  D6  -   P1.11   -   BATTERY FAULT       -   batFlt      -   (SOLID) RED
 *  D7  -   P1.12   -   LTE CONNECTED       -   onCell      -   (SOLID) GREEN
 *  D8  -   P1.03   -   LTE SEARCHING       -   cellSearch  -   (FLASHING) RED
 *   
 */


// Include Particle Device OS APIs
#include "Particle.h"
#include "power_monitor.h"
#include "battery.h"
#include "cellular.h"
#include "power.h"
#include "datatransmit.h"
#include "shutdown.h"
#include "spark_wiring.h"

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(AUTOMATIC);

// Run the application and system concurrently in separate threads
SYSTEM_THREAD(ENABLED);

// Object for monitoring power system.
PMIC pmic;

//Declare function prototypes
void init(void);

//Check AC line voltage every 1 second.
Timer powerCheckTimer(1000, checkACLineVoltage, false);

//Check battery status every 1 second.
Timer batteryCheck(1000, batteryStatus, false);

//Check cellular connection every 60 seconds.
Timer cellCheckTimer(60000, testCellularConnection, false);

/*
 *  @brief  Initialization routine called automatically by SoM when system is booted up.
 *  @param  none
 *  @retval none
 */
void setup() {
    
    // The device has booted, reconnect the battery.
	pmic.enableBATFET();

    //initialize variables
	publishFlag = false;
    onAC = false;
    onBattery = false;
    lowBattery = false;
    systemOnBattery = false;
    batteryCharging = false;
    batteryCharged = false;
    batUnknown = false;
    batNotCharging = false;
    batFaulted = false;
    batDisconnected = false;
    defaultDoOnce = false;
    LTEindicatorFlash = false;
    systemConnected = false;
	unknownCount = 0;
    notChargingCount = 0;
    faultCount = 0;
    disconnectCount = 0;

    //initialize digital I/O
	init();

    //Turn on LED indicating that we are waiting for a cellular connection and connection to Particle cloud.
    if (!Cellular.ready() && !Particle.connected()) {
        systemConnected = false;
        digitalWrite(cellSearch, HIGH);
        digitalWrite(onCell, LOW);
    }

    //Wait until connected to cellular network.
    waitUntil(Cellular.ready);

    //Ensure we are connected to the Particle cloud infrastructure.
    waitUntil(Particle.connected);

    //Turn on a LED output indicating cellular and Particle clound are connected.
    if (Cellular.ready() && Particle.connected()) {
        systemConnected = true;
        digitalWrite(cellSearch, LOW);
        digitalWrite(onCell, HIGH);
    }

    // Check whether we are connected to AC line voltage or battery 
    int powerSource = System.powerSource();

    if (powerSource == POWER_SOURCE_BATTERY) {
        //we are on battery
        onBattery = true;
        onAC = false;
        digitalWrite(onBatPwr, HIGH);
        digitalWrite(onAcPwr, LOW);
    }
    else {
        //otherwise we are connected to AC power
        onBattery = false;
        onAC = true;
        digitalWrite(onBatPwr, LOW);
        digitalWrite(onAcPwr, HIGH);
    }
    
    //Send notification to user that the application is booting and connected to cellular.
    //Indicate to user if monitor is on AC power or not.
    if(onBattery) {
         str1 = "Application booting...";
         str2 = "NO AC POWER";
         sendData();
    }
    else {
         str1 = "Application booting...";
         str2 = "AC POWER GOOD";
         sendData();        
    }
    
    //Start timers
	cellCheckTimer.start();
	powerCheckTimer.start();
	batteryCheck.start();
}


/*
 *  @brief  Main routine continuous loop.
 *  @param  none
 *  @retval none
 */
void loop() {
	
    //Must be performed in main thread due to blocking calls of Particle.publish()
	//publish data to Particle cloud and Pushover.  Reset flag after every publish.
	if (publishFlag) {
		sendData();
		publishFlag = false;
	}
	
	//Must be performed in main thread due to blocking calls of delay()
	//Check for low battery conditions and shutdown if necessary.
	//Non-blocking.  Must not be on a timer interrupt callback due to calls to delay().
	lowBatteryLife();
}


/*
 *	@brief	Initialize all physical I/O.
 *	@param	none
 *	@retval	none
 */
 void init(void) {
 
	//Digital outputs - for LED indicators
    onAcPwr = D2;
    onBatPwr = D3;
    batCharged = D4;
    batCharging = D5;
    batFlt = D6;
    onCell = D7;
    cellSearch = D8;

    //Initialize digital outputs
    pinMode(onAcPwr, OUTPUT);
    pinMode(onBatPwr, OUTPUT);
    pinMode(batCharged, OUTPUT);
    pinMode(batCharging, OUTPUT);
    pinMode(batFlt, OUTPUT);
    pinMode(onCell, OUTPUT);
    pinMode(cellSearch, OUTPUT);

    //Set all outputs to known OFF state
    digitalWrite(onAcPwr, LOW);
    digitalWrite(onBatPwr, LOW);
    digitalWrite(batCharged, LOW);
    digitalWrite(batCharging, LOW);
    digitalWrite(batFlt, LOW);
    digitalWrite(onCell, LOW);
    digitalWrite(cellSearch, LOW);
 }
