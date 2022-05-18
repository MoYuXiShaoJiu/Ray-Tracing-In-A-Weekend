# Ray Tracing In A weekend
## 说明：

本文是对学习完 [Ray Tracing In A weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)之后的一个简单总结与分享

同时感谢牛仔学长(Cowboy)对本文提出的宝贵建议。

## 废话：

其实在学习Ray Tracing In A weekend之前，学习了一段时间的OpenGL，相比之下，我还是觉得Ray Tracing In A weekend要来的有意思多了。

## 源代码： [代码](https://github.com/MoYuXiShaoJiu/Ray-Tracing-In-A-Weekend)

代码放在了github上，需要自取，当然就我自己看来代码质量堪忧www
同时这个代码有一点小问题，最后渲染出来的随机球的颜色都是绿色的，应该是随机函数的问题，不过到这一步已经懒得去处理了（懒狗.jpg）

## 关于文件：
camera.h是相机所用头文件，包含了在defocus blur之前的所有相机的操作

xiangji.h是相机所用头文件，包含了defocus blur的操作


color.h是针对球的不同性质获取颜色的color函数的头文件


material.h是包含了球的材质类的头文件

random.h是包含了生成本次内容所需的随机数的头文件

sphere.h是球所用的类

hitSphere.cpp是main函数和最后渲染场景的生成函数所在的源文件

## 结果

[图片](raytracing.png)

结果本身存在一点小问题，在图片中可以看到，这里所有的随机生成的漫反射的球都是绿色的，且所有的金属材质的球都是金色的。如上所说这应该是随机函数的问题。

同时还有一个较为显著的问题是图中球的数量显著少于教程中最后给出来的球的数量，这是为了减少程序运行的时间，当然如果使用cuda加速的话，能显著提升运行的速度。

有大佬已经做了这样的工作 [利用cuda加速计算Ray Tracing In A Weekend](https://github.com/rogerallen/raytracinginoneweekendincuda)。




## 问题
总的来说我认为从材质开始才会出现一些小问题，在此之前的内容并不困难。

### 向量
我使用了Eigen库来替代教程中的vec3和color等类。Eigen库详见 [Eigen](https://eigen.tuxfamily.org/dox/group__TutorialMatrixArithmetic.html)

### PPM

参见我的上一篇博客

### 光线追踪的思想

整篇教程中最重要的就是color函数中的递归调用，当然还包括通过参数的调整来模拟光线的吸收。

games101中有提到这部分。

### 金属
这部分是简单的一个向量运算，本身并不复杂。


### 折射
我碰到的问题是在折射的那一章中，忽略了判断光线的位置，直接使用了eta作为折射的参数，而原文中使用了一次法向量和方向向量的点乘的正负作为判断的依据，来判断到底是从空气入射玻璃还是从玻璃中射出，但是由于snell定律，从玻璃中射出是无解的，故进入了全反射，这里还是非常有意思的设计。

### defocus blur（景深）
这部分理解起来我认为不如前面的章节来的直接，这一篇[博客](https://blog.csdn.net/libing_zeng/article/details/54561271)的图要来的更加直接。理解之后写起来就快很多。





