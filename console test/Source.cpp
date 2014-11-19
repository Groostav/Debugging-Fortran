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
	cout << "c++: running... "
		#if _M_IX86
		<< "is IX86, "
		#else
		<< "is not IX86"
		#endif
		#if _M_AMD64 
			<< "and is AMD64, "
		#else
			<< "and is NOT AMD64, "
		#endif	
		#if _WIN64
			<< "and is WIN64"
		#else 
			<< "and is NOT WIN64"
		#endif
			<< endl;
	system("PAUSE");

	cout << "c++: passing in a boolean: " << endl;
	bool aBool = true;
	pauseOptimization(&aBool);
	cout << "c++: fortran code has returned." << endl;
	system("PAUSE");

	
	cout << "c++: passing in a func ptr! " << endl;
	acceptCallback([](int integer, double aDouble) -> double { 
		cout << "c++: hello again from C++!" << endl;
		cout << "c++: got integer:" << integer << "!!" << endl;
		cout << "c++: got double:" << aDouble << "!!" << endl;
		return 42;
	});
	cout << "c++: fortran code has returned." << endl;
	system("PAUSE");

	cout << "c++: building parameter objects..." << endl;
	ArrayEvaluator arrayEval = [](int integer, double aDouble, double* doubleArray) -> double {
		cout << "c++: hello again from C++!" << endl;
		cout << "c++: got integer:" << integer << "!!" << endl;
		cout << "c++: got double:" << aDouble << "!!" << endl;
		cout << "c++: got doubleArray: 0x" << doubleArray << " {" 
			<< doubleArray[0] << ", " 
			<< doubleArray[1] << "..." 
			<< "}" << "!!" << endl;
		return 42;
	};
	SomeStruct* someStruct = new SomeStruct();
	someStruct->someInt = 10;
	someStruct->someDouble = 20.0;
	cout << "c++: passing in a func ptr that takes an array! FORTRAN{ " << endl;
	acceptArrayCallback(arrayEval, someStruct);
	cout << "c++: fortran code returned" << endl;

	cout << "Done!!!" << endl;
	system("PAUSE");
}