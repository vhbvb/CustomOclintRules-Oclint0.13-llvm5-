#include "TestRuleOnCode.h"
#include "rules/custom/BracesNewLineRule.cpp"

TEST(BracesNewLineRuleTest, PropertyTest)
{
    BracesNewLineRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("braces new line", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(BracesNewLineRuleTest, FirstFailingTest)
{
    EXPECT_FALSE("Start writing a new test");
}
