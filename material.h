#pragma once
#include"Ray.h"
#include<vector>
#include"sphere.h"
#include"random.h"
#include<math.h>
using namespace Eigen;
using namespace std;
class sphere;
//дһ�������࣬������sphere�̳��������
class material
{
public:
	//��������������ϵ��Ӧ����һ����ά��������ʾ�����������е����⣬Ϊʲô����ά������ʾ
	virtual bool scatter(ray& r, sphere sp, ray& rx) const= 0;
	virtual Vector3d absordLight(Vector3d colorx)const = 0;



};

class lambertain:public material//��ʾ����ɢ����ʣ����ص���һ��vector3d
{
public:
	Vector3d absord;
	lambertain(Vector3d absordNum)
	{
		absord = absordNum;
	}
	bool scatter(ray& r,  sphere sp, ray& rx) const
	{
		Vector3d target = r.getTimeRay(sp.getTimeOfTwo()) + sp.getNormal() + randomVector();
		 rx = ray(r.getTimeRay(sp.getTimeOfTwo()), target - r.getTimeRay(sp.getTimeOfTwo()));
		 return true;
	}
	Vector3d absordLight(Vector3d colorx)const
	{
		Vector3d temp = Vector3d(colorx.x() * absord.x(), colorx.y() * absord.y(), colorx.z() * absord.z());
		return temp;
	}

	

};


//�������
class matal :public material
{
public:
	Vector3d absord;
	matal(Vector3d absordNum)
	{
		absord = absordNum;
	}
	Vector3d absordLight(Vector3d colorx)const
	{
		Vector3d temp = Vector3d(colorx.x() * absord.x(), colorx.y() * absord.y(), colorx.z() * absord.z());
		return temp;
	}
	bool scatter(ray& r, sphere sp, ray& rx) const
	{
		
		Vector3d reflect = reflected(r.getDirection(), sp.getNormal());
		rx = ray(r.getTimeRay(sp.getTimeOfTwo()), reflect.normalized());
		return(rx.getDirection().dot(sp.getNormal())>0);
	}


	//���ڷ��߶ԳƵķ��亯��
	Vector3d reflected(Vector3d inRay, Vector3d normalLine)const//�ֱ�����������ߵķ�����������ķ�����
	{

		return inRay -(2 * inRay.dot(normalLine)*normalLine);
	}


};

//�������
class dielectric :public material
{
public:
	Vector3d absord=Vector3d(1.0,1.0,1.0);
	double refractNum;
	
	//��ʵ������Կ���һ�����չ��ߵ�
	dielectric(double refract)
	{
		refractNum = refract;//������
	}


	bool scatter(ray& r, sphere sp, ray& rx)const//���𷵻������������
	{
		double cosTheta = fmin(-r.getDirection().normalized().dot(sp.getNormal()), 1.0);
		double sinTheta = sqrt(1 - cosTheta*cosTheta);
		double currentRefract;
		Vector3d normalLine;
		if (r.getDirection().dot(sp.getNormal())<0)
		{
			currentRefract = 1 / refractNum;
			normalLine = sp.getNormal();
		}
		else
		{
			currentRefract = refractNum;
			normalLine = -sp.getNormal();
		}



		if (sinTheta*currentRefract>1)
		{
			Vector3d reflect = reflected(r.getDirection(), sp.getNormal());
			rx = ray(r.getTimeRay(sp.getTimeOfTwo()), reflect.normalized());
		}
		else
		{
			rx = ray(r.getTimeRay(sp.getTimeOfTwo()), refraction(r.getDirection(), normalLine, currentRefract));
			
		}
		return true;

	}
	Vector3d absordLight(Vector3d colorx)const//�������չ��ߵ�
	{
		Vector3d temp = Vector3d(colorx.x() * absord.x(), colorx.y() * absord.y(), colorx.z() * absord.z());
		return temp;
	}

	Vector3d refraction(Vector3d inDirection,Vector3d normalLine,double current)const//����
	{
		Vector3d InDirection = -(inDirection.normalized());//ȡ��������ߵķ��������ķ�����
		double cosTheta = fmin(InDirection.dot(normalLine),1.0);//cos theta
		Vector3d rPrimePrep = current * (-InDirection + cosTheta * normalLine);
		double tempNum = -sqrt(fabs(1 - rPrimePrep.dot(rPrimePrep)));
		Vector3d rPrimeParallel = tempNum * normalLine;
		return rPrimeParallel + rPrimePrep;

	}
	Vector3d reflected(Vector3d inRay, Vector3d normalLine)const//�ֱ�����������ߵķ�����������ķ�����
	{

		return inRay - (2 * inRay.dot(normalLine) * normalLine);
	}
	

};




