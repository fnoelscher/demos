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
#include <vector>

#include "image.hpp"
#include "imagereader.hpp"
#include "imagewriter.hpp"
#include "bwfilter.hpp"
#include "util/fileops.hpp"

int main(int argc, char **argv)
{
  Imagereader r;
  Imagewriter w;
  std::vector<Image*> images;
  BwFilter bf;

  // get directory contents
  std::vector<std::string> filenames = listDirectoryContents("jpg images");

  try
    {
      // open images
      for(std::string filename : filenames)
	{   
	  if(filename.length() < 3)
	    continue;
    
	  std::string destfile = "jpg images/" + filename;

	  images.push_back( r.readImageFromFile(destfile) );
	}
      std::cout << "Successfully read image files!" << std::endl;

      // process images - stop time TBD
      for(Image *img : images)
	{
	  bf.transform(img);
	}

      // write images
      char index = '1';
      for(Image *img : images)
	{
	  std::string filename = "test output/bwfilter/";
	  filename += index;
	  filename += ".jpeg";
	  w.writeImage(filename, img, imageType::Jpeg);
	  index++;
	}
      std::cout << "Successfully wrote output files!" << std::endl;

      // clean up
      for(Image *img : images)
	{
	  delete img;
	}
      images.clear();      
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
