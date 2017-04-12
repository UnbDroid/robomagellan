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

class RastreiaCone5{
public:

	int min_H1;
	int max_H1;
	int min_S1;
	int max_S1;
	int min_V1;
	int max_V1;
	int min_H2;
	int max_H2;
	int min_S2;
	int max_S2;
	int min_V2;
	int max_V2;

	int min_H1i;
	int max_H1i;
	int min_S1i;
	int max_S1i;
	int min_V1i;
	int max_V1i;
	int min_H2i;
	int max_H2i;
	int min_S2i;
	int max_S2i;
	int min_V2i;
	int max_V2i;


	int min_H1z;
	int max_H1z;
	int min_S1z;
	int max_S1z;
	int min_V1z;
	int max_V1z;
	int min_H2z;
	int max_H2z;
	int min_S2z;
	int max_S2z;
	int min_V2z;
	int max_V2z;

	int min_H1p;
	int max_H1p;
	int min_S1p;
	int max_S1p;
	int min_V1p;
	int max_V1p;
	int min_H2p;
	int max_H2p;
	int min_S2p;
	int max_S2p;
	int min_V2p;
	int max_V2p;



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
	

private:

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


public:
	bool anterior;

	RastreiaCone5();
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

void RastreiaCone5::int_to_string(int valor, string* numeral){
	int inteiro = valor;
	int resto = valor;
	do{
		resto = inteiro%10;
		inteiro = inteiro/10;
		(*numeral).push_back( (char)(resto + 48) );
	}while(inteiro > 0);
	reverse((*numeral).begin(),(*numeral).end()); 
}

RastreiaCone5::RastreiaCone5(){
	define_blur_x = 0;
	define_blur_y = 0;
	define_thresh = 127;	

	anterior = false;
	proximo = false;
	delta = 20;


	min_H1i = 0;
	max_H1i = 15;
	min_S1i = 150;
	max_S1i = 255;
	min_V1i = 80;
	max_V1i = 200;
	min_H2i = 160;
	max_H2i = 180;
	min_S2i = 150;
	max_S2i = 190;
	min_V2i = 120;
	max_V2i = 255;


	min_H1z = 0;
	max_H1z = 15;
	min_S1z = 100;
	max_S1z = 255;
	min_V1z = 70;
	max_V1z = 255;
	min_H2z = 160;
	max_H2z = 180;
	min_S2z = 50;
	max_S2z = 255;
	min_V2z = 30;
	max_V2z = 255;

	min_H1p = 0;
	max_H1p = 15;
	min_S1p = 130;
	max_S1p = 215;
	min_V1p = 40;
	max_V1p = 255;
	min_H2p = 160;
	max_H2p = 180;
	min_S2p = 130;
	max_S2p = 255;
	min_V2p = 120;
	max_V2p = 255;


	min_blur = 120;
	blur_y = 3;
	blur_x = 1;

	min_blur_i = 105;
	blur_y_i = 3;
	blur_x_i = 0;

	tamanho_mat = 120;

	atualiza = true;

	passo = -1;

	calibra = false;
	iniciou_calibra = false;

	tamanho_final = 200;
	tamanho0 = 400;

	min_pontos = 10;
	perc_pontosi = 400;

	cont_ruim = 0;
	aux_cont = 0;

}


void RastreiaCone5::Laranja(Mat source, Mat* dest, int vez){
	/*
	if(atualiza){
		gettimeofday(&velho, NULL);
	}
	*/
	Mat azul, verde, hsv;
	cvtColor(source, hsv, CV_BGR2HSV);

	inRange(hsv, Scalar(min_H1, min_S1, min_V1), Scalar(max_H1, max_S1, max_V1), azul);
	inRange(hsv, Scalar(min_H2, min_S2, min_V2), Scalar(max_H2, max_S2, max_V2), verde);
	

	//Visual

	if(vez == 3){
			
			vector<Mat> canais;
			canais.clear();
			canais.push_back(azul);
			canais.push_back(verde);

			Mat vermelho(source.size(), CV_8UC1);
			vermelho = Scalar(0);

			canais.push_back(vermelho);
			merge(canais, vermelho);
			imshow("cor3", vermelho);
	}
	
		if(vez == 1){
			
			vector<Mat> canais;
			canais.clear();
			canais.push_back(azul);
			canais.push_back(verde);

			Mat vermelho(source.size(), CV_8UC1);
			vermelho = Scalar(0);

			canais.push_back(vermelho);
			merge(canais, vermelho);
			imshow("cor1", vermelho);
		}


		if(vez == 2){

			vector<Mat> canais;
			canais.clear();
			canais.push_back(azul);
			canais.push_back(verde);

			Mat vermelho(source.size(), CV_8UC1);
			vermelho = Scalar(0);

			canais.push_back(vermelho);
			merge(canais, vermelho);
			imshow("cor2", vermelho);
		}
	//inRange(normal_img, Scalar(255,0,0), Scalar(255,255,0), azul);
	//inRange(normal_img, Scalar(0,255,0), Scalar(255,255,0), verde);
	//fim visual
	

	add(azul, verde, (*dest));
	//imshow("aceita", hsv);
	/*
	if(atualiza){
		gettimeofday(&novo, NULL);
		tempo = (int) (1000000 * (novo.tv_sec - velho.tv_sec) + (novo.tv_usec - velho.tv_usec));
		cout<<"Tempo laranja: "<<tempo<<endl;
	}
	*/

}




int RastreiaCone5::varredura0(Mat* source){
	//gettimeofday(&velho, NULL);
	bool certo = false;
	int pos, x, y;
	vector<Mat> canais;

	min_H1 = min_H1i;
	max_H1 = max_H1i;
	min_S1 = min_S1i;
	max_S1 = max_S1i;
	min_V1 = min_V1i;
	max_V1 = max_V1i;
	min_H2 = min_H2i;
	max_H2 = max_H2i;
	min_S2 = min_S2i;
	max_S2 = max_S2i;
	min_V2 = min_V2i;
	max_V2 = max_V2i;

	Mat aux;
	//blur(*source, *source, Size(1,4 ));
	Laranja(*source, source,1);
	/*
	blur( (*source), aux, Size(2,4 ));
	inRange(aux, Scalar(120), Scalar(255), aux);
	canais.clear();
	canais.push_back(aux);
	canais.push_back( (*source) );
	merge(canais, aux);
	inRange(aux, Scalar(255, 255), Scalar(255,255), (*source) );
	*/
	vector<Mat> manchas;
	vector<Vec4i> posicoes;
	string num;
	Mat temp;
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
	min_H1 = min_H1z;
	max_H1 = max_H1z;
	min_S1 = min_S1z;
	max_S1 = max_S1z;
	min_V1 = min_V1z;
	max_V1 = max_V1z;
	min_H2 = min_H2z;
	max_H2 = max_H2z;
	min_S2 = min_S2z;
	max_S2 = max_S2z;
	min_V2 = min_V2z;
	max_V2 = max_V2z;
	return 1;
}


bool RastreiaCone5::varredura1(Mat* source, int num_area){
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

	/*
	imshow("antes", (*source));
	
	blur( (*source), aux, Size(blur_x+1,blur_y + 1  ));
	inRange(aux, Scalar(min_blur), Scalar(255), aux);
	canais.clear();
	canais.push_back(aux);
	canais.push_back( (*source) );
	merge(canais, aux);
	inRange(aux, Scalar(255, 255), Scalar(255,255), (*source) );
	
	imshow("depois", (*source));
	//imshow("parte", *source);
	*/
}


void RastreiaCone5::define_objetos(Mat* source, vector<Mat> *manchas, vector<Vec4i> *posicoes, int min_pontos, int min_frac){
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


bool RastreiaCone5::dados_mancha(Mat mancha, int partes){
	
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


	for(i = 1; i<partes-2; i++){
		if(atualiza)
			cout<<dados[i-1]<<"   "<<dados[i]<<"   "<<endl;
		if(dados[i-1]<=dados[i]){
			cont_verdadeiros++;
			if(dados[i-1]<dados[i]){
				cont_quase++;
			}
		}
	}
	cont_verdadeiros = cont_verdadeiros/(float)(partes-2-1);
	cont_quase = cont_quase/(float)(partes-2-1);

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



	if(atualiza)
		cout<<" "<<cont_verdadeiros<<"   "<<cont_quase<<endl<<endl;
	if( (cont_quase > 0.7)&&(cont_verdadeiros> 0.7)&&( (float)mancha.rows > (float)mancha.cols) ){
		continuidade = true;
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


bool RastreiaCone5::identifica(Mat* source, int num_area, Mat* temp){
	
	bool achou = false;
	vector<Mat> manchas;
	vector<Vec4i> posicoes;
	//gettimeofday(&velho, NULL);

	define_objetos(source, &manchas, &posicoes, 15, 400);
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
			aux_pos =100*( ((area[3] - area[1])*(area[2] - area[0]))  /( (float)(*Original).rows*(float)(*Original).cols) );
			pos_dist.push_back(aux_pos);
			if(aux_pos > 20){
				proximo = true;
			}
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
		

	}
	//imshow("SOURCE", (*temp));


	return achou;

}


void RastreiaCone5::angulo(Mat* source, int ref){
	float angulo;
	angulo = 60*pos_angulo[ref] - 30;
	
	pub_angulo = angulo;

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
	
	imshow("SOURCE", (*source));
		
}


void RastreiaCone5::distancia(Mat* source, int ref){

	float prox = pos_dist[ref];

	pub_distancia = prox;
	encontrou_cone = true;

	string num;
	int prox2 = prox;
	int_to_string(prox2, &num);
	string num2;
	prox = prox-prox2;
	if( fabs(prox) > 0 )
		prox = prox*10000000;
	else 
		prox = 0;
	prox2 = prox;
	int_to_string(prox2, &num2);
	while(num2.size() < 7){
		num2 = '0'+num2;
	}


	putText((*source), num+'.'+num2+'%', Point(0,40), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255), 1, 8, false );
		
	imshow("SOURCE", (*source));

}


void RastreiaCone5::achaPerto(Mat* source, Mat* temp){
		/*
		if(anterior){
			cout<<"PROXIMO INICIA AQUI"<<endl;
		}
		*/
		proximo = false;
		anterior = false;
		min_H1 = min_H1p;
		max_H1 = max_H1p;
		min_S1 = min_S1p;
		max_S1 = max_S1p;
		min_V1 = min_V1p;
		max_V1 = max_V1p;
		min_H2 = min_H2p;
		max_H2 = max_H2p;
		min_S2 = min_S2p;
		max_S2 = max_S2p;
		min_V2 = min_V2p;
		max_V2 = max_V2p;
		resize( (*Original), (*source), Size((int)(((float)50)*ratio_original), 50 ));
		Laranja((*source), source, 3);
		pos_dist.clear();
		pos_angulo.clear();
		vector<Mat> manchas;
		vector<Vec4i> posicoes;
		define_objetos(source, &manchas, &posicoes, 50, 400);
		vector<float> dados;
		vector<Vec4i> limites;
		cvtColor((*source),(*source), CV_GRAY2BGR);
		float ratio_perto = ( (float) (*temp).rows /(float)(*source).rows );
		Vec4i area;

		float aux_pos;
		if(posicoes.size()>0){
			proximo = true;
			
			for(int i = 0; i<posicoes.size(); i++){	


				aux_pos =100*( (float)manchas[i].cols * (float)manchas[i].rows) /( (float)(*source).rows*(float)(*source).cols) ;
				pos_dist.push_back(aux_pos);

				area[0] = posicoes[i][0]*ratio_perto;
				area[1] = posicoes[i][1]*ratio_perto;
				area[2] = posicoes[i][2]*ratio_perto;
				area[3] = posicoes[i][3]*ratio_perto;

				aux_pos = ((area[2] + area[0])/2)/((float)(*temp).cols);
				pos_angulo.push_back(aux_pos);

				line( (*temp), Point(area[0],area[1]), Point(area[2],area[1]), Scalar(0,0,255), 1, 8);
				line( (*temp), Point(area[2],area[1]), Point(area[2],area[3]), Scalar(0,0,255), 1, 8);
				line( (*temp), Point(area[2],area[3]), Point(area[0],area[3]), Scalar(0,0,255), 1, 8);
				line( (*temp), Point(area[0],area[3]), Point(area[0],area[1]), Scalar(0,0,255), 1, 8);			
			
			}
		}
		/*
		else{
			cout<<"PROXIMO ACABA AQUI"<<endl;
		}
		*/
		imshow("SOURCE", (*temp));
}


void RastreiaCone5::rastreia(Mat source){
	


	//gettimeofday(&velho, NULL);
	Mat temp2(source.size(), CV_8UC3);
	Original = &source;
	ratio_original = (float)source.cols/(float)source.rows;

	
	//Visual
	Mat temp;
	if(tamanho_final < 10)
			tamanho_final = 10;
	resize((*Original), temp, Size((int)(((float)tamanho_final)*ratio_original), tamanho_final ));
	ratio_novo = ( (float) temp.rows /(float)(*Original).rows );
	imshow("SOURCE", temp);
	//Fim Visual
	

	//estando muito proximo do cone não é mais necessário gastar muito processamento confirmando a identificação
	//basta monitorar a aproximação em relação ao mesmo
	
	pub_angulo = 100;
	pub_distancia = -1;
	encontrou_cone = false;

	//if(proximo){
	if(false){
		achaPerto(&temp2, &temp);
		for(int i = 0; i< pos_angulo.size(); i++){
			angulo(&temp, i);
			distancia(&temp, i);
		}
	}
	
	else{
		//avaliza apenas regiao em torno de onde o cone foi encontrado anteriormente
		if(anterior){
		//if(false){
			min_H1 = min_H1z;
			max_H1 = max_H1z;
			min_S1 = min_S1z;
			max_S1 = max_S1z;
			min_V1 = min_V1z;
			max_V1 = max_V1z;
			min_H2 = min_H2z;
			max_H2 = max_H2z;
			min_S2 = min_S2z;
			max_S2 = max_S2z;
			min_V2 = min_V2z;
			max_V2 = max_V2z;

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
				identifica(&temp2, i, &temp2);
			}
			/*
			for(int i = 0; i<pos_angulo.size(); i++){
				angulo(&temp, i);
				distancia(&temp, i);
			}
			*/
			regioes_antigas = regioes_novas;
			regioes_novas = 1-regioes_antigas;	
		}
	}
	/*
	gettimeofday(&novo, NULL);
	tempo = (int) (1000000 * (novo.tv_sec - velho.tv_sec) + (novo.tv_usec - velho.tv_usec));
	if(atualiza){
		cout<<"Tempo novo: "<<tempo<<endl;
	}
	*/
}
