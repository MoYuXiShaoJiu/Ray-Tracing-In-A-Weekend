// Sphere.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//使用vector容器来存储sphere类，解决了list的问题

#include <iostream>
#include<Eigen/Dense>
#include"Ray.h"
#include"sphere.h"
#include"camera.h"
#include<vector>
#include<cstdlib>
#include<math.h>
#include"color.h"
#include"random.h"
#include"material.h"
#include"xiangji.h"

using namespace std;
using namespace Eigen;
vector<sphere> finalSence();



int main()
{
    int nx = 400;
    int ny = 200;
    int maxBunceNum = 50;
    int samplePerPixel = 100;
    double R = cos(pi / 4);
    cout << "P3\n" << nx << " " << ny << "\n255\n";
    Vector3d leftCornerLower = Vector3d(-2, -1, -1);
    Vector3d horizontal(4.0, 0.0, 0.0);
    Vector3d vertical(0.0, 2.0, 0.0);
    Vector3d position(0.0, 0.0, 0.0);
    Vector3d lookfrom(13, 3, 2);
    Vector3d lookat(0, 0, 0);
    Vector3d vup(0, 1, 0);
    Vector3d tempVector = lookfrom - lookat;
    double distTofocus = sqrt(tempVector.dot(tempVector));
    double aperture = 0.1;
    camera cam(leftCornerLower, horizontal, vertical, position);
    camera cam1(90.0, double(nx)/double(ny));
    camera cam2(Vector3d(-2, 2, 1), Vector3d(0, 0, -1), Vector3d(0, 1, 0), 60, double(nx) / double(ny));
    camera cam3(lookfrom, lookat, vup, 45, double(nx)/double(ny), aperture, distTofocus);
    xiangji cam4(lookfrom, lookat, vup, 20, double(nx) / double(ny), aperture, distTofocus);

    vector<sphere> finalS;
    // ****************************************************************
    sphere list0(Vector3d(0, -1000, 0), 1000, lambertain(Vector3d(0.5, 0.5, 0.5)));
    sphere list1(Vector3d(0, 1, 0), 1, dielectric(1.5));
    sphere list2(Vector3d(-4, 1, 0), 1, lambertain(Vector3d(0.4, 0.2, 0.1)));
    sphere list3(Vector3d(4, 1, 0), 1, matal(Vector3d(0.7, 0.6, 0.5)));

    finalS.push_back(list0);
    finalS.push_back(list1);
    finalS.push_back(list2);
    finalS.push_back(list3);
    int i = 1;
    for (int a = -5; a < 5; a++)
    {
        for (int b = -5; b < 5; b++)
        {
            double chooseMat = randomDouble();
            Vector3d center(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());
            if (sqrt((center - Vector3d(4, 0.2, 0)).dot(center - Vector3d(4, 0.2, 0))) > 0.9)
            {

                if (chooseMat < 0.8)
                {
                    finalS.push_back(sphere(center, 0.2, lambertain(Vector3d(randomDouble() * randomDouble(), randomDouble() * randomDouble(), randomDouble() * randomDouble()))));
                }
                else if (chooseMat < 0.95)
                {
                    finalS.push_back(sphere(center, 0.2, matal(Vector3d(0.5 * (1 + randomDouble()), 0.5 * (1 + randomDouble()), 0.5 * randomDouble()))));
                }
                else
                {
                    finalS.push_back(sphere(center, 0.2, dielectric(1.5)));
                }

            }


        }
    }





    //*************************************************************************














    vector<sphere> Spheres;
    vector<sphere> Sp2;

    lambertain l1(Vector3d(0.8,0.8,0.2));
    lambertain l4(Vector3d(0.7, 0.2, 0.6));
    lambertain x1(Vector3d(1.0, 0.0, 0.0));
    lambertain x2(Vector3d(0.0, 0.0, 1.0));

    matal l2(Vector3d(0.8, 0.8, 0.8));
    matal l3(Vector3d(0.618, 0.618, 0.618));

    dielectric l5(1.5);

    sphere s1(Vector3d(0, 0, -1), 0.5,l4);
    sphere s2(Vector3d(0, -100.5, -1), 100,l1);
    sphere s3(Vector3d(-1, 0, -1), 0.5, l3);
    sphere s4(Vector3d(1, 0, -1), 0.5, l5);

    sphere y1(Vector3d(-R, 0, -1), R, x1);
    sphere y2(Vector3d(R, 0, -1), R, x2);

    Sp2.push_back(y1);
    Sp2.push_back(y2);

    Spheres.push_back(s1);
    Spheres.push_back(s2);
    Spheres.push_back(s3);
    Spheres.push_back(s4);

    for (int j=ny-1; j>=0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            Vector3d col;
            for (int k = 0; k < samplePerPixel; k++)
            {
                double x = double(rand() % 10000) / 10000;
                double y = double(rand() % 10000) / 10000;
                double u = (double(i) + x) / double(nx);
                double v = (double(j) + y) / double(ny);
                ray r = cam4.getRay(u, v);
                 col += color(r, finalS, maxBunceNum);

            }
            col /= (double)samplePerPixel;
            //col = Vector3d(sqrt(col.x()), sqrt(col.y()), sqrt(col.z()));
            //col=Vector3d(pow(col.x(),0.5), pow(col.y(), 0.5), pow(col.z(), 0.5))

            int ir = int(255.99 * sqrt(col.x()));
            int ig = int(255.99 * sqrt(col.y()));
            int ib = int(255.99 * sqrt(col.z()));
            cout << ir << " " << ig << " " << ib << "\n";
            
            
        }
    }

    
}


//vector<sphere> finalSence()
//{
//    
//    vector<sphere> finalS;
//    sphere list0( Vector3d(0, -1000, 0), 1000,  lambertain( Vector3d(0.5, 0.5, 0.5)));
//    sphere list1(Vector3d(0, 1, 0), 1,  dielectric(1.5));
//    sphere list2(Vector3d(-4, 1, 0), 1, lambertain(Vector3d(0.4, 0.2, 0.1)));
//    sphere list3(Vector3d(4, 1, 0), 1, matal(Vector3d(0.7, 0.6, 0.5)));
//
//    finalS.push_back(list0);
//    finalS.push_back(list1);
//    finalS.push_back(list2);
//    finalS.push_back(list3);
//    int i = 1;
//    for (int a = -5;a < 5; a++)
//    {
//        for (int b = -5; b < 5; b++)
//        {
//            double chooseMat = randomDouble();
//            Vector3d center(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());
//            if (sqrt((center - Vector3d(4, 0.2, 0)).dot(center - Vector3d(4, 0.2, 0))) > 0.9)
//            {
//
//                if (chooseMat < 0.8)
//                {
//                    finalS.push_back(sphere(center, 0.2, lambertain(Vector3d(randomDouble() * randomDouble(), randomDouble() * randomDouble(), randomDouble() * randomDouble()))));
//                }
//                else if (chooseMat < 0.95)
//                {
//                    finalS.push_back( sphere(   center, 0.2, matal(Vector3d(0.5 * (1 + randomDouble()), 0.5 * (1 + randomDouble()), 0.5 * randomDouble()))   )   );
//                }
//                else
//                {
//                    finalS.push_back(sphere(center, 0.2, dielectric(1.5)));
//                }
//
//            }
//
//
//        }
//    }
//    return finalS;
//}







