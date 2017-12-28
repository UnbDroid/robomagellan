#include "RastreiaCone0.hpp"


void RastreiaCone::PreencheTabela(){

		
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
	if(baixoV > 256)
		baixoV = 256;
	for(i = descidaV; i<baixoV; i++){
		valor += incremento;
		V[i] = valor;
	}
	for(i = baixoV; i<256; i++){
		V[i] = 0;
	}

	
	for(k = 0; k<256; k++){
		for(i = 0; i<256; i++){
			for(j = 0; j<256; j++){
				Tabela[i][j][k] = (uchar) 255*H[i]*S[j]*V[k];
			}
		}
	}
	

	
	#ifndef useLab

	#ifndef soma
		float vetor_temporario[256];
		if (potH == 0){
			for(j = 0; j<256; j++){
				H[j] = sqrt(H[j]);
			}
		}
		else if(potH > 1){
			for(i = 0; i<256; i++){
				vetor_temporario[i] = H[i];
			}
			for(i = 0; i<potH-1; i++){
				for(j = 0; j<256; j++){
					H[j] = H[j]*vetor_temporario[j];
				}
			}
		}
		if (potS == 0){
			for(j = 0; j<256; j++){
				S[j] = sqrt(S[j]);
			}
		}
		else if(potS > 1){
			for(i = 0; i<256; i++){
				vetor_temporario[i] = S[i];
			}
			for(i = 0; i<potS-1; i++){
				for(j = 0; j<256; j++){
					S[j] = S[j]*vetor_temporario[j];
				}
			}
		}
		if (potV == 0){
			for(j = 0; j<256; j++){
				V[j] = sqrt(V[j]);
			}
		}
		else if(potV > 1){
			for(i = 0; i<256; i++){
				vetor_temporario[i] = V[i];
			}
			for(j = 0; j<256; j++){
				for(i = 0; i< (potV-1); i++){
					V[j] =  V[j]*vetor_temporario[j];
				}
			}
		}	

	#endif

	for(k = 0; k<251; k++){
		for(i = 0; i<256; i++){
			for(j = 0; j<256; j++){
				
				#ifdef soma
					Tabela[i][j][k] = (uchar) 255*( (H[i] + S[j] + V[k])/3.0);
				#endif
				#ifndef soma
					Tabela[i][j][k] = (uchar) 255*H[i]*S[j]*V[k];
				#endif
			}
		}
	}

	for(i = 10; i<21; i++){
		H[i] = 1;
	}

	for(k = 251; k<256; k++){
		for(i = 0; i<256; i++){
			for(j = 0; j<256; j++){
				
				#ifdef soma
					Tabela[i][j][k] = (uchar) 255*( (H[i] + S[j] + V[k])/3.0);
				#endif
				#ifndef soma
					Tabela[i][j][k] = (uchar) 255*H[i]*S[j]*V[k];
				#endif
			}
		}
	}

	for(i = 175; i<177; i++ ){
		for(k = 200; k<256; k++){
			for(j = 190; j<256; j++){
				
				#ifdef soma
					Tabela[i][j][k] = (uchar) 255*( (H[i] + S[j] + V[k])/3.0);
				#endif
				#ifndef soma
					Tabela[i][j][k] = (uchar) 255*0.8;
				#endif
			}
		}
	}

	for(i = 177; i<180; i++ ){
		for(k = 200; k<256; k++){
			for(j = 190; j<256; j++){
				
				#ifdef soma
					Tabela[i][j][k] = (uchar) 255*( (H[i] + S[j] + V[k])/3.0);
				#endif
				#ifndef soma
					Tabela[i][j][k] = (uchar) 255;
				#endif
			}
		}
	}

	
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
			S_pondera = 60;
			V_pondera = 70;
			aceita_final = 160;
			size_blur = 15;
			aceita_blur = 30;

			min_aceita = 250;
			aceita_final = 160;

			dif_centroide = 10;
			dif_pixel = 5;

			//Peso_original = 8;

			subidaH1 = 0;
			step1_H1 = 0;
			altoH1 = 12;
			descidaH1 = 17;
			step2_H1 = 20;
			baixoH1 = 30;

			subidaH2 = 160;
			step1_H2 = 0;
			altoH2 = 170;
			descidaH2 = 170;
			step2_H2 = 0;
			baixoH2 = 180;

			subidaS = 0;
			step1_S = 0;
			altoS = 200;
			descidaS = 256;
			step2_S = 100;
			baixoS = 256;

			subidaV = 0;
			step1_V = 0;
			altoV = 0;
			descidaV = 256;
			step2_V = 70;
			baixoV = 256;

			potH = 3;
			potS = 5;
			potV = 0;


			//Perto
			min_aceitaz = 250;
			H_ponderaz = 0;
			S_ponderaz = 100;
			V_ponderaz = 70;
			aceita_finalz = 160;
			size_blurz = 15;
			aceita_blurz = 30;
			//Peso_original = 8;



			subidaH1z = 0;
			step1_H1z = 0;
			altoH1z = 0;
			descidaH1z = 10;
			step2_H1z = 20;
			baixoH1z = 30;

			subidaH2z = 160;
			step1_H2z = 0;
			altoH2z = 170;
			descidaH2z = 170;
			step2_H2z = 0;
			baixoH2z = 180;

			subidaSz = 130;
			step1_Sz = 0;
			altoSz = 250;
			descidaSz = 256;
			step2_Sz = 100;
			baixoSz = 256;

			subidaVz = 0;
			step1_Vz = 80;
			altoVz = 100;
			descidaVz = 256;
			step2_Vz = 70;
			baixoVz = 256;


		#endif	

	#endif

	#ifdef fosco

		#ifdef ponderado
			
			H_pondera = 0;
			S_pondera = 100;
			V_pondera = 70;
			aceita_final = 160;
			size_blur = 25;
			aceita_blur = 50;
			//Peso_original = 8;

			subidaH1 = 0;
			step1_H1 = 0;
			altoH1 = 0;
			descidaH1 = 15;
			step2_H1 = 20;
			baixoH1 = 30;

			subidaH2 = 160;
			step1_H2 = 0;
			altoH2 = 170;
			descidaH2 = 170;
			step2_H2 = 0;
			baixoH2 = 180;

			subidaS = 70;
			step1_S = 0;
			altoS = 170;
			descidaS = 220;
			step2_S = 0;
			baixoS = 256;

			subidaV = 0;
			step1_V = 80;
			altoV = 100;
			descidaV = 256;
			step2_V = 70;
			baixoV = 256;

			min_aceita = 250;


			potH = 3;
			potS = 5;
			potV = 0;


			//Perto
			min_aceitaz = 250;
			H_ponderaz = 0;
			S_ponderaz = 100;
			V_ponderaz = 70;
			aceita_finalz = 160;
			size_blurz = 15;
			aceita_blurz = 30;
			//Peso_original = 8;
			
		#endif

	#endif

	#ifdef useLab

			H_pondera = 0;
			S_pondera = 100;
			V_pondera = 70;
			aceita_final = 160;
			size_blur = 25;
			aceita_blur = 50;
			//Peso_original = 8;

			subidaH1 = 0;
			step1_H1 = 0;
			altoH1 = 90;
			descidaH1 = 140;
			step2_H1 = 0;
			baixoH1 = 256;

			subidaH2 = 255;
			step1_H2 = 0;
			altoH2 = 255;
			descidaH2 = 0;
			step2_H2 = 0;
			baixoH2 = 0;

			subidaS = 125;
			step1_S = 0;
			altoS = 145;
			descidaS = 160;
			step2_S = 0;
			baixoS = 180;

			subidaV = 140;
			step1_V = 0;
			altoV = 155;
			descidaV = 175;
			step2_V = 0;
			baixoV = 190;

			min_aceita = 250;

	#endif

	PreencheTabela();



	min_blur = 120;
	blur_y = 3;
	blur_x = 1;

	min_blur_i = 105;
	blur_y_i = 3;
	blur_x_i = 0;

	tamanho_mat = 180;

	atualiza = true;

	passo = -1;

	calibra = false;
	iniciou_calibra = false;

	tamanho_final = 480;
	tamanho0 = 480;

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



#ifdef segmentacao

void RastreiaCone::Luminosidade(Mat* source)
{
	//Equaliza canal L
	vector<Mat> channels;
	split((*source),channels);
	equalizeHist(channels[0],channels[0]);
	merge(channels,(*source));
}


void RastreiaCone::Segmenta(Mat src)
{  
	vector<Segmento> segmentos;
	Segmento segmento;
	Mat ref(src.size(),CV_8UC1);
	ref = Scalar(255);
	int i,j,k;
	uchar *p,*p2;
	int nRows = src.rows;
	int nCols = src.cols * 3;
	for( i = 0; i < nRows; ++i)
	{
		p = src.ptr<uchar>(i);
		p2 = ref.ptr<uchar>(i);
		for ( j = 0, k = 0; j < nCols; j+=3, k++){
			if(p2[k]>120 )
			{
				if(Tabela[p[j]][p[j+1]][p[j+2]] > min_aceita)
				{

				}
			}
		}
	}
}

int RastreiaCone::varredura0(Mat* source){

	Mat aux;
	source->copyTo(aux);
	cvtColor(*source,*source,CV_BGR2Lab);
	Luminosidade(source);
	Segmenta(*source);
	return 1;
}

#endif

#ifndef useLab

void RastreiaCone::Laranja(Mat source, Mat* dest, int vez){

	gettimeofday(&tempo1, NULL);

	Mat Lab;
	int num_channels;
	
	cvtColor(source, Lab, CV_BGR2HSV);
	cvtColor(source, (*dest), CV_BGR2GRAY);

	Mat uniao;

	int i,j;
    uchar* p; 
    uchar* p2;
    int nRows;
    int nCols;

    vector<Mat> channels;
    vector<Mat> canais(3);

	
	if(vez > 0 ){
		split(Lab,channels);			
		#ifdef ponderado
			//equalizeHist(channels[0], canais[0]);
			
			equalizeHist(channels[1], canais[1]);
			
			float S_hist = (float)S_pondera/100;
			float S_regular = 1-S_hist;
			add(S_regular*channels[1], S_hist*canais[1], channels[1]);	
			equalizeHist(channels[2], canais[2]);
			float V_hist = (float)V_pondera/100;
			float V_regular = 1-V_hist;
			add(V_regular*channels[2], V_hist*canais[2], channels[2]);

			
			Mat mostrar;
			merge(channels, mostrar);
			cvtColor(mostrar,mostrar, CV_HSV2BGR);
			//imshow("PONDERADO",mostrar);
			
		#endif	
			
	    #ifdef mostra_partes
			/*
			if(vez==1)
			{
				imshow("h",channels[0]);
				imshow("s",channels[1]);
				imshow("v",channels[2]);
			}
			else
			{
				imshow("H",channels[0]);
				imshow("S",channels[1]);
				imshow("V",channels[2]);
			}
			*/
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
			    	putText(mostra_imagem, ("L"), Point(0,20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,0,0), 1, 8, false );
			    	//imshow("Hdepois3", mostra_imagem);
			    	cvtColor(partes_mostra7, mostra_imagem, CV_GRAY2BGR);
			    	putText(mostra_imagem, ("a"), Point(0,20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,0,0), 1, 8, false );
			    	//imshow("Sdepois3", mostra_imagem);
			    	cvtColor(partes_mostra8, mostra_imagem, CV_GRAY2BGR);
			    	putText(mostra_imagem, ("b"), Point(0,20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,0,0), 1, 8, false );
			    	//imshow("Vdepois3", mostra_imagem);
			    #endif	
		    
		    }

	    #endif
	  
	    
		    
		#ifdef ponderado   
		    num_channels = Lab.channels();
		    nRows = Lab.rows;
		    nCols = Lab.cols * num_channels;
		    for( i = 0; i < nRows; ++i)
		    {
		        p = Lab.ptr<uchar>(i);
		        p2 = dest->ptr<uchar>(i);
		        int k = 0;
		        for ( j = 0, k = 0; j < nCols; j+=3, k++){
		            p2[k] = Tabela[p[j]][p[j+1]][p[j+2]];
		        }
		    }
		    #ifdef mostra_partes
		    	//if(vez == 1)
		    		//imshow("combinacao",(*dest));
		    	//else
		    		//imshow("Combinacao",(*dest));
		    #endif
		#endif    
		    	
	}

	
	gettimeofday(&tempo2, NULL);
	tempo = (int) (1000000 * (tempo2.tv_sec - tempo1.tv_sec) + (tempo2.tv_usec - tempo1.tv_usec));
	if(atualiza && vez == 1){
		//cout<<"laranja: "<<tempo<<endl;
	}

}



