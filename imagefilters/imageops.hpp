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

/* common image operations */

#ifndef IMAGEOPS_HPP
#define IMAGEOPS_HPP

// converts image data form BGR to RGB using temporary
// modifies data in place!
void fromBGRtoRGB(unsigned char *data, unsigned int imageSize);


// converts image data form RGB to BGR using temporary
void fromRGBtoBGR(unsigned char *data, unsigned int imageSize);

#endif
