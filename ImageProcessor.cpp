#include "ImageProcessor.h"
#include <iostream>

using namespace std;

// Fonction pour ajouter un filtre au gestionnaire de filtres
void ImageProcessor::addFilter(const std::string &name, FilterFunction filter)
{
    filters[name] = filter;
}

// Fonctoion pour ppliquer un filtre par nom
cv::Mat ImageProcessor::applyFilter(const std::string &name, const cv::Mat &src)
{
    if (filters.find(name) != filters.end())
    {
        return filters[name](src);
    }
    else
    {
        std::cerr << "Filter not found: " << name << std::endl;
        return src.clone();
    }
}

/****************************************************************************************
 *                               TRAITEMENTS & HISTOGRAMMES                             *
 ****************************************************************************************/

// Calculer un histogramme de couleurs
cv::Mat ImageProcessor::calculateHistogram(const cv::Mat &src)
{
    std::vector<int> histogram(256, 0);

    for (int y = 0; y < src.rows; ++y)
    {
        for (int x = 0; x < src.cols; ++x)
        {
            int pixelValue = src.at<uchar>(y, x);
            histogram[pixelValue]++;
        }
    }

    cv::Mat histImage(256, 256, CV_8U, cv::Scalar(255));
    int max = *std::max_element(histogram.begin(), histogram.end());

    for (int i = 0; i < 256; ++i)
    {
        int value = static_cast<int>(histogram[i] * 256 / max);
        cv::line(histImage, cv::Point(i, 256), cv::Point(i, 256 - value), cv::Scalar(0));
    }

    return histImage;
}

// Calculer un histogramme cumulé
cv::Mat ImageProcessor::calculateCumulatedHistogram(const cv::Mat &src)
{
    std::vector<int> histogram(256, 0);
    std::vector<int> cumulativeHistogram(256, 0);
    for (int y = 0; y < src.rows; ++y)
    {
        for (int x = 0; x < src.cols; ++x)
        {
            int pixelValue = src.at<uchar>(y, x);
            histogram[pixelValue]++;
        }
    }
    cumulativeHistogram[0] = histogram[0];
    for (int i = 1; i < 256; ++i)
    {
        cumulativeHistogram[i] = cumulativeHistogram[i - 1] + histogram[i];
    }
    cv::Mat histImage(256, 256, CV_8U, cv::Scalar(255));
    int max = *std::max_element(cumulativeHistogram.begin(), cumulativeHistogram.end());
    for (int i = 0; i < 256; ++i)
    {
        int value = static_cast<int>(cumulativeHistogram[i] * 256 / max);
        cv::line(histImage, cv::Point(i, 256), cv::Point(i, 256 - value), cv::Scalar(0));
    }
    return histImage;
}

