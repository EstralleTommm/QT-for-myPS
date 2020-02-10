#include "tlm.h"

Tlm::Tlm()
{

}

Tlm::~Tlm()
{

}
// 灰度化处理
QImage* Tlm::Graylevel(QImage img)
{
    int r,g,b,gray;
    QImage* grayImg = new QImage(img.width(), img.height(), QImage::Format_Grayscale8);
    for (int i = 0; i < img.width(); i++)
    {
        for (int j= 0; j < img.height(); j++)
        {
            //自带方法 Gray = (R * 11 + G * 16 + B * 5)/32
            /*QRgb color = img.pixel(i, j);
            int gray = qGray(color);
            img.setPixel(i, j, qRgba(gray, gray, gray, qAlpha(color)));*/

            //Gray = Gray=（R+G+B）/3
            r = qRed(img.pixel(i, j));
            g = qGreen(img.pixel(i, j));
            b = qBlue(img.pixel(i, j));
            gray = (r+g+b)/3;
            grayImg->setPixel(i, j, qRgb(gray, gray, gray));
        }
    }
    return grayImg;
}
// 二值化处理
QImage* Tlm::TowValue(QImage img, int value)
{
    int r,g,b,gray;
    QImage* grayImg = new QImage(img.width(), img.height(), QImage::Format_Grayscale8);
    for (int i = 0; i < img.width(); i++)
    {
        for (int j= 0; j < img.height(); j++)
        {
            r = qRed(img.pixel(i, j));
            g = qGreen(img.pixel(i, j));
            b = qBlue(img.pixel(i, j));
            gray = (r+g+b)/3;
            if(gray<value){
                grayImg->setPixel(i, j, qRgb(0, 0, 0));
            }else{
                grayImg->setPixel(i, j, qRgb(255, 255, 255));
            }
        }
    }
    return grayImg;
}

// 均值滤波
QImage Tlm::averageImage(QImage img, int length)
{
    int r,g,b;
    QImage averageImg = img;
    QRgb rgb = 0;
    for(int x = length/2; x < img.width() - (length/2); ++x)
    {
        for(int y = length/2; y < img.height() - (length/2); ++y)
        {
            r = 0;
            g = 0;
            b = 0;
            for(int i = 0; i < length; i++)
            {
                for(int j = 0;j < length; j++)
                {
                    rgb = img.pixel(x-length/2+i, y-length/2+j);
                    r += qRed(rgb);
                    g += qGreen(rgb);
                    b += qBlue(rgb);
                }
            }
            r /= length*length;
            g /= length*length;
            b /= length*length;
            averageImg.setPixel(x, y, QColor(r, g, b).rgb());
        }
    }
    return averageImg;
}

// 中值滤波
QImage Tlm::medianImage(QImage img, int length)
{
    int len = length * length;
    int mode[len];
    int g[len];
    int b[len];
    QImage averageImg = img;
    QRgb rgb = 0;
    for(int x = length/2; x < img.width() - (length/2); ++x)
    {
        for(int y = length/2; y < img.height() - (length/2); ++y)
        {
            for(int i = 0; i < length; i++)
            {
                for(int j = 0;j < length; j++)
                {
                    rgb = img.pixel(x-length/2+i, y-length/2+j);
                    mode[i * length + j] = qRed(rgb); //二维数组下标转换为一维数组下标
                    g[i * length + j] = qGreen(rgb);
                    b[i * length + j] = qBlue(rgb);
                }
            }
            bubbleSort(mode, len);
            bubbleSort(g, len);
            bubbleSort(b, len);
            averageImg.setPixel(x, y, QColor(mode[len/2], g[len/2], b[len/2]).rgb());
        }
    }
    return averageImg;
}

//冒泡排序
void Tlm::bubbleSort(int arr[], int n)
{
    for(int i = 0;i < n;i++){
        //比较两个相邻的元素
        for(int j = 0;j < n-i-1;j++){
            if(arr[j] > arr[j+1]){
                int t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t;
            }
        }
    }
}

