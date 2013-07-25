/*  Test for image reading and writing

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
#include <exception>

#include "image.hpp"
#include "imagefilter.hpp"
#include "imagereader.hpp"
#include "imagewriter.hpp"

void printImageData(Image *img);

int main(int argc, char **argv)
{
  // test imagereader, imagewriter
  Imagereader r;
  Imagewriter w;
  Image *testimage;

  try 
    {
      testimage = r.readImageFromFile("test_input3.jpg");

      std::cout << "Successfully read image file!" << std::endl;
      printImageData(testimage);
      std::cout << "Now trying to write output file" << std::endl;

      w.writeImage("output.jpg", testimage, imageType::Jpeg);

      std::cout << "Successfully wrote output file!" << std::endl;
      delete testimage;
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

void printImageData(Image *img)
{
  std::cout << "## Image metadata: ##" << std::endl;
  std::cout << "Image data size: " << img->getSize() << std::endl;
  std::cout << "Image width: " << img->getWidth() << std::endl;
  std::cout << "Image height: " << img->getHeight() << std::endl;
  std::cout << "Bits per Pixel: " << img->getBitsPerPixel() << std::endl; 

  std::cout << std::endl;
}
