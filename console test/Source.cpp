#include <cstdlib>
#include <iostream>

using namespace std;

extern "C"{
	void pauseOptimization(bool);
}

int main()
{
	cout << "running!" << endl;
	system("PAUSE");

	pauseOptimization(true);
	cout << "did it!" << endl;
}