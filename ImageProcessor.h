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

    // Afficher un histogramme de couleurs
    void displayHistogram(const cv::Mat& src);

private:
    std::map<std::string, FilterFunction> filters;
};

#endif // IMAGE_PROCESSOR_H
