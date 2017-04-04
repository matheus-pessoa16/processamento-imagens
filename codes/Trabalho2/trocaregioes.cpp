#include <iostream>
#include <cv.h>
#include <highgui.h>

using namespace cv;
using namespace std;

int main(int argc, char** argv){

    Mat img;

    img = imread("biel.png", CV_LOAD_IMAGE_GRAYSCALE);

    if(!img.data){
        cout << "Não foi possível carregar a imagem" <<endl;
    }

    int row, col;

    row = img.rows;
    col = img.cols;
    int aux;
    cout << row << " " << col;

    for(int i=0; i < row-1; i++){
        for(int j=0; j<col-1; j++){
            if(i < ((row/2)) &&  j < (col/2)){
                aux = img.at<uchar>(i,j);
                img.at<uchar>(i,j) = img.at<uchar>((row/2)+i,(col/2)+j);
                img.at<uchar>((row/2)+i,(col/2)+j) = aux;
            }
            else if(i >= (row/2)  && j >= (col/2)){
                aux = img.at<uchar>(i - (row/2), j);
                img.at<uchar>(i - (row/2), j) = img.at<uchar>(i, j-(col/2));
                img.at<uchar>(i, j - (col/2))= aux;
             }
        }
    }

    imshow("janela", img);
    waitKey();
    return 0;
}
