/*   
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

#include "imagereader.hpp"

Imagereader::Imagereader() {}

Image* Imagereader::readImageFromFile(std::string uri)
{
  // detect filetype and format image
  int imagetype = this->detectImageType(uri);

  switch (imagetype) 
    {
    case imageType::Bitmap:
      return this->loadBitmap(uri);
      break;
    case imageType::Jpeg:
      return this->loadJpeg(uri);
      break;
    }  
}

int Imagereader::detectImageType(std::string filename)
{
  // bmp checks
  // lazy evaluation by checking the filename

  if(filename.find(".bmp", filename.length() - 4) != std::string::npos)
    return imageType::Bitmap;
  if( (filename.find(".jpeg", filename.length() - 5) != std::string::npos) ||
      (filename.find(".jpg", filename.length() - 4) != std::string::npos) )
    return imageType::Jpeg;
  else
    throw FiletypeNotDetectedException();
}

Image * Imagereader::loadBitmap(std::string uri)
{
  bmpFileHeader fHeader;
  bmpInfoHeader infoHeader;
  unsigned char * imageData;  

  // create stream, open file
  std::ifstream file;
  file.open(uri.c_str(), std::ios::binary);
  
  if(! file.is_open())
    throw OpenFailedException();

  // read data
  file.read(reinterpret_cast<char *> (&fHeader), sizeof(fHeader));

  // verify bitmap format
  if (fHeader.bfType !=0x4D42)
    throw FiletypeNotDetectedException();
  
  // read info header
  file.read(reinterpret_cast<char *> (&infoHeader), sizeof(infoHeader));

  std::cout << "biSizeImage: " << infoHeader.biSizeImage << std::endl;

  // move cursor to image data
  file.seekg(fHeader.bfOffBits);
  
  // determine real size of image data
  int startImageData = file.tellg();
  file.seekg(0, file.end);
  int endImageData = file.tellg();
  int imageDataSize = endImageData - startImageData;

  // set cursor back to startImageData and read data
  file.seekg(startImageData, std::ios_base::beg);
  
  imageData = new unsigned char [imageDataSize];
  
  // take care of padding
  // row sizes are rounded to multiples of 4 bytes but we only want image data!
  char padData[4] = {0, 0, 0, 0};
  unsigned int rowsize = floor( ((infoHeader.biBitCount * infoHeader.biWidth + 31) / 32) * 4 );
  unsigned int paddingSize = rowsize % 4;

  for(unsigned int i = 0; i < infoHeader.biHeight; ++i)
    {     
      file.read(reinterpret_cast<char *> (imageData + (i*rowsize)), rowsize);
      file.read(reinterpret_cast<char *> (padData), paddingSize);
    }

  file.close();

  if ( (file.rdstate() & std::ifstream::failbit ) != 0 ) // necessary?
    throw ReadFailedException();

  // convert to rgb
  fromBGRtoRGB(imageData, imageDataSize);

  // create image
  Image * img = new Image(imageData);
  img->setHeight(infoHeader.biHeight);
  img->setWidth(infoHeader.biWidth);
  img->setSize(imageDataSize);
  img->setBitsPerPixel(infoHeader.biBitCount);
  
  return img;
}

Image * Imagereader::loadJpeg(std::string uri)
{
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;
  
  FILE * file; // using c style is easier in this case
  JSAMPARRAY rowbuffer;
  int row_stride;
  unsigned long imageIndex = 0; // used to determine position in data array

  if((file = fopen(uri.c_str(), "rb")) == NULL)
    throw OpenFailedException();

  // set up decompression
  cinfo.err = jpeg_std_error( &jerr );
  jpeg_create_decompress(&cinfo);
  jpeg_stdio_src(&cinfo, file);
  jpeg_read_header(&cinfo, TRUE);

  jpeg_start_decompress(&cinfo);
  
  /* JSAMPLEs per row in output buffer */
  row_stride = cinfo.output_width * cinfo.output_components;

  // calculate image size, allocate buffer accordingly
  unsigned char *buffer;
  buffer = (unsigned char*) malloc(cinfo.output_width * cinfo.output_height * cinfo.num_components);

  /* Make a one-row-high sample array that will go away when done with image */
  rowbuffer = (*cinfo.mem->alloc_sarray)
		((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

  while (cinfo.output_scanline < cinfo.output_height) {
    jpeg_read_scanlines(&cinfo, rowbuffer, 1);

    // write to buffer
    for(unsigned int i = 0; 
	i < cinfo.image_width * cinfo.num_components; 
	i++)
      {
	buffer[imageIndex++] = rowbuffer[0][i];
      }
  }

  jpeg_finish_decompress(&cinfo); 
  jpeg_destroy_decompress(&cinfo);
  fclose(file);

  // create image
  Image *img = new Image(buffer);
  img->setSize(cinfo.image_width * cinfo.image_height * cinfo.num_components);
  img->setWidth(cinfo.image_width);
  img->setHeight(cinfo.image_height);
  img->setBitsPerPixel(cinfo.num_components * 8);

  return img;
}
