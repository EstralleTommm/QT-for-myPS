#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget* p = takeCentralWidget();   //删除中央窗体
    if (p)
        delete p;
    setDockNestingEnabled(true);        //允许嵌套dock

    InitImage();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::InitImage()        // 初始化图像
{
    imgVector.resize(2);

    // 初始化QDockWidget可移动隐藏的小窗口，
    dock_Image = new QDockWidget(tr("图像"), this);          //   图像

    dock_Image->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);         // 设置为可移动可浮动，但不可关闭
    dock_Image->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);  // 可移动范围：左右
    dock_Image->setMinimumSize(600, 600);   // 设置最小宽高

    dock_Tool = new QDockWidget(tr("工具箱"), this);           // 工具箱窗口,若想设置特征或移动范围，方法同上。
    dock_Geom = new QDockWidget(tr("几何变换"), this);          // 几何变换窗口
    dock_Gray = new QDockWidget(tr("灰度变换"), this);          // 灰度变换窗口
    dock_Enhance = new QDockWidget(tr("图像增强"), this);       // 图像增强窗口
    dock_Color = new QDockWidget(tr("颜色模型"), this);         // 颜色模型窗口
    dock_Prop = new QDockWidget(tr("属性"), this);                // 属性窗口

    // 输出窗口编辑框
    outputEdit = new QTextEdit();
    outputEdit->textCursor().movePosition(QTextCursor::End);		// 垂直滚动条自动跟踪到最底部
    outputEdit->setWordWrapMode(QTextOption::NoWrap);				// 水平滚动条
    outputEdit->setReadOnly(true);
    dock_Output = new QDockWidget(tr("输出"), this);          // 输出窗口
    dock_Output->setFeatures(QDockWidget::AllDockWidgetFeatures);
    dock_Output->setWidget(outputEdit);

    // 窗口大小
    dock_Tool->setFixedWidth(100);
    dock_Geom->setFixedWidth(450);
    dock_Geom->setMinimumHeight(400);
    dock_Gray->setFixedWidth(450);
    dock_Enhance->setFixedWidth(450);
    dock_Color->setFixedWidth(450);
    dock_Prop->setMinimumHeight(200);
    dock_Prop->setMaximumHeight(400);

    // 进行布局
    setCentralWidget(dock_Image);       // 指定为中心窗口
    addDockWidget(Qt::LeftDockWidgetArea, dock_Tool);
    addDockWidget(Qt::BottomDockWidgetArea, dock_Output);
    addDockWidget(Qt::RightDockWidgetArea, dock_Geom);
    addDockWidget(Qt::RightDockWidgetArea, dock_Gray);
    addDockWidget(Qt::RightDockWidgetArea, dock_Enhance);
    addDockWidget(Qt::RightDockWidgetArea, dock_Color);
    addDockWidget(Qt::RightDockWidgetArea, dock_Prop);

    // 分割窗口
    splitDockWidget(dock_Tool, dock_Image, Qt::Horizontal);     // 水平
    splitDockWidget(dock_Geom, dock_Output, Qt::Vertical);      // 垂直

    // 合并窗口
    tabifyDockWidget(dock_Geom, dock_Gray);
    tabifyDockWidget(dock_Gray, dock_Enhance);
    tabifyDockWidget(dock_Enhance, dock_Color);
    tabifyDockWidget(dock_Output, dock_Prop);

    dock_Geom->raise();             // raise()函数可使指定窗口置于最前
    dock_Output->raise();

    connect(dock_Tool, SIGNAL(visibilityChanged(bool)), this, SLOT(isDockTool()));
    connect(dock_Output, SIGNAL(visibilityChanged(bool)), this, SLOT(isDockOutput()));
    connect(dock_Prop, SIGNAL(visibilityChanged(bool)), this, SLOT(isDockProp()));
    connect(dock_Geom, SIGNAL(visibilityChanged(bool)), this, SLOT(isDockGeom()));
    connect(dock_Gray, SIGNAL(visibilityChanged(bool)), this, SLOT(isDockGray()));
    connect(dock_Enhance, SIGNAL(visibilityChanged(bool)), this, SLOT(isDockEnhance()));
    connect(dock_Color, SIGNAL(visibilityChanged(bool)), this, SLOT(isDockColor()));

    // 初始化QLabel
    imgLabel = new PaintWidget(dock_Image);
    imgLabel->setScaledContents(true);  // 设置QLabel自动适应图像大小

    // 初始图像
    QImage image = QImage(500, 500, QImage::Format_RGB32);  // 新建图像
    image.fill(qRgb(255, 255, 255));                        // 全白
    imgLabel->setPenWidth(2);
    imgLabel->setPenColor(Qt::black);
    imgLabel->setImage(image);
    imgLabel->setPixmap(QPixmap::fromImage(image));         // 显示图像
    //imgLabel->resize(image.width(), image.height());        // 图像与imgLabel同大小
    imgVector[0].push_back(image);


    iter = imgVector[0].end() - 1;			// 最后一个元素对应的迭代器指针
    ui->action_3->setEnabled(false);		// 不允许撤销
    ui->action_4->setEnabled(false);		// 不允许重做

    // 增加滚动条,如果图像比imgLabel大，就会出现滚动条
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setAlignment(Qt::AlignCenter);
    scrollArea->setWidget(imgLabel);
    dock_Image->setWidget(scrollArea);


    WinTool();
    WinGeom();
    WinGray();
    WinEnhance();
    WinColor();
    WinProp();		// 属性窗口
    ColorToolBar(); //绘图工具栏
    UpdateProp(image);
    UpdateImgName("图像");

    whiteRadio = new QRadioButton();// 关于 单选框
    blackRadio = new QRadioButton();

    editCounter = 0;
    counter = 0;
}

// 绘图工具栏
void MainWindow::ColorToolBar()
{
    toolBar = new QToolBar();
    toolBar = addToolBar(tr("画笔工具栏"));
    toolBar->setMovable(true);

    QLabel *label_penWidth = new QLabel(tr("线宽"));
    spinbox_penWidth = new QSpinBox;
    spinbox_penWidth->setRange(1, 50);
    spinbox_penWidth->setValue(2);

    QPushButton *button_color = new QPushButton(tr("画笔颜色"));

    frame_color = new QFrame;
    frame_color->setObjectName("customFrame");
    frame_color->setFrameShape(QFrame::Box);
    frame_color->setPalette(QPalette(Qt::black));
    frame_color->setAutoFillBackground(true);
    frame_color->setFixedSize(25, 25);
    frame_color->setStyleSheet("QFrame{background-color: rgba(" + QString::number(0) + "," + QString::number(0) + "," + QString::number(0) + ",1);border:none}");

    connect(spinbox_penWidth, SIGNAL(valueChanged(int)), this, SLOT(penWidth()));
    connect(button_color, SIGNAL(clicked()), this, SLOT(penColor()));

    QHBoxLayout *colorLayout = new QHBoxLayout();
    colorLayout->setAlignment(Qt::AlignLeft);

    colorLayout->addWidget(label_penWidth);
    colorLayout->addWidget(spinbox_penWidth);
    colorLayout->addWidget(button_color);
    colorLayout->addWidget(frame_color);

    QWidget *colorWidget = new QWidget();
    colorWidget->setLayout(colorLayout);
    toolBar->addWidget(colorWidget);
}

// 属性窗口
void MainWindow::WinProp()
{
    dock_Prop->setFeatures(QDockWidget::AllDockWidgetFeatures);

    line_img = new QLineEdit();
    line_length = new QLineEdit();
    line_width = new QLineEdit();
    line_depth = new QLineEdit();
    line_isGray = new QLineEdit();

    line_img->setReadOnly(true);
    line_length->setReadOnly(true);
    line_width->setReadOnly(true);
    line_depth->setReadOnly(true);
    line_isGray->setReadOnly(true);

    QFormLayout *propLayout = new QFormLayout();
    propLayout->addRow(tr("图像"), line_img);
    propLayout->addRow(tr("长度"), line_length);
    propLayout->addRow(tr("宽度"), line_width);
    propLayout->addRow(tr("深度"), line_depth);
    propLayout->addRow(tr("是否灰度"), line_isGray);
    propLayout->setSpacing(20);
    propLayout->setMargin(20);

    QWidget *propWidget = new QWidget(dock_Prop);
    propWidget->setLayout(propLayout);
    dock_Prop->setWidget(propWidget);
}

// 更新图像地址
void MainWindow::UpdateImgName(QString name)
{
    line_img->setText(name);
}

// 更新属性窗口数据
void MainWindow::UpdateProp(QImage Img)
{
    line_length->setText(QString::number(Img.width()));
    line_width->setText(QString::number(Img.height()));
    line_depth->setText(QString::number(Img.depth()));
    if (Img.depth() == 8 || Img.depth() == 1)
        line_isGray->setText("是");
    else
        line_isGray->setText("否");
}

