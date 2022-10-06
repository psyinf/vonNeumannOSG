#pragma once
#include "DataLogger.h"
#include "EntityBehavior.h"

#include <cppkafka/cppkafka.h>


namespace entities
{
class KafkaLogger : public BehaviorBase
{
public:
    KafkaLogger(const config::BehaviorConf& conf);


    void frame(Entity& entity, FrameTime frameTime) override;
    void handleMessage(nsDataLogger::Message&& msg) const;
    void flush() const;

private:
    nlohmann::json channelConf;

    std::unique_ptr<cppkafka::BufferedProducer<std::string>> producer;

    std::unique_ptr<nsDataLogger::DataLogger> dataLogger;
};
} // namespace entities