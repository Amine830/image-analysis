#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connecter les actions aux slots
    connect(ui->actionLoad_Image, &QAction::triggered, this, &MainWindow::loadNewImage);
    connect(ui->actionSave_Image, &QAction::triggered, this, &MainWindow::saveImage);
    connect(ui->actionApply_Median_Filter , &QAction::triggered, this, &MainWindow::applyMedianFilterWarp);
    connect(ui->actionApply_Gaussian_Blur , &QAction::triggered, this, &MainWindow::applyGaussianBlurWarp);
    connect(ui->actionApply_Sobel_Filter , &QAction::triggered, this, &MainWindow::applySobelFilterWarp);
    connect(ui->actionApply_Mean_Filter , &QAction::triggered, this, &MainWindow::applyMeanFilterWarp);

    // connect buttons to slots
    connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::loadNewImage);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::saveImage);
    connect(ui->medianFilterButton, &QPushButton::clicked, this, &MainWindow::applyMedianFilterWarp);
    connect(ui->gaussianBlurButton, &QPushButton::clicked, this, &MainWindow::applyGaussianBlurWarp);
    connect(ui->sobelFilterButton, &QPushButton::clicked, this, &MainWindow::applySobelFilterWarp);
    connect(ui->meanFilterButton, &QPushButton::clicked, this, &MainWindow::applyMeanFilterWarp);

    connect(ui->equalizeButton, &QPushButton::clicked, this, &MainWindow::applyEqualizeHistogram);
    connect(ui->stretchButton, &QPushButton::clicked, this, &MainWindow::applyStretchHistogram);

    // connect transformations to slots
    connect(ui->zoomButton, &QPushButton::clicked, this, &MainWindow::zoomIn);
    connect(ui->reduceButton, &QPushButton::clicked, this, &MainWindow::zoomOut);
    connect(ui->rotateButton, &QPushButton::clicked, this, &MainWindow::rotateImage);
    connect(ui->flipButton, &QPushButton::clicked, this, &MainWindow::flipImage);
    connect(ui->compressButton, &QPushButton::clicked, this, &MainWindow::compressImage);

}

MainWindow::~MainWindow()
{
    delete ui;
}

// Charger une nouvelle image
void MainWindow::loadNewImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Image", "", "Images (*.png *.xpm *.jpg)");
    if (fileName.isEmpty()) return;

    currentImage = cv::imread(fileName.toStdString());
    if (currentImage.empty()) {
        QMessageBox::warning(this, "Error", "Failed to load image.");
        return;
    }

    displayImage(currentImage);

    histImage = processor.calculateHistogram(currentImage);
    displayHist(histImage);

    cumHistImage = processor.calculateCumulatedHistogram(currentImage);
    displayCumHist(cumHistImage);
}

//--------------------------------------------------------------------------------------------
// Appliquer des filtres
//--------------------------------------------------------------------------------------------

// Appliquer un filtre à l'image
void MainWindow::applyMedianFilterWarp()
{
    if (currentImage.empty()) {
        QMessageBox::warning(this, "Error", "No image loaded.");
        return;
    }

    processor.addFilter("Median", [](const cv::Mat& src) { return applyMedianFilter(src, 5); });
    currentImage = processor.applyFilter("Median", currentImage);
    displayImage(currentImage);

    histImage = processor.calculateHistogram(currentImage);
    displayHist(histImage);

    cumHistImage = processor.calculateCumulatedHistogram(currentImage);
    displayCumHist(cumHistImage);
}

void MainWindow::applyGaussianBlurWarp()
{
    if (currentImage.empty()) {
        QMessageBox::warning(this, "Error", "No image loaded.");
        return;
    }

    processor.addFilter("Gaussian", [](const cv::Mat& src) { return applyGaussianBlur(src, 5, 1.0); });
    currentImage = processor.applyFilter("Gaussian", currentImage);
    displayImage(currentImage);

    histImage = processor.calculateHistogram(currentImage);
    displayHist(histImage);

    cumHistImage = processor.calculateCumulatedHistogram(currentImage);
    displayCumHist(cumHistImage);
}

void MainWindow::applySobelFilterWarp()
{
    if (currentImage.empty()) {
        QMessageBox::warning(this, "Error", "No image loaded.");
        return;
    }

    processor.addFilter("Sobel", [](const cv::Mat& src) { return applySobelFilter(src); });
    currentImage = processor.applyFilter("Sobel", currentImage);
    displayImage(currentImage);

    histImage = processor.calculateHistogram(currentImage);
    displayHist(histImage);

    cumHistImage = processor.calculateCumulatedHistogram(currentImage);
    displayCumHist(cumHistImage);
}

void MainWindow::applyMeanFilterWarp()
{
    if (currentImage.empty()) {
        QMessageBox::warning(this, "Error", "No image loaded.");
        return;
    }

    processor.addFilter("Mean", [](const cv::Mat& src) { return applyMeanFilter(src, 3); });
    currentImage = processor.applyFilter("Mean", currentImage);
    displayImage(currentImage);

    histImage = processor.calculateHistogram(currentImage);
    displayHist(histImage);

    cumHistImage = processor.calculateCumulatedHistogram(currentImage);
    displayCumHist(cumHistImage);
}

