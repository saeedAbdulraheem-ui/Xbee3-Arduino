# Xbee3-Arduino Library

The Xbee3-Arduino library provides functionality to interact with Xbee3 devices using an Arduino microcontroller. This library is designed to simplify the process of sending and receiving data to and from Xbee3 modules.

## Table of Contents
- [Introduction](#introduction)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
  - [AtCmds Class](#atcmds-class)
    - [broadcastAT](#broadcastat)
    - [apiToAddr](#apitoaddr)
    - [apiToAddr64](#apitoaddr64)
    - [discovery](#discovery)
    - [transmitCoordinator](#transmitcoordinator)
- [Contributing](#contributing)
- [License](#license)

## Introduction

The Xbee3-Arduino library simplifies communication with Xbee3 devices in an Arduino environment. It offers functions for broadcasting commands, sending data to specific addresses, and discovering nearby devices.

## Getting Started

### Prerequisites

Before using this library, ensure you have the following prerequisites:

- An Arduino board compatible with your Xbee3 module.
- Xbee3 module(s) with the appropriate firmware and setup.

### Installation

To install the Xbee3-Arduino library, follow these steps:

1. Download the library from [GitHub](https://github.com/saeedAbdulraheem-ui/Xbee3-Arduino).

2. In the Arduino IDE, go to **Sketch > Include Library > Add .ZIP Library...**.

3. Select the downloaded Xbee3-Arduino library ZIP file and click **Open**.

The library is now installed and ready to use.

## Usage

### AtCmds Class

The `AtCmds` class provides methods to communicate with Xbee3 modules. Below are the available methods:

#### `broadcastAT(par1, par2, value)`

Broadcasts an AT command to all Xbee3 devices.

- `par1` and `par2`: Command parameters.
- `value`: The value you want to assign to these parameters.

Example:
    AtCmds atCmds;
    atCmds.broadcastAT('A', 'T', 'D');

#### `apiToAddr(par1, par2, value, msb, lsb)`
Sends an AT command to a specific 16-bit address.

- par1 and par2: Command parameters.
- value: The value you want to assign to these parameters.
- msb and lsb: The 16-bit address.

Example:
    AtCmds atCmds;
    atCmds.apiToAddr('D', 'H', 42, 36);

#### `apiToAddr64(par1, par2, ms32, ls32, lenHigh, lenLow)`
Sends an AT command to a specific 64-bit address with a specified length.

- par1 and par2: Command parameters.
- ms32 and ls32: The 64-bit address.
- lenHigh and lenLow: Length of the packet.

Example:
    AtCmds atCmds;
    atCmds.apiToAddr64('D', 'H', 0x0013A200, 0x40C4CB89, 0x00, 0x0F);

#### `apiToAddr64(par1, par2, ms32, ls32, lenHigh, lenLow, value)`
Sends an AT command to a specific 64-bit address with a specified length and value.

- par1 and par2: Command parameters.
- ms32 and ls32: The 64-bit address.
- lenHigh and lenLow: Length of the packet.
- value: The value you want to assign to these parameters.

Example:
    AtCmds atCmds;
    atCmds.apiToAddr64('D', 'H', 0x0013A200, 0x40C4CB89, 0x00, 0x0F, 'P');

#### `discovery()`
Initiates a discovery process.

#### `transmitCoordinator(len, payload)`
Transmits data to the coordinator.

- len: Length of the payload.
- payload: The data to be transmitted.

Example: 
    AtCmds atCmds;
    char data[] = "Hello, Xbee3!";
    atCmds.transmitCoordinator(strlen(data), data);

Contributing
Feel free to contribute to this library by submitting bug reports, feature requests, or code enhancements. Please follow the standard GitHub workflow for contributing to open-source projects.
