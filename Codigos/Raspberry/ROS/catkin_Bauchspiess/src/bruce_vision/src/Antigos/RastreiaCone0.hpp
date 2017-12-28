#define usuario 
//#define filmar

//#define mostra_partes

//#define mostra_range
//#define mostra_rangez


#define fosforescente
//#define fosco

#define VEZ 1

//#define soma

//#define regular
//#define histograma
#define ponderado
//#define useLab

//#define segmentacao


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

class RastreiaCone{
public:

	int tamanho_mat;


	int min_blur;
	int blur_y;
	int blur_x;

	int min_blur_i;
	int blur_y_i;
	int blur_x_i;


	bool atualiza;

	bool frag;

	float desvio;


	bool calibra;

	int define_blur_x, define_blur_y, define_thresh;

	int tamanho_final;
	int tamanho0;

	int min_pontos;
	int perc_pontosi;

	float pub_angulo;
	float pub_distancia;
	bool encontrou_cone;

	int subidaH1;
	int step1_H1;
	int altoH1;
	int descidaH1;
	int step2_H1;
	int baixoH1;

	int subidaH2;
	int step1_H2;
	int altoH2;
	int descidaH2;
	int step2_H2;
	int baixoH2;

	int subidaS;
	int step1_S;
	int altoS;
	int descidaS;
	int step2_S;
	int baixoS;

	int subidaV;
	int step1_V;
	int altoV;
	int descidaV;
	int step2_V;
	int baixoV;


	int min_aceita;
	int aceita_final;
	int dif_centroide;
	int dif_pixel;


	int H_pondera;
	int S_pondera;
	int V_pondera;
	int size_blur;
	int aceita_blur;

	int potH;
	int potS;
	int potV;


	int subidaH1z;
	int step1_H1z;
	int altoH1z;
	int descidaH1z;
	int step2_H1z;
	int baixoH1z;

	int subidaH2z;
	int step1_H2z;
	int altoH2z;
	int descidaH2z;
	int step2_H2z;
	int baixoH2z;

	int subidaSz;
	int step1_Sz;
	int altoSz;
	int descidaSz;
	int step2_Sz;
	int baixoSz;

	int subidaVz;
	int step1_Vz;
	int altoVz;
	int descidaVz;
	int step2_Vz;
	int baixoVz;

	int min_aceitaz;
	int aceita_finalz;
	int H_ponderaz;
	int S_ponderaz;
	int V_ponderaz;
	int size_blurz;
	int aceita_blurz;

	int potHz;
	int potSz;
	int potVz;





	bool filtro;

private:

	bool min_valido;

	float H[256];
	float S[256];
	float V[256];
	uchar Tabela[256][256][256];

	float Hz[256];
	float Sz[256];
	float Vz[256];
	uchar Tabela_perto[256][256][256];

	vector<Vec3f> dados;
	int ref_dados;
	int ultimo_valido;

	Mat* Original;

	struct timeval tempo1, tempo2, velho, novo;
	int tempo;

	vector<float> ponto_camera;
	vector<float> angulo_robo;
	bool iniciou_calibra;


	int topo;
	int baixo;
	int esquerda;
	int direita;

	int num_colunas;

	float ratio_original;

	float quadrado_x, quadrado_y;
	float quadrado_d, quadrado_b;
	float delta;

	vector<float> Quadrado_x[2], Quadrado_y[2];
	vector<float> Quadrado_d[2], Quadrado_b[2];

	vector<float> pos_angulo;
	vector<float> pos_dist;


	float canny_x, canny_y;

	vector<float> angulos;

	int passo;

	int seleciona;

	int regioes_antigas;
	int regioes_novas;

	float ratio_novo; 


	bool confirma;
	bool proximo;

	int cont_ruim;
	float aux_cont;

	VideoWriter *video;
	bool video_init;
	void PreencheTabela();
public:
	bool anterior;

	RastreiaCone();
	void Laranja(Mat source, Mat* dest,int vez);
	void int_to_string(int valor, string* numeral);


	void rastreia(Mat source);
	int varredura0(Mat* source);
	bool varredura1(Mat* source, int num_area);


	void define_objetos(Mat* source, vector<Mat> *manchas, vector<Vec4i> *posicoes, int min_pontos, int min_frac);
	bool dados_mancha(Mat mancha, int partes);
	bool identifica(Mat* source, int num_area, Mat* temp);

	void achaPerto(Mat* source, Mat* temp);

	void angulo(Mat* source, int ref);
	void distancia(Mat* source, int ref);

	void calibra_angulos(Mat source);
	void calibra_input(vector<float> input_pontos, vector<float> input_angulos);

	#ifdef segmentacao
	void Luminosidade(Mat*);
	void Segmenta(Mat);
	#endif

};

class Segmento{
public:
	Point inicio;
	Point fim;
	vector<Point> pontos;
	vector<Point> rotated;
	Point centro;
	int num_pontos;
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
	void addVector(vector<Point>);
	void bordas();

};

