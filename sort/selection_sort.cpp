#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


void printVector(vector<int>& v) 
{
	for(auto& i : v)
		cout << i << ' ';
	cout << endl;
}

void selectionSort(vector<int>& v)
{
	for(vector<int>::iterator iter1 = v.begin();iter1 != v.end() - 1;iter1++){
		vector<int>::iterator minValue = min_element(iter1,v.end());
		swap(*iter1,*minValue);
	}
}

int main()
{
	vector<int> v;

	for(int i=9;i>=0;i--)
		v.push_back(i);	

	printVector(v);
	selectionSort(v);	
	printVector(v);
	return 0;
}
