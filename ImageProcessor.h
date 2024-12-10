// ImageProcessor.h
#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include"Filters.h"
#include <map>
#include <functional>
#include <cmath>
#include <vector>
#include <algorithm>


class ImageProcessor {
public:
    using FilterFunction = std::function<cv::Mat(const cv::Mat&)>;

    // Ajouter un filtre au gestionnaire
    void addFilter(const std::string& name, FilterFunction filter);

    // Appliquer un filtre par nom
    cv::Mat applyFilter(const std::string& name, const cv::Mat& src);

    // Calculer un histogramme
    cv::Mat calculateHistogram(const cv::Mat& src);

    // Calculer un histogramme cumulé
    cv::Mat calculateCumulatedHistogram(const cv::Mat& src);

    // Calculer une Égalisation d'histogramme
   cv::Mat equalizeHistogramColorFromScratch(const cv::Mat& src);

    // Calculer une Égalisation d'histogramme
   cv::Mat stretchHistogram(const cv::Mat& src);

    static cv::Mat zoom(const cv::Mat &src, double scaleFactor);
    static cv::Mat reduce(const cv::Mat &src, double scaleFactor);
    static cv::Mat rotate(const cv::Mat &src, double angle);
    static cv::Mat translate(const cv::Mat &src, int dx, int dy);
    static cv::Mat flip(const cv::Mat &src, int flipCode);
    static cv::Mat compress(const cv::Mat &src);


private:
    std::map<std::string, FilterFunction> filters;
};

#endif // IMAGE_PROCESSOR_H
