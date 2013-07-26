/*   
    Simple file and directory operations

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


#ifndef FILEOPS_HPP
#define FILEOPS_HPP

#include <vector>
#include <string>
#include <iostream>
#include <dirent.h>

std::vector<std::string>
listDirectoryContents(std::string path)
{
  DIR *dir;
  struct dirent *ent;
  std::vector<std::string> files;

  if ((dir = opendir (path.c_str())) != NULL) 
    {
      while ((ent = readdir (dir)) != NULL) 
	{
	  files.push_back( ((std::string) ent->d_name) );
	}
      closedir (dir);
    } else 
    {
      std::cerr << "Could not open directory!" << std::endl;
    }
  return files;
}

#endif
