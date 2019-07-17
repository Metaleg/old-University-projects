/* PCX_IO.c implementation file   
-----------------------------------------------------------------------   
   
 Function Swap     - exchange hi and low bytes in unsigned short int.   
                     Use only for Motorola CPU. For internal use only.   
 Function ReadPCX  - read PCX (Grayscale or 256-colors ) file   
                     into buffer   
 Function WritePCX - write buffer into PCX (256-colors ) file   
   
 Written by Alex N. Kotlikov (St.Petersburg, Russia)   
 FIDOnet 2:5030/691.10   
 Feb 1999    
   
-----------------------------------------------------------------------   
*/   
   
   
   
#include <stdio.h>
#include <stdlib.h>
#include <memory.h> 
#include "PCX_IO.h"   
   
/*   
   
 Function Swap - exchange hi and low bytes in unsigned short int.   
                 Use only for Motorola CPU   
   
*/   
unsigned short int Swap(unsigned short int i)    
{   
#ifdef __SUN__   
  return( (unsigned short int) (i>>8) + (i<<8) );   
#else   
  return (i);   
#endif   
}   
   
/*   
-----------------------------------------------------------------------   
   
    Function ReadPCX - read PCX (Grayscale or 256-colors ) file   
	                   into buffer   
   
    Input:      Name      - file name   
                XS        - horizontal size   
                YS        - vertical size   
   
    Return:     NULL if error occured,   
                or pointer to buffer with image if successfully,    
                in this case memory for image will be allocated.   
   
-----------------------------------------------------------------------   
*/   
unsigned char* ReadPCX( char Name[], int *XSize, int *YSize )   
{   
	FILE* f;   
	unsigned char* lpGrayDIB;   
	long		i, j;
	int		GrayWidth;
   
	PCXHeader	Header;   
    
	long		PackedImageSize;   
	unsigned char*	PackedImage;   
	unsigned char*	PackedBytes;   
	long		PackCount;   
	long		sizeX, sizeY;
	long	        NewSizeX;
 	unsigned char*  Image;  
	double	Gray; 
	unsigned long   IndexOfColor;     
	unsigned char   Palette[768];   

	f = fopen( Name, "rb" );   
	if( f == NULL )   
	{   
		printf("File %s not found.\n", Name);   
		return NULL;   
	}   

   	i = 0;
	fseek( f, 0, SEEK_SET );   
	fread( &Header, sizeof( PCXHeader ), 1, f );   
   
#ifdef __SUN__   
	Header.X1 = Swap( Header.X1 );   
	Header.Y1 = Swap( Header.Y1 );   
	Header.X2 = Swap( Header.X2 );   
	Header.Y2 = Swap( Header.Y2 );   
   
	Header.HResolution = Swap( Header.HResolution );   
	Header.VResolution = Swap( Header.VResolution );   
   
	Header.BytePerLine = Swap( Header.BytePerLine );   
	Header.PaletteInfo = Swap( Header.PaletteInfo );   
   
	Header.SHResolution = Swap( Header.SHResolution );   
	Header.SVResolution = Swap( Header.SVResolution );   
#endif   
   
   
	if ( Header.PlanesNumber != 1 || Header.BitPerPixel != 8 ||    
		 Header.ZsoftSign != 10   || Header.Version != 5 )    
	{   
		fseek( f, 0, SEEK_SET );   
		fclose( f );   
		printf("File %s isn't a Grayscale og 256-inexed color PCX file.\n", Name);   
		return NULL;   
	}   
   
	sizeX = Header.X2 - Header.X1 + 1;   
	sizeY = Header.Y2 - Header.Y1 + 1;   
   
	NewSizeX = sizeX;   
   
	if ( NewSizeX % 4 )   
		NewSizeX = ( long )( NewSizeX / 4 ) * 4 + 4;   
   
	lpGrayDIB = ( unsigned char* )malloc( sizeY * NewSizeX );   

	if( !lpGrayDIB )   
	{   
		fseek( f, 0, SEEK_SET );   
		fclose( f );   
   
		printf("Can not allocate memory for buffer.\n");   
   
		return NULL;   
	}   
	   
	fseek( f, 0, SEEK_END );   
   
	PackedImageSize = ftell( f );   
   
	PackedImage = ( unsigned char* )malloc( PackedImageSize + 100);   
	if( !PackedImage )   
	{   
		fseek( f, 0, SEEK_SET );   
		fclose( f );   
		free( lpGrayDIB );   
   
		printf("Can not allocate memory for buffer.\n");   
   
		return NULL;   
	}   
   
	fseek( f, sizeof( PCXHeader ), SEEK_SET );   
   
	fread( PackedImage, PackedImageSize, 1, f );   
   
	PackedBytes = PackedImage;   

	*XSize = Header.X2 - Header.X1 + 1;   
	*YSize = Header.Y2 - Header.Y1 + 1;   
   
	GrayWidth = *XSize + ( *XSize % 2 );   

	for( i = 0; i < sizeY; i ++ )
	{
		j = 0;
    
		while ( j < (long)(( unsigned long )Header.BytePerLine) )   
	        {   
			if ( *PackedBytes > (unsigned char)191 )   
			{   
				PackCount = *( PackedBytes ++ ) ^ ( unsigned char )0xC0;   

				memset( &( lpGrayDIB [ i * GrayWidth + j ] ),
					 ( int )*( PackedBytes ++ ),
					 PackCount );   
				j += PackCount;   
			}   
			else   
			{
				lpGrayDIB [ i * GrayWidth + j ] = *( PackedBytes ++ );   
				j ++;
			}
    		}   
	}
   
  
	free( PackedImage );   
   
	Image = (unsigned char*)malloc( (*XSize) * (*YSize) );   
   
	if( !Image )   
	{   
		free( lpGrayDIB );   
		return NULL;   
	}   
   
	if( Header.PaletteInfo == 2 )   
	{   
		for( i = 0; i < *YSize; i ++ )   
		{   
			for( j = 0 ; j < *XSize; j ++ )   
			{   
				Image[ i * (*XSize) + j ] = lpGrayDIB[ i * GrayWidth + j ];   
			}   
		}   
	}   
	else   
	{   
		fseek( f, PackedImageSize - 768, SEEK_SET );   

		fread( Palette, 768, 1, f );  
   
   
		for( i = 0; i < *YSize; i ++ )   
		{   
			for( j = 0 ; j < *XSize; j ++ )   
			{   
				IndexOfColor = lpGrayDIB[ i * GrayWidth + j ] * 3;   
				Gray = 0.299 * Palette[ IndexOfColor     ] +    
					   0.587 * Palette[ IndexOfColor + 1 ] +    
					   0.114 * Palette[ IndexOfColor + 2 ];   
				if( Gray > 255.0 ) Gray = 255.0;   
				if( Gray < 0.0   ) Gray = 0.0;   
				Image[ i * (*XSize) + j ] = (unsigned char)Gray;   
			}   
		}   
	}   
   
	fclose( f );   
   
	free( lpGrayDIB );   
   
	return Image;   
}   
   
