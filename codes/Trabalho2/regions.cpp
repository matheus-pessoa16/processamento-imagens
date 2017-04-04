#include <iostream>
#include <cv.h>
#include <highgui.h>

using namespace cv;
using namespace std;

int main(){
    Mat image;
    

    int p1[2], p2[2];

    image = imread("biel.png", CV_LOAD_IMAGE_GRAYSCALE);
    if(!image.data){
        cout << "Não foi possível abrir a imagem biel.png" << endl;
    }

    cout << "informe as coordenadas X e Y do ponto 1"<< endl;
    cin >> p1[0] >> p1[1];

    cout << "informe as coordenadas X e Y do ponto 2"<< endl;
    cin >> p2[0] >> p2[1];

    for (int i = p1[0]; i < p2[0]; i++) {
        for (int j = p1[1]; j < p2[1]; j++) {
            image.at<uchar>(i,j) = 255 - image.at<uchar>(i,j);
        }
    }

    imshow("janela", image);
    waitKey();

    return 0;
}
