#include "KafkaLoggerBehavior.h"
#include "Entity.h"
#include "cppkafka/cppkafka.h"
#include <vector>

cppkafka::Configuration config = {
		{ "metadata.broker.list", "127.0.0.1:9093" },
		// { "debug", "all" },
		 { "group.id", "viewer"}

};

nsEntities::KafkaLogger::KafkaLogger()
	:BehaviorBase("kafkalogger")
	, dataLogger(std::make_unique<nsDataLogger::DataLogger>(std::bind(&KafkaLogger::handleMessage, this, std::placeholders::_1), std::bind(&KafkaLogger::flush, this)))
{
	producer = std::make_unique<cppkafka::BufferedProducer<std::string>>(config);
	dataLogger->start();
}

void nsEntities::KafkaLogger::frame(Entity& entity, FrameTime frameTime)
{
	
	auto x = std::dynamic_pointer_cast<PositionController>(entity.getBehavior("position"));
	const float err = x->pidController.getPreError().length();
	
	
	//auto payload = nlohmann::json()["pid.err"] = err;
	//std::string p_str = payload.dump();
	auto errStr = std::to_string(err);
	dataLogger->push(nsDataLogger::Message({ entity.getName(), std::move(errStr) }));
	//producer->add_message(cppkafka::MessageBuilder(entity.getName()).partition(0).payload(errStr));
	//std::cout << x->pidController.getPreError().length() << std::endl;

	//TODO: we need to access other behaviors?
	//kafkaLogger.produce(cppkafka::MessageBuilder("entities/" + entity.getName() + "/log/").payload());
		

}

void nsEntities::KafkaLogger::setConfiguration(nlohmann::json conf)
{
	const auto& channels = conf["channels"];
}

void nsEntities::KafkaLogger::handleMessage(nsDataLogger::Message msg)
{
	producer->add_message(cppkafka::MessageBuilder(msg.topic).partition(0).payload(msg.buffer));
}

void nsEntities::KafkaLogger::flush()
{
	producer->async_flush();

}
