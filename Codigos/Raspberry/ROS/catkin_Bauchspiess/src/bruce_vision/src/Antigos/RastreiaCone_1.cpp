#include "RastreiaCone.hpp"




RastreiaCone::RastreiaCone(){

	

	delta = 0.1;

	/*
	subidaL = 0;
	step1_L = 0;
	altoL = 90;
	descidaL = 140;
	step2_L = 0;
	baixoL = 256;

	subidaA = 125;
	step1_A = 0;
	altoA = 145;
	descidaA = 160;
	step2_A = 0;
	baixoA = 180;

	subidaB = 140;
	step1_B = 0;
	altoB = 155;
	descidaB = 175;
	step2_B = 0;
	baixoB = 190;
	*/

	/*
	minL = 50;
	maxL = 256;
	minB = 5;
	maxB = 70;
	minG = 40;
	maxG = 90;
	minR = 100;
	maxR = 200;

	minLo = 40;
	maxLo = 200;
	minBo = 20;
	maxBo = 45;
	minGo = 65;
	maxGo = 73;
	minRo = 140;
	maxRo = 165;
	*/

	//copo
	/*
	minL = 50;
	maxL = 256;
	minB = 10;
	maxB = 240;
	minG = 130;
	maxG = 210;
	minR = 130;
	maxR = 205;

	minLo = 40;
	maxLo = 200;
	minBo = 50;
	maxBo = 180;
	minGo = 155;
	maxGo = 180;
	minRo = 155;
	maxRo = 185;
	*/


	//cone
	
	minL = 50;
	maxL = 256;
	minB = 10;
	maxB = 240;
	minG = 130;
	maxG = 175;
	minR = 130;
	maxR = 180;

	minLo = 40;
	maxLo = 200;
	minBo = 50;
	maxBo = 180;
	minGo = 135;
	maxGo = 155;
	minRo = 140;
	maxRo = 165;

	sizeCanny = 0;

	minCanny = 30;
	maxCanny = 60;


	aceita_final = 200;
	min_aceita = 250;

	dif_pixel = 15;
	dif_centroide = 140;
	max_dif_pixel = 15;
	max_dif_centroide = 140;

	max_dif_pixelL = 8;
	max_dif_centroideL = 80;


	min_segment_size = 50;

	//PreencheTabela();

	atualiza = true;

	tamanho_final = 480;
	tamanho0 = 480;

	PreencheTabela();


	filtro = false;
	#ifdef filmar
	video_init = false;
	#endif
}



#ifdef segmentacao


