#include "KafkaLoggerBehavior.h"

#include "Entity.h"
//#include "cppkafka/cppkafka.h"

#include <vector>

const cppkafka::Configuration config = {
    {"metadata.broker.list", "127.0.0.1:9093"},
    // { "debug", "all" },
    //{"group.id", "viewer"},
    {"batch.num.messages", "200000"},
    {"linger.ms", "100"},
    {"acks", "1"}

};

entities::KafkaLogger::KafkaLogger(const nsConfig::BehaviorConf& conf)
    : BehaviorBase(conf)
    , dataLogger(std::make_unique<nsDataLogger::DataLogger>([this](auto m) { this->handleMessage(std::move(m)); }, [this]() { this->flush(); }))
{
    const auto& channels = conf.conf["channels"];
    //producer             = std::make_unique<cppkafka::BufferedProducer<std::string>>(config);
    //producer->set_queue_full_notification(cppkafka::BufferedProducer<std::string>::QueueFullNotification::OncePerMessage);
    //producer->set_queue_full_callback([]([[maybe_unused]] const auto& msgBuilder) { std::cerr << "Producer queue full"; });
    //dataLogger->start();
}

void entities::KafkaLogger::frame(Entity& entity, FrameTime frameTime)
{
    // TODO: how to couple properties between Plugins?
    // auto x = std::dynamic_pointer_cast<PositionController>(entity.getBehavior("position"));

    const auto err = 1.0;
    // x->pidController.getPreError().length();

    auto errStr = std::to_string(err);
    dataLogger->push(nsDataLogger::Message({entity.getName(), std::move(errStr)}));
}


void entities::KafkaLogger::handleMessage(nsDataLogger::Message&& msg) const
{
   // producer->add_message(cppkafka::MessageBuilder(std::move(msg.topic)).partition(0).payload(msg.buffer));
}

void entities::KafkaLogger::flush() const
{
    //producer->async_flush();
}
