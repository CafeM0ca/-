#include <iostream>
#include <random>

using namespace std;

int main()
{
	std::random_device rd;
	std::uniform_int_distribution<int> distribution(1,6);
	for(int i = 0; i < 10; i++)
		cout << distribution(rd)  << endl;
	return 0;
}
