uint8_t weekday(tmElements_t *t)
/* Calculate day of week in proleptic Gregorian calendar. Sunday == 0. */
{
  uint8_t adjustment, mm, yy;
  adjustment = (14 - t->Month) / 12;
  mm = t->Month + 12 * adjustment - 2;
  yy = tmYearToCalendar(t->Year) - adjustment;
  return ((t->Day) + (13 * mm - 1) / 5 + yy + yy / 4 - yy / 100 + yy / 400 + 1) % 7;
}

void flash()
{
  uint16_t year;
  uint8_t month, day, hour, minute, second, week;
  byte digit10;
  uint8_t pm = 0;  //OLED일때는 boolean하면 안됨.
  boolean syncFlash = false;

  year = tmYearToCalendar(tm.Year);
  month = tm.Month;
  day = tm.Day;
  hour = tm.Hour;
  week = weekday(&tm);
  if (hour >= 12) pm = 2;
  hour = hour % 12;
  if (hour == 0) hour = 12;
  minute = tm.Minute;
  second = tm.Second;
  syncFlash = (second % 2 == 0) && (rtcTime - gpsTime <= SYNKDISPLAYTIME);

  putFont16n(PosHH, &Font16_AmPm[hour / 10 + pm][0], 10);
  delFont16n(PosHH - 10, 1);
  num10x16(PosHH - 11, hour % 10);
  putFont16n(PosMM + 4, Font2x16_colon, 2);
  delFont16n(PosMM + 2, 2);
  num10x16(PosMM, minute / 10);
  delFont16n(PosMM - 10, 1);
  num10x16(PosMM - 11, minute % 10);
  num3x5(PosSS, 0, second / 10);
  num3x5(PosSS - 4, 0, second % 10);
  num3x5(PosYMD, 1, year / 1000 % 10);
  num3x5(PosYMD - 4, 1, year / 100 % 10);
  //num3x5(PosYMD - 4, 1, gm.Second % 10); //For Test
  num3x5(PosYMD - 8, 1, year / 10 % 10);
  num3x5(PosYMD - 12, 1, year % 10);
  putFont8n(PosYMD - 16, 1, &Font1x5_dot, 1);
  num3x5(PosYMD - 18, 1, month / 10 % 10);
  num3x5(PosYMD - 22, 1, month % 10);
  putFont8n(PosYMD - 26, 1, &Font1x5_dot, 1);
  num3x5(PosYMD - 28, 1, day / 10 % 10);
  num3x5(PosYMD - 32, 1, day % 10);
  week11x16(PosWeek, week);
  if (syncFlash) putFont8n(PosSS - 8, 0, &Font1x5_dot, 1);
  else delFont8n(PosSS - 8, 0, 1);
#if KEAD
  if (gpsAltValid) {
    if (alt >= 1000)   num3x5(PosALT, 0, alt / 1000 % 10);
    else delFont8n(PosALT, 0, 4);
    if (alt >= 100) num3x5(PosALT - 4, 0, alt / 100 % 10);
    else delFont8n(PosALT - 4, 0, 4);
    if (alt >= 10) num3x5(PosALT - 8, 0, alt / 10 % 10);
    else delFont8n(PosALT - 8, 0, 4);
    num3x5(PosALT - 12, 0, alt % 10);
    putFont8n(PosALT - 16, 0, Font5x5_m, 5);
  }
  else {
    delFont8n(PosALT, 0, 22);
  }
#else
  if (wifiset && (second % 2 == 0)) {
    delFont8n(PosALT - 2, 0, 19);
  } else {
    putFont8n(PosALT - 2, 0, Font5x19_kead, 19);
  }
#endif
}
