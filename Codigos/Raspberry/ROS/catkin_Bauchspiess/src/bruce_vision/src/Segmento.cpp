#include "Segmento.hpp"

Segmento::Segmento()
{
	num_pontos = 0;
	altura = 0;
	largura = 0;

	//porque = 0;
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
	if(num_pontos == 1)
	{
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
	}
	/*
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
	*/
}

void Segmento::addPoint(Point ponto, vector<uchar> cor)
{
	int i;
	//float ratio;
	pontos.push_back(ponto);
	num_pontos++;
	if(num_pontos == 1)
	{
		/*
		for(i = 0; i<cor.size();i++)
		{
			avg_cor.push_back(cor[i]);
		}
		*/
		//centro.x = ponto.x;
		//centro.y = ponto.y;
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

		/*
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
		*/
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

float Segmento::Forma(vector<Point>* limites)
{
	Vec4f esq,dir;
	Point2f ds,di,es,ei;
	float angulo;

	fitLine(esquerda, esq, CV_DIST_L2, 0, 0.01, 0.01);
	es.y = anchor.y;
	es.x = (int)(esq[2] + ( (es.y-esq[3])*(esq[0]/esq[1]) ) );
	ei.y = altura + anchor.y;
	ei.x = (int)(esq[2] + ((ei.y-esq[3])*(esq[0]/esq[1]))   );
	fitLine(direita, dir, CV_DIST_L2, 0, 0.01, 0.01);
	ds.y = anchor.y;
	ds.x = (int)(dir[2] + ( (ds.y-dir[3])*(dir[0]/dir[1]))   );
	di.y = altura + anchor.y;
	di.x = (int)(dir[2] + ((di.y-dir[3])*(dir[0]/dir[1]))   );

	angulo = (180*fabs( atan(esq[0]/esq[1]) -  atan(dir[0]/dir[1]) ))/CV_PI;
	//cout<<180*angulo/CV_PI<<endl;

	limites->push_back(es);
	limites->push_back(ei);
	limites->push_back(ds);
	limites->push_back(di);
	
	/*
	int i,x,y;
	Mat mostra(altura,largura,CV_8UC3);
	mostra = Scalar(0);
	for(i = 0; i< rotated.size();i++)
	{
		x = rotated[i].x-anchor.x;
		y = rotated[i].y-anchor.y;
		mostra.at<Vec3b>(Point(x,y))[0] = 120;
		mostra.at<Vec3b>(Point(x,y))[1] = 120;
		mostra.at<Vec3b>(Point(x,y))[2] = 120;
	}
	for(i = 0; i<esquerda.size();i++)
	{
		x = esquerda[i].x-anchor.x;
		y = esquerda[i].y-anchor.y;
		mostra.at<Vec3b>(Point(x,y))[0] = 255;
		mostra.at<Vec3b>(Point(x,y))[1] = 0;
		mostra.at<Vec3b>(Point(x,y))[2] = 0;

		x = direita[i].x-anchor.x;
		y = direita[i].y-anchor.y;
		mostra.at<Vec3b>(Point(x,y))[0] = 255;
		mostra.at<Vec3b>(Point(x,y))[1] = 0;
		mostra.at<Vec3b>(Point(x,y))[2] = 0;

	}

	Point a1,a2;

	a1.x = ds.x-anchor.x;
	a1.y = ds.y-anchor.y;
	a2.x = di.x-anchor.x;
	a2.y = di.y-anchor.y;

	line(mostra,a1,a2,Scalar(0,0,255));
	
	a1.x = es.x-anchor.x;
	a1.y = es.y-anchor.y;
	a2.x = ei.x-anchor.x;
	a2.y = ei.y-anchor.y;
	line(mostra,a1,a2,Scalar(0,0,255));
	imshow("mostra",mostra);
	*/
	return angulo;

}

/*
void Segmento::Momentos()
{
	/*
	vector<Point> lados;
	int i;
	Moments mu;
	for(i=0;i<altura;i++)
	{
		lados.push_back(esquerda[i]);
		lados.push_back(direita[i]);
	}

	mu = moments(lados,false);
	vector<double> hu;

	HuMoments(mu,hu);

	for(i=0;i<7;i++)
	{
		cout<<hu[i]<<"  ";
	}
	cout<<endl;
	*/
	//cout<<mu<<endl;
	/*
	int x,y;

	Mat mostra(altura,largura,CV_8UC1);
	mostra = Scalar(0);
	for(i = 0; i< rotated.size();i++)
	{
		x = rotated[i].x-anchor.x;
		y = rotated[i].y-anchor.y;
		mostra.at<uchar>(Point(x,y)) = 255;
	}

	imshow("mostra",mostra);
	*/
//}


void Segmento::rotate()
{
	int i;
	rotated.clear();
	Point aux;
	Vec4f matriz(0,0,0,0);

	//inv_rotacao.create(2,2,CV_32FC1);
	
	//cout<<centro<<endl;
	calc_centro();
	//cout<<centro<<endl;

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
	inercia.at<float>(Point(1,0)) = matriz[1]/num_pontos;
	inercia.at<float>(Point(0,1)) = inercia.at<float>(Point(1,0));
	inercia.at<float>(Point(1,1)) = matriz[3]/num_pontos;
	Mat autovetores(2,2,CV_32FC1);
	Mat autovalores(2,1,CV_32FC1);
	eigen(inercia,autovalores, autovetores);	
	//Mat rotacao = (autovetores.inv());
	float gira_data[4] = {0,-1,1,0}; 
	Mat gira(2,2,CV_32FC1,gira_data);
	Mat rotacao = gira*autovetores.inv();
	inv_rotacao = rotacao.inv();
	inv_rotacao.copyTo(inv_rotacao);


	int max_x = -1;
	int max_y = -1;
	int min_x = 9999999;
	int min_y = 9999999;
	//rotaciona pontos
	int x,y;
	for(i = 0; i<num_pontos; i++){
		x = rotacao.at<float>(Point(0,0))*rotated[i].x + rotacao.at<float>(Point(1,0))*rotated[i].y ;
		y = rotacao.at<float>(Point(0,1))*rotated[i].x + rotacao.at<float>(Point(1,1))*rotated[i].y ;
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
		if(rotated[i].y < min_y)
		{
			min_y = rotated[i].y;
		}
	}
	altura = max_y-min_y+1;
	largura = max_x-min_x+1;
	anchor.x = min_x;
	anchor.y = min_y;

	Mat mostra(altura,largura,CV_8UC1);
	mostra = Scalar(0);
	for(i=0;i<num_pontos;i++)
	{
		mostra.at<uchar>(rotated[i].y-min_y,rotated[i].x-min_x) = 255;
	}
	imshow("rotated seg",mostra);


	
}

void Segmento::bordas()
{
	esquerda.clear();
	direita.clear();
	direita.resize(altura);
	int i;

	int miny, maxy;

	miny = (int)(0.1*(float)altura);
	maxy = (int)(0.8*(float)altura);



	direita.resize(maxy-miny);
	esquerda.resize(maxy-miny);
	int aux;

	aux = 99999;
	for(i = 0; i<esquerda.size();i++)
	{
		esquerda[i].y = anchor.y+i+miny;
		direita[i].y = anchor.y+i+miny;
		esquerda[i].x = largura; 
		direita[i].x = -largura;

	}


	for(i=0;i<num_pontos;i++)
	{
		aux = rotated[i].y - anchor.y - miny;
		if(aux>=0 && aux < esquerda.size())
		{
			if(rotated[i].x < esquerda[aux].x)
			{
				esquerda[aux].x = rotated[i].x;
			}

			if(rotated[i].x > direita[aux].x)
			{
				direita[aux].x = rotated[i].x;
			}
		}
	}

	/*
	int x,y;
	Mat mostra(altura,largura,CV_8UC1);
	mostra = Scalar(0);
	for(i = 0; i< rotated.size();i++)
	{
		x = rotated[i].x-anchor.x;
		y = rotated[i].y-anchor.y;
		mostra.at<uchar>(Point(x,y)) = 120;
	}

	for(i = 0; i<esquerda.size();i++)
	{
		x = esquerda[i].x-anchor.x;
		y = esquerda[i].y-anchor.y;
		mostra.at<uchar>(Point(x,y)) = 255;

		x = direita[i].x-anchor.x;
		y = direita[i].y-anchor.y;
		mostra.at<uchar>(Point(x,y)) = 255;

	}
	imshow("mostra",mostra);
	*/

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



Cone::Cone()
{
	tamanho = 0.5;
}

void Cone::Posicao(int cols, float anguloH, int rows, float anguloV)
{
	float distancia, angulo;

	float a1,a2;

	angulo = (CV_PI/180.0)*( anguloH*(float)(cols/2 - centro.x))/((float)cols);
	//a1 = (CV_PI/180.0)*( anguloV*((float)rows/2 - ((float)inicio.y-0.5) ))/((float)rows);
	//a2 = (CV_PI/180.0)*( anguloV*((float)rows/2 - ((float)fim.y+0.5 )  ))/((float)rows);
	
	a1 = (CV_PI/180.0)*( anguloV*((float)rows/2 - ((float)inicio.y) ))/((float)rows);
	a2 = (CV_PI/180.0)*( anguloV*((float)rows/2 - ((float)fim.y )  ))/((float)rows);
	
	a1 = tan(a1-a2);
	//cout<<angulo<<endl;

	distancia = tamanho/a1;
	//cout<<distancia<<endl;



	//distancia = 0.16006 + 0.8647*distancia - 0.0086275*distancia*distancia;
	distancia = 0.31168+1.0495*distancia-0.018916*distancia*distancia;
	
	
	//float altura = (float)(fim.y-inicio.y)/(float)rows;
	
	//altura = tamanho/altura;
	
	//distancia = -0.034275 + 1.0516*altura - 0.014733*altura*altura - 0.00014726*altura*altura*altura;
	//distancia = -0.14065 + 1.1005*altura-0.01991*altura*altura;
	
	
	
	//distancia = tamanho/(tan(a1) - tan(a2) );

	//distancia *= (0.87-0.005*distancia);

	X = distancia*cos(angulo);
	Y = distancia*sin(angulo);

	//cout<<X<<"   "<<Y<<endl;

	//cout<<distancia<<"   "<<a2<<endl;


}
