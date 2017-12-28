#include "RastreiaCone.hpp"
#include "Segmento.hpp"

void int_to_string(int valor, string* numeral){
  int inteiro = valor;
  int resto = valor;
  do{
    resto = inteiro%10;
    inteiro = inteiro/10;
    (*numeral).push_back( (char)(resto + 48) );
  }while(inteiro > 0);
  reverse((*numeral).begin(),(*numeral).end()); 
}

void float_to_string(float valor, string* numeral, int casas)
{
  numeral->clear();
  if(valor < 0)
  {
  	(*numeral) = "-";
  	valor*=-1;
  	}
  int val = valor;
  string aux;
  int_to_string(val,&aux);
  (*numeral) = (*numeral) + aux + ".";
  valor -= val;
  float mul = pow(10,casas);
  valor *= mul;
  mul/=10;
  while(mul>valor&&mul>1)
  {
  	(*numeral) = (*numeral)+"0";
  	mul/=10;
  }
  val = valor;
  aux.clear();
  int_to_string(val,&aux);
  (*numeral) = (*numeral)+aux;
}

RastreiaCone::RastreiaCone(){
	delta = 0.2;

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


	//teste
	/*
	minB = 0;
	maxB = 240;
	minG = 100;
	maxG = 165;
	minR = 60;
	maxR = 150;

	minBo = 30;
	maxBo = 150;
	minGo = 135;
	maxGo = 155;
	minRo = 60;
	maxRo = 115;
	*/

	//cone
	/*
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
	*/
	//coneCasaWebCam
	/*
	minL = 50;
	maxL = 256;
	minB = 10;
	maxB = 240;
	minG = 100;
	maxG = 200;
	minR = 130;
	maxR = 185;

	minLo = 40;
	maxLo = 200;
	minBo = 50;
	maxBo = 180;
	minGo = 155;
	maxGo = 175;
	minRo = 145;
	maxRo = 180;
	*/

	
	minB = 0;
	maxB = 240;
	minG = 135;//140;
	maxG = 175;
	minR = 135;//140;
	maxR = 200;


	minBo = 20;
	maxBo = 140;
	minGo = 145;//150;
	maxGo = 175;
	minRo = 145;//160;
	maxRo = 200;




	difLo = 10;
	difLb = 20;
	difAo = 3;
	difAb = 8;
	difBo = 3;
	difBb = 10;

	max_dif = 80;

	sizeCanny = 0;

	minCanny = 30;
	maxCanny = 60;


	aceita_final = 60;//160;
	min_aceita = 250;

	//dif_pixel = 15;
	//dif_centroide = 140;
	//max_dif_pixel = 15;
	//max_dif_centroide = 140;

	//max_dif_pixelL = 8;
	//max_dif_centroideL = 80;

	angulo_ideal = 20.10;



	min_segment_size = 50;

	//PreencheTabela();

	atualiza = true;

	tamanho0 = 240;

	linha_centro = tamanho0/2;

	max_search_area = 40000;

	PreencheTabela();


	filtro = false;
	#ifdef filmar
	video_init = false;
	#endif
	
}