// 颜色模型窗口
void MainWindow::WinColor()
{
    dock_Color->setFeatures(QDockWidget::AllDockWidgetFeatures);

    QLabel *label_RGB = new QLabel(tr("RGB模型"));
    QPushButton *button_R = new QPushButton(tr("R分量图"));
    QPushButton *button_G = new QPushButton(tr("G分量图"));
    QPushButton *button_B = new QPushButton(tr("B分量图"));

    connect(button_R, SIGNAL(clicked()), this, SLOT(splitR()));
    connect(button_G, SIGNAL(clicked()), this, SLOT(splitG()));
    connect(button_B, SIGNAL(clicked()), this, SLOT(splitB()));

    QGridLayout *colorLayout = new QGridLayout();
    colorLayout->setAlignment(Qt::AlignTop);
    colorLayout->setMargin(30);

    colorLayout->addWidget(label_RGB, 0, 0, 1, 1);
    colorLayout->addWidget(button_R, 1, 1, 1, 1);
    colorLayout->addWidget(button_G, 1, 2, 1, 1);
    colorLayout->addWidget(button_B, 1, 3, 1, 1);

    QWidget *colorWidget = new QWidget(dock_Color);
    colorWidget->setFixedWidth(420);
    colorWidget->setLayout(colorLayout);
    dock_Color->setWidget(colorWidget);

    QScrollArea *scrollArea = new QScrollArea(dock_Color);
    scrollArea->setAlignment(Qt::AlignLeft);
    scrollArea->setWidget(colorWidget);
    dock_Color->setWidget(scrollArea);
}

void MainWindow::WinGeom()
{
    dock_Geom->setFeatures(QDockWidget::AllDockWidgetFeatures);

    // 图像大小
    QLabel *null = new QLabel(tr("	"));
    QLabel *label_area = new QLabel(tr("图像大小"));
    QLabel *labelL = new QLabel(tr("图像长度:"));
    QLabel *labelW = new QLabel(tr("图像宽度:"));
    QPushButton *buttonDefault = new QPushButton(tr("默认"));
    QPushButton *buttonOK = new QPushButton(tr("确认"));
    line_L = new QLineEdit("500");
    line_L->setValidator(new QIntValidator(1, 10000));		// 只能输入数字
    line_L->setAlignment(Qt::AlignCenter);
    line_L->setStyleSheet("min-width: 50px;");
    line_W = new QLineEdit("500");
    line_W->setValidator(new QIntValidator(1, 10000));
    line_W->setAlignment(Qt::AlignCenter);
    connect(buttonDefault, SIGNAL(clicked()), this, SLOT(autoSize()));
    connect(buttonOK, SIGNAL(clicked()), this, SLOT(changeImageSize()));

    // 图像缩放
    QLabel *label_size = new QLabel(tr("图像缩放"));
    QLabel *label_times = new QLabel(tr("缩放倍数:"));
    QPushButton *button_size = new QPushButton(tr("确认"));
    line_times = new QSpinBox();
    line_times->setAlignment(Qt::AlignCenter);
    line_times->setRange(-10, 10);
    line_times->setValue(0);
    connect(button_size, SIGNAL(clicked()), this, SLOT(enlargeReduce()));

    // 图像旋转
    QLabel *label_rotate = new QLabel(tr("图像旋转"));
    QLabel *label_degree = new QLabel(tr("旋转角度:"));
    QPushButton *button_rotate = new QPushButton(tr("确认"));
    QPushButton *button_left = new QPushButton(tr("顺时针90"));
    QPushButton *button_right = new QPushButton(tr("逆时针90"));
    QPushButton *button_180 = new QPushButton(tr("旋转180"));
    line_degree = new QSpinBox();
    line_degree->setAlignment(Qt::AlignCenter);
    line_degree->setRange(-360, 360);
    line_degree->setValue(0);
    connect(button_rotate, SIGNAL(clicked()), this, SLOT(rotateImage()));
    connect(button_left, SIGNAL(clicked()), this, SLOT(rotateImage_270()));
    connect(button_right, SIGNAL(clicked()), this, SLOT(rotateImage_90()));
    connect(button_180, SIGNAL(clicked()), this, SLOT(rotateImage_180()));

    // 图像翻转
    QLabel *label_reverse = new QLabel(tr("图像翻转"));
    QPushButton *button_H = new QPushButton(tr("水平翻转"));
    QPushButton *button_V = new QPushButton(tr("垂直翻转"));
    connect(button_H, SIGNAL(clicked()), this, SLOT(flipImage_H()));
    connect(button_V, SIGNAL(clicked()), this, SLOT(flipImage_V()));

    // 格栅布局
    QGridLayout *geomLayout = new QGridLayout();
    geomLayout->setAlignment(Qt::AlignTop);
    geomLayout->setMargin(30);

    geomLayout->addWidget(label_area, 0, 0, 1, 1);// 图像大小
    geomLayout->addWidget(labelL, 1, 1, 1, 1);
    geomLayout->addWidget(line_L, 1, 2, 1, 1);
    geomLayout->addWidget(labelW, 2, 1, 1, 1);
    geomLayout->addWidget(line_W, 2, 2, 1, 1);
    geomLayout->addWidget(buttonOK, 1, 3, 1, 1);
    geomLayout->addWidget(buttonDefault, 1, 4, 1, 1);

    geomLayout->addWidget(null, 10, 0, 1, 1);// 图像缩放
    geomLayout->addWidget(label_size, 11, 0, 1, 1);
    geomLayout->addWidget(label_times, 12, 1, 1, 1);
    geomLayout->addWidget(line_times, 12, 2, 1, 1);
    geomLayout->addWidget(button_size, 12, 3, 1, 1);
    geomLayout->addWidget(null, 14, 0, 1, 1);

    geomLayout->addWidget(null, 20, 0, 1, 1);// 图像旋转
    geomLayout->addWidget(label_rotate, 21, 0, 1, 1);
    geomLayout->addWidget(label_degree, 22, 1, 1, 1);
    geomLayout->addWidget(line_degree, 22, 2, 1, 1);
    geomLayout->addWidget(button_rotate, 22, 3, 1, 1);
    geomLayout->addWidget(button_180, 23, 2, 1, 1);
    geomLayout->addWidget(button_left, 23, 3, 1, 1);
    geomLayout->addWidget(button_right, 23, 4, 1, 1);


    geomLayout->addWidget(null, 40, 0, 1, 1);// 图像翻转
    geomLayout->addWidget(label_reverse, 41, 0, 1, 1);
    geomLayout->addWidget(button_H, 42, 1, 1, 2);
    geomLayout->addWidget(button_V, 42, 3, 1, 2);

    QWidget *geomWidget = new QWidget(dock_Geom);
    geomWidget->setFixedWidth(420);
    geomWidget->setLayout(geomLayout);
    dock_Geom->setWidget(geomWidget);

    QScrollArea *scrollArea = new QScrollArea(dock_Geom);
    scrollArea->setAlignment(Qt::AlignLeft);
    scrollArea->setWidget(geomWidget);
    dock_Geom->setWidget(scrollArea);
}

