//#define usuario 
//#define filmar

//#define mostra_partes

//#define mostra_range

#define fosforescente
//#define fosco

#define VEZ 1

//#define soma

//#define regular
//#define histograma
#define ponderado



//#define ve_tempo


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

	bool filtro;

	int H_pondera;
	int S_pondera;
	int V_pondera;
	int Hist_final;
	int Peso_blur;
	int Peso_original;
	int aceita_blur;

private:

	bool min_valido;

	float H[256];
	float S[256];
	float V[256];
	uchar Tabela[256][256][256];

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

};


void RastreiaCone::PreencheTabela(){

	#ifdef ve_tempo	
		gettimeofday(&tempo1, NULL);
	#endif
		
	int i, j, k;
	float incremento;
	float valor;

	//Filtro da Matiz
	for(i = 0; i<subidaH1; i++){
		H[i] = 0;
	}
	incremento = (1.0-(float)((float)step1_H1/100.0) )/(float)(altoH1 - subidaH1);
	valor = (float)((float)step1_H1/100.0);
	for( i = subidaH1; i<altoH1; i++){
		valor += incremento;
		H[i] = valor;
	}
	for(i = altoH1 ; i<descidaH1; i++){
		H[i] = 1;
	}
	valor = 1;
	incremento = (1.0-(float)((float)step2_H1/100.0) )/(float)(descidaH1 - baixoH1);
	for(i = descidaH1; i<baixoH1; i++){
		valor += incremento;
		H[i] = valor;
	}
	for(i = baixoH1; i<subidaH2; i++){
		H[i] = 0;
	}

	incremento = (1.0-(float)((float)step1_H2/100.0) )/(float)(altoH2 - subidaH2);
	valor = (float)((float)step1_H2/100.0);
	for( i = subidaH2; i<altoH2; i++){
		valor += incremento;
		H[i] = valor;
	}
	for(i = altoH2 ; i<descidaH2; i++){
		H[i] = 1;
	}
	valor = 1;
	incremento = (1.0-(float)((float)step2_H2/100.0) )/(float)(descidaH2 - baixoH2);
	if(baixoH2 > 256)
		baixoH2 = 256;
	for(i = descidaH2; i<baixoH2; i++){
		valor += incremento;
		H[i] = valor;
	}
	for(i = baixoH2; i<256; i++){
		H[i] = 0;
	}



	//Filtro da Saturação
	for(i = 0; i<subidaS; i++){
		S[i] = 0;
	}
	incremento = (1.0-(float)((float)step1_S/100.0) )/(float)(altoS - subidaS);
	valor = (float)((float)step1_S/100.0);
	for( i = subidaS; i<altoS; i++){
		valor += incremento;
		S[i] = valor;
	}
	for(i = altoS ; i<descidaS; i++){
		S[i] = 1;
	}
	valor = 1;
	incremento = (1.0-(float)((float)step2_S/100.0) )/(float)(descidaS - baixoS);
	if(baixoS > 256)
		baixoS = 256;
	for(i = descidaS; i<baixoS; i++){
		valor += incremento;
		S[i] = valor;
	}
	for(i = baixoS; i<256; i++){
		S[i] = 0;
	}


	//Filtro do Value
	for(i = 0; i<subidaV; i++){
		V[i] = 0;
	}
	incremento = (1.0-(float)((float)step1_V/100.0) )/(float)(altoV - subidaV);
	valor = (float)((float)step1_V/100.0);
	for( i = subidaV; i<altoV; i++){
		valor += incremento;
		V[i] = valor;
	}
	for(i = altoV ; i<descidaV; i++){
		V[i] = 1;
	}
	valor = 1;
	incremento = (1.0-(float)((float)step2_V/100.0) )/(float)(descidaV - baixoV);
	if(baixoS > 256)
		baixoS = 256;
	for(i = descidaV; i<baixoV; i++){
		valor += incremento;
		V[i] = valor;
	}
	for(i = baixoV; i<256; i++){
		V[i] = 0;
	}

	for(i = 0; i<256; i++){
		for(j = 0; j<256; j++){
			for(k = 0; k<256; k++){
				
				#ifdef soma
					Tabela[i][j][k] = (uchar) 255*( (H[i] + S[j] + V[k])/3.0);
				#endif
				#ifndef soma
					Tabela[i][j][k] = (uchar) 255*H[i]*H[i]*H[i]*S[j]*S[j]*S[j]*S[j]*S[j]*V[k];
				#endif
			}
		}
	}


	#ifdef ve_tempo
		gettimeofday(&tempo2, NULL);
		tempo = (int) (1000000 * (tempo2.tv_sec - tempo1.tv_sec) + (tempo2.tv_usec - tempo1.tv_usec));
			cout<<"Preenche: "<<tempo<<endl;
	#endif	
}

void RastreiaCone::int_to_string(int valor, string* numeral){
	int inteiro = valor;
	int resto = valor;
	do{
		resto = inteiro%10;
		inteiro = inteiro/10;
		(*numeral).push_back( (char)(resto + 48) );
	}while(inteiro > 0);
	reverse((*numeral).begin(),(*numeral).end()); 
}

