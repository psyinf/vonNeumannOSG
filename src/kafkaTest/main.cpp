#include <cppkafka/cppkafka.h>
#include <iostream>
using namespace std;
using namespace cppkafka;

int main() try {
    // Create the config
    Configuration config = {
        { "metadata.broker.list", "127.0.0.1:9093" }
    };

    // Create the producer
    Producer producer(config);
    producer.poll();

    // Produce a message!
    string message = "hey there!";
    producer.produce(MessageBuilder("my_topic").partition(0).payload(message));
    producer.flush(std::chrono::milliseconds(10000));
}
catch (const std::exception& e) {
    std::cerr << "main encountered error: " << std::endl;
}