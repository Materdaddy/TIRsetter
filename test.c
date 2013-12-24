#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int i;
	int count = 0;
	uint16_t count2 = 0;

	if ( argc < 3 )
	{
		printf("Need serial as first arg, and address as second\n");
		exit(EXIT_FAILURE);
	}

	int serial = atoi(argv[1]);
	int address = atoi(argv[2]);

	uint8_t data[] = {
	0x37,//0
	0x07,//1
	0x54,//2
	0x49,//3
	0x52,//4
	0x4C,//5
	0x55,//6
	0x4D,//7
	0x56,//8
	0x31,//9
	0x35,//10
	0x00,//11
	0x00,//12
	0x2F,//13
	0x02,//14
	0xBE,//15
	0x00,//16
	0x01,//17
	0x00,//18
	0x00,//19
	0xEC,//20
	0x40,//21
	0x41,//22
	0x00,//23
	0x70,//24
	0x56,//25
	0x01,//26
	0x00,//27
	0x70,//28
	0x72,//29
	0x65,//30
	0x73,//31
	0x65,//32
	0x74,//33
	0x30,//34
	0x30,//35
	0x00,//36
	0x00,//37
	0x00,//38
	0x00,//39
	0x00,//40
	0x00,//41
	0x00,//42
	0x00,//43
	0x00,//44
	0x00,//45
	0x00,//46
	0x00,//47
	0x00,//48
	0x00,//49
	0x00,//50
	0x00,//51
	0x00,//52
	0x00 //53
	};

	// Set our address bytes
	data[13] = (serial & 0x00FF0000)>>16;
	data[14] = (serial & 0x0000FF00)>>8;
	data[15] = (serial & 0x000000FF);

	// Set the value our sample set uses
	data[18] = 0x18;

	//		Checksum code from PIC spreadsheet:
	//
	//		e3=3080852	serial number
	//		e4=33		dmx address
	//		e72=3080000	base serial number
	//		e73=1		base dmx address
	//		e74=0x46	base checksum 1
	//		e75=0xCA	base checksum 2
	//		
	//		dec2hex(mod((mod(mod((e3-e72)+(e4-e73),256)+hex2dec(e74),256))+(if((e3-e72)>191,if((e3-e72-192)>255,quotient((e3-e72-192),256)*1+2,2),0)+if((e4-e73)>=255,1,0)),256),2)
	//		dec2hex(mod((mod(mod((e3-e72)+(e4-e73),256)*2+hex2dec(e75),256)+(if((e3-e72)>191,if((e3-e72-192)>255,(quotient((e3-e72-192),256)*1+2),2),0)+if((e4-e73)>=255,1,0))*2),256),2)

	data[52] = (((((((serial-3080000)+(address-1))%256) +0x46)%256))+((((serial-3080000)>191)?(((serial-3080000-192)>255)?((serial-3080000-192)/256)*1+2:2):0)+((address-1)>=255?1:0))%256);
	data[53] = (((((((serial-3080000)+(address-1))%256) *2+0xCA)%256)+((((serial-3080000)>191)?(((serial-3080000-192)>255)?(((serial-3080000-192)/256)*1+2):2):0)+(((address-1)>=255)?1:0))*2)%256);

	// Print our results
	for ( i = 0; i < 54; i++ )
	{
		printf("%02x|", data[i]);
	}
	printf("\n");

	return 0;
}
