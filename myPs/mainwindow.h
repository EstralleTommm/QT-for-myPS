#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtWidgets>
#include <QDebug>
#include <tlm.h>
#include <paintwidget.h>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <videosurface.h>
#include <QTextEdit>

class QMediaPlayer;
class QVideoWidget;
class Tlm;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    std::vector<std::vector<QImage>> imgVector;	// 存储图像的Vector容器
    std::vector<QImage>::iterator iter;			// Vector迭代器
    QToolBar* toolBar;                          //绘图工具栏

    void ShowImage(QImage Img, bool isSave);	// 显示图像

    void output(QString information);           //输出

    void UpdateProp(QImage src);				// 更新属性

    void UpdateImgName(QString name);			// 更新图像地址


private slots:
    void Imagezhen();                           //帧选择

    void videoTimer();                          //计时器

    void ImageVideoPro();                       //图片视频预览

    void ImageVideoStop();                      //图片视频停止

    void ImageVideoPlay();                      //图片视频播放

    void ProcessFrame(QVideoFrame &frame);           //取帧

    void updatePosition(qint64 postion);        //更新播放进度滑块

    void setPosition(int position);                          //设置播放进度

    void videoPlay();                           //视频播放

    void videoStop();                           //视频停止

    void binSliderImage();                      //滑条二值化

    void penWidth();                            //画笔宽度

    void penColor();                            //画笔颜色

    void toolButtonClicked(int id);             //绘图按钮组

    void changeLanguage();                      //语言切换

    void whiteLayout();                         //白色布局

    void blackLayout();                         //黑色布局

    void option();                      //设置

    void on_new_2_triggered();

    void on_open_triggered();

    void on_save_triggered();

    void on_saveAs_triggered();

    void grayImage();                   //灰度变换

    void binImageOK();                  //二值化变换

    void on_action_28_triggered();

    void on_action_27_triggered();

    void on_action_3_triggered();

    void on_action_4_triggered();

    void averageImage();                //均值滤波

    void gammaImage();					// 伽马变换

    void expImage();                    //指数变换

    void medianImage();                 //中值滤波

    void gaussianImage();               //高斯滤波

    void flipImage_H();                 //水平翻转

    void flipImage_V();                 //垂直翻转

    void sobelImage();                  //sebel算子 3x3

    void laplacianImage();              //Laplacian算子 3x3

    void changeImageSize();             //设置图片大小

    void autoSize();                    //默认窗口大小

    void enlargeReduce();             //缩放

    void rotateImage();                 //旋转

    void histeqImage();                 //灰度直方图均值化

    void rotateImage_270();             //顺时针旋转90°

    void rotateImage_90();              //逆时针旋转90°

    void rotateImage_180();             //旋转180°

    void linearImage();                 //线性变换

    void reverseImage();                //图像反转

    void splitR();                      //R分量图

    void splitG();                      //G分量图

    void splitB();                      //B分量图

    void on_action_49_triggered();

    void on_action_22_triggered();

    void on_action_23_triggered();

    void on_action_5_triggered();

    void on_action_6_triggered();

    void on_close_triggered();

    void on_action_24_triggered();

    void on_action_25_triggered();

    void on_action_26_triggered();

    void on_action_29_triggered();

    void on_action_30_triggered();

    void on_action_32_triggered();

    void on_action_33_triggered();

    void on_action_34_triggered();

    void on_action_39_triggered();

    void on_action_40_triggered();

    void on_action_41_triggered();

    void on_actionSobel_triggered();

    void on_actionLaplacian_triggered();

    void on_actionCanny_triggered();

    void on_actionR_triggered();

    void on_actionG_triggered();

    void on_actionB_triggered();

    void on_action_7_triggered();

    // 检测各窗口是否打开
    //void isDockImage();
    void isDockTool();
    void isDockOutput();
    void isDockProp();
    void isDockGeom();
    void isDockGray();
    void isDockEnhance();
    void isDockColor();

    void on_action_12_triggered();

    void on_action_13_triggered();

    void on_action_8_triggered();

    void on_action_9_triggered();

    void on_action_10_triggered();

    void on_action_11_triggered();

    void on_action_50_triggered();

    void on_action_20_triggered();

    void on_action_21_triggered();

    void on_action_triggered();

    void on_action_2_triggered();

