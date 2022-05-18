#pragma once
#include<iostream>
#include"Ray.h"
#include<Eigen/Dense>
#include<math.h>
#include"random.h"
#define pi 3.1415926
using namespace std;
using namespace Eigen;

class xiangji
{
public:
	Vector3d original;
	Vector3d horizontal;
	Vector3d vertical;
	Vector3d leftLowerConer;
	Vector3d u, v, w;
	double lensRadius;
	
	xiangji(Vector3d lookfrom, Vector3d lookat, Vector3d vup, double vfov, double aspect,double aperture, double focusDis)
	{
		this->lensRadius = aperture / 2.0;
		double  theta = (vfov / 180.0) * pi;
		double halfHeight = tan(theta / 2.0);
		double halfWeight = halfHeight * aspect;
		this->original = lookfrom;
		w = (lookfrom - lookat).normalized();
		u = vup.cross(w).normalized();
		v = w.cross(u);
		leftLowerConer = original - halfWeight * focusDis * u - halfHeight * focusDis * v - focusDis * w;
		this->horizontal = 2 * halfWeight * focusDis * u;
		this->vertical = 2 * halfHeight * focusDis * v;

	}
	ray getRay(double s, double t)
	{
		Vector3d rd = lensRadius * randomInUnitDisk();
		Vector3d offest = u * rd.x() + v * rd.y();
		return ray(original + offest, leftLowerConer + s * horizontal + t * vertical - original - offest);
	}

};