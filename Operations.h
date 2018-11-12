#ifndef Operations_h
#define Operations_h
#include "itkVector.h"
#include "itkMatrix.h"
template<typename M0, typename M1>  M0 Summation(M1 A,int ra,int ca, int rc);
template<typename M0, typename TD> M0 PowElementMatrix(M0 A,int ra,int ca, TD m);
template<typename M0, typename M1, typename M2> M0 Multiply(M1 A, M2 B, int ra,int ca,int cb);
template<typename M0, typename M1, typename M2> M0 ElementToElementDivision(M1 A, M2 B,int ra,int ca);
template<typename M0, typename M1,typename M2> M0 Distance(M1 A, M2 B,int ra,int ca,int cluster, int c);

template<typename M0, typename M1>
inline M0 Summation(M1 A, int ra, int ca, int rc)
{
	M0 D;
	if (rc == 1)
	{

		for (unsigned int row = 0; row < ra; ++row)
		{
			D[row] = 0;
			for (unsigned int col = 0; col < ca; ++col)
			{
				D[row] = D[row] + A(row, col);
			}

		}
	}
	else if (rc == 2)
	{
		for (unsigned int col = 0; col < ca; ++col)
		{
			D[col] = 0;
			for (unsigned int row = 0; row < ra; ++row)
			{
				D[col] = D[col] + A(row, col);
			}


		}
	}
	return D;
}

template<typename M0, typename TD>
inline M0 PowElementMatrix(M0 A, int ra, int ca, TD m)
{
	M0 D;
	for (unsigned int row = 0; row < ra; ++row)
	{
		for (unsigned int col = 0; col < ca; ++col)
		{
			D(row, col) = pow(A(row, col), m);
		}
	}
	return D;
}

template<typename M0, typename M1, typename M2>
inline M0 Multiply(M1 A, M2 B, int ra, int ca, int cb)
{
	M0 product;
	
	for (int row = 0; row < ra; row++) {
		for (int col = 0; col < cb; col++) {
			product(row, col) = 0;
			for (int inner = 0; inner < ca; inner++) {
				product(row, col) += A(row, inner) * B(inner, col);
			}

		}

	}
	return product;
}

template<typename M0, typename M1, typename M2>
inline M0 ElementToElementDivision(M1 A, M2 B, int ra, int ca)
{
	M0 Mproduct;

	for (int row = 0; row < ra; ++row)
	{
		for (int col = 0; col < ca; ++col)
		{
			Mproduct(row, col) = A(row, col) / B(row, col);
		}
	}
	
	return Mproduct;
}

template<typename M0, typename M1,typename M2>
inline M0 Distance(M1 A, M2 B, int ra,int ca, int cluster, int c)
{
	M0 dist;
	if (c == 1)
	{
		for (int i = 0; i < cluster; i++)
		{
			for (int row = 0; row < ra; ++row)
			{

				dist(i,row) = abs(A(i, 0) - B(row, 0));

			}
		}
	}
	else if (c == 2)
	{
		for (int i = 0; i < cluster; i++)
		{
			for (int row = 0; row < ra; ++row)
			{
				dist(i,row) = 0;
				for (int col = 0; col < ca; ++col)
				{
					
					dist(i,row) = dist(i, row) + pow((A(i, col) - B(row, col)), 2);
					
				}
				dist(i, row) = sqrt(dist(i, row));
				
			}
		}
		
	}
	return dist;
}



#endif