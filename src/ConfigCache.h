#pragma once
#include <nlohmann/json_fwd.hpp>
#include <any>

namespace nsConfig{
	static std::map<std::string, std::any> configItems;

	template<class T>
	static T load(const std::string& fileName) {

		auto iter = configItems.find(fileName);
		if (iter == configItems.end()) {
			try {
				auto conf_item = nlohmann::json::parse(std::ifstream(fileName)).get<T>();
				configItems.emplace(fileName, conf_item);
				return conf_item;
			}
			catch (const std::exception& e) {
				throw e;
			}
		}
		else {
			auto conf_item = std::any_cast<T>((*iter).second);
			//if (nullptr == conf_item) {
				//throw std::bad_typeid(std::format("Cached type {} is not matching expected type {}", typeid(conf_item), typeid(T)));
				//throw std::runtime_error("Cached type  is not matching expected type}");
			//}
		
			return	conf_item;
		}
	}
	
}