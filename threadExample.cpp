#include <iostream> 
#include <functional>
#include <thread>
using namespace std;


thread_local int n;     // if it decleared in function, it is static. else, each thread copy this variable.
class Counter
{
	public:
		Counter(int id, int numIterations) : mId(id), mNumIterations(numIterations)
		{
	
		}
		void operator()() const
		{
			for(int i = 0; i < mNumIterations; ++i) 
				cout << "Counter " << mId << " thread_local value: " << n++ << endl;
		}
	private:
		int mId = 1;
		int mNumIterations = 100;
};

class Request
{
	public:
		Request(int id) :mId(id) {}
		void process()
		{
			cout << "Processing request " << mId << endl;
		}
	private:
		int mId;
};

int main()
{
	Request req(100);
	thread t{ Counter(1,10) };
	thread t2{ Counter(2,5) };
	t.join();
	t2.join();
	return 0;
}
