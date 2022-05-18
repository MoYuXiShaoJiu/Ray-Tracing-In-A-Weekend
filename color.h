#pragma once
#include"Ray.h"
#include"sphere.h"
#include<vector>
#include<Eigen/Dense>
#include"random.h"
#include"material.h"
using namespace std;
using namespace Eigen;



Vector3d color(ray r, sphere s)
{
    double t = s.hitSphere(r);
    if (t > 0)
    {
        //这里的光线是直接到屏幕上的一个点的，因为摄像机位置是（0，0，0）
        Vector3d newRay = (r.getTimeRay(t) - Vector3d(0, 0, -1)).normalized();
        return 0.5 * Vector3d(newRay.x() + 1, newRay.y() + 1, newRay.z() + 1);

    }
    else
    {
        Vector3d temp = r.getDirection().normalized();
        double t = 0.5 * (temp.y() + 1);
        return (1.0 - t) * Vector3d(1.0, 1.0, 1.0) + t * Vector3d(0.5, 0.7, 1.0);
    }
}
//这里输入的是一个包含了很多球的list，对于这个球使用zbuffer来计算，只取得最近的那个那个时间的值
//同时，由于摄像机位置的原因，这里的值应该还都是正数

Vector3d color(ray r, vector<sphere> spheres)
{
    //对list中的每一个球求交点，且是较小的那个交点，接着再在这些交点里面选出最小的值
    //将这些值放在一个数组中
    vector<double>times;
    double minTimes = 99999;
    int  id = 0;
    for (int i = 0; i < spheres.size(); i++)
    {
        bool temp = spheres[i].hitSphere(r, 0, 99999);
        if (temp)//如果打到了东西，就更新时间
        {
            double x = spheres[i].getTimeOfTwo();
            if (x < minTimes)
            {
                minTimes = x;
                id = i;
            }

        }

    }
    //以上是找出单个像素的时候先打到的物体
    if (minTimes < 99999)
    {
        return 0.5 * (Vector3d(1 + spheres[id].getNormal().x(), 1 + spheres[id].getNormal().y(), 1 + spheres[id].getNormal().z()));
    }
    else
    {
        Vector3d unit = r.getDirection().normalized();
        double t = 0.5 * (unit.y() + 1);
        return (1 - t) * Vector3d(1.0, 1.0, 1.0) + t * Vector3d(0.5, 0.7, 1.0);
    }




}

Vector3d color(ray r, vector<sphere> spheres, int bunceNum)
{
    if (bunceNum <= 0)
    {
        return Vector3d(0, 0, 0);
    }


    double minTimes = 99999;
    int  id = 0;
    for (int i = 0; i < spheres.size(); i++)
    {
        bool temp = spheres[i].hitSphere(r, 0.00001, 99999);
        if (temp)//如果打到了东西，就更新时间
        {
            double x = spheres[i].getTimeOfTwo();
            if (x < minTimes)
            {
                minTimes = x;
                id = i;
            }

        }

    }

    if (minTimes < 99999)
    {
      ///  cout << "进入该处" << endl;
        //Vector3d target = r.getTimeRay(spheres[id].getTimeOfTwo()) + spheres[id].getNormal() + randomVector();
        ray rx;
        
        /*if (spheres[id].getPointer()==NULL)
        {
            cout << "id是" << id << endl;

        }
        else
        {
            cout << "不是空指针" << endl;
        }*/




        if (spheres[id].getMaterial().scatter(r, spheres[id], rx))
        {
            return spheres[id].getMaterial().absordLight(color(rx, spheres, bunceNum - 1));
                
                //0.5 * color(rx, spheres, bunceNum - 1);
        }
            //= ray(r.getTimeRay(spheres[id].getTimeOfTwo()), target - r.getTimeRay(spheres[id].getTimeOfTwo()));
       
       
        //这里调用球本身的性质来计算散射
        /*ray rx = spheres[id].getMaterial().scatter(r, spheres, id);*/
        else

        {
            return Vector3d(0, 0, 0);
        }



    }
    else
    {
       // cout<<"else"<<endl;
        Vector3d unit = r.getDirection().normalized();
        double t = 0.5 * (unit.y() + 1);
        return (1 - t) * Vector3d(1.0, 1.0, 1.0) + t * Vector3d(0.5, 0.7, 1.0);
    }


}



