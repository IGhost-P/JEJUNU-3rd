#include <stdio.h>
#include <malloc.h>

#ifndef MYBMPLOADER_INCLUDED
#define MYBMPLOADER_INCLUDED


class MyBMPLoader
{
public:
	unsigned char *image;
	int height, width;

	MyBMPLoader() { image = NULL; height = 0; width = 0; }
	MyBMPLoader( char *filename );

	~MyBMPLoader() { if( image != NULL ) free( image ); }

};

MyBMPLoader::MyBMPLoader( char *filename )
{
    FILE *fp = NULL;
	fopen_s( &fp, filename, "rb" );
    if( fp ) {
		unsigned char bmpfheader[14], bmpiheader[40];
		// read bitmap file header
		fread( bmpfheader, 1, 14, fp );
		// read bitmap information header
		fread( bmpiheader, 1, 40, fp );
		
		// width & height of bitmap
		width = height = 0;
		for( int i=0; i<3; i++ ) {
			width |= ( bmpiheader[4+i] & 0xFF ) << ( i * 8 );
			height |= ( bmpiheader[8+i] & 0xFF ) << ( i * 8 );
		}
		// bit count of color
		int bitcount = ( bmpiheader[15]  &0xFF )<<8 | bmpiheader[14]&0xFF;

		// 24 bits == (r, g, b)
		if( bitcount == 24 ) {
			// size of pixels (r, g, b)
			int size = width * height * 3;
			unsigned char *data = (unsigned char *)malloc( size );
			fread(data, 1, size, fp);
			// rgb colors of image
			image = (unsigned char *)malloc( size );
			for( int i=0; i<width; i++ ) {
				for( register int j=0; j<height; j++ ) {
					int index = ( j * width + i ) * 3;
					int pindex = ( ( height - 1 - j ) * width + i ) * 3;
					image[index++] = data[pindex+2] & 0xFF;
					image[index++] = data[pindex+1] & 0xFF;
					image[index++] = data[pindex] & 0xFF;
				}
			}
			free( data );
		}
		fclose(fp);
    }
    return;
}

#endif // #ifndef MYBMPLOADER_INCLUDED