/*   
-----------------------------------------------------------------------   
   
  Function WritePCX  -  write buffer into PCX file   
   
  Input:   
			Image       - pointer to array with image   
			XSize       - horizontal size of image   
			YSize       - vertical size of image   
			Name        - file name   
  Return:   
           1 if error occured, 0 if successfully.   
   
  WARNING: before exit from your program use free( Image ) in order to free   
           allocated memory.   
   
-----------------------------------------------------------------------   
*/   
int WritePCX ( unsigned char *Image, int XSize, int YSize,	char Name[] )   
{   
	FILE          *f;   
   
	unsigned char data, cnt;   
    
	long int line, i, j;   
   
	PCXHeader	Header;   
    
	unsigned char  Palette[768];   
    
   
	Header.ZsoftSign = 0x0a;   
	Header.Version = 5;   
	Header.GroupCoding = 1;   
	Header.BitPerPixel = 8;   
	Header.X1 = 0;   
	Header.Y1 = 0;   
	Header.X2 = XSize - 1;   
	Header.Y2 = YSize - 1;   
	Header.HResolution = XSize;   
	Header.VResolution = YSize;   
   
	Header.SHResolution = XSize;   
	Header.SVResolution = YSize;   
   
	Header.PlanesNumber = 1;   
	Header.BytePerLine = XSize;   
	Header.PaletteInfo = 1;   
   
#ifdef __SUN__   
	Header.X1 = Swap( Header.X1 );   
	Header.Y1 = Swap( Header.Y1 );   
	Header.X2 = Swap( Header.X2 );   
	Header.Y2 = Swap( Header.Y2 );   
   
	Header.HResolution = Swap( Header.HResolution );   
	Header.VResolution = Swap( Header.VResolution );   
   
	Header.BytePerLine = Swap( Header.BytePerLine );   
	Header.PaletteInfo = Swap( Header.PaletteInfo );   
   
	Header.SHResolution = Swap( Header.SHResolution );   
	Header.SVResolution = Swap( Header.SVResolution );   
#endif   
   
	for (i = 0; i < 48; i++) Header.EGAPalette[ i ] = 0;   
	for (i = 0; i < 54; i++) Header.Reserve[ i ] = 0;   
/*  PCXHeader.Reserved = 0;*/   
   
	if ( (f = fopen(Name, "wb")) == NULL )    
		return 1;   
   
	fwrite( &Header, sizeof(PCXHeader), 1, f);   
   
	for( line = 0; line < YSize; line ++ )   
	{   
		i=0;   
		do    
		{   
			data = Image[i+(long)line*XSize];   
			cnt = 1;   
			while ((i+cnt)<XSize && data==Image[i+cnt+(long)XSize*line] && cnt<63)   
			{   
				cnt++;   
			}   
			i += cnt;   
			if (cnt>1 || data>= 0xc0)   
			{   
				cnt |= 0xc0;   
				fwrite(&cnt, 1, 1, f);   
			}   
			fwrite(&data, 1, 1, f);   
		}while( i < XSize );   
	}   
	   
	data=0x0c;   
	   
	fwrite(&data, 1, 1, f);   
     
	for( j = 0; j < 256; j++ )   
	{   
		unsigned long nIndex = j * 3;   
		Palette[ nIndex ++ ] = (unsigned char)j;   
		Palette[ nIndex ++ ] = (unsigned char)j;   
		Palette[ nIndex    ] = (unsigned char)j;   
	}   
	   
	fwrite(Palette, sizeof(Palette), 1, f);   
	   
	fclose(f);   
	   
	return(0);   
}   
/*  
-----------------------------------------------------------------------  
    Function ReadTrueColorPCX - read True Color (24-bit) PCX file  
	                   into buffers  
  
    Input:      Name      - file name  
                XS        - horizontal size  
                YS        - vertical size  
  
    Return:     0  if succesful,  
	            -1 if not enought memory  
				-2 if file cannot open of not 24-bits PCX file  
-----------------------------------------------------------------------  
*/  
int   ReadTrueColorPCX  ( char* Name, int *XSize, int *YSize,  
                          unsigned char** RImage,  
                          unsigned char** GImage,  
                          unsigned char** BImage  )  
{  
    unsigned char* pPcxImage;  
    unsigned char* pPcxPtr;  

    long int            i = 0;  
    int                 nFileLength;
  
    int                 PackedImageSize;  
    unsigned char*      PackedImage;  
    unsigned char*      PackedBytes;  
    int                 PackCount;  
    int                 sizeX, sizeY;  
    PCXHeader           Header;  
    int                 length,j;

    unsigned char*      pRBits;     
    unsigned char*      pGBits;     
    unsigned char*      pBBits; 

    FILE* f;

    *XSize = 0;  
    *YSize = 0;  
  
    *RImage = NULL;  
    *GImage = NULL;  
    *BImage = NULL;  
  
 
  
    f = fopen( Name, "rb" );  
    if( f == NULL )  
    {  
        printf("File %s not found.\n", Name);  
        return -2;  
    }  
  
    fseek( f, 0, SEEK_SET );  
    fread( &Header, sizeof( PCXHeader ), 1, f );  
  
#ifdef __SUN__  
    Header.X1 = Swap( Header.X1 );  
    Header.Y1 = Swap( Header.Y1 );  
    Header.X2 = Swap( Header.X2 );  
    Header.Y2 = Swap( Header.Y2 );  
  
    Header.HResolution = Swap( Header.HResolution );  
    Header.VResolution = Swap( Header.VResolution );  
  
    Header.BytePerLine = Swap( Header.BytePerLine );  
    Header.PaletteInfo = Swap( Header.PaletteInfo );  
  
    Header.SHResolution = Swap( Header.SHResolution );  
    Header.SVResolution = Swap( Header.SVResolution );  
#endif  
  
    if ( Header.PlanesNumber != 3 ||  
         Header.BitPerPixel != 8 ||   
         Header.ZsoftSign != 10 ||  
         Header.Version != 5 ||  
         Header.PaletteInfo != 1 )   
    {  
        fclose( f );  
        return -2;  
    }  
  
    sizeX = Header.X2 - Header.X1 + 1;  
    sizeY = Header.Y2 - Header.Y1 + 1;  
    length = sizeX + ( sizeX % 2 );  
  
  
    fseek( f, 0, SEEK_END );  
    nFileLength = ftell( f );  
    fseek( f, sizeof( PCXHeader ), SEEK_SET );  
  
    PackedImageSize = nFileLength - sizeof(PCXHeader);  
  
    if( ( PackedImage = (unsigned char*)malloc( PackedImageSize + 100)) == NULL )  
    {  
        fclose( f );  
        return -1;  
    }  
  
    PackedBytes = PackedImage;  
  
  
    if( ( pPcxImage = ( unsigned char* )malloc( sizeY*length*3 ) ) == NULL )  
    {  
        free( PackedImage );  
        fclose( f );  
        return -1;  
    }  
  
    pPcxPtr = pPcxImage;  
  
    fread( PackedImage, PackedImageSize, 1, f );  
  
    fclose( f );   
  
    while (	i < sizeY * length * 3 )  
    {  
        if ( *PackedBytes > ( unsigned char )0xC0 )  
        {  
            PackCount = *( PackedBytes ) ^ ( unsigned char )0xC0;  
            PackedBytes ++;  
  
            memset ( pPcxPtr, *PackedBytes, PackCount );  
  
            PackedBytes ++;  
            i += PackCount;  
            pPcxPtr += PackCount;  
        }  
        else  
        {  
            *pPcxPtr ++ = *PackedBytes ++;  
            i ++;  
        }  
    }  
  
    free( PackedImage );  
  
    pRBits = (unsigned char*)malloc( sizeX * sizeY );  
    if( !pRBits )  
    {  
        free ( pPcxImage );  
        return -1;  
    }  
    pGBits = (unsigned char*)malloc( sizeX * sizeY );  
    if( !pGBits )  
    {  
        free ( pPcxImage );  
        free ( pRBits );  
        return -1;  
    }  
    pBBits = (unsigned char*)malloc( sizeX * sizeY );  
    if( !pBBits )  
    {  
        free ( pPcxImage );  
        free ( pRBits );  
        free ( pGBits );  
        return -1;  
    }  
  
    for ( i = 0; i < sizeY; i ++ )  
    {  
        for ( j = 0; j < sizeX; j ++ )  
        {  
            pRBits[ i * sizeX + j ] = pPcxImage [ i * length * 3 + j + 0 * length ];  
            pGBits[ i * sizeX + j ] = pPcxImage [ i * length * 3 + j + 1 * length ];  
            pBBits[ i * sizeX + j ] = pPcxImage [ i * length * 3 + j + 2 * length ];  
        }  
    }  
  
    free ( pPcxImage );  
  
    *XSize = sizeX;  
    *YSize = sizeY;  
  
    *RImage = pRBits;  
    *GImage = pGBits;  
    *BImage = pBBits;  
  
    return 0;  
} 
/*   
-----------------------------------------------------------------------   
   
  Function WriteTrueColorPCX  -  write buffer into PCX file   
   
  Input:   
			RImage       - pointer to array with red image chanel
			GImage       - pointer to array with green image chanel
			BImage       - pointer to array with blue image chanel
			XSize       - horizontal size of image   
			YSize       - vertical size of image   
			Name        - file name   
  Return:   
           1 if error occured, 0 if successfully.   
   
  WARNING: before exit from your program use free( Image ) in order to free   
           allocated memory.   
   
-----------------------------------------------------------------------   
*/ 
int			   WriteTrueColorPCX  ( char* Name, int XSize, int YSize,  
						unsigned char* RImage,  
						unsigned char* GImage,  
						unsigned char* BImage  )  
{  
	FILE          *f;  
  
	unsigned char data, cnt;  
   
	long int line, i;  
  
	PCXHeader	Header;  
   
	Header.ZsoftSign = 0x0a;  
	Header.Version = 5;  
	Header.GroupCoding = 1;  
	Header.BitPerPixel = 8;  
	Header.X1 = 0;  
	Header.Y1 = 0;  
	Header.X2 = XSize - 1;  
	Header.Y2 = YSize - 1;  
	Header.HResolution = XSize;  
	Header.VResolution = YSize;  
  
	Header.SHResolution = XSize;  
	Header.SVResolution = YSize;  
  
	Header.PlanesNumber = 3;  
	Header.BytePerLine = XSize;  
	Header.PaletteInfo = 1;  
  
#ifdef __SUN__  
	Header.X1 = Swap( Header.X1 );  
	Header.Y1 = Swap( Header.Y1 );  
	Header.X2 = Swap( Header.X2 );  
	Header.Y2 = Swap( Header.Y2 );  
  
	Header.HResolution = Swap( Header.HResolution );  
	Header.VResolution = Swap( Header.VResolution );  
  
	Header.BytePerLine = Swap( Header.BytePerLine );  
	Header.PaletteInfo = Swap( Header.PaletteInfo );  
  
	Header.SHResolution = Swap( Header.SHResolution );  
	Header.SVResolution = Swap( Header.SVResolution );  
#endif  
  
	for (i = 0; i < 48; i++) Header.EGAPalette[ i ] = 0;  
	for (i = 0; i < 54; i++) Header.Reserve[ i ] = 0;  
  
	if ( (f = fopen(Name, "wb")) == NULL )   
		return -1;  
  
	fwrite( &Header, sizeof(PCXHeader), 1, f);  
  
	for( line = 0; line < YSize; line ++ )  
	{  
		i=0;  
		do   
		{  
			data = RImage[i+(long)line * XSize];  
			cnt = 1;  
			while ( ( i + cnt ) < XSize && data == RImage[i + cnt + (long)XSize * line] && cnt < 63)  
			{  
				cnt++;  
			}  
			i += cnt;  
			if (cnt>1 || data>= 0xc0)  
			{  
				cnt |= 0xc0;  
				fwrite( &cnt, 1, 1, f);  
			}  
			fwrite(&data, 1, 1, f);  
		}while( i < XSize );  
		i=0;  
		do   
		{  
			data = GImage[i+(long)line * XSize];  
			cnt = 1;  
			while ((i+cnt)<XSize && data==GImage[i+cnt+(long)XSize*line] && cnt<63)  
			{  
				cnt++;  
			}  
			i += cnt;  
			if (cnt>1 || data>= 0xc0)  
			{  
				cnt |= 0xc0;  
				fwrite(&cnt, 1, 1, f);  
			}  
			fwrite(&data, 1, 1, f);  
		}while( i < XSize );  
		i=0;  
		do   
		{  
			data = BImage[i+(long)line * XSize];  
			cnt = 1;  
			while ((i+cnt)<XSize && data==BImage[i+cnt+(long)XSize*line] && cnt<63)  
			{  
				cnt++;  
			}  
			i += cnt;  
			if (cnt>1 || data>= 0xc0)  
			{  
				cnt |= 0xc0;  
				fwrite(&cnt, 1, 1, f);  
			}  
			fwrite(&data, 1, 1, f);  
		}while( i < XSize );  
	}  
  
	fclose( f );  
	return 0;  
} 

