#include "opencv2/opencv.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/core/core.hpp"
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <sys/time.h>



class AchaArvore{
	public:

	int verde_baixo;
	int verde_alto;
	int saturacao_baixa;
	int saturacao_alta;
	int value_baixo;
	int value_alto;

	int blur_size;
	int min_blur;

	void detecta_arvore(Mat source);
	AchaArvore();
};

AchaArvore::AchaArvore(){
	verde_baixo = 20;
	verde_alto = 90;
	saturacao_baixa = 20;
	saturacao_alta = 100;
	value_baixo = 30;
	value_alto = 200;

	blur_size = 10;
	min_blur = 60;
}


void AchaArvore::detecta_arvore(Mat source){
	Mat hsv;
	Mat verde;
	imshow("SOURCE", source);
	float ratio_original = (float)source.cols/(float)source.rows;
	resize(source, hsv, Size((int)(((float)200)*ratio_original), 200 ));
	
	cvtColor(hsv, hsv, CV_BGR2HSV);

	inRange(hsv, Scalar(verde_baixo,saturacao_baixa,value_baixo), Scalar(verde_alto, saturacao_alta, value_alto), verde);
	imshow("verde",verde);

	blur(verde, verde, Size(blur_size,blur_size));
	imshow("blur verde", verde);
	inRange(verde,Scalar(min_blur), Scalar(300), verde);
	imshow("regiao verde", verde);
}