// 灰度变换窗口
void MainWindow::WinGray()
{
    dock_Gray->setFeatures(QDockWidget::AllDockWidgetFeatures);

    QLabel *label_linear = new QLabel(tr("线性变换"));
    QLabel *label_alpha = new QLabel(tr("K :"));
    QLabel *label_beta = new QLabel(tr("B :"));
    QPushButton *button_linear = new QPushButton(tr("确认"));
    line_alpha = new QDoubleSpinBox();
    line_alpha->setAlignment(Qt::AlignCenter);
    line_alpha->setRange(0, 10);
    line_alpha->setValue(1);
    line_beta = new QSpinBox();
    line_beta->setAlignment(Qt::AlignCenter);
    line_beta->setRange(-255, +255);
    line_beta->setValue(0);

    QLabel *label_log = new QLabel(tr("指数变换"));
    QLabel *label_c = new QLabel(tr("  Exp:"));
    QPushButton *button_exp = new QPushButton(tr("确认"));
    line_c = new QDoubleSpinBox();
    line_c->setAlignment(Qt::AlignCenter);
    line_c->setRange(0, 10);
    line_c->setValue(1);

    QLabel *label_gamma = new QLabel(tr("伽马变换"));
    QLabel *label_gam = new QLabel(tr("Gamma:"));
    QPushButton *button_gamma = new QPushButton(tr("确认"));
    line_gamma = new QDoubleSpinBox();
    line_gamma->setAlignment(Qt::AlignCenter);
    line_gamma->setRange(0, 5);
    line_gamma->setValue(1);

    // 二值图像
    QLabel *null = new QLabel(tr("	"));
    QLabel *label_bin = new QLabel(tr("二值图像"));
    QLabel *label_threshold = new QLabel(tr(" 阈值:"));
    QPushButton *button_bin = new QPushButton(tr("确认"));

    QSlider *slider_bin = new QSlider(Qt::Horizontal);		// 滑动条
    slider_bin->setRange(0, 255);
    slider_bin->setValue(100);

    line_bin = new QSpinBox();
    line_bin->setAlignment(Qt::AlignCenter);
    line_bin->setRange(0, 255);
    line_bin->setValue(100);

    connect(line_bin, SIGNAL(valueChanged(int)), slider_bin, SLOT(setValue(int)));
    connect(slider_bin, SIGNAL(valueChanged(int)), line_bin, SLOT(setValue(int)));
    connect(slider_bin, SIGNAL(valueChanged(int)), this, SLOT(binSliderImage()));

    QLabel *label_graylevel = new QLabel(tr("灰度图像"));
    QPushButton *button_graylevel = new QPushButton(tr("灰度图像"));

    QLabel *label_reverse = new QLabel(tr("反转变换"));
    QPushButton *button_reverse = new QPushButton(tr("图像反转"));

    QLabel *label_histeq = new QLabel();
    label_histeq->setText(tr("直方图"));
    QPushButton *button_histeq = new QPushButton();
    button_histeq->setText(tr("灰度直方图均衡化"));

    connect(button_bin, SIGNAL(clicked()), this, SLOT(binImageOK()));
    connect(button_graylevel, SIGNAL(clicked()), this, SLOT(grayImage()));
    connect(button_reverse, SIGNAL(clicked()), this, SLOT(reverseImage()));
    connect(button_linear, SIGNAL(clicked()), this, SLOT(linearImage()));
    connect(button_gamma, SIGNAL(clicked()), this, SLOT(gammaImage()));
    connect(button_exp, SIGNAL(clicked()), this, SLOT(expImage()));
    connect(button_histeq, SIGNAL(clicked()), this, SLOT(histeqImage()));

    // 格栅布局
    QGridLayout *grayLayout = new QGridLayout();
    grayLayout->setAlignment(Qt::AlignTop);
    grayLayout->setMargin(30);

    grayLayout->addWidget(label_linear, 16, 0, 1, 1);
    grayLayout->addWidget(label_alpha, 17, 1, 1, 1);
    grayLayout->addWidget(line_alpha, 17, 2, 1, 1);
    grayLayout->addWidget(label_beta, 18, 1, 1, 1);
    grayLayout->addWidget(line_beta, 18, 2, 1, 1);
    grayLayout->addWidget(button_linear, 17, 3, 1, 1);

    grayLayout->addWidget(null, 20, 0, 1, 1);
    grayLayout->addWidget(label_log, 21, 0, 1, 1);
    grayLayout->addWidget(label_c, 22, 1, 1, 1);
    grayLayout->addWidget(line_c, 22, 2, 1, 1);
    grayLayout->addWidget(button_exp, 22, 3, 1, 1);

    grayLayout->addWidget(null, 25, 0, 1, 1);
    grayLayout->addWidget(label_gamma, 26, 0, 1, 1);
    grayLayout->addWidget(label_gam, 27, 1, 1, 1);
    grayLayout->addWidget(line_gamma, 27, 2, 1, 1);
    grayLayout->addWidget(button_gamma, 27, 3, 1, 1);

    grayLayout->addWidget(null, 30, 0, 1, 1);
    grayLayout->addWidget(label_bin, 31, 0, 1, 1);
    grayLayout->addWidget(label_threshold, 32, 1, 1, 1);
    grayLayout->addWidget(slider_bin, 32, 2, 1, 1);
    grayLayout->addWidget(line_bin, 32, 3, 1, 1);
    grayLayout->addWidget(button_bin, 33, 3, 1, 1);

    grayLayout->addWidget(null, 35, 0, 1, 1);
    grayLayout->addWidget(label_graylevel, 36, 0, 1, 1);
    grayLayout->addWidget(button_graylevel, 37, 1, 1, 4);

    grayLayout->addWidget(null, 40, 0, 1, 1);
    grayLayout->addWidget(label_reverse, 41, 0, 1, 1);
    grayLayout->addWidget(button_reverse, 42, 1, 1, 4);

    grayLayout->addWidget(null, 45, 0, 1, 1);
    grayLayout->addWidget(label_histeq, 46, 0, 1, 1);
    grayLayout->addWidget(button_histeq, 47, 1, 1, 4);

    QWidget *grayWidget = new QWidget(dock_Gray);
    grayWidget->setFixedWidth(420);
    grayWidget->setLayout(grayLayout);
    dock_Gray->setWidget(grayWidget);

    QScrollArea *scrollArea = new QScrollArea(dock_Gray);
    scrollArea->setAlignment(Qt::AlignLeft);
    scrollArea->setWidget(grayWidget);
    dock_Gray->setWidget(scrollArea);
}
// 图像增强窗口
void MainWindow::WinEnhance()
{
    dock_Enhance->setFeatures(QDockWidget::AllDockWidgetFeatures);

    QLabel *label_smooth = new QLabel(tr("图像平滑"));
    QLabel *label_coreSmooth = new QLabel(tr("模板大小"));
    QPushButton *button_average = new QPushButton(tr("均值滤波"));
    QPushButton *button_Gaussian = new QPushButton(tr("高斯滤波"));
    QPushButton *button_Median = new QPushButton(tr("中值滤波"));
    combo_smooth = new QComboBox();
    combo_smooth->addItem(tr("3×3")); combo_smooth->addItem(tr("5×5"));
    combo_smooth->addItem(tr("7×7")); combo_smooth->addItem(tr("9×9"));
    combo_smooth->addItem(tr("11×11")); combo_smooth->addItem(tr("13×13"));
    combo_smooth->addItem(tr("15×15")); combo_smooth->addItem(tr("17×17"));
    combo_smooth->addItem(tr("19×19")); combo_smooth->addItem(tr("21×21"));

    connect(button_average, SIGNAL(clicked()), this, SLOT(averageImage()));
    connect(button_Gaussian, SIGNAL(clicked()), this, SLOT(gaussianImage()));
    connect(button_Median, SIGNAL(clicked()), this, SLOT(medianImage()));

    QLabel *label_sharpen = new QLabel(tr("图像锐化"));
    QPushButton *button_sobel = new QPushButton(tr("Sobel边缘检测"));
    QPushButton *button_laplacian = new QPushButton(tr("Laplacian检测"));
    QPushButton *button_canny = new QPushButton(tr("Canny边缘检测"));

    QLabel *label_canny = new QLabel(tr("Canny阈值"));
    spinbox_canny = new QSpinBox;							// 微调框
    spinbox_canny->setRange(0, 100);
    spinbox_canny->setValue(20);

    QSlider *slider_canny = new QSlider(Qt::Horizontal);		// 滑动条
    slider_canny->setRange(0, 100);
    slider_canny->setValue(20);

    connect(button_sobel, SIGNAL(clicked()), this, SLOT(sobelImage()));
    connect(button_laplacian, SIGNAL(clicked()), this, SLOT(laplacianImage()));
    connect(button_canny, SIGNAL(clicked()), this, SLOT(cannyImage()));

    connect(spinbox_canny, SIGNAL(valueChanged(int)), slider_canny, SLOT(setValue(int)));
    connect(slider_canny, SIGNAL(valueChanged(int)), spinbox_canny, SLOT(setValue(int)));
    connect(spinbox_canny, SIGNAL(valueChanged(int)), this, SLOT(cannyValueChange()));

    // 格栅布局
    QGridLayout *enhanceLayout = new QGridLayout();
    enhanceLayout->setAlignment(Qt::AlignTop);
    enhanceLayout->setMargin(30);

    enhanceLayout->addWidget(label_smooth, 0, 0, 1, 1);
    enhanceLayout->addWidget(label_coreSmooth, 1, 1, 1, 1);
    enhanceLayout->addWidget(combo_smooth, 1, 2, 1, 1);
    enhanceLayout->addWidget(button_average, 2, 2, 1, 1);
    enhanceLayout->addWidget(button_Gaussian, 3, 2, 1, 1);
    enhanceLayout->addWidget(button_Median, 4, 2, 1, 1);

    enhanceLayout->addWidget(label_sharpen, 5, 0, 1, 1);
    enhanceLayout->addWidget(button_sobel, 7, 2, 1, 1);
    enhanceLayout->addWidget(button_laplacian, 8, 2, 1, 1);
    enhanceLayout->addWidget(button_canny, 9, 2, 1, 1);

    enhanceLayout->addWidget(label_canny, 10, 1, 1, 1);
    enhanceLayout->addWidget(slider_canny, 10, 2, 1, 1);
    enhanceLayout->addWidget(spinbox_canny, 10, 3, 1, 1);

    QWidget *enhanceWidget = new QWidget(dock_Enhance);
    enhanceWidget->setFixedWidth(420);
    enhanceWidget->setLayout(enhanceLayout);
    dock_Enhance->setWidget(enhanceWidget);

    QScrollArea *scrollArea = new QScrollArea(dock_Enhance);
    scrollArea->setAlignment(Qt::AlignLeft);
    scrollArea->setWidget(enhanceWidget);
    dock_Enhance->setWidget(scrollArea);
}


