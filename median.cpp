#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

cv::Mat applyMedianFilter(const cv::Mat& src, int kernelSize) {
    cv::Mat dst = src.clone();
    int border = kernelSize / 2;

    for (int y = border; y < src.rows - border; ++y) {
        for (int x = border; x < src.cols - border; ++x) {
            for (int c = 0; c < src.channels(); ++c) {
                std::vector<uchar> neighborhood;

                for (int ky = -border; ky <= border; ++ky) {
                    for (int kx = -border; kx <= border; ++kx) {
                        neighborhood.push_back(src.at<cv::Vec3b>(y + ky, x + kx)[c]);
                    }
                }

                std::sort(neighborhood.begin(), neighborhood.end());
                dst.at<cv::Vec3b>(y, x)[c] = neighborhood[neighborhood.size() / 2];
            }
        }
    }

    return dst;
}

int main() {
    // Charger l'image en couleur
    cv::Mat image = cv::imread("img/Donnee2/mer.jpg", cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "Could not open or find the image" << std::endl;
        return -1;
    }

    int kernelSize = 5; // Taille du noyau (doit être impair)
    cv::Mat filtered_image = applyMedianFilter(image, kernelSize);

    cv::imshow("Original Image", image);
    cv::imshow("Filtered Image", filtered_image);

    cv::waitKey(0);

    return 0;
}
