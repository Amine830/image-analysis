#ifndef FILTERS_H
#define FILTERS_H

#include <opencv2/opencv.hpp>

// Déclaration des fonctions de filtrage

/**
 * @brief Applique un filtre médian à une image.
 * 
 * @param src L'image source.
 * @param kernelSize La taille du noyau
 * @return Une image avec le filtre médian appliqué.
 */
cv::Mat applyMedianFilter(const cv::Mat& src, int kernelSize);

/**
 * @brief Applique un flou gaussien à une image.
 * 
 * @param src L'image source.
 * @param kernelSize La taille du noyau (doit être impaire).
 * @param sigma L'écart-type de la distribution gaussienne.
 * @return Une image avec le flou gaussien appliqué.
 */
cv::Mat applyGaussianBlur(const cv::Mat& src, int kernelSize, double sigma);

/**
 * @brief Applique un filtre de Sobel pour la détection de contours.
 * 
 * @param src L'image source.
 * @return Une image avec le filtre de Sobel appliqué.
 */
cv::Mat applySobelFilter(const cv::Mat& src);

/**
 * @brief Applique un filtre moyen à une image.
 * 
 * @param src L'image source.
 * @param kernelSize La taille du noyau (doit être impaire).
 * @return Une image avec le filtre moyen appliqué.
 */
cv::Mat applyMeanFilter(const cv::Mat& src, int kernelSize);

#endif // FILTERS_H
