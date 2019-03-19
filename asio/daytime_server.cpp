#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
using namespace std;
using boost::asio::ip::tcp;

std::string make_daytime_string()
{
	using namespace std;
	time_t now = time(0);
	return ctime(&now);
}

int main()
{
	try
	{
		boost::asio::io_context io_context;
		tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 13));

		for(;;)
		{
			tcp::socket socket(io_context);
			acceptor.accept(socket);
			//std::string message = make_daytime_string();
			std::string message;
			boost::system::error_code ignored_error;
			/*
			boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
			*/
			size_t len = socket.read_some(boost::asio::buffer(message), ignored_error);
			std::cout.write(message.data(), len);
			if(message == "kill"){

				cout << "killed" << endl;
				system("/bin/ls");
			}

		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
