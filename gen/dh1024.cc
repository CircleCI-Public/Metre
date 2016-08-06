#ifndef HEADER_DH_H
#include <openssl/dh.h>
#endif
DH *get_dh1024()
	{
	static unsigned char dh1024_p[]={
		0x9C,0xDE,0x51,0xE6,0xED,0x1B,0x8D,0x2F,0x05,0x33,0x35,0x87,
		0x7A,0x46,0x6A,0xE5,0x05,0x45,0xF8,0x21,0xA6,0xE6,0xBA,0xEB,
		0xFF,0x70,0x50,0x2E,0x9B,0x1F,0x21,0x2D,0x0B,0x3B,0xF2,0xD7,
		0xBB,0xF0,0x78,0x49,0x5F,0xCD,0x63,0x68,0x96,0x64,0x18,0x2D,
		0xA9,0x3A,0x10,0xD7,0xC9,0x02,0xC2,0x5F,0x55,0x4C,0xF7,0x47,
		0x9D,0x9A,0x8A,0x98,0x8B,0xAD,0x5B,0x1E,0x36,0xE6,0x0E,0x25,
		0x93,0x20,0xCC,0xF5,0xC5,0x7C,0x8E,0x35,0x01,0x5F,0x88,0x9B,
		0xCF,0x8E,0x85,0xDD,0x77,0xB8,0xC7,0xD1,0x64,0xD2,0x7E,0x59,
		0x49,0xA3,0x14,0xF2,0xF5,0x30,0xB7,0x2A,0x32,0xE2,0x9E,0x1C,
		0x1C,0xF3,0xFD,0x6E,0x6E,0xD5,0xBD,0x3D,0xEE,0x6A,0x89,0x85,
		0x28,0x9A,0x48,0x05,0x78,0x1A,0x64,0x53,
		};
	static unsigned char dh1024_g[]={
		0x02,
		};
	DH *dh;

	if ((dh=DH_new()) == NULL) return(NULL);
	dh->p=BN_bin2bn(dh1024_p,sizeof(dh1024_p),NULL);
	dh->g=BN_bin2bn(dh1024_g,sizeof(dh1024_g),NULL);
	if ((dh->p == NULL) || (dh->g == NULL))
		{ DH_free(dh); return(NULL); }
	return(dh);
	}