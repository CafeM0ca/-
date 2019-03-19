// g++ -o queue queue.cpp -std=c++17

#include <iostream>
#include <cstring>
using namespace std;

template <typename TYPE>
class queue{
public:
	queue(){ m_data = new TYPE[m_max_len]; }
	~queue() { safe_delete(); }
	void push(TYPE);
	void pop();
	bool empty() const;
	void swap(queue<TYPE>&);
	TYPE top() const;
	inline auto size() const { return m_size; }

//	template <typename Friend>											
//	friend ostream& operator<<(ostream& os, const queue<Friend>&);						// ostream 객체는 queue<Friend> type에 접근 가능
	//friend ostream& operator<<(ostream& os, const queue<TYPE>&);						// can't
private:
	void safe_delete();
	void allocate();
	TYPE * m_data = nullptr;	

	// member variable
	size_t m_size= 0;
	size_t m_max_len = 8;
};
/////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	queue<int> s1, s2;
	cout << "s1 size: " << s1.size() << endl;
	cout << "s1 empty: " << s1.empty() << endl;

	s1.push(10);
	cout << "s1 top: " << s1.top() << endl;
	cout << "s1 size: " << s1.size() << endl;
	cout << "s1 empty: " << s1.empty() << endl;

	s1.push(20);
	s1.push(30);
	cout << "s1 size: " << s1.size() << endl;
	cout << "s2 size: " << s2.size() << endl;
	

	cout << "s1 s2 swap" << endl;


	s1.swap(s2);

	cout << "s1 size: " << s1.size() << endl;
	cout << "s2 size: " << s2.size() << endl;
	cout << "s2 empty: " << s2.empty() << endl;
	
	s2.push(50);
	cout << "s2 top: " << s2.top() << endl;
	cout << "s2 size: " << s2.size() << endl;
	cout << "s1 size: " << s1.size() << endl;


	cout << "---s1---" << endl;
	while(!s1.empty()){
		cout << s1.top() << endl;
		s1.pop();
	}
	cout << "---s2---" << endl;
	while(!s2.empty()){
		cout << s2.top() << endl;
		s2.pop();
	}

	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////// */
template <typename TYPE>
void queue<TYPE>::push(TYPE data) {
	if(m_size == m_max_len){
		allocate();	
	}	
	m_data[m_size++] = data;
}

template <typename TYPE>
void queue<TYPE>::pop(){
	if(size() > 0){
		m_size--;
		if(m_size < m_max_len / 2){
			allocate();
		}
	}
		
}

template <typename TYPE>
bool queue<TYPE>::empty() const{
	if(size() == 0) return true;
	else			return false;
}

template <typename TYPE>
TYPE queue<TYPE>::top() const{
	try{
		return m_data[m_size-1];
	}
	catch(exception& e){
		cerr << "Error: " << e.what() << endl;
	}
}

template <typename TYPE>
void queue<TYPE>::swap(queue<TYPE>& s){
	/*
	cout << "rhs addr" << hex << s.m_data << endl;
	cout << "lhs addr" << m_data << endl;
	*/

	TYPE *temp_data = s.m_data;
	s.m_data = m_data;
	m_data = temp_data;

	/*
	cout << "rhs addr" << s.m_data << endl;
	cout << "lhs addr" << m_data << dec << endl;
	*/

	auto temp_mml = s.m_max_len;
	s.m_max_len = m_max_len;
	m_max_len = temp_mml;

	auto temp_size = s.m_size;
	s.m_size = m_size;
	m_size = temp_size;

}	

template <typename TYPE>
void queue<TYPE>::safe_delete() { 
	if(m_data != nullptr){
		delete m_data;
		m_data = nullptr;
	}
}

template <typename TYPE>
void queue<TYPE>::allocate(){
	TYPE *temp = nullptr;
	if(m_size < m_max_len / 2) {
		m_max_len /= 2;
		temp = new TYPE[m_max_len];	
	}	
	else {
		m_max_len *= 2;
		temp = new TYPE[m_max_len];	
	}		

	memcpy(temp, m_data, sizeof(&m_data[0]) * m_size);
	safe_delete();
	m_data = temp;
	temp = nullptr;
}


