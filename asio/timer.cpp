#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

class printer
{
public:
	printer(boost::asio::io_context& io)
		:strand_(io),
		timer1_(io, boost::asio::chrono::seconds(1)),
		timer2_(io, boost::asio::chrono::seconds(1)),
		count_(0)
	{
		timer2_.async_wait(boost::asio::bind_executor(strand_, boost::bind(&printer::print2,this)));
		timer1_.async_wait(boost::asio::bind_executor(strand_, boost::bind(&printer::print1,this)));
	}
	~printer()
	{
		std::cout << "Final count is " << count_ << std::endl;	
	}
	void print1()
	{
		if(count_ < 10)
		{
			std::cout << "Timer 1: " << count_ << std::endl;
			++count_;
			timer1_.expires_at(timer1_.expiry() + boost::asio::chrono::seconds(1));

			timer1_.async_wait(boost::asio::bind_executor(strand_, boost::bind(&printer::print1, this)));
		}
	}
	void print2()
	{
		if(count_ < 10)
		{
			std::cout << "Timer 2: " << count_ << std::endl;
			++count_;
			timer2_.expires_at(timer2_.expiry() + boost::asio::chrono::seconds(1));

			timer2_.async_wait(boost::asio::bind_executor(strand_, boost::bind(&printer::print2, this)));
		}
	}
private:
	boost::asio::io_context::strand strand_;
	boost::asio::steady_timer timer1_;
	boost::asio::steady_timer timer2_;
	int count_;
};
/*
void print(const boost::system::error_code&)
{
	std::cout << "Hello, world!" << std::endl;
}
*/
/*
void print(const boost::system::error_code&,
			boost::asio::deadline_timer *t, int& count)
{
	if(count < 5)
	{
		std::cout << count << "번째 타이머 호출" << std::endl;
		count++;
		t->expires_at(t->expires_at() _ boost::posix_time::seconds(1));
		t->async_wait(boost::bind(print, boost::asio::placeholders::error, t, &count));
	}
}
*/
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
	

	/*
	boost::asio::io_context io;
	int count = 0;
	boost::asio::deadline_timer t(io, boost::posix_time::second(1));
	t.async_wait(boost::bind(print, boost::asio::placeholders:;error, &t, &count));
	io.run();
	std::cout << "Final count is" << count << std::endl;
	*/

	boost::asio::io_context io;
	printer p(io);
	boost::thread t(boost::bind(&boost::asio::io_context::run, &io));
	io.run();
	t.join();
	return 0;
}
