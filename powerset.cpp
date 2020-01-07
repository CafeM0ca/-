#include <iostream>
#include <array>
using namespace std;

array<char, 6> data = { 'a', 'b', 'c', 'd', 'e', 'f' };
int n = data.size();
bool include[6];
void powerset(int k) {
	if(k==n) {
		for(int i = 0; i < n; i++){
			if(include[i]) 
				cout << data[i] << " ";
		}
		cout << endl;
		return;
	}

	include[k] = false;
	powerset(k+1);
	include[k] = true;
	powerset(k+1);
}

int main()
{
	powerset(0);
	return 0;
}
