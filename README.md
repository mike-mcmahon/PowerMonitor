# PowerMonitor

## Table of Contents
- [Introduction](#introduction)
- [Documentation](#documentation)
- [Source Code](#source-code)

- [Information - Particle.io](#information---particleio)
- [Prerequisites To Use This Repository (Software)](#prerequisites-to-use-this-repository-software)
- [Getting Started](#getting-started)

- [License](#license)
- [Support and Feedback](#support-and-feedback)



## Introduction

This project was started to create a device that monitors AC voltage and to send push notifications to a users smartphone upon loss and restoration of power.

This device comes in handy if you ever are concerned about the loss of power in your home or at your cottage.  The user will receive push notifications via cellular (LTE CAT M1) when power is lost
and retored.  Battery backup lasts at least one day *(usually more)*.  No reliance on wifi or ethernet based network connectivity; though you should ensure you have cellular reception in the 
area you plan to deploy this.  *No subscription or data plan is required when using this device.*

For details of what this product can *currently* do for you, please read the user manual included in the documentation section of this repository.
The project was intended to be a product/device for sale; however, I have decided to open source it.  Users have the option to use these project files to make their own device, or you can optionally contact me to manufacture and program part, or all, of this project for a *fee*.  

## Documentation:

Included in this repository are the Fusion360 files for 3D models and the electronics required to make this device along with printouts of the schematics.
To use this device you will be required to:
-	Have a Particle.io account and device
-	Pushover.net account

The included user manual provides information that details the features and functionality of the device.  Additional setup guides provide instruction on proper battery installation, and on how to setup your Pushover account.
To set up your account on Particle.io see the documentation below and online at [Particle.io](https://www.particle.io/).  In the future I may provide a setup guide for creating/implementing the required custom webhook for Pushover.
*Note again that this was a device I had intended to sell, so keep this in mind while reading the documentation.*

## Source Code:

You will need VS Code installed on your system along with the Particle Workbench extension.
  
Please note that I have built this application on DeviceOS 6.0.0.

See [Getting Started](#getting-started) for further information.

## Information - Particle.io

The firmware in this project was created using [Particle Developer Tools](https://www.particle.io/developer-tools/).

## Prerequisites To Use This Repository (Software)

To use this software/firmware you'll need:

- A BRN404X [Particle Device](https://www.particle.io/devices/).
- Windows/Mac/Linux for building the software and flashing it to a device.
- [Particle Development Tools](https://docs.particle.io/getting-started/developer-tools/developer-tools/) installed and set up on your computer.  VC Code with Particle Workbench installed is recommended.
- [Pushover.net](https://pushover.net/) account set up and User key along with API token created.  See setup guide included in the documentation section of this repository.

## Getting Started

1. While not essential, it is recommended to run the [device setup process](https://setup.particle.io/) on your Particle device first. This ensures your device's firmware is up-to-date and you have a solid baseline to start from.

2. If you haven't already, open this project in Visual Studio Code (File -> Open Folder). 

3. There are two spots in the source code that you are required to update with your own information.
  a.	.vscode/settings.json
    - Update `"particle.targetDevice”: “xxxxxxx”` with `xxxxxxxx` being the correct device name for your Particle Device as configured on Particle.io.
  b.	datatransmit.cpp
    - Update `Particle.publish("yyyyyyyy", pushoverPacket, PRIVATE);` in the file datatransmit.cpp where `yyyyyyyy` is the event name you created for the custom webhook.

4. Then [compile and flash](https://docs.particle.io/getting-started/developer-tools/workbench/#cloud-build-and-flash) your device. Ensure your device's USB port is connected to your computer.

5. Refer to the user manual included in this repository on the functionality the PowerMonitor provides and verify the device is working.

## License:

Copyright (C) 2025 Mike McMahon.  Creative Commons CC BY-NC-SA 4.0 License applies to all files in this repository.  See LICENSE.md for details.

## Support and Feedback

Contact me at [mike@3rdgear.ca] or [mike@cypressembeddedsystems.ca]



