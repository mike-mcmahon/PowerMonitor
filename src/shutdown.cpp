/**
  ******************************************************************************
  * Project:    Power Monitor
  * @file    	shutdown.cpp
  * @author  	Mike McMahon, Cypress Embedded Systems
  * @brief   	Implement header file functions for shutting down the device
  *          	when below minimum voltage while on battery.
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
#include "power_monitor.h"
#include "power_monitor.h"
#include "shutdown.h"
#include "datatransmit.h"

//Check battery voltage
bool lowBattery;
FuelGauge fuel;

/*
 *  @brief  Check for low battery voltage and shut down system if necessary.
 *          This rountine MUST be called from the main thread (loop()) as it is not thread safe.
 *  @param  none
 *  @retval none
 */
void lowBatteryLife(void) {
	float batteryVoltage = fuel.getVCell();
    int batteryState = System.batteryState();

    //If battery voltage drops below 3.4V send an alert
    if ((batteryVoltage < 3.4) && (batteryState != BATTERY_STATE_DISCONNECTED)) { 
        if (!lowBattery) {
            lowBattery=true;
            str1 = "Power Monitor";
            str2 = "Low Battery";
            sendData();
        }
    }
    //To prevent multiple messages  
    else if (batteryVoltage>3.5) {
            lowBattery=false;
    }

    //Gracefully shut down system when battery voltage is less than 3.3V
    if (batteryVoltage < 3.3) {
        
        //Not connected to line voltage
        if (!pmic.isPowerGood()){
            
            str1 = "Power Monitor";
            str2 = "Shutting down...";
            sendData();

            delay(2000);

            // Disconnect from the cloud and power down the modem.
			Particle.disconnect();
			Cellular.off();
			delay(10000);

            // Disabling the BATFET disconnects the battery from the PMIC. Since there
			// is no longer power, this will turn off the device.
			pmic.disableBATFET();

            // This line should not be reached. When AC line power is applied again, the device
			// will cold boot starting with setup().

			// However, there is a potential for power to be re-applied while we were in
			// the process of shutting down so if we're still running, enable the BATFET
			// again and reconnect to the cloud. Wait a bit before doing this so the
			// device has time to actually power off.
			delay(2000);

			pmic.enableBATFET();
			Cellular.on();
			Particle.connect();

            //Add waitUntil for cellular and cloud???

            str1 = "Power reconnected";
            str2 = "Resuming operation";
            sendData();
        }
    }
}