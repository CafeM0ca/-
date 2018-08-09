#include <iostream>
#include <vector>
using namespace std;

vector<int>& merge(vector<int>& v1, vector<int>& v2){
	vector<int> temp;
	while (!v1.empty() || !v2.empty()) {
		if (v1.front() > v2.front()) {
			temp.push_back(v1.front());
			v1.erase(v1.begin());
		}
		else {
			temp.push_back(v2.front());
			v2.erase(v2.begin());
		}
	}
	while (!v1.empty()) {
		temp.push_back(v1.front());
		v1.erase(v1.begin());
	}
	while (!v2.empty()) {
		temp.push_back(v2.front());
		v2.erase(v2.begin());
	}
	cout << "------------merged vector-----------" << endl;
	for (auto i : temp)
		cout << i << " ";
	cout << endl;
	return temp;
}
void split(vector<int>& v)
{
	if (v.size() >= 2) {
		vector<int> splied1, splied2;
		// divide two vector	
		for (int i = 0; i < v.size(); i++) {
			if (i < v.size() / 2) {
				splied1.push_back(v.at(i));
			}
			else {
				splied2.push_back(v.at(i));
			}
		}
		cout << "splied1-size: " << splied1.size() << endl;
		for (auto i : splied1)
			cout << i << " ";
		cout << endl;

		cout << "splied2-size: " << splied1.size() << endl;
		for (auto i : splied2)
			cout << i << " ";
		cout << endl;

		cout << v.size() << "size vector before split" << endl;
		split(splied1); // repeat 
		split(splied2); // repeat
		v = merge(splied1, splied2); // merge
	}
	else {
		cout << "single or none vector" << endl;
	}
}

int main()
{
	vector<int> v;
	v.push_back(5);
	v.push_back(2);
	v.push_back(7);
	v.push_back(1);
	v.push_back(2);
	v.push_back(4);
	v.push_back(3);
	cout << "unsortted vector" << endl;
	for (auto i : v)
		cout << i << " ";
	cout << endl;
	split(v);
	return 0;
}