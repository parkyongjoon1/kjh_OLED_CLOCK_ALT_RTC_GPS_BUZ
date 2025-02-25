const uint16_t Font10x16[10][10] = {
  {0x3ffc, 0x7ffe, 0xe007, 0xc003, 0xc003, 0xc003, 0xc003, 0xe007, 0x7ffe, 0x3ffc}, //0
  {0x0000, 0x0000, 0x0000, 0x2000, 0x6000, 0xffff, 0xffff, 0x0000, 0x0000, 0x0000}, //1
  {0x3007, 0x600f, 0xc01f, 0xc03b, 0xc073, 0xc0e3, 0xc1c3, 0xe383, 0x7f03, 0x3e03}, //2
  {0x300c, 0x700e, 0xe007, 0xc003, 0xc183, 0xc183, 0xc3c3, 0xe7e7, 0x7e7e, 0x3c3c}, //3
  {0x03c0, 0x07c0, 0x0ec0, 0x1cc0, 0x38c0, 0x70c0, 0xffff, 0xffff, 0x00c0, 0x00c0}, //4
  {0xff0c, 0xff0e, 0xc307, 0xc303, 0xc303, 0xc303, 0xc303, 0xc387, 0xc1fe, 0xc0fc}, //5
  {0x0ffc, 0x1ffe, 0x3987, 0x7183, 0xe183, 0xc183, 0xc183, 0xc1c7, 0x40fe, 0x007c}, //6
  {0xf000, 0xf000, 0xc000, 0xc000, 0xc07f, 0xc0ff, 0xc180, 0xc300, 0xfe00, 0xfc00}, //7
  {0x3c3c, 0x7e7e, 0xe7e7, 0xc3c3, 0xc183, 0xc183, 0xc3c3, 0xe7e7, 0x7e7e, 0x3c3c}, //8
  {0x3e00, 0x7f00, 0xe380, 0xc181, 0xc183, 0xc187, 0xc18e, 0xe19c, 0x7ff8, 0x3ff0}, //9
};

const uint16_t Font11x16_week[7][11] = {
  {0x0000, 0x0000, 0x7FC0, 0x4440, 0x4440, 0x4440, 0x4440, 0x4440, 0x7FC0, 0x0000, 0x0000},  //��
  {0x0000, 0x0020, 0x0040, 0xFF80, 0x9200, 0x9200, 0x9200, 0x9200, 0x9220, 0xFFE0, 0x0000},  //��
  {0x0820, 0x3040, 0x0080, 0x0100, 0x0600, 0xF800, 0x0600, 0x0100, 0x0880, 0x3040, 0x0020},  //��
  {0x1040, 0x1080, 0x1300, 0x1C00, 0x0020, 0xFFE0, 0x3000, 0x0C00, 0x0B00, 0x1080, 0x2040},  //�
  {0x1040, 0x1080, 0x1100, 0x1200, 0x1400, 0xFFE0, 0x1400, 0x1200, 0x1100, 0x1080, 0x1040},  //��
  {0x1020, 0x1220, 0x2AA0, 0x2A60, 0x4A20, 0x8FE0, 0x4A20, 0x2A60, 0x2AA0, 0x1220, 0x1020},  //��
  {0x0020, 0x0820, 0x0820, 0x0820, 0x0820, 0xFFE0, 0x0820, 0x0820, 0x0820, 0x0820, 0x0020},  //��
};


const uint8_t Font3x5[10][3] = {
  {0x1f, 0x11, 0x1f}, //0
  {0x09, 0x1f, 0x01}, //1
  {0x17, 0x15, 0x1d}, //2
  {0x15, 0x15, 0x1f}, //3
  {0x1c, 0x04, 0x1f}, //4
  {0x1d, 0x15, 0x17}, //5
  {0x1f, 0x05, 0x07}, //6
  {0x10, 0x10, 0x1f}, //7
  {0x1f, 0x15, 0x1f}, //8
  {0x1c, 0x14, 0x1f}, //9
};

const uint16_t Font16_AmPm[4][10] = {
  {0x0000, 0x0000, 0x0000, 0x0000, 0x3E00, 0x2800, 0x3E00, 0x0000, 0x0000, 0x0000}, //am0
  {0x3E00, 0x2800, 0x3E00, 0x0000, 0x0000, 0x2000, 0x6000, 0xffff, 0xffff, 0x0000}, //am1
  {0x0000, 0x0000, 0x0000, 0x0000, 0x003E, 0x0028, 0x0038, 0x0000, 0x0000, 0x0000}, //pm0
  {0x003E, 0x0028, 0x0038, 0x0000, 0x0000, 0x2000, 0x6000, 0xffff, 0xffff, 0x0000}, //pm1
};
const uint16_t Font2x16_colon[2]  = {0x0C30, 0x0C30};
const uint16_t Font2x16_dot[2] = {0x0003, 0x0003};
const uint8_t Font1x5_dot = 0x01;
const uint8_t Font5x5_m[5] = {3, 4, 3, 4, 3};
const uint8_t Font5x19_kead[19] = {0x1F,0x04,0x0A,0x11,0x00,0x1F,0x15,0x15,0x11,0x00,0x0F,0x14,0x14,0x0F,0x00,0x1F,0x11,0x11,0x0E};
