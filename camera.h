#pragma once
#include<iostream>
#include"Ray.h"
#include<Eigen/Dense>
#include<math.h>
#include"random.h"
#define pi 3.1415926
using namespace std;
using namespace Eigen;

class camera
{
private:
	Vector3d leftLowerCorner;
	Vector3d horizontal;
	Vector3d vertical;
	Vector3d origenal;
	double lensRadius;
	Vector3d u;
	Vector3d v;
	Vector3d w;
	

public:
	camera(Vector3d leftLowerCorner, Vector3d horizontal, Vector3d vertical, Vector3d origenal)
	{
		this->leftLowerCorner = leftLowerCorner;//���½�
		this->horizontal = horizontal;//ˮƽ���ƫ����
		this->vertical = vertical;//��ֱ���ƫ����
		this->origenal = origenal;//�������λ��
	}
	camera(double vfov, double aspect_ratio)
	{
		double theta = (vfov / 180.0) * pi;//ת��Ϊ����ֵ
		double h = tan(theta / 2);
		double viewportHeight = 2 * h;
		double viewportWidth = aspect_ratio * viewportHeight;
		double focalLength = 1.0;

		this->origenal = Vector3d(0, 0, 0);
		this->horizontal = Vector3d(viewportWidth, 0, 0);
		this->vertical = Vector3d(0, viewportHeight, 0);
		this->leftLowerCorner = origenal - horizontal / 2 - vertical / 2 - Vector3d(0, 0, focalLength);


	}
	camera(Vector3d lookfrom, Vector3d loookat, Vector3d vup, double vfov, double aspect_ratio)
	{

		double theta = (vfov / 180.0) * pi;//ת��Ϊ����ֵ
		double h = tan(theta / 2);
		double viewportHeight = 2 * h;
		double viewportWidth = aspect_ratio * viewportHeight;

		Vector3d w = (lookfrom - loookat).normalized();
		Vector3d u = vup.cross(w).normalized();
		Vector3d v = w.cross(u);

		this->origenal = lookfrom;
		this->horizontal = viewportWidth * u;
		this->vertical = viewportHeight * v;
		this->leftLowerCorner = origenal - horizontal / 2 - vertical / 2 - w;


	}
	camera(Vector3d lookfrom, Vector3d loookat, Vector3d vup, double vfov, double aspect_ratio,double aperture,double focusDist)
	{
		this->lensRadius = aperture / 2;
		double theta = (vfov * pi / 180.0) ;//ת��Ϊ����ֵ
		double h = tan(theta / 2)*focusDist;//�����Ļ�ĸ߶�
		double viewportHeight = 2 * h;//������Ļ����ĸ߶�
		double viewportWidth = aspect_ratio * viewportHeight;//������Ļ����Ŀ��
		this->origenal = lookfrom;//�����ǿ���ȥ�ĵ�
		Vector3d w = (lookfrom - loookat).normalized();//һ����������������µ�����ϵ��������׼������
		Vector3d u = vup.cross(w).normalized();//
		Vector3d v = w.cross(u);//��Ӧvup�ķ���

		
		this->horizontal = viewportWidth * u;//ˮƽ����
		this->vertical =viewportHeight * v;
		this->leftLowerCorner = origenal - horizontal / 2 -  vertical / 2 - focusDist*w;
		

	}


	ray getRay(double s, double t)
	{
		/*Vector3d rd = lensRadius * randomInUnitDisk();
		Vector3d offset = u * rd.x() + v * rd.y();
		ray r(origenal+offset, (leftLowerCorner + s * horizontal + t * vertical)-origenal-offset);
		return r;*/

		return ray(origenal, leftLowerCorner + s * horizontal + t * vertical - origenal);
	}

	ray getRayNew(double s, double t)
	{
		Vector3d rd = lensRadius * randomInUnitDisk();
		Vector3d offset = u * rd.x() + v * rd.y();
		return ray(origenal + offset, leftLowerCorner + s * horizontal + t * vertical - origenal - offset);
	}



};