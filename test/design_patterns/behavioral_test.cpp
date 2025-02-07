/***********************************************************************************************************************
+=================================================== Behavioral Test =================================================+
|                                                                                                                     |
| These tests are designed to validate the behavior and interaction between objects in the implementation of          |
| behavioral design patterns. They ensure that the patterns manage complex communication flows, promote loose         |
| coupling, and delegate responsibilities effectively among components.                                               |
|                                                                                                                     |
| The tests focus on verifying that the patterns correctly encapsulate behaviors, handle dynamic workflows, and       |
| maintain clarity and flexibility in the interactions between objects.                                               |
|                                                                                                                     |
+=====================================================================================================================+
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "behavioral/behavioral.h"

/* 10 tests */
TEST(behavioral, chain_of_responsibility)
{
    static const auto client_code = [](const chain_of_responsiblity::ihandler& handler, std::string request) { return handler.action(request); };

    chain_of_responsiblity::handler_1 handler1;
    chain_of_responsiblity::handler_2 handler2;
    chain_of_responsiblity::handler_3 handler3;

    handler3.set_next(handler2).set_next(handler1);

    /* Request is flowing over the system until gets suitable handler; otherwise stays unhandled */
    EXPECT_THAT(handler3.action("request_1"), testing::StrEq("request_1 handled by handler_1"));
    EXPECT_THAT(handler3.action("request_2"), testing::StrEq("request_2 handled by handler_2"));
    EXPECT_THAT(handler3.action("request_3"), testing::StrEq("request_3 handled by handler_3"));
    EXPECT_THAT(handler3.action("request_4"), testing::StrEq("request_4 not handled!"));

    EXPECT_THAT(handler2.action("request_1"), testing::StrEq("request_1 handled by handler_1"));
    EXPECT_THAT(handler2.action("request_2"), testing::StrEq("request_2 handled by handler_2"));
    EXPECT_THAT(handler2.action("request_3"), testing::StrEq("request_3 not handled!"));

    EXPECT_THAT(handler1.action("request_1"), testing::StrEq("request_1 handled by handler_1"));
    EXPECT_THAT(handler1.action("request_2"), testing::StrEq("request_2 not handled!"));
}

TEST(behavioral, command)
{
    command::simple_command simple{"|simple|"};
    command::complex_command complex{"|complex1|", "|complex2|"};

    command::invoker invoker{};
    invoker.set_on_start(simple);
    invoker.set_on_finish(complex);

    EXPECT_THAT(invoker.invoke(), "simple_command: execute: |simple| invoker: invoke receiver: action_1: |complex1| receiver: action_2: |complex2|");
}

TEST(behavioral, iterator)
{
    std::vector<char> collector;

    char str[] = "ABCDE";
    auto iter = iterator::make_str_iterator(str);

    for (auto iter = iterator::make_str_iterator(str); !iter.is_final(); iter.next())
    {
        collector.push_back(iter.get());
    }
    EXPECT_THAT(collector, testing::ElementsAre('A', 'B', 'C', 'D', 'E'));
}

TEST(behavioral, mediator)
{
    mediator::component_1 component1;
    mediator::component_2 component2;

    EXPECT_THAT(component1.action_1(), testing::StrEq("component_1: action_1"));
    EXPECT_THAT(component2.action_2(), testing::StrEq("component_2: action_2"));

    /* Mediator is hidden in the components allowing to call component2 method from component1 method and vice versa */
    mediator::mediator mediator{component1, component2};

    EXPECT_THAT(component1.action_1(), testing::StrEq("component_1: action_1 trigerred mediator which triggered component_2: handle_2"));
    EXPECT_THAT(component2.action_2(), testing::StrEq("component_2: action_2 trigerred mediator which triggered component_1: handle_1"));
}

TEST(behavioral, memento)
{
    memento::originator originator{};
    memento::caretaker caretaker{originator};

    EXPECT_THAT(originator.state(), testing::IsEmpty());
    EXPECT_THAT(caretaker.history(), testing::IsEmpty());

    originator.action("originator state_0");
    caretaker.backup();
    EXPECT_THAT(originator.state(), testing::StrEq("originator state_0"));
    EXPECT_THAT(caretaker.history(), testing::ElementsAre(testing::StrEq("memento state: originator state_0")));

    originator.action("originator state_1");
    caretaker.backup();
    EXPECT_THAT(originator.state(), testing::StrEq("originator state_1"));
    EXPECT_THAT(caretaker.history(), testing::ElementsAre(testing::StrEq("memento state: originator state_0"),  //
                                                          testing::StrEq("memento state: originator state_1")));

    originator.action("originator state_2");
    caretaker.backup();
    EXPECT_THAT(originator.state(), testing::StrEq("originator state_2"));
    EXPECT_THAT(caretaker.history(), testing::ElementsAre(testing::StrEq("memento state: originator state_0"),  //
                                                          testing::StrEq("memento state: originator state_1"),  //
                                                          testing::StrEq("memento state: originator state_2")));

    caretaker.undo();
    EXPECT_THAT(originator.state(), testing::StrEq("originator state_2"));
    EXPECT_THAT(caretaker.history(), testing::ElementsAre(testing::StrEq("memento state: originator state_0"),  //
                                                          testing::StrEq("memento state: originator state_1")));

    caretaker.undo();
    EXPECT_THAT(originator.state(), testing::StrEq("originator state_1"));
    EXPECT_THAT(caretaker.history(), testing::ElementsAre(testing::StrEq("memento state: originator state_0")));

    caretaker.undo();
    EXPECT_THAT(originator.state(), testing::StrEq("originator state_0"));
    EXPECT_THAT(caretaker.history(), testing::IsEmpty());
}