private:
    Ui::MainWindow *ui;
    Tlm *tom;
    QTranslator m_qtTranslator;

    QDockWidget* dock_Image;// 图像窗口
    QDockWidget* dock_Image1;//多图像窗口
    QDockWidget* dock_video;//视频窗口
    QDockWidget* dock_image_video;
    QDockWidget* dock_Tool;// 工具箱窗口
    QDockWidget* dock_Geom;// 几何变换窗口
    QDockWidget* dock_Gray;// 灰度变换窗口
    QDockWidget* dock_Enhance;// 图像增强窗口
    QDockWidget* dock_Color;// 颜色模型窗口
    QDockWidget* dock_Prop;// 属性窗口
    QDockWidget* dock_Output;// 输出窗口

    QScrollArea* ImgscrollArea;					// 图像窗口滑动条

    //工具箱
    void WinTool();                             // 工具栏
    QButtonGroup *toolButtonGroup;
    int drawType;

    //几何变换窗口
    void WinGeom();
    QSpinBox *spinbox_size;						// 缩放微调框
    QSpinBox *spinbox_rotate;					// 旋转微调框
    QSpinBox *spinbox_leanX, *spinbox_leanY;	// 图像移动距离
    QLineEdit *line_L, *line_W;					// 设置长宽
    QSpinBox *line_times;
    QSpinBox *line_degree;
    QSpinBox *line_leanX, *line_leanY;			// 倾斜角度

    //灰度变换窗口
    void WinGray();
    QSpinBox *spinbox_bin;
    QSpinBox *spinbox_alpha, *spinbox_beta;		// 图像灰度变换
    QSpinBox *spinbox_gamma, *spinbox_c;		// 图像灰度变换
    QSpinBox *line_bin;
    QSpinBox *line_beta;
    //QSpinBox *line_c;
    QDoubleSpinBox *line_gamma,*line_c,*line_alpha;

    //图像增强窗口
    void WinEnhance();
    QSpinBox *spinbox_canny;					// canny微调框
    QSpinBox *spinbox_lineThreshold, *spinbox_minLineLength, *spinbox_maxLineGap;// Line
    QSpinBox *spinbox_minRadius, *spinbox_maxRadius;	// circle
    QComboBox *combo_smooth, *combo_sharpen;	// 下拉选择框

    //颜色模型窗口
    void WinColor();

    // 属性窗口
    void WinProp();
    QLineEdit *line_img;
    QLineEdit *line_length;
    QLineEdit *line_width;
    QLineEdit *line_depth;
    QLineEdit *line_isGray;

    //输出窗口
    QTextEdit *outputEdit;						// 输出框

    // Help
    QRadioButton *whiteRadio, *blackRadio;
    QPushButton *langButton;
    bool m_bTranslator = true;                  //是否是中文
    bool isSkin;								// 是否切换成黑色皮肤

    // 绘图工具栏
    void ColorToolBar();                        //绘图工具栏
    QSpinBox *spinbox_penWidth;                 //线宽
    QFrame *frame_color;                        //画笔颜色

    QString currentPath;                        // 当前图像的路径
    PaintWidget *imgLabel;                           // 图像显示框
    QLabel *imgLabel1;
    void InitImage();                           // 初始化图像

    QImage pro;     //原始图像

    //视频播放
    QMediaPlayer *player;   //播放player
    QMediaPlayer *playerIn;   //取帧player
    QVideoWidget *videoWidget;
    QString videoCurrentPath;
    bool isPlay;            //是否播放
    QPushButton *button_go; //播放按钮

    QSlider *slider_video;  //播放滑块
    VideoSurface *videoSurface;//取帧
    QPushButton *button_Image_go; //图片播放按钮
    bool imageIsPlay;

    QImage imageVideo[1000];
    int counter;//帧数
    long time;
    QTimer *timer;
    int zhenshu;
    QLabel *label_time_in; // 显示时间
    QLabel *label_zhen_in;
    int editCounter;
    int counters[100];
    QImage editeImageVideo[100];
    QSpinBox *zhen_edit;
};

#endif // MAINWINDOW_H
