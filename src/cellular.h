/**
  ******************************************************************************
  * Project:    Power Monitor
  * @file    	  cellular.h
  * @author  	  Mike McMahon, Cypress Embedded Systems
  * @brief   	  This header file provides function and variable declarations for
  *          	  monitoring cellular and Particle cloud connections.
  *  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2025 Mike McMahon, Cypress Embedded Systems. All rights reserved.</center></h2>
  *	
  * <h3><center>This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.</center></h3>
  * <h3><center>You should have received a copy of the license along with this work.</center></h3>
  * <h3><center>If not, see http://creativecommons.org/licenses/by-nc-sa/4.0/.</center></h3>
  *	
  ******************************************************************************
  */

//For LTE Cellular connection status
extern bool systemConnected;
extern bool LTEindicatorFlash;
extern int onCell;
extern int cellSearch;

//Function prototype
void testCellularConnection(void);