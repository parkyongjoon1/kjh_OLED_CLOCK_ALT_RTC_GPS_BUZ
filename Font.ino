void num10x16(uint8_t x, uint8_t n) {
  lcd.command(0x80 | x);
  lcd.command(0x40);
  for (uint8_t i = 0; i < 10; i++)
    lcd.write(Font10x16[n][i] & 0xFF);
  lcd.command(0x80 | x);
  lcd.command(0x41);
  for (uint8_t i = 0; i < 10; i++)
    lcd.write(Font10x16[n][i] >> 8 & 0xFF);
}

void week11x16(uint8_t x, uint8_t n) {
  lcd.command(0x80 | x);
  lcd.command(0x40);
  for (uint8_t i = 0; i < 11; i++)
    lcd.write(Font11x16_week[n][i] & 0xFF);
  lcd.command(0x80 | x);
  lcd.command(0x41);
  for (uint8_t i = 0; i < 11; i++)
    lcd.write(Font11x16_week[n][i] >> 8 & 0xFF);
}

void num3x5(uint8_t x, uint8_t y, uint8_t n) {
  lcd.command(0x80 | x);
  lcd.command(0x40 | y);
  for (int i = 0; i < 3; i++)
    lcd.write(Font3x5[n][i]);
}

void delFont16n(uint8_t x, uint8_t n) {
  lcd.command(0x80 | x);
  lcd.command(0x40);
  for (uint8_t i = 0; i < n; i++) lcd.write(0);
  lcd.command(0x80 | x);
  lcd.command(0x41);
  for (uint8_t i = 0; i < n; i++) lcd.write(0);
}

void delFont8n(uint8_t x, uint8_t y, uint8_t n) {
  lcd.command(0x80 | x);
  lcd.command(0x40 | y);
  for (uint8_t i = 0; i < n; i++) lcd.write(0);
}

void putFont16n(uint8_t x, uint16_t *font, uint8_t n) {
  lcd.command(0x80 | x);
  lcd.command(0x40);
  for (uint8_t i = 0; i < n; i++) lcd.write(*(font + i) & 0xff);
  lcd.command(0x80 | x);
  lcd.command(0x41);
  for (uint8_t i = 0; i < n; i++) lcd.write(*(font + i) >> 8 & 0xff);
}

void putFont8n(uint8_t x, uint8_t y, uint8_t *font, uint8_t n) {
  lcd.command(0x80 | x);
  lcd.command(0x40 | y);
  for (uint8_t i = 0; i < n; i++) lcd.write(*(font + i));
}

void putVol16(uint8_t x, uint8_t vol) {
  lcd.command(0x80 | x);
  lcd.command(0x40);
  for (uint8_t i = 0; i < 16; i++) {
    if (i <= vol) lcd.write((1 << i) - 1 );
    else lcd.write(0);
  }
  lcd.command(0x80 | x);
  lcd.command(0x41);
  for (uint8_t i = 0; i < 16; i++) {
    if (i <= vol) lcd.write(((1 << i) - 1) >> 8 );
    else lcd.write(0);
  }
}

