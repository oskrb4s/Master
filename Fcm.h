#pragma once
#include "Operations.h"
#include "itkVector.h"
#include "itkMatrix.h"
#include <ctime>
#include <stdlib.h>
template<typename M1, int cluster_n = 2,int data_n = 2, int xdata = 2>
class Fcm
{
public:
	Fcm(M1 _data, double _m);
	~Fcm();
	void StartUint();
	void CalculateClusterCenter();
	void UpdateU();
	
	using MulData = itk::Matrix<double, cluster_n, xdata>;
	using M0 = itk::Matrix<double, cluster_n, data_n>;
	using  V1 = itk::Vector<double, data_n>;
	using  V2 = itk::Vector<double, cluster_n>;
	M1 GetCluster();
	M0 membership_mat;
	M1 data;
	double m;
	V1 Vec;
	private:
		MulData Dat;
		MulData Center;
		V2 VecCol;
		V1 VecRow;
		double FunObj;
		

};

