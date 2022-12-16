/*!
 * @file progressbar.cpp
 *
 * @mainpage progressbar Library
 *
 * @section intro_sec Introduction
 *
 * This is a library for beautiful I2C LCD Displays
 *
 *
 * These displays use I2C to communicate, 2 pins are required to interface
 *
 * black-backdoor invests time and resources providing this open source code,
 * respect this and don't give this code out as our own
 * and pleas reporte any bug you find.
 *
 * @section author Author
 *
 * Written by black-backdoor.
 *
 * @section license License
 *
 * MIT license, all text above must be included in any redistribution
 */

#ifndef Morse_h
#define Morse_h

#include "Arduino.h"

class progressbar
{
  public:
    print_progressbar(bool text_percent, String text, int delay_ms);
    void draw_progressbar();
  private:
    void start_progressbar();
    void switch_progressbar_bank();
};