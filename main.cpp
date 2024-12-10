#include "ImageProcessor.h"
#include <opencv2/opencv.hpp>

int main() {
    ImageProcessor processor;

    // Charger une image
    cv::Mat image = cv::imread("img/Donnee2/cathedrale.jpg", cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "Could not open or find the image" << std::endl;
        return -1;
    }

    // Enregistrer des filtres
    processor.addFilter("Median", [](const cv::Mat& src) { return applyMedianFilter(src, 5); });
    processor.addFilter("Gaussian", [](const cv::Mat& src) { return applyGaussianBlur(src, 5, 1.0); });
    processor.addFilter("Sobel", applySobelFilter);
    processor.addFilter("Mean", [](const cv::Mat& src) { return applyMeanFilter(src, 3); });

    // Appliquer les filtres
    cv::Mat filteredImage1 = processor.applyFilter("Median", image);
    cv::Mat filteredImage2 = processor.applyFilter("Sobel", image);
    cv::Mat filteredImage3 = processor.applyFilter("Gaussian", image);
    cv::Mat filteredImage4 = processor.applyFilter("Mean", image);

    // Afficher les résultats
    cv::imshow("Original Image", image);
    cv::imshow("Filtered Image with Median", filteredImage1);
    cv::imshow("Filtered Image with Sobel", filteredImage2);
    cv::imshow("Filtered Image with Gaussian", filteredImage3);
    cv::imshow("Filtered Image with Mean", filteredImage4);

    cv::waitKey(0);
    return 0;
}
