#define subthresh
#define mostra_seg
#define usuario 
#define filmar

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
#include "Segmento.hpp"

using namespace cv;
using namespace std;

void float_to_string(float valor, string* numeral, int casas);
void int_to_string(int valor, string* numeral);


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

	int porque;


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

	int minLB;
	int maxLB;
	int minBB;
	int maxBB;
	int minAB;
	int maxAB;



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

	int difLo;
	int difLb;
	int difAo;
	int difAb;
	int difBo;
	int difBb;
	int max_dif;
	float max_fdif;

	int min_segment_size;

	vector<vector<Point>  > lista;

	vector<Cone > cones;
	float angulo_ideal;

	//#ifdef usuario
	bool filtro;
	//#endif

	vector<Segmento> objetos;
private:

	float L[256];
	float A[256];
	float B[256];

	float difL[50];
	float difA[50];
	float difB[50];
	float difTable[50][50][50];
	uchar Tabela[256][256][256];

	

	float ratio_original;
	float delta;

	int best_cone;
	int linha_centro;
	float H_centro;
	int max_search_area;

	#ifdef ve_tempo9
	struct timeval tempo1, tempo2, velho, novo;
	int tempo;
	#endif
	#ifdef filmar
	VideoWriter *video;
	bool video_init; 
	#endif

	float ratio_novo;

public:
	void PreencheTabela();
	int varredura(Mat,Rect,Mat);
	int varredura2(Mat,Rect,Mat);
	int Busca(Mat,Mat,float,int,int);
	void segmentaDif(Mat,Mat);
	void segmenta(Mat,Mat);
	void DesenhaSeg(Mat*);
	void DesenhaBordas(Mat*,float);
	void Thresh(Mat,Mat*);
	float corIgual(Vec3b,Vec3b);
	void Identifica(int,float,int,float,float);
	void Filtrar(Mat*);
public:
	RastreiaCone();
	void int_to_string(int valor, string* numeral);
	double rastreia(Mat source, bool, float, float, float, float, float);
};



