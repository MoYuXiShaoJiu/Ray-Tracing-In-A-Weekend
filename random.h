#pragma once
#include<Eigen/Dense>
#include<cstdlib>
using namespace std;
using namespace Eigen;

double randomDouble();
Vector3d randomVector();
double randomPNDouble();

//创建一个用来返回随机的向量长度小于1的向量的函数
Vector3d randomVector()
{
    Vector3d rv;
    do
    {
        rv = 2 * Vector3d(randomDouble(), randomDouble(), randomDouble()) - Vector3d(1, 1, 1);


    } while (fabs(rv.dot(rv)) >= 1);
    return rv;
}

//创建一个用来返回double随机数的函数
double randomDouble()
{
    double  temp = 1000;
    return double(rand() % 1000) / temp;
}

double randomPNDouble()
{
    double temp = 1000;
    if (rand() % 2 == 0)
    {
        return -double(rand() % 1000) / temp;
    }
    else

        return double(rand() % 1000) / temp;
}


Vector3d randomInUnitDisk()
{
  /*  while (true)
    {
        Vector3d p = Vector3d(randomPNDouble(), randomPNDouble(), 0);
        if (p.dot(p) >= 1) continue;
        return p;
    }*/

    Vector3d p;
    do
    {
         p = 2*Vector3d(       (double)(rand()%100)/(double)100 , (double)(rand() % 100) / (double)100,               0)                         -Vector3d(1,1,0);
    } while (p.dot(p)>=1.0);
    return p;

}