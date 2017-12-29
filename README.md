# STK500 Repository!
---

[![Version: 1.0 Release](https://img.shields.io/badge/Version-1.0%20Release-green.svg)](https://github.com/sunriax) [![Build Status](https://travis-ci.org/sunriax/STK500.svg?branch=master)](https://travis-ci.org/sunriax/STK500) [![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0) [![Slack: Join](https://img.shields.io/badge/Slack-Join-blue.svg)](https://join.slack.com/t/sunriax-technology/shared_invite/enQtMjg3OTE2MjIyMTE2LTU1MmEwNmY5Y2Y3MTNjNzFhYzE5NTFkYWY4NzE0YmQzNzA5NjBkMWQ3ODkyNDI1NjJmMGIwYzMwOGI5ZjA2MDg)

## Description
---
The STK500 repository is a set of librarys used in the [module](https://github.com/sunriax/module) repository for communication with different microchips. It tries to abstract the hardware from the software layer. Our aim is to abstract the hardware from the software so that the platform can be changed (e.g. from ATmega to Microchip) without changing the module librarys. The STK500 library supports (@ the moment) only a few kind of microcontrollers but it will be extended in the future.

1. Supported Controller
   * Atmel ATmega8
   * Atmel ATmega16
   * Atmel ATmega32
1. Development Hardware
   * STK500 (Atmel)
   * Megacard (HTL-Rankweil)
1. Additionak Hardware
   * LCD Module ([HD44780](https://www.pollin.de/productdownloads/D120622D.PDF))
1. Development Software
   * Atmel Studio (uC C/C++)

## Abstraction
---
![Grapical Description](https://raw.githubusercontent.com/sunriax/manual/master/docs/image/STK500_abstraction.png "Graphical Description")

## Getting Started
---
Every project has a demo application as sidecar (e.g. uart has uartDEMO). This demos can be used as quickstart guide. We also try to keep our [WIKI](https://wiki.sunriax.at) up-to-date. Also we provide a small introduction i the [WIKI](https://github.com/sunriax/STK500/wiki) of the Github repository.

## Important Notice
---
This files are valid for all repositories at the SUNriaX Github!
* [Readme](https://github.com/sunriax/manual/blob/master/README.md)
* [License](https://github.com/sunriax/manual/blob/master/license.md)
* [Warranty](https://github.com/sunriax/manual/blob/master/warranty.md)

## Additional Information
---
You can find more additional information in the [manual](https://github.com/sunriax/manual/tree/master/docs) repository and/or visit the [SUNriaX Project Wikipedia](https://wiki.sunriax.at/) for further information (currently under construction)

If there are any further questions feel free to start an issue or contact us, we try to react as quick as possible.

**R. GÄCHTER, Rankweil Dec/2017**