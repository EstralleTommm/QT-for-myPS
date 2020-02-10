#ifndef TLM_H
#define TLM_H
#include <mainwindow.h>


class Tlm
{
public:
    Tlm();
    ~Tlm();

    QImage *Graylevel(QImage src);                  //灰度化
    QImage *TowValue(QImage src, int value);        //二值化
    QImage averageImage(QImage src, int length);    //均值滤波
    QImage medianImage(QImage src, int length);     //中值滤波
    void bubbleSort(int arr[], int n);              //冒泡排序
    QImage *expImage(QImage src, double length);    //指数变换
    QImage *gammaImage(QImage src, double length);  //伽马变换
    QImage *spin(QImage _img,bool t);               //90°旋转
    QImage *symmetry(QImage img,bool t);           //翻转
    QImage laplaImage(QImage img, int key);         //Laplacian算子 3x3
    QImage my_sobelImage(QImage img, int key);         //sobel算子 3x3
    QImage linearImage(QImage img, double k, int b);//线性变换
    QImage reverseImage(QImage img);                //图像反转
    QImage histeqImage(QImage img);                 //灰度直方图均值化
    QImage sobelImage(QImage image, int key);     //sobel算子 3x3
    QImage gaussImage(QImage image, int length, double sigma);               //高斯滤波

    QImage splitBGR(QImage src, int color);
    QImage* filter(QImage _img,int r,int g,int b);  //RGB分量增加

};

#endif // TLM_H
