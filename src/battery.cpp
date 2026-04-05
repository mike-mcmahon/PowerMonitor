/**
  ******************************************************************************
  * Project:    Power Monitor
  * @file    	battery.cpp
  * @author  	Mike McMahon, Cypress Embedded Systems
  * @brief   	This file implements functions in battery.h
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
#include "battery.h"
#include "datatransmit.h"
#include "power.h"

// Battery status
bool systemOnBattery;
bool batteryCharging;
bool batteryCharged;
bool batUnknown;
bool batNotCharging;
bool batFaulted;
bool batDisconnected;
bool defaultDoOnce;

// Used for battery alarms and faults
int unknownCount;
int notChargingCount;
int faultCount;
int disconnectCount;

// Status LED's
int batCharged;
int batCharging;
int batFlt;

/*
 *  @brief  Check and monitor battery status for faults and current condition.
 *          Low voltage conditions leading to shutdown are covered in shutdown.h .cpp
 *  @param  none
 *  @retval none
 */
void batteryStatus(void)
{
    // Check to see if the battery is connected and charged or charging.
    int batteryState = System.batteryState();

    // If battery is charged
    if (batteryState == BATTERY_STATE_CHARGED && !batteryCharged)
    {
        batteryCharged = true;
        batteryCharging = false;
        systemOnBattery = false;
        digitalWrite(batFlt, LOW);
        digitalWrite(batCharging, LOW);
        digitalWrite(batCharged, HIGH);
    }

    // If battery is charging
    if (batteryState == BATTERY_STATE_CHARGING && !batteryCharging)
    {
        batteryCharged = false;
        systemOnBattery = false;
        batteryCharging = true;
        digitalWrite(batFlt, LOW);
        digitalWrite(batCharged, LOW);
        digitalWrite(batCharging, LOW);
    }
    else if (batteryState == BATTERY_STATE_CHARGING && batteryCharging)
    {
        batteryCharging = false;
        digitalWrite(batFlt, LOW);
        digitalWrite(batCharged, LOW);
        digitalWrite(batCharging, HIGH);
    }

    // If we are on battery power turn off the battery charged and charging status LED's
    if (onBattery && !systemOnBattery)
    {
        systemOnBattery = true;
        batteryCharged = false;
        batteryCharging = false;
        digitalWrite(batCharged, LOW);
        digitalWrite(batCharging, LOW);
    }

    // Battery fault handling
    // Add delay counter to each fault state to ignore transient events.  Only faults lasting longer than 10 seconds should be noted.
    switch (batteryState)
    {
    case BATTERY_STATE_UNKNOWN:
        unknownCount++;
        if ((unknownCount > 10) && !batUnknown)
        {
            // to prevent overflow errors
            unknownCount = 0;
            batUnknown = true;
            defaultDoOnce = false;
            batteryCharged = false;
            batteryCharging = false;
            digitalWrite(batCharged, LOW);
            digitalWrite(batCharging, LOW);
            digitalWrite(batFlt, HIGH);
            str1 = "Battery";
            str2 = "State Unknown";
            publishFlag = true;
        }
        break;

    case BATTERY_STATE_NOT_CHARGING:
        notChargingCount++;
        if ((notChargingCount > 10) && !batNotCharging)
        {
            // to prevent overflow errors
            notChargingCount = 0;
            batNotCharging = true;
            defaultDoOnce = false;
            batteryCharged = false;
            batteryCharging = false;
            digitalWrite(batCharged, LOW);
            digitalWrite(batCharging, LOW);
            digitalWrite(batFlt, HIGH);
            str1 = "Battery";
            str2 = "Not Charging";
            publishFlag = true;
        }
        break;

    case BATTERY_STATE_FAULT:
        faultCount++;
        if ((faultCount > 10) && !batFaulted)
        {
            // to prevent overflow errors
            faultCount = 0;
            batFaulted = true;
            defaultDoOnce = false;
            batteryCharged = false;
            batteryCharging = false;
            digitalWrite(batCharged, LOW);
            digitalWrite(batCharging, LOW);
            digitalWrite(batFlt, HIGH);
            str1 = "Battery";
            str2 = "Fault";
            publishFlag = true;
        }
        break;

    case BATTERY_STATE_DISCONNECTED:
        disconnectCount++;
        if ((disconnectCount > 10) && !batDisconnected)
        {
            // to prevent overflow errors
            disconnectCount = 0;
            batDisconnected = true;
            defaultDoOnce = false;
            batteryCharged = false;
            batteryCharging = false;
            digitalWrite(batCharged, LOW);
            digitalWrite(batCharging, LOW);
            digitalWrite(batFlt, HIGH);
            str1 = "Battery";
            str2 = "Disconnected";
            publishFlag = true;
        }
        break;

    default:
        // Do only once to prevent multiple writes
        if (!defaultDoOnce)
        {
            defaultDoOnce = true;
            batUnknown = false;
            unknownCount = 0;
            batNotCharging = false;
            notChargingCount = 0;
            batFaulted = false;
            faultCount = 0;
            batDisconnected = false;
            disconnectCount = 0;
            digitalWrite(batFlt, LOW);
        }
        break;
    }
}