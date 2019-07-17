/* PCX_IO.h header file   
-----------------------------------------------------------------------  
 
  Read and Write image files in PCX format  
  
 Written by Alex N. Kotlikov (St.Petersburg, Russia)  
 FIDOnet 2:5030/691.10  
 Feb 1999   
  
-----------------------------------------------------------------------  
*/  
// #define __SUN__
  
#ifndef	__PCX_HEADER__  
#define __PCX_HEADER__  
  
typedef	struct	_PCXHeader  {  
  
    unsigned char      ZsoftSign;      /* Always = 10 for PaintBrush        */  
    unsigned char      Version;        /* Info about version                */  
    unsigned char      GroupCoding;    /* Group coding ( = 1 )              */  
    unsigned char      BitPerPixel;    /* Bit per pixel                     */  
    unsigned short int X1;		       /* Image size ( includ. )            */  
    unsigned short int Y1;  
    unsigned short int X2;  
    unsigned short int Y2;  
    unsigned short int HResolution;    /* Horisontal display resolution     */  
    unsigned short int VResolution;    /* Vertical display resolution       */  
    unsigned char      EGAPalette[48]; /* Palette                           */  
    unsigned char      VideoMode;      /* Ignoring                          */  
    unsigned char      PlanesNumber;   /* Planes number ( ver.2.5 = 0 )     */	  
    unsigned short int BytePerLine;    /* Byte per line                     */  
    unsigned short int PaletteInfo;    /* Palette info (2 = gray,1 = color) */  
    unsigned short int SHResolution;   /* Scanner horisontal resolution     */  
    unsigned short int SVResolution;   /* Scanner vertical resolution       */  
    unsigned char      Reserve[54];    /* Reserved                          */  
  
} PCXHeader;  
  
#endif /* __PCX_HEADER__ */  
  
#ifndef __PCX_IO_H__  
#define __PCX_IO_H__  
  
int            WritePCX ( unsigned char *Image, int XSize, int YSize, char* Name );  
unsigned char* ReadPCX  ( char* Name, int *XSize, int *YSize );  
int	   ReadTrueColorPCX  ( char* Name, int *XSize, int *YSize,  
                               unsigned char** RImage,
                               unsigned char** GImage,  
                               unsigned char** BImage  );  
int       WriteTrueColorPCX  ( char* Name, int XSize, int YSize,  
			       unsigned char* RImage,  
			       unsigned char* GImage,  
			       unsigned char* BImage  );

unsigned char* ReadPCX24_( char* Name, int* XSize, int* YSize );
 
#endif /* __PCX_IO_H__ */
