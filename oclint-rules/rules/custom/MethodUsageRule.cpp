#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class MethodUsageRule : public AbstractASTVisitorRule<MethodUsageRule>
{
private:
    string sourceCode(SourceRange range)
    {
        string code = _carrier->getSourceManager().getCharacterData(range.getBegin());
        size_t offet = range.getEnd().getRawEncoding() - range.getBegin().getRawEncoding() + 1;
        return code.substr(0,offet);
    }
    
    // 检查是不是注释 orz~~~
    bool isCommentedCode (const char *body, const char *target)
    {
        size_t pos = target - body;
        std::string bodyStr = body;
        
        size_t m0Begin = bodyStr.rfind("//",pos);
        size_t m0End = bodyStr.rfind("\n",pos);
        size_t m1Begin = bodyStr.rfind("/*",pos);
        size_t m1End = bodyStr.rfind("*/",pos);
        
        if (m0Begin != bodyStr.npos && (m0End == bodyStr.npos || m0End < m0Begin))
        {
            return true;
        }
        else if (m1Begin != bodyStr.npos && (m1End == bodyStr.npos || m1End < m1Begin))
        {
            return true;
        }
        
        return false;
    }
    
public:
    virtual const string name() const override
    {
        return "方法使用";
    }
    
    virtual int priority() const override
    {
        return 1;
    }
    
    virtual const string category() const override
    {
        return "注意";
    }
    
#ifdef DOCGEN
    virtual const std::string since() const override
    {
        return "0.15";
    }
    
    virtual const std::string description() const override
    {
        return ""; // TODO: fill in the description of the rule.
    }
    
    virtual const std::string example() const override
    {
        return R"rst(
        .. code-block:: cpp
        
        void example()
        {
        // TODO: modify the example for this rule.
        }
        )rst";
    }
    
#endif
    
    bool VisitObjCMethodDecl(ObjCMethodDecl *node)
    {
        string method = node -> getNameAsString();
        
        if (method.compare("initialize") == 0)
        {
            string code = sourceCode(node->getSourceRange());
            
            if (node -> getBody() != nullptr)
            {
                string body = sourceCode(node -> getBody() -> getSourceRange());
                
                if (body.find("dispatch_") != string::npos)
                {
                    if (!isCommentedCode(body.c_str(), "dispatch_")) {
                        addViolation(node, this, "在initialize方法中不要调起其他线程操作");
                    }
                    
                }else if (body.find("onThread")!= string::npos)
                {
                    if (!isCommentedCode(body.c_str(), "onThread")) {
                        addViolation(node, this, "在initialize方法中不要调起其他线程操作");
                    }
                }else if (body.find("performSelectorOnMainThread")!= string::npos){
                    if (!isCommentedCode(body.c_str(), "performSelectorOnMainThread")) {
                        addViolation(node, this, "在initialize方法中不要调起其他线程操作");
                    }
                }
            }
        }
        return true;
    }
    
    bool VisitObjCMessageExpr(ObjCMessageExpr *node)
    {
        string code =  sourceCode(node -> getSourceRange());
        size_t space_pos = code.find(" ");
        size_t pos;
        
        bool invalid = false;
        
        if ((pos = code.find("NSString")) != string::npos || pos < space_pos)
        {
            if (code.find("WithString:") != string::npos)
            {
                invalid = true;
            }else if (code.find("initWithData:") != string::npos && code.find("encoding:") != string::npos)
            {
                addViolation(node, this, "对于NSData转NSString，以后请使用initWithUTF8String或者initWithCString来代替initWithData，主要原因如果data内容中包含结束符\0不在最后时，会导致整个NSString产生异常，length不能正常计算。JSON、正则之类的操作无法进行");
                
                return true;
            }
        }
        else if ((pos = code.find("NSNumber")) != string::npos || pos < space_pos)
        {
            if (code.find("WithInteger:") != string::npos
                || code.find("WithChar:") != string::npos
                || code.find("WithUnsignedChar:") != string::npos
                || code.find("WithShort:") != string::npos
                || code.find("WithUnsignedShort:") != string::npos
                || code.find("WithInt:") != string::npos
                || code.find("WithUnsignedInt:") != string::npos
                || code.find("WithLong:") != string::npos
                || code.find("WithUnsignedLong:") != string::npos
                || code.find("WithLongLong:") != string::npos
                || code.find("WithUnsignedLongLong:") != string::npos
                || code.find("WithFloat:") != string::npos
                || code.find("WithDouble:") != string::npos
                || code.find("WithBool:") != string::npos
                || code.find("WithUnsignedInteger:") != string::npos)
            {
                invalid = true;
            }
        }
        else if ((pos = code.find("NSArray")) != string::npos || pos < space_pos)
        {
            if (code.find("WithObjects:") != string::npos)
            {
                invalid = true;
            }
        }
        else if ((pos = code.find("NSDictionary")) != string::npos || pos < space_pos)
        {
            if (code.find("WithObjectsAndKeys:") != string::npos)
            {
                invalid = true;
            }
        }
        
        if (invalid)
        {
            string des = "少用与之等价的方法:\"" + code + "\",多用字面量语法,字面量就是直接能从代码中看到的变量值。如字符串: @\"12345\"";
            addViolation(node, this, des);
        }
        
        return true;
    }
};

static RuleSet rules(new MethodUsageRule());
