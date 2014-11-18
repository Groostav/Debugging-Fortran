#include <cstdlib>
#include <iostream>

using namespace std;

typedef double (*PointEvaluator)(int);

extern "C"{
	//oh nifty, VS generates this like its documentation...
	void pauseOptimization(bool*);

	//callback is (double*, int) -> double*
	void acceptCallback(PointEvaluator);
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

    PointEvaluator eval = [](int nCoords) -> double { 
		cout << "hello again from C++!" << endl;
		cout << "the C++ got the value " << nCoords << " for its input!" << endl;
		return 0;
	};

	cout << "passing in a func ptr! FOTRAN{" << endl;
	acceptCallback(eval);
	cout << "}" << endl;

	system("PAUSE");
}