// 指数变换
QImage* Tlm::expImage(QImage img,double t)
{
    QImage* expImg = new QImage(img.width(), img.height(), img.format());
    QRgb rgbVal = 0;
    for (int x = 0; x < img.width(); ++x)
    {
        for (int y = 0; y < img.height(); ++y)
        {
            rgbVal = img.pixel(x, y);
            double a2 = qRed(rgbVal);
            double a3 = qGreen(rgbVal);
            double a4 = qBlue(rgbVal);

            a2 = pow(a2, t);
            a3 = pow(a3, t);
            a4 = pow(a4, t);

            if (a4 >= 255)
            {
               a4 = 255;
            }
            if (a3 >= 255)
            {
               a3 = 255;
            }
            if (a2 >= 255)
            {
               a2 = 255;
            }
           expImg->setPixel(x, y, QColor(a2,a3,a4).rgb());
        }
    }
    return expImg;
}

// 伽马变换
QImage* Tlm::gammaImage(QImage img,double gamma)
{
    double fNormalFactor  = 1.0 / 255.0;
    QRgb rgbVal = 0;
    QImage* gammaImg = new QImage(img.width(), img.height(), img.format());
    for (int x = 0; x < img.width(); x++)
    {
        for (int y = 0; y < img.height(); y++)
        {
            rgbVal = img.pixel(x, y);
            double a2 = qRed(rgbVal);
            double a3 = qGreen(rgbVal);
            double a4 = qBlue(rgbVal);

            a2 = pow(a2 * fNormalFactor, gamma);
            a3 = pow(a3 * fNormalFactor, gamma);
            a4 = pow(a4 * fNormalFactor, gamma);

            a2 = a2 > 1.0f ? 1.0f : a2;
            a3 = a3 > 1.0f ? 1.0f : a3;
            a4 = a4 > 1.0f ? 1.0f : a4;

           gammaImg->setPixel(x, y, QColor(a2 * 255.0, a3 * 255.0, a4 * 255.0).rgb());
        }
    }
    return gammaImg;
}

// 旋转90°
QImage* Tlm::spin(QImage _img,bool t)
{
    int nWidth = _img.width();
    int nHeight = _img.height();

    QImage* smoothImg = new QImage(nHeight, nWidth, _img.format());
    QRgb rgbVal = 0;
    int arrx2;
    int stepx2;
    int arry2;
    int stepy2;
    if(t){
        arrx2=0;
        stepx2=1;
        arry2=nHeight-1;
        stepy2=-1;
    }else{
        arrx2=nWidth-1;
        stepx2=-1;
        arry2=0;
        stepy2=1;
    }
    int y2=arry2;
    for (int x = 0; x < nHeight; ++x)
    {
        int x2=arrx2;
        for (int y = 0; y < nWidth; ++y)
        {
           //rgbVal = _img->pixel(x, y);
           rgbVal = _img.pixel(x2, y2);
           smoothImg->setPixel(x, y, QColor(qRed(rgbVal),qGreen(rgbVal),qBlue(rgbVal)).rgb());
           x2+=stepx2;
        }
        y2+=stepy2;
    }
    return smoothImg;
}

// 翻转
QImage* Tlm::symmetry(QImage img, bool t)
{
    int nWidth = img.width();
    int nHeight = img.height();
    QImage* smoothImg = new QImage(nWidth, nHeight, img.format());
    QRgb rgbVal = 0;
    int arrx2;
    int stepx2;
    int arry2;
    int stepy2;
    if(t){
        arrx2=0;
        stepx2=1;
        arry2=nHeight-1;
        stepy2=-1;
    }else{
        arrx2=nWidth-1;
        stepx2=-1;
        arry2=0;
        stepy2=1;
    }
    int x2=arrx2;
    for (int x = 0; x < nWidth; ++x)
    {
        int y2=arry2;
        for (int y = 0; y < nHeight; ++y)
        {
           rgbVal = img.pixel(x2, y2);
           smoothImg->setPixel(x, y, QColor(qRed(rgbVal),qGreen(rgbVal),qBlue(rgbVal)).rgb());
           y2+=stepy2;
        }
        x2+=stepx2;
    }
    return smoothImg;
}

