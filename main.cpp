#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <map>
#include <functional>
#include "ImageProcessor.h"
#include "Filters.h"

int main() {
    ImageProcessor processor;

    // Register filters
    processor.addFilter("Median", [](const cv::Mat& src) { return applyMedianFilter(src, 5); });
    processor.addFilter("Gaussian", [](const cv::Mat& src) { return applyGaussianBlur(src, 5, 1.0); });
    processor.addFilter("Sobel", [](const cv::Mat& src) { return applySobelFilter(src); });
    processor.addFilter("Mean", [](const cv::Mat& src) { return applyMeanFilter(src, 3); });

    // Variables to manage the current and original image
    cv::Mat originalImage, currentImage;

    while (true) {
        // Main menu
        std::cout << "\nMain Menu:\n";
        std::cout << "1. Load a new image\n";
        std::cout << "2. Apply a filter or transformation\n";
        std::cout << "3. Save the modified image\n";
        std::cout << "0. Exit\n";
        std::cout << "\nEnter your choice: ";

        int mainChoice;
        std::cin >> mainChoice;

        if (mainChoice == 0) {
            std::cout << "Goodbye!" << std::endl;
            break;
        } else if (mainChoice == 1) {
            // Load a new image
            std::cin.ignore(); // Clear the buffer
            std::string imagePath;
            std::cout << "Enter the image path: ";
            std::getline(std::cin, imagePath);

            originalImage = cv::imread(imagePath, cv::IMREAD_COLOR);
            if (originalImage.empty()) {
                std::cerr << "Error: Unable to load the image. Please ensure the path is correct." << std::endl;
                continue;
            }

            currentImage = originalImage.clone();
            std::cout << "Image loaded successfully." << std::endl;
        } else if (mainChoice == 2) {
            if (currentImage.empty()) {
                std::cerr << "Error: No image loaded. Please load an image first." << std::endl;
                continue;
            }

            // List of options
            std::map<int, std::function<cv::Mat(const cv::Mat&)>> operations = {
                {1, [&](const cv::Mat& img) { return processor.applyFilter("Median", img); }},
                {2, [&](const cv::Mat& img) { return processor.applyFilter("Gaussian", img); }},
                {3, [&](const cv::Mat& img) { return processor.applyFilter("Sobel", img); }},
                {4, [&](const cv::Mat& img) { return processor.applyFilter("Mean", img); }},
                {5, [&](const cv::Mat& img) { return processor.zoom(img, 1.5); }},
                {6, [&](const cv::Mat& img) { return processor.reduce(img, 0.5); }},
                {7, [&](const cv::Mat& img) { return processor.rotate(img, 45); }},
                {8, [&](const cv::Mat& img) { return processor.flip(img, 1); }},
                {9, [&](const cv::Mat& img) { return processor.compress(img); }}
            };

            std::cout << "\nChoose an operation to apply:\n";
            std::cout << "1. Median Filter\n";
            std::cout << "2. Gaussian Filter\n";
            std::cout << "3. Sobel Filter\n";
            std::cout << "4. Mean Filter\n";
            std::cout << "5. Zoom (1.5x)\n";
            std::cout << "6. Reduce (0.5x)\n";
            std::cout << "7. Rotate (45 degrees)\n";
            std::cout << "8. Flip Horizontal\n";
            std::cout << "9. Compress\n";
            std::cout << "0. Return to main menu\n";

            int choice;
            std::cout << "\nEnter your choice: ";
            std::cin >> choice;

            if (choice == 0) {
                continue;
            }

            if (operations.find(choice) != operations.end()) {
                currentImage = operations[choice](currentImage);
                std::string windowName = "Result - Operation " + std::to_string(choice);
                cv::imshow(windowName, currentImage);
                cv::waitKey(0); // Wait for a key press to continue
                cv::destroyWindow(windowName);
            } else {
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        } else if (mainChoice == 3) {
            if (currentImage.empty()) {
                std::cerr << "Error: No image loaded. Please load an image first." << std::endl;
                continue;
            }

            std::cin.ignore(); // Clear the buffer
            std::string savePath;
            std::cout << "Enter the path to save the image: ";
            std::getline(std::cin, savePath);

            if (cv::imwrite(savePath, currentImage)) {
                std::cout << "Image saved successfully to: " << savePath << std::endl;
            } else {
                std::cerr << "Error: Unable to save the image." << std::endl;
            }
        } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}