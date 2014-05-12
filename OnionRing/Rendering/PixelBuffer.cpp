#include <Rendering/PixelBuffer.h>

#include <stdio.h>
#include <malloc.h>
#include <System/EngineTypes.h>

void PixelBuffer_Create( PixelBuffer_t* pixelBuffer, int bpp, int w, int h )
{
    pixelBuffer->bpp = bpp;
    pixelBuffer->w = w;
    pixelBuffer->h = h;
    pixelBuffer->addr = malloc( ( w * h * bpp ) );
}

void PixelBuffer_Destroy( PixelBuffer_t* pixelBuffer )
{
    free( pixelBuffer->addr );
    pixelBuffer->addr = NULL;
}

void* PixelBuffer_Pixel( PixelBuffer_t* pixelBuffer, int x, int y )
{
    byte* byteAddr = (byte*)pixelBuffer->addr;
    return byteAddr + ( ( x + y * pixelBuffer->w ) * pixelBuffer->bpp );
}
