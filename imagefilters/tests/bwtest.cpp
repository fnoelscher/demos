/*   
    Test for black and white filter

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

#include "image.hpp"
#include "imagereader.hpp"
#include "imagewriter.hpp"
#include "bwfilter.hpp"

int main(int argc, char **argv)
{
  Imagereader r;
  Imagewriter w;
  Image *img;
  BwFilter bf;
  // open image
  try
    {
      // open image
      img = r.readImageFromFile("test_input3.jpg");
      std::cout << "Successfully read image file!" << std::endl;

      // process image
      bf.transform(img);

      // write image
      w.writeImage("bw_output.jpg", img, imageType::Jpeg);
      std::cout << "Successfully wrote output file!" << std::endl;

      // clean up
      delete img;
    }
  catch (OpenFailedException& e)
    {
      std::cout << "Opening input file did not work!" << std::endl;
      return -1;
    }
  catch (ReadFailedException& e)
    {
      std::cout << "Reading image failed!" << std::endl;
      return -1;
    }
  catch (FiletypeNotDetectedException& e)
    {
      std::cout << "Filetype detection failed!" << std::endl;
      return -1;
    }
  catch (ImagereaderException& e)
    {
      std::cout << "Something else imagereader-related failed!" << std::endl;
      return -1;
    }
  catch (ImagewriterException& e)
    {
      std::cout << "Writing image failed!" << std::endl;
      return -1;
    }

  return 0;
}
