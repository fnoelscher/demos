/*  Copyright (C) 2013  H. F. Noelscher

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef FORMATS_HPP
#define FORMATS_HPP

#ifndef WIN32
typedef uint32_t DWORD;
typedef uint16_t WORD;
typedef uint32_t LONG;
#endif

/* Format definitions and structs */


/* emum for image formats */
enum imageType { Bitmap, Jpeg };


/* BITMAP STUFF */

#pragma pack(push, 1)

typedef struct bmpFileHeader
{
    WORD bfType;  // file type
    DWORD bfSize;  // size in bytes of the bitmap file
    DWORD bfReserved1;  // reserved; must be 0
    DWORD bfOffBits;  // header to data offset
} bmpFileHeader;

#pragma pack(pop)

#pragma pack(push, 1)

typedef struct bmpInfoHeader
{
    DWORD biSize;  // number of bytes required by the struct
    LONG biWidth;  // width in pixels
    LONG biHeight;  // height in pixels
    WORD biPlanes; // number of color planes, must be 1
    WORD biBitCount; // number of bit per pixel
    DWORD biCompression;// type of compression
    DWORD biSizeImage;  // size of image in bytes
    LONG biXPelsPerMeter;  //number of pixels per meter in x axis
    LONG biYPelsPerMeter;  //number of pixels per meter in y axis
    DWORD biClrUsed;  //number of colors used by th ebitmap
    DWORD biClrImportant;  //number of colors that are important
} bmpInfoHeader;

#pragma pack(pop)

#endif
