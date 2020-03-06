#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class VariableNameRule : public AbstractASTVisitorRule<VariableNameRule>
{
public:
    virtual const string name() const override
    {
        return "变量命名";
    }

    virtual int priority() const override
    {
        return 3;
    }

    virtual const string category() const override
    {
        return "命名";
    }

#ifdef DOCGEN
    virtual const std::string since() const override
    {
        return "0.15";
    }

    virtual const std::string description() const override
    {
        return "变量的命名需要遵循驼峰式命名方式"; // TODO: fill in the description of the rule.
    }

    virtual const std::string example() const override
    {
        return R"rst(
.. code-block:: cpp

    void example()
    {
        // test
        NSString *userName = @"Jack";
        // test
        NSString *user_name = @"Jack";
        NSString *_UserName = @"Jack";
        NSString *USERName_ = @"Jack";
    }
        )rst";
    }

#endif
    bool VisitVarDecl(VarDecl *node)
    {
        std::string varName = node->getNameAsString();
        
        if (varName.length() > 0) //block里面有些没名字
        {
            bool invalid = false;

            invalid = varName[0]<'a'||varName[0]>'z';
            
            for (int i=1; i<varName.length(); i++)
            {
                if (invalid)
                {
                    break;
                }
                
                bool inlowcase = varName[i]>='a' && varName[i]<='z';
                bool inUpcase = varName[i]>='A' && varName[i]<='Z';
                
                invalid = !inlowcase && !inUpcase;
            }

            if (invalid)
            {
                string des = "非法的变量命名: \"" + varName + "\" ，需要遵循小驼峰式命名方式";
                addViolation(node, this, des);
            }
        }
        
        return true;
    }
    
    bool VisitObjCIvarDecl(ObjCIvarDecl *node)
    {
        std::string varName = node->getNameAsString();
        bool invalid = false;
        invalid = varName[0]!='_';
        for (int i=1; i<varName.length(); i++)
        {
            if (invalid)
            {
                break;
            }
            
            bool inlowcase = varName[i]>='a' && varName[i]<='z';
            bool inUpcase = varName[i]>='A' && varName[i]<='Z';
            
            invalid = !inlowcase && !inUpcase;
        }
        
        if (invalid)
        {
            string des = "非法的私有变量命名: \"" + varName + "\" ，私有变量命名需要遵循小驼峰式命名方式，并在前面加下划线";
            addViolation(node, this, des);
        }
        return true;
    }
    
    bool VisitObjCPropertyDecl(ObjCPropertyDecl *node)
    {
        std::string varName = node->getNameAsString();
        
        bool invalid = false;
        invalid = varName[0]<'a'||varName[0]>'z';
        for (int i=1; i<varName.length(); i++)
        {
            if (invalid)
            {
                break;
            }
            
            bool inlowcase = varName[i]>='a' && varName[i]<='z';
            bool inUpcase = varName[i]>='A' && varName[i]<='Z';
            
            invalid = !inlowcase && !inUpcase;
        }

        if (invalid)
        {
            string des = "非法的Property属性命名: \"" + varName + "\"，没有遵循小驼峰命名";
            addViolation(node, this, des);
        }
        
        return true;
    }
};

static RuleSet rules(new VariableNameRule());
