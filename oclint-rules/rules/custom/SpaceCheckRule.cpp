#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class SpaceCheckRule : public AbstractASTVisitorRule<SpaceCheckRule>
{
private:
    string sourceCode(SourceRange range)
    {
        string code = _carrier->getSourceManager().getCharacterData(range.getBegin());
        size_t offet = range.getEnd().getRawEncoding() - range.getBegin().getRawEncoding() + 1;
        return code.substr(0,offet);
    }
    
    void checkLeftParenthesis(Stmt *node)
    {
        string code = sourceCode(node->getSourceRange());
        
        size_t pos = code.find("(");
        if (pos != string::npos)
        {
            bool match = (code[pos - 1] == ' ' && code[pos - 2] != ' ');
            if (!match)
            {
                string source = code.length() >= 20?code.substr(0,15)+"...":code;
                string des = "\"" + source + "\"" + ":'(' 前面需要一个空格";
                addViolation(node, this, des);
            }
        }
    }
    
public:
    virtual const string name() const override
    {
        return "空格检查";
    }
    
    virtual int priority() const override
    {
        return 3;
    }
    
    virtual const string category() const override
    {
        return "格式";
    }
    
#ifdef DOCGEN
    virtual const std::string since() const override
    {
        return "0.15";
    }
    
    virtual const std::string description() const override
    {
        return "空格检查"; // TODO: fill in the description of the rule.
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
    
    bool VisitIfStmt(IfStmt *node)
    {
        checkLeftParenthesis(node);
        return true;
    }
    
    bool VisitSwitchStmt(SwitchStmt *node)
    {
        checkLeftParenthesis(node);
        return true;
    }
    
    bool VisitWhileStmt(WhileStmt *node)
    {
        checkLeftParenthesis(node);
        return true;
    }
    
    bool VisitForStmt(ForStmt *node)
    {
        checkLeftParenthesis(node);
        return true;
    }
    
    // 定义变量
    bool VisitDeclStmt (DeclStmt *node)
    {
        string code = sourceCode(node->getSourceRange());
        bool invalid = false;
        
        size_t pos = code.find("^");
        
        if (pos == string::npos)
        {
            size_t pos_0 = code.find(" ");
            if (pos_0 != string::npos)
            {
                string sub = code.substr(pos_0+1);
                if (sub[0] == ' ')
                {
                    invalid = true;
                }
            }
            
            size_t pos_1 = code.find("*");
            if (pos_1 != string::npos)
            {
                string sub = code.substr(pos_1+1);
                if (sub[0] == ' ')
                {
                    invalid = true;
                }
            }
        }
        else//block   *规范没写
        {
            size_t pos_0 = code.find("=");
            string leftCode = code.substr(0,pos_0-1);
            string rightCode = code.substr(pos_0+1);
            
            //            size_t pos_1 = leftCode.find("*");
            //            if (pos_1 != string::npos)
            //            {
            //                invalid = leftCode[pos_1 -1] == ' ';
            //            }
            
            size_t post_2 = leftCode.find("(");
            if (post_2 != string::npos)
            {
                bool match = (leftCode[post_2 - 1] == ' ' && leftCode[post_2 - 2] != ' ');
                if (!match)
                {
                    invalid = true;
                }
            }
            
            size_t post_3 = leftCode.find(")");
            if (post_3 != string::npos)
            {
                bool match = (leftCode[post_3 +1] == ' ' && leftCode[post_3+2] != ' ');
                if (!match)
                {
                    invalid = true;
                }
            }
            
            size_t post_4 = leftCode.find(",");
            if (post_4 != string::npos)
            {
                bool match = (leftCode[post_4+1] == ' ' && leftCode[post_4+2] != ' ' && leftCode[post_4-1] != ' ');
                if (!match)
                {
                    invalid = true;
                }
            }
            
            //            size_t post_5 = rightCode.find("*");
            //            if (post_5 != string::npos)
            //            {
            //                invalid = rightCode[pos_1 -1] == ' ';
            //            }
            
            size_t post_6 = rightCode.find("(");
            if (post_6 != string::npos)
            {
                bool match = rightCode[post_6 - 1] == '^' || (rightCode[post_6 - 1] == ' ' && rightCode[post_6 - 2] != ' ');
                if (!match)
                {
                    invalid = true;
                }
            }
            
            size_t post_7 = rightCode.find(",");
            if (post_7 != string::npos)
            {
                bool match = (rightCode[post_7+1] == ' ' && rightCode[post_7+2] != ' ' && rightCode[post_7-1] != ' ');
                if (!match)
                {
                    invalid = true;
                }
            }
            
            
        }
        
        // = 2边空格
        size_t pos_2 = code.find("=");
        if (pos_2 != string::npos)
        {
            bool match = (code[pos_2-1]==' ' && code[pos_2-2]!=' ' && code[pos_2+1]==' ' && code[pos_2+2]!=' ');
            if (!match)
            {
                invalid = true;
            }
        }
        
        // ;前不需要空格
        if (code[code.length()-2]==' ') {
            invalid = true;
        }
        
        if (invalid)
        {
            string des = "不正确的变量定义:\"" + code + "\"；类型和变量名称之间需要保留一个空格，＊号与变量名称相连";
            addViolation(node, this, des);
        }
        
        return true;
    }
    
    bool VisitBinaryOperator(BinaryOperator *node)
    {
        string code = sourceCode(node->getSourceRange());
        string t = node->getOpcodeStr();
        size_t pos = code.find(t);
        
        if (pos != string::npos)
        {
            bool match = (code[pos-1] == ' ' && code [pos+t.length()] == ' ' && code[pos-2] != ' ' && code[pos+1+t.length()] != ' ');
            
            if (!match)
            {
                string source = code.length() > 50?code.substr(0,50)+"...":code;
                string des = "不正确的运算符格式:\"" + source + "\"; 运算符:'" + t + "'左右需要一个空格间距";
                addViolation(node, this, des);
            }
        }
        
        return true;
    }
    
    bool VisitUnaryOperator(UnaryOperator *node)
    {
        string code = sourceCode(node->getSourceRange());
        string o = node->getOpcodeStr(node->getOpcode());
        size_t pos = code.find(o);
                
        if (code[pos-1] == ' ')
        {
            string des = "不正确的运算符格式:\"" + code + "；\"" + o + "\"前面不需要空格";
            addViolation(node, this, des);
        }
        return true;
    }
    
    bool VisitConditionalOperator(ConditionalOperator *node)
    {
        string code = sourceCode(node->getSourceRange());
        
        size_t pos_0 = code.find(":");
        size_t pos_1 = code.find("?");
                
        bool match_0 = (code[pos_0-1]==' ' && code[pos_0-2]!=' ' && code[pos_0+1]==' ' && code[pos_0+2]!=' ');
        bool match_1 = (code[pos_1-1]==' ' && code[pos_1-2]!=' ' && code[pos_1+1]==' ' && code[pos_1+2]!=' ');
        
        if (!match_0 || !match_1)
        {
            string des = "不正确的三目运算符格式:\"" + code + "\"  ，“？”和“:” 两边都需要一个空格间距";
            addViolation(node, this, des);
        }
        
        return true;
    }
    
    //?:
    bool VisitBinaryConditionalOperator(BinaryConditionalOperator *node)
    {
        string code = sourceCode(node->getSourceRange());
        size_t pos = code.find("?:");
        
        if (pos != string::npos)
        {
            bool match = (code[pos-1]==' ' && code[pos-2]!=' ' && code[pos+2]==' ' && code[pos+3]!=' ');
            if (!match)
            {
                string des = "不正确的二目条件运算符:\"" + code + "\", “?:” 两边都需要一个空格间距";
                addViolation(node, this, des);
            }
        }
        return true;
    }
    
    bool VisitObjCMethodDecl(ObjCMethodDecl *node)
    {
        string code = sourceCode(node->getSourceRange());
        
        size_t pos_0 = code.find("(");
        size_t pos_1 = code.find(")");
        
        bool match = (code[pos_0-1]==' ' && code[pos_0-2]!=' ' && code[pos_1+1] != ' ');

        if (!match)
        {
            string source = code.length() > 20?code.substr(0,15)+"...":code;
            string des = "不正确的方法命名格式:\"" + source + "\"" + "; 方法类型符和返回类型间需要一个空格间距, 返回类型和方法名中间不需要空格";
            addViolation(node, this, des);
        }
        
        return true;
    }
    
    bool VisitObjCInterfaceDecl(ObjCInterfaceDecl *node)
    {
        string code = sourceCode(node->getSourceRange());
        size_t space_pos = code.find("@interface") + 10;
        bool match = code[space_pos] == ' ' && code[space_pos+1] != ' ';
        if (!match) {
            string des = "类定义格式错误："+code+ "; @interface 和类名之间只需要一个空格";
            addViolation(node, this, des);
            return true;
        }
        
        size_t parent_pos = code.find(":");
        if (parent_pos != string::npos)
        {
            match = code[parent_pos-1] == ' ' && code[parent_pos-2] != ' ' && code[parent_pos+1] == ' ' && code[parent_pos+2] != ' ';
            if (!match)
            {
                string des = "类定义格式错误："+code+ "; \":\"两边各需要一个空格";
                addViolation(node, this, des);
                return true;
            }
        }
        
        size_t protocol_pos = code.find("<");
        if (protocol_pos != string::npos)
        {
            match = code[protocol_pos-1] == ' ' && code[protocol_pos-2] != ' ';
            if (!match)
            {
                string des = "类定义格式错误："+code+ "; 继承协议\"<\"前需要一个空格";
                addViolation(node, this, des);
                return true;
            }
        }

        return true;
    }
        
    bool VisitObjCCategoryDecl(ObjCCategoryDecl *node)
    {
        string code = sourceCode(node->getSourceRange());
        
        size_t space_pos = code.find("@interface") + 10;
        bool match = code[space_pos] == ' ' && code[space_pos+1] != ' ';
        if (!match) {
            string des = "类定义格式错误："+code+ "; @interface 和类名之间只需要一个空格";
            addViolation(node, this, des);
            return true;
        }
                
        size_t protocol_pos = code.find("<");
        if (protocol_pos != string::npos)
        {
            match = code[protocol_pos-1] == ' ' && code[protocol_pos-2] != ' ';
            if (!match)
            {
                string des = "类扩展定义格式错误："+code+ "; 继承协议\"<\"前需要一个空格";
                addViolation(node, this, des);
                return true;
            }
        }
        
        return true;
    }
        
    bool VisitObjCProtocolDecl(ObjCProtocolDecl *node)
    {
        string code = sourceCode(node->getSourceRange());
        size_t space_pos = code.find("@protocol") + 9;
        
        bool match = code[space_pos] == ' ' && code[space_pos+1] != ' ';
        if (!match) {
            string des = "协议定义格式错误："+code+ "; @protocol 和协议名之间只需要一个空格";
            addViolation(node, this, des);
            return true;
        }
        
        size_t parent_pos = code.find("<");
        if (parent_pos != string::npos)
        {
            match = code[parent_pos-1] == ' ' && code[parent_pos-2] != ' ';
            if (!match) {
                string des = "协议定义格式错误："+code+ ";协议名和继承协议之间只需要一个空格";
                addViolation(node, this, des);
            }
        }
        
        return true;
    }
};

static RuleSet rules(new SpaceCheckRule());
