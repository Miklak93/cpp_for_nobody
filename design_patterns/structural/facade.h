#pragma once
/**********************************************************************************************************************
+======================================================== Facade =====================================================+
|                                                                                                                     |
| Description:                                                                                                        |
| The Facade design pattern provides a simplified interface to a complex subsystem, making it easier for clients to   |
| interact with the subsystem without exposing its underlying complexity.                                             |
|                                                                                                                     |
| When to use:                                                                                                        |
| Use the Facade pattern when you want to provide a unified interface to a set of interfaces in a subsystem, or when  |
| you need to reduce dependencies between clients and the complex subsystem.                                          |
|                                                                                                                     |
+=====================================================================================================================+
***********************************************************************************************************************/

#include <vector>
namespace facade
{
struct inserter_1
{
    inserter_1() : data_() {}

    void init()
    {
        data_ = std::vector<int>{0};
    }

    std::vector<int> get() const
    {
        return data_;
    }

    void insert_1()
    {
        data_.push_back(1);
    }

    void insert_2()
    {
        data_.push_back(2);
    }

    void insert_3()
    {
        data_.push_back(3);
    }

    void insert_4()
    {
        data_.push_back(4);
    }

    void insert_5()
    {
        data_.push_back(5);
    }

    std::vector<int> data_;
};

struct inserter_2
{
    inserter_2() : data_() {}

    void set(std::vector<int> data)
    {
        data_ = std::move(data);
    }

    std::vector<int> finalize() const
    {
        return data_;
    }

    void insert_6()
    {
        data_.push_back(6);
    }

    void insert_7()
    {
        data_.push_back(7);
    }

    void insert_8()
    {
        data_.push_back(8);
    }

    void insert_9()
    {
        data_.push_back(9);
    }

    void insert_10()
    {
        data_.push_back(10);
    }

    std::vector<int> data_;
};

class facade
{
    public:
    facade(inserter_1 inserter1, inserter_2 inserter2) : inserter1_(std::move(inserter1)), inserter2_(std::move(inserter2)), data_() {}

    void init()
    {
        inserter1_.init();
    }

    void insert()
    {
        inserter1_.insert_1();
        inserter1_.insert_2();
        inserter1_.insert_3();
        inserter1_.insert_4();
        inserter1_.insert_5();

        inserter2_.set(inserter1_.get());

        inserter2_.insert_6();
        inserter2_.insert_7();
        inserter2_.insert_8();
        inserter2_.insert_9();
        inserter2_.insert_10();
    }

    std::vector<int> finalize() const
    {
        return inserter2_.finalize();
    }

    private:
    inserter_1 inserter1_;
    inserter_2 inserter2_;
    std::vector<int> data_;
};

}  // namespace facade
