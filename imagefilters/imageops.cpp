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

#include "imageops.hpp"

void fromBGRtoRGB(unsigned char *data, unsigned int imageSize)
{
  unsigned char temp;
  for(unsigned int i = 0; i < imageSize; i += 3)
    {
      temp = data[i];
      data[i] = data[i + 2];
      data[i + 2] = temp;
    }
}

void fromRGBtoBGR(unsigned char *data, unsigned int imageSize)
{
  fromBGRtoRGB(data, imageSize);
}
