#include "Kalman.hpp"

void Kalman::init(Mat x_inicial, Mat F_inicial, Mat P_inicial, Mat Q_inicial, Mat H_inicial, Mat R_inicial, Mat B_inicial)
{
	

	x_inicial.copyTo(x);	
	F_inicial.copyTo(F);

	B_inicial.copyTo(B);
	B_inicial.copyTo(b);

	P_inicial.copyTo(P);
	Q_inicial.copyTo(Q);
	H_inicial.copyTo(H);
	R_inicial.copyTo(R);

	y.create(H.rows,1,CV_32F);
	S.create(x.rows,x.rows,CV_32F);
	K .create(x.rows,y.rows,CV_32F);
	I = Mat::eye(P.cols,P.rows,CV_32F); 

	
}

void Kalman::init(Mat x_inicial, Mat F_inicial, Mat P_inicial, Mat Q_inicial, Mat H_inicial, Mat R_inicial)
{
	

	x_inicial.copyTo(x);	
	F_inicial.copyTo(F);


	P_inicial.copyTo(P);
	Q_inicial.copyTo(Q);
	H_inicial.copyTo(H);
	R_inicial.copyTo(R);

	y.create(H.rows,1,CV_32F);
	S.create(x.rows,x.rows,CV_32F);
	K .create(x.rows,y.rows,CV_32F);
	I = Mat::eye(P.rows,P.cols,CV_32F); 


	
}


void Kalman::predict(bool nonlinear)
{

	//x = F*x + B*u;
	P = (((F*P)*(F.t()) )+Q);
}


void Kalman::predict(Mat u)
{

	x = F*x + B*u;
	P = (((F*P)*(F.t()) )+Q);
}


void Kalman::predict()
{

	x = F*x;
	P = (((F*P)*(F.t()) )+Q);
}


void Kalman::update(Mat z)
{
	y = z-H*x;
	S = H*P*(H.t())+R;
	K = P*H.t()*(S.inv());
	x = x+K*y;

	P = (I-K*H)*P*((I-K*H).t())+ K*R*(K.t());


	//P = (I-K*H)*P;

}

void Kalman::timeF(float* f)
{
	int i;
	float* p;
	p = F.ptr<float>(0);
	int size = F.cols*F.rows;
	for(i=0;i<size;i++)
	{
		p[i] = f[i];
	}


}