/*
  This file is part of the Astrometry.net suite.
  Copyright 2006-2008 Dustin Lang, Keir Mierle and Sam Roweis.

  The Astrometry.net suite is free software; you can redistribute
  it and/or modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation, version 2.

  The Astrometry.net suite is distributed in the hope that it will be
  useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with the Astrometry.net suite ; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
*/

#ifndef STARUTIL_H
#define STARUTIL_H

#include <math.h>
#include "an-bool.h"
#include "keywords.h"

#define DIM_STARS 3
#define DIM_XY 2

// upper bound of dimquads value
#define DQMAX 5
// upper bound of dimcodes value
#define DCMAX 6

InlineDeclare int dimquad2dimcode(int dimquad);

typedef unsigned char uchar;

#define ONE_OVER_SIXTY 0.016666666666666666

// pi / 180.
#define RAD_PER_DEG 0.017453292519943295
// pi / (180. * 60.)
#define RAD_PER_ARCMIN 0.00029088820866572158
// pi / (180. * 60. * 60.)
#define RAD_PER_ARCSEC 4.8481368110953598e-06

// 180. / pi
#define DEG_PER_RAD 57.295779513082323
#define DEG_PER_ARCMIN ONE_OVER_SIXTY
// 1./3600.
#define DEG_PER_ARCSEC 0.00027777777777777778

// 60. * 180. / pi
#define ARCMIN_PER_RAD 3437.7467707849396
#define ARCMIN_PER_DEG 60.0
#define ARCMIN_PER_ARCSEC ONE_OVER_SIXTY

// 60. * 60. * 180. / pi
#define ARCSEC_PER_RAD 206264.80624709636
#define ARCSEC_PER_DEG 3600.0
#define ARCSEC_PER_ARCMIN 60.0

InlineDeclare Const double rad2deg(double x);
InlineDeclare Const double rad2arcmin(double x);
InlineDeclare Const double rad2arcsec(double x);

InlineDeclare Const double deg2rad(double x);
InlineDeclare Const double deg2arcmin(double x);
InlineDeclare Const double deg2arcsec(double x);

InlineDeclare Const double arcmin2rad(double x);
InlineDeclare Const double arcmin2deg(double x);
InlineDeclare Const double arcmin2arcsec(double x);

InlineDeclare Const double arcsec2rad(double x);
InlineDeclare Const double arcsec2deg(double x);
InlineDeclare Const double arcsec2arcmin(double x);

#ifdef INCLUDE_INLINE_SOURCE
#define InlineDefine InlineDefineH
#include "starutil.inc"
#undef InlineDefine
#endif

// RA,Dec in radians:
#define radec2x(r,d) (cos(d)*cos(r))
#define radec2y(r,d) (cos(d)*sin(r))
#define radec2z(r,d) (sin(d))
InlineDeclare Const double xy2ra(double x, double y);
InlineDeclare Const double z2dec(double z);

double atora(const char* str);
double atodec(const char* str);

double mag2flux(double mag);

/*
 RA,Dec in degrees.  RAs in range [0, 360], Decs in range [-90, 90].
 */
void radecrange2xyzrange(double ralow, double declow, double rahigh, double dechigh,
						 double* xyzlow, double* xyzhigh);

// RA,Dec in radians:
InlineDeclare void radec2xyz(double ra, double dec, double* x, double* y, double* z);
InlineDeclare Flatten void xyz2radec(double x, double y, double z, double *ra, double *dec);
InlineDeclare Flatten void xyzarr2radec(const double* xyz, double *ra, double *dec);
inline void xyzarr2radecarr(const double* xyz, double *radec);
InlineDeclare void radec2xyzarr(double ra, double dec, double* xyz);
inline void radec2xyzarrmany(double *ra, double *dec, double* xyz, int n);

// RA,Dec in degrees:
InlineDeclare void radecdeg2xyz(double ra, double dec, double* x, double* y, double* z);
InlineDeclare void xyzarr2radecdeg(const double* xyz, double *ra, double *dec);
InlineDeclare void xyzarr2radecdegarr(double* xyz, double *radec);
InlineDeclare void radecdeg2xyzarr(double ra, double dec, double* xyz);
inline void radecdegarr2xyzarr(double* radec, double* xyz);
inline void radecdeg2xyzarrmany(double *ra, double *dec, double* xyz, int n);

// Returns the distance-squared between two (RA,Dec)s in degrees.
double distsq_between_radecdeg(double ra1, double dec1, double ra2, double dec2);

// Returns the arcseconds between two (RA,Dec)s in degrees.
double arcsec_between_radecdeg(double ra1, double dec1, double ra2, double dec2);

// RA in degrees to Mercator X coordinate [0, 1).
inline double ra2mercx(double ra);
// Dec in degrees to Mercator Y coordinate [0, 1).
inline double dec2mercy(double dec);

// RA in degrees to H:M:S
void ra2hms(double ra, int* h, int* m, double* s);
// Dec in degrees to D:M:S
void dec2dms(double dec, int* d, int* m, double* s);

double hms2ra(int h, int m, double s);
double dms2dec(int sgn, int d, int m, double s);

inline void project_hammer_aitoff_x(double x, double y, double z, double* projx, double* projy);

inline void project_equal_area(double x, double y, double z, double* projx, double* projy);

// Converts a distance-squared between two points on the
// surface of the unit sphere into the angle between the
// rays from the center of the sphere to the points, in
// radians.
Const inline double distsq2arc(double dist2);

// Distance^2 on the unit sphere to radians.
// (alias of distsq2arc)
Const inline double distsq2rad(double dist2);

Const inline double distsq2deg(double dist2);

// Distance on the unit sphere to radians.
Const inline double dist2rad(double dist);

// Distance^2 on the unit sphere to arcseconds.
Const inline double distsq2arcsec(double dist2);

// Distance on the unit sphere to arcseconds
Const inline double dist2arcsec(double dist);

// Radians to distance^2 on the unit sphere.
// (alias of arc2distsq)
InlineDeclare Const double rad2distsq(double arcInRadians);

// Radians to distance on the unit sphere.
InlineDeclare Const double rad2dist(double arcInRadians);

// Converts an angle (in arcseconds) into the distance-squared
// between two points on the unit sphere separated by that angle.
InlineDeclare Const double arcsec2distsq(double arcInArcSec);

// Arcseconds to distance on the unit sphere.
Const inline double arcsec2dist(double arcInArcSec);

// Degrees to distance on the unit sphere.
Const inline double deg2dist(double arcInDegrees);

Const inline double deg2distsq(double d);

InlineDeclare Const double arcmin2dist(double arcmin);

InlineDeclare Const double arcmin2distsq(double arcmin);

// Distance on the unit sphere to degrees.
Const inline double dist2deg(double dist);

#define HELP_ERR -101
#define OPT_ERR -201

void make_rand_star(double* star, double ramin, double ramax,
					double decmin, double decmax);

/* 
 Computes the 2D coordinates (x,y) (in units of a celestial sphere of
 radius 1) that star s would have in a TANGENTIAL PROJECTION defined
 by (centred at) star r.  s and r are both given in xyz coordinates,
 the parameters are pointers to arrays of size3.

 WARNING -- this code assumes s and r are UNIT vectors (ie normalized
 to have length 1), the resulting x direction is increasing DEC, the
 resulting y direction is increasing RA, which might not be the normal
 convention.
*/
WarnUnusedResult InlineDeclare bool star_coords(const double *s, const double *r, double *x, double *y);

inline void star_midpoint(double* mid, const double* A, const double* B);

#endif
