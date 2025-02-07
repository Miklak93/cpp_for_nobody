#pragma once
/**********************************************************************************************************************
+=================================================== Abstract Factory ================================================+
|                                                                                                                     |
| Description:                                                                                                        |
| The Abstract Factory design pattern provides an interface for creating families of related or dependent objects     |
| without specifying their concrete classes. It encapsulates object creation, ensuring consistency across products.   |
| In short, you have different factories with the same interface.                                                     |
|                                                                                                                     |
| When to use:                                                                                                        |
| Use the Abstract Factory pattern when your system needs to work with multiple families of related objects, or when  |
| you want to ensure that objects from the same family are used together. It is useful for enforcing consistency.     |
|                                                                                                                     |
+=====================================================================================================================+
***********************************************************************************************************************/

namespace abstract_factory
{
struct iproduct_A
{
    virtual ~iproduct_A() {};
    virtual std::string name() const = 0;
};

struct product_A1 : iproduct_A
{
    virtual std::string name() const override
    {
        return std::string{"Name of product_A1"};
    }
};

struct product_A2 : iproduct_A
{
    virtual std::string name() const override
    {
        return std::string{"Name of product_A2"};
    }
};

struct iproduct_B
{
    virtual ~iproduct_B() {};
    virtual std::string id() const = 0;
};

struct product_B1 : iproduct_B
{
    virtual std::string id() const override
    {
        return std::string{"Id of product_B1"};
    }
};

struct product_B2 : iproduct_B
{
    virtual std::string id() const override
    {
        return std::string{"Id of product_B2"};
    }
};

/* Most important - abstract factory */
struct ifactory
{
    virtual ~ifactory() {}

    virtual std::unique_ptr<iproduct_A> create_product_A() const = 0;
    virtual std::unique_ptr<iproduct_B> create_product_B() const = 0;
};

struct factory_1 : ifactory
{
    virtual std::unique_ptr<iproduct_A> create_product_A() const override
    {
        return std::make_unique<product_A1>();
    }

    virtual std::unique_ptr<iproduct_B> create_product_B() const override
    {
        return std::make_unique<product_B1>();
    }
};

struct factory_2 : ifactory
{
    virtual std::unique_ptr<iproduct_A> create_product_A() const override
    {
        return std::make_unique<product_A2>();
    }

    virtual std::unique_ptr<iproduct_B> create_product_B() const override
    {
        return std::make_unique<product_B2>();
    }
};
}  // namespace abstract_factory
