#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class ClassNamingRule : public AbstractASTVisitorRule<ClassNamingRule>
{
private:
    void applyDecl(Decl *decl, string name, string descriptionPrefix)
    {
        if (name.length() == 0) //匿名类
        {
            return;
        }
        
        bool invalid = false;
        for (int i=0; i<3; i++)
        {
            invalid = name[i]<'A' || name[i]>'Z';
            
            if (invalid)
            {
                break;
            }
        }
        
        if (invalid)
        {
            string des = "无效的Class命名:\""+ name + "\"（" + descriptionPrefix + "）， 类命名格式为“前缀+名称”，其中名称首字母必须为大写字母，通常以项目的缩写进行命名，为了避免跟iOS系统中内置的类型发生冲突，前缀命名必须不少于三个字母。";
            addViolation(decl, this, des);
        }
    }
    
public:
    virtual const string name() const override
    {
        return "类目命名";
    }

    virtual int priority() const override
    {
        return 2;
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
        return "Classes, protocols, extensions require project prefixes and follow camelcase naming"; // TODO: fill in the description of the rule.
    }

    virtual const std::string example() const override
    {
        return R"rst(
.. code-block:: cpp
        
        @interface MOBFViewController : UIViewController
        @end
        
        @protocol MOBFViewDelegate <NSObject>
        @end
        
        )rst";
    }

#endif
    
    bool VisitObjCInterfaceDecl(ObjCInterfaceDecl *decl)
    {
        applyDecl(decl, decl->getNameAsString(), "Objective-C interface");
        return true;
    }

    bool VisitObjCCategoryDecl(ObjCCategoryDecl *decl)
    {
        applyDecl(decl,decl->getNameAsString(), "Objective-C category");
        return true;
    }

    bool VisitObjCProtocolDecl(ObjCProtocolDecl *decl)
    {
        applyDecl(decl,decl->getNameAsString(), "Objective-C protocol");

        return true;
    }

    bool VisitObjCImplDecl(ObjCImplDecl *decl)
    {
        applyDecl(decl,decl->getNameAsString(), "Objective-C implementation");

        return true;
    }

    bool VisitCXXRecordDecl(CXXRecordDecl *decl)
    {
        applyDecl(decl,decl->getNameAsString(), "C++ class");

        return true;
    }
};

static RuleSet rules(new ClassNamingRule());
