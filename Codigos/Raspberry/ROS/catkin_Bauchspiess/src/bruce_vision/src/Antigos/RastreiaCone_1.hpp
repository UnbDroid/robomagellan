#define usuario 
//#define filmar

#define mostra_partes

//#define mostra_range
//#define mostra_rangez


//#define fosforescente
#define fosco

#define VEZ 1

//#define soma

//#define regular
//#define histograma
#define ponderado
//#define useLab

#define segmentacao


#define ve_tempo9


#include "opencv2/opencv.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/core/core.hpp"
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <sys/time.h>

using namespace cv;
using namespace std;

class Segmento{
public:
	Point inicio;
	Point fim;
	vector<Point> pontos;
	vector<Point> rotated;
	Point centro;
	int num_pontos;
	Vec3b cor_centro;
	vector<uchar> avg_cor;
	vector<Point> esquerda;
	vector<Point> direita;
	int altura;
	int largura;
	Point canto;
	
	Segmento();
	void calc_centro();
	void rotate();
	void limites();
	void addPoint(Point);
	void addPoint(Point,vector<uchar>);
	void addVector(vector<Point>);
	void addVector(vector<Point>,vector<uchar>,Point);
	void bordas();
	void clear();
	float ratio();
};

class RastreiaCone{
public:

	bool atualiza; //tirar da classe e colocar na main

	//saidas do rastreamento
	float pub_angulo;
	float pub_distancia;
	bool encontrou_cone;

	float pubx,puby;

	//tamanhos das matrizes de exposição e utilizada
	int tamanho_final;
	int tamanho0;

	//parâmetros de cor
	int subidaL;
	int step1_L;
	int altoL;
	int descidaL;
	int step2_L;
	int baixoL;

	int subidaA;
	int step1_A;
	int altoA;
	int descidaA;
	int step2_A;
	int baixoA;

	int subidaB;
	int step1_B;
	int altoB;
	int descidaB;
	int step2_B;
	int baixoB;




	int minL;
	int maxL;
	int minB;
	int maxB;
	int minG;
	int maxG;
	int minR;
	int maxR;

	int minLo;
	int maxLo;
	int minBo;
	int maxBo;
	int minGo;
	int maxGo;
	int minRo;
	int maxRo;


	int minCanny;
	int maxCanny;
	int sizeCanny;


	//parametros para a segmentação
	int min_aceita;
	int aceita_final;
	
	int dif_centroide;
	int dif_pixel;
	int max_dif_centroide;
	int max_dif_pixel;

	int max_dif_centroideL;
	int max_dif_pixelL;


	int min_segment_size;


	#ifdef usuario
	bool filtro;
	#endif

private:

	float L[256];
	float A[256];
	float B[256];
	uchar Tabela[256][256][256];

	vector<Segmento> objetos;

	Mat* Original;
	float ratio_original;
	float delta;

	#ifdef ve_tempo9
	struct timeval tempo1, tempo2, velho, novo;
	int tempo;
	#endif
	#ifdef filmar
	VideoWriter *video;
	bool video_init; 
	#endif

	float ratio_novo;

private:
	void PreencheTabela();
	//void Luminosidade(Mat*);
	//void Segmenta(Mat,Mat);
	//int varredura0(Mat* source,Point);
	int varredura(Mat,Rect,Mat);
	//void Normaliza(Mat, Mat*);
	//void segmentaNorm(Mat,Mat);
	//void segmentaBGR(Mat,Mat);
	void segmentaDif(Mat,Mat);
	void DesenhaSeg(Mat*);
	void Thresh(Mat,Mat*);
public:
	RastreiaCone();
	void int_to_string(int valor, string* numeral);
	void rastreia(Mat source);
};



