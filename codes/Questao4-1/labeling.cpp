#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
	Mat image, mask;
	int width, height;

	CvPoint p;
	image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);

	if(!image.data){
		std::cout << "imagem nao carregou corretamente\n";
		return(-1);
	}
	width=image.size().width; //largura
	height=image.size().height; //altura

	p.x=0;
	p.y=0;
	// elimina as figuras que estão encostada nas bordas
	for (int i = 0; i < width; i++) {
		image.at<uchar>(i, height -1) = 255;
		image.at<uchar>(i, 0) = 255;
	}

	for (int i = 0; i < height; i++) {
		image.at<uchar>(0, i) = 255;
		image.at<uchar>(width -1, i) = 255;
	}
	 
	//pinta as figuras da borda de pret0
	floodFill(image, p, 0);
	//mudo o background da imagem/
	floodFill(image, p, 100); //background
	imshow("image", image);
	imwrite("labeling.png", image);
	waitKey();

	// econtro primeiro as figuras nas imagens
	int qtdTotal = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			// verifico se o ponto econtrado é branco e se ele o seu vizinho anterior a ele é da cor do background, se sim mudo a cor do msm
			if (image.at<uchar>(i, j) == 255 && image.at<uchar>(i-1, j) == 100 ) {
			p.x = j;
			p.y = i;
			floodFill(image, p, 150); //itens encontrados
			qtdTotal++;
			}
		}
	}
	cout << "Quantidade de objetos "<< qtdTotal << endl;
	imshow("image", image);
	imwrite("labeling.png", image);
	waitKey();

	int qtdTotalBolhas = 0;
	for (int i = 0; i < height; i++)
	{	
		for (int j = 0; j < width; j++)
		{	// procuro os únicos intens brancos que restou na imagem (esses são as bolhas.)
			if (image.at<uchar>(i,j) == 255 )
			{
				p.x = j;
				p.y = i;
				floodFill(image, p, 50);
				qtdTotalBolhas ++;		
			}
		}
	}
	cout << "Quantidade de bolhas nos objetos " << qtdTotalBolhas << endl;
	imshow("image", image);
	imwrite("labeling.png", image);
	waitKey();
	return 0;
}
