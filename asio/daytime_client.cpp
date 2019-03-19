#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>
using namespace std;
using namespace boost::asio::ip;
int main(int argc, char *argv[])
{
	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: client <host>" << std::endl;
			return 1;
		}
		boost::asio::io_context io_context;		//asio에서 최소 1개 필요

		tcp::resolver resolver(io_context);		//tcp endpoints로 변환하기 위해. argument는 서버 이름
		tcp::resolver::results_type endpoints = resolver.resolve(argv[1], "daytime");

		tcp::socket socket(io_context);
		boost::asio::connect(socket, endpoints);
	
		std::string message;
		for(;;)
		{
			boost::array<char, 128> buf;
			boost::system::error_code error;
			getline(cin, message);
			//size_t len = socket.read_some(boost::asio::buffer(buf), error)//;
			boost::asio::write(socket, boost::asio::buffer(message), error);

			if(error == boost::asio::error::eof) break;
			else if (error) throw boost::system::system_error(error);

		}
	}
	catch(std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
