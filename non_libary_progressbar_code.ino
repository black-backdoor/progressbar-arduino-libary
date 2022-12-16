#include <Wire.h> // Wire import Libary
#include <LiquidCrystal_I2C.h> //LCD Display Libary 

//Display Size
const int lcd_rows = 4; //rows starting with one
const int lcd_colums = 20;  //colums starting with one

//LCD Display Init
LiquidCrystal_I2C lcd(0x27, lcd_colums, lcd_rows);   // I2C Adresse: "0x3F" or "0x27"

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


/*
------------------------ Progressbar ------------------------
Download: https://www.carnetdumaker.net/snippets/4/
Best Explanation https://www.carnetdumaker.net/articles/faire-une-barre-de-progression-avec-arduino-et-liquidcrystal/
Short Explanation https://www.carnetdumaker.net/articles/faire-une-barre-de-progression-avec-arduino-et-liquidcrystal/#barre-de-progression-v3
*/
void start_progressbar() {
  lcd.createChar(0, START_DIV_4_OF_4);
  lcd.createChar(1, DIV_0_OF_8);
  lcd.createChar(2, DIV_8_OF_8);
  lcd.createChar(3, END_DIV_0_OF_4);
}

void print_progressbar(bool text_percent, String text, int delay_ms) { //Main Progressbar funktion
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

void switch_progressbar_bank(byte bank) { //Progressbar Symbol Bank
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

void draw_progressbar(bool show_text_percent, byte percent, String text, int position_text, int position_bar) { // draw Progressbar
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




void setup() {
  lcd.init(); //LCD Display init
  lcd.backlight(); //LCD Display activate Backlight
  
  print_progressbar(false, F(""), 300);
}

void loop(){
  
}
