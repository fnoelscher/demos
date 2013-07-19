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

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <cstdlib>

/*
  Standard Image class, unified data representation of images
  Images are loaded from files using Imagereader
  Images are written to files using Imagewriter
  Pixel format is RGB, pixel depth can vary
 */

class Image {
public:
  Image() {}
  Image(unsigned char *data) { this->data = data; }// loads bitmap directly

  ~Image() { free(this->data); }

  // accessors
  unsigned char *getData() { return this->data; }
  long getHeight() { return this->height; }
  long getWidth() { return this->width; }
  unsigned int getSize() { return this->size; }
  unsigned int getBitsPerPixel() { return this->bitsPerPixel; }

  void setData(unsigned char *newdata) { this->data = newdata; }
  void setHeight(unsigned int h) { this->height = h; }
  void setWidth(unsigned int w) { this->width = w; }
  void setSize(unsigned int s) { this->size = s; }
  void setBitsPerPixel(unsigned short b) { this->bitsPerPixel = b; }


private:
  // no reason to not use vector here! TBD
  unsigned char **array; // array for 2D access TBD
  unsigned char *data; // image data

  long height; // number of pixels, height
  long width; // number of pixels, width
  unsigned int size; // size of image data in bytes
  unsigned short bitsPerPixel;
};

#endif
