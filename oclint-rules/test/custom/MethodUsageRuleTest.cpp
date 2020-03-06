#include "TestRuleOnCode.h"
#include "rules/custom/MethodUsageRule.cpp"

TEST(MethodUsageRuleTest, PropertyTest)
{
    MethodUsageRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("method usage", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(MethodUsageRuleTest, FirstFailingTest)
{
    EXPECT_FALSE("Start writing a new test");
}
