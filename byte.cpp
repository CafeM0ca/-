#include <iostream>
#include <cstddef>
int main()
{
	std::byte b{0x41};
	std::cout << static_cast<char>(b) << std::endl;
	return 0;
}