#else 

void RastreiaCone::Laranja(Mat source, Mat* dest, int vez){

	gettimeofday(&tempo1, NULL);

	Mat Lab;
	int num_channels;
	
	cvtColor(source, Lab, CV_BGR2Lab);
	cvtColor(source, (*dest), CV_BGR2GRAY);

	Mat uniao;

	int i,j;
    uchar* p; 
    uchar* p2;
    int nRows;
    int nCols;

    vector<Mat> channels;
	
	if(vez > 0 ){
			
		
	    #ifdef mostra_partes
			split(Lab,channels);
			if(vez==1)
			{
				imshow("l",channels[0]);
				imshow("a",channels[1]);
				imshow("b",channels[2]);
			}
			else
			{
				imshow("L",channels[0]);
				imshow("A",channels[1]);
				imshow("B",channels[2]);
			}

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
			    	putText(mostra_imagem, ("L"), Point(0,20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,0,0), 1, 8, false );
			    	imshow("Ldepois3", mostra_imagem);
			    	cvtColor(partes_mostra7, mostra_imagem, CV_GRAY2BGR);
			    	putText(mostra_imagem, ("a"), Point(0,20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,0,0), 1, 8, false );
			    	imshow("Adepois3", mostra_imagem);
			    	cvtColor(partes_mostra8, mostra_imagem, CV_GRAY2BGR);
			    	putText(mostra_imagem, ("b"), Point(0,20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,0,0), 1, 8, false );
			    	imshow("Bdepois3", mostra_imagem);
			    #endif	
		    
		    }

	    #endif
	  
	    
		    
		#ifdef ponderado   
		    num_channels = Lab.channels();
		    nRows = Lab.rows;
		    nCols = Lab.cols * num_channels;
		    for( i = 0; i < nRows; ++i)
		    {
		        p = Lab.ptr<uchar>(i);
		        p2 = dest->ptr<uchar>(i);
		        int k = 0;
		        for ( j = 0, k = 0; j < nCols; j+=3, k++){
		            p2[k] = Tabela[p[j]][p[j+1]][p[j+2]];
		        }
		    }
		    #ifdef mostra_partes
		    	if(vez == 1)
		    		imshow("combinacao",(*dest));
		    	else
		    		imshow("Combinacao",(*dest));
		    #endif
		#endif    
		    	
	}

	
	gettimeofday(&tempo2, NULL);
	tempo = (int) (1000000 * (tempo2.tv_sec - tempo1.tv_sec) + (tempo2.tv_usec - tempo1.tv_usec));
	if(atualiza && vez == 1){
		//cout<<"laranja: "<<tempo<<endl;
	}

}

