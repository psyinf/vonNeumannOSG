#pragma once
#include <array>
#include <string>
#include <thread>
#include <vector>
#include <boost/lockfree/spsc_queue.hpp>

namespace nsDataLogger {
struct Message {
	std::string topic;
	std::string buffer;

};

class DataLogger {
public:
	using ProcessMessageFunc = std::function<void(nsDataLogger::Message)>;
	using FlushFunc = std::function<void(void)>;
	DataLogger(ProcessMessageFunc pmf, FlushFunc ff);
	~DataLogger();
	void push(Message message);

	void send();

	void start();
protected:
	boost::lockfree::spsc_queue<Message> dataQueue{ 100000 };
	ProcessMessageFunc processMessageFunc;
	FlushFunc flushMessagesFunc;
	std::thread sendThread;
};
}//namespace