RastreiaCone::RastreiaCone(){

	filtro = false;

	define_blur_x = 0;
	define_blur_y = 0;
	define_thresh = 127;	

	anterior = false;
	proximo = false;
	delta = 20;

	#ifdef fosforescente

		#ifdef ponderado

			H_pondera = 0;
			S_pondera = 100;
			V_pondera = 70;
			Hist_final = 160;
			Peso_blur = 25;
			aceita_blur = 50;
			//Peso_original = 8;

			subidaH1 = 0;
			step1_H1 = 0;
			altoH1 = 0;
			descidaH1 = 10;
			step2_H1 = 20;
			baixoH1 = 30;

			subidaH2 = 160;
			step1_H2 = 0;
			altoH2 = 170;
			descidaH2 = 170;
			step2_H2 = 0;
			baixoH2 = 180;

			subidaS = 130;
			step1_S = 0;
			altoS = 250;
			descidaS = 256;
			step2_S = 100;
			baixoS = 256;

			subidaV = 0;
			step1_V = 80;
			altoV = 100;
			descidaV = 256;
			step2_V = 70;
			baixoV = 256;

			min_aceita = 250;
		#endif

		#ifndef ponderado
			subidaH1 = 0;
			step1_H1 = 50;
			altoH1 = 0;
			descidaH1 = 10;
			step2_H1 = 0;
			baixoH1 = 20;

			subidaH2 = 190;
			step1_H2 = 50;
			altoH2 = 190;
			descidaH2 = 180;
			step2_H2 = 0;
			baixoH2 = 180;

			subidaS = 90;
			step1_S = 0;
			altoS = 170;
			descidaS = 256;
			step2_S = 50;
			baixoS = 256;

			subidaV = 30;
			step1_V = 70;
			altoV = 130;
			descidaV = 256;
			step2_V = 50;
			baixoV = 256;

			min_aceita = 230;
		#endif	

	#endif

	#ifdef fosco

		#ifdef ponderado
			

			subidaH1 = 0;
			step1_H1 = 0;
			altoH1 = 0;
			descidaH1 = 30;
			step2_H1 = 0;
			baixoH1 = 80;

			subidaH2 = 190;
			step1_H2 = 50;
			altoH2 = 190;
			descidaH2 = 180;
			step2_H2 = 0;
			baixoH2 = 180;

			subidaS = 215;
			step1_S = 60;
			altoS = 220;
			descidaS = 256;
			step2_S = 50;
			baixoS = 256;

			subidaV = 140;
			step1_V = 50;
			altoV = 200;
			descidaV = 250;
			step2_V = 0;
			baixoV = 256;

			min_aceita = 220;
		#endif

		#ifndef ponderado
			subidaH1 = 0;
			step1_H1 = 0;
			altoH1 = 0;
			descidaH1 = 30;
			step2_H1 = 0;
			baixoH1 = 80;

			subidaH2 = 190;
			step1_H2 = 50;
			altoH2 = 190;
			descidaH2 = 180;
			step2_H2 = 0;
			baixoH2 = 180;

			subidaS = 215;
			step1_S = 60;
			altoS = 220;
			descidaS = 256;
			step2_S = 50;
			baixoS = 256;

			subidaV = 0;
			step1_V = 50;
			altoV = 30;
			descidaV = 136;
			step2_V = 0;
			baixoV = 256;

			min_aceita = 220;
		#endif

	#endif

	PreencheTabela();



	min_blur = 120;
	blur_y = 3;
	blur_x = 1;

	min_blur_i = 105;
	blur_y_i = 3;
	blur_x_i = 0;

	tamanho_mat = 80;

	atualiza = true;

	passo = -1;

	calibra = false;
	iniciou_calibra = false;

	tamanho_final = 300;
	tamanho0 = 300;

	min_pontos = 10;
	perc_pontosi = 250;

	cont_ruim = 0;
	aux_cont = 0;

	Vec3f dado;
	dado[0] = 0;
	dado[1] = 0;
	dado[2] = 0;


	for(int i = 0; i<30; i++){
		dados.push_back(dado);
	}
	ref_dados = 29;
	ultimo_valido = 0;

	video_init = false;


	min_valido = false;
}


void RastreiaCone::Laranja(Mat source, Mat* dest, int vez){

	gettimeofday(&tempo1, NULL);

	Mat hsv;
	int num_channels;



	

	cvtColor(source, hsv, CV_BGR2HSV);
	Mat final(source.size(), CV_8UC1);


	Mat uniao;

	int i,j;
    uchar* p; 
    uchar* p2;
    int nRows;
    int nCols;

    vector<Mat> channels;
    vector<Mat> canais(3);
    vector<Mat> fusao(3);


	split(hsv, channels);

	



	#ifdef ponderado
		//equalizeHist(channels[0], canais[0]);
		equalizeHist(channels[1], channels[1]);
		equalizeHist(channels[2], canais[2]);

		float V_hist = (float)V_pondera/100;
		float V_regular = 1-V_hist;

		add(V_regular*channels[2], V_hist*canais[2], channels[2]);
	#endif	

	
    #ifdef mostra_partes


		Mat mostra_imagem;
		#ifdef ponderado	
			Mat partes_mostra6(source.size(), CV_8UC1);
			Mat partes_mostra7(source.size(), CV_8UC1);
			Mat partes_mostra8(source.size(), CV_8UC1);;
		#endif	

   


		#ifdef ponderado    
		    nRows = channels[0].rows;
		    nCols = channels[0].cols;
			if (channels[0].isContinuous())
		    {
		        nCols *= nRows;
		        nRows = 1;
		    }

		    for( i = 0; i < nRows; ++i)
		    {
		    	p2 = partes_mostra6.ptr<uchar>(i);
		        p = channels[0].ptr<uchar>(i);
		        for ( j = 0; j < nCols; ++j)
		        {
		            p2[j] = 255*H[p[j]];
		        }
		    }

		    nRows = channels[1].rows;
		    nCols = channels[1].cols;
			if (channels[1].isContinuous())
		    {
		        nCols *= nRows;
		        nRows = 1;
		    }

		    for( i = 0; i < nRows; ++i)
		    {
		    	p2 = partes_mostra7.ptr<uchar>(i);
		        p = channels[1].ptr<uchar>(i);
		        for ( j = 0; j < nCols; ++j)
		        {
		            p2[j] = 255*S[p[j]];
		        }
		    }

		    nRows = channels[2].rows;
		    nCols = channels[2].cols;
			if (channels[2].isContinuous())
		    {
		        nCols *= nRows;
		        nRows = 1;
		    }

		    for( i = 0; i < nRows; ++i)
		    {
		    	p2 = partes_mostra8.ptr<uchar>(i);
		        p = channels[2].ptr<uchar>(i);
		        for ( j = 0; j < nCols; ++j)
		        {
		            p2[j] = 255*V[p[j]];
		        }
		    }

		#endif    

	    if(vez == VEZ){
	    	
	    	#ifdef ponderado
		    	cvtColor(partes_mostra6, mostra_imagem, CV_GRAY2BGR);
		    	putText(mostra_imagem, ("H"), Point(0,20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,0,0), 1, 8, false );
		    	imshow("Hdepois3", mostra_imagem);
		    	cvtColor(partes_mostra7, mostra_imagem, CV_GRAY2BGR);
		    	putText(mostra_imagem, ("S"), Point(0,20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,0,0), 1, 8, false );
		    	imshow("Sdepois3", mostra_imagem);
		    	cvtColor(partes_mostra8, mostra_imagem, CV_GRAY2BGR);
		    	putText(mostra_imagem, ("V"), Point(0,20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,0,0), 1, 8, false );
		    	imshow("Vdepois3", mostra_imagem);
		    #endif	
	    
	    }
    #endif
  
    

	#ifdef ponderado
	    merge(channels, hsv);    
	    num_channels = hsv.channels();
	    nRows = hsv.rows;
	    nCols = hsv.cols * num_channels;
	    for( i = 0; i < nRows; ++i)
	    {
	        p = hsv.ptr<uchar>(i);
	        p2 = final.ptr<uchar>(i);
	        for ( j = 0; j < nCols; j+=3)
	        {
	            p2[j/3] = Tabela[p[j]][p[j+1]][p[j+2]];
	        }
	    }
	    #ifdef mostra_partes
	    	imshow("combinacao",final);
	    #endif
	#endif    

    final.copyTo(*dest);
	
    #ifdef ve_tempo
	    gettimeofday(&tempo2, NULL);
		tempo = (int) (1000000 * (tempo2.tv_sec - tempo1.tv_sec) + (tempo2.tv_usec - tempo1.tv_usec));
		if(atualiza){
					//cout<<"Laranja: "<<tempo<<endl;
		}
	#endif



}




