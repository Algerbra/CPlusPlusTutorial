/************************************************************************/
/*                                                                      */
/************************************************************************/
///  >> 11/16/8/2016 BY.gaohuancai QQ1293302539 <<
#pragma once

#include <math.h>

class DMath
{
public:
	static void do_floor_X(float argf = 0.0f);
	static void do_ceil_X(float argf = 0.0f);
	static void do_fmodf_X(float argf = 0.0f, float * iptr = nullptr);

	static int main_DMath();
};