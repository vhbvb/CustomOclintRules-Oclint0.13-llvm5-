#include "TestRuleOnCode.h"
#include "rules/custom/SpaceCheckRule.cpp"

TEST(SpaceCheckRuleTest, PropertyTest)
{
    SpaceCheckRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("space check", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(SpaceCheckRuleTest, FirstFailingTest)
{
    EXPECT_FALSE("Start writing a new test");
}