int RastreiaCone::varredura0(Mat* source){
	//gettimeofday(&velho, NULL);
	bool certo = false;
	int pos, x, y;
	vector<Mat> canais;

	string num;


	Mat aux;
	Mat aux2;
	Mat aux3;
	//blur(*source, *source, Size(1, 3));
	Laranja(*source, source,1);
	
	#ifdef usuario
		#ifdef mostra_range
			imshow("Laranja", (*source) );
		#endif
	#endif
	
	inRange( (*source) , Scalar(min_aceita), Scalar(257), aux);
	#ifdef usuario
		#ifdef mostra_range
			imshow("Range", aux);
		#endif
	#endif
	blur(aux, aux2, Size(Peso_blur,Peso_blur));
	inRange( aux2 , Scalar(aceita_blur), Scalar(257), aux2);
	#ifdef usuario
		#ifdef mostra_range
			imshow("Regiao de Interesse", aux2);
		#endif
	#endif
	inRange( (*source) , Scalar(Hist_final), Scalar(257), aux3);
	#ifdef usuario
		#ifdef mostra_range
			imshow("Pontos novos", aux3);
		#endif
	#endif
	bitwise_and(aux2,aux3, (*source));
	#ifdef usuario
		#ifdef mostra_range
			imshow("Aceitos 1", (*source));
		#endif
	#endif



	
	vector<Mat> manchas;
	vector<Vec4i> posicoes;
	//Mat temp;
	define_objetos(source, &manchas, &posicoes, min_pontos, perc_pontosi);
	float ratio_y = (float)(*Original).rows/(float)(*source).rows;
	float ratio_x = (float)(*Original).cols/(float)(*source).cols;
	Quadrado_x[regioes_antigas].clear();
	Quadrado_y[regioes_antigas].clear();
	Quadrado_d[regioes_antigas].clear();
	Quadrado_b[regioes_antigas].clear();
	for(int i = 0; i<manchas.size(); i++){
		if((float)manchas[i].rows > 1.2*(float)manchas[i].cols){
			num.clear();
			int_to_string(i, &num);
			//imshow(num, manchas[i]);
			quadrado_x = max( (int)((float)posicoes[i][0]*ratio_x - 20 )  ,0);
			Quadrado_x[regioes_antigas].push_back(quadrado_x);
			quadrado_d = min(  (int) ((float)posicoes[i][2]*ratio_x + 20), (*Original).cols - 1);
			Quadrado_d[regioes_antigas].push_back(quadrado_d);
			quadrado_y = max(  (int) ((float)posicoes[i][1]*ratio_y -40),0);
			Quadrado_y[regioes_antigas].push_back(quadrado_y);
			quadrado_b = min( (int) ((float)posicoes[i][3]*ratio_y + 40), (*Original).rows - 1);
			Quadrado_b[regioes_antigas].push_back(quadrado_b);
		}
	}
	return 1;
}


bool RastreiaCone::varredura1(Mat* source, int num_area){
	int pos, x, y;
	Mat aux;
	vector<Mat> canais;

	Mat temp;
	temp = (*Original)( Rect(Quadrado_x[regioes_antigas][num_area],Quadrado_y[regioes_antigas][num_area],Quadrado_d[regioes_antigas][num_area]-Quadrado_x[regioes_antigas][num_area],Quadrado_b[regioes_antigas][num_area]-Quadrado_y[regioes_antigas][num_area]) );
	temp.copyTo( (*source) );

	if(tamanho_mat < 10){
		tamanho_mat = 10;
	}

	float ratio =((float)(*source).cols)/((float)(*source).rows);
	float size = min( (quadrado_b - quadrado_y) , (float)tamanho_mat);
	resize((*source), (*source), Size((int)(((float)size)*ratio), size ));

	//blur((*source), (*source), Size(blur_x_i+1,blur_y_i+1 ));
	Laranja((*source), source,2);

	Mat aux2;
	Mat aux3;
	#ifdef usuario
		#ifdef mostra_range
			imshow("Laranja", (*source) );
		#endif
	#endif
	
	inRange( (*source) , Scalar(min_aceita), Scalar(257), aux);
	#ifdef usuario
		#ifdef mostra_range
			imshow("Range", aux);
		#endif
	#endif
	blur(aux, aux2, Size(Peso_blur,Peso_blur));
	inRange( aux2 , Scalar(aceita_blur), Scalar(257), aux2);
	#ifdef usuario
		#ifdef mostra_range
			imshow("Regiao de Interesse", aux2);
		#endif
	#endif
	inRange( (*source) , Scalar(Hist_final), Scalar(257), aux3);
	#ifdef usuario
		#ifdef mostra_range
			imshow("Pontos novos", aux3);
		#endif
	#endif
	bitwise_and(aux2,aux3, (*source));
	#ifdef usuario
		#ifdef mostra_range
			imshow("Aceitos 1", (*source));
		#endif
	#endif
	
}


