/**
  ******************************************************************************
  * Project:    Power Monitor
  * @file    	  cellular.cpp
  * @author  	  Mike McMahon, Cypress Embedded Systems
  * @brief   	  Implements prototypes in header file cellular.h
  *          	  monitoring cellular and Particle cloud connections.
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
#include "cellular.h"

//For LTE Cellular connection status
bool systemConnected;
bool LTEindicatorFlash;
int onCell;
int cellSearch;

/*
 *  @brief  Check to ensure LTE cellular is still connected.
 *          Note: If cellular connection is lost, the module will attempt to reconnect on its own.  
 *          There is no need for this application code to make the attempt to reconnect.
 *  @param  none
 *  @retval none
 */
void testCellularConnection(void) {
    //check that we are still connected to cellular and the Particle cloud service
	if (Cellular.ready() && Particle.connected()) {
		systemConnected = true;
		digitalWrite(onCell, HIGH);
		digitalWrite(cellSearch, LOW);
	}
	else {
		systemConnected = false;
		digitalWrite(onCell, LOW);
		digitalWrite(cellSearch, HIGH);
	}
}