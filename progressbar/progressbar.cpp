/*!
 * @file progressbar.h
 *
 * ---------------------------------------------------------------
 * Name: progressbar.h
 * Discription: Library for nice LCD Dispaly progressbars
 * Version: 1.0
 * Author: black-backdoor
 *
 * Github: https://github.com/black-backdoor
 * ---------------------------------------------------------------
 *
 * This is a library for beautiful I2C LCD Displays
 *
 * These displays use I2C to communicate, 2 pins are required to
 * interface
 *
 * black-backdoor invests time and resources providing this open source code,
 * respect this and don't give this code out as our own
 * and pleas reporte any bug you find.
 *
 * Written by black-backdoor.
 * MIT license, all text above must be included in any redistribution
 *
 *
 * Fork of https://www.carnetdumaker.net/articles/faire-une-barre-de-progression-avec-arduino-et-liquidcrystal/
 *
 * ------------------------ Progressbar ------------------------
 * Download: https://www.carnetdumaker.net/snippets/4/
 * Best Explanation https://www.carnetdumaker.net/articles/faire-une-barre-de-progression-avec-arduino-et-liquidcrystal/
 * Short Explanation https://www.carnetdumaker.net/articles/faire-une-barre-de-progression-avec-arduino-et-liquidcrystal/#barre-de-progression-v3
 *
 */


#include "Arduino.h"
#include "progressbar.h"


//------------------------ progress bar animation characters ------------------------
byte START_DIV_0_OF_4[8] = {B01111,B11000,B10000,B10000,B10000,B10000,B11000,B01111}; 
byte START_DIV_1_OF_4[8] = {B01111,B11000,B10000,B10000,B10000,B10011,B11000,B01111};
byte START_DIV_2_OF_4[8] = {B01111,B11000,B10000,B10000,B10111,B10011,B11000,B01111};
byte START_DIV_3_OF_4[8] = {B01111,B11000,B10000,B10111,B10111,B10011,B11000,B01111};
byte START_DIV_4_OF_4[8] = {B01111,B11000,B10011,B10111,B10111,B10011,B11000,B01111};
byte DIV_0_OF_8[8] = {B11111,B00000,B00000,B00000,B00000,B00000,B00000,B11111};
byte DIV_1_OF_8[8] = {B11111,B00000,B00000,B00000,B00000,B11000,B00000,B11111}; 
byte DIV_2_OF_8[8] = {B11111,B00000,B00000,B00000,B11000,B11000,B00000,B11111};
byte DIV_3_OF_8[8] = {B11111,B00000,B00000,B11000,B11000,B11000,B00000,B11111};
byte DIV_4_OF_8[8] = {B11111,B00000,B11000,B11000,B11000,B11000,B00000,B11111};
byte DIV_5_OF_8[8] = {B11111,B00000,B11000,B11000,B11000,B11011,B00000,B11111};
byte DIV_6_OF_8[8] = {B11111,B00000,B11000,B11000,B11011,B11011,B00000,B11111};
byte DIV_7_OF_8[8] = {B11111,B00000,B11000,B11011,B11011,B11011,B00000,B11111};
byte DIV_8_OF_8[8] = {B11111,B00000,B11011,B11011,B11011,B11011,B00000,B11111};
byte END_DIV_0_OF_4[8] = {B11110,B00011,B00001,B00001,B00001,B00001,B00011,B11110};
byte END_DIV_1_OF_4[8] = {B11110,B00011,B00001,B00001,B00001,B11001,B00011,B11110};
byte END_DIV_2_OF_4[8] = {B11110,B00011,B00001,B00001,B11101,B11001,B00011,B11110};
byte END_DIV_3_OF_4[8] = {B11110,B00011,B00001,B11101,B11101,B11001,B00011,B11110};
byte END_DIV_4_OF_4[8] = {B11110,B00011,B11001,B11101,B11101,B11001,B00011,B11110};



