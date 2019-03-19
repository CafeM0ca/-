#include <iostream>
#include <vector>
#include <random>
using namespace std;

vector<int> temp;

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v){
	for(const auto& i : v){
		os << i << " ";
	}
	os << "\n";
	return os;
}
void sort(vector<int>& v, int left, int right){	
	//cout << "range of index ";
	//for(int i = left; i <= right; i++)
		//cout << v[i] << " ";
	//cout << endl;
	
	int mid = (left+right) / 2;
	int itr1 = left, itr2 = mid+1;
	while(itr1 <= mid || itr2 <= right){
		if(itr1 != mid+1 && itr2 != right+1){
			if(v[itr1] > v[itr2]){
				temp.push_back(v[itr1]);
				itr1++;
			}	
			else{
				temp.push_back(v[itr2]);
				itr2++;
			}
		}
		else if(itr1 == mid+1){						// 왼쪽 인덱스가 정렬이 완료되었을 때
			temp.push_back(v[itr2]);
			itr2++;
		}
		else if(itr2 == right+1){				// 오른쪽 인덱스가 정렬이 완료되었을 때
			temp.push_back(v[itr1]);
			itr1++;
		}
	}

	// v 에 temp대입
	for(int i = 0; i < temp.size(); i++){
		v.at(i+left) = temp[i];
	}

	//cout << "temp: " << temp << endl;
}
void merge_sort(vector<int>& v, int left, int right){
	static int num = 0;
	int mid;
	if(left < right){
		mid = (left + right) / 2;
		
		//cout << "go in left~mid" << endl;
		merge_sort(v, left, mid);
		//cout << "go in mid+1~right" << endl;
		merge_sort(v, mid+1, right);
	}
	//cout << num++ << " of sorting" << endl;
	//cout << "left: " << left << " , right: " << right << endl;
	sort(v, left, right);
}
int main()
{
	vector<int> v;
	random_device rd;
	mt19937_64 rnd(rd());
	uniform_int_distribution<int> range(1,100);
	int n;
	cin.tie(0);
	cin.sync_with_stdio(false);
	cin >> n;
	for(int i = 0; i < n; i++){
		int num;
		cin >> num;
		//v.push_back(range(rnd));	
		v.push_back(num);
	}

	//cout << "before sorting vector" << endl;
	for(const auto& i : v)
		//cout << i << " ";
	//cout << "\n" << "\n";

	//cout << "merge sort!--------------------------" << endl;
	merge_sort(v, 0, n-1);

	//cout << "after sorting vector" << endl;
	for(const auto& i : v)
		cout << i << endl;
	//cout << "\n";
	return 0;
}
