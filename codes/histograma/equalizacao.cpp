#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char const *argv[]) {
    Mat src, dest;
    VideoCapture cap;

    cap.open(0);

    if( !cap.isOpened() ){
        cout<<"câmera indisponível"<<endl;
        return -1;
    }

    while(true){
        cap >> src;
        cvtColor( src, src, COLOR_BGR2GRAY );
        equalizeHist( src, dest );
        imshow( "Source", src );
        imshow( "Equalized", dest );    
        if(waitKey(30) >= 0) break;
    }
    return 0;
}
