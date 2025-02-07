/***********************************************************************************************************************
+=================================================== Structural Test =================================================+
|                                                                                                                     |
| These tests are designed to validate the implementation and integration of structural design patterns. They ensure  |
| that the patterns effectively define relationships between objects and classes, enabling flexibility, reusability,  |
| and maintainability in the system architecture.                                                                     |
|                                                                                                                     |
| The tests focus on verifying that the patterns support seamless collaboration between components and correctly       |
| manage the composition of objects while maintaining clarity and scalability in the design.                          |
|                                                                                                                     |
+=====================================================================================================================+
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "structural/structural.h"

/* 7 tests */
TEST(structural, adapter)
{
    adapter::to_be_adapted item{};
    adapter::adapter target{item};

    /* Adapter is able to wrap and convert API incompatible with user needs.
     * Compare with decorator.
     */
    EXPECT_THAT(target.request(), testing::StrEq("request 1000"));
}

TEST(structural, bridge)
{
    auto implementation1 = bridge::implementation_1{};
    auto implementation2 = bridge::implementation_2{};
    auto implementation3 = bridge::implementation_3{};

    EXPECT_THAT(bridge::abstraction{implementation1}.trigger_action(), testing::StrEq("abstraction with implementation_1: action"));
    EXPECT_THAT(bridge::abstraction{implementation2}.trigger_action(), testing::StrEq("abstraction with implementation_2: action"));
    EXPECT_THAT(bridge::abstraction{implementation3}.trigger_action(), testing::StrEq("abstraction with implementation_3: action"));
}

TEST(structural, composite)
{
    static const auto client_code = [](const composite::component& component) { return component.operation(); };

    auto tree = composite::make_tree();
    auto branch1 = composite::make_branch();
    auto branch2 = composite::make_branch();
    auto leaf_1 = composite::make_leaf();
    auto leaf_2 = composite::make_leaf();
    auto leaf_3 = composite::make_leaf();

    branch1->add(*leaf_1);
    branch1->add(*leaf_2);
    branch2->add(*leaf_3);
    tree->add(*branch1);
    tree->add(*branch2);

    EXPECT_THAT(tree->operation(), testing::StrEq("branch->{branch->{{leaf operation}{leaf operation}}. branch->{{leaf operation}}. }. "));
}

TEST(structural, decorator)
{
    /* Decorator has the same API as a component but adds extra functionalities in it.
     * Decorator focuses on dynamically adding functions to an object, while Proxy focuses
     * on controlling access to an object. */
    auto component1 = decorator::component_1{};
    EXPECT_THAT(component1.operation(), testing::StrEq("component_1: operation"));

    auto component2 = decorator::component_2{};
    EXPECT_THAT(component2.operation(), testing::StrEq("component_2: operation"));

    auto decorated1 = decorator::decorator{component1};
    EXPECT_THAT(decorated1.operation(), testing::StrEq("decorated{component_1: operation}"));

    auto decorated2 = decorator::decorator{component2};
    EXPECT_THAT(decorated2.operation(), testing::StrEq("decorated{component_2: operation}"));
}

TEST(structural, facade)
{
    auto facade = facade::facade(facade::inserter_1{}, facade::inserter_2{});

    facade.init();
    facade.insert();
    auto result = facade.finalize();

    EXPECT_THAT(result, testing::ElementsAre(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
}

TEST(structural, flyweight)
{
    auto factory = std::make_shared<flyweight::shared_memory_factory>();

    // Add shared memory objects to the factory
    factory->add({{1, 2, 3}, {4}, "A"});
    factory->add({{5, 6}, {7, 8}, "B"});
    factory->add({{9}, {10, 11, 12}, "C"});

    flyweight::flyweight_combiner combiner(factory);

    EXPECT_THAT(combiner("A", 5.0, 'a'), testing::StrEq("shared { vector_data: 1, 2, 3, set_data: 4 | } unique { double_data: 5 char_data: a }"));
    EXPECT_THAT(combiner("B", 0.0, 'b'), testing::StrEq("shared { vector_data: 5, 6, set_data: 7 | 8 | } unique { double_data: 0 char_data: b }"));
    EXPECT_THAT(combiner("C", -5.0, 'c'),
                testing::StrEq("shared { vector_data: 9, set_data: 10 | 11 | 12 | } unique { double_data: -5 char_data: c }"));
}

TEST(structural, proxy)
{
    static const auto client_code = [](const proxy::irequest& request) { return request.send(); };

    auto request = proxy::request();
    EXPECT_THAT(client_code(request), testing::StrEq("request: send"));

    /* Decorator focuses on dynamically adding functions to an object, while Proxy focuses
     * on controlling access to an object. */
    auto proxy = proxy::proxy(request);
    EXPECT_THAT(client_code(proxy), testing::StrEq("proxy: is_connected and is_logged so request: send"));
}
