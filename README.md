# STK500 Repository!

[![Version: 1.0 Release](https://img.shields.io/badge/Version-1.0%20Release-green.svg)](https://github.com/sunriax) [![Build Status](https://travis-ci.org/sunriax/STK500.svg?branch=master)](https://travis-ci.org/sunriax/STK500) [![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0) [![Slack: Join](https://img.shields.io/badge/Slack-Join-blue.svg)](https://join.slack.com/t/sunriax-technology/shared_invite/enQtMjg3OTE2MjIyMTE2LTU1MmEwNmY5Y2Y3MTNjNzFhYzE5NTFkYWY4NzE0YmQzNzA5NjBkMWQ3ODkyNDI1NjJmMGIwYzMwOGI5ZjA2MDg)

## Description

The STK500 repository is a set of library's used in the [module](https://github.com/sunriax/module) and other repositories for communication with different microchips and or semiconductors. It has been written to abstract the software from the hardware platform. Our aim is that platform can be changed (e.g. from ATmega to Microchip) without changing the developed software (like a browser). The STK500 library supports (@ the moment) only a few kind of controllers but it will increase in the future.

1. Supported Controller
   * Atmel ATmega8
   * Atmel ATmega16
   * Atmel ATmega32
1. Development Hardware
   * STK500 ([Atmel](http://www.microchip.com/webdoc/stk500/index.html))
   * Megacard ([HTL-Rankweil](http://www.htl-rankweil.at/))
1. Additional Hardware
   * LCD Module ([HD44780](https://www.pollin.de/productdownloads/D120622D.PDF))
1. Development Software
   * Atmel Studio (uC C/C++)

## Abstraction

![Graphical Description](https://raw.githubusercontent.com/sunriax/manual/master/docs/image/STK500_abstraction.png "Graphical Description")

## Getting Started

Every project has a demo application as side car (e.g. uart has uartDEMO). This demo can be used as quick start guide. We also try to keep our [WIKI](https://wiki.sunriax.at) up-to-date. Also there is a short description at the libraries folder:

* [PWM](./pwm/pwm.md)
* [ADC](./adc/adc.md)
* [UART](./uart/uart.md)
* [SPI](./spi/spi.md)
* [TWI](./twi/twi.md)
* [LCD](./lcd/lcd.md)

## Important Notice

This files are valid for all repositories at the SUNriaX Github!
* [Readme](https://github.com/sunriax/manual/blob/master/README.md)
* [License](https://github.com/sunriax/manual/blob/master/license.md)
* [Warranty](https://github.com/sunriax/manual/blob/master/warranty.md)

## Additional Information

You can find more additional information in the [manual](https://github.com/sunriax/manual/tree/master/docs) repository and/or visit the [SUNriaX Project Wikipedia](https://wiki.sunriax.at/) for further information (currently under construction).

If there are any further questions feel free to start an issue or contact us, we try to react as quick as possible.

---
**R. GÄCHTER, Rankweil Dec/2017**