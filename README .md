# PowerMonitor

Introduction:
This project was started to create a device that monitors AC voltage and to send push notifications to a users smartphone upon loss of power.
For details of what this product can (currently) do for you, please read the user manual included in the documentation section of this repository.
The project was intended to be a device for sale; however, I have decided to open source it.  Users have the option to use these project files to make their own device, or you can optionally contact me to manufacture and program parts, or all of this project for a fee.  


Documentation:
Included in this repository are the Fusion360 files for 3D models and the electronics required to make this device along with printouts of the schematics and mechanical general assembly drawings.
To use this device you will be required to:
-	Have a Particle.io account and device
-	Pushover.net account
The included user manual provides information that details the features and functionality of the device.  Additional setup guides provide instruction on proper battery installation, and on how to setup your Pushover account.
To set up your account on Particle.io see the documentation below.  In the future I may provide a setup guide for creating/implementing the required custom webhook for Pushover.
Note again that this was a device I had intended to sell, so keep this in mind while reading the documentation.

Source Code:
You will need VS Code installed on your system.
Please note that there are two spots in the source code that you are required to update with your own information.
1.	.vscode/settings.json
Update “particle.targetDevice”: “xxxxxxx” with the correct device name for your Particle Device as configured on Particle.io.
2.	Update Particle.publish("yyyyyyyy", pushoverPacket, PRIVATE); in the file datatransmit.cpp where “yyyyyyyy” is the event name you created for the custom webhook.
Please note that I have built this application on DeviceOS 6.0.0.

License:
Copyright (C) 2025 Mike McMahon.  Creative Commons CC BY-NC-SA 4.0 License applies to all files in this repository.  See LICENSE.md for details.

