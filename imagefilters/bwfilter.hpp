/*   
    Simple black and white filter
     simply sums up all color-values and calculates "lightness"

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

#ifndef BWFILTER_HPP
#define BWFILTER_HPP

#include <cmath>

#include "imagefilter.hpp"

class BwFilter : public Imagefilter {
public:
  // override
  void transform(Image *img);
  void transform(Image *src, Image *dst);
};

#endif
