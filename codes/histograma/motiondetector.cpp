#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int main(int argc, char const *argv[]) {

    Mat src_base, hsv_base;
    //int width, height;
    VideoCapture cap;
    vector<Mat> planes;
    Mat histR, histG;
    int nbins = 64;
    float range[] = {0, 256};
    const float *histrange = { range };
    bool uniform = true;
    bool acummulate = false;

    cap.open(0);

    if(!cap.isOpened())
    {
        cout << "Câmera indisponível" << endl;
        return -1;
    }

    int histw = nbins, histh = nbins/2;

    Mat histImgR(histh, histw, CV_8UC3, Scalar(0,0,0));


    int cont=0;

    cap >> src_base;

    split (src_base, planes);

    double base;

    calcHist(&planes[0], 1, 0, Mat(), histG, 1,
             &nbins, &histrange,
             uniform, acummulate);

    normalize(histG, histG, 0, histImgR.rows, NORM_MINMAX, -1, Mat());

    while(true){

        cap >> src_base;
        split (src_base, planes);
        while(cont < 10000){
            cont++;
        }

        calcHist(&planes[0], 1, 0, Mat(), histR, 1,
                 &nbins, &histrange,
                 uniform, acummulate);

        normalize(histR, histR, 0, histImgR.rows, NORM_MINMAX, -1, Mat());

        base = compareHist( histG, histR, CV_COMP_CORREL);
        //cout << base << endl;

        calcHist(&planes[0], 1, 0, Mat(), histG, 1,
                 &nbins, &histrange,
                 uniform, acummulate);

        normalize(histG, histG, 0, histImgR.rows, NORM_MINMAX, -1, Mat());

        if(base < 0.996){
            cout << "detectou" << endl;
            cout << "\n" << endl;
        }else{
            cout << "sem movimento" << endl;
        }
        imshow("image", src_base);
        if(waitKey(30) >= 0) break;

    }

    return 0;
}
