#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

cv::Mat calculateHistogram(const cv::Mat& src) {
    std::vector<int> histogram(256, 0);

    for (int y = 0; y < src.rows; ++y) {
        for (int x = 0; x < src.cols; ++x) {
            int pixelValue = src.at<uchar>(y, x);
            histogram[pixelValue]++;
        }
    }

    cv::Mat histImage(256, 256, CV_8U, cv::Scalar(255));
    int max = *std::max_element(histogram.begin(), histogram.end());

    for (int i = 0; i < 256; ++i) {
        int value = static_cast<int>(histogram[i] * 256 / max);
        cv::line(histImage, cv::Point(i, 256), cv::Point(i, 256 - value), cv::Scalar(0));
    }

    return histImage;
}

cv::Mat calculateCumulativeHistogram(const cv::Mat& src) {
    std::vector<int> histogram(256, 0);
    std::vector<int> cumulativeHistogram(256, 0);

    for (int y = 0; y < src.rows; ++y) {
        for (int x = 0; x < src.cols; ++x) {
            int pixelValue = src.at<uchar>(y, x);
            histogram[pixelValue]++;
        }
    }

    cumulativeHistogram[0] = histogram[0];
    for (int i = 1; i < 256; ++i) {
        cumulativeHistogram[i] = cumulativeHistogram[i - 1] + histogram[i];
    }

    cv::Mat histImage(256, 256, CV_8U, cv::Scalar(255));
    int max = *std::max_element(cumulativeHistogram.begin(), cumulativeHistogram.end());

    for (int i = 0; i < 256; ++i) {
        int value = static_cast<int>(cumulativeHistogram[i] * 256 / max);
        cv::line(histImage, cv::Point(i, 256), cv::Point(i, 256 - value), cv::Scalar(0));
    }

    return histImage;
}

int main() {
    cv::Mat image = cv::imread("img/Donnee1/lena2.png", cv::IMREAD_GRAYSCALE);
    if (image.empty()) {
        std::cerr << "Could not open or find the image" << std::endl;
        return -1;
    }

    cv::Mat histImage = calculateHistogram(image);
    cv::Mat cumulativeHistImage = calculateCumulativeHistogram(image);

    cv::imshow("Original Image", image);
    cv::imshow("Histogram", histImage);
    cv::imshow("Cumulative Histogram", cumulativeHistImage);
    cv::waitKey(0);

    return 0;
}