// Égalisation d'histogramme
cv::Mat ImageProcessor::equalizeHistogram(const cv::Mat &src){

    CV_Assert(src.type() == CV_8UC3); // Vérification : image en couleur

    // Convertir l'image en espace YCrCb
    cv::Mat ycrcb;
    cv::cvtColor(src, ycrcb, cv::COLOR_BGR2YCrCb);

    // Diviser les canaux
    std::vector<cv::Mat> channels;
    cv::split(ycrcb, channels);

    // Calcul de l'histogramme pour le canal Y
    std::vector<int> histogram(256, 0);
    for (int y = 0; y < channels[0].rows; ++y)
    {
        for (int x = 0; x < channels[0].cols; ++x)
        {
            int pixelValue = channels[0].at<uchar>(y, x);
            histogram[pixelValue]++;
        }
    }

    // Calcul de la distribution de probabilité P(y)
    int totalPixels = channels[0].rows * channels[0].cols;
    std::vector<double> probability(256, 0.0);
    for (int i = 0; i < 256; ++i)
    {
        probability[i] = static_cast<double>(histogram[i]) / totalPixels;
    }

    // Calcul de la CDF
    std::vector<double> cdf(256, 0.0);
    cdf[0] = probability[0];
    for (int i = 1; i < 256; ++i)
    {
        cdf[i] = cdf[i - 1] + probability[i];
    }

    // Mise à jour des valeurs d'intensité lumineuse
    std::vector<uchar> lut(256, 0);
    double cdfMin = cdf[0];
    for (int i = 0; i < 256; ++i)
    {
        lut[i] = static_cast<uchar>((cdf[i] - cdfMin) * 255 / (1.0 - cdfMin));
    }

    // Appliquer la LUT au canal Y
    for (int y = 0; y < channels[0].rows; ++y)
    {
        for (int x = 0; x < channels[0].cols; ++x)
        {
            channels[0].at<uchar>(y, x) = lut[channels[0].at<uchar>(y, x)];
        }
    }

    // Fusionner les canaux
    cv::Mat equalizedYCrCb;
    cv::merge(channels, equalizedYCrCb);

    // Reconvertir en espace BGR
    cv::Mat equalizedImage;
    cv::cvtColor(equalizedYCrCb, equalizedImage, cv::COLOR_YCrCb2BGR);

    return equalizedImage;
}

// Étirement d'histogramme
cv::Mat ImageProcessor::stretchHistogram(const cv::Mat &src) {

    CV_Assert(src.type() == CV_8UC3); // Ensure the image is a color image (BGR)

    // Split the image into its three channels (Blue, Green, Red)
    std::vector<cv::Mat> channels(3);
    cv::split(src, channels);

    // Process each channel independently
    for (int i = 0; i < 3; ++i)
    {
        // Find the minimum and maximum pixel values in the current channel
        double minVal, maxVal;
        cv::minMaxLoc(channels[i], &minVal, &maxVal);

        // Apply the histogram stretching on the current channel
        for (int y = 0; y < channels[i].rows; ++y)
        {
            for (int x = 0; x < channels[i].cols; ++x)
            {
                // Retrieve the pixel value and stretch it to the [0, 255] range
                uchar pixelValue = channels[i].at<uchar>(y, x);
                int stretchedValue = static_cast<int>((pixelValue - minVal) * 255 / (maxVal - minVal));
                channels[i].at<uchar>(y, x) = static_cast<uchar>(stretchedValue);
            }
        }
    }

    // Merge the channels back to a single image
    cv::Mat stretchedImage;
    cv::merge(channels, stretchedImage);

    return stretchedImage;
}

/****************************************************************************************
 *                  OPERATIONS DE TRANSFORMATION GÉOMÉTRIQUE D'IMAGES                   *
 ****************************************************************************************/

// Zoom (agrandissement) 
cv::Mat ImageProcessor::zoom(const cv::Mat &src, double scaleFactor)
{
    int newRows = src.rows;
    int newCols = src.cols;
    cv::Mat dst(newRows, newCols, src.type());

    for (int y = 0; y < newRows; ++y)
    {
        for (int x = 0; x < newCols; ++x)
        {
            int srcY = static_cast<int>((y - newRows / 2) / scaleFactor + newRows / 2);
            int srcX = static_cast<int>((x - newCols / 2) / scaleFactor + newCols / 2);

            if (srcY >= 0 && srcY < src.rows && srcX >= 0 && srcX < src.cols)
            {
                // Remplir avec les valeurs de l'image source si dans les limites
                dst.at<cv::Vec3b>(y, x) = src.at<cv::Vec3b>(srcY, srcX);
            }
            else
            {
                // Remplir avec du noir si hors limites
                dst.at<cv::Vec3b>(y, x) = cv::Vec3b(0, 0, 0); 
            }
        }
    }

    return dst;
}

