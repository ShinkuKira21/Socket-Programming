#include <iostream>
#include <thread>
#include <sstream>
#include <vector>
#include <mutex>
#include <future>
#include <random>

namespace E1
{
	void GetFromThreadedFunction(std::promise<std::string>& returnPromise)
	{
		std::this_thread::sleep_for(std::chrono::seconds(10));
		returnPromise.set_value("Hello from threaded function");
		std::this_thread::sleep_for(std::chrono::seconds(10));
	}

	void Run_E1()
	{
		std::promise<std::string> returnPromise;
		std::thread t = std::thread([&returnPromise] { E1::GetFromThreadedFunction(returnPromise); });

		std::future<std::string> rf = returnPromise.get_future();

		std::cout << rf.get() << std::endl;
		t.join();

		std::cout << "Finished" << std::endl;
	}
}

namespace E2
{
	void SleepThenSetData(int sleepTime, std::promise<std::string>& returnPromise)
	{
		std::this_thread::sleep_for(std::chrono::seconds(sleepTime));
		std::stringstream ss;

		ss << "I have slept for " << sleepTime << std::endl;

		returnPromise.set_value(ss.str());
	}

	void Run_E2()
	{
		const int nThreads = 10;
		std::promise<std::string>* returnPromise = new std::promise<std::string>[nThreads];
		std::vector<std::thread*> ts;
		std::vector<std::future<std::string>> returnFutures;

		for (size_t i = 0; i < nThreads; i++)
		{
			ts.push_back(new std::thread([i, returnPromise] { SleepThenSetData((i + 1) * 2, returnPromise[i]); }));

			returnFutures.push_back(returnPromise[i].get_future());
		}

		while (std::find_if(returnFutures.begin(), returnFutures.end(), [](std::future<std::string>& f) { return f.valid(); }) != returnFutures.end())
		{
			auto it = std::find_if(returnFutures.begin(), returnFutures.end(), [](std::future<std::string>& f){
				return f.valid() && f.wait_for(std::chrono::milliseconds(1)) == std::future_status::ready;
			});

			if (it != returnFutures.end())
				std::cout << it->get();

			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}

		for(auto t : ts)
		{
			t->join();
			delete t;
		}
		
		delete[] returnPromise;
	}
}

namespace E3
{
	std::string GetFromThreadedFunction()
	{
		std::this_thread::sleep_for(std::chrono::seconds(10));
		return "Hello from threaded function!";
	}

	void Run_E3()
	{
		std::future<std::string> rf = std::async(std::launch::async, GetFromThreadedFunction);
		std::this_thread::sleep_for(std::chrono::seconds(5));
		std::cout << "Main thread woke up." << std::endl;
		std::cout << rf.get() << std::endl;
	}
}

namespace E4
{
	void SleepForRandomTime(int threadID)
	{
		std::random_device rd;
		std::uniform_int_distribution<unsigned> dist(3, 10);
		int sleepTime = dist(rd);

		std::stringstream ss;

		std::cout << "thread " << threadID << " sleeping for " << sleepTime << " seconds." << std::endl;
		std::cout << ss.str();

		std::this_thread::sleep_for(std::chrono::seconds(sleepTime));

		std::cout << "thread " << threadID << " woke up." << std::endl;
	}

	void Run_E4()
	{
		std::vector<std::future<void>> futures;
		for (size_t i = 0; i < 20; i++)
			futures.push_back(std::async(std::launch::async, [i] {SleepForRandomTime((int)i); }));
	}
}

int main()
{
	E1::Run_E1();
	E2::Run_E2();
	E3::Run_E3();
	E4::Run_E4();
	return 0;
}