// RGB增量
QImage* Tlm::filter(QImage _img,int r,int g,int b)
{
    int nWidth = _img.width();
    int nHeight = _img.height();
    QImage* smoothImg = new QImage(nWidth, nHeight, _img.format());
    QRgb rgbVal = 0;
    int red;
    int green;
    int blue;
    for (int x = 0; x < nWidth; ++x)
    {
        for (int y = 0; y < nHeight; ++y)
        {
           rgbVal = _img.pixel(x, y);
           red=qRed(rgbVal)+r;
           if(red>255) red=255;
           green=qGreen(rgbVal)+g;
           if(green>255) green=255;
           blue=qBlue(rgbVal)+b;
           if(blue>255) blue=255;
           smoothImg->setPixel(x, y, QColor(red,green,blue).rgb());
        }
    }

    return smoothImg;
}

// Sobel算子 3x3
QImage Tlm::my_sobelImage(QImage img, int key)
{
    QImage* g = Graylevel(img);
    QImage dealImg = averageImage(*g, 3);
    QImage sobelImg = dealImg.copy(0,0,dealImg.width()-1,dealImg.height()-1);
    int length = 3;
    //QRgb keya = key;

    for(int x = length/2; x < img.width() - (length/2); ++x)
    {
        for(int y = length/2; y < img.height() - (length/2); ++y)
        {

            QRgb f00 = dealImg.pixel(x - 1, y - 1);
            QRgb f01 = dealImg.pixel(x - 1, y);
            QRgb f02 = dealImg.pixel(x - 1, y + 1);

            QRgb f10 = dealImg.pixel(x, y - 1);
            QRgb f12 = dealImg.pixel(x, y + 1);

            QRgb f20 = dealImg.pixel(x + 1, y - 1);
            QRgb f21 = dealImg.pixel(x + 1, y);
            QRgb f22 = dealImg.pixel(x + 1, y + 1);

            QRgb Dx = (f20 - f00) + 2 * (f21 - f01) + (f22 - f02);
            QRgb Dy = (f02 - f00) + 2 * (f12 - f10) + (f22 - f20);
            QRgb result = sqrt(pow(Dx,2) * pow(Dy,2));

            sobelImg.setPixel(x, y, result>(QRgb)key?result:qRgb(255,255,255));
        }
    }
    return sobelImg;
}

// Laplacian算子 3x3
QImage Tlm::laplaImage(QImage img, int key)
{
    QImage* g = Graylevel(img);
    QImage dealImg = averageImage(*g, 3);
    QImage laplaImg = dealImg.copy(0,0,dealImg.width()-1,dealImg.height()-1);
    int length = 3;
    //QRgb keya = key;
    for(int x = length/2; x < img.width() - (length/2); ++x)
    {
        for(int y = length/2; y < img.height() - (length/2); ++y)
        {
            QRgb f01 = dealImg.pixel(x - 1, y);

            QRgb f10 = dealImg.pixel(x, y - 1);
            QRgb f11 = dealImg.pixel(x, y);
            QRgb f12 = dealImg.pixel(x, y + 1);

            QRgb f21 = dealImg.pixel(x + 1, y);

            QRgb result = 4 * f11 - f01 - f21 - f10 - f12;

            laplaImg.setPixel(x, y, result>(QRgb)key?result:qRgb(0,0,0));
        }
    }
    return laplaImg;
}

