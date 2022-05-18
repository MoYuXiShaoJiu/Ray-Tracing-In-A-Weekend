#pragma once
#include<Eigen/Dense>
#include<iostream>
#include"Ray.h"
#include<math.h>
//#include"material.h"
using namespace std;
using namespace Eigen;
//һ�������
//�����ĵ�center��ʹ��eigen
//�а뾶r��double
class material;
class lambertain;
class matal;
class sphere
{
private:
	Vector3d center;
	 double r;
	 Vector3d nomal;
	 double hitTime=0;
	 material& m;
	 material* mp = &m;
	 bool uesd = false;
	 
public:
	
	/*sphere(Vector3d center, double radius)
	{
		this->center = center;
		this->r = radius;
	}*/
	sphere(Vector3d center, double radius, material& ma):m(ma)
	{
		this->center = center;
		this->r = radius;
		mp = &m;
	}



	const material& getMaterial()
	{
		return m;
	}
	const material* getPointer()
	{
		return mp;
	}

	

	void setCenter(Vector3d center)
	{
		this->center = center;
	}
	void setRadius(double r)
	{
		this->r = r;
	}

	Vector3d  getCenter()
	{
		return center;
	}

	double getRadius()
	{
		return r;
	}

	double  hitSphere(ray r)
	{
		double a = r.getDirection().dot(r.getDirection());
		double b = 2 * r.getDirection().dot(r.getPosition() - this->center);
		double c = (r.getPosition() - this->center).dot(r.getPosition() - this->center)-(this->getRadius()*this->getRadius());
		if ((b * b - 4 * a * c) > 0)
		{
			double temp = b * b - 4 * a * c;
			this->nomal = (r.getTimeRay(temp) - this->center).normalized();
			return (-b-pow((b*b-4*a*c),0.5))/(2*a);//����ط���ͨ������ʵ��������ģ����������������λ�ã�����t���Ǵ���0��
		}
		else
			return -1.0;

	}
	bool hitSphere(ray r, double timeMin,double timeMax)
	{
		double a = r.getDirection().dot(r.getDirection());
		double b = 2 * r.getDirection().dot(r.getPosition() - this->center);
		double c = (r.getPosition() - this->center).dot(r.getPosition() - this->center) - (this->getRadius() * this->getRadius());
		double x1 = (-b - pow((b * b - 4 * a * c), 0.5)) / (2 * a);
		double x2 = ((-b + pow((b * b - 4 * a * c), 0.5)) / (2 * a));
		if (x1 > timeMin && x1 < timeMax)
		{
			this->nomal = (r.getTimeRay(x1) - this->center).normalized();
			this->hitTime = x1;
			return true;
		}
		if (x2 > timeMin && x2 < timeMax)
		{
			this->nomal = (r.getTimeRay(x2) - this->center).normalized();
			this->hitTime = x2;
			return true;
		}
		return false;
	}
	



	Vector3d getNormal()
	{

		return this->nomal;
	}


	//��main�������������ȡ�ôﵽ���ϵ�ʱ��ġ�
	double getTimeOfTwo()//�ú�����ʹ��ǰһ��Ҫ����hitSphere�Ķ�����������صĺ�����
	{
		return hitTime;
	}




};






