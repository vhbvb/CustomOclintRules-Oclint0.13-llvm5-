#include "TestRuleOnCode.h"
#include "rules/custom/VariableNameRule.cpp"

TEST(VariableNameRuleTest, PropertyTest)
{
    VariableNameRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("variable name", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(VariableNameRuleTest, FirstFailingTest)
{
    EXPECT_FALSE("Start writing a new test");
}
