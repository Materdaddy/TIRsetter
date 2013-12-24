// DMX code from: http://arduino.cc/playground/Learning/DMXSerial

//------------------------------------
// START EDITING YOUR SETTINGS HERE!!!
//------------------------------------
#define SERIAL_NUMBER    3080852
#define NEW_DMX_ADDRESS  33
//------------------------------------
//      STOP EDITING HERE!!!
//------------------------------------

void DMXflush(uint8_t *buffer, uint16_t buf_size)
{
  // send the break by sending a slow 0 byte
  Serial.begin(125000);
  Serial.write((uint8_t)0);

  // now back to DMX speed: 250000baud
  Serial.begin(250000);
  // write all the values from the array
  Serial.write(buffer, buf_size);
}

void setup()
{
  uint8_t DMXBuffer[54] = {

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
    0x00,
    //54 CRC 1 Byte Checksum
    0x00
  };

  //  Checksum code from PIC spreadsheet:
  //
  //      e3=3080852      serial number
  //      e4=33           dmx address
  //      e72=3080000     base serial number
  //      e73=1           base dmx address
  //      e74=0x46        base checksum 1
  //      e75=0xCA        base checksum 2
  //
  //  dec2hex(mod((mod(mod((e3-e72)+(e4-e73),256)+hex2dec(e74),256))+(if((e3-e72)>191,if((e3-e72-192)>255,quotient((e3-e72-192),256)*1+2,2),0)+if((e4-e73)>=255,1,0)),256),2)
  //  dec2hex(mod((mod(mod((e3-e72)+(e4-e73),256)*2+hex2dec(e75),256)+(if((e3-e72)>191,if((e3-e72-192)>255,(quotient((e3-e72-192),256)*1+2),2),0)+if((e4-e73)>=255,1,0))*2),256),2)

  DMXBuffer[52] = (((((((SERIAL_NUMBER-3080000)+(NEW_DMX_ADDRESS-1))%256) +0x46)%256))+((((SERIAL_NUMBER-3080000)>191)?(((SERIAL_NUMBER-3080000-192)>255)?((SERIAL_NUMBER-3080000-192)/256)*1+2:2):0)+((NEW_DMX_ADDRESS-1)>=255?1:0))%256);
  DMXBuffer[53] = (((((((SERIAL_NUMBER-3080000)+(NEW_DMX_ADDRESS-1))%256) *2+0xCA)%256)+((((SERIAL_NUMBER-3080000)>191)?(((SERIAL_NUMBER-3080000-192)>255)?(((SERIAL_NUMBER-3080000-192)/256)*1+2):2):0)+(((NEW_DMX_ADDRESS-1)>=255)?1:0))*2)%256);

  Serial.begin(250000);
  UCSR0C = (1<<USBS0)|(3<<UCSZ00);

  delay(2000);
  DMXflush(&DMXBuffer[0], sizeof(DMXBuffer));
  delay(1000);
}

static int chantoggle = 0;
uint8_t chans[513];

void loop()
{
  if ( chantoggle )
    chantoggle = 0;
  else
    chantoggle = 1;

  for ( int i = 1; i < 513; ++i )
  {
    if ( chantoggle )
      chans[i] = 0xFF;
    else
      chans[i] = 0;
  }

  if ( !chantoggle )
    chans[NEW_DMX_ADDRESS] = 0xFF;
  else
    chans[NEW_DMX_ADDRESS] = 0;

  DMXflush(&chans[0], 513);

  delay(3000);
}
