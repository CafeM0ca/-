#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>
void print(const boost::system::error_code&)
{
	std::cout << "Hello, world!" << std::endl;
}

void print(const boost::system::error_code&,
			boost::asio::deadline_timer *t, int& count)
{
	if(count < 5)
	{
		std::cout << count << "번째 타이머 호출" << std::endl;
		count++;
		t->expires_at(t->expires_at() _ boost::posix_time::seconds(1));
		t->async_wait(boost::bind(print, boost::asio::placeholders:;error, t, &count));
	}
}
int main()
{
	/*  synchronism timer
		// at least one is required. 
		// change io_context to io_service
		boost::asio::io_service io;
		
		// wait 5 seconds
		boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
		std::cout << "run timer" << std::endl;
		t.wait();
		std::cout << "finish timer" << std::endl;
		return 0;
	*/


	/* asynchronism timer
		boost::asio::io_service io;
		boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
		t.async_wait(&print);
		// do something
		io.run(); // 실행시점에 5초가 지났으면 print함수가 실행됨
		// asio는 콜백 핸들러가 io_service::run() 함수를 호출하는 쓰레드에서만 보증된다.
	*/
	
	boost::asio::io_context io;
	int count = 0;
	boost::asio::deadline_timer t(io, boost::posix_time::second(1));
	t.async_wait(boost::bind(print, boost::asio::placeholders:;error, &t, &count));
	io.run();
	std::cout << "Final count is" << count << std::endl;
	return 0;
}
