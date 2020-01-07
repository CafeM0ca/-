#include <iostream>
#include <random>
#include <cstdlib>
using namespace std;


void generate(vector<int>& v) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(1,30);
	for(int i = 0; i < 10; i++) {
		v.push_back(dis(gen));
	}
}

int partition(vector<int>& v, int p, int r) {
	int rp = rand() % (r-p) + p;
	cout << "rp: " << rp << ", r: " << r << endl;
	swap(v[rp], v[r]);
		
	int i = p-1, j = p;

	while(j < r){
		if(v[j] < v[r]) { // 오름차순
			j++;
		}
		else {
			i++;
			swap(v[i], v[j]);
			j++;
		}
	}
	swap(v[r], v[i+1]);
	return i+1;
}

void quicksort(vector<int>& v, int p, int r) {
	if(p < r) {
		// q = pivot pos
		// 정렬
		int q = partition(v, p, r);

		// 작은쪽 분할
		quicksort(v, p, q-1);
		// 큰쪽 분할
		quicksort(v, q+1, r);
	}
}

int main() {
	srand(time(0));
	vector<int> v;
	for(int i = 0; i < 10; i++) {
		v.clear();
		generate(v);
		
		cout << "---before---\n";
		for(auto& _v : v) { 
			cout << _v << " ";
		}
		cout << endl << endl;

		quicksort(v, 0, v.size()-1);
		cout << "---after---\n";
		for(auto& _v : v) { 
			cout << _v << " ";
		}
	
		cout << "\n====================\n";
	}
	
	return 0;
}