// 工具箱
void MainWindow::WinTool()
{
    dock_Tool->setFeatures(QDockWidget::DockWidgetClosable);

    QPushButton *button_pen = new QPushButton(QIcon(":/new/Image/toolbox/Painbrush.png"), tr(""), this);
    button_pen->setFixedSize(35, 35);
    button_pen->setToolTip(tr("钢笔"));
    button_pen->setObjectName("customButton");
    QPushButton *button_line = new QPushButton(QIcon(":/new/Image/toolbox/Line.png"), tr(""), this);
    button_line->setFixedSize(35, 35);
    button_line->setToolTip(tr("线条"));
    button_line->setObjectName("customButton");
    QPushButton *button_circle = new QPushButton(QIcon(":/new/Image/toolbox/Circle.png"), tr(""), this);
    button_circle->setFixedSize(35, 35);
    button_circle->setToolTip(tr("圆形"));
    button_circle->setObjectName("customButton");
    QPushButton *button_ellipse = new QPushButton(QIcon(":/new/Image/toolbox/Elipse.png"), tr(""), this);
    button_ellipse->setFixedSize(35, 35);
    button_ellipse->setToolTip(tr("椭圆"));
    button_ellipse->setObjectName("customButton");
    QPushButton *button_triangle = new QPushButton(QIcon(":/new/Image/toolbox/Triangle.png"), tr(""), this);
    button_triangle->setFixedSize(35, 35);
    button_triangle->setToolTip(tr("三角形"));
    button_triangle->setObjectName("customButton");
    QPushButton *button_rhombus = new QPushButton(QIcon(":/new/Image/toolbox/Rhombus.png"), tr(""), this);
    button_rhombus->setFixedSize(35, 35);
    button_rhombus->setToolTip(tr("菱形"));
    button_rhombus->setObjectName("customButton");
    QPushButton *button_rect = new QPushButton(QIcon(":/new/Image/toolbox/Rectangle.png"), tr(""),this);
    button_rect->setFixedSize(35, 35);
    button_rect->setToolTip(tr("长方形"));
    button_rect->setObjectName("customButton");
    QPushButton *button_square = new QPushButton(QIcon(":/new/Image/toolbox/Square.png"), tr(""), this);
    button_square->setFixedSize(35, 35);
    button_square-> setToolTip(tr("正方形"));
    button_square->setObjectName("customButton");
    QPushButton *button_hexagon = new QPushButton(QIcon(":/new/Image/toolbox/Hexagon.png"), tr(""), this);
    button_hexagon->setFixedSize(35, 35);
    button_hexagon->setToolTip(tr("六边形"));
    button_hexagon->setObjectName("customButton");

    toolButtonGroup = new QButtonGroup();
    connect(toolButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(toolButtonClicked(int)));
    toolButtonGroup->addButton(button_pen,1);
    toolButtonGroup->addButton(button_line,2);
    toolButtonGroup->addButton(button_ellipse,3);
    toolButtonGroup->addButton(button_circle,4);
    toolButtonGroup->addButton(button_triangle,5);
    toolButtonGroup->addButton(button_rhombus,6);
    toolButtonGroup->addButton(button_rect,7);
    toolButtonGroup->addButton(button_square,8);
    toolButtonGroup->addButton(button_hexagon,9);

    QGridLayout *toolLayout = new QGridLayout();
    toolLayout->setAlignment(Qt::AlignTop);
    toolLayout->addWidget(button_pen, 0, 0);
    toolLayout->addWidget(button_line, 0, 1);
    toolLayout->addWidget(button_ellipse, 1, 1);
    toolLayout->addWidget(button_circle, 1, 0);
    toolLayout->addWidget(button_triangle, 2, 0);
    toolLayout->addWidget(button_rhombus, 2, 1);
    toolLayout->addWidget(button_rect, 3, 0);
    toolLayout->addWidget(button_square, 3, 1);
    toolLayout->addWidget(button_hexagon, 4, 0);

    QWidget *toolWidget = new QWidget(dock_Tool);
    toolWidget->setLayout(toolLayout);
    dock_Tool->setWidget(toolWidget);
}

// 显示图像
void MainWindow::ShowImage(QImage Img, bool isSave)
{
    imgLabel->setImage(Img);
    imgLabel->setPixmap(QPixmap::fromImage(Img));
    imgLabel->resize(Img.width(), Img.height());
    UpdateImgName(currentPath);
    UpdateProp(Img);  //更新属性窗口数据
    if (isSave == true)
    {
        if (iter != (imgVector[0].end() - 1))
        {
            imgVector[0].erase(++iter, imgVector[0].end());
        }

        imgVector[0].push_back(Img);
        iter = imgVector[0].end() - 1;
        ui->action_3->setEnabled(true);
        ui->action_4->setEnabled(false);

    }
    /*if(editCounter != 0)
    {
        imageVideo[editCounter] = imgLabel->getImage().copy();
        editCounter = 0;
    }*/
}


void MainWindow::on_new_2_triggered()
{
    QImage image = QImage(500, 500, QImage::Format_RGB32);  // 创建长宽各500的RGB图像
    image.fill(qRgb(255, 255, 255));                        // 白色图像
    ShowImage(image,true);
    currentPath = "";                                       // 当前路径为空
    output("新建图像：长500，宽500");
    UpdateImgName("新图像");
}

void MainWindow::on_open_triggered()
{
    //qDebug("1");
    QStringList paths = QFileDialog::getOpenFileNames(this, "选择图像", ".", "Images(*.jpg *.png *.bmp)");// 文件选择框
    //qDebug("2");
    for(int i=0; i<paths.length(); i++)
    {
        QImage* img = new QImage();
        QString path = paths[i];
        if(i == 0 && !path.isEmpty())
        {
            if (!(img->load(path)))
            {
                QMessageBox::information(this, tr("错误"), tr("打开图像失败！"));
                delete img;
                return;
            }
            currentPath = path;
            ShowImage(*img, true);
            output("图像打开"+path);
        }else
        {
            if (!path.isEmpty())                                    // 检测当前路径是否正确
            {
                if (!(img->load(path)))
                {
                    QMessageBox::information(this, tr("错误"), tr("打开图像失败！"));
                    delete img;
                    return;
                }
                // 初始化QDockWidget可移动隐藏的小窗口
                dock_Image1 = new QDockWidget(tr("图像"), this);          //   图像
                dock_Image1->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetClosable);         // 设置为可移动可浮动，但不可关闭
                dock_Image1->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);  // 可移动范围：左右
                dock_Image1->setMinimumSize(600, 600);   // 设置最小宽高
                tabifyDockWidget(dock_Image, dock_Image1);

                imgLabel1 = new QLabel(dock_Image1);
                imgLabel1->setScaledContents(true);  // 设置QLabel自动适应图像大小

                // 增加滚动条,如果图像比imgLabel大，就会出现滚动条
                QScrollArea* scrollArea = new QScrollArea(dock_Image1);
                scrollArea->setBackgroundRole(QPalette::Dark);
                scrollArea->setAlignment(Qt::AlignCenter);
                scrollArea->setWidget(imgLabel1);
                dock_Image1->setWidget(scrollArea);


                imgLabel1->setPixmap(QPixmap::fromImage(*img));
                imgLabel1->resize(img->width(), img->height());
                currentPath = path;
                //ShowImage(*img, true);
                dock_Image1->raise();
                output("图像打开"+path);
            }
        }
    }
    pro = imgLabel->pixmap()->toImage().copy(0, 0,imgLabel->pixmap()->toImage().width(),imgLabel->pixmap()->toImage().height());
}

void MainWindow::on_save_triggered()
{
    QString path;
    if (currentPath.isEmpty())      // 判断是新建的图像还是打开的图像
    {
        path = QFileDialog::getSaveFileName(this, tr("保存图像"), ".", tr("Images(*.jpg *.png *.bmp)"));
        {
            if (!path.isEmpty())
                currentPath = path;
        }
    }
    QImage img = imgLabel->pixmap()->toImage();     // 读取图像
    img.save(currentPath);                          // 保存图像
    output("图像保存: " + path);
}

void MainWindow::on_saveAs_triggered()
{
    QString path = QFileDialog::getSaveFileName(this, tr("图像另存为"), ".", tr("Images(*.jpg *.png *.bmp)"));
    if (!path.isEmpty())
    {
        QImage img = imgLabel->pixmap()->toImage();
        img.save(path);
        currentPath = path;
    }
    output("图像另存为: " + path );
}

// 灰度图像
void MainWindow::grayImage()
{
    QImage *img = tom->Graylevel(imgLabel->pixmap()->toImage());
    counters[editCounter] = counter-1;
    editeImageVideo[editCounter] = img->copy();
    editCounter++;
    ShowImage(*img, true);
    output("灰度变换：灰度图像");

}

// 二值图像
void MainWindow::binImageOK()
{
    QImage *img = tom->TowValue(imgLabel->pixmap()->toImage(),line_bin->text().toInt());
    counters[editCounter] = counter-1;
    editeImageVideo[editCounter] = img->copy();
    editCounter++;
    ShowImage(*img, true);
    output("灰度变换：图像二值化");
}

void MainWindow::on_action_28_triggered()
{
    grayImage();
    output("灰度变换：灰度图像");
}


void MainWindow::on_action_27_triggered()
{
    binImageOK();
    output("灰度变换：图像二值化");
}

// 撤销
void MainWindow::on_action_3_triggered()
{
    if (iter != imgVector[0].begin())			// 前面还有对象
    {
        iter--;
        ShowImage(*iter, false);
        //output("系统提示：撤销");
        ui->action_4->setEnabled(true);

        if (iter == imgVector[0].begin())		// 判断自减后是否为初始图像
        {
            ui->action_3->setEnabled(false);
        }
    }
    output("撤销");
}

// 重做
void MainWindow::on_action_4_triggered()
{
    if (iter != (imgVector[0].end() - 1))		// 后面还有对象
    {
        iter++;
        ShowImage(*iter, false);
        //output("系统提示：重做");
        ui->action_3->setEnabled(true);

        if (iter == (imgVector[0].end() - 1))
        {
            ui->action_4->setEnabled(false);
        }
    }
    output("重做");
}

// 均值滤波
void MainWindow::averageImage()
{
    QImage img = tom->averageImage(imgLabel->pixmap()->toImage(), 2 * (combo_smooth->currentIndex()) + 3);
    counters[editCounter] = counter-1;
    editeImageVideo[editCounter] = img.copy();
    editCounter++;
    ShowImage(img, true);
    output("图像增强：均值滤波");
}

// 中值滤波
void MainWindow::medianImage()
{
    QImage img = tom->medianImage(imgLabel->pixmap()->toImage(), 2 * (combo_smooth->currentIndex()) + 3);
    counters[editCounter] = counter-1;
    editeImageVideo[editCounter] = img.copy();
    editCounter++;
    ShowImage(img, true);
    output("图像增强：中值滤波");
}