void RastreiaCone::PreencheTabela(){

	cout<<"atualizando"<<endl;

	int i, j, k;
	float incremento;
	float valor;

	//Filtro da Luminancia
	for(i = 0; i<minB; i++){
		L[i] = 0;
	}
	//incremento = (1.0- (((float)aceita_final)/255) )/(float)(minBo - minB);
	//valor = aceita_final;
	incremento = (1.0 )/(float)(minBo - minB);
	valor = 0;
	
	for( i = minB; i<minBo; i++){
		valor += incremento;
		L[i] = valor;
	}
	for(i = minBo ; i<maxBo; i++){
		L[i] = 1;
	}
	valor = 1;
	//incremento = (1.0-(((float)aceita_final)/255) )/(float)(maxBo - maxB);
	incremento = (1.0 )/(float)(maxBo - maxB);
	for(i = maxBo; i<maxB; i++){
		valor += incremento;
		L[i] = valor;
	}
	for(i = maxB; i<256; i++){
		L[i] = 0;
	}




	
	//Filtro da Saturação
	for(i = 0; i<minG; i++){
		A[i] = 0;
	}
	//incremento = (1.0-(((float)aceita_final)/255) )/(float)(minGo - minG);
	//valor = aceita_final;
	incremento = (1.0 )/(float)(minGo - minG);
	valor = 0;
	
	for( i = minG; i<minGo; i++){
		valor += incremento;
		A[i] = valor;
	}
	for(i = minGo ; i<maxGo; i++){
		A[i] = 1;
	}
	valor = 1;
	//incremento = (1.0 -(((float)aceita_final)/255) )/(float)(maxGo - maxG);
	incremento = (1.0 )/(float)(maxGo - maxG);
	for(i = maxGo; i<maxG; i++){
		valor += incremento;
		A[i] = valor;
	}
	for(i = maxG; i<256; i++){
		A[i] = 0;
	}
	

	//Filtro do Value
	for(i = 0; i<minR; i++){
		B[i] = 0;
	}
	//incremento = (1.0 -(((float)aceita_final)/255) )/(float)(minRo - minR);
	//valor = aceita_final;
	incremento = (1.0  )/(float)(minRo - minR);
	valor = 0;
	
	for( i = minR; i<minRo; i++){
		valor += incremento;
		B[i] = valor;
	}
	for(i = minRo ; i<maxRo; i++){
		B[i] = 1;
	}
	valor = 1;
	//incremento = (1.0 -(((float)aceita_final)/255) )/(float)(maxRo - maxR);
	incremento = (1.0 )/(float)(maxRo - maxR);
	if(baixoB > 256)
		baixoB = 256;
	for(i = maxRo; i<maxR; i++){
		valor += incremento;
		B[i] = valor;
	}
	for(i = maxR; i<256; i++){
		B[i] = 0;
	}

	
	for(k = 0; k<256; k++){
		for(i = 0; i<256; i++){
			for(j = 0; j<256; j++){
				Tabela[i][j][k] = (uchar) 255*L[i]*A[j]*B[k];
			}
		}
	}



/*
	
	int i, j, k;
	float incremento;
	float valor;

	//Filtro da Luminancia
	for(i = 0; i<subidaL; i++){
		L[i] = 0;
	}
	incremento = (1.0-(float)((float)step1_L/100.0) )/(float)(altoL - subidaL);
	valor = (float)((float)step1_L/100.0);
	for( i = subidaL; i<altoL; i++){
		valor += incremento;
		L[i] = valor;
	}
	for(i = altoL ; i<descidaL; i++){
		L[i] = 1;
	}
	valor = 1;
	incremento = (1.0-(float)((float)step2_L/100.0) )/(float)(descidaL - baixoL);
	for(i = descidaL; i<baixoL; i++){
		valor += incremento;
		L[i] = valor;
	}
	for(i = baixoL; i<subidaL; i++){
		L[i] = 0;
	}




	
	//Filtro da Saturação
	for(i = 0; i<subidaA; i++){
		A[i] = 0;
	}
	incremento = (1.0-(float)((float)step1_A/100.0) )/(float)(altoA - subidaA);
	valor = (float)((float)step1_A/100.0);
	for( i = subidaA; i<altoA; i++){
		valor += incremento;
		A[i] = valor;
	}
	for(i = altoA ; i<descidaA; i++){
		A[i] = 1;
	}
	valor = 1;
	incremento = (1.0-(float)((float)step2_A/100.0) )/(float)(descidaA - baixoA);
	if(baixoA > 256)
		baixoA = 256;
	for(i = descidaA; i<baixoA; i++){
		valor += incremento;
		A[i] = valor;
	}
	for(i = baixoA; i<256; i++){
		A[i] = 0;
	}
	

	//Filtro do Value
	for(i = 0; i<subidaB; i++){
		B[i] = 0;
	}
	incremento = (1.0-(float)((float)step1_B/100.0) )/(float)(altoB - subidaB);
	valor = (float)((float)step1_B/100.0);
	for( i = subidaB; i<altoB; i++){
		valor += incremento;
		B[i] = valor;
	}
	for(i = altoB ; i<descidaB; i++){
		B[i] = 1;
	}
	valor = 1;
	incremento = (1.0-(float)((float)step2_B/100.0) )/(float)(descidaB - baixoB);
	if(baixoB > 256)
		baixoB = 256;
	for(i = descidaB; i<baixoB; i++){
		valor += incremento;
		B[i] = valor;
	}
	for(i = baixoB; i<256; i++){
		B[i] = 0;
	}

	
	for(k = 0; k<256; k++){
		for(i = 0; i<256; i++){
			for(j = 0; j<256; j++){
				Tabela[i][j][k] = (uchar) 255*L[i]*A[j]*B[k];
			}
		}
	}
	

	/*
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
	*/

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

void RastreiaCone::Luminosidade(Mat* source)
{
	//Equaliza canal L
	vector<Mat> channels;
	split((*source),channels);
	equalizeHist(channels[0],channels[0]);
	merge(channels,(*source));
}


void RastreiaCone::Normaliza(Mat src,Mat* dst )
{
	int nCols = src.cols;
	int nRows = src.rows;
	int i,j,k,l;

	int sum;
	float ratio;

	uchar *p, *p2;


	Mat aux(nRows,nCols,CV_8UC1);
	uchar *p3;

	(*dst).create(nRows,nCols,CV_8UC4);


	for(i=0;i<nRows;i++)
	{
		p=src.ptr<uchar>(i);
		p2=dst->ptr<uchar>(i);

		p3=aux.ptr<uchar>(i);
		for(j=0,k=0,l=0;j<nCols;j++,k+=3,l+=4)
		{

			//p3[j] = min(p[k],min(p[k+1],p[k+2]));
			sum = (p[k]+p[k+1]+p[k+2]);
			ratio = 255/(float)sum;
			p2[l+3] = sum/3;
			p2[l] = (int)(ratio*(float)p[k]);
			p2[l+1] = (int)(ratio*(float)p[k+1]);
			p2[l+2] = (int)(ratio*(float)p[k+2]);

			//p[k] = p2[l];
			//p[k+1] = p2[l+1];
			//p[k+2] = p2[l+2];

		}

	}
	//imshow("min",aux);

}


void RastreiaCone::Segmenta(Mat src, Mat aux)
{  
	
	Mat aux2;
	imshow("src",src);
	Canny(src,aux2,30,90,3);
	imshow("cannyLab", aux2);
	vector<Mat> channels;
	split(src,channels);
	Canny(channels[0],aux2,30,90,3);
	imshow("L",channels[0]);
	equalizeHist(channels[0],channels[0]);
	imshow("Leq",channels[0]);
	imshow("cannyL",aux2);
	Canny(channels[1],aux2,30,90,3);
	imshow("A",channels[1]);
	equalizeHist(channels[1],channels[1]);
	imshow("Aeq",channels[1]);
	imshow("cannyA",aux2);
	Canny(channels[2],aux2,30,90,3);
	imshow("B",channels[2]);
	equalizeHist(channels[2],channels[2]);
	imshow("Beq",channels[2]);
	imshow("cannyB",aux2);







	/*
	vector<Segmento> segmentos;
	Segmento segmento;
	Point ponto;
	Mat ref(src.size(),CV_8UC1);
	ref = Scalar(255);
	int i,j,k,l,m,x,y;
	int avx,avy,cont;
	uchar L,a,b,L2,a2,b2;
	uchar *p,*p2;
	int nRows = src.rows;
	int nCols = src.cols;
	Point lados[4] = {Point(-1,0),Point(0,-1),Point(1,0),Point(0,1)};
	for( i = 0; i < nRows; ++i)
	{
		p = src.ptr<uchar>(i);
		p2 = ref.ptr<uchar>(i);
		for ( j = 0, k = 0; k < nCols; j+=3, k++){
			if(p2[k]>120 )
			{
				if(Tabela[p[j]][p[j+1]][p[j+2]] > min_aceita)//encontrou ponto otimo
				{
					segmento.clear();
					ponto = Point(k,i);
					segmento.addPoint(ponto);
					ref.at<uchar>(Point(k,i)) = 0;
					segmento.cor_centro[0] = p[j];
					segmento.cor_centro[1] = p[j+1];
					segmento.cor_centro[2] = p[j+2];
					avx = k;
					avy = i;
					l=0;
					while(l<segmento.num_pontos)
					{
						a = src.at<Vec3b>(segmento.pontos[l])[1];
						b = src.at<Vec3b>(segmento.pontos[l])[2];
						for(m=0;m<4;m++)
						{
							x=segmento.pontos[l].x+lados[m].x;
							y=segmento.pontos[l].y+lados[m].y;
							//ponto dentro da matriz
							if(x>=0&&x<nCols&&y>=0&&y<=nRows&&ref.at<uchar>(Point(x,y))>120)
							{
								
								if(Tabela[p[j]][p[j+1]][p[j+2]] > aceita_final && abs(a-src.at<Vec3b>(Point(x,y))[1])<dif_pixel && abs(b-src.at<Vec3b>(Point(x,y))[2])<dif_pixel 
									&& abs(segmento.cor_centro[1]-src.at<Vec3b>(Point(x,y))[1])<dif_centroide && abs(segmento.cor_centro[2]-src.at<Vec3b>(Point(x,y))[2])<dif_centroide)
								//if(Tabela[p[j]][p[j+1]][p[j+2]] > aceita_final)
								{
									ref.at<uchar>(Point(x,y)) = 0;
									ponto = Point(x,y);
									
									segmento.cor_centro[1] = (uchar)( (float)(segmento.num_pontos*segmento.cor_centro[1])/(float)(segmento.num_pontos+1)+((float)src.at<Vec3b>(Point(x,y))[1])/(float)(segmento.num_pontos+1) );
									segmento.cor_centro[2] = (uchar)( (float)(segmento.num_pontos*segmento.cor_centro[2])/(float)(segmento.num_pontos+1)+((float)src.at<Vec3b>(Point(x,y))[2])/(float)(segmento.num_pontos+1) );

									segmento.addPoint(ponto);

									avx+=x;
									avy+=y;
								}
								else if(Tabela[p[j]][p[j+1]][p[j+2]] <= aceita_final)
								{
									ref.at<uchar>(Point(x,y)) = 0;
								}
							}
						}
						l++;
					}
					segmento.centro = Point(avx/segmento.num_pontos,avy/segmento.num_pontos);
					segmentos.push_back(segmento);
				}
			}
		}
	}
	k = 0;
	for(i=0;i<segmentos.size();i++)
	{
		if(segmentos[i].num_pontos>1000)
		{
			k+=50;
			if(k>255)
				k=0;
			for(j=0;j<segmentos[i].num_pontos;j++)
			{
				aux.at<Vec3b>(segmentos[i].pontos[j])[0] = k;
				aux.at<Vec3b>(segmentos[i].pontos[j])[1] = k;
				aux.at<Vec3b>(segmentos[i].pontos[j])[2] = k;
			}
		}
	}
	imshow("segmento",aux);
	*/
}


//versao problematica, ir para o modo easy
/*
void RastreiaCone::segmentaNorm(Mat src, Mat thresh)
{
	Mat corID(src.size(),CV_8UC1);
	//Mat id(src.size(),CV_32FC1);
	int id[src.rows][src.cols];
	//id = Scalar(0);
	vector<int> ID;
	ID.push_back(0);
	int cont = 1;
	vector<Segmento> segmentos;
	Segmento segmento;
	segmentos.push_back(segmento); 
	vector<int> ref;


	int c = src.channels();


	int nRows = src.rows;
	int nCols = src.cols;


	int i, j_src, j_id; 
	int k,l, n;
	uchar *p_src, *p;
	float *p_id; 
	float *point;
	//float *p2;

	int num = 4;
	Point dir[4] = {Point(-1,0),Point(-1,-1),Point(0,-1),Point(1,-1)};
	int difp[num];
	int difc[num];
	int maxdifp[num];
	int maxdifc[num];

	int dif;

	vector<uchar> cor(c);
	Point ponto;


	int x,y;

	vector<int> bons;

	for(i=0;i<nRows;i++)
	{
		for(k=0;k<nCols;k++)
		{
			id[i][k] = 0;
		}
	}




	for(i=0;i<nRows;i++)
	{
		p_src = src.ptr<uchar>(i);
		//p_id = id.ptr<float>(i);
		for(j_src = 0, j_id = 0; j_id<nCols; j_id++, j_src+=c)
		{
			//Verifica threshold
			if(  (p_src[j_src]>minB)&&(p_src[j_src]<maxB)&&(p_src[j_src+1]>minG)&&(p_src[j_src+1]<maxG)&&(p_src[j_src+2]>minR)&&(p_src[j_src+2]<maxR)&&(p_src[j_src+3]>minL)&&(p_src[j_src+3]<maxL) )
			{
				
				//calcula diferenças com cada segmento adjacente
				for(l=0;l<c;l++)
				{
					cor[l] = p_src[j_src+l];
				}

				bons.clear();
				//cout<<"aqui"<<endl;
				for(k=0;k<num;k++)
				{
					//cout<<k<<"  ";
					x=j_id+dir[k].x;
					y=i+dir[k].y;
					
					if(x>=0&&x<nCols&&y>=0&&y<nRows)
					{
						
						difp[k] = 0;
						difc[k] = 0;
						maxdifp[k] = 0;
						maxdifc[k] = 0;


						n = ID[id[y][x]];
						
						if(n>0)
						{
							p = src.ptr<uchar>(y);
							x*=3;	 

						
							for(l=0;l<c;l++)
							{
								
								//diferença entre pixeis
								dif = abs(cor[l]-p[x+l]);
								difp[k] += dif;
								if(dif>maxdifp[k])
								{
									maxdifp[k] = dif;
								}

								//diferença para centroide
								dif = abs(cor[l]-segmentos[n].avg_cor[l]);
								
								difc[k] += dif;
								if(dif>maxdifc[k])
								{
									maxdifc[k] = dif;
								}
								
							}						
							if(maxdifc[k]<dif_centroide && maxdifp[k]<dif_pixel)
							{
								bons.push_back(k);
							}
							
								
						}
						
								
					}			
					else
					{
						difp[k] = 9999;
						difc[k] = 9999;
						maxdifp[k] = 9999;
						maxdifc[k] = 9999;
					}
				}
				//cout<<endl;
				
				//define a qual segmento anexar, se unir segmentos ou se criar segmento novo
				if(bons.size() == 0)
				{					
					segmento.clear();
					ponto.x = j_id;
					ponto.y = i;
					segmento.addPoint(ponto,cor);
					id[i][j_id] = segmentos.size();
					segmentos.push_back(segmento);
					//cout<<segmentos.size()<<endl;
				}
				
				else //if(bons.size() == 1)
				{
					y = i+dir[bons[0]].x;
					x = j_id+dir[bons[0]].y;
					p2 = id.ptr<float>(y);
					n = ID[(int)p2[x]];
					p_id[j_id] = n;
					ponto.x = j_id;
					ponto.y = i;
					segmentos[n].addPoint(ponto,cor);
				}
				
				
				else
				{

				}
				
			}
		} 
	}
}
*/

void RastreiaCone::segmentaNorm(Mat src, Mat thresh)
{


	
	//vector<Segmento> segmentos;
	
	Segmento segmento;
	Point ponto;
	vector<uchar> cor;


	int nRows = src.rows;
	int nCols = src.cols;
	int nCanais = src.channels();

	int avx,avy,cont;

	//indices
	int i,j,k,l,m,n;
	//posicao pixel
	int x,y,x2,y2; 
	int x3,x4;


	Mat ref(src.size(),CV_8UC1);
	ref = Scalar(255);

	int num_dir = 4;
	Point lados[4] = {Point(-1,0),Point(0,-1),Point(1,0),Point(0,1)};
	uchar *p,*p2, *p3, *p4;
	uchar* paux;


	float difP, difC, maxdifP, maxdifC, dif;
	float ratio_lux = 2.0; 


	for(i=0;i<nRows;i++)
	{
		p=src.ptr<uchar>(i);
		//p2 = ref.ptr<uchar>(i);
		p3 = thresh.ptr<uchar>(i);
		for(j=0,k=0;j<nCols;j++,k+=nCanais)
		{
			if( p3[j] > 200)
			{
				segmento.clear();
				ponto = Point(j,i);
				cor.clear();
				for(l=0;l<nCanais;l++)
				{
					cor.push_back(p[k+l]);
				}
				segmento.addPoint(ponto,cor);
				ref.at<uchar>(Point(j,i)) = 0;
				l=0;
				while(l<segmento.num_pontos)
				{
					//posicao do ponto pertencente ao segmento
					x = segmento.pontos[l].x;
					y = segmento.pontos[l].y;
					p4 = src.ptr<uchar>(y);
					x4 = x*nCanais;
					for(m=0;m<num_dir;m++)
					{
						//posicao do novo ponto
						x2 = x+lados[m].x;
						y2 = y+lados[m].y;
						x3 = x2*nCanais;
						p2 = src.ptr<uchar>(y2);
						//ponto dentro da imagem
						if(x2>=0&&y2>=0&&x2<nCols&&y2<nRows)
						{
							//ponto bom ainda nao incluido em um segmento
							if(thresh.at<uchar>(Point(x2,y2)) > 100)
							{
								//calcula diferenca do pixel novo para o segmento e o pixel adjacente do segmento
								maxdifC = 0;
								maxdifP = 0;
								difP = 0;
								difC = 0;
								for(n=0;n<nCanais-1;n++)
								{

									dif=abs(p4[x4+n]-p2[x3+n]);
									difP+=dif;
									if(dif>maxdifP)
									{
										maxdifP = dif;
									}

									dif=abs(segmento.avg_cor[n]-p2[x3+n]);
									difC+=dif;
									if(dif>maxdifC)
									{
										maxdifC = dif;
									} 
								}
								//checa se cor do pixel é suficientemente semelhante
								if(maxdifC<max_dif_centroide && maxdifP<max_dif_pixel && difP < dif_pixel && difC < dif_centroide)
								{
									//checa diferença de luminosidade
									difP = abs(p4[x4+nCanais-1] - p2[x3+nCanais-1]);
									difC = abs(segmento.avg_cor[nCanais-1] - p2[x3+nCanais-1]);
									if(difC<max_dif_centroideL && difP<(float)max_dif_pixelL)
									{
										//retira ponto da imagem de thresh, esse ponto não poderá ser incluído em outros
										thresh.at<uchar>(Point(x2,y2)) = 0;
										//adiciona pixel ao segmento

										cor.clear();
										for(n=0;n<nCanais;n++){
											cor.push_back(p2[x3+n]);
										}
										segmento.addPoint(Point(x2,y2),cor);
									}
								}

							}
							else
							{
								ref.at<uchar>(Point(x2,y2)) = 0;
							}
						}
					}

					l++;

				}

				if(segmento.num_pontos > min_segment_size)
				{
					objetos.push_back(segmento);
				}

			}
		}
	}
	
	Mat mostra(src.size(),CV_8UC3);
	mostra = Scalar(0,0,0);
	vector<Vec3b> Cor;
	Vec3b corseg;
	for(i=50;i<255;i+=50){
		for(j=0;j<255;j+=50){
			for(k=0;k<255;k+=50){
				corseg[0] = i;
				corseg[1] = j;
				corseg[2] = k; 
				Cor.push_back(corseg);
			}
		}
	}
	for(i=0;i<objetos.size();i++)
	{
		for(j=0;j<objetos[i].num_pontos;j++)
		{
			mostra.at<Vec3b>(objetos[i].pontos[j])[0] = Cor[i][0];
			mostra.at<Vec3b>(objetos[i].pontos[j])[1] = Cor[i][1];
			mostra.at<Vec3b>(objetos[i].pontos[j])[2] = Cor[i][2];
		}
	}

	imshow("mostra",mostra);
	
}



void RastreiaCone::segmentaBGR(Mat src, Mat thresh)
{


	
	//vector<Segmento> segmentos;
	
	Segmento segmento;
	Point ponto;
	vector<uchar> cor;


	int nRows = src.rows;
	int nCols = src.cols;
	int nCanais = src.channels();

	int avx,avy,cont;

	//indices
	int i,j,k,l,m,n;
	//posicao pixel
	int x,y,x2,y2; 
	int x3,x4;


	Mat ref(src.size(),CV_8UC1);
	ref = Scalar(255);

	int num_dir = 4;
	Point lados[4] = {Point(-1,0),Point(0,-1),Point(1,0),Point(0,1)};
	uchar *p,*p2, *p3, *p4;
	uchar* paux;


	float difP, difC, maxdifP, maxdifC, dif;
	float ratio_lux = 2.0; 


	for(i=0;i<nRows;i++)
	{
		p=src.ptr<uchar>(i);
		//p2 = ref.ptr<uchar>(i);
		p3 = thresh.ptr<uchar>(i);
		for(j=0,k=0;j<nCols;j++,k+=nCanais)
		{
			if( p3[j] > 200)
			{
				segmento.clear();
				ponto = Point(j,i);
				cor.clear();
				for(l=0;l<nCanais;l++)
				{
					cor.push_back(p[k+l]);
				}
				segmento.addPoint(ponto,cor);
				ref.at<uchar>(Point(j,i)) = 0;
				l=0;
				while(l<segmento.num_pontos)
				{
					//posicao do ponto pertencente ao segmento
					x = segmento.pontos[l].x;
					y = segmento.pontos[l].y;
					p4 = src.ptr<uchar>(y);
					x4 = x*nCanais;
					for(m=0;m<num_dir;m++)
					{
						//posicao do novo ponto
						x2 = x+lados[m].x;
						y2 = y+lados[m].y;
						x3 = x2*nCanais;
						p2 = src.ptr<uchar>(y2);
						//ponto dentro da imagem
						if(x2>=0&&y2>=0&&x2<nCols&&y2<nRows)
						{
							//ponto bom ainda nao incluido em um segmento
							if(thresh.at<uchar>(Point(x2,y2)) > 100)
							{
								//calcula diferenca do pixel novo para o segmento e o pixel adjacente do segmento
								maxdifC = 0;
								maxdifP = 0;
								difP = 0;
								difC = 0;
								for(n=0;n<nCanais;n++)
								{

									dif=abs(p4[x4+n]-p2[x3+n]);
									difP+=dif;
									if(dif>maxdifP)
									{
										maxdifP = dif;
									}

									dif=abs(segmento.avg_cor[n]-p2[x3+n]);
									difC+=dif;
									if(dif>maxdifC)
									{
										maxdifC = dif;
									} 
								}
								//checa se cor do pixel é suficientemente semelhante
								if(maxdifC<max_dif_centroide && maxdifP<max_dif_pixel && difP < dif_pixel && difC < dif_centroide)
								{
									//retira ponto da imagem de thresh, esse ponto não poderá ser incluído em outros
									thresh.at<uchar>(Point(x2,y2)) = 0;
									//adiciona pixel ao segmento

									cor.clear();
									for(n=0;n<nCanais;n++){
										cor.push_back(p2[x3+n]);
									}
									segmento.addPoint(Point(x2,y2),cor);
								}

							}
							else
							{
								ref.at<uchar>(Point(x2,y2)) = 0;
							}
						}
					}

					l++;

				}

				if(segmento.num_pontos > min_segment_size)
				{
					objetos.push_back(segmento);
				}

			}
		}
	}
	
	Mat mostra(src.size(),CV_8UC3);
	mostra = Scalar(0,0,0);
	vector<Vec3b> Cor;
	Vec3b corseg;
	for(i=50;i<255;i+=50){
		for(j=0;j<255;j+=50){
			for(k=0;k<255;k+=50){
				corseg[0] = i;
				corseg[1] = j;
				corseg[2] = k; 
				Cor.push_back(corseg);
			}
		}
	}
	for(i=0;i<objetos.size();i++)
	{
		for(j=0;j<objetos[i].num_pontos;j++)
		{
			mostra.at<Vec3b>(objetos[i].pontos[j])[0] = Cor[i][0];
			mostra.at<Vec3b>(objetos[i].pontos[j])[1] = Cor[i][1];
			mostra.at<Vec3b>(objetos[i].pontos[j])[2] = Cor[i][2];
		}
	}

	imshow("mostra",mostra);
	
}



void RastreiaCone::segmentaDif(Mat src, Mat thresh)
{

	//imshow("source",src);
	//imshow("thresh",thresh);
	
	//vector<Segmento> segmentos;
	

	Segmento segmento;
	Point ponto;
	vector<uchar> cor;


	int nRows = src.rows;
	int nCols = src.cols;
	int nCanais = src.channels();

	//cout<<nRows<<"   "<<nCols<<endl;
	int avx,avy,cont;

	//indices
	int i,j,k,l,m,n;
	//posicao pixel
	int x,y,x2,y2; 
	int x3,x4;


	//Mat ref(src.size(),CV_8UC1);
	//ref = Scalar(255);

	int num_dir = 4;
	Point lados[4] = {Point(-1,0),Point(0,-1),Point(1,0),Point(0,1)};
	uchar *p,*p2, *p3, *p4;
	uchar* paux;


	float difP, difC, maxdifP, maxdifC, dif;
	float ratio_lux = 2.0; 


	for(i=0;i<nRows;i++)
	{
		p=src.ptr<uchar>(i);
		//p2 = ref.ptr<uchar>(i);
		p3 = thresh.ptr<uchar>(i);
		for(j=0,k=0;j<nCols;j++,k+=nCanais)
		{
			if( p3[j] > min_aceita)
			{
				segmento.clear();
				ponto = Point(j,i);
				cor.clear();
				for(l=0;l<nCanais;l++)
				{
					cor.push_back(p[k+l]);
				}
				segmento.addPoint(ponto,cor);
				//cout<<"   "<<ponto<<"/"<<(int)cor[0];
				//ref.at<uchar>(Point(j,i)) = 0;
				l=0;
				while(l<segmento.num_pontos)
				{
					//posicao do ponto pertencente ao segmento
					x = segmento.pontos[l].x;
					y = segmento.pontos[l].y;
					p4 = src.ptr<uchar>(y);
					//cout<<"   "<<segmento.pontos[l]<<"/"<<(int)p4[x];
					x4 = x*nCanais;
					//cout<<"(";
					for(m=0;m<num_dir;m++)
					{
						//posicao do novo ponto
						x2 = x+lados[m].x;
						y2 = y+lados[m].y;
						x3 = x2*nCanais;
						p2 = src.ptr<uchar>(y2);
						//ponto dentro da imagem
						if(x2>=0&&y2>=0&&x2<nCols&&y2<nRows)
						{
							//ponto bom ainda nao incluido em um segmento
							if(thresh.at<uchar>(Point(x2,y2)) > aceita_final)
							{
								//calcula diferenca do pixel novo para o segmento e o pixel adjacente do segmento
								maxdifC = 0;
								maxdifP = 0;
								difP = 0;
								difC = 0;
								for(n=0;n<nCanais;n++)
								{

									/*
									if(p4[x4+n] >  p2[x3+n] )
									{
										dif = p4[x4+n]-p2[x3+n];
									}
									else
									{
										dif = p2[x3+n]-p4[x4+n];
									}									*/
									dif = abs((int)p4[x4+n]-(int)p2[x3+n]);
									//cout<<"("<<(int)p4[x4+n]<<","<<(int)p2[x3+n]<<")";
									difP+=dif;
									if(dif>maxdifP)
									{
										maxdifP = dif;
									}
									/*
									dif=abs(segmento.avg_cor[n]-p2[x3+n]);
									difC+=dif;
									if(dif>maxdifC)
									{
										maxdifC = dif;
									} 
									*/
								}
								//checa se cor do pixel é suficientemente semelhante
								//if(maxdifC<max_dif_centroide && maxdifP<max_dif_pixel && difP < dif_pixel && difC < dif_centroide)
								if( (maxdifP<max_dif_pixel) && (difP < dif_pixel) )
								{
									//retira ponto da imagem de thresh, esse ponto não poderá ser incluído em outros
									thresh.at<uchar>(Point(x2,y2)) = 0;
									//adiciona pixel ao segmento

									cor.clear();
									for(n=0;n<nCanais;n++){
										cor.push_back(p2[x3+n]);
									}
									segmento.addPoint(Point(x2,y2),cor);
								}

							}
							else
							{
								thresh.at<uchar>(Point(x2,y2)) = 0;
							}

							//cout<<difP<<",";

						}
					}
					//cout<<")";
					l++;

				}
				//cout<<endl;
				//cout<<"    "<<l<<endl;
				if(segmento.num_pontos > min_segment_size && segmento.ratio() > 0.5)
				//if(segmento.num_pontos > min_segment_size)	
				//if(true)
				{
					objetos.push_back(segmento);
				}

			}

		}
	}
	
	//cout<<"seg: "<<objetos.size()<<endl;


}



void RastreiaCone::DesenhaSeg(Mat* src)
{
	vector<Vec3b> Cor;
	Vec3b corseg;
	int i, j,k;
	for(i=50;i<255;i+=50){
		for(j=0;j<255;j+=50){
			for(k=0;k<255;k+=50){
				corseg[0] = i;
				corseg[1] = j;
				corseg[2] = k; 
				Cor.push_back(corseg);
			}
		}
	}
	for(i=0;i<objetos.size();i++)
	{
		for(j=0;j<objetos[i].num_pontos;j++)
		{
			src->at<Vec3b>(objetos[i].pontos[j]+objetos[i].canto)[0] = Cor[i][0];
			src->at<Vec3b>(objetos[i].pontos[j]+objetos[i].canto)[1] = Cor[i][1];
			src->at<Vec3b>(objetos[i].pontos[j]+objetos[i].canto)[2] = Cor[i][2];
		}
	}
}


int RastreiaCone::varredura0(Mat* source, Point inicio = Point(0,0)){
	/*
	Mat aux;
	Mat temp(source->size(),CV_8UC1); 
	Mat tempB(source->size(),CV_8UC1);
	Mat tempG(source->size(),CV_8UC1);
	Mat tempR(source->size(),CV_8UC1);

	uchar *p, *p2, *pB,*pG,*pR;

	Normaliza(*source,&aux);

	int i,j,k;
	int C = aux.channels();

	for(i=0;i<temp.rows;i++)
	{
		p = aux.ptr<uchar>(i);
		p2 = temp.ptr<uchar>(i);
		//pB = tempB.ptr<uchar>(i);
		//pG = tempG.ptr<uchar>(i);
		//pR = tempR.ptr<uchar>(i);
		for(j=0,k=0;j<temp.cols;j++,k+=C)
		{
			p2[j] = Tabela[p[k] ][p[k+1] ][p[k+2] ];
			//pB[j] = (255.0*L[p[k] ]);
			//pG[j] = (255*A[p[k+1] ]);
			//pR[j] = (255*B[p[k+2] ]);			
		}
	}
	/*
	imshow("B",tempB);
	imshow("G",tempG);
	imshow("R",tempR);
	imshow("combined",temp);
	

	inRange(temp,Scalar(min_aceita),Scalar(256),tempB);
	inRange(temp,Scalar(aceita_final),Scalar(256),tempG);
	imshow("otimo",tempB);
	imshow("bom",tempG);
	*/
	/*
	k = objetos.size();

	segmentaDif(*source,temp,k);

	for(i = k; i<objetos.size();i++)
	{
		objetos[i].inicio.x += inicio.x;
		objetos[i].fim.x += inicio.x;
		objetos[i].inicio.y += inicio.y;
		objetos[i].fim.y += inicio.y;
	}

	*/
	//segmentaBGR(*source,temp);
	/*
	vector<Mat> channels;

	Mat sharp;
	Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);
    filter2D(*source, aux, CV_32F, kernel);
    
    //aux.convertTo(temp2,CV_8U);
    //aux*=0.5;
    imshow("laplacian",aux);



    //blur(*source,sharp,Size(5,5));
    //imshow("blur",sharp);

    source->convertTo(sharp,CV_32F);

 

    sharp = sharp - aux;

    sharp.convertTo(sharp,CV_8U);

    imshow("sharpened", sharp);	



	Normaliza(sharp, &aux);

	Canny(sharp,sharp,minCanny,maxCanny,2*sizeCanny+3);
	imshow("Canny", sharp);

	
	inRange(aux,Scalar(minB,minG,minR,minL),Scalar(maxB,maxG,maxR,maxL),temp);
	//imshow("bom", temp);
	inRange(aux,Scalar(minBo,minGo,minRo,minLo),Scalar(maxBo,maxGo,maxRo,maxLo),temp2);
	
	addWeighted(temp,0.5,temp2,1,0,temp);
	imshow("thresh",temp);


	bitwise_not(sharp,sharp);
	bitwise_and(sharp,temp,temp);
	imshow("areas",temp);
	
	//Laplacian(*source,laplacian,CV_8UC3);
	//imshow("laplacian",laplacian);



	
	
	*/
	//segmentaNorm(aux,temp);

	/*
	vector<Mat> channels;
	split(aux,channels);
	channels.erase(channels.begin()+3);

	Canny(aux,temp,minCanny,maxCanny,2*sizeCanny+1);

	imshow("canny",temp);
	*/

	/*
	vector<Mat> channels;
	split(aux,channels);
	vector<Mat> canais(3);
	imshow("B",channels[0]);
	imshow("G",channels[1]);
	imshow("R",channels[2]);
	imshow("L",channels[3]);
	inRange(aux,Scalar(minB,minG,minR,minL),Scalar(maxB,maxG,maxR,maxL),temp);
	imshow("Range",temp);
	inRange(channels[0],Scalar(minB),Scalar(maxB),temp);
	imshow("RangeB",temp);
	inRange(channels[1],Scalar(minG),Scalar(maxG),temp);
	imshow("RangeG",temp);
	inRange(channels[2],Scalar(minR),Scalar(maxR),temp);
	imshow("RangeR",temp);
	inRange(channels[3],Scalar(minL),Scalar(maxL),temp);
	imshow("RangeL",temp);
	*/

	//imshow("src",*source);

	/*
	Mat temp;
	vector<Mat> channels;
	split(aux,channels);

	inRange(channels[0],Scalar(minB),Scalar(maxB),temp);
	imshow("B",temp);
	inRange(channels[1],Scalar(minG),Scalar(maxG),temp);
	imshow("G",temp);
	inRange(channels[2],Scalar(minR),Scalar(maxR),temp);
	imshow("R",temp);
	inRange(channels[3],Scalar(minL),Scalar(maxL),temp);
	imshow("L",temp);
	inRange(aux,Scalar(minB,minG,minR,minL),Scalar(maxB,maxG,maxR,maxL),temp);
	imshow("combinado",temp);

	segmentaNorm(aux,temp);
	*/
	/*
	source->copyTo(aux);
	cvtColor(*source,*source,CV_BGR2Lab);
	Luminosidade(source);
	Segmenta(*source,aux);
	*/
	return 1;
}


void RastreiaCone::Thresh(Mat src, Mat* dst)
{

	cvtColor(src,src,CV_BGR2Lab);

	int i,j,k;
	int C = src.channels();
	uchar *p, *p2;
	int nRows = src.rows;
	int nCols = src.cols;

	
	Mat l(src.size(),CV_8UC1);
	Mat a(src.size(),CV_8UC1);
	Mat b(src.size(),CV_8UC1);

	uchar *pl,*pa,*pb;
	
	for(i=0;i<nRows;i++)
	{
		p = src.ptr<uchar>(i);
		p2 = dst->ptr<uchar>(i);
		
		pl = l.ptr<uchar>(i);
		pa = a.ptr<uchar>(i);
		pb = b.ptr<uchar>(i);
		
		for(j=0,k=0;j<nCols;j++,k+=C)
		{
			p2[j] = Tabela[p[k] ][p[k+1] ][p[k+2] ];
			pl[j] = (uchar)(255*L[ p[k] ]);
			pa[j] = (uchar)(255*A[p[k+1] ]);
			pb[j] = (uchar)(255*B[p[k+2] ]);		
		}
	}

	imshow("L",l);
	imshow("a",a);
	imshow("b",b);


}


int RastreiaCone::varredura(Mat source, Rect area, Mat thresh ){


	/*
	Mat aux;
	//Mat temp(source->size(),CV_8UC1); 
	//temp = Scalar(0);
	//Mat tempB(source->size(),CV_8UC1);
	//Mat tempG(source->size(),CV_8UC1);
	//Mat tempR(source->size(),CV_8UC1);

	uchar *p, *p2;
	uchar *pB,*pG,*pR;

	Normaliza( *source,&aux);

	int i,j,k;
	int C = aux.channels();

	Mat t2((*source)(area).size(),CV_8UC1);


	for(i=0;i<(*thresh)(area).rows;i++)
	{
		p = aux(area).ptr<uchar>(i);
		p2 = (*thresh)(area).ptr<uchar>(i);
		pB = t2.ptr<uchar>(i);

		for(j=0,k=0;j<(*thresh)(area).cols;j++,k+=C)
		{
			p2[j] = Tabela[p[k] ][p[k+1] ][p[k+2] ];
			pB[j] = p2[j];		
		}
	}
	*/

	int i, k,j;
	k = objetos.size();


	Mat temp,temp2;
	//thresh(area).copyTo(temp);
	//temp = (*source)(area);
	//temp2 = thresh(area);


	//imshow("source",source);
	//imshow("thresh",thresh);
	//imshow("asrc",source(area));
	//imshow("tsrc",thresh(area));

	//Mat temp;

	(thresh(area)).copyTo(temp);

	segmentaDif( source(area), temp );



	
	for(i = k; i<objetos.size();i++)
	{
		/*
		for(j=0;j<objetos[i].num_pontos;j++)
		{
			objetos[i].pontos[j].x += area.x;
			objetos[i].pontos[j].y += area.y;
			thresh.at<uchar>(Point(objetos[i].pontos[j].x ,objetos[i].pontos[j].y) ) = 0;
		}
		*/
		objetos[i].inicio.x += area.x;
		objetos[i].fim.x += area.x;
		objetos[i].inicio.y += area.y;
		objetos[i].fim.y += area.y;
		objetos[i].canto.x = area.x;
		objetos[i].canto.y = area.y;
		for(j=0;j<objetos[i].num_pontos;j++)
		{
			(thresh(area)).at<uchar>(Point(objetos[i].pontos[j].x ,objetos[i].pontos[j].y) ) = 0;
		}

	}
	
}

#endif



void RastreiaCone::rastreia(Mat source){
	
	#ifdef usuario

	if(filtro){
		PreencheTabela();
	}

	#endif



	//gettimeofday(&velho, NULL);
	Mat temp2;
	ratio_original = (float)source.cols/(float)source.rows;

	
	pub_angulo = 100;
	pub_distancia = -1;
	encontrou_cone = false;


	if(tamanho0 < 10)
		tamanho0 = 10;

	resize(source, temp2, Size((int)(((float)tamanho0)*ratio_original), tamanho0 ));
	imshow("source",temp2);
	Mat thresh(temp2.size(),CV_8UC1);
	thresh = Scalar(0);

	Mat segmentos;
	temp2.copyTo(segmentos);

	
	int adx, ady;

	int minx,miny,maxx,maxy;
	if(objetos.size() > 0)
	//if(false)
	{
		int i;
		int x,y,w,h;
		vector<Rect> roi;
		roi.clear();
		int num = objetos.size();
		//vector<Point> inicio;
		for(i = 0; i<num;i++)
		{
			x = objetos[i].inicio.x;
			y = objetos[i].inicio.y;
			w = objetos[i].fim.x;
			h = objetos[i].fim.y;

			adx = (int)(((float)(w-x))*delta);
			ady = (int)(((float)(h-y))*delta);

			x-=adx;
			y-=ady;
			w+=adx;
			h+=ady;
			if(x<0){
				x=0;
			}
			if(x>=temp2.cols)
			{
				x = temp2.cols-1;
			}
			if(y<0){
				y = 0;
			}
			if(y>=temp2.rows)
			{
				y = temp2.rows-1;
			}

			if(w>=temp2.cols){
				w = temp2.cols-1;
			}
			if(w<0)
			{
				w = 0;
			}
			if(h>=temp2.rows){
				h = temp2.rows-1;
			}
			if(h<0)
			{
				h=0;
			}
			
			if(i==0)
			{
				minx = x;
				miny = y;
				maxx = w;
				maxy = h;
			}
			else
			{
				if(x<minx)
					minx = x;
				if(w>maxx)
					maxx = w;
				if(y<miny)
					miny = y;
				if(h>maxy)
					maxy = h;
			}
			
			w-=x;
			h-=y;
			if(w>10 && h>10)
			{
				roi.push_back( Rect(x,y,w,h) ); 
				//inicio.push_back(Point(x,y));
				//rectangle(temp2,Point(x,y),Point(x+w,y+h),Scalar(250,0,250)); 
			}
		}
		objetos.clear();

		Mat aux = thresh(Rect(minx,miny,maxx-minx,maxy-miny));
		Thresh(temp2(Rect(minx,miny,maxx-minx,maxy-miny)), &aux );
		imshow("thresh",thresh);
		
		for(i=0;i<roi.size();i++)
		{
			//cout<<"roi: "<<roi[i]<<endl;
			varredura(thresh,roi[i],thresh );
		}

		DesenhaSeg(&segmentos);
		imshow("Seg",segmentos);
	}
	else
	{
		objetos.clear();
		Thresh(temp2,&thresh);
		imshow("thresh",thresh);
		varredura(thresh,Rect(0,0,temp2.cols,temp2.rows),thresh );
		
		DesenhaSeg(&segmentos);
		imshow("Seg",segmentos);
		

		//objetos.clear();

	}


	
	/*
	#ifdef filmar
	if(!video_init){
		video = new VideoWriter("/home/ricardo/Documents/oi3.avi",CV_FOURCC('M','J','P','G'),33, Size(temp.cols,temp.rows),true);
		video_init = true;
	}
	video->write(temp);
	#endif
	*/
} 

Segmento::Segmento()
{
	num_pontos = 0;
}


float Segmento::ratio()
{
	return (float)(fim.y-inicio.y)/(float)(fim.x-inicio.x);
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
	if(num_pontos==1)
	{
		centro.x = ponto.x;
		centro.y = ponto.y;
	}
	else
	{
		centro.x = (((float)(num_pontos-1)/(float)num_pontos)*centro.x + (float)ponto.x/(float)num_pontos);
		centro.y = (((float)(num_pontos-1)/(float)num_pontos)*centro.y + (float)ponto.y/(float)num_pontos);
	}
}

void Segmento::addPoint(Point ponto, vector<uchar> cor)
{
	int i;
	float ratio;
	pontos.push_back(ponto);
	num_pontos++;
	if(num_pontos == 1)
	{
		for(i = 0; i<cor.size();i++)
		{
			avg_cor.push_back(cor[i]);
		}
		centro.x = ponto.x;
		centro.y = ponto.y;
		inicio.x = ponto.x;
		inicio.y = ponto.y;
		fim.x = ponto.x;
		fim.y = ponto.y;
	}
	else
	{
		if(ponto.x<inicio.x)
			inicio.x = ponto.x;
		if(ponto.y<inicio.y)
			inicio.y = ponto.y;
		if(ponto.x>fim.x)
			fim.x = ponto.x;
		if(ponto.y>fim.y)
			fim.y = ponto.y;

		ratio = ((float)(num_pontos-1)/(float)num_pontos);
		centro.x = (ratio*centro.x + (float)ponto.x/(float)num_pontos);
		centro.y = (ratio*centro.y + (float)ponto.y/(float)num_pontos);
		if(cor.size()!=avg_cor.size())
		{
			cerr<<"Ponto possue numero de canais diferente do segmento"<<endl;
		}
		else
		{
			for(i=0; i<avg_cor.size();i++)
			{
				avg_cor[i] = (uchar)(ratio*(float)avg_cor[i]+(float)cor[i]/(float)num_pontos);
			}
		}
	}
}

void Segmento::addVector(vector<Point> novos_pontos)
{
	for(int i = 0; i<novos_pontos.size();i++)
	{
		pontos.push_back(novos_pontos[i]);
	}
	num_pontos+=novos_pontos.size();
}


void Segmento::addVector(vector<Point> novos_pontos, vector<uchar> cor, Point centro_novo)
{
	int i;
	float ratio_ant, ratio_novo;


	if(cor.size() != avg_cor.size())
	{
		cerr<<"Ponto possue numero de canais diferente do segmento"<<endl;		
	}
	else
	{
		ratio_ant =  ((float)num_pontos/(float)(num_pontos+novos_pontos.size()));
		ratio_novo =  ((float)novos_pontos.size()/(float)(num_pontos+novos_pontos.size()));

		for(i = 0; i<novos_pontos.size();i++)
		{
			pontos.push_back(novos_pontos[i]);
			if(novos_pontos[i].x<inicio.x)
				inicio.x = novos_pontos[i].x;
			if(novos_pontos[i].y<inicio.y)
				inicio.y = novos_pontos[i].y;
			if(novos_pontos[i].x>fim.x)
				fim.x = novos_pontos[i].x;
			if(novos_pontos[i].y>fim.y)
				fim.y = novos_pontos[i].y;
		}
		num_pontos+=novos_pontos.size();

		centro.x = (ratio_ant*(float)centro.x+ratio_novo*(float)centro_novo.x);
		centro.y = (ratio_ant*(float)centro.y+ratio_novo*(float)centro_novo.y);


		for(i=0;i<cor.size();i++)
		{
			avg_cor[i] = (ratio_ant*(float)avg_cor[i]+ratio_novo*(float)cor[i]);
		}

	}

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

void Segmento::clear()
{
	pontos.clear();
	rotated.clear();
	esquerda.clear();
	direita.clear();
	avg_cor.clear();
	num_pontos = 0;
	altura = 0;
	largura = 0;
	inicio = fim = centro = canto = Point(0,0);
}

