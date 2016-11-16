/************************************************************************/
/*                                                                      */
/************************************************************************/
///  >> 11/16/8/2016 BY.gaohuancai QQ1293302539 <<
#pragma once

#include <stdexcept>

class FileIO
{
public:
	class Exception : public std::runtime_error
	{
	public:
		Exception(const std::string &msg)
			:std::runtime_error(msg)
		{}
	};


public:

	static int cpp_GetFileLength(const char * filename);

	static bool c_LoadFileData(const char * filename);

	static int main_FileIO();

};