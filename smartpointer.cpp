#include <iostream>
#include <memory>


int main(){
	// unique ptr
	std::unique_ptr<char> ch = std::make_unique<char>('c');
	auto a = std::make_unique<int>(1);
	std::cout << "ch: " << *ch << std::endl;
	std::cout << "a: " << *a << std::endl;

	decltype(a) ptr = a;		// compile error 
	std::cout << "a: " << *a << std::endl;
	return 0;
}
