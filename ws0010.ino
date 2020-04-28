#include "ws0010.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Arduino.h"


// On power up, the display is initilaized as:
// 1. Display clear
// 2. Function set:
//    DL="1": 8-bit interface data
//    N="0": 1-line display
//    F="0": 5 x 8 dot character font
// 3. Power turn off
//    PWR=”0”
// 4. Display on/off control: D="0": Display off C="0": Cursor off B="0": Blinking off
// 5. Entry mode set
//    I/D="1": Increment by 1
//    S="0": No shift
// 6. Cursor/Display shift/Mode / Pwr
//    S/C=”0”, R/L=”1”: Shifts cursor position to the right
//    G/C=”0”: Character mode
//    Pwr=”1”: Internal DCDC power on
//
// Note, however, that resetting the Arduino doesn't reset the LCD, so we
// can't assume that its in that state when a sketch starts (and the
// WS0010 constructor is called).

WS0010::WS0010(uint8_t rs, uint8_t rw, uint8_t enable,
               uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
{
  init(rs, rw, enable, d4, d5, d6, d7);
}

void WS0010::init(uint8_t rs, uint8_t rw, uint8_t enable,
                  uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
{
  _rs_pin = rs;
  _rw_pin = rw;
  _enable_pin = enable;

  _data_pins[0] = d4;
  _data_pins[1] = d5;
  _data_pins[2] = d6;
  _data_pins[3] = _busy_pin = d7;

  pinMode(_rs_pin, OUTPUT);
  pinMode(_rw_pin, OUTPUT);
  pinMode(_enable_pin, OUTPUT);

  _displayfunction = LCD_FUNCTIONSET | LCD_4BITMODE;

  begin(16, 2);
}

void WS0010::begin(uint8_t cols, uint8_t lines)
{
  _numlines = lines;
  _currline = 0;

  pinMode(_rs_pin, OUTPUT);
  pinMode(_rw_pin, OUTPUT);
  pinMode(_enable_pin, OUTPUT);

  digitalWrite(_rs_pin, LOW);
  digitalWrite(_enable_pin, LOW);
  digitalWrite(_rw_pin, LOW);

  delayMicroseconds(16300); // give it some time to power up

  // Now we pull both RS and R/W low to begin commands

  for (int i = 0; i < 4; i++) {
    pinMode(_data_pins[i], OUTPUT);
    digitalWrite(_data_pins[i], LOW);
  }

  // Initialization sequence is not quite as documented by Winstar.
  // Documented sequence only works on initial power-up.
  // An additional step of putting back into 8-bit mode first is
  // required to handle a warm-restart.
  //
  // In the data sheet, the timing specs are all zeros(!).  These have been tested to
  // reliably handle both warm & cold starts.

  // 4-Bit initialization sequence from Technobly
  //write4bits(0x03); // Put back into 8-bit mode
  delayMicroseconds(16300);
  //write4bits(0x03); // Put back into 8-bit mode
  delayMicroseconds(16300);
  //waitForReady();
  //delay(500);
  write4bits(0);
  write4bits(0);
  write4bits(0);
  write4bits(0);
  write4bits(0);
  
  
  write4bits(0x02); // Put into 4-bit mode
  //waitForReady();
  write4bits(0x02);
  //waitForReady();
  write4bits(0x08);
  waitForReady();
  command(0x08);  // Turn Off
  command(0x01);  // Clear Display
  command(0x02); //Return home
  command(0x06);  // Set Entry Mode
  //command(0x1f);  //Graph mode
}

/********** high level commands, for the user! */
void WS0010::clear()
{
  command(LCD_CLEARDISPLAY);  // clear display, set cursor position to zero
}

void WS0010::home()
{
  command(LCD_RETURNHOME);  // set cursor position to zero
}

void WS0010::reset()
{
  command(0x00);
  command(0x01); //1.Display clear
  command(0x30); //2. Function set
  command(0x13); //3. Power turn off
  command(0x08); //4. Display off
  command(0x06); //5. Entry mode set
  command(0x14); //6. Cursor/Display shift/Mode
  command(0x17); //Pwrr
}

void WS0010::setCursor(uint8_t col, uint8_t row)
{
  uint8_t row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
  if ( row >= _numlines )
  {
    row = 0;  //write to first line if out off bounds
  }
  command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

// Turn the display on/off (quickly)
void WS0010::noDisplay() {
  _displaycontrol &= ~LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void WS0010::display() {
  _displaycontrol |= LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off
void WS0010::noCursor() {
  _displaycontrol &= ~LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void WS0010::cursor() {
  _displaycontrol |= LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turn on and off the blinking cursor
void WS0010::noBlink() {
  _displaycontrol &= ~LCD_BLINKON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void WS0010::blink() {
  _displaycontrol |= LCD_BLINKON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM
void WS0010::scrollDisplayLeft(void) {
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
void WS0010::scrollDisplayRight(void) {
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void WS0010::leftToRight(void) {
  _displaymode |= LCD_ENTRYLEFT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
void WS0010::rightToLeft(void) {
  _displaymode &= ~LCD_ENTRYLEFT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'right justify' text from the cursor
void WS0010::autoscroll(void) {
  _displaymode |= LCD_ENTRYSHIFTINCREMENT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor
void WS0010::noAutoscroll(void) {
  _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void WS0010::createChar(uint8_t location, uint8_t charmap[]) {
  location &= 0x7; // we only have 8 locations 0-7
  command(LCD_SETCGRAMADDR | (location << 3));
  for (int i = 0; i < 8; i++) {
    write(charmap[i]);
  }
}

void WS0010::graphicMode() {
  command(0x1b);  //Gr mode and power off
  command(0x01);
  command(0x02);
  command(0x05); // entry mode
  command(0x0C); //display on
  command(0x14); //cursor/ display shift
  command(0x1F); //gr mode and power on
  command(0x01); //clear
  command(0x02);  //home
}

/*********** mid level commands, for sending data/cmds */

inline void WS0010::command(uint8_t value) {
  send(value, LOW);
  waitForReady();
}

inline size_t WS0010::write(uint8_t value) {
  send(value, HIGH);
  waitForReady();
}

/************ low level data pushing commands **********/
uint8_t WS0010::receive(uint8_t mode) {
  uint8_t value;
  digitalWrite(_rs_pin, mode);
  digitalWrite(_rw_pin, HIGH);
  value = (read4bits() << 4) | read4bits();
  return value;
}


// write either command or data, with automatic 4/8-bit selection
void WS0010::send(uint8_t value, uint8_t mode) {
  digitalWrite(_rs_pin, mode);
  pinMode(_rw_pin, OUTPUT);
  digitalWrite(_rw_pin, LOW);

  write4bits(value >> 4);
  write4bits(value);
}

void WS0010::pulseEnable(void) {
  digitalWrite(_enable_pin, HIGH);
  delayMicroseconds(10);  // Timing Spec?
  digitalWrite(_enable_pin, LOW);
}

uint8_t WS0010::read4bits() {
  uint8_t value = 0;
  for (int i = 0; i < 4; i++) {
    pinMode(_data_pins[i], INPUT);
  }
  for (int i = 0; i < 4; i++) {
    value |= digitalRead(_data_pins[i] << i);
  }
  for (int i = 0; i < 4; i++) {
    pinMode(_data_pins[i], OUTPUT);
  }
  pulseEnable();
  return value;
}

void WS0010::write4bits(uint8_t value) {
  for (int i = 0; i < 4; i++)
  {
    pinMode(_data_pins[i], OUTPUT);
    digitalWrite(_data_pins[i], (value >> i) & 0x01);
  }
  pulseEnable();
}


// Poll the busy bit until it goes LOW
void WS0010::waitForReady(void)
{
  unsigned char busy = 1;
  pinMode(_busy_pin, INPUT);
  digitalWrite(_rs_pin, LOW);
  digitalWrite(_rw_pin, HIGH);
  do
  {
    digitalWrite(_enable_pin, LOW);
    digitalWrite(_enable_pin, HIGH);

    delayMicroseconds(10);
    busy = digitalRead(_busy_pin);
    digitalWrite(_enable_pin, LOW);
    pulseEnable();    // get remaining 4 bits, which are not used.
  }
  while (busy);
  pinMode(_busy_pin, OUTPUT);
  digitalWrite(_rw_pin, LOW);
}

