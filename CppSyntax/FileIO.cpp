/************************************************************************/
/*                                                                      */
/************************************************************************/
///  >> 11/16/8/2016 BY.gaohuancai QQ1293302539 <<
#include "FileIO.h"

//#include <istream>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int FileIO::cpp_GetFileLength(const char * filename)
{
	//check if filename string validates;
	//check if filename exists;
	std::ifstream fin(filename, std::ifstream::in);
	if (!fin.is_open()) {
		std::string msg = std::string(": unable to open ") +
			std::string(filename) + std::string(" for reading");
		throw Exception(msg);
	}

	int pos = fin.tellg();
	fin.seekg(0, std::ios::end);
	int fileLen = fin.tellg();

	//restore the position of the get pointer;
	fin.seekg(pos);
	fin.close();

	fprintf(stderr, ": <%s> is of %d bytes len..\n", filename, fileLen);

	return fileLen;
}

bool FileIO::c_LoadFileData(const char * filename)
{
	FILE * fp = fopen(filename, "rt");
	if (!fp)
		throw Exception(": unable to open file\n");

	// Get all lines from a file;
	std::vector<std::string> sLines;
	char sline[255];
	while (fgets(sline, 255, fp))
		sLines.push_back(sline);
	fclose(fp);
	for (auto& it : sLines)
		fprintf(stderr, "\t %s", it.c_str());
	
	return true;
}


static char * strfile = "qshambler.md5mesh";
int FileIO::main_FileIO()
{
	FileIO::c_LoadFileData(strfile);

	return 0;
}