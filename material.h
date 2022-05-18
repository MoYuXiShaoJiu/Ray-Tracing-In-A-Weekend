#pragma once
#include"Ray.h"
#include<vector>
#include"sphere.h"
#include"random.h"
#include<math.h>
using namespace Eigen;
using namespace std;
class sphere;
//写一个虚拟类，接着让sphere继承这个虚类
class material
{
public:
	//本身吸收能量的系数应该用一个三维向量来表示，但是这里有点问题，为什么用三维向量表示
	virtual bool scatter(ray& r, sphere sp, ray& rx) const= 0;
	virtual Vector3d absordLight(Vector3d colorx)const = 0;



};

class lambertain:public material//表示立项散射材质，返回的是一个vector3d
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


//反光材质
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


	//关于法线对称的反射函数
	Vector3d reflected(Vector3d inRay, Vector3d normalLine)const//分别输入入射光线的方向向量，球的法向量
	{

		return inRay -(2 * inRay.dot(normalLine)*normalLine);
	}


};

//折射材质
class dielectric :public material
{
public:
	Vector3d absord=Vector3d(1.0,1.0,1.0);
	double refractNum;
	
	//其实这里可以考虑一下吸收光线的
	dielectric(double refract)
	{
		refractNum = refract;//折射率
	}


	bool scatter(ray& r, sphere sp, ray& rx)const//负责返回最后的折射光线
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
	Vector3d absordLight(Vector3d colorx)const//处理吸收光线的
	{
		Vector3d temp = Vector3d(colorx.x() * absord.x(), colorx.y() * absord.y(), colorx.z() * absord.z());
		return temp;
	}

	Vector3d refraction(Vector3d inDirection,Vector3d normalLine,double current)const//折射
	{
		Vector3d InDirection = -(inDirection.normalized());//取得入射光线的方向向量的反方向
		double cosTheta = fmin(InDirection.dot(normalLine),1.0);//cos theta
		Vector3d rPrimePrep = current * (-InDirection + cosTheta * normalLine);
		double tempNum = -sqrt(fabs(1 - rPrimePrep.dot(rPrimePrep)));
		Vector3d rPrimeParallel = tempNum * normalLine;
		return rPrimeParallel + rPrimePrep;

	}
	Vector3d reflected(Vector3d inRay, Vector3d normalLine)const//分别输入入射光线的方向向量，球的法向量
	{

		return inRay - (2 * inRay.dot(normalLine) * normalLine);
	}
	

};