// 线性变换
QImage Tlm::linearImage(QImage img, double k, int b)
{
    QRgb rgbVal = 0;
    QImage* linearImg = new QImage(img.width(), img.height(), img.format());
    for (int i = 0; i < img.width(); i++)
    {
        for (int j= 0; j < img.height(); j++)
        {
            rgbVal = img.pixel(i, j);
            int a2 = qRed(rgbVal);
            int a3 = qGreen(rgbVal);
            int a4 = qBlue(rgbVal);

            a2 = k * a2 + b;
            a3 = k * a3 + b;
            a4 = k * a4 + b;

            if (a4 >= 255)
            {
               a4 = 255;
            }
            if (a3 >= 255)
            {
               a3 = 255;
            }
            if (a2 >= 255)
            {
               a2 = 255;
            }

            if (a4 <= 0)
            {
               a4 = 0;
            }
            if (a3 <= 0)
            {
               a3 = 0;
            }
            if (a2 <= 0)
            {
               a2 = 0;
            }
           linearImg->setPixel(i, j, QColor(a2,a3,a4).rgb());
        }
    }
    return *linearImg;
}

// 图像反转
QImage Tlm::reverseImage(QImage img)
{
    int r,g,b;
    QImage* reverseImg = new QImage(img.width(), img.height(), img.format());
    for (int i = 0; i < img.width(); i++)
    {
        for (int j= 0; j < img.height(); j++)
        {
            r = qRed(img.pixel(i, j));
            g = qGreen(img.pixel(i, j));
            b = qBlue(img.pixel(i, j));

            //方式一
            /*r = 255 - r;
            g = 255 - g;
            b = 255 - b;*/

            //方式二
            r = ~r;
            g = ~g;
            b = ~b;
           reverseImg->setPixel(i, j, qRgb(r, g, b));
        }
    }
    return *reverseImg;
}

// 灰度直方图均值化
QImage Tlm::histeqImage(QImage img)
{
    double data[256] = {0.0};           //直方图
    double pr[2][256] = {0.0};          //概率分布
    int r,g,b,gray,result;
    QImage* histeqImg = new QImage(img.width(), img.height(), img.format());
    //统计灰度直方图
    for (int i = 0; i < img.width(); i++)
    {
        for (int j= 0; j < img.height(); j++)
        {
            r = qRed(img.pixel(i, j));
            g = qGreen(img.pixel(i, j));
            b = qBlue(img.pixel(i, j));
            gray = (r+g+b)/3;
            data[gray]++;
        }
    }
    //计算出累计概率
    for(int i = 0; i <= 255; i++)
    {
        pr[0][i] = data[i] / (img.width() * img.height());

        for(int j = 0; j <= i; j++)
        {
            pr[1][i] += pr[0][j];
        }
    }
    //绘图
    for (int i = 0; i < img.width(); i++)
    {
        for (int j= 0; j < img.height(); j++)
        {
            r = qRed(img.pixel(i, j));
            g = qGreen(img.pixel(i, j));
            b = qBlue(img.pixel(i, j));
            gray = (r+g+b)/3;
            result = (int)(pr[1][gray] * 255);
            histeqImg->setPixel(i, j, qRgb(result, result, result));
        }
    }
    return *histeqImg;
}

// Sobel算法
QImage Tlm::sobelImage(QImage image, int key){
    int height ,width;
    QColor c;
    width=image.width();
    height=image.height();
    int pixel[width][height];
    double Gx,Gy,G;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            c = image.pixel(j,i);
            pixel[j][i] = (c.red()+c.green()+c.blue())/3;
        }
    }
    for(int i = 1; i < height - 1; i++)
    {
        for(int j = 1; j < width - 1; j++)
        {
            Gx=pixel[j - 1][i - 1]*(-1) + pixel[j - 1][i]*(-2) + pixel[j - 1][i + 1]*(-1) + pixel[j][i - 1]*0 + pixel[j][i]*0
                    + pixel[j][i + 1]*0 + pixel[j + 1][i - 1]*1 + pixel[j + 1][i]*2 + pixel[j + 1][i + 1]*1;
            Gy=pixel[j - 1][i - 1]*1 + pixel[j - 1][i]*0 + pixel[j - 1][i + 1]*(-1) + pixel[j][i - 1]*2 + pixel[j][i]*0
                    + pixel[j][i + 1]*(-2) + pixel[j + 1][i - 1]*1 + pixel[j + 1][i]*0 + pixel[j + 1][i + 1]*(-1);
           G=abs(Gx)+abs(Gy);
           image.setPixel(j, i, G>key?qRgb(255,255,255):qRgb(0,0,0));
        }
    }
    return image;
}

