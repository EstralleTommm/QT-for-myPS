# QT-for-myPS
C++桌面应用程序，实现各种图像处理算法
# 概述

实现一个简易图形处理软件，并且能播放视频，取出其中一帧进行处理。

翻出来了陈年老书，看了很多图像处理算法，大部分实现了。部分操作的响应时间较长，有待优化。

具体报告和实现源码已放置github[点击此处进入](https://github.com/EstralleTommm/QT-for-myPS)

# 实现功能

实现图像处理软件的基本功能，其中包括，
`几何变换：` 图像大小变换、图像缩放、图像旋转、图像翻转；
`灰度变换：`线性变换、指数变换、伽马变换、二值图、灰度图、图像反转，直方图均值化；
`图像增强：`可调模板大小的均值滤波、高斯滤波、中值滤波， sobe 边缘检测、laplacian检测；
`RGB 模型：` R 分量图， G 分量图， B 分量图；
`绘画：`可以通过画笔、直线和各种形状（圆、三角、长方形等） 在图像上进行绘画并保存，可以调节画笔线宽和颜色；
`输出窗口：`显示操作记录;
`属性窗口：`图像基本信息；
`其他：`各种窗口部件的隐藏和显示、全屏、关于、设置、皮肤切换、语言转换、跨平台等  ;



# 实现的过程与步骤

### 1.界面设计

主界面由菜单栏，工具栏，以及工具箱、图像、几何变换、灰度变换、图像增强、颜色模型、输出、属性九个Dock窗口；其中图像窗口为主窗口且不可关闭，几何变换、灰度变换、图像增强、颜色模型合并，默认几何窗口显示最前端。输出、属性窗口合并，默认输出窗口显示在最前端；

工具栏包括新建、打开、保存、另存为、撤销、重做、画笔宽度、画笔颜色等

菜单栏包括文件、编辑、视图、几何变换、灰度变换、图像增强、颜色模型、帮助；

 

### 2.几何变换

`图像大小：`设置宽高，通过scaled(int width, int height)完成；

`图像缩放：`倍数放大缩小，通过scaled(int width, int height)完成；

`图像旋转：`旋转的角度，QMatrix对象rotate(qreal degrees)完成；

`图像翻转：`将图像水平或竖直翻转，Tlm类中symmetry(QImage img,bool t);

 

### 3.灰度变换

`线性变换：`通过y = kx+b对像素点处理，Tlm类中linearImage(QImage img, double k, int b)完成；

`指数变换：`通过y = x^a对像素点处理，Tlm类中expImage(QImage img,double t)完成

`伽马变换：`通过y = cr^gamma ，r范围为[0,1]对像素点处理，Tlm类中gammaImage(QImage img,double gamma)完成；

`二值图像：`像素点灰度值和阈值比较，赋值白或黑，Tlm类中TowValue(QImage img, int value)完成；

`灰度图像：`通过Gray =(R+G+B)/3，赋值给像素点，Tlm类中Graylevel(QImage src)完成；

`反转变换：`通过对像素点取反对像素点进行处理，Tlm类中reverseImage(QImage img)完成

`直方图均值化：`见主要算法一栏；

 

### 4.图像增强

**图像平滑：**

   `均值滤波：`将模板像素点取平均，赋给中心点；Tlm类中averageImage(QImage src, int length)完成；

   `高斯滤波：`将模板像素点通过二维高斯函数加权计算后赋给中心点，Tlm类中gaussImage(QImage image, int length, double sigma)完成；

   `中值滤波：`将模板像素点排序，取中间值赋给中间点，Tlm类中medianImage(QImage src, int length)完成；

**图像锐化：**

   `Sobel边缘检测：`通过sobel算子对图像进行边缘检测，Tlm类中sobelImage(QImage image, int key)完成；（详细过程见“主要算法”一栏）

   `Laplacian边缘检测：`用Laplacian算子对图像进行边缘检测，Tlm类中laplaImage(QImage img, int key)完成；

 

### 5.颜色模型

`RGB模型：`通过仅保留R、G或者B值，提取R、G、B分量图，Tlm类中splitBGR(QImage src, int color)完成；

 

### 6.输出窗口

通过QLabel的append方法，在每次图像处理后进行输出操作；

 

### 7.属性窗口

每次显示图片后更新图片信息；

 

### 8.绘图

通过paint类实现基本绘图功能；

 

### 9.其他功能（全屏、窗口部件隐藏显示、关于、设置、换皮肤、中英文转换）

`全屏：`通过showFullScreen()和showNormal()实现全屏和退出全屏；

`关于：`自定义窗口，显示软件信息和作者信息；

`设置：`自定义窗口，可进行皮肤切换、语言切换；

 

### 10.视频处理

创建视频播放Dock窗口和视频控制Dock窗口。播放窗口进行视频正常播放，可以停止、暂停、调节亮度、对比度、色相、饱和度；控制窗口是控制图片帧在label上的显示，可以通过暂停对这一帧进行上述图像各种处理，将修改后的图片帧保存，预览按钮可以播放刚刚修改过的视频，此外还能输入帧数进行查看。

11.发布名称、图标设置

略

### 12.跨平台

在Ubuntu虚拟机下载Qt以及配置插件等，对项目进行编译。即可运行


# 界面展示

![image-20200210201140179](http://wisdomclass.tech/blog/2020/0210/image-20200210201140179.png)



### 注：具体的效果和详细实现过程见github仓库中报告和源码
