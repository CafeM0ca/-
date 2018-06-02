#include <iostream>
using namespace std;

auto factorial(int n) 
{
	static int sum = 1;
	if(n == 1){
		int result = sum;
		sum = 0;
		return result;
	}
	sum *= n;
	factorial(n-1);
}
int main()
{
	cout << factorial(5) << endl;
	return 0;
}