// 伽马变换
void MainWindow::gammaImage()
{
    QImage* Img = tom->gammaImage(imgLabel->pixmap()->toImage(), line_gamma->text().toDouble());
    counters[editCounter] = counter-1;
    editeImageVideo[editCounter] = Img->copy();
    editCounter++;
    ShowImage(*Img, true);
    output("灰度变换：伽马变换");
}

// 指数变换
void MainWindow::expImage()
{
    QImage* Img = tom->expImage(imgLabel->pixmap()->toImage(), line_c->text().toDouble());
    counters[editCounter] = counter-1;
    editeImageVideo[editCounter] = Img->copy();
    editCounter++;
    ShowImage(*Img, true);
    output("灰度变换：指数变换");
}

// 关于
void MainWindow::on_action_49_triggered()
{
    QDialog *helpWin = new QDialog();
    helpWin->setWindowIcon(QIcon(":/new/Image/help/Help_Info.png"));
    helpWin->resize(600, 400);

    QLabel *label_about = new QLabel(helpWin);
    label_about->setText(tr("自编Ps 1.0版本"));
    QLabel *label_right = new QLabel(helpWin);
    label_right->setText(tr("杭州电子科技大学信息工程学院"));
    QLabel *label_author = new QLabel(helpWin);
    label_author->setText(tr("作者：Tom"));
    QLabel *label_blog = new QLabel(helpWin);
    label_blog->setOpenExternalLinks(true);
    label_blog->setText(tr("博客：<style> a {text-decoration: none} </style><a href=\"https://newbeetom.top/\">https://newbeetom.top"));
    QLabel *label_maill = new QLabel(helpWin);
    label_maill->setText(tr("邮箱：EstralleTommm.163.com"));
    QPushButton *button_ok = new QPushButton(helpWin);
    button_ok->setText(tr("确定"));
    connect(button_ok, SIGNAL(clicked()), helpWin, SLOT(close()));

    label_about->move(180, 80);
    label_right->move(180, 130);
    label_author->move(180, 180);
    button_ok->move(400, 350);
    label_blog->move(180, 230);
    label_maill->move(180, 280);

    helpWin->exec();
}

// 顺时针旋转90°
void MainWindow::on_action_22_triggered()
{
    QImage* Img = tom->spin(imgLabel->pixmap()->toImage(), true);
    counters[editCounter] = counter-1;
    editeImageVideo[editCounter] = Img->copy();
    editCounter++;
    ShowImage(*Img, true);
    output("几何变换：顺时针旋转90°");
}

// 逆时针旋转90°
void MainWindow::on_action_23_triggered()
{
    QImage* Img = tom->spin(imgLabel->pixmap()->toImage(), false);
    counters[editCounter] = counter-1;
    editeImageVideo[editCounter] = Img->copy();
    editCounter++;
    ShowImage(*Img, true);
    output("几何变换：逆时针旋转90°");
}

// 水平翻转
void MainWindow::flipImage_H()
{
    QImage* Img = tom->symmetry(imgLabel->pixmap()->toImage(), false);
    counters[editCounter] = counter-1;
    editeImageVideo[editCounter] = Img->copy();
    editCounter++;
    ShowImage(*Img, true);
    output("几何变换：水平翻转");
}

// 垂直翻转
void MainWindow::flipImage_V()
{
    QImage* Img = tom->symmetry(imgLabel->pixmap()->toImage(), true);
    counters[editCounter] = counter-1;
    editeImageVideo[editCounter] = Img->copy();
    editCounter++;
    ShowImage(*Img, true);
    output("几何变换：垂直翻转");
}

// sebol算子 3x3
void MainWindow::sobelImage()
{
    QImage Img = tom->sobelImage(imgLabel->pixmap()->toImage(), 100);
    counters[editCounter] = counter-1;
    editeImageVideo[editCounter] = Img.copy();
    editCounter++;
    ShowImage(Img, true);
    output("图像增强：sebol算子边缘检测");
}

// Laplacian算子 3x3
void MainWindow::laplacianImage()
{
    QImage Img = tom->laplaImage(imgLabel->pixmap()->toImage(), 250);
    counters[editCounter] = counter-1;
    editeImageVideo[editCounter] = Img.copy();
    editCounter++;
    ShowImage(Img, true);
    output("图像增强：Laplacian算子边缘检测");
}

// 高斯滤波
void MainWindow::gaussianImage()
{
    QImage Img = tom->gaussImage(imgLabel->pixmap()->toImage(), 2 * (combo_smooth->currentIndex()) + 3, 1.5);
    counters[editCounter] = counter-1;
    editeImageVideo[editCounter] = Img.copy();
    editCounter++;
    ShowImage(Img, true);
    output("图像增强：高斯滤波");
}

// 改变大小
void MainWindow::changeImageSize()
{
    QImage Img = imgLabel->pixmap()->toImage().scaled(line_L->text().toInt(), line_W->text().toInt());
    counters[editCounter] = counter-1;
    editeImageVideo[editCounter] = Img.copy();
    editCounter++;
    ShowImage(Img,true);	// 图像保存
    output("长宽改变：长 " + QString::number(Img.width()) + "	宽 " + QString::number(Img.height()));
}

// 默认窗口大小
void MainWindow::autoSize()
{
    QImage Img = imgLabel->pixmap()->toImage().scaled(400, 400);
    counters[editCounter] = counter-1;
    editeImageVideo[editCounter] = Img.copy();
    editCounter++;
    ShowImage(Img, true);
    output("几何变换：默认窗口大小");
}

