#include <iostream>
#include <boost/asio>

/*
 * 서버는 클라이언트들을 관리한다.
 * 첫번째 목표는 하나의 방을 만들고 여기에 클라이언트를 접속한다.
 *
 * 서버작동과정
 * 1. 소켓생성
 * 2. IP, PORT 설정 
 * 3. 접속대기
 * 4. 메시지 교환
 * 5. 종료
 * 6. 소켓제거
 */

class server
{
	:wq
}

int main(int argc, char *argv[])
{
	try{
		if(argc != 2){
			std::cerr << "Usage:  chat_server <port> : <port>\n";
			return 1;
		}	

		boost::asio::io_context io_context;

		// do something 
	
	}
	catch(std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
	return 0;
}

