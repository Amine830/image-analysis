#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <map>
#include <functional>
#include "ImageProcessor.h"
#include "Filters.h"

#ifdef _WIN32
#include <windows.h>
void clearConsole() { system("cls"); }
#else
#include <cstdlib>
void clearConsole() { system("clear"); }
#endif

void displayImageWithHistograms(const cv::Mat& image, ImageProcessor& processor) {
    cv::Mat histogram = processor.calculateHistogram(image);
    cv::Mat cumulativeHistogram = processor.calculateCumulatedHistogram(image);

    // Display the image
    cv::imshow("Image", image);

    // Display histograms
    cv::imshow("Histogramme", histogram);
    cv::imshow("Histogramme Cumulé", cumulativeHistogram);
}

void printMenu(const std::string& title, const std::vector<std::string>& options) {
    std::cout << "\n==================== " << title << " ====================\n";
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << i + 1 << ". " << options[i] << "\n";
    }
    std::cout << "0. Retour au menu principal\n";
    std::cout << "====================================================\n";
    std::cout << "Entrez votre choix: ";
}

int main() {
    ImageProcessor processor;

    // Register filters
    processor.addFilter("Médian", [](const cv::Mat& src) { return applyMedianFilter(src, 5); });
    processor.addFilter("Gaussien", [](const cv::Mat& src) { return applyGaussianBlur(src, 5, 1.0); });
    processor.addFilter("Sobel", [](const cv::Mat& src) { return applySobelFilter(src); });
    processor.addFilter("Moyenne", [](const cv::Mat& src) { return applyMeanFilter(src, 3); });

    // Variables to manage the current and original image
    cv::Mat originalImage, currentImage;

    while (true) {
        clearConsole(); // Clear the console before showing the menu

        // Main menu
        printMenu("Menu Principal", {"Charger une nouvelle image", "Appliquer un filtre ou une transformation", "Enregistrer l'image modifiée"});

        int mainChoice;
        std::cin >> mainChoice;

        if (mainChoice == 0) {
            std::cout << "Au revoir!" << std::endl;
            cv::destroyAllWindows(); // Close all windows when exiting
            break;
        } else if (mainChoice == 1) {
            // Load a new image
            std::cin.ignore(); // Clear the buffer
            std::string imagePath;
            std::cout << "Entrez le chemin de l'image: ";
            std::getline(std::cin, imagePath);

            originalImage = cv::imread(imagePath, cv::IMREAD_COLOR);
            if (originalImage.empty()) {
                std::cerr << "Erreur: Impossible de charger l'image. Veuillez vérifier le chemin." << std::endl;
                continue;
            }

            currentImage = originalImage.clone();
            std::cout << "Image chargée avec succès." << std::endl;

            // Close all windows before displaying new ones
            cv::destroyAllWindows();

            // Display the image with histograms
            displayImageWithHistograms(currentImage, processor);
            cv::waitKey(0); // Wait for a key press
        } else if (mainChoice == 2) {
            if (currentImage.empty()) {
                std::cerr << "Erreur: Aucune image chargée. Veuillez d'abord charger une image." << std::endl;
                continue;
            }

            // List of options
            std::map<int, std::function<cv::Mat(const cv::Mat&)>> operations = {
                {1, [&](const cv::Mat& img) { return processor.applyFilter("Médian", img); }},
                {2, [&](const cv::Mat& img) { return processor.applyFilter("Gaussien", img); }},
                {3, [&](const cv::Mat& img) { return processor.applyFilter("Sobel", img); }},
                {4, [&](const cv::Mat& img) { return processor.applyFilter("Moyenne", img); }},
                {5, [&](const cv::Mat& img) { return processor.zoom(img, 1.5); }},
                {6, [&](const cv::Mat& img) { return processor.reduce(img, 0.5); }},
                {7, [&](const cv::Mat& img) { return processor.rotate(img, 45); }},
                {8, [&](const cv::Mat& img) { return processor.flip(img, 1); }},
                {9, [&](const cv::Mat& img) { return processor.compress(img); }},
                {10, [&](const cv::Mat& img) { return processor.stretchHistogram(img); }},
                {11, [&](const cv::Mat& img) { return processor.equalizeHistogram(img); }}
            };

            clearConsole(); // Clear the console before showing the filter menu

            printMenu("Choisissez une opération à appliquer", {
                "Filtre Médian", "Filtre Gaussien", "Filtre Sobel", "Filtre Moyenne",
                "Zoom (1.5x)", "Réduire (0.5x)", "Rotation (45 degrés)", "Retourner Horizontalement",
                "Compresser", "Étirer l'Histogramme", "Égaliser l'Histogramme"
            });

            int choice;
            std::cin >> choice;

            if (choice == 0) {
                continue;
            }

            if (operations.find(choice) != operations.end()) {
                currentImage = operations[choice](currentImage);

                // Close all windows before displaying new ones
                cv::destroyAllWindows();

                // Display the modified image with histograms
                displayImageWithHistograms(currentImage, processor);
                cv::waitKey(0); // Wait for a key press
            } else {
                std::cout << "Choix invalide. Veuillez réessayer." << std::endl;
            }
        } else if (mainChoice == 3) {
            if (currentImage.empty()) {
                std::cerr << "Erreur: Aucune image chargée. Veuillez d'abord charger une image." << std::endl;
                continue;
            }

            std::cin.ignore(); // Clear the buffer
            std::string savePath;
            std::cout << "Entrez le chemin pour enregistrer l'image: ";
            std::getline(std::cin, savePath);

            if (cv::imwrite(savePath, currentImage)) {
                std::cout << "Image enregistrée avec succès à: " << savePath << std::endl;
            } else {
                std::cerr << "Erreur: Impossible d'enregistrer l'image." << std::endl;
            }
        } else {
            std::cout << "Choix invalide. Veuillez réessayer." << std::endl;
        }
    }

    return 0; 
}
