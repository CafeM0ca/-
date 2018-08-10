#include <iostream>
#include <string>
#include <boost/asio.hpp>
using namespace std;

const string serverIP{ "127.0.0.1" };
const short port = 31400;

int main()
{
	boost::asio::io_context io_context;
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
	boost::asio::ip::tcp::acceptor acceptor(io_context, endpoint);
	boost::asio::ip::tcp::socket socket(io_context);

	acceptor.accept(socket);

	cout << "conect clinent" << endl;

	for(;;)
	{
		string buf;
		boost::system::error_code error;
		socket.read_some(boost::asio::buffer(buf), error);

		if(error)
		{
			if(error == boost::asio::error::eof)
				cout << "disconnected" << endl;
			else
				cout << "error No." << error.value() << ", error message: " << error.message() << endl;
			break;	
		}
		cout << "Say Clinent: " << buf << endl;
		string r_buf;
		boost::system::error_code r_error;

		getline(cin, buf);
		socket.write_some(boost::asio::buffer(buf, buf.size()), r_error);
		cout << "send message: " << buf << endl;

	}
	return 0;
}
