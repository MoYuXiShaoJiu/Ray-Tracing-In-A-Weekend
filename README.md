# Ray Tracing In A weekend
### 说明：

本文是对学习完 [Ray Tracing In A weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)之后的一个简单总结与分享


#### 废话：

其实在学习Ray Tracing In A weekend之前，学习了一段时间的OpenGL，相比之下，我还是觉得Ray Tracing In A weekend要来的有意思多了。

### 源代码： [代码]（https://github.com/MoYuXiShaoJiu/Ray-Tracing-In-A-Weekend）

代码放在了github上，需要自取，当然就我自己看来代码质量堪忧www
同时这个代码有一点小问题，最后渲染出来的随机球的颜色都是绿色的，应该是随机函数的问题，不过到这一步已经懒得去处理了（懒狗.jpg）

#### 关于文件：
camera.h是相机所用头文件，包含了在defocus blur之前的所有相机的操作
xiangji.h是相机所用头文件，包含了defocus blur的操作
color.h是针对球的不同性质获取颜色的color函数的头文件
material.h是包含了球的材质类的头文件
random.h是包含了生成本次内容所需的随机数的头文件
sphere.h是球所用的类
hitSphere.cpp是main函数和最后渲染场景的生成函数所在的源文件

## 结果

！[结果](raytracing.png)




## 问题
也许从材质开始才会出现一些小问题，在此之前的内容并不困难
#### 折射
我碰到的问题是在折射的那一章中，忽略了判断光线的位置，直接使用了eta作为折射的参数，而原文中使用了一次法向量和方向向量的点乘的正负作为判断的依据，来判断到底是从空气入射玻璃还是从玻璃中射出，但是由于snell定律，从玻璃中射出是无解的，故进入了全反射，这里还是非常有意思的设计。

#### defocus blur（景深）
这部分理解起来我认为不如前面的章节来的直接，这一篇[博客](https://blog.csdn.net/libing_zeng/article/details/54561271)的图要来的更加直接。理解之后写起来就快很多。w
