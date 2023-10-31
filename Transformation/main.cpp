#include "opencv2/highgui/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
    // Charger l'image d'entrée
    Mat inputImage = imread("C:/Users/Naima/Downloads/foreground.jpg", -1);
    Mat transformedImage;

    if (inputImage.empty()) {
        cout << "Erreur lors du chargement de l'image" << endl;
        return -1;
    }

    // Définir les points de destination pour la transformation perspective
    vector<Point2f> destinationPoints;
    destinationPoints.push_back(Point2f(0, 0));  // Coin supérieur gauche
    destinationPoints.push_back(Point2f(inputImage.cols - 1, 0));  // Coin supérieur droit
    destinationPoints.push_back(Point2f(0, inputImage.rows - 1));  // Coin inférieur gauche
    destinationPoints.push_back(Point2f(inputImage.cols - 1, inputImage.rows - 1));  // Coin inférieur droit

    // Définir les points d'origine (coin des images d'entrée)
    vector<Point2f> sourcePoints;
    sourcePoints.push_back(Point2f(0, 0));
    sourcePoints.push_back(Point2f(inputImage.cols - 1, 0));
    sourcePoints.push_back(Point2f(0, inputImage.rows - 1));
    sourcePoints.push_back(Point2f(inputImage.cols - 1, inputImage.rows - 1));

    // Calculer la matrice de transformation perspective
    Mat perspectiveMatrix = getPerspectiveTransform(sourcePoints, destinationPoints);

    // Appliquer la transformation perspective à l'image d'entrée
    warpPerspective(inputImage, transformedImage, perspectiveMatrix, inputImage.size());

    // Afficher l'image transformée
    namedWindow("Image transformée", 1);
    imshow("Image transformée", transformedImage);
    waitKey(0);

    return 0;
}
