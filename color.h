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
        //����Ĺ�����ֱ�ӵ���Ļ�ϵ�һ����ģ���Ϊ�����λ���ǣ�0��0��0��
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
//�����������һ�������˺ܶ����list�����������ʹ��zbuffer�����㣬ֻȡ��������Ǹ��Ǹ�ʱ���ֵ
//ͬʱ�����������λ�õ�ԭ�������ֵӦ�û���������

Vector3d color(ray r, vector<sphere> spheres)
{
    //��list�е�ÿһ�����󽻵㣬���ǽ�С���Ǹ����㣬����������Щ��������ѡ����С��ֵ
    //����Щֵ����һ��������
    vector<double>times;
    double minTimes = 99999;
    int  id = 0;
    for (int i = 0; i < spheres.size(); i++)
    {
        bool temp = spheres[i].hitSphere(r, 0, 99999);
        if (temp)//������˶������͸���ʱ��
        {
            double x = spheres[i].getTimeOfTwo();
            if (x < minTimes)
            {
                minTimes = x;
                id = i;
            }

        }

    }
    //�������ҳ��������ص�ʱ���ȴ򵽵�����
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
        if (temp)//������˶������͸���ʱ��
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
      ///  cout << "����ô�" << endl;
        //Vector3d target = r.getTimeRay(spheres[id].getTimeOfTwo()) + spheres[id].getNormal() + randomVector();
        ray rx;
        
        /*if (spheres[id].getPointer()==NULL)
        {
            cout << "id��" << id << endl;

        }
        else
        {
            cout << "���ǿ�ָ��" << endl;
        }*/




        if (spheres[id].getMaterial().scatter(r, spheres[id], rx))
        {
            return spheres[id].getMaterial().absordLight(color(rx, spheres, bunceNum - 1));
                
                //0.5 * color(rx, spheres, bunceNum - 1);
        }
            //= ray(r.getTimeRay(spheres[id].getTimeOfTwo()), target - r.getTimeRay(spheres[id].getTimeOfTwo()));
       
       
        //����������������������ɢ��
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



