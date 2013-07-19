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

#include "imagewriter.hpp"

void Imagewriter::writeImage(std::string uri, Image *img, imageType format)
{
  switch (format)
    {
    case imageType::Bitmap:
      this->writeBitmap(uri, img);
      break;
    case imageType::Jpeg:
      this->writeJpeg(uri, img);
      break;
    }
}

void Imagewriter::writeBitmap(std::string uri, Image *img)
{
  bmpFileHeader fHeader;
  bmpInfoHeader infoHeader;
  unsigned char * data = img->getData();  
  
  std::ofstream file;

  // genereate headers
  fHeader.bfType = 0x4D42;
  fHeader.bfSize = img->getSize() + sizeof(fHeader) + sizeof(infoHeader); // tbc
  fHeader.bfReserved1 = 0;
  fHeader.bfOffBits = sizeof(fHeader) + sizeof(infoHeader);

  infoHeader.biSize = sizeof(infoHeader);
  infoHeader.biWidth = img->getWidth();
  infoHeader.biHeight = img->getHeight();
  infoHeader.biPlanes = 1;
  infoHeader.biBitCount = img->getBitsPerPixel();
  infoHeader.biSizeImage = img->getSize();
  infoHeader.biCompression = 0; // no compression
  infoHeader.biXPelsPerMeter = 0;
  infoHeader.biYPelsPerMeter = 0;
  infoHeader.biClrUsed = 0;
  infoHeader.biClrImportant = 0;

  // convert to BGR
  fromRGBtoBGR(data, img->getSize());

  // write it
  file.open(uri.c_str(), std::ios::binary);
  
  if(! file.is_open())
    throw ImagewriterException();

  file.write(reinterpret_cast<char *> (&fHeader), sizeof(fHeader));
  file.write(reinterpret_cast<char *> (&infoHeader), sizeof(infoHeader));
  
  // fix padding
  char padData[4] = {0, 0, 0, 0};
  unsigned int rowsize = floor( ((img->getBitsPerPixel() * img->getWidth() + 31) / 32) * 4 );
  unsigned int paddingSize = rowsize % 4;

  for(unsigned int i = 0; i < img->getHeight(); ++i)
    {
      file.write(reinterpret_cast<char *> (data + (i*rowsize)), rowsize);
      file.write(reinterpret_cast<char *> (padData), paddingSize);
    }

  file.close();

  
  if ( (file.rdstate() & std::ifstream::failbit ) != 0 ) // necessary?
    throw ImagewriterException();
}

void Imagewriter::writeJpeg(std::string uri, Image *img)
{
  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;

  FILE *file;
  JSAMPROW rowbuffer[1];
  unsigned char *buffer = img->getData();

  if(! (file = fopen(uri.c_str(), "wb")))
    throw ImagewriterException();

  cinfo.err = jpeg_std_error( &jerr );
  jpeg_create_compress(&cinfo);
  jpeg_stdio_dest(&cinfo, file);

  // set params
  cinfo.image_width = img->getWidth();	
  cinfo.image_height = img->getHeight();
  cinfo.input_components = img->getBitsPerPixel() / 8;
  cinfo.in_color_space = JCS_RGB; // default: RGB
  jpeg_set_defaults( &cinfo ); // default compression params

  jpeg_start_compress( &cinfo, TRUE );

  while( cinfo.next_scanline < cinfo.image_height )
    {
      rowbuffer[0] = &buffer[ cinfo.next_scanline * cinfo.image_width *  cinfo.input_components];
      jpeg_write_scanlines( &cinfo, rowbuffer, 1 );
    }

  // cleanup
  jpeg_finish_compress( &cinfo );
  jpeg_destroy_compress( &cinfo );
  fclose(file);
}
