#include "KafkaLoggerBehavior.h"
#include "Entity.h"
#include "cppkafka/cppkafka.h"
#include <vector>

const cppkafka::Configuration config = {
    {"metadata.broker.list", "127.0.0.1:9093"},
    // { "debug", "all" },
    //{"group.id", "viewer"},
    {"batch.num.messages", "200000"},
    {"linger.ms", "100"},
    {"acks", "1"}

};

nsEntities::KafkaLogger::KafkaLogger()
	:BehaviorBase("kafkalogger")
    , dataLogger(std::make_unique<nsDataLogger::DataLogger>([this](auto m) { this->handleMessage(std::move(m)); }, [this]() { this->flush(); }))
{
	producer = std::make_unique<cppkafka::BufferedProducer<std::string>>(config);
    producer->set_queue_full_notification(cppkafka::BufferedProducer<std::string>::QueueFullNotification::OncePerMessage);
    producer->set_queue_full_callback([]([[maybe_unused]] const auto& msgBuilder) { std::cerr << "Producer queue full"; });
	dataLogger->start();
}

void nsEntities::KafkaLogger::frame(Entity& entity, FrameTime frameTime)
{
	auto x = std::dynamic_pointer_cast<PositionController>(entity.getBehavior("position"));
	const auto err = x->pidController.getPreError().length();

	auto errStr = std::to_string(err);
	dataLogger->push(nsDataLogger::Message({ entity.getName(), std::move(errStr) }));
}

void nsEntities::KafkaLogger::setConfiguration(nlohmann::json conf)
{
	const auto& channels = conf["channels"];
}
 
void nsEntities::KafkaLogger::handleMessage(nsDataLogger::Message&& msg) const
{
	producer->add_message(cppkafka::MessageBuilder(std::move(msg.topic)).partition(0).payload(msg.buffer));
}

void nsEntities::KafkaLogger::flush() const
{
	producer->async_flush();
}
