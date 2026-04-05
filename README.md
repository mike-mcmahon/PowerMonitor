# PowerMonitor

## Introduction:

This project was started to create a device that monitors AC voltage and to send push notifications to a users smartphone upon loss of power.

This device comes in handy if you ever are concerned about the loss of power in your home or at your cottage.  The user will receive push notifications via cellular (LTE CAT M1) when power is lost
and retored.  Battery backup lasts at least one day (usually more).  No reliance on wifi or ethernet base network connectivity; though you should ensure you have cellular reception in the 
area you plan to deploy this.  *No subscription or dataplan is required when using this device.*

For details of what this product can (currently) do for you, please read the user manual included in the documentation section of this repository.
The project was intended to be a device for sale; however, I have decided to open source it.  Users have the option to use these project files to make their own device, or you can optionally contact me to manufacture and program parts, or all of this project for a fee.  


## Documentation:

Included in this repository are the Fusion360 files for 3D models and the electronics required to make this device along with printouts of the schematics.
To use this device you will be required to:
-	Have a Particle.io account and device
-	Pushover.net account

The included user manual provides information that details the features and functionality of the device.  Additional setup guides provide instruction on proper battery installation, and on how to setup your Pushover account.
To set up your account on Particle.io see the documentation below and online at particle.io.  In the future I may provide a setup guide for creating/implementing the required custom webhook for Pushover.
Note again that this was a device I had intended to sell, so keep this in mind while reading the documentation.

## Source Code:

You will need VS Code installed on your system along with the Particle Workbench extension.
Please note that there are two spots in the source code that you are required to update with your own information.
1.	.vscode/settings.json
  - Update `"particle.targetDevice”: “xxxxxxx”` with `xxxxxxxx` being the correct device name for your Particle Device as configured on Particle.io.
2.	datatransmit.cpp
  - Update `Particle.publish("yyyyyyyy", pushoverPacket, PRIVATE);` in the file datatransmit.cpp where `yyyyyyyy` is the event name you created for the custom webhook.
  
Please note that I have built this application on DeviceOS 6.0.0.

## License:

Copyright (C) 2025 Mike McMahon.  Creative Commons CC BY-NC-SA 4.0 License applies to all files in this repository.  See LICENSE.md for details.

Contact me at [mike@3rdgear.ca] or [mike@cypressembeddedsystems.ca]

-------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------
Automatically generated README file information from Particle Workbench.

This firmware project was created using [Particle Developer Tools](https://www.particle.io/developer-tools/) and is compatible with all [Particle Devices](https://www.particle.io/devices/).

Feel free to replace this README.md file with your own content, or keep it for reference.

## Table of Contents
- [Introduction](#introduction)
- [Prerequisites To Use This Template](#prerequisites-to-use-this-repository)
- [Getting Started](#getting-started)
- [Particle Firmware At A Glance](#particle-firmware-at-a-glance)
  - [Logging](#logging)
  - [Setup and Loop](#setup-and-loop)
  - [Delays and Timing](#delays-and-timing)
  - [Testing and Debugging](#testing-and-debugging)
  - [GitHub Actions (CI/CD)](#github-actions-cicd)
  - [OTA](#ota)
- [Support and Feedback](#support-and-feedback)
- [Version](#version)

## Introduction

For an in-depth understanding of this project template, please refer to our [documentation](https://docs.particle.io/firmware/best-practices/firmware-template/).

## Prerequisites To Use This Repository

To use this software/firmware on a device, you'll need:

- A [Particle Device](https://www.particle.io/devices/).
- Windows/Mac/Linux for building the software and flashing it to a device.
- [Particle Development Tools](https://docs.particle.io/getting-started/developer-tools/developer-tools/) installed and set up on your computer.
- Optionally, a nice cup of tea (and perhaps a biscuit).

## Getting Started

1. While not essential, we recommend running the [device setup process](https://setup.particle.io/) on your Particle device first. This ensures your device's firmware is up-to-date and you have a solid baseline to start from.

2. If you haven't already, open this project in Visual Studio Code (File -> Open Folder). Then [compile and flash](https://docs.particle.io/getting-started/developer-tools/workbench/#cloud-build-and-flash) your device. Ensure your device's USB port is connected to your computer.

3. Verify the device's operation by monitoring its logging output:
    - In Visual Studio Code with the Particle Plugin, open the [command palette](https://docs.particle.io/getting-started/developer-tools/workbench/#particle-commands) and choose "Particle: Serial Monitor".
    - Or, using the Particle CLI, execute:
    ```
    particle serial monitor --follow
    ```

4. Uncomment the code at the bottom of the cpp file in your src directory to publish to the Particle Cloud! Login to console.particle.io to view your devices events in real time.

5. Customize this project! For firmware details, see [Particle firmware](https://docs.particle.io/reference/device-os/api/introduction/getting-started/). For information on the project's directory structure, visit [this link](https://docs.particle.io/firmware/best-practices/firmware-template/#project-overview).

## Particle Firmware At A Glance

### Logging

The firmware includes a [logging library](https://docs.particle.io/reference/device-os/api/logging/logger-class/). You can display messages at different levels and filter them:

```
Log.trace("This is trace message");
Log.info("This is info message");
Log.warn("This is warn message");
Log.error("This is error message");
```

### Setup and Loop

Particle projects originate from the Wiring/Processing framework, which is based on C++. Typically, one-time setup functions are placed in `setup()`, and the main application runs from the `loop()` function.

For advanced scenarios, explore our [threading support](https://docs.particle.io/firmware/software-design/threading-explainer/).

### Delays and Timing

By default, the setup() and loop() functions are blocking whilst they run, meaning that if you put in a delay, your entire application will wait for that delay to finish before anything else can run. 

For techniques that allow you to run multiple tasks in parallel without creating threads, checkout the code example [here](https://docs.particle.io/firmware/best-practices/firmware-template/).

(Note: Although using `delay()` isn't recommended for best practices, it's acceptable for testing.)

### Testing and Debugging

For firmware testing and debugging guidance, check [this documentation](https://docs.particle.io/troubleshooting/guides/build-tools-troubleshooting/debugging-firmware-builds/).

### GitHub Actions (CI/CD)

This project provides a YAML file for GitHub, automating firmware compilation whenever changes are pushed. More details on [Particle GitHub Actions](https://docs.particle.io/firmware/best-practices/github-actions/) are available.

### OTA

To learn how to utilize Particle's OTA service for device updates, consult [this documentation](https://docs.particle.io/getting-started/cloud/ota-updates/).

Test OTA with the 'Particle: Cloud Flash' command in Visual Studio Code or the CLI command 'particle flash'!

This firmware supports binary assets in OTA packages, allowing the inclusion of audio, images, configurations, and external microcontroller firmware. More details are [here](https://docs.particle.io/reference/device-os/api/asset-ota/asset-ota/).

## Support and Feedback

For support or feedback on this template or any Particle products, please join our [community](https://community.particle.io)!

## Version

Template version 1.0.2

