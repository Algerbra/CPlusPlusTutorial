/************************************************************************/
/*                                                                      */
/************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DSString.h"


/************************************************************************
	https://github.com/julycoding/The-Art-Of-Programming-By-July/blob/master/ebook/zh/01.01.md

	move nLetters back to the tail of the string itself;
/************************************************************************/
void stringFlip(char * str, int sPos, int dPos)
{
	char c = 0;
	while (sPos < dPos)
	{
		c = str[sPos];
		str[sPos++] = str[dPos];
		str[dPos--] = c;
	}

}
char * DSString::moveLetter(char * str, size_t strSz, size_t nLetter)
{
	//str[] = "Hello world";
	//strSz = 11  nLetter = 2;
	if (NULL == str || strSz <= 0 || strSz <= nLetter)
		return str;

	nLetter %= strSz;//
	
	stringFlip(str, 0, nLetter - 1);		//[flip] He				->eH				;
	stringFlip(str, nLetter, strSz - 1);	//[flip]   llo world	->  dlrow oll		;
	stringFlip(str, 0, strSz - 1);			//[flip] eHdlrow oll	->llo worldHe		;

	return str;
}


/************************************************************************/
/*                                                                      */
/************************************************************************/
int DSString::main_DSString()
{

	char * ps = "Hello world, i am here.";
	char *str = (char *)malloc(strlen(ps));
	strcpy(str, ps);
	int n = strlen(str);
	DSString::moveLetter(str, strlen(str), 2);

	fprintf(stderr, "\t <%s>\n", str);

	return 0;
}

