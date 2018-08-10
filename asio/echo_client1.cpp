#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;
const string serverIP{ "127.0.0.1" };
const short port = 31400;

int main()
{
	boost::asio::io_context io_context;
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(serverIP), port);
	boost::asio::ip::tcp::socket socket(io_context);
	boost::system::error_code c_error;

	socket.connect(endpoint, c_error);
	if(c_error)
	{
		if(c_error == boost::asio::error::eof)
			cout << "disconnected" << endl;
		else
			cout << "error No." << c_error.value() << ", error message" << c_error.message() << endl;
		getchar();
		return 0;
	}
	cout << "Success server connection" << endl;
	for(int i = 0; i < 7; i++)
	{
		string buf;
		getline(cin, buf);
		boost::system::error_code error;
		socket.write_some(boost::asio::buffer(buf, buf.size()), error);
		cout << "send meesage: " << buf << endl;

		string r_buf;
		boost::system::error_code r_error;
		socket.read_some(boost::asio::buffer(r_buf), r_error);
		if(r_error)
		{
			if(r_error == boost::asio::error::eof)
				cout << "disconnected" << endl;
			else
				cout << "error No." << r_error.value() << ", error message" << r_error.message() << endl;
			break;
		}
		cout << "Say server: " << r_buf << endl;
	}
	if(socket.is_open())
	{
		socket.close();

	}
	cout << "close client" << endl;
	return 0;
}