// 缩放
void MainWindow::enlargeReduce()
{
    int x = line_times->text().toInt();
    QImage Img = imgLabel->pixmap()->toImage();
    if(x>0)
    {
        Img = imgLabel->pixmap()->toImage()
                .scaled(imgLabel->pixmap()->toImage().width() * (x+1),
                        imgLabel->pixmap()->toImage().height() * (x+1),
                        Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    }
    if(x<0)
    {
        Img = imgLabel->pixmap()->toImage()
                .scaled(imgLabel->pixmap()->toImage().width() / (1-x),
                        imgLabel->pixmap()->toImage().height() / (1-x),
                        Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    }
    counters[editCounter] = counter-1;
    editeImageVideo[editCounter] = Img.copy();
    editCounter++;
    ShowImage(Img, true);
    output("图像缩放：长 " + QString::number(Img.width()) + "	宽 " + QString::number(Img.height()));
}

// 旋转
void MainWindow::rotateImage()
{
    QMatrix leftmatrix;
    leftmatrix.rotate(line_degree->text().toInt());

    QImage Img = imgLabel->pixmap()->toImage().transformed(leftmatrix);

    counters[editCounter] = counter-1;
    editeImageVideo[editCounter] = Img.copy();
    editCounter++;
    ShowImage(Img, true);
    output("几何变换：旋转");
}

// 顺时针旋转90°
void MainWindow::rotateImage_270()
{
    QImage* Img = tom->spin(imgLabel->pixmap()->toImage(), true);
    counters[editCounter] = counter-1;
    editeImageVideo[editCounter] = Img->copy();
    editCounter++;
    ShowImage(*Img, true);
    output("几何变换：顺时针旋转90°");
}

// 逆时针旋转90°
void MainWindow::rotateImage_90()
{
    QImage* Img = tom->spin(imgLabel->pixmap()->toImage(), false);
    counters[editCounter] = counter-1;
    editeImageVideo[editCounter] = Img->copy();
    editCounter++;
    ShowImage(*Img, true);
    output("几何变换：逆时针旋转90°");
}

// 旋转180°
void MainWindow::rotateImage_180()
{
    QImage* Img = tom->spin(imgLabel->pixmap()->toImage(), true);
    counters[editCounter] = counter-1;
    editeImageVideo[editCounter] = Img->copy();
    editCounter++;
    QImage* Img2 = tom->spin(*Img, true);
    ShowImage(*Img2, true);
    output("几何变换：旋转180°");
}

// 线性变换
void MainWindow::linearImage()
{
    QImage Img = tom->linearImage(imgLabel->pixmap()->toImage(), line_alpha->text().toDouble(), line_beta->text().toInt());
    counters[editCounter] = counter-1;
    editeImageVideo[editCounter] = Img.copy();
    editCounter++;
    ShowImage(Img, true);
    output("灰度处理：线性变换");
}

// 图像反转
void MainWindow::reverseImage()
{
    QImage Img = tom->reverseImage(imgLabel->pixmap()->toImage());
    counters[editCounter] = counter-1;
    editeImageVideo[editCounter] = Img.copy();
    editCounter++;
    ShowImage(Img, true);
    output("几何变换：图像反转");
}

// 灰度直方图均值化
void MainWindow::histeqImage()
{
    QImage Img = tom->histeqImage(imgLabel->pixmap()->toImage());
    counters[editCounter] = counter-1;
    editeImageVideo[editCounter] = Img.copy();
    editCounter++;
    ShowImage(Img, true);
    output("灰度变换：灰度直方图均值化");
}

// 输出
void MainWindow::output(QString information)
{
    outputEdit->append(information);
}

// R分量图
void MainWindow::splitR()
{
    QImage Img = tom->splitBGR(imgLabel->pixmap()->toImage(),0);
    counters[editCounter] = counter-1;
    editeImageVideo[editCounter] = Img.copy();
    editCounter++;
    ShowImage(Img, true);
    output("颜色模型：RGB模型——R分量图");
}

// G分量图
void MainWindow::splitG()
{
    QImage Img = tom->splitBGR(imgLabel->pixmap()->toImage(),1);
    counters[editCounter] = counter-1;
    editeImageVideo[editCounter] = Img.copy();
    editCounter++;
    ShowImage(Img, true);
    output("颜色模型：RGB模型——G分量图");
}

// B分量图
void MainWindow::splitB()
{
    QImage Img = tom->splitBGR(imgLabel->pixmap()->toImage(),2);
    counters[editCounter] = counter-1;
    editeImageVideo[editCounter] = Img.copy();
    editCounter++;
    ShowImage(Img, true);
    output("颜色模型：RGB模型——B分量图");
}

//全屏显示
void MainWindow::on_action_5_triggered()
{
    showFullScreen();
}

void MainWindow::on_action_6_triggered()
{
    showNormal();
}

void MainWindow::on_close_triggered()
{
    close();
}

// 中心翻转
void MainWindow::on_action_24_triggered()
{
    dock_Geom->raise();
    rotateImage_180();
}

// 水平翻转
void MainWindow::on_action_25_triggered()
{
    dock_Geom->raise();
    flipImage_H();
}

// 垂直翻转
void MainWindow::on_action_26_triggered()
{
    dock_Geom->raise();
    flipImage_V();
}

// 图像反转
void MainWindow::on_action_29_triggered()
{
    dock_Gray->raise();
    reverseImage();
}

// 线性变换
void MainWindow::on_action_30_triggered()
{
    dock_Gray->raise();
    linearImage();
}

// 指数变换
void MainWindow::on_action_32_triggered()
{
    dock_Gray->raise();
    expImage();
}

// 伽马变换
void MainWindow::on_action_33_triggered()
{
    dock_Gray->raise();
    gammaImage();
}

// 直方图均值化
void MainWindow::on_action_34_triggered()
{
    dock_Gray->raise();
    histeqImage();
}

// 均值滤波
void MainWindow::on_action_39_triggered()
{
    dock_Enhance->raise();
    averageImage();
}

// 高斯滤波
void MainWindow::on_action_40_triggered()
{
    dock_Enhance->raise();
    gaussianImage();
}

// 中值滤波
void MainWindow::on_action_41_triggered()
{
    dock_Enhance->raise();
    medianImage();
}

// sobel算子
void MainWindow::on_actionSobel_triggered()
{
    dock_Enhance->raise();
    sobelImage();
}

// laplacian算子
void MainWindow::on_actionLaplacian_triggered()
{
    dock_Enhance->raise();
    laplacianImage();
}

//  canny算子
void MainWindow::on_actionCanny_triggered()
{
    dock_Enhance->raise();

}

// R分量图
void MainWindow::on_actionR_triggered()
{
    dock_Color->raise();
    splitR();
}

// G分量图
void MainWindow::on_actionG_triggered()
{
    dock_Color->raise();
    splitG();
}

// B分量图
void MainWindow::on_actionB_triggered()
{
    dock_Color->raise();
    splitB();
}

// 工具窗口开关
void MainWindow::on_action_7_triggered()
{
    isDockTool();
    if (dock_Tool->isHidden() == true)
    {
        dock_Tool->show();
        output("窗口显示：工具栏窗口");
    }
    else
    {
        dock_Tool->hide();
        output("窗口关闭：工具栏窗口");
    }
}

// 工具窗口开关图标
void MainWindow::isDockTool()
{
    if (dock_Tool->isHidden() == true)
    {
        ui->action_7->setIcon(QIcon(""));
    }
    else
    {
        ui->action_7->setIcon(QIcon(":/new/Image/view/Check.png"));
    }
}

// 输出窗口开关图标
void MainWindow::isDockOutput()
{
    if (dock_Output->isHidden() == true)
    {
        ui->action_12->setIcon(QIcon(""));
    }
    else
    {
        ui->action_12->setIcon(QIcon(":/new/Image/view/Check.png"));
    }
}

// 输出窗口开关
void MainWindow::on_action_12_triggered()
{
    isDockOutput();
    if (dock_Output->isHidden() == true)
    {
        dock_Output->show();
        output("窗口显示：输出窗口");
    }
    else
    {
        dock_Output->hide();
        output("窗口关闭：输出窗口");
    }
}

// 属性窗口开关图标
void MainWindow::isDockProp()
{
    if (dock_Prop->isHidden() == true)
    {
        ui->action_13->setIcon(QIcon(""));
    }
    else
    {
        ui->action_13->setIcon(QIcon(":/new/Image/view/Check.png"));
    }
}

// 属性窗口开关
void MainWindow::on_action_13_triggered()
{
    isDockProp();
    if (dock_Prop->isHidden() == true)
    {
        dock_Prop->show();
        output("窗口显示：属性窗口");
    }
    else
    {
        dock_Prop->hide();
        output("窗口关闭：属性窗口");
    }
}

// 几何窗口开关图标
void MainWindow::isDockGeom()
{
    if (dock_Geom->isHidden() == true)
    {
        ui->action_8->setIcon(QIcon(""));
    }
    else
    {
        ui->action_8->setIcon(QIcon(":/new/Image/view/Check.png"));
    }
}

// 几何窗口开关
void MainWindow::on_action_8_triggered()
{
    isDockGeom();
    if (dock_Geom->isHidden() == true)
    {
        dock_Geom->show();
        output("窗口显示：几何窗口");
    }
    else
    {
        dock_Geom->hide();
        output("窗口关闭：几何窗口");
    }
}

// 灰度窗口开关图标
void MainWindow::isDockGray()
{
    if (dock_Gray->isHidden() == true)
    {
        ui->action_9->setIcon(QIcon(""));
    }
    else
    {
        ui->action_9->setIcon(QIcon(":/new/Image/view/Check.png"));
    }
}

// 灰度窗口开关
void MainWindow::on_action_9_triggered()
{
    isDockGray();
    if (dock_Gray->isHidden() == true)
    {
        dock_Gray->show();
        output("窗口显示：灰度窗口");
    }
    else
    {
        dock_Gray->hide();
        output("窗口关闭：灰度窗口");
    }
}

// 图像增强窗口开关图标
void MainWindow::isDockEnhance()
{
    if (dock_Enhance->isHidden() == true)
    {
        ui->action_10->setIcon(QIcon(""));
    }
    else
    {
        ui->action_10->setIcon(QIcon(":/new/Image/view/Check.png"));
    }
}

// 图像增强窗口开关
void MainWindow::on_action_10_triggered()
{
    isDockEnhance();
    if (dock_Enhance->isHidden() == true)
    {
        dock_Enhance->show();
        output("窗口显示：图像增强窗");
    }
    else
    {
        dock_Enhance->hide();
        output("窗口关闭：图像增强窗");
    }
}

// 颜色模型窗口开关图标
void MainWindow::isDockColor()
{
    if (dock_Color->isHidden() == true)
    {
        ui->action_11->setIcon(QIcon(""));
    }
    else
    {
        ui->action_11->setIcon(QIcon(":/new/Image/view/Check.png"));
    }
}

// 图像增强窗口开关
void MainWindow::on_action_11_triggered()
{
    isDockEnhance();
    if (dock_Color->isHidden() == true)
    {
        dock_Color->show();
        output("窗口显示：颜色模型窗口");
    }
    else
    {
        dock_Color->hide();
        output("窗口关闭：颜色模型窗口");
    }
}

// 设置
void MainWindow::option()
{
    QDialog *optionWin = new QDialog();
    optionWin->setWindowTitle(tr("设置"));
    optionWin->setWindowIcon(QIcon(":/new/Image/edit/Edit_Option.png"));
    optionWin->resize(600, 400);

    QTabWidget *tabWidget = new QTabWidget(optionWin);
    QWidget *optionWidget = new QWidget(optionWin);
    tabWidget->addTab(optionWidget, "选择样式");
    QWidget *otherWidget = new QWidget(optionWin);
    tabWidget->addTab(otherWidget, "其它设置");

    // 设置样式(图片)
    QLabel *label_white = new QLabel();
    QImage *img_white = new QImage();
    img_white->load(":/new/Image/edit/img_white.png");
    label_white->setPixmap(QPixmap::fromImage(*img_white));
    label_white->resize(label_white->width(), label_white->height());

    QLabel *label_black = new QLabel();
    QImage *img_black = new QImage();
    img_black->load(":/new/Image/edit/img_black.png");
    label_black->setPixmap(QPixmap::fromImage(*img_black));
    label_black->resize(img_black->width(), img_black->height());
    //qDebug("444");
    // 设置样式(单选框)
    whiteRadio->setText(tr("经典白色"));
    blackRadio->setText(tr("酷炫黑色"));
    //qDebug("111");
    QButtonGroup *radioGroup = new QButtonGroup();
    radioGroup->setExclusive(true);
    radioGroup->addButton(whiteRadio);
    radioGroup->addButton(blackRadio);

    connect(whiteRadio, SIGNAL(clicked()), this, SLOT(whiteLayout()));
    connect(blackRadio, SIGNAL(clicked()), this, SLOT(blackLayout()));

    if (blackRadio->isChecked() == true)		// 针对初始化无按钮按下问题
        blackRadio->setChecked(true);
    else
        whiteRadio->setChecked(true);
    // 样式选择布局
    QVBoxLayout *whiteLayout = new QVBoxLayout;
    whiteLayout->setAlignment(Qt::AlignCenter);
    whiteLayout->addWidget(label_white);
    whiteLayout->addWidget(whiteRadio);
    QWidget *whiteWidget = new QWidget();
    whiteWidget->setLayout(whiteLayout);

    QVBoxLayout *blackLayout = new QVBoxLayout();
    blackLayout->setAlignment(Qt::AlignCenter);
    blackLayout->addWidget(label_black);
    blackLayout->addWidget(blackRadio);
    QWidget *blackWidget = new QWidget();
    blackWidget->setLayout(blackLayout);

    QHBoxLayout *optionLayout = new QHBoxLayout();
    optionLayout->setAlignment(Qt::AlignCenter);
    optionLayout->addWidget(whiteWidget);
    optionLayout->addWidget(blackWidget);
    optionWidget->setLayout(optionLayout);

    // 其他设置布局
    QLabel *langLabel = new QLabel(tr("语言选择："));
    langButton = new QPushButton(tr("切换为英文"));

    connect(langButton, SIGNAL(clicked()), this, SLOT(changeLanguage()));

    QVBoxLayout *langLayout = new QVBoxLayout;
    langLayout->setAlignment(Qt::AlignCenter);
    langLayout->addWidget(langLabel);
    langLayout->addWidget(langButton);
    QWidget *langWidget = new QWidget();
    langWidget->setLayout(langLayout);

    QHBoxLayout *otherLayout = new QHBoxLayout();
    otherLayout->setAlignment(Qt::AlignCenter);
    otherLayout->addWidget(langWidget);
    otherWidget->setLayout(otherLayout);

    // 窗口
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok	| QDialogButtonBox::Cancel);
    buttonBox->button(QDialogButtonBox::Ok)->setText(tr("确定"));
    buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("取消"));
    connect(buttonBox, SIGNAL(accepted()), optionWin, SLOT(close()));
    connect(buttonBox, SIGNAL(rejected()), optionWin, SLOT(close()));

    QVBoxLayout *QssLayout = new QVBoxLayout;
    QssLayout->addWidget(tabWidget);
    QssLayout->addWidget(buttonBox);
    optionWin->setLayout(QssLayout);

    optionWin->exec();
}

