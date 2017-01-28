
float r4_uni (__global uint *jsr )

/******************************************************************************/
/*
  Purpose:

    R4_UNI returns a uniformly distributed real value.

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    04 October 2013

  Author:

    John Burkardt

  Reference:

    George Marsaglia, Wai Wan Tsang,
    The Ziggurat Method for Generating Random Variables,
    Journal of Statistical Software,
    Volume 5, Number 8, October 2000, seven pages.

  Parameters:

    Input/output, uint *JSR, the seed.

    Output, float R4_UNI, a uniformly distributed random value in
    the range [0,1].
*/
{
  uint jsr_input;
  float value;

  jsr_input = *jsr;

  *jsr = ( *jsr ^ ( *jsr <<   13 ) );
  *jsr = ( *jsr ^ ( *jsr >>   17 ) );
  *jsr = ( *jsr ^ ( *jsr <<    5 ) );

  value = fmod ( 0.5 
    + ( float ) ( jsr_input + *jsr ) / 65536.0 / 65536.0, 1.0 );

  return value;
}
/******************************************************************************/


uint shr3_seeded (__global uint *jsr )

/******************************************************************************/
/*
  Purpose:

    SHR3_SEEDED evaluates the SHR3 generator for integers.

  Discussion:

    Thanks to Dirk Eddelbuettel for pointing out that this code needed to
    use the uint data type in order to execute properly in 64 bit mode,
    03 October 2013.

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    04 October 2013

  Author:

    John Burkardt

  Reference:

    George Marsaglia, Wai Wan Tsang,
    The Ziggurat Method for Generating Random Variables,
    Journal of Statistical Software,
    Volume 5, Number 8, October 2000, seven pages.

  Parameters:

    Input/output, uint *JSR, the seed, which is updated 
    on each call.

    Output, uint SHR3_SEEDED, the new value.
*/
{
  uint value;

  value = *jsr;

  *jsr = ( *jsr ^ ( *jsr <<   13 ) );
  *jsr = ( *jsr ^ ( *jsr >>   17 ) );
  *jsr = ( *jsr ^ ( *jsr <<    5 ) );

  value = value + *jsr;

  return value;
}
/******************************************************************************/


float r4_exp (__global uint *jsr, __global uint* ke, __global float *fe, __global float* we)

/******************************************************************************/
/*
  Purpose:

    R4_EXP returns an exponentially distributed single precision real value.

  Discussion:

    The underlying algorithm is the ziggurat method.

    Before the first call to this function, the user must call R4_EXP_SETUP
    to determine the values of KE, FE and WE.

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    15 October 2013

  Author:

    John Burkardt

  Reference:

    George Marsaglia, Wai Wan Tsang,
    The Ziggurat Method for Generating Random Variables,
    Journal of Statistical Software,
    Volume 5, Number 8, October 2000, seven pages.

  Parameters:

    Input/output, uint *JSR, the seed.

    Input, uint KE[256], data computed by R4_EXP_SETUP.

    Input, float FE[256], WE[256], data computed by R4_EXP_SETUP.

    Output, float R4_EXP, an exponentially distributed random value.
*/
{
  uint iz;
  uint jz;
  float value;
  float x;

  jz = shr3_seeded ( jsr );
  iz = ( jz & 255 );

  if ( jz < ke[iz] )
  {
    value = ( float ) ( jz ) * we[iz];
  }
  else
  {
    for ( ; ; )
    {
      if ( iz == 0 )
      {
        value = 7.69711 - log ( r4_uni ( jsr ) );
        break;
      }

      x = ( float ) ( jz ) * we[iz];

      if ( fe[iz] + r4_uni ( jsr ) * ( fe[iz-1] - fe[iz] ) < exp ( - x ) )
      {
        value = x;
        break;
      }

      jz = shr3_seeded ( jsr );
      iz = ( jz & 255 );

      if ( jz < ke[iz] )
      {
        value = ( float ) ( jz ) * we[iz];
        break;
      }
    }
  }
  return value;
}
/******************************************************************************/

void r4_exp_setup (__global uint* ke,__global float* fe,__global float* we)

/******************************************************************************/
/*
  Purpose:

    R4_EXP_SETUP sets data needed by R4_EXP.

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    14 October 2013

  Author:

    John Burkardt

  Reference:

    George Marsaglia, Wai Wan Tsang,
    The Ziggurat Method for Generating Random Variables,
    Journal of Statistical Software,
    Volume 5, Number 8, October 2000, seven pages.

  Parameters:

    Output, uint KE[256], data needed by R4_EXP.

    Output, float FE[256], WE[256], data needed by R4_EXP.
*/
{
  float de = 7.697117470131487;
  int i;
  const float m2 = 2147483648.0;
  float q;
  float te = 7.697117470131487;
  const float ve = 3.949659822581572E-03;

  q = ve / exp ( - de );

  ke[0] = ( uint ) ( ( de / q ) * m2 );
  ke[1] = 0;

  we[0] = ( float ) ( q / m2 );
  we[255] = ( float ) ( de / m2 );

  fe[0] = 1.0;
  fe[255] = ( float ) ( exp ( - de ) );

  for ( i = 254; 1 <= i; i-- )
  {
    de = - log ( ve / de + exp ( - de ) );
    ke[i+1] = ( uint ) ( ( de / te ) * m2 );
    te = de;
    fe[i] = ( float ) ( exp ( - de ) );
    we[i] = ( float ) ( de / m2 );
  }
  return;
}
/******************************************************************************/

