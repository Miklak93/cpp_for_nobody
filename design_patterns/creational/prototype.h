#pragma once
/**********************************************************************************************************************
+======================================================= Prototype ===================================================+
|                                                                                                                     |
| Description:                                                                                                        |
| The Prototype design pattern allows objects to be cloned, creating new instances by copying an existing object.     |
| This is achieved by defining a prototype interface and implementing a cloning method in concrete classes.           |
|                                                                                                                     |
| When to use:                                                                                                        |
| Use the Prototype pattern when object creation is costly or complex, and a similar object can be used as a template |
| to create new instances efficiently. It is especially useful when the system needs to avoid creating instances      |
| directly using the `new` keyword.                                                                                   |
|                                                                                                                     |
+=====================================================================================================================+
***********************************************************************************************************************/

#include <memory>
#include <unordered_map>

namespace prototype
{
enum class type
{
    type1,
    type2
};

struct iprototype
{
    virtual ~iprototype() {}

    /* Most important function - it will be used by a factory to create other instances from the prototype */
    virtual std::unique_ptr<iprototype> clone() const = 0;

    virtual std::string to_string() const = 0;
};

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
class prototype_1 : public iprototype
{
    public:
    prototype_1() : value_() {}
    prototype_1(T value) : value_(std::move(value)) {}

    virtual std::unique_ptr<iprototype> clone() const override
    {
        return std::make_unique<prototype_1<T>>(value_);
    }

    virtual std::string to_string() const override
    {
        return std::to_string(value_);
    }

    private:
    T value_;
};

template <typename T, typename = std::enable_if_t<std::is_base_of_v<std::basic_string<char>, T>>>
class prototype_2 : public iprototype
{
    public:
    prototype_2() : value_() {}
    prototype_2(T value) : value_(std::move(value)) {}

    virtual std::unique_ptr<iprototype> clone() const override
    {
        return std::make_unique<prototype_2<T>>(value_);
    }

    virtual std::string to_string() const override
    {
        return std::string{value_.begin(), value_.end()};
    }

    private:
    T value_;
};

struct prototype_factory
{
    prototype_factory()
    {
        prototypes_[type::type1] = std::make_unique<prototype_1<float>>(1.0);
        prototypes_[type::type2] = std::make_unique<prototype_2<std::string>>("prototype_2");
    }

    /* Create other instances of the object from the given prototype */
    std::unique_ptr<iprototype> create_prototype(type t)
    {
        return prototypes_[t]->clone();
    }

    std::unordered_map<type, std::unique_ptr<iprototype>> prototypes_;
};
}  // namespace prototype