void RastreiaCone::define_objetos(Mat* source, vector<Mat> *manchas, vector<Vec4i> *posicoes, int min_pontos, int min_frac){
	//gettimeofday(&velho, NULL);
	int mat_rows = (*source).rows;
	int mat_cols = (*source).cols;
	uchar ponto;
	int p, c;
	bool preenchendo = false;

	Vec3i reta;
	vector<Vec3i> linha[2];
	int l, m;
	vector<int> id_conjunto[2];
	int num_conjuntos;

	vector<int> ref_conjunto;

	vector<vector<Vec3i> > conjuntos;
	vector<int> conjuntoID;
	int cont_conjuntos = 0;

	vector<Vec4i> limites;
	Vec4i temp_limite;

	float perc_pontos = (float)min_frac/1000;


	//imshow("pre blur", source);
	
	/*
	if(blur_x_define > 1){
		blur( source, source, Size(blur_x_define,1  ));
		inRange(source, Scalar(define_thresh), Scalar(255), source);
	}
	imshow("blur x", source);
	*/
	//gettimeofday(&velho, NULL);
	
	/*
	if(blur_y_define > 1){
		if(blur_x_define > 1)
			blur( source, aux, Size(blur_x_define, blur_y_define  ));
		else
			blur( source, aux, Size(1, blur_y_define  ));
		inRange(aux, Scalar(150), Scalar(255), aux);
		vector<Mat> canais;
		canais.clear();
		canais.push_back(aux);
		canais.push_back( source );
		merge(canais, aux);
		inRange(aux, Scalar(255, 255), Scalar(255,255), source );
	}
	*/
	/*
	gettimeofday(&novo, NULL);
	tempo = (int) (1000000 * (novo.tv_sec - velho.tv_sec) + (novo.tv_usec - velho.tv_usec));
	if(atualiza){
		cout<<"Tempo novo: "<<tempo<<endl;
	}
	*/
	//imshow("blur y", source);



	//varre a matriz encontrando os pontos positivos
	for(int y = 0; y<mat_rows; y++){
		l = y%2;
		m = 1-l;
		linha[l].clear();
		id_conjunto[l].clear();
		//coleta todas as retas da linha y
		for(int x = 0; x<mat_cols; x++){
			ponto = (*source).at<uchar>(Point(x, y));
			switch(preenchendo){
				case(false):
					if(ponto > 127){
						reta[0] = y;
						reta[1] = x;
						preenchendo = true;
					}	
					break;
				case(true):
					if(ponto < 127 ){
						reta[2] = x-1;
						preenchendo = false;
						linha[l].push_back(reta);
					}
					else if(x==mat_cols-1){
						reta[2] = x;
						preenchendo = false;
						linha[l].push_back(reta);
					}
					break;	
			}
		}
		for(p=0;p<linha[l].size();p++){
			num_conjuntos = 0;
			ref_conjunto.clear();
			for(c = 0; c<linha[m].size();c++){
				if( (linha[l][p][1] <= linha[m][c][2])&&(linha[l][p][2] >= linha[m][c][1]) ){
					num_conjuntos++;
					ref_conjunto.push_back( id_conjunto[m][c] );
				}
			}
			//se a linha não pertence a nenhum conjunto, cria novo conjunto
			if(num_conjuntos == 0){
				conjuntoID.push_back(cont_conjuntos);
				cont_conjuntos++;
				vector<Vec3i> temp;
				temp.push_back(linha[l][p]);
				conjuntos.push_back(temp);
				id_conjunto[l].push_back(conjuntoID.back() );
				temp_limite[1] = temp_limite[3] = y;
				temp_limite[0] = linha[l][p][1];
				temp_limite[2] = linha[l][p][2];
				limites.push_back(temp_limite);
			}
			//se a linha pertence apenas a um conjunto anexa a essa conjunto
			else if(num_conjuntos == 1){
				conjuntos[ref_conjunto[0]].push_back(linha[l][p]);
				id_conjunto[l].push_back(ref_conjunto[0]);
				limites[ref_conjunto[0]][3] = y;
				if(linha[l][p][1] < limites[ref_conjunto[0]][0]){
					limites[ref_conjunto[0]][0] = linha[l][p][1];
				} 
				if(linha[l][p][2] > limites[ref_conjunto[0]][2]){
					limites[ref_conjunto[0]][2] = linha[l][p][2];
				} 
			}
			//se a linha pertence a dois conjuntos, anexa ao primeiro e une os conjuntos
			else {
				conjuntos[ref_conjunto[0]].push_back(linha[l][p]);
				id_conjunto[l].push_back(ref_conjunto[0]);
				limites[ref_conjunto[0]][3] = y;
				if(linha[l][p][1] < limites[ref_conjunto[0]][0]){
					limites[ref_conjunto[0]][0] = linha[l][p][1];
				} 
				if(linha[l][p][2] > limites[ref_conjunto[0]][2]){
					limites[ref_conjunto[0]][2] = linha[l][p][2];
				} 
				for(c = 1; c<ref_conjunto.size(); c++){
					conjuntoID[ref_conjunto[c]] = ref_conjunto[0];
					if(limites[ref_conjunto[c]][0] < limites[ref_conjunto[0]][0]){
						limites[ref_conjunto[0]][0] = limites[ref_conjunto[c]][0];
					} 
					if(limites[ref_conjunto[c]][2] > limites[ref_conjunto[0]][2]){
						limites[ref_conjunto[0]][2] = limites[ref_conjunto[c]][2];
					}
					if(limites[ref_conjunto[c]][1] < limites[ref_conjunto[0]][1]){
						limites[ref_conjunto[0]][1] = limites[ref_conjunto[c]][1];
					} 
				}
			}
		}

	}

	//reajuste da união de conjuntos
	int posicao;
	int conteudo;
	int cont;
	vector<int> caminho;
	bool loop;
	for(p = 0; p<conjuntoID.size(); p++){
		cont = 0;
		posicao = p;
		caminho.clear();
		caminho.push_back(posicao);
		conteudo = conjuntoID[posicao];
		loop = false;
		while(posicao != conteudo){
			for(int c = 0; c<caminho.size(); c++){
				if(conteudo == caminho[c]){
					loop = true;
					c = caminho.size();
					conteudo = posicao;
				}
			}
			if(!loop){
				posicao = conteudo;
				caminho.push_back(posicao);
				conteudo = conjuntoID[posicao];
			}	
		}
		conjuntoID[p] = conteudo;

		if(limites[p][0] < limites[conteudo][0]){
			limites[conteudo][0] = limites[p][0];
		}
		if(limites[p][1] < limites[conteudo][1]){
			limites[conteudo][1] = limites[p][1];
		}
		if(limites[p][2] > limites[conteudo][2]){
			limites[conteudo][2] = limites[p][2];
		}
		if(limites[p][3] > limites[conteudo][3]){
			limites[conteudo][3] = limites[p][3];
		}

	}

	//Gera os objetos a partir dos conjuntos
	vector<Mat> objetos;
	vector<int> IDobjetos;
	vector<int> n_pontos;
	vector<Vec4i> limites_finais;

	objetos.clear();
	IDobjetos.clear();
	n_pontos.clear();
	limites_finais.clear();


	for(p = 0; p<conjuntos.size(); p++){
		cont = 0;
		while( (cont<IDobjetos.size() )&&( conjuntoID[p]!=IDobjetos[cont] ) ){
			cont++;
		}
		//se não achou um número existente cria nova matriz para objeto novo
		if(cont==IDobjetos.size()){
			IDobjetos.push_back(conjuntoID[p]);
			limites_finais.push_back(limites[conjuntoID[p]]);
			Mat temp_mat( (*source).size(), CV_8UC1);
			n_pontos.push_back(0);
			temp_mat = Scalar(0);
			objetos.push_back(temp_mat);
		}
		
		for(c = 0; c<conjuntos[p].size(); c++){
			n_pontos[cont] += (conjuntos[p][c][2] - conjuntos[p][c][1] + 1);
			//line( objetos[cont], Point(conjuntos[p][c][1] - limites_finais[cont][0] + 1,conjuntos[p][c][0] - limites_finais[p][1] +1), Point(conjuntos[p][c][2] - limites_finais[p][0] +1,conjuntos[p][c][0] - limites_finais[p][1] +1), Scalar(255), 1, 8);
			
			line( objetos[cont], Point(conjuntos[p][c][1],conjuntos[p][c][0]), Point(conjuntos[p][c][2],conjuntos[p][c][0]), Scalar(255,255,255), 1, 8);
			
			//line( objetos[cont], Point(limites_finais[cont][0],0), Point(limites_finais[cont][0],objetos[cont].rows), Scalar(255,0,0), 1, 8);
			//line( objetos[cont], Point(0 ,limites_finais[cont][1]), Point(objetos[cont].cols ,limites_finais[cont][1]), Scalar(255,0,0), 1, 8);
			
		}				
	}  
	//mostra as matrizes
	Mat temp;
	//cvtColor( (*source), (*source), CV_GRAY2BGR);
	/*
	string num;
	Mat pedacos( (*source).size(), CV_8UC1);
	pedacos = Scalar(0);
	*/
	//cont = 0;
	for(p = 0; p<objetos.size(); p++){
		if(n_pontos[p] > min_pontos){
			//num.clear();
			//int_to_string(cont, &num);
			//imshow(num, objetos[p]);
			int altura = limites_finais[p][3] - limites_finais[p][1];
			int largura = limites_finais[p][2] - limites_finais[p][0];
			if( (float)n_pontos[p]/(float)(altura*largura) > perc_pontos ){
				temp = (objetos[p])( Rect(limites_finais[p][0],limites_finais[p][1],limites_finais[p][2]-limites_finais[p][0],limites_finais[p][3]-limites_finais[p][1]) );
				//imshow("mancha"+num, temp );
				(*manchas).push_back(temp);
				(*posicoes).push_back(limites_finais[p]);
			}	
			//cont++;
			
			//line( (*source), Point(limites_finais[p][0],limites_finais[p][1]), Point(limites_finais[p][2],limites_finais[p][1]), Scalar(255,0,0), 1, 8);
			//line( (*source), Point(limites_finais[p][2],limites_finais[p][1]), Point(limites_finais[p][2],limites_finais[p][3]), Scalar(255,0,0), 1, 8);
			//line( (*source), Point(limites_finais[p][2],limites_finais[p][3]), Point(limites_finais[p][0],limites_finais[p][3]), Scalar(255,0,0), 1, 8);
			//line( (*source), Point(limites_finais[p][0],limites_finais[p][3]), Point(limites_finais[p][0],limites_finais[p][1]), Scalar(255,0,0), 1, 8);
			
		}
		/*
		else{
			add(pedacos, objetos[p], pedacos);
		}
		*/
	}
	//imshow("fragmento", source);
	//imshow("Pedacos",pedacos);
	

	/*
	gettimeofday(&novo, NULL);
	tempo = (int) (1000000 * (novo.tv_sec - velho.tv_sec) + (novo.tv_usec - velho.tv_usec));
	if(atualiza){
		cout<<"Tempo novo: "<<tempo<<endl;
	}
	*/
}