void MainWindow::applyEqualizeHistogram()
{
    if (currentImage.empty()) {
        QMessageBox::warning(this, "Error", "No image loaded.");
        return;
    }

    currentImage = processor.equalizeHistogram(currentImage);
    displayImage(currentImage);

    histImage = processor.calculateHistogram(currentImage);
    displayHist(histImage);

    cumHistImage = processor.calculateCumulatedHistogram(currentImage);
    displayCumHist(cumHistImage);
}

void MainWindow::applyStretchHistogram()
{
    if (currentImage.empty()) {
        QMessageBox::warning(this, "Error", "No image loaded.");
        return;
    }

    currentImage = processor.stretchHistogram(currentImage);
    displayImage(currentImage);

    histImage = processor.calculateHistogram(currentImage);
    displayHist(histImage);

    cumHistImage = processor.calculateCumulatedHistogram(currentImage);
    displayCumHist(cumHistImage);
}


//--------------------------------------------------------------------------------------------
// Appliquer des transformations géométriques
//--------------------------------------------------------------------------------------------

// Zoomer sur l'image
void MainWindow::zoomIn()
{
    if (currentImage.empty()) {
        QMessageBox::warning(this, "Error", "No image loaded.");
        return;
    }

    currentImage = processor.zoom(currentImage, 1.5);
    displayImage(currentImage);

    histImage = processor.calculateHistogram(currentImage);
    displayHist(histImage);

    cumHistImage = processor.calculateCumulatedHistogram(currentImage);
    displayCumHist(cumHistImage);
}

// Dézoomer sur l'image
void MainWindow::zoomOut()
{
    if (currentImage.empty()) {
        QMessageBox::warning(this, "Error", "No image loaded.");
        return;
    }

    currentImage = processor.zoom(currentImage, 0.5);
    displayImage(currentImage);

    histImage = processor.calculateHistogram(currentImage);
    displayHist(histImage);

    cumHistImage = processor.calculateCumulatedHistogram(currentImage);
    displayCumHist(cumHistImage);
}

// Faire pivoter l'image
void MainWindow::rotateImage()
{
    if (currentImage.empty()) {
        QMessageBox::warning(this, "Error", "No image loaded.");
        return;
    }

    currentImage = processor.rotate(currentImage, 90);
    displayImage(currentImage);

    histImage = processor.calculateHistogram(currentImage);
    displayHist(histImage);

    cumHistImage = processor.calculateCumulatedHistogram(currentImage);
    displayCumHist(cumHistImage);
}

// Retourner l'image
void MainWindow::flipImage()
{
    if (currentImage.empty()) {
        QMessageBox::warning(this, "Error", "No image loaded.");
        return;
    }

    currentImage = processor.flip(currentImage, 1);
    displayImage(currentImage);

    histImage = processor.calculateHistogram(currentImage);
    displayHist(histImage);

    cumHistImage = processor.calculateCumulatedHistogram(currentImage);
    displayCumHist(cumHistImage);
}

// Compresser l'image
void MainWindow::compressImage()
{
    if (currentImage.empty()) {
        QMessageBox::warning(this, "Error", "No image loaded.");
        return;
    }

    currentImage = processor.compress(currentImage);
    displayImage(currentImage);

    histImage = processor.calculateHistogram(currentImage);
    displayHist(histImage);

    cumHistImage = processor.calculateCumulatedHistogram(currentImage);
    displayCumHist(cumHistImage);
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------


// Sauvegarder l'image
void MainWindow::saveImage()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Image", "", "Images (*.png *.xpm *.jpg)");
    if (fileName.isEmpty()) return;

    if (!cv::imwrite(fileName.toStdString(), currentImage)) {
        QMessageBox::warning(this, "Error", "Failed to save image.");
    }
}

// Afficher l'image dans le label
void MainWindow::displayImage(const cv::Mat &image)
{
    if (image.empty()) return;

    QImage qImage(image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
    QPixmap pixmap = QPixmap::fromImage(qImage.rgbSwapped());
    ui->imageLabel->setPixmap(pixmap.scaled(ui->imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

// Afficher l'histogramme dans le label
void MainWindow::displayHist(const cv::Mat &histImage)
{
    if (histImage.empty()) return;

    QImage qImage(histImage.data, histImage.cols, histImage.rows, histImage.step, QImage::Format_Grayscale8);
    QPixmap pixmap = QPixmap::fromImage(qImage);
    ui->histLabel->setPixmap(pixmap.scaled(ui->histLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

// Afficher l'histogramme cumulé dans le label
void MainWindow::displayCumHist(const cv::Mat &cumHist)
{
    if (cumHist.empty()) return;

    QImage qImage(cumHist.data, cumHist.cols, cumHist.rows, cumHist.step, QImage::Format_Grayscale8);
    QPixmap pixmap = QPixmap::fromImage(qImage);
    ui->cumHistLabel->setPixmap(pixmap.scaled(ui->cumHistLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}