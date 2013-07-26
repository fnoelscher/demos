/*   
    Simple, and very ugly, black and white filter
     simply sums up all color-values to calculate "lightness"

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

#include <iostream>

#include "bwfilter.hpp"


void BwFilter::transform(Image *img)
{ 
  // get colour depth, always assuming RGB
  // also assuming that in case of 32bit pixels, the last byte is Alpha
  int bytesPerPixel = img->getBitsPerPixel() / 8;

  std::cout << "Bytes per Pixel: " << bytesPerPixel << std::endl;  
  
  // get data
  unsigned char *data = img->getData();

  // calculate pixels
  unsigned long numPixelValues = ( img->getHeight() * img->getWidth() ) * bytesPerPixel;

  // for each pixel..
  for(unsigned long i = 0;
      i < numPixelValues;
      i += bytesPerPixel)
    {
      // sum lightness values
      long lightness = 0;
      lightness += data[i];
      lightness += data[i+1];
      lightness += data[i+2];

      // calculate black value
      int blackvalue = lightness % (long) (pow(8, bytesPerPixel));

      // set black values
      data[i] = blackvalue;
      data[i+1] = blackvalue;
      data[i+2] = blackvalue;      
    }
}

void BwFilter::transform(Image *src, Image *dst)
{
  // tbd
}
