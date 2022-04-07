#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <sstream>

namespace e1
{
	void ThreadOutput(size_t threadNum, std::mutex& mut)
	{
		for (size_t i = 0; i < 1000; i++)
		{
			//std::stringstream ss;
			mut.lock();
			std::cout << "Thread " << threadNum << " outputting " << i << std::endl;
			mut.unlock();
			//std::cout << ss.str();
		}

	}

	void ThreadOutput2(size_t threadNum, std::mutex& mut)
	{
		for (size_t i = 0; i < 1000; i++)
		{
			//std::stringstream ss;
			mut.lock();
			std::cout << "Thread " << threadNum << " outputting " << i << std::endl;
			mut.unlock();
			//std::cout << ss.str();
		}

	}

	void RunE1()
	{
		std::mutex mut;
		std::thread** thread = new std::thread* [4];
		std::thread** threadSec = new std::thread* [4];

		for (size_t i = 0; i < 4; i++)
			thread[i] = new std::thread([i, &mut] { ThreadOutput(i, mut); });

		for (size_t i = 0; i < 4; i++)
			threadSec[i] = new std::thread([i, &mut] { ThreadOutput2(i, mut); });

		for (size_t i = 0; i < 4; i++)
		{
			thread[i]->join();
			threadSec[i]->join();
			delete thread[i];
			delete threadSec[i];
		}
			

		delete[] thread; delete[] threadSec;

	}
}

namespace e2
{
	void SetArrayThreaded(int* tArray, size_t arraySize, size_t threadNum, size_t numThreads)
	{
		const size_t start = (arraySize * threadNum) / numThreads;
		const size_t end = (arraySize * (threadNum + 1)) / numThreads;
		for (size_t i = start; i < end; i++)
			tArray[i] = (int)i;
	}

	void RunE2()
	{
		const size_t arraySize = 100;
		const size_t numThreads = 4;
		int* tArray = new int[arraySize];

		std::thread** thread = new std::thread*[numThreads];
		for (size_t i = 0; i < numThreads; i++)
		{
			thread[i] = new std::thread([tArray, arraySize, i, numThreads] {SetArrayThreaded(tArray, arraySize, i, numThreads); });
		}

		for(size_t i = 0; i < numThreads; i++)
		{
			thread[i]->join();
			delete thread[i];
		}
			

		delete[] thread;

		for (size_t i = 0; i < arraySize; i++)
			std::cout << tArray[i];

		delete[] tArray;
	}
}

namespace e3
{

	// std::atomic (shorthand for mut.lock and mut.unlock)
	void ABA(std::atomic<int>& sum)
	{
		// mut.lock, mut.unlock
		for (size_t i = 0; i < 100000; i++)
			++sum;
			
	}

	void RunE3()
	{
		std::atomic<int> sum = 0;
		std::vector<std::thread*> threads;

		for (size_t i = 0; i < 10; i++)
			threads.push_back(new std::thread([&sum] {ABA(sum); }));

		for (auto t : threads)
		{
			t->join();
			delete t;
		}

		std::cout << sum;
	}
}

namespace e4
{
	std::timed_mutex mutex;
	void SleepForever()
	{
		mutex.lock();
		std::this_thread::sleep_for(std::chrono::seconds(5));
		mutex.unlock();
	}

	void WaitForever()
	{
		std::cout << "Attempting to obtain mutex.\n";
		if (mutex.try_lock_for(std::chrono::seconds(10)))
		{
			std::cout << "Obtained mutex.\n";
			mutex.unlock();
			std::cout << "Released mutex.\n";
		}
		else {
			std::cout << "Failed to obtain mutex, timer expired :(";
		}
	}

	void RunE4()
	{
		std::vector<std::thread*> threads;
		threads.push_back(new std::thread([] { SleepForever(); }));
		threads.push_back(new std::thread([] { WaitForever(); }));

		for (auto t : threads)
		{
			t->join();
			delete t;
		}
	}
}

namespace e5
{
	std::mutex mut, mut2;

	void ThreadedFunction1()
	{
		std::scoped_lock s1(mut, mut2);
		std::cout << "Function 1 obtained mutex 1\n";
		std::cout << "Function 1 obtained mutex 2\n";
	}

	void ThreadedFunction2()
	{
		std::scoped_lock s1(mut, mut2);
		std::cout << "Function 2 obtained mutex 2\n";
		std::cout << "Function 2 obtained mutex 1\n";
	}

	void RunE5()
	{
		std::vector<std::thread*> threads;

		threads.push_back(new std::thread([] {ThreadedFunction1(); }));
		threads.push_back(new std::thread([] {ThreadedFunction2(); }));

		for(auto t : threads)
		{
			t->join();
			delete t;
		}
	}
}

int main(int argc, char** argv)
{
	e1::RunE1();

	system("PAUSE");

	e2::RunE2();

	e3::RunE3();

	e4::RunE4();

	e5::RunE5();

	return 0;
}