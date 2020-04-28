/**********************************************************
   Title : OLED DIGITAL CLOCK using RTC, GPS
   Date : 2018.03.16.
   Author : Park Yongjoon
 **********************************************************/
#define KEAD 1 //1이면 고도표시(GPS), 0이면 KEAD표시(WIFI)
#define SYNKDISPLAYTIME 3  //GPS일경우 3초, WIFI일경우 3600초 

#include <Arduino.h>
#include <DS1307RTC.h>
#include <TimeLib.h>
#include <Wire.h>
#include <TinyGPS++.h>
#include "ws0010.h"
#include "Font.h"

#define PosHH 99
#define PosMM 72
#define PosYMD 49
#define PosSS 49
#define PosALT 35
#define PosWeek 10

const int rs = 4, rw = 7, en = 8, d4 = A3, d5 = A0, d6 = 3, d7 = 11;
WS0010 lcd(rs, rw, en, d4, d5, d6, d7);

tmElements_t tm, gm;
time_t rtcTime, gpsTime, buttonTime, pGpsTime = 0;
TinyGPSPlus gps;
long alt;
boolean wifiset = false, beepenable = false;
boolean gpsLock = false, gpsAltValid = false;

void setup()
{
  delay(500);
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  lcd.begin(16, 2);
  lcd.graphicMode();

  for (int j = 0; j < 8; j++) {
    lcd.command(0x80 + 99);
    lcd.command(0x40);
    for (int i = 0; i < 100; i++) {
      lcd.write((1 << (j + 1)) - 1);
    }
    delay(100);
  }
  for (int j = 0; j < 8; j++) {
    lcd.command(0x80 + 99);
    lcd.command(0x41);
    for (int i = 0; i < 100; i++) {
      lcd.write((1 << (j + 1)) - 1);
    }
    delay(100);
  }
  for (int j = 0; j < 8; j++) {
    lcd.command(0x80 + 99);
    lcd.command(0x40);
    for (int i = 0; i < 100; i++) {
      lcd.write((0xff << (j + 1)));
    }
    delay(100);
  }
  for (int j = 0; j < 8; j++) {
    lcd.command(0x80 + 99);
    lcd.command(0x41);
    for (int i = 0; i < 100; i++) {
      lcd.write((0xff << (j + 1)));
    }
    delay(100);
  }
  RTC.read(tm);
  buttonTime = makeTime(tm);
  if (tm.Year < 48) RTC.set(1524787200); //2018년 이전이면 2018.04.27.00:00으로 셋
}

void loop() {
  if (gpsLock && (gpsTime - pGpsTime > 1)) {
    rtcTime = gpsTime;
    pGpsTime = gpsTime;
    RTC.set(gpsTime);
    gpsLock = false;
  }
  else {
    rtcTime = RTC.get();
  }
  breakTime(rtcTime, tm);

  while (Serial.available()) {
    char c;
    c = Serial.read();
    //Serial.write(c);

    if (gps.encode(c)) {
      if (gps.time.isValid()) {
        gm.Year = CalendarYrToTm(gps.date.year());
        gm.Month = gps.date.month();
        gm.Day = gps.date.day();
        gm.Hour = gps.time.hour();
        gm.Minute = gps.time.minute();
        gm.Second = gps.time.second();
        if (gps.time.hour() == 88) {
          wifiset = true;
        }
        else {
          if ((gm.Hour != 0) || (gm.Minute != 0) || (gm.Second != 0)) { //9:00로 초기화 되는 현상 막기 위함
            gpsLock = true;
            wifiset = false;
            gpsTime = makeTime(gm) + 9 * 60 * 60;
          }
        }
      }
      gpsAltValid = gps.altitude.isValid();
      if (gpsAltValid) {
        alt = gps.altitude.meters();
      }
    }
  }

  flash();
  if (rtcTime % 3600 == 0) {
    if (beepenable) {
      digitalWrite(2, LOW);
      delay(20);
      beepenable = false;
    }
    digitalWrite(2, HIGH);
  }
  else {
    if ((tm.Hour >= 6) && (tm.Hour <= 22))  beepenable = true;
  }
}