void progressbar::start_progressbar() {
  lcd.createChar(0, START_DIV_4_OF_4);
  lcd.createChar(1, DIV_0_OF_8);
  lcd.createChar(2, DIV_8_OF_8);
  lcd.createChar(3, END_DIV_0_OF_4);
}

void progressbar::print_progressbar(bool text_percent, String text, int delay_ms) { //Main Progressbar funktion
  start_progressbar();
  while (true) {
    static byte percent = 0;
    draw_progressbar(text_percent, percent, text, lcd_rows - 2, lcd_rows - 1);
    if (++percent == 101) {
      percent = 0;
      break;
    }
    delay(delay_ms);
  }
}

void progressbar::switch_progressbar_bank(byte bank) { //Progressbar Symbol Bank
  switch (bank) {
    case 0:
      lcd.createChar(4, START_DIV_0_OF_4);
      lcd.createChar(5, START_DIV_1_OF_4);
      lcd.createChar(6, START_DIV_2_OF_4);
      lcd.createChar(7, START_DIV_3_OF_4);
      break;

    case 1:
      lcd.createChar(4, DIV_1_OF_8);
      lcd.createChar(5, DIV_2_OF_8);
      lcd.createChar(6, DIV_3_OF_8);
      lcd.createChar(7, DIV_4_OF_8);
      break;

    case 2:
      lcd.createChar(4, DIV_4_OF_8);
      lcd.createChar(5, DIV_5_OF_8);
      lcd.createChar(6, DIV_6_OF_8);
      lcd.createChar(7, DIV_7_OF_8);
      break;

    case 3:
      lcd.createChar(4, END_DIV_1_OF_4);
      lcd.createChar(5, END_DIV_2_OF_4);
      lcd.createChar(6, END_DIV_3_OF_4);
      lcd.createChar(7, END_DIV_4_OF_4);
      break;
  }
}

void progressbar::draw_progressbar(bool show_text_percent, byte percent, String text, int position_text, int position_bar) { // draw Progressbar
  if(show_text_percent){
    if (text != "") {
      lcd.setCursor(0, position_text);
      lcd.print(text);
      lcd.setCursor(lcd_colums - 4, position_text);
      lcd.print(percent);
      lcd.print(F("%"));
    }
    else {
      lcd.setCursor(0, position_text);
      lcd.print(percent);
      lcd.print("%");
    }
  }
  lcd.setCursor(0, position_bar);
  byte nb_columns = map(percent, 0, 100, 0, lcd_colums * 2 * 4 - 2 * 4);
  for (byte i = 0; i < lcd_colums; ++i) {
    if (i == 0) {
      if (nb_columns > 4) {
        lcd.write((byte) 0);
        nb_columns -= 4;
      } else if (nb_columns == 4) {
        lcd.write((byte) 0);
        nb_columns = 0;
      } else {
        switch_progressbar_bank(0);
        lcd.setCursor(i, position_bar);
        lcd.write(nb_columns + 4);
        nb_columns = 0;
      }
    } else if (i == lcd_colums - 1) {
      if (nb_columns > 0) {
        switch_progressbar_bank(3);
        lcd.setCursor(i, position_bar);
        lcd.write(nb_columns + 3);
      } else {
        lcd.write(3);
      }
    } else {
      if (nb_columns == 0) {
        lcd.write(1);
      } else if (nb_columns >= 8) {
        lcd.write(2);
        nb_columns -= 8;
      } else if (nb_columns >= 4 && nb_columns < 8) {
        switch_progressbar_bank(2);
        lcd.setCursor(i, position_bar);
        lcd.write(nb_columns);
        nb_columns = 0;
      } else if (nb_columns < 4) {
        switch_progressbar_bank(1);
        lcd.setCursor(i, position_bar);
        lcd.write(nb_columns + 3);
        nb_columns = 0;
      }
    }
  }
}
