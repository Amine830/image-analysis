#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../ImageProcessor.h" // Inclure les fonctionnalités console

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadNewImage();   
    void saveImage();       
    void displayImage(const cv::Mat &image);
    void displayHist(const cv::Mat &histImage);
    void displayCumHist(const cv::Mat &cumHist);

    // Appliquer des filtres
    void applyMedianFilterWarp();
    void applyGaussianBlurWarp();
    void applySobelFilterWarp();
    void applyMeanFilterWarp();
    void applyEqualizeHistogram();
    void applyStretchHistogram(); 

    // Appliquer des transformations géométriques
    void zoomIn();
    void zoomOut();
    void rotateImage();
    void flipImage();
    void compressImage();

private:
    Ui::MainWindow *ui;
    cv::Mat currentImage;   // Stocker l'image actuelle
    cv::Mat histImage;      // Stocker l'histogramme
    cv::Mat cumHistImage;   // Stocker l'histogramme cumulé
    ImageProcessor processor; 
};

#endif // MAINWINDOW_H
