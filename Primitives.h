#ifndef PRIMITIVES_H_
#define PRIMITIVES_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

void cart2cyl(
        double x, double y, double z,
        double &r, double &phi, double &cz);

void cyl2cart(
        double r, double phi, double cz,
        double &x, double &y, double &z,
        double coord);

void cart2sph(
        double x, double y, double z,
        double &r, double &phi, double &theta);

void sph2cart(
        double r, double phi, double theta,
        double &x, double &y, double &z,
        double coord);


void make_cylinder_flat(int sides);

void make_cylinder_smooth(int sides, double cdx, double cdy);

void make_cone_flat(int sides, double cdx, double cdy, double cdzUP, double cdzDOWN, double cdW);

void make_cone_carr(int sides, double cdx, double cdy, double cdzUP, double cdzDOWN, double cdW);

void make_cone_smooth(int sides, double cdx, double cdy, double cdzUP, double cdzDOWN, double cdW);

void make_sphere_flat(int rows, int cols);

void make_sphere_smooth(int rows, int cols, double cdx, double cdy, double cdz, double cdr);

void make_icosphere_flat(int rows, int cols);

void make_icosphere_smooth(int rows, int cols);

#endif /* PRIMITIVES_H_ */