// 白色布局
void MainWindow::whiteLayout()
{
    qApp->setStyleSheet(0);
    isSkin = false;
}

// 黑色布局
void MainWindow::blackLayout()
{
    QFile file(":/black.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = tr(file.readAll());
    qApp->setStyleSheet(styleSheet);
    file.close();
    isSkin = true;
}

// 语言切换
void MainWindow::changeLanguage()
{
    if(m_bTranslator)
    {
        //  翻译文件
        m_qtTranslator.load(":/lang_English.qm");
        qApp->installTranslator(&m_qtTranslator);
        ui->retranslateUi(this);
        dock_Image->close();
        dock_Tool->close();
        dock_Geom->close();
        dock_Gray->close();
        dock_Enhance->close();
        dock_Color->close();
        dock_Prop->close();
        dock_Output->close();
        toolBar->close();
        InitImage();
        langButton->setText("切换为中文");
    }
    else

    {
        qApp->removeTranslator(&m_qtTranslator);
        ui->retranslateUi(this);
        dock_Image->close();
        dock_Tool->close();
        dock_Geom->close();
        dock_Gray->close();
        dock_Enhance->close();
        dock_Color->close();
        dock_Prop->close();
        dock_Output->close();
        toolBar->close();
        InitImage();
        langButton->setText("切换为英文");
    }
    m_bTranslator = !m_bTranslator;
}

// 设置
void MainWindow::on_action_50_triggered()
{
    option();
}

// 绘图槽函数ButtonGroup
void MainWindow::toolButtonClicked(int id)
{
    QList<QAbstractButton *> buttons = toolButtonGroup->buttons();
    foreach(QAbstractButton *button, buttons)
    {
        if (toolButtonGroup->button(id) != button)
        {
            button->setChecked(false);
            button->setStyleSheet("{background-color: transparent}");	// 透明
        }
        else if (drawType == id)
        {
            drawType = 0;
            button->setStyleSheet("{background-color: transparent}");	// 透明
        }
        else
        {
            drawType = id;
            button->setStyleSheet("background-color: rgb(76,235,255)");// 青蓝色
        }
    }

    switch (drawType)
    {
    case 0:
        imgLabel->setShape(PaintWidget::Null);
        ShowImage(imgLabel->getImage(),true);
        output("绘制图形：退出绘制模式"); break;
    case 1:								// 首个图标按钮
        imgLabel->setShape(PaintWidget::Pen);
        output("绘制图形：钢笔"); break;
    case 2:
        imgLabel->setShape(PaintWidget::Line);
        output("绘制图形：线条"); break;
    case 3:
        imgLabel->setShape(PaintWidget::Ellipse);
        output("绘制图形：椭圆形"); break;
    case 4:
        imgLabel->setShape(PaintWidget::Circle);
        output("绘制图形：圆形"); break;
    case 5:
        imgLabel->setShape(PaintWidget::Triangle);
        output("绘制图形：三角形"); break;
    case 6:
        imgLabel->setShape(PaintWidget::Rhombus);
        output("绘制图形：菱形"); break;
    case 7:
        imgLabel->setShape(PaintWidget::Rect);
        output("绘制图形：长方形"); break;
    case 8:
        imgLabel->setShape(PaintWidget::Square);
        output("绘制图形：正方形"); break;
    case 9:
        imgLabel->setShape(PaintWidget::Hexagon);
        output("绘制图形：六边形"); break;
    default:
        break;
    }
}

// 设置画笔线宽
void MainWindow::penWidth()
{
    imgLabel->setPenWidth(spinbox_penWidth->text().toInt());
    output("设置线宽");

}

// 设置画笔颜色
void MainWindow::penColor()
{
    QColor c = QColorDialog::getColor(Qt::red, this, tr("选择画笔颜色"));
    //qDebug()<<"color:"<<c;
    if (c.isValid())
    {
        frame_color->setPalette(QPalette(c));
        imgLabel->setPenColor(c);
        frame_color->setStyleSheet("QFrame{background-color: rgba(" + QString::number(c.red()) + "," + QString::number(c.green()) + "," + QString::number(c.blue()) + ",1);border:none}");
    }
}

// 放大一倍
void MainWindow::on_action_20_triggered()
{
    int x = 1;
    QImage Img = imgLabel->pixmap()->toImage();
    Img = imgLabel->pixmap()->toImage()
            .scaled(imgLabel->pixmap()->toImage().width() * (x+1),
                    imgLabel->pixmap()->toImage().height() * (x+1),
                    Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ShowImage(Img, true);
    output("图像缩放：长 " + QString::number(Img.width()) + "	宽 " + QString::number(Img.height()));
}

// 缩小一倍
void MainWindow::on_action_21_triggered()
{
    int x = -1;
    QImage Img = imgLabel->pixmap()->toImage();
    Img = imgLabel->pixmap()->toImage()
            .scaled(imgLabel->pixmap()->toImage().width() / (1-x),
                    imgLabel->pixmap()->toImage().height() / (1-x),
                    Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ShowImage(Img, true);
    output("图像缩放：长 " + QString::number(Img.width()) + "	宽 " + QString::number(Img.height()));
}

// 二值图像
void MainWindow::binSliderImage()
{
    QImage *img = tom->TowValue(pro,line_bin->text().toInt());
    ShowImage(*img, true);
}

// 打开视频
void MainWindow::on_action_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, "选择视频", ".", "video(*.mp4)");// 文件选择框

    if (!path.isEmpty())                                    // 检测当前路径是否正确
    {
        dock_video = new QDockWidget(tr("视频"), this);
        dock_video->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetClosable);         // 设置为可移动可浮动，但不可关闭
        dock_video->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);  // 可移动范围：左右
        dock_video->setMinimumSize(600, 600);   // 设置最小宽高
        tabifyDockWidget(dock_Image, dock_video);

        player = new QMediaPlayer(this);
        videoWidget = new QVideoWidget(dock_video);
        videoWidget ->resize(550,400);
        //videoWidget->move(25,30);
        player->setVideoOutput(videoWidget);
        player->setMedia(QUrl::fromLocalFile(path));
        //dock_video->setWidget(videoWidget);
        isPlay = true;
        player->play();

        playerIn = new QMediaPlayer(this);
        videoSurface = new VideoSurface;
        playerIn->setVideoOutput(videoSurface);
        playerIn->setMedia(QUrl::fromLocalFile(path));
        imageIsPlay = true;
        counter = 0;
        editCounter = 0;
        playerIn->play();

        connect(videoSurface, SIGNAL(frameAvailable(QVideoFrame &)), this, SLOT(ProcessFrame(QVideoFrame &)));

        videoCurrentPath = path;
        output("打开视频:"+path);

        slider_video = new QSlider(Qt::Horizontal);		// 进度条
        slider_video->setRange(0, player->duration()/1000);
        connect(slider_video, SIGNAL(sliderMoved(int)), this, SLOT(setPosition(int)));
        connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::updatePosition);

        QSlider *slider_liangdu = new QSlider(Qt::Horizontal);		// 亮度
        slider_liangdu->setRange(-255, 255);
        slider_liangdu->setValue(videoWidget->brightness());
        connect(slider_liangdu, &QSlider::sliderMoved, videoWidget, &QVideoWidget::setBrightness);
        connect(videoWidget, &QVideoWidget::brightnessChanged, slider_liangdu, &QSlider::setValue);

        QSlider *slider_duibidu = new QSlider(Qt::Horizontal);		// 对比度
        slider_duibidu->setRange(-255, 255);
        slider_duibidu->setValue(videoWidget->contrast());
        connect(slider_duibidu, &QSlider::sliderMoved, videoWidget, &QVideoWidget::setContrast);
        connect(videoWidget, &QVideoWidget::contrastChanged, slider_duibidu, &QSlider::setValue);

        QSlider *slider_sexiang = new QSlider(Qt::Horizontal);		// 色相
        slider_sexiang->setRange(-255, 255);
        slider_sexiang->setValue(videoWidget->contrast());
        connect(slider_sexiang, &QSlider::sliderMoved, videoWidget, &QVideoWidget::setHue);
        connect(videoWidget, &QVideoWidget::hueChanged, slider_sexiang, &QSlider::setValue);

        QSlider *slider_baohedu = new QSlider(Qt::Horizontal);		// 饱和度
        slider_baohedu->setRange(-255, 255);
        slider_baohedu->setValue(videoWidget->saturation());
        connect(slider_baohedu, &QSlider::sliderMoved, videoWidget, &QVideoWidget::setSaturation);
        connect(videoWidget, &QVideoWidget::saturationChanged, slider_baohedu, &QSlider::setValue);

        QPushButton *button_stop = new QPushButton(tr("停止"));
        connect(button_stop, SIGNAL(clicked()), this, SLOT(videoStop()));

        button_go = new QPushButton(tr("暂停"));
        connect(button_go, SIGNAL(clicked()), this, SLOT(videoPlay()));

        QLabel *label_liangdu = new QLabel(tr("亮度"));
        QLabel *label_duibi = new QLabel(tr("对比度"));
        QLabel *label_sexiang = new QLabel(tr("色相"));
        QLabel *label_baohedu = new QLabel(tr("饱和度"));

        QGridLayout *videoLayoutCountrol = new QGridLayout();
        videoLayoutCountrol->setAlignment(Qt::AlignHCenter);
        videoLayoutCountrol->addWidget(slider_video, 0, 1);
        videoLayoutCountrol->addWidget(button_stop, 1, 0);
        videoLayoutCountrol->addWidget(button_go, 1, 2);

        QWidget *videoWidgetCountrol = new QWidget(dock_video);
        videoWidgetCountrol->setLayout(videoLayoutCountrol);
        //videoWidgetCountrol->move(0,-200);
        //dock_video->setWidget(videoWidgetCountrol);

        QGridLayout *videoLayout = new QGridLayout();
        videoLayout->setAlignment(Qt::AlignHCenter);
        videoLayout->addWidget(label_liangdu, 2, 0);
        videoLayout->addWidget(slider_liangdu, 2, 1);
        videoLayout->addWidget(label_duibi, 2, 2);
        videoLayout->addWidget(slider_duibidu, 2, 3);
        videoLayout->addWidget(label_sexiang, 3, 0);
        videoLayout->addWidget(slider_sexiang, 3, 1);
        videoLayout->addWidget(label_baohedu, 3, 2);
        videoLayout->addWidget(slider_baohedu, 3, 3);

        QWidget *videoWidget1 = new QWidget(dock_video);
        videoWidget1->setLayout(videoLayout);

        QGridLayout *allLayout = new QGridLayout();
        allLayout->addWidget(videoWidget, 0, 0);
        allLayout->addWidget(videoWidgetCountrol, 2, 0);
        allLayout->addWidget(videoWidget1, 3, 0);
        QWidget *allWidget = new QWidget(dock_video);
        allWidget->setLayout(allLayout);

        dock_video->setWidget(allWidget);

        dock_image_video = new QDockWidget(tr("视频控制"), this);
        dock_image_video->setMaximumWidth(450);
        dock_image_video->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetClosable);         // 设置为可移动可浮动，但不可关闭
        dock_image_video->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);  // 可移动范围：左右
        tabifyDockWidget(dock_Color, dock_image_video);

        button_Image_go = new QPushButton(tr("暂停"));
        connect(button_Image_go, SIGNAL(clicked()), this, SLOT(ImageVideoPlay()));

        QPushButton *button_Image_stop = new QPushButton(tr("停止"));
        connect(button_Image_stop, SIGNAL(clicked()), this, SLOT(ImageVideoStop()));

        QPushButton *button_Image_pro = new QPushButton(tr("预览"));
        connect(button_Image_pro, SIGNAL(clicked()), this, SLOT(ImageVideoPro()));

        zhen_edit = new QSpinBox();
        zhen_edit->setAlignment(Qt::AlignCenter);
        zhen_edit->setRange(0, 1000);
        zhen_edit->setValue(0);
        QLabel *label_show_zhen = new QLabel(tr("帧"));
        QPushButton *button_zhen_ok = new QPushButton(tr("确定"));
        connect(button_zhen_ok, SIGNAL(clicked()), this, SLOT(Imagezhen()));

        /*QLabel *label_time = new QLabel(tr("时间："));
        label_time_in = new QLabel(tr("0"));
        QLabel *label_time_out = new QLabel(tr("ms"));
        QLabel *label_zhen = new QLabel(tr("帧数："));
        label_zhen_in = new QLabel(tr("0"));
        QLabel *label_zhen_out = new QLabel(tr("帧"));*/

        QGridLayout *imageVideoLayout = new QGridLayout();
        imageVideoLayout->setAlignment(Qt::AlignVCenter);
        imageVideoLayout->addWidget(zhen_edit, 0, 0);
        imageVideoLayout->addWidget(label_show_zhen, 0, 1);
        imageVideoLayout->addWidget(button_zhen_ok, 0, 2);
        /*imageVideoLayout->addWidget(label_zhen, 1, 0);
        imageVideoLayout->addWidget(label_zhen_in, 1, 1);
        imageVideoLayout->addWidget(label_zhen_out, 1, 2);*/
        imageVideoLayout->addWidget(button_Image_stop, 2, 0);
        imageVideoLayout->addWidget(button_Image_go, 2, 1);
        imageVideoLayout->addWidget(button_Image_pro, 2, 2);

        QWidget *allImageWidget = new QWidget(dock_image_video);
        allImageWidget->setLayout(imageVideoLayout);
        dock_image_video->setWidget(allImageWidget);
    }
}

