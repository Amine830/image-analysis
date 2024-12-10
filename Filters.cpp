#include <opencv2/opencv.hpp>

cv::Mat applyMedianFilter(const cv::Mat &src, int kernelSize){
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

cv::Mat applyGaussianBlur(const cv::Mat &src, int kernelSize, double sigma)
{
    cv::Mat dst = src.clone();
    int border = kernelSize / 2;

    std::vector<std::vector<double>> kernel(kernelSize, std::vector<double>(kernelSize));
    double sum = 0.0;

    // Créer le noyau de convolution
    for (int y = -border; y <= border; ++y)
    {
        for (int x = -border; x <= border; ++x)
        {
            kernel[y + border][x + border] = exp(-(x * x + y * y) / (2 * sigma * sigma)) / (2 * CV_PI * sigma * sigma);
            sum += kernel[y + border][x + border];
        }
    }

    // Normaliser le noyau
    for (int y = 0; y < kernelSize; ++y)
    {
        for (int x = 0; x < kernelSize; ++x)
        {
            kernel[y][x] /= sum;
        }

    }

    // printf("Kernel:\n");
    for (int y = 0; y < kernelSize; ++y)
    {
        for (int x = 0; x < kernelSize; ++x)
        {
            printf("%f ", kernel[y][x]);
        }
        printf("\n");
    }

    for (int y = border; y < src.rows - border; ++y)
    {
        for (int x = border; x < src.cols - border; ++x)
        {
            for (int c = 0; c < src.channels(); ++c)
            {
                double sum = 0.0;

                for (int ky = -border; ky <= border; ++ky)
                {
                    for (int kx = -border; kx <= border; ++kx)
                    {
                        sum += src.at<cv::Vec3b>(y + ky, x + kx)[c] * kernel[ky + border][kx + border];
                    }
                }

                dst.at<cv::Vec3b>(y, x)[c] = static_cast<uchar>(sum);
            }
        }
    }

    return dst;
}

cv::Mat applySobelFilter(const cv::Mat &src)
{
    cv::Mat dst = src.clone();
    cv::Mat kernel_x = (cv::Mat_<int>(5, 5) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
    cv::Mat kernel_y = (cv::Mat_<int>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);

    int border = 1;

    for (int y = border; y < src.rows - border; ++y)
    {
        for (int x = border; x < src.cols - border; ++x)
        {
            for (int c = 0; c < src.channels(); ++c)
            {
                double sum_x = 0.0;
                double sum_y = 0.0;

                for (int ky = -border; ky <= border; ++ky)
                {
                    for (int kx = -border; kx <= border; ++kx)
                    {
                        sum_x += src.at<cv::Vec3b>(y + ky, x + kx)[c] * kernel_x.at<int>(ky + border, kx + border);
                        sum_y += src.at<cv::Vec3b>(y + ky, x + kx)[c] * kernel_y.at<int>(ky + border, kx + border);
                    }
                }

                double sum = sqrt(sum_x * sum_x + sum_y * sum_y);
                dst.at<cv::Vec3b>(y, x)[c] = static_cast<uchar>(sum);
            }
        }
    }

    return dst;
}

cv::Mat applyMeanFilter(const cv::Mat &src, int kernelSize)
{
    cv::Mat dst = src.clone();
    int border = kernelSize / 2;

    for (int y = border; y < src.rows - border; ++y)
    {
        for (int x = border; x < src.cols - border; ++x)
        {
            for (int c = 0; c < src.channels(); ++c)
            {
                float sum = 0.0;
                int count = 0;

                for (int ky = -border; ky <= border; ++ky)
                {
                    for (int kx = -border; kx <= border; ++kx)
                    {
                        sum += src.at<cv::Vec3b>(y + ky, x + kx)[c];
                        count++;
                    }
                }

                dst.at<cv::Vec3b>(y, x)[c] = static_cast<uchar>(sum / count);
            }
        }
    }

    return dst;
}
