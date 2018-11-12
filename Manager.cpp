#include "Manager.h"
Manager::Manager()
{
}

Manager::~Manager()
{
}
int main()
{
	unsigned t0, t1;
	const int N_cluster = 4;
	const int N_Data = 10;
	const int NCol = 2;
	const int m = 2;
	using Datos = itk::Matrix<double, N_Data, NCol>;
	Datos D_;
	D_(0, 0) = 0.218959190000000;
	D_(1, 0) = 0.679296410000000;
	D_(2, 0) = 0.830965350000000;
	D_(3, 0) = 0.0534616350000000;
	D_(4, 0) = 0.686772710000000;
	D_(5, 0) = 0.0919648910000000;
	D_(6, 0) = 0.653918960000000;
	D_(7, 0) = 0.701190590000000;
	D_(8, 0) = 0.910320830000000;
	D_(9, 0) = 0.736081880000000;
	D_(0, 1) = 0.719711080000000;
	D_(1, 1) = 0.313898370000000;
	D_(2, 1) = 0.479039930000000;
	D_(3, 1) = 0.779314850000000;
	D_(4, 1) = 0.522195680000000;
	D_(5, 1) = 0.714057610000000;
	D_(6, 1) = 0.166317870000000;
	D_(7, 1) = 0.422224000000000;
	D_(8, 1) = 0.318835530000000;
	D_(9, 1) = 0.457606850000000;
	Fcm<Datos, N_cluster, N_Data, NCol> a(D_, m);
	t0 = clock();
	a.StartUint();
	for (int i = 0; i < 100; i++)
	{
		a.CalculateClusterCenter();
		a.UpdateU();
	}
	std::cout << "Exec " << a.GetCluster() << std::endl;
	t1 = clock();
	double time = (double(t1 - t0) / CLOCKS_PER_SEC);
	std::cout << "Execution Time: " << time << std::endl;
	system("pause");
	return 0;
}