#include "TestRuleOnCode.h"
#include "rules/custom/MethodNamingRule.cpp"

TEST(MethodNamingRuleTest, PropertyTest)
{
    MethodNamingRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("method naming", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(MethodNamingRuleTest, FirstFailingTest)
{
    EXPECT_FALSE("Start writing a new test");
}