#endif



#ifndef segmentacao


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
	blur(aux, aux2, Size(size_blur,size_blur));
	inRange( aux2 , Scalar(aceita_blur), Scalar(257), aux2);
	#ifdef usuario
		#ifdef mostra_range
			imshow("Regiao de Interesse", aux2);
		#endif
	#endif
	inRange( (*source) , Scalar(aceita_final), Scalar(257), aux3);
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

	imshow("Aceitos 1", (*source));

	
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

#endif


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
	size = (float)tamanho_mat;
	resize((*source), (*source), Size((int)(((float)size)*ratio), size ));

	
	#ifdef usuario
		#ifdef mostra_rangez
			imshow("Zoom", (*source));
		#endif
	#endif


	//blur((*source), (*source), Size(blur_x_i+1,blur_y_i+1 ));
	Laranja((*source), source,2);

	Mat aux2;
	Mat aux3;
	#ifdef usuario
		#ifdef mostra_rangez
			imshow("Laranja2", (*source) );
		#endif
	#endif
	
	inRange( (*source) , Scalar(min_aceitaz), Scalar(257), aux);
	#ifdef usuario
		#ifdef mostra_rangez
			//imshow("Range2", aux);
		#endif
	#endif
	blur(aux, aux2, Size(size_blurz,size_blurz));
	inRange( aux2 , Scalar(aceita_blurz), Scalar(257), aux2);
	#ifdef usuario
		#ifdef mostra_rangez
			//imshow("Regiao de Interesse2", aux2);
		#endif
	#endif
	inRange( (*source) , Scalar(aceita_finalz), Scalar(257), aux3);
	#ifdef usuario
		#ifdef mostra_rangez
			//imshow("Pontos novos2", aux3);
		#endif
	#endif
	bitwise_and(aux2,aux3, (*source));
	#ifdef usuario
		#ifdef mostra_rangez
			imshow("Aceitos 2", (*source));
		#endif
	#endif
	
	imshow("Aceitos 2", (*source));

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
	

	bool continuidade = false;

	bool achou;
	int nRows = mancha.rows;
	int nCols = mancha.cols;


	if(nCols>5 && nRows>5){
		uchar* p;
		uchar* p2;
		int i,j, k;
		Vector<Point> nuvem;
		Vec4f matriz(0,0,0,0);
		float num_pontos = 0;
		float sum_i = 0;
		float sum_j = 0;
		//coleta pontos da mancha	
		for(i = 0; i<nRows; i++){
			p = mancha.ptr<uchar>(i);
			for(j=0; j<nCols; j++){
				if(p[j] >120){
					nuvem.push_back(Point(j,i));
					num_pontos++;
					sum_i += i;
					sum_j += j;
				}
			}
		}
		//obtém matriz de rotação da mancha
		float centro_i = sum_i/num_pontos;
		float centro_j = sum_j/num_pontos;
		int nSize = nuvem.size();
		float min_y = 500000;
		float max_y = -5000000;
		float min_x = 50000000;
		float max_x = -500000000;
		for(i = 0; i<nSize; i++){
			nuvem[i].x -= centro_j;	
			nuvem[i].y -= centro_i;
			matriz[0] += nuvem[i].x*nuvem[i].x;
			matriz[1] += nuvem[i].x*nuvem[i].y;
			matriz[3] += nuvem[i].y*nuvem[i].y;
		}
		Mat inercia(2,2,CV_32FC1);
		inercia.at<float>(Point(0,0)) = matriz[0]/nSize;
		inercia.at<float>(Point(0,1)) = matriz[1]/nSize;
		inercia.at<float>(Point(1,0)) = inercia.at<float>(Point(0,1));
		inercia.at<float>(Point(1,1)) = matriz[3]/nSize;
		Mat autovetores(2,2,CV_32FC1);
		Mat autovalores(2,1,CV_32FC1);
		eigen(inercia,autovalores, autovetores);	
		Mat rotacao = autovetores.inv();
		//imshow("Mancha", mancha);

		//rotaciona mancha
		Vector<Point> nuvem_nova;
		for(i = 0; i<nSize; i++){
			sum_i = rotacao.at<float>(Point(0,0))*nuvem[i].x + rotacao.at<float>(Point(0,1))*nuvem[i].y ;
			sum_j = rotacao.at<float>(Point(1,0))*nuvem[i].x + rotacao.at<float>(Point(1,1))*nuvem[i].y ;
			nuvem_nova.push_back(Point(sum_j,sum_i));
		}
		min_y = 500000;
		max_y = -5000000;
		min_x = 50000000;
		max_x = -500000000;
		nSize = nuvem_nova.size();

		//obtém limites da mancha
		for(i = 0; i<nSize; i++){
			if(nuvem_nova[i].y < min_y)
				min_y = nuvem_nova[i].y;
			if(nuvem_nova[i].y > max_y)
				max_y = nuvem_nova[i].y;
			if(nuvem_nova[i].x < min_x)
				min_x = nuvem_nova[i].x;
			if(nuvem_nova[i].x > max_x)
				max_x = nuvem_nova[i].x;
		}
		int tamanho_x = max_x - min_x + 1;
		int tamanho_y = max_y - min_y + 1;
		int meio_x = tamanho_x/2;
		int meio_y = tamanho_y/2;

		//posiciona pontos dentro do frame
		for(i = 0; i<nSize; i++){
			nuvem_nova[i].x -= min_x;
			nuvem_nova[i].y -= min_y;
		}

		//imagem com a mancha no canto
		for(i = 0; i<nSize; i++){
			
			if(nuvem_nova[i].x > meio_x )
				nuvem_nova.push_back(Point(nuvem_nova[i].x-1,nuvem_nova[i].y));
			else
				nuvem_nova.push_back(Point(nuvem_nova[i].x+1,nuvem_nova[i].y));
		}
		Mat mostra(tamanho_y, tamanho_x, CV_8UC1);
		mostra = Scalar(0);
		for(i = 0; i<2*nSize; i++){
			mostra.at<uchar>(Point(nuvem_nova[i].x,nuvem_nova[i].y)) = 255;
		}
		//imshow("Mostra", mostra);
		

		//verifica se a mancha caracteriza um cone

		int limE[tamanho_y];
		int limD[tamanho_y];

		vector<Point> esquerda;
		vector<Point> direita;
		Point ponto;

		Mat borda(tamanho_y, tamanho_x, CV_8UC1);
		borda = Scalar(0);
		float sumE = 0;
		float sumD = 0;
		float mediaE, mediaD;
		float aumentaE = 0;
		float aumentaD = 0;
		float difE = 0;
		float difD = 0;
		for(i = 0.1*tamanho_y; i<0.8*tamanho_y; i++){
			achou = false;
			j=0;
			p = mostra.ptr<uchar>(i);
			p2 = borda.ptr<uchar>(i);
			while(!achou && j<tamanho_x){
				if(p[j] > 200){
					achou = true;
				}
				else{
					j++;
				}
			}
			ponto.y = i;
			ponto.x = j;
			esquerda.push_back(ponto);
			limE[i] = j;
			sumE += j;
			p2[j] = 255;

			k = tamanho_x -1;
			achou = false;
			while(!achou && k>=j){
				if(p[k] > 200){
					achou = true;
				}
				else{
					k--;
				}
			}
			ponto.y = i;
			ponto.x = k;
			direita.push_back(ponto);
			limD[i] = k;
			sumD += k;
			p2[k] = 255;
			
		}
		//imshow("BORDA", borda);


		float a1,a2,b1,b2;
		Point pontoL[2];
		Mat lms;
		cvtColor(borda, lms, CV_GRAY2BGR);
		Vec4f linhaLMS;
		fitLine(esquerda, linhaLMS, CV_DIST_L2, 0, 0.01, 0.01);
		pontoL[0].y = 0;
		pontoL[0].x = (int)(linhaLMS[2] + ((pontoL[0].y-linhaLMS[3])*(linhaLMS[0]/linhaLMS[1]))   );
		pontoL[1].y = borda.rows - 1;
		pontoL[1].x = (int)(linhaLMS[2] + ((pontoL[1].y-linhaLMS[3])*(linhaLMS[0]/linhaLMS[1]))   );
		a1 = pontoL[0].x;
		b1 = pontoL[1].x;
		line(lms, pontoL[0], pontoL[1], Scalar(0,255,0), 1, CV_AA);
		fitLine(direita, linhaLMS, CV_DIST_L2, 0, 0.01, 0.01);
		pontoL[0].y = 0;
		pontoL[0].x = (int)(linhaLMS[2] + ((pontoL[0].y-linhaLMS[3])*(linhaLMS[0]/linhaLMS[1]))   );
		pontoL[1].y = borda.rows - 1;
		pontoL[1].x = (int)(linhaLMS[2] + ((pontoL[1].y-linhaLMS[3])*(linhaLMS[0]/linhaLMS[1]))   );
		a2 = pontoL[0].x;
		b2 = pontoL[1].x;
		line(lms, pontoL[0], pontoL[1], Scalar(0,255,0), 1, CV_AA);
		if( (a2-a1)*1.2<(b2-b1) )
		{
			circle(lms,Point( (b2+b1)/2,(pontoL[1].y+pontoL[0].y)/2),5,Scalar(255,0,0));
			continuidade = true;
		}
		//imshow("LMS", lms);
	}	


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
		//num.clear();
		//int_to_string(i,&num);
		//imshow(num,manchas[i]);
		if(dados_mancha(manchas[i],8)){
			limites.push_back(posicoes[i]);
			//line( (*source), Point(posicoes[i][0],posicoes[i][1]), Point(posicoes[i][2],posicoes[i][1]), Scalar(0,0,255), 1, 8);
			//line( (*source), Point(posicoes[i][2],posicoes[i][1]), Point(posicoes[i][2],posicoes[i][3]), Scalar(0,0,255), 1, 8);
			//line( (*source), Point(posicoes[i][2],posicoes[i][3]), Point(posicoes[i][0],posicoes[i][3]), Scalar(0,0,255), 1, 8);
			//line( (*source), Point(posicoes[i][0],posicoes[i][3]), Point(posicoes[i][0],posicoes[i][1]), Scalar(0,0,255), 1, 8);			
		}
	}
	num.clear();
	int_to_string(num_area, &num);
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
		quadrado_x = (float)area[0] - (float)4*delta;
		if(quadrado_x < 0){
			quadrado_x = 0;
		}	
		quadrado_d = (float)area[2] + (float)4*delta;
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
	#ifdef usuario
	imshow("SOURCE", (*temp));
	#endif

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
				encontrou_cone = true;
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

	if(encontrou_cone){
		min_valido = true;
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

Segmento::Segmento()
{
	num_pontos = 0;
}

void Segmento::calc_centro()
{
	if(num_pontos > 0)
	{
		int i;
		int x = 0;
		int y = 0;
		for(i=0;i<num_pontos;i++)
		{
			x+=pontos[i].x;
			y+=pontos[i].y;
		}
		centro.x = x/num_pontos;
		centro.y = y/num_pontos;
	}
}

void Segmento::addPoint(Point ponto)
{
	pontos.push_back(ponto);
	num_pontos++;
}
void Segmento::addVector(vector<Point> novos_pontos)
{
	for(int i = 0; i<novos_pontos.size();i++)
	{
		pontos.push_back(novos_pontos[i]);
	}
	num_pontos+=novos_pontos.size();
}

void Segmento::limites()
{
	int max_x = -1;
	int max_y = -1;
	int min_x = 9999999;
	int min_y = 9999999;
	for(int i=0; i<pontos.size(); i++)
	{
		if(pontos[i].x > max_x)
		{
			max_x = pontos[i].x;
		}
		if(pontos[i].x < min_x)
		{
			min_x = pontos[i].x;
		}
		if(pontos[i].y > max_y)
		{
			max_y = pontos[i].y;
		}
		if(pontos[i].y < max_y)
		{
			min_y = pontos[i].y;
		}
	}
	inicio.x = min_x;
	inicio.y = min_y;
	fim.x = max_x;
	fim.y = max_y;
}

void Segmento::rotate()
{
	int i;
	rotated.clear();
	Point aux;
	Vec4f matriz(0,0,0,0);
	
	//centraliza pontos na origem
	for(i = 0; i<num_pontos; i++){
		aux.x = pontos[i].x - centro.x;
		aux.y = pontos[i].y - centro.y;
		rotated.push_back(aux);
		matriz[0] += aux.x*aux.x;
		matriz[1] += aux.x*aux.y;
		matriz[3] += aux.y*aux.y;
	}

	//obtem matriz de rotação
	Mat inercia(2,2,CV_32FC1);
	inercia.at<float>(Point(0,0)) = matriz[0]/num_pontos;
	inercia.at<float>(Point(0,1)) = matriz[1]/num_pontos;
	inercia.at<float>(Point(1,0)) = inercia.at<float>(Point(0,1));
	inercia.at<float>(Point(1,1)) = matriz[3]/num_pontos;
	Mat autovetores(2,2,CV_32FC1);
	Mat autovalores(2,1,CV_32FC1);
	eigen(inercia,autovalores, autovetores);	
	Mat rotacao = autovetores.inv();



	int max_x = -1;
	int max_y = -1;
	int min_x = 9999999;
	int min_y = 9999999;
	//rotaciona pontos
	int x,y;
	for(i = 0; i<num_pontos; i++){
		y = rotacao.at<float>(Point(0,0))*rotated[i].x + rotacao.at<float>(Point(0,1))*rotated[i].y ;
		x = rotacao.at<float>(Point(1,0))*rotated[i].x + rotacao.at<float>(Point(1,1))*rotated[i].y ;
		rotated[i] = Point(x,y);
		if(rotated[i].x > max_x)
		{
			max_x = rotated[i].x;
		}
		if(rotated[i].x < min_x)
		{
			min_x = rotated[i].x;
		}
		if(rotated[i].y > max_y)
		{
			max_y = rotated[i].y;
		}
		if(rotated[i].y < max_y)
		{
			min_y = rotated[i].y;
		}
	}
	altura = max_y-min_y+1;
	largura = max_x-min_x+1;
	canto.x = min_x;
	canto.y = min_y;
	
}

void Segmento::bordas()
{
	esquerda.clear();
	esquerda.resize(altura);
	direita.clear();
	direita.resize(altura);
	int i;
	for(int i = 0; i<altura;i++)
	{
		esquerda[i].y = canto.y+i;
		direita[i].y = canto.y+i;
		esquerda[i].x = largura; 
		direita[i].x = -largura;
	}
	for(i=0;i<num_pontos;i++)
	{
		if(rotated[i].x < esquerda[rotated[i].y-canto.y].x)
		{
			esquerda[rotated[i].y-canto.y].x = rotated[i].x;
		}

		if(rotated[i].x > direita[rotated[i].y-canto.y].x)
		{
			direita[rotated[i].y-canto.y].x = rotated[i].x;
		}
	}
}
