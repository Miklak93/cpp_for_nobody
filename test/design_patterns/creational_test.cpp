/***********************************************************************************************************************
+==================================================== Creational Test ================================================+
|                                                                                                                     |
| These tests are designed to simulate the typical usage scenarios of creational design patterns. By mimicking the    |
| client-side interaction with the patterns, these tests verify the correctness, flexibility, and robustness of       |
| object creation mechanisms. They also ensure that the design principles, such as decoupling and scalability, are    |
| effectively upheld during instantiation.                                                                            |
|                                                                                                                     |
| The focus is on validating how well the patterns handle different client requirements while maintaining consistent   |
| object creation processes.                                                                                          |
|                                                                                                                     |
+=====================================================================================================================+
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "creational/creational.h"

/* 5 tests */
TEST(creational, abstract_factory)
{
    auto factory1 = abstract_factory::factory_1();

    auto productA1 = factory1.create_product_A();
    EXPECT_THAT(productA1->name(), "Name of product_A1");

    auto productB1 = factory1.create_product_B();
    EXPECT_THAT(productB1->id(), "Id of product_B1");

    auto factory2 = abstract_factory::factory_2();
    auto productA2 = factory2.create_product_A();
    EXPECT_THAT(productA2->name(), "Name of product_A2");

    auto productB2 = factory2.create_product_B();
    EXPECT_THAT(productB2->id(), "Id of product_B2");
}

TEST(creational, builder_function)
{
    static const auto setter = [](builder_function::complex_product& product)
    {
        product.push_back("A");
        product.push_back("B");
        product.push_back("C");
    };

    auto product = builder_function::builder<builder_function::complex_product>(setter);
    EXPECT_THAT(product, testing::ElementsAre(testing::StrEq("A"), testing::StrEq("B"), testing::StrEq("C")));
}

TEST(creational, builder)
{
    auto director = builder::director();
    EXPECT_THROW(director.new_instance(), std::runtime_error);

    director.set_builder<builder::builder_1>();
    auto product1 = director.new_instance().build_first_part("A").build_second_part("B").build_third_part("C").get();
    EXPECT_THAT(product1, testing::ElementsAre(testing::StrEq("1A"), testing::StrEq("1B"), testing::StrEq("1C")));

    director.set_builder<builder::builder_2>();
    auto product2 = director.new_instance().build_first_part("A").build_second_part("B").build_third_part("C").get();
    EXPECT_THAT(product2, testing::ElementsAre(testing::StrEq("A2"), testing::StrEq("B2"), testing::StrEq("C2")));
}

TEST(creational, factory_method)
{
    static const auto client_code = [](const factory_method::icreator& creator) { return creator.operation(); };

    auto creator1 = factory_method::creator_1();
    EXPECT_THAT(client_code(creator1), testing::StrEq("Performing operation on product_1"));

    auto creator2 = factory_method::creator_2();
    EXPECT_THAT(client_code(creator2), testing::StrEq("Performing operation on product_2"));
}

TEST(creational, prototype)
{
    prototype::prototype_factory factory;

    auto prototype1 = factory.create_prototype(prototype::type::type1);
    EXPECT_THAT(prototype1->to_string(), testing::StrEq("1.000000"));

    auto prototype2 = factory.create_prototype(prototype::type::type2);
    EXPECT_THAT(prototype2->to_string(), testing::StrEq("prototype_2"));
}

TEST(creational, singleton)
{
    const auto value = singleton::singleton<int>::get(0);

    const auto same_value1 = singleton::singleton<int>::get();
    EXPECT_THAT(value, same_value1);

    /* We can't modify value of the singleton */
    const auto same_value2 = singleton::singleton<int>::get(1);
    EXPECT_THAT(value, same_value2);

    /* But other-type singleton is acceptable */
    const auto other_value = singleton::singleton<double>::get(1);
    EXPECT_THAT(value, testing::Ne(other_value));

    singleton::singleton<int>::reset();

    const auto next_value = singleton::singleton<int>::get(2);
    EXPECT_THAT(value, testing::Ne(next_value));
}
