/*   
    Imagereader class - reads images from different formats
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

#ifndef IMAGEREADER_HPP
#define IMAGEREADER_HPP

#include <string>
#include <fstream>
#include <exception>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <jpeglib.h>

#include <iostream>

#include "image.hpp"
#include "formats.hpp"
#include "imageops.hpp"


struct ImagereaderException {};
struct OpenFailedException : ImagereaderException {};
struct ReadFailedException : ImagereaderException {};
struct FiletypeNotDetectedException : ImagereaderException {};
struct OtherFailException : ImagereaderException {};

class Imagereader {
public:
  Imagereader();

  Image * readImageFromFile(std::string uri);

  int detectImageType(std::string filename);

private:
  // loads bmp using own loader implementation (experimental)
  Image * loadBitmap(std::string uri); 

  // loads jpeg image using libjpeg
  Image * loadJpeg(std::string uri); 
};

#endif