bool RastreiaCone::dados_mancha(Mat mancha, int partes){
	
	vector<float> dados;
	dados.clear();

	int centro_x = mancha.cols/2;
	int centro_y = mancha.rows/2;
	int linha;
	int k, ponto;
	int i, j;

	int min_lenght, avg_lenght_sup, avg_lenght_inf, max_lenght;
	min_lenght = 0;
	max_lenght = 0;

	int lenght;

	int inicio, fim;
	bool iniciou;


	int tamanho = mancha.rows/partes;

	float avg_inicio;
	float avg_fim;

	bool continuidade = false;
	float cont_verdadeiros = 0;
	float cont_quase = 0;



	for(k = 0; k< partes; k++){
		avg_inicio = 0;
		avg_fim = 0;
		for(i = k*tamanho; i < (k+1)*tamanho; i++){
			iniciou = false;
			for(j = 0; j< mancha.cols; j++){
				 if(mancha.at<uchar>(Point(j, i)) > 200 ){
				 	if(!iniciou){
				 		iniciou = true;
				 		inicio = j;
				 	}
				 	fim = j;
				 }
			}
			avg_fim+=fim+1;
			//avg_fim += (mancha.cols - 1 - fim);
			avg_inicio += ( (fim+1) - inicio);

		}
		dados.push_back(avg_inicio/(float)tamanho);
		//dados.push_back(avg_fim/(float)tamanho);
		//cout<<dados[k*2]<<"   "<<dados[k*2 +1]<<"   ";

	}
	//cout<<endl;





	for(i = 1; i<partes; i++){
		if(atualiza)
			//cout<<dados[i-1]<<"   "<<dados[i]<<"   "<<endl;
		if(dados[i-1]<=dados[i]){
			cont_verdadeiros++;
			if(dados[i-1]<dados[i]){
				cont_quase++;
			}
		}
	}
	cont_verdadeiros = cont_verdadeiros/(float)(partes-1);
	cont_quase = cont_quase/(float)(partes-1);

	/*
	for(i = 1; i<partes; i++){
		if(atualiza)
			cout<<dados[2*(i-1)]<<"   "<<dados[2*i]<<"   ";
		if(dados[2*(i-1)]>=dados[2*i]){
			cont_verdadeiros++;
			if(dados[2*(i-1)]>dados[2*i]){
				cont_quase++;
			}
		}
		if(atualiza)
			cout<<dados[2*(i-1)+1]<<"   "<<dados[2*i+1]<<endl;
		if(dados[2*(i-1)+1]>=dados[2*i+1]){
			cont_verdadeiros++;
			if(dados[2*(i-1)+1]>dados[2*i+1]){
				cont_quase++;
			}
		}
	}
	

	cont_verdadeiros = cont_verdadeiros/(float)(2*(partes-1));
	cont_quase = cont_quase/(float)(2*(partes-1));
	*/



	//if(atualiza)
	//	cout<<" "<<cont_verdadeiros<<"   "<<cont_quase<<endl;
	if( (cont_quase > 0.5)&&(cont_verdadeiros> 0.7)&&( (float)mancha.rows > (float)mancha.cols) ){
		continuidade = true;
	//	cout<<"ACHOU"<<endl;
	}




	/*
	for(i = 1; i<partes; i++){
		//if(atualiza)
			//cout<<dados[2*(i-1)]<<"   "<<dados[2*i]<<"   ";
		if(dados[2*(i-1)]>=dados[2*i]){
			cont_verdadeiros++;
		}
		//if(atualiza)
			//cout<<dados[2*(i-1)+1]<<"   "<<dados[2*i+1]<<endl;
		if(dados[2*(i-1)+1]>=dados[2*i+1]){
			cont_verdadeiros++;
		}
	}
	cont_verdadeiros = cont_verdadeiros/(float)(2*(partes-1));
	//if(atualiza)
		//cout<<" "<<cont_verdadeiros<<endl<<endl;
	if( (cont_verdadeiros> 0.8)&&( (float)mancha.rows > (float)mancha.cols) ){
		continuidade = true;
	}
	*/
	return continuidade;

}


