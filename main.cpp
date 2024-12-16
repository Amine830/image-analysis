#include "ImageProcessor.h"
#include <opencv2/opencv.hpp>

int main() {
    ImageProcessor processor;

    // Charger une image
    cv::Mat image = cv::imread("img/donnee1/lena.png", cv::IMREAD_COLOR);
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
    // cv::imshow("Original Image", image);
    // cv::imshow("Filtered Image with Median", filteredImage1);
    // cv::imshow("Filtered Image with Sobel", filteredImage2);
    // cv::imshow("Filtered Image with Gaussian", filteredImage3);
    // cv::imshow("Filtered Image with Mean", filteredImage4);


    // Afficher l'image originale
    cv::imshow("Original Image", image);
    // Appliquer différentes transformations
    cv::Mat zoomed = processor.zoom(image, 1.5);       // Zoom 1.5x
    cv::Mat reduced = processor.reduce(image, 0.5);   // Réduction 0.5x
    cv::Mat rotated = processor.rotate(image, 45);    // Rotation 45 degrés
    cv::Mat flipped = processor.flip(image, 1);       // Flip horizontal
    cv::Mat compressed = processor.compress(image);   // Compression

    // Afficher les résultats
    cv::imshow("Zoomed Image", zoomed);
    cv::imshow("Reduced Image", reduced);
    cv::imshow("Rotated Image", rotated);
    cv::imshow("Flipped Image", flipped);
    cv::imshow("Compressed Image", compressed);
    

    // Histogramme 
    // cv::Mat hist = processor.calculateHistogram(image);
    // cv::imshow("Histogram", hist);

    // // Histogramme cumulé
    // cv::Mat cumulatedHist = processor.calculateCumulatedHistogram(image);
    // cv::imshow("Cumulated Histogram", cumulatedHist);

    // // Égalisation d'histogramme
    // cv::Mat equalizedImage = processor.equalizeHistogram(image);
    // cv::imshow("Equalized Image", equalizedImage);

    // //afficher l'histogramme de l'image après égalisation
    // cv::Mat histEqualized = processor.calculateHistogram(equalizedImage);
    // cv::imshow("Histogram Equalized", histEqualized);

    // Étirement d'histogramme
    // cv::Mat stretchedImage = processor.stretchHistogram(image);
    // cv::imshow("Stretched Image", stretchedImage);

    // // Afficher l'histogramme de l'image après étirement
    // cv::Mat histStretched = processor.calculateHistogram(stretchedImage);
    // cv::imshow("Histogram Stretched", histStretched);

    cv::waitKey(0);
    return 0;
}
