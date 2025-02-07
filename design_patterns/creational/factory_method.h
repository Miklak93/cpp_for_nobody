#pragma once
/**********************************************************************************************************************
+==================================================== Factory Method =================================================+
|                                                                                                                     |
| Description:                                                                                                        |
| The Factory Method design pattern provides an interface for creating objects in a superclass, but allows subclasses |
| to alter the type of objects that will be created. It delegates the instantiation logic to subclasses.              |
|                                                                                                                     |
| When to use:                                                                                                        |
| Use the Factory Method pattern when the exact class of objects to be created is determined at runtime, or when      |
| the client code should depend on an abstract interface rather than concrete implementations.                        |
|                                                                                                                     |
+=====================================================================================================================+
***********************************************************************************************************************/

#include <memory>

namespace factory_method
{
struct iproduct
{
    virtual ~iproduct() {}

    virtual std::string name() const = 0;
};

struct product_1 : iproduct
{
    public:
    virtual std::string name() const
    {
        return "product_1";
    }
};

struct product_2 : iproduct
{
    public:
    virtual std::string name() const
    {
        return "product_2";
    }
};

class icreator
{
    public:
    virtual ~icreator() {}

    std::string operation() const
    {
        /* Function implemented by a derived class is called here */
        const auto product = factory_method();
        return std::string{"Performing operation on "} + product->name();
    }

    protected:
    using product_ptr = std::unique_ptr<iproduct>;

    /* This function has to be abstract and implemented in derived class */
    virtual product_ptr factory_method() const = 0;
};

class creator_1 : public icreator
{
    public:
    creator_1() = default;

    protected:
    virtual icreator::product_ptr factory_method() const override
    {
        return std::make_unique<product_1>();
    }
};

class creator_2 : public icreator
{
    public:
    creator_2() = default;

    protected:
    virtual icreator::product_ptr factory_method() const override
    {
        return std::make_unique<product_2>();
    }
};
}  // namespace factory_method
