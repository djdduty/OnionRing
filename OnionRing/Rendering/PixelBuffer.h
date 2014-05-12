#ifndef PIXELBUFFER_H
#define PIXELBUFFER_H

/*
 *
 * Yes, I COMPLETELY ripped this off of @NeiloGD I don't fully understand what is going on here,
 * so I decided to use his stuff until I do, then write my own.
 *
 */
typedef struct
{
    int     bpp;
    int     w;
    int     h;
    void*   addr;
} PixelBuffer_t;

/**
 * Create pixel buffer.
 * @param pixelBuffer Output pixel buffer.
 * @param bpp Bytes per pixel.
 * @param w Width
 * @param h Height
 * @param startAddress Start address. NULL if you want to create one.
 */
void PixelBuffer_Create( PixelBuffer_t* pixelBuffer, int bpp, int w, int h );

/**
 * Destroy pixel buffer.
 * @param pixelBuffer Pixel buffer.
 */
void PixelBuffer_Destroy( PixelBuffer_t* pixelBuffer );

/**
 * Get pointer to pixel.
 * @param pixelBuffer Pixel buffer.
 * @param x
 * @param y
 */
void* PixelBuffer_Pixel( PixelBuffer_t* pixelBuffer, int x, int y );

#endif // PIXELBUFFER_H
