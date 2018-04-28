/*
삽입 정렬
1.데이터가 있다. 데이터는 두 개 이상이다.

2.두번째 요소부터 마지막 요소까지 돈다.

3.n번째 요소는 n부터 1까지 돈다.

4.만약 n번째 요소가 n-1번째 요소보다 크면 그만 돈다.

5.삽입으로 인해 요소들이 밀린다.
*/
#include <iostream>
using namespace std;

inline void ShowArray(int arr[],int);

void InsertSort(int arr[],int len)
{
	cout << "arr[0]: " << arr[0] << endl;
	cout << "arr[1]: " << arr[1] << endl;
	cout << "arr[2]: " << arr[2] << endl;
	cout << "len: " << len << endl;
	for(int i=1;i<len;i++)
	{
		for(int j=i;j>0;j--) //j는 i-1번째 원소
		{
			if(arr[j-1] < arr[j]) break;
			ShowArray(arr,len);
			int remember = arr[j-1];
			arr[j-1] = arr[j];
			arr[j] = remember;
		}
	}
	ShowArray(arr,len);
}

inline void ShowArray(int arr[],int len) 
{
	cout << "array: ";
	for(int i=0;i<len;i++)
		cout << arr[i] << ' ';
	cout << '\n';
}
int main()
{
	int arr[10000]{'\0',};
	int n;
	cout << "how many? : ";
	cin >> n;
	for(int i=0;i<n;i++)
	{
		int num;
		cin >> num;
		arr[i] = num;
	}
	ShowArray(arr,n);
	InsertSort(arr,n);
	return 0;
}