bool RastreiaCone::identifica(Mat* source, int num_area, Mat* temp){
	
	bool achou = false;
	vector<Mat> manchas;
	vector<Vec4i> posicoes;
	//gettimeofday(&velho, NULL);

	define_objetos(source, &manchas, &posicoes, 15, 250);
	string num;
	int_to_string(num_area, &num);

	//vector<float> dados;

	vector<Vec4i> limites;

	//cvtColor((*source),(*source), CV_GRAY2BGR);
	for(int i = 0; i<posicoes.size(); i++){
		//dados.clear();

		if(dados_mancha(manchas[i],8)){
			limites.push_back(posicoes[i]);
			//line( (*source), Point(posicoes[i][0],posicoes[i][1]), Point(posicoes[i][2],posicoes[i][1]), Scalar(0,0,255), 1, 8);
			//line( (*source), Point(posicoes[i][2],posicoes[i][1]), Point(posicoes[i][2],posicoes[i][3]), Scalar(0,0,255), 1, 8);
			//line( (*source), Point(posicoes[i][2],posicoes[i][3]), Point(posicoes[i][0],posicoes[i][3]), Scalar(0,0,255), 1, 8);
			//line( (*source), Point(posicoes[i][0],posicoes[i][3]), Point(posicoes[i][0],posicoes[i][1]), Scalar(0,0,255), 1, 8);			
		}
	}

	//imshow(num+'i', (*source) );

	Quadrado_x[regioes_novas].clear();
	Quadrado_y[regioes_novas].clear();
	Quadrado_d[regioes_novas].clear();
	Quadrado_b[regioes_novas].clear();
	Vec4f area;
	if(limites.size() > 0){
		anterior = true;
	}
	

	//float ratio_y = (Quadrado_b[regioes_antigas][num_area] - Quadrado_y[regioes_antigas][num_area])/((float)(*source).rows);
	float ratio_x = (Quadrado_d[regioes_antigas][num_area] - Quadrado_x[regioes_antigas][num_area])/((float)(*source).cols);

	float aux_pos;

	for(int i = 0; i<limites.size(); i++){


		area[0] = (float)limites[i][0];
		area[1] = (float)limites[i][1];
		area[2] = (float)limites[i][2];
		area[3] = (float)limites[i][3];

		area[0] = area[0]*ratio_x;
		area[1] = area[1]*ratio_x;
		area[2] = area[2]*ratio_x;
		area[3] = area[3]*ratio_x;

		area[0] = area[0]+Quadrado_x[regioes_antigas][num_area];
		area[1] = area[1]+Quadrado_y[regioes_antigas][num_area];
		area[2] = area[2]+Quadrado_x[regioes_antigas][num_area];
		area[3] = area[3]+Quadrado_y[regioes_antigas][num_area];

		if(confirma){
			aux_pos = ((area[2] + area[0])/2)/((float)(*Original).cols);
			pos_angulo.push_back(aux_pos);
			aux_pos = ( (area[3] - area[1]) /( (float)(*Original).rows ) );
			pos_dist.push_back(aux_pos);
			aux_cont = aux_pos;
		}

		quadrado_y = (float)area[1] - (float)2*(float)delta;
		if(quadrado_y < 0){
			quadrado_y = 0;
		}

		quadrado_b = (float)area[3]+(float)2*(float)delta;
		if(quadrado_b > (float)(*Original).rows-1 ){
			quadrado_b = (float)(*Original).rows-1;
		}
		quadrado_x = (float)area[0] - (float)delta;
		if(quadrado_x < 0){
			quadrado_x = 0;
		}	
		quadrado_d = (float)area[2] + (float)delta;
		if(quadrado_d > (float)(*Original).cols -1){
			quadrado_d = (float)(*Original).cols - 1;
		}
		Quadrado_x[regioes_novas].push_back(quadrado_x);
		Quadrado_y[regioes_novas].push_back(quadrado_y);
		Quadrado_d[regioes_novas].push_back(quadrado_d);
		Quadrado_b[regioes_novas].push_back(quadrado_b);

		
		#ifdef filmar		
			if(confirma){

				
				area[0] = area[0]*ratio_novo;
				area[1] = area[1]*ratio_novo;
				area[2] = area[2]*ratio_novo;
				area[3] = area[3]*ratio_novo;
				

				line( (*temp), Point(area[0],area[1]), Point(area[2],area[1]), Scalar(0,0,255), 1, 8);
				line( (*temp), Point(area[2],area[1]), Point(area[2],area[3]), Scalar(0,0,255), 1, 8);
				line( (*temp), Point(area[2],area[3]), Point(area[0],area[3]), Scalar(0,0,255), 1, 8);
				line( (*temp), Point(area[0],area[3]), Point(area[0],area[1]), Scalar(0,0,255), 1, 8);
			}	
		#endif
		

		#ifdef usuario		
			if(confirma){

				
				area[0] = area[0]*ratio_novo;
				area[1] = area[1]*ratio_novo;
				area[2] = area[2]*ratio_novo;
				area[3] = area[3]*ratio_novo;
				

				line( (*temp), Point(area[0],area[1]), Point(area[2],area[1]), Scalar(0,0,255), 1, 8);
				line( (*temp), Point(area[2],area[1]), Point(area[2],area[3]), Scalar(0,0,255), 1, 8);
				line( (*temp), Point(area[2],area[3]), Point(area[0],area[3]), Scalar(0,0,255), 1, 8);
				line( (*temp), Point(area[0],area[3]), Point(area[0],area[1]), Scalar(0,0,255), 1, 8);
			}	
		#endif

	}
	imshow("SOURCE", (*temp));

	return achou;

}


