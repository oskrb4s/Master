#include "Fcm.h"
template<typename M1, int cluster_n = 2, int data_n = 2, int xdata = 2>
inline Fcm<M1, cluster_n , data_n, xdata>::Fcm(M1 _data, double _m)
{
	m = _m;
	data = _data;
	
}
template<typename M1, int cluster_n = 2, int data_n = 2, int xdata = 2>
inline Fcm<M1, cluster_n, data_n,xdata>::~Fcm()
{
}
template<typename M1, int cluster_n = 2, int data_n = 2, int xdata = 2>
inline void Fcm<M1, cluster_n, data_n,xdata>::StartUint()
{
	
	srand(time(NULL));
	M0  B;
	for (unsigned int row = 0; row < cluster_n; ++row)
	{
		for (unsigned int col = 0; col < data_n; ++col)
		{

			membership_mat(row, col) = abs(rand());

		}
	}
	Vec = Summation<V1, M0>(membership_mat, cluster_n, data_n, 2);
	for (unsigned int row = 0; row < cluster_n; ++row)
	{
		for (unsigned int col = 0; col < data_n; ++col)
		{

			B(row, col) = Vec[col];

		}
	}
	membership_mat = ElementToElementDivision<M0, M0, M0>(membership_mat, B, cluster_n, data_n);
		
	
}

template<typename M1, int cluster_n, int data_n, int xdata = 2>
void Fcm<M1, cluster_n, data_n,xdata>::CalculateClusterCenter()
{
	M0 pw;
	MulData aux;
	pw = PowElementMatrix<M0, double>(membership_mat,cluster_n,data_n,m);
	Dat = Multiply<MulData, M0, M1>(pw, data, cluster_n, data_n, xdata);
	VecCol = Summation<V2, M0>(pw, cluster_n, data_n, 1);
	for (unsigned int row = 0; row < cluster_n; ++row)
	{
		for (unsigned int col = 0; col < xdata; ++col)
		{

			aux(row, col) = VecCol[row];

		}
	}
		
	Center = ElementToElementDivision<MulData, MulData, MulData>(Dat, aux, cluster_n, xdata);
	//std::cout << "resveddd" << Center << std::endl;
	
	
}

template<typename M1, int cluster_n, int data_n, int xdata>
void Fcm<M1, cluster_n, data_n, xdata>::UpdateU()
{
	double p = -2 / (m-1); 
	M0 d;
	M0 Tem;
	M0 aux;
	M0 pwdTem1;
	M0 pwUTem2,res;
	d = Distance<M0, MulData, M1>(Center, data,data_n, xdata, cluster_n, 2);
	Tem = PowElementMatrix<M0, double>(d, cluster_n, data_n, p);
	pwdTem1 = PowElementMatrix<M0, double>(d, cluster_n, data_n, 2);
	pwUTem2 = PowElementMatrix<M0, double>(membership_mat, cluster_n, data_n, m);
	res = Multiply<M0, M0, M0>(pwdTem1, pwUTem2, cluster_n, data_n, data_n);
	V1 VV = Summation<V1, M0>(res, cluster_n, data_n, 2);
	FunObj = 0;
	for (int i = 0; i < data_n; i++)
	{
		FunObj = FunObj + VV[i];

	}
	std::cout << "funob" << FunObj << std::endl;
	VecRow = Summation<V1, M0>(Tem, cluster_n, data_n, 2);
	for (int i = 0; i < cluster_n; i++)
	{
		for (int j = 0; j < data_n; j++)
		{
			aux(i, j) = VecRow[j];
		}

	}
	membership_mat = ElementToElementDivision<M0, M0, M0>(Tem, aux, cluster_n, data_n);
	//std::cout << "dd" << membership_mat << std::endl;
}

template<typename M1, int cluster_n, int data_n, int xdata>
M1 Fcm<M1, cluster_n, data_n, xdata>::GetCluster()
{
	V1 DataGet;
	M1 D;
	
	double mayor = 0;
	int rowM = 0;
	for (int col = 0; col < data_n; col++)
	{
		mayor = 0; 
		rowM = 0;

		for (int row = 0; row < cluster_n; row++)
		{
			
			if (membership_mat(row,col) > mayor)
			{
				mayor = membership_mat(row, col);
				rowM = row;

			}
		}
		
		DataGet[col]= rowM +1;

	}
	
	for (int i = 0; i < data_n; i++)
	{
		for (int j = 0; j < xdata; j++)
		{
			D(i, j) = DataGet[i];
		}

	}
	return D;
}
