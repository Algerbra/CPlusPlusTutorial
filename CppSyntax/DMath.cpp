/************************************************************************/
/*                                                                      */
/************************************************************************/
///  >> 11/16/8/2016 BY.gaohuancai QQ1293302539 <<
#include "DMath.h"
#include <stdio.h>
#include <float.h>
#include <fenv.h>


/************************************************************************
http://en.cppreference.com/w/c/numeric/math/floor

  floor()
	defined in header <math.h>

  @brief
	computes the largest integer value not greater than argf;

************************************************************************/
void DMath::do_floor_X(float argf /* = 0.0f */)
{
	fprintf(stderr, "floor(+2.7) = %+.1f\n", floor(2.7));
	fprintf(stderr, "floor(-2.7) = %+.1f\n", floor(-2.7));
	fprintf(stderr, "floor(-0.0) = %+.1f\n", floor(-0.0));
	fprintf(stderr, "floor(-Inf) = %+f\n", floor(-INFINITY));
}

void DMath::do_ceil_X(float argf /* = 0.0f */)
{
	fprintf(stderr, "ceil(+2.4) = %+.1f\n", ceil(2.4));
	fprintf(stderr, "ceil(-2.4) = %+.1f\n", ceil(-2.4));
	fprintf(stderr, "ceil(-0.0) = %+.1f\n", ceil(-0.0));
	fprintf(stderr, "ceil(-Inf) = %+f\n", ceil(-INFINITY));
}

/************************************************************************
http://en.cppreference.com/w/c/numeric/math/modf

  modf()
	defined in header <math.h>
  @brief
	decomposes given floating point value arg into integral and
	fractional parts, each having the same type and sign as argf.

	the integer part (in floating-point format) is stored in the object
	pointed to by iptr;

************************************************************************/
void DMath::do_fmodf_X(float argf /* = 0.0f */, float * iptr /* = NULL */)
{
	fprintf(stderr, "fmod(+5.1, +3.0) = %.1f\n", fmod(5.1, 3));
	fprintf(stderr, "fmod(-5.1, +3.0) = %.1f\n", fmod(-5.1, 3));
	fprintf(stderr, "fmod(+5.1, -3.0) = %.1f\n", fmod(5.1, -3));
	fprintf(stderr, "fmod(-5.1, -3.0) = %.1f\n", fmod(-5.1, -3));
	
	// error handling
	feclearexcept(FE_ALL_EXCEPT);
	fprintf(stderr, "fmod(+5.1, 0) = %.1f\n", fmod(5.1, 0));
	if (fetestexcept(FE_INVALID)) puts("    FE_INVALID raised");
}

int DMath::main_DMath()
{
	DMath::do_floor_X();
	DMath::do_ceil_X();
	DMath::do_fmodf_X();

	return 0;
}