void RastreiaCone::angulo(Mat* source, int ref){
	float angulo;
	angulo = 60*pos_angulo[ref] - 30;
	
	pub_angulo = angulo;


	#ifdef usuario
		bool sinal = false;
		if(angulo < 0){
			sinal = true;
			angulo = angulo*(-1);
		}
		string num;
		int angulo2 = angulo;
		int_to_string(angulo2, &num);
		string num2;
		angulo = angulo-angulo2;
		if( fabs(angulo) > 0 )
			angulo = angulo*100;
		else 
			angulo = 0;
		angulo2 = angulo;
		int_to_string(angulo2, &num2);

		while(num2.size() < 2){
			num2 = '0'+num2;
		}

		if(sinal)
			putText((*source), ('-'+num+'.'+num2+" graus"), Point(0,20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,0,0), 1, 8, false );
		else
			putText((*source), (num+'.'+num2+" graus"), Point(0,20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,0,0), 1, 8, false );
		
		//imshow("SOURCE", (*source));
	#endif
	#ifdef filmar
		bool sinal = false;
		if(angulo < 0){
			sinal = true;
			angulo = angulo*(-1);
		}
		string num;
		int angulo2 = angulo;
		int_to_string(angulo2, &num);
		string num2;
		angulo = angulo-angulo2;
		if( fabs(angulo) > 0 )
			angulo = angulo*100;
		else 
			angulo = 0;
		angulo2 = angulo;
		int_to_string(angulo2, &num2);

		while(num2.size() < 2){
			num2 = '0'+num2;
		}

		if(sinal)
			putText((*source), ('-'+num+'.'+num2+" graus"), Point(0,20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,0,0), 1, 8, false );
		else
			putText((*source), (num+'.'+num2+" graus"), Point(0,20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,0,0), 1, 8, false );
		
		//imshow("SOURCE", (*source));
	#endif	
}


void RastreiaCone::distancia(Mat* source, int ref){

	float prox = pos_dist[ref];


	Vec3f dado;


	//prox = sqrt(10/prox);
	prox = (2/(3*prox) );

	if(prox < 1){
		proximo = true;
	}

	dado[0] = prox;
	dado[1] = pub_angulo;
	dado[2] = 1;

	dados[ref_dados] = dado;

	ultimo_valido = ref_dados;

	#ifdef usuario
		string num;
		int prox2 = prox;
		int_to_string(prox2, &num);
		string num2;
		prox = prox-prox2;
		if( fabs(prox) > 0 )
			prox = prox*1000;
		else 
			prox = 0;
		prox2 = prox;
		int_to_string(prox2, &num2);
		while(num2.size() < 3){
			num2 = '0'+num2;
		}


		putText((*source), num+'.'+num2+'m', Point(0,40), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255), 1, 8, false );
			
		imshow("SOURCE", (*source));
	#endif

	#ifdef filmar
		string num;
		int prox2 = prox;
		int_to_string(prox2, &num);
		string num2;
		prox = prox-prox2;
		if( fabs(prox) > 0 )
			prox = prox*1000;
		else 
			prox = 0;
		prox2 = prox;
		int_to_string(prox2, &num2);
		while(num2.size() < 3){
			num2 = '0'+num2;
		}


		putText((*source), num+'.'+num2+'m', Point(0,40), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255), 1, 8, false );
			
	#endif
}