// Réduction 
cv::Mat ImageProcessor::reduce(const cv::Mat &src, double scaleFactor)
{
    // Vérifier que le facteur de réduction est valide
    if (scaleFactor <= 0 || scaleFactor >= 1)
    {
        std::cerr << "Scale factor doit être compris entre 0 et 1" << std::endl;
        return src;
    }
    return zoom(src, scaleFactor);
}

// Compression 
cv::Mat ImageProcessor::compress(const cv::Mat &src){

    CV_Assert(src.type() == CV_8UC3); // Vérification : image en couleur

    // Diviser l'image en ses trois canaux (Bleu, Vert, Rouge)
    std::vector<cv::Mat> channels(3);
    cv::split(src, channels);

    // Processus de chaque canal indépendamment
    for (int i = 0; i < 3; ++i)
    {
        // Trouver les valeurs minimale et maximale des pixels dans le canal actuel
        double minVal = 255, maxVal = 0;
        for (int y = 0; y < channels[i].rows; ++y)
        {
            for (int x = 0; x < channels[i].cols; ++x)
            {
                uchar pixelValue = channels[i].at<uchar>(y, x);
                if (pixelValue < minVal) minVal = pixelValue;
                if (pixelValue > maxVal) maxVal = pixelValue;
            }
        }

        // Appliquer la compression d'histogramme sur le canal actuel
        for (int y = 0; y < channels[i].rows; ++y)
        {
            for (int x = 0; x < channels[i].cols; ++x)
            {
                uchar pixelValue = channels[i].at<uchar>(y, x);
                int stretchedValue = static_cast<int>((pixelValue - minVal) * 255 / (maxVal - minVal));
                channels[i].at<uchar>(y, x) = static_cast<uchar>(stretchedValue);
            }
        }
    }

    // Fusionner les canaux en une seule image
    cv::Mat compressedImage;
    cv::merge(channels, compressedImage);

    return compressedImage;
}

// Rotation
cv::Mat ImageProcessor::rotate(const cv::Mat &src, double angle){
    int rows = src.rows;
    int cols = src.cols;
    cv::Mat dst(rows, cols, src.type());

    // convertir l'angle en radians
    double radians = angle * CV_PI / 180.0;
    double cosA = cos(radians);
    double sinA = sin(radians);

    int centerX = cols / 2;
    int centerY = rows / 2;

    // Appliquer la rotation
    for (int y = 0; y < rows; ++y)
    {
        for (int x = 0; x < cols; ++x)
        {
            int newX = static_cast<int>((x - centerX) * cosA - (y - centerY) * sinA + centerX);
            int newY = static_cast<int>((x - centerX) * sinA + (y - centerY) * cosA + centerY);

            if (newX >= 0 && newX < cols && newY >= 0 && newY < rows)
            {
                // Remplir avec les valeurs de l'image source si dans les limites
                dst.at<cv::Vec3b>(y, x) = src.at<cv::Vec3b>(newY, newX);
            }
            else
            {
                // Remplir avec du noir si hors limites
                dst.at<cv::Vec3b>(y, x) = cv::Vec3b(0, 0, 0);
            }
        }
    }

    return dst;
}

// Flip
cv::Mat ImageProcessor::flip(const cv::Mat &src, int flipCode)
{
    int rows = src.rows;
    int cols = src.cols;
    cv::Mat dst(rows, cols, src.type());

    // Appliquer le flip
    for (int y = 0; y < rows; ++y)
    {
        for (int x = 0; x < cols; ++x)
        {
            int newX = x;
            int newY = y;

            if (flipCode == 0) // Vertical flip
            {
                newY = rows - y - 1;
            }
            else if (flipCode == 1) // Horizontal flip
            {
                newX = cols - x - 1;
            }
            else if (flipCode == -1) // flip horizontal et vertical
            {
                newX = cols - x - 1;
                newY = rows - y - 1;
            }

            // Remplir avec les valeurs de l'image source
            dst.at<cv::Vec3b>(y, x) = src.at<cv::Vec3b>(newY, newX);
        }
    }

    return dst;
}