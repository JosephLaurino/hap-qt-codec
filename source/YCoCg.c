//
//  YCoCg.c
//
//  Created by Tom Butterworth on 12/07/2012.
//  Copyright (c) 2012 Tom Butterworth. All rights reserved.
//

#include "YCoCg.h"
#include <stdint.h>
#include "ImageMath.h"

/*
 RGB <-> YCoCg
 Y  = [1/4  1/2  1/4][R]
 Co = [1/2  0   -1/2][G]
 Cg = [-1/4 1/2 -1/4][B]
 
 R  = [1    1   -1] [Y]
 G  = [1    0    1] [Co]
 B  = [1   -1   -1] [Cg]
 */

void ConvertRGBAToCoCgAY8888( uint8_t *src, uint8_t *dst, unsigned long width, unsigned long height, size_t src_rowbytes, size_t dst_rowbytes )
{
    const int32_t post_bias[4] = { 512, 512, 0, 0 };
    
    const int16_t matrix[16] = {
         2, -1,  0,  1, // R
         0,  2,  0,  2, // G
        -2, -1,  0,  1, // B
         0,  0,  4,  0  // A
    };
    
    ImageMath_MatrixMultiply8888(src, src_rowbytes, dst, dst_rowbytes, width, height, matrix, 4, NULL, post_bias);
}

void ConvertCoCgAY8888ToRGBA( uint8_t *src, uint8_t *dst, unsigned long width, unsigned long height, size_t src_rowbytes, size_t dst_rowbytes )
{
    const int16_t pre_bias[4] = { -128, -128, 0, 0 };
    
    const int16_t matrix[16] = {
         1,  0, -1,  0, // Co
        -1,  1, -1, 0,  // Cg
         0,  0,  0, 1,  // A
         1,  1,  1,  0  // Y
    };
    
    ImageMath_MatrixMultiply8888(src, src_rowbytes, dst, dst_rowbytes, width, height, matrix, 1, pre_bias, NULL);
}


void ConvertBGRAToCoCgAY8888( uint8_t *src, uint8_t *dst, unsigned long width, unsigned long height, size_t src_rowbytes, size_t dst_rowbytes )
{
    const int32_t post_bias[4] = { 512, 512, 0, 0 };
    
    const int16_t matrix[16] = {
        -2, -1,  0,  1, // B
         0,  2,  0,  2, // G
         2, -1,  0,  1, // R
         0,  0,  4,  0  // A
    };
    
    ImageMath_MatrixMultiply8888(src, src_rowbytes, dst, dst_rowbytes, width, height, matrix, 4, NULL, post_bias);
}

void ConvertCoCgAY8888ToBGRA( uint8_t *src, uint8_t *dst, unsigned long width, unsigned long height, size_t src_rowbytes, size_t dst_rowbytes )
{
    const int16_t pre_bias[4] = { -128, -128, 0, 0 };
    
    const int16_t matrix[16] = {
        -1,  0,  1,  0, // Co
        -1,  1, -1,  0, // Cg
         0,  0,  0,  1, // A
         1,  1,  1,  0  // Y
    };
    
    ImageMath_MatrixMultiply8888(src, src_rowbytes, dst, dst_rowbytes, width, height, matrix, 1, pre_bias, NULL);
}

void ConvertBGR_ToCoCg_Y8888( uint8_t *src, uint8_t *dst, unsigned long width, unsigned long height, size_t src_rowbytes, size_t dst_rowbytes )
{
    ConvertBGRAToCoCgAY8888(src, dst, width, height, src_rowbytes, dst_rowbytes);
}

void ConvertCoCg_Y8888ToBGR_( uint8_t *src, uint8_t *dst, unsigned long width, unsigned long height, size_t src_rowbytes, size_t dst_rowbytes )
{
    ConvertCoCgAY8888ToBGRA(src, dst, width, height, src_rowbytes, dst_rowbytes);
}

void ConvertRGB_ToCoCg_Y8888( uint8_t *src, uint8_t *dst, unsigned long width, unsigned long height, size_t src_rowbytes, size_t dst_rowbytes )
{
    ConvertRGBAToCoCgAY8888(src, dst, width, height, src_rowbytes, dst_rowbytes);
}