// 保存视频
void MainWindow::on_action_2_triggered()
{
    QString path;
    if (videoCurrentPath.isEmpty())      // 判断是新建的图像还是打开的图像
    {
        path = QFileDialog::getSaveFileName(this, tr("保存视频"), ".", tr("video(*.mp4)"));
        {
            if (!path.isEmpty())
                videoCurrentPath = path;
        }
    }
    //QMediaPlayer videoSave = player->currentMedia();     // 读取视频
    //videoSave.save(videoCurrentPath);                          // 保存图像
    output("视频保存: " + path);
}

// 视频播放
void MainWindow::videoPlay()
{
    if(isPlay)
    {
        player->pause();
        button_go->setText("播放");
        isPlay = false;
    }
    else
    {
        player->play();
        button_go->setText("暂停");
        isPlay = true;
    }
}

// 视频停止
void MainWindow::videoStop()
{
    player->stop();
}

// 更新播放滑块显示
void MainWindow::updatePosition(qint64 postion)
{
    slider_video->setMaximum(player->duration()/1000);
    slider_video->setValue(postion/1000);
}

// 设置播放进度
void MainWindow::setPosition(int position)
{
    player->setPosition(position*1000);
}

// 取帧
void MainWindow::ProcessFrame(QVideoFrame &frame)
{
    qDebug() << "=============ProcessFrame===============";
    qDebug() << "width : " << frame.width() << " height : " << frame.height();
    qDebug() << "start time : " << frame.startTime()/1000 << "ms";
    qDebug() << "end time : " << frame.endTime()/1000 << "ms";
    qDebug() << "pixelFormat :" << frame.pixelFormat();

    frame.map(QAbstractVideoBuffer::ReadOnly);
    QImage recvImage(frame.bits(), frame.width(), frame.height(), QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat()));
    ShowImage(recvImage, false);
    imageVideo[counter] = recvImage.copy();
    counter++;
    time = frame.endTime()/1000;
    qDebug() << "frame data size :" << frame.mappedBytes();
    qDebug() << "帧数 :" << counter;
    frame.unmap();
}

// 图片视频播放
void MainWindow::ImageVideoPlay()
{
    if(imageIsPlay)
    {
        playerIn->pause();
        button_Image_go->setText("播放");
        imageIsPlay = false;
    }
    else
    {
        playerIn->play();
        button_Image_go->setText("暂停");
        imageIsPlay = true;
    }

}

// 图片视频停止
void MainWindow::ImageVideoStop()
{
    playerIn->stop();
}

// 图片视频预览
void MainWindow::ImageVideoPro()
{
    for(int i = 0; i<editCounter; i++)
    {
        int a = counters[i];
        imageVideo[a] = editeImageVideo[i];
        qDebug() << "修改帧数 :" << a;
    }
    editCounter = 0;
    zhenshu = 0;
    long indexTime = time/counter;
    on_new_2_triggered();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(videoTimer()));
    timer->start(indexTime);
    //QTimer::singleShot(indexTime, this, SLOT(videoTimer()));
}

// 计时器响应
void MainWindow::videoTimer()
{
    ShowImage(imageVideo[zhenshu], false);
    qDebug() << "帧数 :" << zhenshu;
    if(zhenshu >= counter)
    {
        timer->stop();
    }
    zhenshu++;
}

// 查看帧
void MainWindow::Imagezhen()
{
    if(zhen_edit->text().toInt() < counter){
        ShowImage(imageVideo[zhen_edit->text().toInt()], false);
    }
}
