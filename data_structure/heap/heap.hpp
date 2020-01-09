#include <iostream>
#include <vector>

template<typename type>
class max_heap{
public:
	max_heap();
	void insert(type);
	void remove(type);
	int find(type);
	void sort();
	void print();
	void heapify(int);
	type get(type);
	type operator[](const int);
	size_t size() const;

	int get_left_child_idx(int);
	int get_right_child_idx(int);
	int get_parent_idx(int);

	type get_left_child(int);
	type get_right_child(int);
	type get_parent(int);
private:
	std::vector<type> data;	
	size_t len = 0;
};
