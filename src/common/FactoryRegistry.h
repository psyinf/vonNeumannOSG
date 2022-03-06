#pragma once
#include <FlagSet.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <ranges>
#include <string>
#include <vector>

namespace common
{
template <typename CtorType, typename KeyType = std::string>
class FactoryRegistry
{
private:
    enum Flags_
    {
        NONE,
        PER_SCENE, // basically a singleton
    };

public:
    using Flags = FlagSet<Flags_>;
    struct RegisteredFactory
    {
    };

public:
    FactoryRegistry()  = default;
    ~FactoryRegistry() = default;

    /**
     * \brief	Adds a constructor to 'constructor_function'.
     * \param	key						The key.
     * \param	constructor_function	The constructor function. You can use boost::factory to create the "constructor"
     * \return	true if it succeeds, false if it fails.
     */
    virtual bool registerPrototype(KeyType key, CtorType&& constructor_function)
    {
        std::cout << "Registered " << key << " as plugin" << std::endl;
        auto ret = registeredConstructors.emplace(std::move(key), std::move(constructor_function));
        return ret.second;
    }

    /**
     * \brief	Query if a a constructor for the given key has been registered
     * \param	key	The key.
     * \return	true if constructor, false if not.
     */
    bool hasPrototype(const KeyType& key) const
    {
        return 0 < registeredConstructors.count(key);
    }

    /**
     * \brief	Gets module constructor by name
     * \param	type_name	Name of the type you want to build.
     * \return	The constructor of that type.
     */
    virtual const CtorType& getPrototype(KeyType type_name) const
    {
        return registeredConstructors.at(type_name);
    }

    /**
     * \brief	Gets registered types as a sorted list
     * \return	The registered types.
     */
    std::vector<KeyType> getRegisteredTypes() const
    {
        // TODO: use pipes
        std::vector<KeyType> reg_types;
        std::ranges::transform(registeredConstructors, std::back_inserter(reg_types), [](const auto& pair) { return pair.first; });
        return reg_types;
    }

private:
    std::map<KeyType, CtorType, std::less<>> registeredConstructors; ///< Mapping of key to constructors
};

} // namespace common