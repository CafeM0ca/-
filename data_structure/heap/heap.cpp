#include "heap.hpp"
#include <iostream>
using namespace std;
int main() {
	max_heap<int> heap;
	heap.insert(1);
	heap.print();
	heap.insert(6);
	heap.print();
	heap.insert(3);
	heap.print();
	heap.insert(2);
	heap.print();
	heap.insert(5);
	heap.print();
	heap.insert(13);
	heap.print();
	heap.insert(11);
	heap.print();
	heap.insert(9);
	heap.print();
	heap.insert(15);
	heap.print();
	heap.insert(17);
	heap.print();
	heap.remove(15);
	heap.print();


	cout << "\n" << "\n" << "heap sort!!!\n";
	heap.sort();
	heap.print();


	return 0;
}


template<typename type>
max_heap<type>::max_heap() {
	// 편의를 위해 안쓰는 데이터
	data.push_back(0);
}

template<typename type>
void max_heap<type>::insert(type d) {
	++this->len;
	data[this->len] = d;

	for(int idx = this->len; idx > 1; idx = get_parent_idx(idx)) {
		if(data[idx] < get_parent(idx)) break;
		swap(data[idx], data[get_parent_idx(idx)]);
	}
}

template<typename type>
void max_heap<type>::remove(type t) {
	if(len == 0) return;
	int t_idx = find(t);
	if(!t_idx) return;
	swap(data[t_idx], data[len]);
	this->len--;
	heapify(t_idx);
}

template<typename type>
void max_heap<type>::heapify(int idx){
	if(idx < 1) return;

	// 부모보다 작을 경우
	if(data[idx] >= get_left_child(idx) && data[idx] >= get_right_child(idx)) return;

	int bigger_idx = get_left_child(idx) > get_right_child(idx) ? get_left_child_idx(idx) : get_right_child_idx(idx);
	swap(data[idx], data[bigger_idx]);
	heapify(bigger_idx);
}

template<typename type>
int max_heap<type>::find(type t) {
	for(int i=1; i<=this->len; i++) {
		if(t == data[i]) return i;
	}
	return 0;
}

template<typename type>
void max_heap<type>::sort() {
	int heap_len = this->len;
	for(int i = this->len; i > 1; i--) {
		swap(data[i], data[1]);
		this->len--;
		heapify(1);
	}
	this->len = heap_len;
} // 힙 쏘트 3줄컷

template<typename type>
void max_heap<type>::print() {
	cout << "=====print heap=====\n";
	for(int i = 1; i <= this->len; i++) {
		cout << data[i] << ' ';
	}
	cout << '\n';
}

template<typename type>
int max_heap<type>::get_left_child_idx(int p_idx) {
	if(p_idx * 2 > this->len) return 0;
	return p_idx*2;
}

template<typename type>
int max_heap<type>::get_right_child_idx(int p_idx) {
	if(p_idx * 2+1 > this->len) return 0;
	return p_idx*2+1;
}

template<typename type>
int max_heap<type>::get_parent_idx(int p_idx) {
	if(p_idx < 0 || p_idx > this->len) return 0;
	return p_idx / 2;
}

template<typename type>
type max_heap<type>::get_left_child(int p_idx) {
	return data[get_left_child_idx(p_idx)];
}

template<typename type>
type max_heap<type>::get_right_child(int p_idx) {
	return data[get_right_child_idx(p_idx)];
}


template<typename type>
type max_heap<type>::get_parent(int p_idx) {
	return data[get_parent_idx(p_idx)];
}

template<typename type>
type max_heap<type>::get(type t) {
	return data[find(t)];
}

template<typename type>
size_t max_heap<type>::size() const{
	return this->len;
}

template<typename type>
type max_heap<type>::operator[](const int idx) {
	if(idx < 1 && idx > this->len) return data[0];

	return data[idx];
}