TEST(behavioral, observer)
{
    observer::target target{};
    observer::observer observer0{target, 0};
    observer::observer observer1{target, 1};
    observer::observer observer2{target, 2};
    observer::observer observer3{target, 3};
    observer::observer observer4{target, 4};

    EXPECT_THAT(observer0.current(), testing::IsEmpty());
    EXPECT_THAT(observer1.current(), testing::IsEmpty());
    EXPECT_THAT(observer2.current(), testing::IsEmpty());
    EXPECT_THAT(observer3.current(), testing::IsEmpty());
    EXPECT_THAT(observer4.current(), testing::IsEmpty());

    target.action("first message");
    EXPECT_THAT(observer0.current(), testing::StrEq("first message"));
    EXPECT_THAT(observer1.current(), testing::StrEq("first message"));
    EXPECT_THAT(observer2.current(), testing::StrEq("first message"));
    EXPECT_THAT(observer3.current(), testing::StrEq("first message"));
    EXPECT_THAT(observer4.current(), testing::StrEq("first message"));

    observer0.unsubscribe();

    target.action("second message");
    EXPECT_THAT(observer0.current(), testing::StrEq("first message"));
    EXPECT_THAT(observer1.current(), testing::StrEq("second message"));
    EXPECT_THAT(observer2.current(), testing::StrEq("second message"));
    EXPECT_THAT(observer3.current(), testing::StrEq("second message"));
    EXPECT_THAT(observer4.current(), testing::StrEq("second message"));

    observer1.unsubscribe();
    observer2.unsubscribe();

    target.action("third message");
    EXPECT_THAT(observer0.current(), testing::StrEq("first message"));
    EXPECT_THAT(observer1.current(), testing::StrEq("second message"));
    EXPECT_THAT(observer2.current(), testing::StrEq("second message"));
    EXPECT_THAT(observer3.current(), testing::StrEq("third message"));
    EXPECT_THAT(observer4.current(), testing::StrEq("third message"));

    target.attach(observer0);
    target.detach(observer3);

    target.action("fourth message");
    EXPECT_THAT(observer0.current(), testing::StrEq("fourth message"));
    EXPECT_THAT(observer1.current(), testing::StrEq("second message"));
    EXPECT_THAT(observer2.current(), testing::StrEq("second message"));
    EXPECT_THAT(observer3.current(), testing::StrEq("third message"));
    EXPECT_THAT(observer4.current(), testing::StrEq("fourth message"));
}

TEST(behavioral, state)
{
    state::context context{};
    state::state_1 state_1{context};
    state::state_1 state_2{context};

    context.change_state(state_1);

    /* These requests are just proxies - real functionality is implmemented in state functions */
    EXPECT_THAT(context.request_1(), testing::StrEq("state_1: action_1"));
    EXPECT_THAT(context.request_2(), testing::StrEq("state_1: action_2 -> transition to state_2"));

    EXPECT_THAT(context.request_1(), testing::StrEq("state_2: action_1"));
    EXPECT_THAT(context.request_2(), testing::StrEq("state_2: action_2"));
}

TEST(behavioral, strategy)
{
    strategy::target target{};
    strategy::strategy_1 strategy1{};
    strategy::strategy_2 strategy2{};

    target.set_strategy(strategy1);
    EXPECT_THAT(target.request(), testing::StrEq("strategy_1: action"));

    target.set_strategy(strategy2);
    EXPECT_THAT(target.request(), testing::StrEq("strategy_2: action"));
}

TEST(behavioral, template_method)
{
    template_method::template_method_1 template_method1{};
    template_method::template_method_2 template_method2{};

    EXPECT_THAT(
        template_method1.perform_all(),
        testing::StrEq("itemplate_method: impl_action_1 itemplate_method: impl_action_2 template_method_1: action_1 template_method_1: action_2"));

    EXPECT_THAT(
        template_method2.perform_all(),
        testing::StrEq("itemplate_method: impl_action_1 itemplate_method: impl_action_2 template_method_2: action_1 template_method_2: action_2"));
}

TEST(behavioral, visitor)
{
    visitor::component_1 component1{};
    visitor::component_2 component2{};
    std::vector<visitor::icomponent*> components{&component1, &component2};

    const auto visit_components = [&](const visitor::ivisitor& visitor)
    {
        std::vector<std::string> out;
        for (auto&& component : components)
        {
            /* Component accepts visitor */
            out.push_back(component->accept(visitor));
        }
        return out;
    };

    visitor::visitor_1 visitor1{};
    visitor::visitor_2 visitor2{};
    EXPECT_THAT(visit_components(visitor1), testing::ElementsAre(testing::StrEq("component_1 visited by visitor_1"),  //
                                                                 testing::StrEq("component_2 visited by visitor_1")));
    EXPECT_THAT(visit_components(visitor2), testing::ElementsAre(testing::StrEq("component_1 visited by visitor_2"),  //
                                                                 testing::StrEq("component_2 visited by visitor_2")));
}
