// DMX code from: http://arduino.cc/playground/Learning/DMXSerial

//------------------------------------
// START EDITING YOUR SETTINGS HERE!!!
//------------------------------------
#define SERIAL_NUMBER    3080894
#define NEW_DMX_ADDRESS  17
//------------------------------------
//      STOP EDITING HERE!!!
//------------------------------------


#define DMX_MAX 54
uint8_t DMXBuffer[DMX_MAX] = {

  //1 Non Zero Start Code 37  
  0x37,

  //2 Address change code ? 07
  0x07,

  //3-11 "TIRLUMV15"
  'T', 'I', 'R', 'L', 'U', 'M', 'V', '1', '5',

  //12-13 00
  0x00, 0x00,

  //14-16 Hex Serial Number
  (SERIAL_NUMBER & 0x00FF0000)>>16,
  (SERIAL_NUMBER & 0x0000FF00)>>8,
  (SERIAL_NUMBER & 0x000000FF),

  //17-18 HEX DMX Start Channel
  (NEW_DMX_ADDRESS & 0x0000FF00)>>8,
  (NEW_DMX_ADDRESS & 0x000000FF),

  //19 Seems to vary depending on run
  0x18,//??? XXX TODO

  //20-28 ?? Does not Change 00:ec:40:41:00:70:56:01:00
  0x00, 0xEC, 0x40, 0x41, 0x00, 0x70, 0x56, 0x01, 0x00,

  //29-36 "preset00"
  'p', 'r', 'e', 's', 'e', 't', '0', '0',

  //37-52 00
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

// BYTES 53/54 seeded assuming 0x18 for byte 19, base values of 0x46 and 0xCA based on the post here:
// http://doityourselfchristmas.com/forums/showthread.php?21586-Initializer-Program-for-TIR-Systems-Destiny-CG-Lights-Commercial-LED-Spots&p=220032#post220032
  //53
  (0x46 + ((SERIAL_NUMBER - 3080000)+(NEW_DMX_ADDRESS-1))&0xFF),//???
  //54 CRC 1 Byte Checksum
  (0xCA + (((SERIAL_NUMBER - 3080000)+(NEW_DMX_ADDRESS-1))*2)&0xFF)//???
};

#if 0
void DMXflush()
{
  for ( int i = 0; i < DMX_MAX; ++i )
  {
    Serial.print(DMXBuffer[i], HEX);
    Serial.print(" ");
  }
} // DMXflush

void setup()
{
  Serial.begin(115200);

  delay(4000);
  DMXflush();
}
#else
void DMXflush()
{
  // send the break by sending a slow 0 byte
  Serial.begin(125000);
  Serial.write((uint8_t)0);

  // now back to DMX speed: 250000baud
  Serial.begin(250000);
  // write start code
  Serial.write((uint8_t)0);
  // write all the values from the array
  Serial.write(DMXBuffer, sizeof(DMXBuffer));
} // DMXflush

void setup()
{
  Serial.begin(250000);
  UCSR0C = (1<<USBS0)|(3<<UCSZ00);

  delay(4000);
  DMXflush();
}
#endif

void loop()
{
}
