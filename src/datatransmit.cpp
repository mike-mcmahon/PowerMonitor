/**
  ******************************************************************************
  * Project:    Power Monitor
  * @file    	  datatransmit.cpp
  * @author  	  Mike McMahon, Cypress Embedded Systems
  * @brief   	  This file implements the functions in datatransmit.h
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
#include "datatransmit.h"

//Data strings
String str1;
String str2;

//To publish data to Particle cloud
bool publishFlag;

/*
 *  @brief  Prepare and send push notifications.
 *  @param  none
 *  @retval none
 */
void sendData(void) {
     
    //Character arrays for push notifications
    char pushName[50];
    char pushMessage[50];
    str1.toCharArray(pushName, str1.length() + 1);
    str2.toCharArray(pushMessage, str2.length() + 1);
     
    //Concatinate string messages to a Pushover packet.
    String pushoverPacket = "[{\"key\":\"title\", \"value\":\"";
    pushoverPacket.concat(str1);
    pushoverPacket.concat("\"},");
    pushoverPacket.concat("{\"key\":\"message\", \"value\":\"");
    pushoverPacket.concat(str2);
    pushoverPacket.concat("\"}]");
    
    //Transmit push notification.
    Particle.publish("yyyyyyyy", pushoverPacket, PRIVATE);
}