#include "TestRuleOnCode.h"
#include "rules/custom/ClassNamingRule.cpp"

TEST(ClassNamingRuleTest, PropertyTest)
{
    ClassNamingRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("class naming", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(ClassNamingRuleTest, FirstFailingTest)
{
    EXPECT_FALSE("Start writing a new test");
}
