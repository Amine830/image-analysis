#include "ImageProcessor.h"
#include <iostream>

// Ajouter un filtre au gestionnaire de filtres
void ImageProcessor::addFilter(const std::string& name, FilterFunction filter) {
    filters[name] = filter;
}

// Appliquer un filtre par nom
cv::Mat ImageProcessor::applyFilter(const std::string& name, const cv::Mat& src) {
    if (filters.find(name) != filters.end()) {
        return filters[name](src);
    } else {
        std::cerr << "Filter not found: " << name << std::endl;
        return src.clone();
    }
}