void RastreiaCone::PreencheTabela(){

	//cout<<"atualizando"<<endl;

	int i, j, k;
	float incremento;
	float valor;

	//Preenche tabela de cor

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
	for(k = minBB; k<maxBB; k++){
		for(i = minLB; i<maxLB; i++){
			for(j = minAB; j<maxAB; j++){
				Tabela[i][j][k] = max((int)Tabela[i][j][k],(int)aceita_final);
			}
		}
	}
	*/





	//Preenche tabela de diferença
	//Filtro da Luminancia
	for(i = 0; i<difLo; i++){
		difL[i] = 1;
	}
	incremento = (1.0 )/(float)(difLo - difLb);
	valor = 1;
	for( i = difLo; i<difLb; i++){
		valor += incremento;
		difL[i] = valor;
	}
	for(i = difLb ; i<50; i++){
		difL[i] = 0;
	}

	//Filtro de a
	for(i = 0; i<difAo; i++){
		difA[i] = 1;
	}
	incremento = (1.0 )/(float)(difAo - difAb);
	valor = 1;
	for( i = difAo; i<difAb; i++){
		valor += incremento;
		difA[i] = valor;
	}
	for(i = difAb ; i<50; i++){
		difA[i] = 0;
	}

	//Filtro de b
	for(i = 0; i<difBo; i++){
		difB[i] = 1;
	}
	incremento = (1.0 )/(float)(difBo - difBb);
	valor = 1;
	for( i = difBo; i<difBb; i++){
		valor += incremento;
		difB[i] = valor;
	}
	for(i = difBb ; i<50; i++){
		difB[i] = 0;
	}

	for(i=0;i<50;i++)
	{
		for(j=0;j<50;j++)
		{
			for(k=0;k<50;k++)
			{
				difTable[i][j][k] = difL[i]*difA[j]*difB[k];
			}
		}
	}


	max_fdif = (float)max_dif/100;

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

float RastreiaCone::corIgual(Vec3b cor, Vec3b cor2)
{
	float dif;
	int i;
	int aux;
	int dL,dA,dB;
	dL = abs(cor[0]-cor2[0]);
	dA = abs(cor[1]-cor2[1]);
	dB = abs(cor[2]-cor2[2]);
	if(dL >= 50 || dA >= 50 || dB >=50)
		return 0;
	else
	{
		return difTable[dL][dA][dB];
	}
}

void RastreiaCone::segmenta(Mat src, Mat thresh)
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

	Vec3b *aux1, *aux2;

	float difP, difC, maxdifP, maxdifC, dif;
	float ratio_lux = 2.0; 


	for(i=0;i<nRows;i++)
	{
		p=src.ptr<uchar>(i);
		//p2 = ref.ptr<uchar>(i);
		p3 = thresh.ptr<uchar>(i);
		for(j=0,k=0;j<nCols;j++,k+=nCanais)
		{
			if( p3[j] > min_aceita )
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
					//cout<<"   "<<segmento.pontos[l]<<"/"<<(int)p4[x];
					x4 = x*nCanais;
					//cout<<"(";
					for(m=0;m<num_dir;m++)
					{
						//posicao do novo ponto
						x2 = x+lados[m].x;
						y2 = y+lados[m].y;
						x3 = x2*nCanais;
						
						//ponto dentro da imagem
						if(x2>=0&&y2>=0&&x2<nCols&&y2<nRows)
						{
							
							if(thresh.at<uchar>(Point(x2,y2)) > aceita_final)
							{
								aux2 = src.ptr<Vec3b>(y2);
								aux1 = src.ptr<Vec3b>(y);
								difP = corIgual(aux1[x],aux2[x2]);

								//checa se cor do pixel é suficientemente semelhante
								//if(maxdifC<max_dif_centroide && maxdifP<max_dif_pixel && difP < dif_pixel && difC < dif_centroide)
								
								if( difP > max_fdif )
								{
									//retira ponto da imagem de thresh, esse ponto não poderá ser incluído em outros
									thresh.at<uchar>(Point(x2,y2)) = 0;
										//adiciona pixel ao segmento
									
									segmento.addPoint(Point(x2,y2));
								}
							}
							
						}

					}
					l++;
				}

				//cout<<endl;
				//cout<<"    "<<l<<endl;
				if(segmento.num_pontos > min_segment_size && segmento.ratio() > 1 && segmento.ratio() < 10 )
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
	k=0;
	for(i=0;i<objetos.size();i++)
	{

		for(j=0;j<objetos[i].num_pontos;j++)
		{
			src->at<Vec3b>(objetos[i].pontos[j]+objetos[i].canto)[0] = Cor[i][0];
			src->at<Vec3b>(objetos[i].pontos[j]+objetos[i].canto)[1] = Cor[i][1];
			src->at<Vec3b>(objetos[i].pontos[j]+objetos[i].canto)[2] = Cor[i][2];
		}
		k++;
		if(k>=Cor.size())
		{
			k = 0;
		}
	}
}

void RastreiaCone::Thresh(Mat src, Mat* dst)
{

	//cvtColor(src,src,CV_BGR2Lab);

	int i,j,k;
	int C = src.channels();
	uchar *p, *p2;
	int nRows = src.rows;
	int nCols = src.cols;

	#ifdef subthresh
	Mat l(src.size(),CV_8UC1);
	Mat a(src.size(),CV_8UC1);
	Mat b(src.size(),CV_8UC1);
	uchar *pl,*pa,*pb;
	#endif
	
	for(i=0;i<nRows;i++)
	{
		p = src.ptr<uchar>(i);
		p2 = dst->ptr<uchar>(i);
		
		#ifdef subthresh
		pl = l.ptr<uchar>(i);
		pa = a.ptr<uchar>(i);
		pb = b.ptr<uchar>(i);
		#endif
		for(j=0,k=0;j<nCols;j++,k+=C)
		{
			p2[j] = Tabela[p[k] ][p[k+1] ][p[k+2] ];

			#ifdef subthresh
			pl[j] = (uchar)(255*L[ p[k] ]);
			pa[j] = (uchar)(255*A[p[k+1] ]);
			pb[j] = (uchar)(255*B[p[k+2] ]);	
			#endif	
		}
	}

	#ifdef subthresh
	imshow("L",l);
	imshow("a",a);
	imshow("b",b);
	#endif
}


int RastreiaCone::varredura(Mat source, Rect area, Mat thresh ){
	int i, k,j;
	k = objetos.size();
	Mat temp;
	(thresh(area)).copyTo(temp);
	segmenta( source(area), temp );
	for(i = k; i<objetos.size();i++)
	{
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

int RastreiaCone::Busca(Mat source, Mat thresh,float razao, int x0, int y0 ){
	int i, k,j;
	segmenta( source, thresh );
	
	for(i = 0; i<objetos.size();i++)
	{
		objetos[i].inicio.x = (int)((float)objetos[i].inicio.x*razao)+x0;
		objetos[i].fim.x = (int)((float)objetos[i].fim.x*razao)+x0;
		objetos[i].inicio.y = (int)((float)objetos[i].inicio.y*razao)+y0;
		objetos[i].fim.y = (int)((float)objetos[i].fim.y*razao)+y0;
		objetos[i].canto.x = x0;
		objetos[i].canto.y = y0;		
	}
	
}




int RastreiaCone::varredura2(Mat source, Rect area, Mat thresh ){
	int i, k,j;
	k = objetos.size();
	Mat temp;
	(thresh(area)).copyTo(temp);
	segmenta( source(area), temp );
	for(i = k; i<objetos.size();i++)
	{
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


void RastreiaCone::Identifica(int nCols, float anguloH, int nRows, float anguloV, float ratio)
{
	int i,j;
	vector<Point> limites;
	lista.clear();
	float angulo;
	Cone novo_cone;
	cones.clear();
	for(i=0;i<objetos.size();i++)
	{
		
		objetos[i].rotate();
		
		objetos[i].bordas();
		

		limites.clear();
		
		angulo = objetos[i].Forma(&limites);

		/*
		for(j=0;j<limites.size();j++){
			limites[j].x = (int)((float)limites[j].x*ratio);
			limites[j].y = (int)((float)limites[j].y*ratio);
		}
		*/

		lista.push_back(limites);
		if( fabs(angulo-angulo_ideal)<8 )
		{
			novo_cone.angulo = angulo;
			novo_cone.qualidade = 8 - fabs(angulo-angulo_ideal);
			novo_cone.inicio.x = objetos[i].inicio.x;
			novo_cone.inicio.y = objetos[i].inicio.y;
			novo_cone.fim.x = objetos[i].fim.x;
			novo_cone.fim.y = objetos[i].fim.y;
			novo_cone.centro.x = (int)((float)objetos[i].centro.x*ratio)+objetos[i].canto.x;
			novo_cone.centro.y = (int)((float)objetos[i].centro.y*ratio)+objetos[i].canto.y;
			novo_cone.Posicao(nCols,anguloH, nRows, anguloV);
			cones.push_back(novo_cone);
		}
		
		
		//objetos[i].Momentos();
	}
	//objetos.clear();
}


void RastreiaCone::DesenhaBordas(Mat* seg, float ratio)
{
	int i,j,x,y;
	Mat C(2,1,CV_32F);
	Mat P(2,1,CV_32F);
	Mat P2(2,1,CV_32F);

	Point es,ei,ds,di;

	for(i=0;i<objetos.size();i++)
	{
		//C.at<float>(Point(0,0)) = (float)objetos[i].centro.x*ratio + objetos[i].canto.x;
		//C.at<float>(Point(0,1)) = (float)objetos[i].centro.y*ratio + objetos[i].canto.y;
		C.at<float>(Point(0,0)) = (float)objetos[i].centro.x;
		C.at<float>(Point(0,1)) = (float)objetos[i].centro.y;


		P.at<float>(Point(0,0)) = lista[i][0].x;
		P.at<float>(Point(0,1)) = lista[i][0].y;

		P2 = objetos[i].inv_rotacao*P+C;
		es.x = (int)P2.at<float>(Point(0,0));
		es.y = (int)P2.at<float>(Point(0,1));

		P.at<float>(Point(0,0)) = lista[i][1].x;
		P.at<float>(Point(0,1)) = lista[i][1].y;

		P2 = objetos[i].inv_rotacao*P+C;
		ei.x = (int)P2.at<float>(Point(0,0));
		ei.y = (int)P2.at<float>(Point(0,1));

		P.at<float>(Point(0,0)) = lista[i][2].x;
		P.at<float>(Point(0,1)) = lista[i][2].y;

		P2 = objetos[i].inv_rotacao*P+C;
		ds.x = (int)P2.at<float>(Point(0,0));
		ds.y = (int)P2.at<float>(Point(0,1));

		P.at<float>(Point(0,0)) = lista[i][3].x;
		P.at<float>(Point(0,1)) = lista[i][3].y;

		P2 = objetos[i].inv_rotacao*P+C;
		di.x = (int)P2.at<float>(Point(0,0));
		di.y = (int)P2.at<float>(Point(0,1));

		line(*seg, ei,es, Scalar(255,255,0));
		line(*seg, di,ds, Scalar(255,255,0));

		for(j=0;j<objetos[i].altura;j++)
		{
			
			P.at<float>(Point(0,0)) = objetos[i].esquerda[j].x;
			P.at<float>(Point(0,1)) = objetos[i].esquerda[j].y;
			
			
			P2 = objetos[i].inv_rotacao*P+C;
			x = (int)P2.at<float>(Point(0,0));
			y = (int)P2.at<float>(Point(0,1));
			if(x>=0&&x<seg->cols&&y>=0&&y<seg->rows)
			{
				seg->at<Vec3b>(Point(x,y))[0] = 0;
				seg->at<Vec3b>(Point(x,y))[1] = 255;
				seg->at<Vec3b>(Point(x,y))[2] = 0;
			}

			P.at<float>(Point(0,0)) = objetos[i].direita[j].x;
			P.at<float>(Point(0,1)) = objetos[i].direita[j].y;
			
			
			P2 = objetos[i].inv_rotacao*P+C;
			x = (int)P2.at<float>(Point(0,0));
			y = (int)P2.at<float>(Point(0,1));
			if(x>=0&&x<seg->cols&&y>=0&&y<seg->rows)
			{
				seg->at<Vec3b>(Point(x,y))[0] = 255;
				seg->at<Vec3b>(Point(x,y))[1] = 0;
				seg->at<Vec3b>(Point(x,y))[2] = 255;
			}
			
		}
	}
}


void RastreiaCone::Filtrar(Mat *src )
{


	cvtColor((*src),(*src),CV_BGR2Lab);
	//imshow("Lab", (*src));
	vector<Mat> lab;
	split((*src),lab);

	//imshow("l0",lab[0]);
	//imshow("a0",lab[1]);
	//imshow("b0",lab[2]);

	//namedWindow("bar");

	static int ed_size = 2;
	static int median_size = 1;

	//createTrackbar("erode_dilate", "bar", &ed_size, 20);
	//createTrackbar("median", "bar", &median_size, 20);

	Mat element = getStructuringElement( MORPH_ELLIPSE,Size( 2*ed_size + 1, 2*ed_size+1 ),Point( ed_size, ed_size ) );

	dilate( lab[1], lab[1], element );
	erode(lab[1],lab[1],element);
  	medianBlur(lab[1],lab[1],2*median_size+1);
  	//imshow("a1",lab[1]);
  	

  	dilate( lab[2], lab[2], element );
	erode(lab[2],lab[2],element);
  	medianBlur(lab[2],lab[2],2*median_size+1);
  	//imshow("b1",lab[2]);

  	merge(lab,(*src));


  	//imshow("L0",lab[0]);
  	//imshow("a0",lab[1]);
  	//imshow("b0",lab[2]);
  	//imshow("novo",*src);

}


double RastreiaCone::rastreia(Mat source, bool pred, float  X, float Y, float T, float varX, float varY){
	

	//cout<<T<<endl;

	float variancia = 1;

	#ifdef usuario
	/*
	if(filtro){
		PreencheTabela();
		filtro = false;
	}
	*/
	#endif

	if(filtro){
		PreencheTabela();
		filtro = false;
	}

	//gettimeofday(&velho, NULL);
	Mat temp2;
	ratio_original = (float)source.cols/(float)source.rows;


	#if defined(usuario)||defined(filmar)
	Mat mostra;
	resize(source,mostra,Size((int)(((float)120)*ratio_original), 120) );
	//resize(source,mostra,Size((int)(((float)480)*ratio_original), 480) );
	#endif


	encontrou_cone = false;


	if(tamanho0 < 10)
		tamanho0 = 10;


	//resize(source, source, Size((int)(((float)tamanho0)*ratio_original), 480 ));
	

	
	int adx, ady;
	int i,j;
	int minx,miny,maxx,maxy;
	int predxe, predxd, predyt, predyb;

	float xi,xf,yi,yf;

	float  razao = 1;

	bool good_pred = true;

	if(pred)
	//if(false)
	{
		//cout<<X<<"    "<<Y<<endl<<"to"<<endl;
		int x,y,h,w;
		
		float aux = source.cols/2;
		//Posicao prevista
		//Colunas
		float Coluna, Linha;
		float alpha = -(180.0/CV_PI)*atan(Y/X);
		float a0,a1,a2, beta;
		float dist = sqrt(X*X+Y*Y);

		if(dist>21)
			dist = 21;

		//predxd = aux*(1+alpha/30);
		//line(temp2,Point(predxd,0),Point(predxd,tamanho0),Scalar(0,255,0));
		beta = (180.0/CV_PI)*atan(0.30/dist);
		a1 = alpha+beta/2;
		a2 = alpha-beta/2;
		predxd = aux*(1+a1/30);
		predxe = aux*(1+a2/30);


		alpha = linha_centro;
		
		aux = 0.75322976  - (0.03451*dist);
		aux = abs(sqrt(aux)) ;
		aux-= 0.8647;
		aux/=(-0.017255);		
		aux = 0.5/aux;
		aux = atan(aux);
		aux = ( (aux*source.rows*2)/CV_PI);
		predyt = alpha-aux;
		predyb = alpha+aux;

		//Margem de erro
		//menor distancia -> maior area na imagem
		xi = X-varX;
		if(xi<=0)
		{
			xi = 0;
			yi = 0;
			xf = source.cols-1;
			yf = source.rows-1;
		}
		else
		{
			if( (Y-varY)/(Y+varY) < 0 )
				yi = 0;
			else
			{
				yi = min( fabs(Y-varY),fabs(Y+varY)   );
			}
			dist = sqrt(yi*yi+xi*xi);
			
			if(dist>21)
				dist = 21;

			beta = (180.0/CV_PI)*atan(0.30/dist);

			//angulos limites +  meia largura do cone
			a1 = -(180.0/CV_PI)*atan( (Y-varY)/(X-varX)  ) + beta/2;
			a2 = -(180.0/CV_PI)*atan( (Y+varY)/(X-varX)  ) - beta/2;
			if(a1<-30 || a2>30){
				good_pred = false;
			}
			else
			{
				xi = (source.cols-1)*(0.5+a2/60.0);
				xf = (source.cols-1)*(0.5+a1/60.0);


				aux = 0.75322976  - (0.03451*dist);
				aux = abs(sqrt(aux)) ;
				aux-= 0.8647;
				aux/=(-0.017255);		
				aux = 0.5/aux;
				aux = atan(aux);
				aux = ( (aux*source.rows*2)/CV_PI);

				yi = linha_centro - aux-10;
				yf = linha_centro + aux+10;
				//linha_centro/=temp2.rows;
				//yi = source.rows*(H_centro - aux)-10;
				//yf = source.rows*(H_centro + aux)+10;
				if(xi < 0)
					xi = 0;
				if(yi < 0)
					yi = 0;
				if(xf>=source.cols)
					xf = source.cols-1;
				if(yf >= source.rows)
					yf = source.rows-1;
			}	
		}
		if(good_pred)
		{
			w = xf-xi;
			h = yf-yi;
			x = xi;
			y = yi;
			
			Rect roi(x,y,w,h);
			cones.clear();


			

			razao = 1;
			if(w*h > max_search_area)
			{
				temp2 = source(roi);
				float A = max_search_area;
				float ratio = (float)w/(float)h;
				float new_H = sqrt(A/ratio);
				razao = (float)h/new_H;
				resize(temp2,temp2,Size( (int)(ratio*new_H), (int)(new_H) ));
			}
			#ifdef usuario
			else
			{
				source(roi).copyTo(temp2);
			}
			#else
			else{
				temp2 = source(roi);
			} 
			#endif
			//imshow("area",temp2);
			objetos.clear();
			cones.clear();
			Mat temp(temp2.size(),CV_8UC1);
			//blur(temp2(roi),temp2(roi),Size(3,3));
			Filtrar(&temp2);	
			Thresh( temp2, &temp );
			//imshow("thresh",temp);
			Busca(temp2,temp,razao,x,y);
			//varredura(temp2,roi,thresh );
			
			


			Identifica(source.cols,60.00,source.rows,45.00,razao);
			//DesenhaBordas(&temp2,1);
			//imshow("bordas",temp2);
			
			

			
			if(cones.size() == 0){
				good_pred = false;
			}
						
			
			//rectangle(temp2,Point(predxe,predyt),Point(predxd,predyb),Scalar(0,0,255));
			//imshow("pred",temp2);
			

			#ifdef mostra_seg

			
			for(i = 0; i<objetos.size();i++)
			{
				for(j=0;j<objetos[i].num_pontos;j++)
				{
					//objetos[i].pontos[j].x = (int)((float)(objetos[i].pontos[j].x-x)  *razao);
					//objetos[i].pontos[j].y = (int)((float)(objetos[i].pontos[j].y-y) *razao);
					objetos[i].pontos[j].x = (int)((float)(objetos[i].pontos[j].x-x));
					objetos[i].pontos[j].y = (int)((float)(objetos[i].pontos[j].y-y));
				}			
			}
			
			Mat segmentos;
			temp2.copyTo(segmentos);

			DesenhaSeg(&segmentos);
			imshow("Seg",segmentos);
			#endif

			//objetos.clear();
		}	

	}
	//else
	if(!good_pred || !pred)
	{
		//cout<<"aqui"<<endl;
		//resize(source, source, Size((int)(((float)tamanho0)*ratio_original), 480 ));
		//source.copyTo(temp2);

		#ifdef usuario
		source.copyTo(temp2);
		//imshow("area",temp2);
		objetos.clear();
		cones.clear();		
		Mat temp(temp2.size(),CV_8UC1);
		//blur(temp2(roi),temp2(roi),Size(3,3));
		Filtrar(&temp2);		
		Thresh( temp2, &temp );
		//imshow("thresh",temp);
		Busca(temp2,temp,1,0,0);
		Identifica(source.cols,60.00,source.rows,45.00,1);
		//DesenhaBordas(&temp2,1);
		//imshow("bordas",temp2);
		#else
		objetos.clear();
		cones.clear();		
		Mat temp(source.size(),CV_8UC1);
		Filtrar(&source);		
		Thresh( source, &temp );
		Busca(source,temp,1,0,0);
		Identifica(source.cols,60.00,source.rows,45.00,1);
		#endif

		
		//objetos.clear();
		#ifdef mostra_seg
		Mat segmentos;
		temp2.copyTo(segmentos);

		DesenhaSeg(&segmentos);
		imshow("Seg",segmentos);
		#endif
		
		objetos.clear();
	}
	
	#if defined(filmar)||defined(usuario)

		string num;
	#endif

	if(cones.size()>0)
	{
		encontrou_cone = true;
		best_cone=0;
		float best_qualidade = 0;
		for(i=0;i<cones.size();i++)
		{
			if(cones[i].qualidade > best_qualidade)
			{
				best_qualidade = cones[i].qualidade;
				best_cone = i;
			}
		}
		pubx = cones[best_cone].X;
		puby = cones[best_cone].Y;
		//cout<<"Y:  "<<puby<<"   varY:  "<<varY<<endl;
		linha_centro = (cones[best_cone].inicio.y + cones[best_cone].fim.y)/2;
		//H_centro = (float)linha_centro/(float)source.rows;

		//cout<<cones[best_cone].X<<"   "<<cones[best_cone].Y<<"           "<<2*razao/(float)(cones[best_cone].fim.y-cones[best_cone].inicio.y)<<endl;
		
		variancia = 2*razao/(float)(cones[best_cone].fim.y-cones[best_cone].inicio.y);


		#if defined(filmar)||defined(usuario)
			rectangle(mostra,Point(cones[best_cone].inicio.x/4,cones[best_cone].inicio.y/4)  ,  Point(cones[best_cone].fim.x/4,cones[best_cone].fim.y/4),Scalar(255,0,0 ) );
			//rectangle(mostra,Point(cones[best_cone].inicio.x,cones[best_cone].inicio.y)  ,  Point(cones[best_cone].fim.x,cones[best_cone].fim.y),Scalar(255,0,0 ) );

			/*
			int x,y,h,w;
			float aux = source.cols/2;
			//Posicao prevista
			//Colunas
			float Coluna, Linha;
			float alpha = -(180.0/CV_PI)*atan(puby/pubx);
			float a0,a1,a2, beta;
			float dist = sqrt(pubx*pubx+puby*puby);

			//if(dist>15)
				//dist = 15;

			//predxd = aux*(1+alpha/30);
			//line(temp2,Point(predxd,0),Point(predxd,tamanho0),Scalar(0,255,0));
			beta = (180.0/CV_PI)*atan(0.30/dist);
			a1 = alpha+beta/2;
			a2 = alpha-beta/2;
			predxd = aux*(1+a1/30);
			predxe = aux*(1+a2/30);


			alpha = linha_centro;
			
			//aux = 1.199898884  - (0.07964*dist);
			//aux = abs(sqrt(aux)) ;
			//aux-= 1.1005;
			//aux/=(-0.03982);

			aux = 0.75322976  - (0.03451*dist);
			aux = abs(sqrt(aux)) ;
			aux-= 0.8647;
			aux/=(-0.017255);

	

			aux = 0.5/aux;

			//aux = 0.5/dist;

			aux = atan(aux);

			predyt = linha_centro - ((2.0f/CV_PI)*aux*source.rows);
			predyb = linha_centro + ((2.0f/CV_PI)*aux*source.rows);

			//beta = 45.0*((((float)linha_centro)/source.rows) - 0.5);


			//predyt = (beta - aux/2)*((4*source.rows)/(CV_PI))-source.rows/2;
			//predyb = (beta + aux/2)*((4*source.rows)/(CV_PI))-source.rows/2;

			//rectangle(mostra,Point(predxe,predyt),Point(predxd,predyb),Scalar(0,0,255));
			rectangle(mostra,Point(predxe,predyt),Point(predxd,predyb),Scalar(0,0,255));
			*/

			float_to_string(cones[best_cone].X,&num,5);
			putText(mostra, "X: "+num, Point(10,20), FONT_HERSHEY_SIMPLEX, 0.25, Scalar(255,255,0), 1, 8, false );
			num.clear();
			float_to_string(cones[best_cone].Y,&num,5);
			putText(mostra, "Y: "+num, Point(10,30), FONT_HERSHEY_SIMPLEX, 0.25, Scalar(255,255,0), 1, 8, false );
			//cout<<cones[best_cone].inicio<<"  "<<cones[best_cone].fim<<"  "<<linha_centro<<endl;
		#endif
	}
	#if defined(filmar)||defined(usuario)
		else
		{
			putText(mostra, "X: -", Point(10,20), FONT_HERSHEY_SIMPLEX, 0.25, Scalar(255,255,0), 1, 8, false );
			putText(mostra, "Y: -", Point(10,30), FONT_HERSHEY_SIMPLEX, 0.25, Scalar(255,255,0), 1, 8, false );
		}
		
		num.clear();
		float_to_string(T,&num,5);
		putText(mostra, "T: "+num, Point(10,10), FONT_HERSHEY_SIMPLEX, 0.25, Scalar(255,255,0), 1, 8, false );
		if(pred){
			//cout<<varX<<"    "<<varY<<endl;
			//rectangle(mostra,Point(predxe,predyt),Point(predxd,predyb),Scalar(0,0,255));
			//rectangle(mostra,Point((int)xi,(int)yi),Point((int)xf,(int)yf),Scalar(0,255,0));

			rectangle(mostra,Point(predxe/4,predyt/4),Point(predxd/4,predyb/4),Scalar(0,0,255));
			rectangle(mostra,Point((int)xi/4,(int)yi/4),Point((int)xf/4,(int)yf/4),Scalar(0,255,0));
			/*
			num.clear();
			float_to_string(varX,&num,5);
			putText(mostra, "varX: "+num, Point(20,80), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,0), 1, 8, false );
			num.clear();
			float_to_string(varY,&num,5);
			putText(mostra, "varY: "+num, Point(20,100), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,0), 1, 8, false );
			*/
		}
		#ifdef usuario
			imshow("src",mostra);
		#endif
	#endif

	
	
	#ifdef filmar
	if(!video_init){
		//resize(mostra, mostra, Size((int)(((float)240)*ratio_original), 240 ));
		//video = new VideoWriter("/home/pi/Desktop/Receiver/Camera.avi",CV_FOURCC('M','J','P','G'),10, Size(mostra.cols,mostra.rows),true);
		video = new VideoWriter("Camera.avi",CV_FOURCC('M','J','P','G'),10, Size(mostra.cols,mostra.rows),true);
		video_init = true;
	}
	video->write(mostra);
	#endif
	
	return variancia;

} 
