#include "DataLogger.h"

#include <iostream>
using namespace nsDataLogger;
DataLogger::DataLogger(ProcessMessageFunc pmf, FlushFunc ff)
	:processMessageFunc(pmf)
	, flushMessagesFunc(ff)
{

}

DataLogger::~DataLogger()
{
	sendThread.join();
}

void DataLogger::push(Message message)
{
	dataQueue.push(std::move(message));
}

void DataLogger::send()
{
	size_t numProcessed = 1;
	auto startTime = std::chrono::system_clock::now();
	std::vector<Message> messages(10000);
	while (true) {
		
		
		auto numPopped = dataQueue.pop(messages.data(), messages.size());
		numProcessed += numPopped;
		std::for_each(std::cbegin(messages), std::cbegin(messages) + numPopped, [this](Message m) {processMessageFunc(std::move(m)); });
		if (numProcessed > 1000 ){
			flushMessagesFunc();
		}
		if (numProcessed > 10000 ) {
			
			auto current = std::chrono::system_clock::now();
			std::chrono::duration<double> diff = current - startTime;
			std::cout << numProcessed / 1000 / diff.count() << "k / s" << std::endl;
			startTime = current;
			numProcessed = 0;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));

		}
	}
}

void DataLogger::start()
{
	sendThread = std::thread(&DataLogger::send, this);

}

