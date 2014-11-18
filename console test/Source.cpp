#include <cstdlib>
#include <iostream>

using namespace std;

typedef double (*PointEvaluator)(int, double);

extern "C"{
	//oh nifty, VS generates this like its documentation...
	void pauseOptimization(bool*);

	//callback is (double*, int) -> double*
	void acceptCallback(PointEvaluator);
}

int main()
{
	cout << "running!" << endl;
	cout << 
#if _M_AMD64
	"is _M_AMD64, "
#else
	"is not _M_AMD64, "
#endif
	<<
#if _WIN64
	"is _WIN64"
#else 
	"is not _WIN64"
#endif
	<< endl;
	system("PAUSE");

	cout << "passing in a boolean: FORTRAN{" << endl;
	bool aBool = true;
	pauseOptimization(&aBool);
	cout << "}" << endl;
	system("PAUSE");

    PointEvaluator eval = [](int integer, double aDouble) -> double { 
		cout << "hello again from C++!" << endl;
		cout << "got integer:" << integer << "!!" << endl;
		cout << "got double:" << aDouble << "!!" << endl;
		return 0;
	};

	cout << "passing in a func ptr! FOTRAN{" << endl;
	acceptCallback(eval);
	cout << "}" << endl;

	system("PAUSE");
}