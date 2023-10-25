#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat img, imgr, imghsv, mask;
bool changesONOFF = false;

void f(int pos){
     changesONOFF = true;
}

int main(){
    img = imread("../Others/Downloads/foreground.jpg");
    int hmin = 0, hmax = 179, smin = 0, smax = 255, vmin = 0, vmax = 255;

    if (img.empty()){
        cout << "Erreur de lecture" << endl; return -1;
    }

    // Afficher l'image
    imshow("Image couleur", img);
    imshow("HSV Ranges", img);

    // Creer les TrackBars
    cvCreateTrackbar("Hmin", "HSV Ranges", &hmin, 179, f);
    cvCreateTrackbar("Hmax", "HSV Ranges", &hmax, 179, f);
    cvCreateTrackbar("Smin", "HSV Ranges", &smin, 255, f);
    cvCreateTrackbar("Smin", "HSV Ranges", &hmin, 255, f);
    cvCreateTrackbar("Hmin", "HSV Ranges", &hmin, 255, f);
    cvCreateTrackbar("Hmin", "HSV Ranges", &hmin, 255, f);

    while(true){
        if (changesONOFF == true){
            cvtColor(img, imghsv, CV_BGR2HSV);

            // Exraire
            inRange(imghsv, Scalar(hmin, smin, vmin), Scalar(hmax, smax, vmax), mask);
            cvtColor(mask, mask, CV_GRAY2BGR);
            bitwise_and(img, mask, imgr);

            // Affichage
            imshow("HSV Ranges", imgr);
            imshow("Image binaire", mask);
            changesONOFF = false;
        }

        if (cvWaitKey(50) == 27)
            break;
    }

    // Fermer les fenetres
    destroyAllWindows();
    return 0;
}

