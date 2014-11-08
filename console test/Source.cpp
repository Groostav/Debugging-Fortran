#include <cstdlib>
#include <iostream>

using namespace std;

typedef double* (*PointEvaluator)(double*, int);

extern "C"{
	//oh nifty, VS generates this like its documentation...
	void pauseOptimization(bool*);

	//callback is (double*, int) -> double*
	void acceptCallback(bool, PointEvaluator);
}

int main()
{
	cout << "running!" << endl;
	system("PAUSE");

	cout << "passing in a boolean: FORTRAN{" << endl;
	bool aBool = true;
	pauseOptimization(&aBool);
	cout << "}" << endl;
	system("PAUSE");

	cout << "passing in a boolean and a NULL func ptr! FOTRAN{" << endl;
	acceptCallback(true, [](double* point, int nCoords) -> double* { 
		cout << "hello again from C++!" << endl;
		return NULL;
	});
	cout << "}" << endl;

	system("PAUSE");
}