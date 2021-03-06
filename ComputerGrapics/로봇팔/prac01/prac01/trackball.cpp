// trackball.cpp: implementation of the TrackBall class.
//
///////////////////////////////////////////////////////////////////////

#include "trackball.h"

//------------------------------------------------------
// vector operations
void normalize( vec3d &v )
{
	double d = 1.0 / sqrt( v[0]*v[0] + v[1]*v[1] + v[2]*v[2] );
	v[0] *= d;
	v[1] *= d;
	v[2] *= d;
	return;
}

double dot( vec3d &a, vec3d &b )
{
	return ( a[0]*b[0] + a[1]*b[1] + a[2]*b[2] );
}

void cross( vec3d &a, vec3d &b, vec3d &c )
{
	c[0] = a[1]*b[2] - a[2]*b[1];
	c[1] = a[2]*b[0] - a[0]*b[2];
	c[2] = a[0]*b[1] - a[1]*b[0];
	return;
}
//------------------------------------------------------

TrackBall::TrackBall()
{
	initialize();
}

TrackBall::~TrackBall()
{

}

void TrackBall::initialize( void )
{
	s = 1.0;
	v[0] = v[1] = v[2] = 0.0;
	for( int i=0; i<16; i++ ) rMat[i] = 0.0;
	rMat[0] = rMat[5] = rMat[10] = rMat[15]= 1.0;
	return;
}

void TrackBall::resize( const int &cx, const int &cy )
{
	width = cx;
	height = cy;
	return;
}

void TrackBall::project( int &xi, int &yi, vec3d &v )
{
	// project x, y onto a hemisphere centered within width, height
	v[0] = ( 2.0*xi - width ) / (double)width;
	v[1] = ( height - 2.0*yi ) / (double)height;
	double d = sqrt( v[0]*v[0] + v[1]*v[1] );
	v[2] = cos( M_PI * 0.5 * ( (d<1.0)? d : 1.0 ) );

	// normalize
	normalize( v );
	return;
}

void TrackBall::start( int xi, int yi )
{
	project( xi, yi, lastPos );
	return;
}

void TrackBall::end( int xi, int yi )
{
	vec3d currPos, t;

	project( xi, yi, currPos );

	t[0] = currPos[0] - lastPos[0];
	t[1] = currPos[1] - lastPos[1];
	t[2] = currPos[2] - lastPos[2];

	if( t[0] || t[1] || t[2] )
	{
		double angle = M_PI * 0.5 * sqrt( t[0]*t[0] + t[1]*t[1] + t[2]*t[2] );
		vec3d axis;
		cross( currPos, lastPos, axis );
		normalize( axis );
		
		// create a quaternion
		double s2 = sin( angle*0.5 );
		vec3d v2 = { s2*axis[0], s2*axis[1], s2*axis[2] };
		s2 = cos( angle*0.5 );

		// quaternions update -- multiplication of quaternions
		double s1 = s;
		vec3d v1 = { v[0], v[1], v[2] }, v3;
		cross( v1, v2, v3 );
		s = ( s1 * s2 ) - dot( v1, v2 );
		v[0] = s1*v2[0] + s2*v1[0] + v3[0];
		v[1] = s1*v2[1] + s2*v1[1] + v3[1];
		v[2] = s1*v2[2] + s2*v1[2] + v3[2];
		
		// normalize the quaternion
		double d = 1.0 / sqrt( s*s + v[0]*v[0] + v[1]*v[1] + v[2]*v[2] );
		s *= d;
		v[0] *= d;
		v[1] *= d;
		v[2] *= d;
		
		// rotation with quaternions	
		// P' = quat * P * quat^-1
		// M = { { 1-2b^2-2c^2, 2ab-2sc,     2ac+2sb }, 
		//		 { 2ab+2sc,     1-2a^2-2c^2, 2bc-2sa },
		//		 { 2ac-2sb,     2bc+2sa,     1-2a^2-2b^2 } };
		rMat[0] = 1.0 - 2.0 * (v[1]*v[1] + v[2]*v[2]);
		rMat[1] =       2.0 * (v[0]*v[1] - s*v[2]);
		rMat[2] =       2.0 * (v[2]*v[0] + s*v[1]);
		//rMat[3] = 0.0;

		rMat[4] =       2.0 * (v[0]*v[1] + s*v[2]);
		rMat[5] = 1.0 - 2.0 * (v[2]*v[2] + v[0]*v[0]);
		rMat[6] =       2.0 * (v[1]*v[2] - s*v[0]);
		//rMat[7] = 0.0;

		rMat[8] =        2.0 * (v[2]*v[0] - s*v[1]);
		rMat[9] =        2.0 * (v[1]*v[2] + s*v[0]);
		rMat[10] = 1.0 - 2.0 * (v[0]*v[0] + v[1]*v[1]);
		//rMat[11] = 0.0;

		//rMat[12] = rMat[13] = rMat[14] = 0.0;
		//rMat[15] = 1.0;

		lastPos[0] = currPos[0];
		lastPos[1] = currPos[1];
		lastPos[2] = currPos[2];
	}
	return;
}

