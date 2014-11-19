#include <cstdlib>
#include <iostream>

using namespace std;

extern "C"{

	//TYPE, BIND(C) :: SomeStruct
    //    INTEGER(C_INT) :: someInt
    //    REAL(C_DOUBLE) :: someDouble
    //END TYPE
	struct SomeStruct{
		int someInt;
		double someDouble;
	};

	typedef double (*NumEvaluator)(int, double);
	typedef double (*ArrayEvaluator)(int, double, double*);

	//oh nifty, VS generates this like its documentation...
	void pauseOptimization(bool*);

	//callback is (double*, int) -> double*
	void acceptCallback(NumEvaluator);

	void acceptArrayCallback(ArrayEvaluator, SomeStruct*);
}

int main()
{
	cout << "running!" << endl;
	cout 
		#if _M_IX86
		<< "is _M_IX86, "
		#else
		<< "is not _M_IX86"
		#endif
		#if _M_AMD64 
			<< "and is _M_AMD64, "
		#else
			<< "and is NOT _M_AMD64, "
		#endif	
		#if _WIN64
			<< "and is _WIN64"
		#else 
			<< "and is NOT _WIN64"
		#endif
			<< endl;
	system("PAUSE");

	cout << "passing in a boolean: FORTRAN{" << endl;
	bool aBool = true;
	pauseOptimization(&aBool);
	cout << "}" << endl;
	system("PAUSE");

	
	cout << "passing in a func ptr! FORTRAN{" << endl;
	acceptCallback([](int integer, double aDouble) -> double { 
		cout << "hello again from C++!" << endl;
		cout << "got integer:" << integer << "!!" << endl;
		cout << "got double:" << aDouble << "!!" << endl;
		return 42;
	});
	cout << "}" << endl;
	system("PAUSE");

	cout << "building parameter objects..." << endl;
	ArrayEvaluator arrayEval = [](int integer, double aDouble, double* doubleArray) -> double {
		cout << "hello again from C++!" << endl;
		cout << "got integer:" << integer << "!!" << endl;
		cout << "got double:" << aDouble << "!!" << endl;
		cout << "got doubleArray: 0x" << doubleArray << " {" 
			<< doubleArray[0] << "," 
			<< doubleArray[1] << "..." 
			<< "}" << "!!" << endl;
		return 42;
	};
	SomeStruct* someStruct = new SomeStruct();
	someStruct->someInt = 10;
	someStruct->someDouble = 20.0;
	cout << "passing in a func ptr that takes an array! FORTRAN{ " << endl;
	acceptArrayCallback(arrayEval, someStruct);
	cout << "}" << endl;

	cout << "Done!!!" << endl;
	system("PAUSE");
}