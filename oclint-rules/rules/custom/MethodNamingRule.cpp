#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "oclint/util/ASTUtil.h"

using namespace std;
using namespace clang;
using namespace oclint;

class MethodNamingRule : public AbstractASTVisitorRule<MethodNamingRule>
{
private:
    void applydecl(Decl *decl, string name)
    {
        camelCaseCheck(decl,name);
        aligned(decl,name);
    }
    
    void aligned(Decl *decl, string name)
    {
        SourceLocation loc = decl -> getLocStart();
        const char *p = _carrier->getSourceManager().getCharacterData(loc);
        int length = decl->getSourceRange().getEnd().getRawEncoding()- decl->getSourceRange().getBegin().getRawEncoding();
        
        int count = 0;
        bool equal = true;
        int tmp = 0;
        int space = 0;
        for (int i=0; i<length; i++)
        {
            if (p[i] != ':')
            {
                if (p[i] == '{') {
                    break;
                }
                if (p[i] == '\n')
                {
                    tmp = 0;
                }else{
                    tmp++;
                }
            }
            else
            {
                if (space == 0)
                {
                    space = tmp;
                }
                else
                {
                    if (equal)
                    {
                        equal = (space == tmp);
                    }
                }
                count ++;
            }
        }
        
        if (count >= 3 && !equal)
        {
            string des = "方法名未对齐:" + name + "，参数大于3个的方法建议参数换行对齐";
            addViolation(decl, this, des);
        }
    }
    
    void camelCaseCheck(Decl *decl, string name)
    {
        bool invalid = false;

        size_t postion = 0;
        std::string token;

        while (1) {
            if ((postion = name.find(":")) != std::string::npos)
            {
                token = name.substr(0, postion);
            }else
            {
                token = name;
            }

            for (int i=0; i<token.length(); i++)
            {
                bool inlowcase = token[i]>='a' && token[i]<='z';
                bool inUpcase = token[i]>='A' && token[i]<='Z';

                invalid = !inlowcase && !inUpcase;

                if (i==0 && token[i]=='_')
                {
                    invalid = false;
                }

                if (invalid)
                {
                    break;
                }
            }

            if (invalid)
            {
                string des = "无效的方法命名: \"" + name + "\"，方法命名需要遵循驼峰式命";
                addViolation(decl, this, des);
                break;
            }else{
                if (name == token)
                {
                    break;
                }else{
                    name.erase(0,postion+1);
                }
            }
        }
    }
    
public:
    virtual const string name() const override
    {
        return "方法命名";
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
        return "方法命名格式效验"; // TODO: fill in the description of the rule.
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
        
    bool VisitCXXMethodDecl(CXXMethodDecl *node)
    {
        std::string varName = node->getNameAsString();
        applydecl(node, varName);

        return true;
    }
    
    bool VisitObjCMethodDecl(ObjCMethodDecl *node)
    {
        std::string varName = node->getNameAsString();
        applydecl(node, varName);
        return true;
    }
};

static RuleSet rules(new MethodNamingRule());
