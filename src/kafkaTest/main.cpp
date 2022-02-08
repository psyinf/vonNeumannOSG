#include <cppkafka/cppkafka.h>
#include <iostream>
#include <strstream>
using namespace std;
using namespace cppkafka;

int main() try {
    // Create the config
    Configuration config = {
        { "metadata.broker.list", "127.0.0.1:9093" },
       // { "debug", "all" },
        { "group.id", "my_topic"}

    };

    // Create the producer
    Producer producer(config);
    producer.set_timeout(std::chrono::milliseconds(5000));
 
    // Produce a message!
    int i = 0;
    while (true) {
        std::stringstream ss;
        ss << "message no: " << i++;
        std::string message = ss.str();
        std::cout << "Sending " << message << std::endl;
        producer.produce(MessageBuilder("my_topic").partition(0).payload(message));
		

        //std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    producer.flush(std::chrono::milliseconds(1000));
}
catch (const std::exception& e) {
    std::cerr << "main encountered error: "<< e.what() << std::endl;
}