void RastreiaCone::achaPerto(Mat* source, Mat* temp){

		proximo = false;
		anterior = false;
		resize( (*Original), (*source), Size((int)(((float)50)*ratio_original), 50 ));
		Laranja((*source), source, 3);
		float centro_x = 0;
		float cont_pontos = 0;
		for(int i= 0; i< source->rows; i++ ){
			for(int j = 0; j<source->cols; j++){
				if(source->at<uchar>(j,i) > 200){
					cont_pontos++;
					centro_x +=j;
				}
			}
		}
		centro_x = centro_x/cont_pontos;
		//cout<<centro_x<<endl;
		centro_x = centro_x/(float)source->cols;
		cont_pontos = cont_pontos/(float)(source->rows * source->cols);

		if(cont_pontos > 0.1){
			proximo = true;
			Vec3f dado;
			pos_dist.clear();
			pos_angulo.clear();
			pos_dist.push_back(1);
			pos_angulo.push_back(centro_x);
			angulo(temp,0);
			distancia(temp,0);
		}
		else{
			Vec3f dado;
			dado[0] = 0;
			dado[1] = 0;
			dado[2] = 0;

			dados[ref_dados] = dado;
		}

		#ifdef usuario
			int pos_x = temp->cols*centro_x;
			line( (*temp), Point(pos_x,0), Point(pos_x,temp->rows), Scalar(0,0,255), 1, 8);
			imshow("SOURCE", (*temp));
		#endif
		#ifdef filmar
			int pos_x = temp->cols*centro_x;
			line( (*temp), Point(pos_x,0), Point(pos_x,temp->rows), Scalar(0,0,255), 1, 8);
		#endif
}


void RastreiaCone::rastreia(Mat source){
	
	#ifdef usuario

	if(filtro){
		PreencheTabela();
	}

	#endif


	ref_dados++;
	if(ref_dados>29){
		ref_dados = 0;
	}
	dados[ref_dados][2] = 0;

	//gettimeofday(&velho, NULL);
	Mat temp2(source.size(), CV_8UC3);
	Original = &source;
	ratio_original = (float)source.cols/(float)source.rows;

	Mat temp;
	if(tamanho_final < 10)
			tamanho_final = 10;
	resize((*Original), temp, Size((int)(((float)tamanho_final)*ratio_original), tamanho_final ));



	//Visual
	#ifdef usuario
	if(tamanho_final < 10)
			tamanho_final = 10;
	resize((*Original), temp, Size((int)(((float)tamanho_final)*ratio_original), tamanho_final ));
	ratio_novo = ( (float) temp.rows /(float)(*Original).rows );
	imshow("SOURCE", temp);
	//Fim Visual
	#endif

	#ifdef filmar
		if(tamanho_final < 10)
				tamanho_final = 10;
		resize((*Original), temp, Size((int)(((float)tamanho_final)*ratio_original), tamanho_final ));
		ratio_novo = ( (float) temp.rows /(float)(*Original).rows );
		
	#endif

	//estando muito proximo do cone não é mais necessário gastar muito processamento confirmando a identificação
	//basta monitorar a aproximação em relação ao mesmo
	
	pub_angulo = 100;
	pub_distancia = -1;
	encontrou_cone = false;

	//if(proximo){
	if(false){
		achaPerto(&temp2, &temp);
		/*
		for(int i = 0; i< pos_angulo.size(); i++){
			angulo(&temp, i);
			distancia(&temp, i);
		}
		*/
	}
	
	else{
		//avaliza apenas regiao em torno de onde o cone foi encontrado anteriormente
		if(anterior){
		//if(false){
			confirma = true;

			anterior = false;
			pos_angulo.clear();
			pos_dist.clear();
			for(int i = 0; i<Quadrado_x[regioes_antigas].size(); i++ ){
				varredura1(&temp2,i);
				identifica(&temp2, i, &temp);
			}
			//Apenas se ja foi identificado o cone no frame anterior marca o angulo e distancia
			//evitar falsos positivos
			for(int i = 0; i<pos_angulo.size(); i++){
				angulo(&temp, i);
				distancia(&temp, i);
			}
			regioes_antigas = regioes_novas;
			regioes_novas = 1-regioes_antigas;
		}
		//avlia imagem inteira da camera
		else{

			regioes_antigas = 0;
			regioes_novas = 1;
			confirma = false;
			proximo = false;
			if(tamanho0 < 10)
				tamanho0 = 10;


			resize(source, temp2, Size((int)(((float)tamanho0)*ratio_original), tamanho0 ));
			varredura0(&temp2);
			


			
			pos_angulo.clear();
			for(int i = 0; i<Quadrado_x[regioes_antigas].size(); i++ ){
				varredura1(&temp2,i);
				identifica(&temp2, i, &temp);
			}
			
			regioes_antigas = regioes_novas;
			regioes_novas = 1-regioes_antigas;	
		}
	}
	int cont_certos = 0;
	for(int i = 0; i<30; i++){
		if(dados[i][2] > 0){
			cont_certos++;
		}		
	}
	encontrou_cone = false;
	if(cont_certos > 15){
		min_valido = true;
		encontrou_cone = true;
		pub_distancia = dados[ultimo_valido][0];
		pub_angulo = dados[ultimo_valido][1];
	}
	else{
		min_valido = false;
	}

	#ifdef filmar
	if(!video_init){
		video = new VideoWriter("/home/ricardo/Documents/oi3.avi",CV_FOURCC('M','J','P','G'),33, Size(temp.cols,temp.rows),true);
		video_init = true;
	}
	video->write(temp);
	#endif
}