// 高斯滤波
/*QImage Tlm::gaussImage(QImage image)
{
    int height, width;
    QColor c;
//    QImage image(s);
    width = image.width();
    height = image.height();
    int pixel[width][height];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            c = image.pixel(j,i);
            pixel[j][i] = (c.red()+c.green()+c.blue())/3;
        }
    }
    for(int i = 1; i < height - 1; i++)
    {
        for(int j = 1; j < width - 1; j++)
        {
            pixel[j][i] =pixel[j - 1][i - 1]*0.0947416 + pixel[j - 1][i]*0.118318 + pixel[j - 1][i + 1]*0.0947416 + pixel[j][i - 1]*0.118318 + pixel[j][i]*0.147761
                    + pixel[j][i + 1]*0.118318 + pixel[j + 1][i - 1]*0.0947416 + pixel[j + 1][i]*0.118318 + pixel[j + 1][i + 1]*0.0947416;
            image.setPixel(j, i, qRgb(pixel[j][i], pixel[j][i], pixel[j][i]));
        }
    }
    //newImage = image;
    return image;
}*/

// 高斯滤波
QImage Tlm::gaussImage(QImage img, int length, double sigma)
{
    int r, g, b;
    double e = 2.71828;
    double pi = 3.14159;
    double data[length][length];
    double sum = 0.0;
    QRgb rgb = 0;
    QImage gaussImg = img;

    for(int i = -length/2; i <= length/2; i++)
    {
        for(int j = -length/2; j <= length/2; j++)
        {
            data[i+length/2][j+length/2] = pow(e,(-(i*i + j*j))/(2*sigma*sigma)) / (2*pi*sigma*sigma);
            sum += data[i+length/2][j+length/2];
            //qDebug("%f",data[i+length/2][j+length/2]);
        }
    }
    //qDebug("%f",sum);
    for(int x = length/2; x < img.width() - (length/2); x++)
    {
        for(int y = length/2; y < img.height() - (length/2); y++)
        {
            r = 0;
            g = 0;
            b = 0;
            for(int i = 0; i < length; i++)
            {
                for(int j = 0;j < length; j++)
                {
                    rgb = img.pixel(x-length/2+i, y-length/2+j);
                    r += (int)(qRed(rgb) * data[i][j]/sum);
                    g += (int)(qGreen(rgb) * data[i][j]/sum);
                    b += (int)(qBlue(rgb) * data[i][j]/sum);
                }
            }
            gaussImg.setPixel(x, y, qRgb(r, g, b));
        }
    }
    return gaussImg;
}

//提取RGB分量
QImage Tlm::splitBGR(QImage img, int color)			// 提取RGB分量
{
    int r,g,b;
    QRgb rgb = 0;
    QImage* RImg = new QImage(img.width(), img.height(), img.format());
    for (int i = 0; i < img.width(); i++)
    {
        for (int j= 0; j < img.height(); j++)
        {
            rgb = img.pixel(i, j);
            r = qRed(rgb);
            g = qGreen(rgb);
            b = qBlue(rgb);
            switch (color) {
            case 0:
                RImg->setPixel(i, j, QColor(r, 0, 0).rgb());
                break;
            case 1:
                RImg->setPixel(i, j, QColor(0, g, 0).rgb());
                break;
            case 2:
                RImg->setPixel(i, j, QColor(0, 0, b).rgb());
                break;
            default:
                break;
            }
        }
    }
    return *RImg;
}