__kernel void r4_nor (__global uint *jsr, __global uint* kn, __global float* fn, __global float* wn, __global float* value, unsigned int offset)

/******************************************************************************/
/*
  Purpose:

    R4_NOR returns a normally distributed single precision real value.

  Discussion:

    The value returned is generated from a distribution with mean 0 and 
    variance 1.

    The underlying algorithm is the ziggurat method.

    Before the first call to this function, the user must call R4_NOR_SETUP
    to determine the values of KN, FN and WN.

    Thanks to Chad Wagner, 21 July 2014, for noticing a bug of the form
      if ( x * x <= y * y );   <-- Stray semicolon!
      {
        break;
      }

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    21 July 2014

  Author:

    John Burkardt

  Reference:

    George Marsaglia, Wai Wan Tsang,
    The Ziggurat Method for Generating Random Variables,
    Journal of Statistical Software,
    Volume 5, Number 8, October 2000, seven pages.

  Parameters:

    Input/output, uint *JSR, the seed.

    Input, uint KN[128], data computed by R4_NOR_SETUP.

    Input, float FN[128], WN[128], data computed by R4_NOR_SETUP.

    Output, float R4_NOR, a normally distributed random value.
*/
{
	if (get_global_id(0) == 0) {
	  int hz;
	  uint iz;
	  const float r = 3.442620;
	  float x;
	  float y;

	  hz = ( int ) shr3_seeded ( jsr );
	  iz = ( hz & 127 );

	  if ( abs ( hz ) < kn[iz] )
	  {
		value[offset] = ( float ) ( hz ) * wn[iz];
	  }
	  else
	  {
		for ( ; ; )
		{
		  if ( iz == 0 )
		  {
			for ( ; ; )
			{
			  x = - 0.2904764 * log ( r4_uni ( jsr ) );
			  y = - log ( r4_uni ( jsr ) );
			  if ( x * x <= y + y )
			  {
				break;
			  }
			}

			if ( hz <= 0 )
			{
			  value[offset] = - r - x;
			}
			else
			{
			  value[offset] = + r + x;
			}
			break;
		  }

		  x = ( float ) ( hz ) * wn[iz];

		  if ( fn[iz] + r4_uni ( jsr ) * ( fn[iz-1] - fn[iz] ) 
			< exp ( - 0.5 * x * x ) )
		  {
			value[offset] = x;
			break;
		  }

		  hz = ( int ) shr3_seeded ( jsr );
		  iz = ( hz & 127 );

		  if ( abs ( hz ) < kn[iz] )
		  {
			value[offset] = ( float ) ( hz ) * wn[iz];
			break;
		  }
		}
	  }
	}
	
}
/******************************************************************************/

__kernel void r4_nor_setup (__global uint* kn,__global float* fn,__global float* wn)

/******************************************************************************/
/*
  Purpose:

    R4_NOR_SETUP sets data needed by R4_NOR.

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    14 October 2013

  Author:

    John Burkardt

  Reference:

    George Marsaglia, Wai Wan Tsang,
    The Ziggurat Method for Generating Random Variables,
    Journal of Statistical Software,
    Volume 5, Number 8, October 2000, seven pages.

  Parameters:

    Output, uint KN[128], data needed by R4_NOR.

    Output, float FN[128], WN[128], data needed by R4_NOR.
*/
{
  float dn = 3.442619855899;
  int i;
  const float m1 = 2147483648.0;
  float q;
  float tn = 3.442619855899;
  const float vn = 9.91256303526217E-03;

  q = vn / exp ( - 0.5 * dn * dn );

  kn[0] = ( uint ) ( ( dn / q ) * m1 );
  kn[1] = 0;

  wn[0] = ( float ) ( q / m1 );
  wn[127] = ( float ) ( dn / m1 );

  fn[0] = 1.0;
  fn[127] = ( float ) ( exp ( - 0.5 * dn * dn ) );

  for ( i = 126; 1 <= i; i-- )
  {
    dn = sqrt ( - 2.0 * log ( vn / dn + exp ( - 0.5 * dn * dn ) ) );
    kn[i+1] = ( uint ) ( ( dn / tn ) * m1 );
    tn = dn;
    fn[i] = ( float ) ( exp ( - 0.5 * dn * dn ) );
    wn[i] = ( float ) ( dn / m1 );
  }

  return;
}
/******************************************************************************/