unsigned char* ReadPCX24_( char* Name, int* XSize, int* YSize )
{
    unsigned char* pPcxImage;  
    unsigned char* pPcxPtr;  

    long int            i = 0;
    long int            j;  
    int                 nFileLength;
  
    int                 PackedImageSize;  
    unsigned char*      PackedImage;  
    unsigned char*      PackedBytes;  
    unsigned char*      ResultImage;  
    int                 PackCount;  
    int                 sizeX, sizeY;  
    PCXHeader           Header;  
    int                 length;

    FILE* f;

    *XSize = 0;  
    *YSize = 0;  
      
    f = fopen( Name, "rb" );  
    if( f == NULL )  
    {  
        printf("File %s not found.\n", Name);  
        return NULL;  
    }  
  
    fseek( f, 0, SEEK_SET );  
    fread( &Header, sizeof( PCXHeader ), 1, f );  
  
#ifdef __SUN__  
    Header.X1 = Swap( Header.X1 );  
    Header.Y1 = Swap( Header.Y1 );  
    Header.X2 = Swap( Header.X2 );  
    Header.Y2 = Swap( Header.Y2 );  
  
    Header.HResolution = Swap( Header.HResolution );  
    Header.VResolution = Swap( Header.VResolution );  
  
    Header.BytePerLine = Swap( Header.BytePerLine );  
    Header.PaletteInfo = Swap( Header.PaletteInfo );  
  
    Header.SHResolution = Swap( Header.SHResolution );  
    Header.SVResolution = Swap( Header.SVResolution );  
#endif  
  
    if ( Header.PlanesNumber != 3 ||  
         Header.BitPerPixel != 8 ||   
         Header.ZsoftSign != 10 ||  
         Header.Version != 5 ||  
         Header.PaletteInfo != 1 )   
    {  
        fclose( f );  
        return NULL;  
    }  
  
    sizeX = Header.X2 - Header.X1 + 1;  
    sizeY = Header.Y2 - Header.Y1 + 1;  
    length = sizeX + ( sizeX % 2 );  
  
  
    fseek( f, 0, SEEK_END );  
    nFileLength = ftell( f );  
    fseek( f, sizeof( PCXHeader ), SEEK_SET );  
  
    PackedImageSize = nFileLength - sizeof(PCXHeader);  
  
    if( ( PackedImage = (unsigned char*)malloc( PackedImageSize + 100)) == NULL )  
    {  
        fclose( f );  
        return NULL;  
    }  
  
    PackedBytes = PackedImage;  
    
    if( ( pPcxImage = ( unsigned char* )malloc( sizeY*length*3 ) ) == NULL )  
    {  
        free( PackedImage );  
        fclose( f );  
        return NULL;  
    }  
  
    pPcxPtr = pPcxImage;  
  
    fread( PackedImage, PackedImageSize, 1, f );  
  
    fclose( f );   
  
    while (	i < sizeY * length * 3 )  
    {  
        if ( *PackedBytes > ( unsigned char )0xC0 )  
        {  
            PackCount = *( PackedBytes ) ^ ( unsigned char )0xC0;  
            PackedBytes ++;  
  
            memset ( pPcxPtr, *PackedBytes, PackCount );  
  
            PackedBytes ++;  
            i += PackCount;  
            pPcxPtr += PackCount;  
        }  
        else  
        {  
            *pPcxPtr ++ = *PackedBytes ++;  
            i ++;  
        }  
    }  
  
    free( PackedImage );   
  
    *XSize = sizeX;  
    *YSize = sizeY;  
    
    ResultImage = (unsigned char*)malloc( sizeX * sizeY * 3 );
    if( !ResultImage )
    {
         free( pPcxImage );
         return NULL;
    }
  
    for ( i = 0; i < sizeY; i ++ )  
    {  
        for ( j = 0; j < sizeX; j ++ )  
        {  
            ResultImage[i* sizeX * 3 + j * 3     ] = pPcxImage [ i * length * 3 + j + 0 * length ];
            ResultImage[i* sizeX * 3 + j * 3 + 1 ] = pPcxImage [ i * length * 3 + j + 1 * length ];
            ResultImage[i* sizeX * 3 + j * 3 + 2 ] = pPcxImage [ i * length * 3 + j + 2 * length ];
        }
    }

    free ( pPcxImage );  

    return ResultImage;  
}
