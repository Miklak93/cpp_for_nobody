#pragma once
/**********************************************************************************************************************
+======================================================= Flyweight ===================================================+
|                                                                                                                     |
| Description:                                                                                                        |
| The Flyweight design pattern minimizes memory usage by sharing as much data as possible with similar objects. It    |
| separates intrinsic (shared) state from extrinsic (unique) state to reduce object overhead.                         |
|                                                                                                                     |
| When to use:                                                                                                        |
| Use the Flyweight pattern when your system needs to handle a large number of fine-grained objects efficiently, and  |
| when many of these objects share common data that can be reused.                                                    |
|                                                                                                                     |
+=====================================================================================================================+
***********************************************************************************************************************/

#include <map>
#include <mutex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <set>
#include <memory>
#include <optional>

namespace flyweight
{
struct shared_memory
{
    std::vector<int> vector_data;
    std::set<float> set_data;
    std::string memory_key;
};

struct unique_memory
{
    double double_data;
    char char_data;
};

std::string to_string(const shared_memory& shared)
{
    std::stringstream ss;
    ss << "shared { vector_data: ";
    for (const auto& data : shared.vector_data)
    {
        ss << data << ", ";
    }

    ss << "set_data: ";
    for (const auto& data : shared.set_data)
    {
        ss << data << " | ";
    }
    ss << "} ";
    return ss.str();
}

std::string to_string(const unique_memory& unique)
{
    std::stringstream ss;
    ss << "unique { double_data: " << unique.double_data << " char_data: " << unique.char_data << " }";
    return ss.str();
}

class flyweight
{
    public:
    flyweight(std::shared_ptr<const shared_memory> shared) : shared_(std::move(shared)) {}

    std::string merge(const unique_memory& unique)
    {
        return to_string(*shared_) + to_string(unique);
    }

    private:
    std::shared_ptr<const shared_memory> shared_;
};

class shared_memory_factory
{
    public:
    void add(const shared_memory& shared)
    {
        memory_[shared.memory_key] = std::make_shared<shared_memory>(shared);
    }

    std::shared_ptr<const shared_memory> get(const std::string& key) const
    {
        auto it = memory_.find(key);
        if (it == memory_.end())
        {
            throw std::runtime_error("Element not found!");
        }
        return it->second;
    }

    std::optional<std::shared_ptr<const shared_memory>> try_get(const std::string& key) const
    {
        auto it = memory_.find(key);
        if (it != memory_.end())
        {
            return it->second;
        }
        return std::nullopt;
    }

    private:
    std::unordered_map<std::string, std::shared_ptr<shared_memory>> memory_;
};

struct flyweight_combiner
{
    flyweight_combiner(std::shared_ptr<shared_memory_factory> factory) : factory_(std::move(factory)) {}

    std::string operator()(const std::string& key, double d, char c) const
    {
        auto shared = factory_->get(key);
        flyweight item{shared};
        return item.merge(unique_memory{d, c});
    }

    private:
    std::shared_ptr<shared_memory_factory> factory_;
};
}  // namespace flyweight
