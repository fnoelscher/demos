/*   
    Imagewriter class - writes images to different formats
    Working: Jpeg
    Not Working: BMP
     
    Copyright (C) 2013  H. F. Noelscher

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

#ifndef IMAGEWRITER_HPP
#define IMAGEWRITER_HPP

#include <fstream>
#include <string>
#include <iostream>
#include <cmath>
#include <jpeglib.h>

#include "image.hpp"
#include "formats.hpp"
#include "imageops.hpp"

struct ImagewriterException {};

class Imagewriter {
public:
  Imagewriter() {}

  void writeImage(std::string uri, Image *img, imageType format);

  void writeBitmap(std::string uri, Image *img);
  void writeJpeg(std::string uri, Image *img);

};

#endif