void ConvertCoCg_Y8888ToRGB_( uint8_t *src, uint8_t *dst, unsigned long width, unsigned long height, size_t src_rowbytes, size_t dst_rowbytes )
{
    ConvertCoCgAY8888ToRGBA(src, dst, width, height, src_rowbytes, dst_rowbytes);
}

void ConvertRGBAToCoYCgA8888( uint8_t *src, uint8_t *dst, unsigned long width, unsigned long height, size_t src_rowbytes, size_t dst_rowbytes )
{
    const int32_t post_bias[4] = { 512, 0, 512, 0 };

    const int16_t matrix[16] = {
         2,  1, -1,  0, // R
         0,  2,  2,  0, // G
        -2,  1, -1,  0, // B
         0,  0,  0,  4  // A
    };

    ImageMath_MatrixMultiply8888(src, src_rowbytes, dst, dst_rowbytes, width, height, matrix, 4, NULL, post_bias);
}

void ConvertCoYCgA8888ToRGBA( uint8_t *src, uint8_t *dst, unsigned long width, unsigned long height, size_t src_rowbytes, size_t dst_rowbytes )
{
    const int16_t pre_bias[4] = { -128, 0, -128, 0 };

    const int16_t matrix[16] = {
         1,  0, -1,  0, // Co
         1,  1,  1,  0, // Y
        -1,  1, -1,  0, // Cg
         0,  0,  0,  1  // A
    };

    ImageMath_MatrixMultiply8888(src, src_rowbytes, dst, dst_rowbytes, width, height, matrix, 1, pre_bias, NULL);
}

void ConvertBGRAToCoYCgA8888( uint8_t *src, uint8_t *dst, unsigned long width, unsigned long height, size_t src_rowbytes, size_t dst_rowbytes )
{
    const int32_t post_bias[4] = { 512, 0, 512, 0 };

    const int16_t matrix[16] = {
        -2,  1, -1,  0, // B
         0,  2,  2,  0, // G
         2,  1, -1,  0, // R
         0,  0,  0,  4  // A
    };

    ImageMath_MatrixMultiply8888(src, src_rowbytes, dst, dst_rowbytes, width, height, matrix, 4, NULL, post_bias);
}

void ConvertCoYCgA8888ToBGRA( uint8_t *src, uint8_t *dst, unsigned long width, unsigned long height, size_t src_rowbytes, size_t dst_rowbytes )
{
    const int16_t pre_bias[4] = { -128, 0, -128, 0 };

    const int16_t matrix[16] = {
        -1,  0,  1,  0, // Co
         1,  1,  1,  0, // Y
        -1,  1, -1,  0, // Cg
         0,  0,  0,  1  // A

    };

    ImageMath_MatrixMultiply8888(src, src_rowbytes, dst, dst_rowbytes, width, height, matrix, 1, pre_bias, NULL);
}

void ConvertBGR_ToCoYCg_8888( uint8_t *src, uint8_t *dst, unsigned long width, unsigned long height, size_t src_rowbytes, size_t dst_rowbytes )
{
    ConvertBGRAToCoYCgA8888(src, dst, width, height, src_rowbytes, dst_rowbytes);
}

void ConvertCoYCg_8888ToBGR_( uint8_t *src, uint8_t *dst, unsigned long width, unsigned long height, size_t src_rowbytes, size_t dst_rowbytes )
{
    ConvertCoYCgA8888ToBGRA(src, dst, width, height, src_rowbytes, dst_rowbytes);
}

void ConvertRGB_ToCoYCg_8888( uint8_t *src, uint8_t *dst, unsigned long width, unsigned long height, size_t src_rowbytes, size_t dst_rowbytes )
{
    ConvertRGBAToCoYCgA8888(src, dst, width, height, src_rowbytes, dst_rowbytes);
}

void ConvertCoYCg_8888ToRGB_( uint8_t *src, uint8_t *dst, unsigned long width, unsigned long height, size_t src_rowbytes, size_t dst_rowbytes )
{
    ConvertCoYCgA8888ToRGBA(src, dst, width, height, src_rowbytes, dst_rowbytes);
}
