/*
 * 1.간단하게 서버를 열고 여러명의 클라이언트들을 접속시킨다.
 * 2. 클라이언트로부터 메시지를 받아 서버에 띄운다.
 * 3. 받은 메시지를 클라이언트들에게 뿌린다.
 */

#include <iostream>
#include <string>
#include <list>
#include <boost/asio>
using namespace std;
std::string make_daytime_string()
{
	using namespace std;
	time_t now = time(0);
	return ctime(&now);
}

class server
{
public:
	server(boost::asio::io_context& io_context, short port)
		: macceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
		socket_(io_context)
	{
		accept();
	}

private:
	void accept()
	{

	}

	void handle_accept(participant::shared_ptr<participant> new_participant,
			const boost::system::error_code& error)
	{
	}

	boost::asio::ip::tcp::acceptor acceptor_;
	// list participant
};

int main(int argc, char *argv[])
{
	try{
		if(argc != 2){
			std::cerr << "Usage:  chat_server <port> : <port>\n";
			return 1;
		}	
		boost::asio::io_context io_context;
		boost::asio::tcp::ip::endpoint endpoint		
		// do something 
		io_context.run();						// 이벤트 콜백이 끝날때까지 대기
	}
	catch(std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
	return 0;
}

