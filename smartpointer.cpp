#include <iostream>
#include <memory>


int main(){
	// unique ptr
	std::unique_ptr<char> ch = std::make_unique<char>('c');
	auto a = std::make_unique<int>(1);
	std::cout << "ch: " << *ch << std::endl;
	std::cout << "a: " << *a << std::endl;

	/*
	decltype(a) ptr = a;		// compile error 
	std::cout << "a: " << *a << std::endl;
	*/

	std::shared_ptr<int> num = std::make_shared<int>(1);
	std::cout << "num: " << *num << std::endl;
	std::cout << "num reference count : " << num.use_count() << std::endl;
	std::shared_ptr<int> nptr = num;
	std::cout << "nptr: " << *nptr<< std::endl;
	std::cout << "num reference count : " << num.use_count() << std::endl;
	std::cout << "nptr reference count : " << nptr.use_count() << std::endl;


	{
		std::shared_ptr<int> nptr2 = num;
		std::cout << "scope in" << std::endl << std::endl;;
		std::cout << "nptr2: " << *nptr2 << std::endl;
		std::cout << "num reference count : " << num.use_count() << std::endl;
		std::cout << "nptr reference count : " << nptr.use_count() << std::endl;
		std::cout << "nptr2 reference count : " << nptr2.use_count() << std::endl;
	}

	// reference count down. automatically deleted.
	std::cout << "scope out" << std::endl << std::endl;;
	std::cout << "num reference count : " << num.use_count() << std::endl;
	std::cout << "nptr reference count : " << nptr.use_count() << std::endl;
	return 0;
}
