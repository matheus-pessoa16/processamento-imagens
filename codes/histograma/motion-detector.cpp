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
    //int h_bins = 50; int s_bins = 60;

    //MatND hist_base;

    int histw = nbins, histh = nbins/2;

    Mat histImgR(histh, histw, CV_8UC3, Scalar(0,0,0));


    int compare_method = 2;

    //cap.set(CV_CAP_PROP_FPS, 10);

    cap >> src_base;
    //cvtColor( src_base, src_base, COLOR_BGR2GRAY );

    split (src_base, planes);

    double base, aux;

    calcHist(&planes[0], 1, 0, Mat(), histG, 1,
             &nbins, &histrange,
             uniform, acummulate);

    normalize(histG, histG, 0, histImgR.rows, NORM_MINMAX, -1, Mat());
    aux = 1;
    // calcHist(&src_base, 1, 0, Mat(), histG, 1,
    //          &nbins, &histrange,
    //          uniform, acummulate);
    //
    // normalize(histG, histG, 0, histImgR.rows, NORM_MINMAX, -1, Mat());

    double media=0;

    while(true){

        cap >> src_base;
        //cvtColor( src_base, src_base, COLOR_BGR2GRAY );
        split (src_base, planes);

        calcHist(&planes[0], 1, 0, Mat(), histR, 1,
                 &nbins, &histrange,
                 uniform, acummulate);

        normalize(histR, histR, 0, histImgR.rows, NORM_MINMAX, -1, Mat());
        base = compareHist( histR, histG, CV_COMP_CORREL);
        // calcHist(&src_base, 1, 0, Mat(), histR, 1,
        //          &nbins, &histrange,
        //          uniform, acummulate);
        //
        // normalize(histG, histG, 0, histImgR.rows, NORM_MINMAX, -1, Mat());
        // for(int i=0; i<10; i++){
        //     base = compareHist( histR, histG, CV_COMP_CORREL);
        //     media+=base;
        // }
        // cout << media/10 << endl;
        cout << base << endl;
        //imshow("image", src_base);

        if( base != media){
            cout << "detectou" << endl;
        }else{
            cout << "no moves" << endl;
            // calcHist(&planes[0], 1, 0, Mat(), histG, 1,
            //          &nbins, &histrange,
            //          uniform, acummulate);
            //
            // normalize(histG, histG, 0, histImgR.rows, NORM_MINMAX, -1, Mat());
            //aux = compareHist( histR, histG, CV_COMP_CORREL);
        }
        media=0;
        imshow("image", src_base);
        if(waitKey(30) >= 0) break;

    }



    return 0;
}
