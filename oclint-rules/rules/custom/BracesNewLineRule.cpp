#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class BracesNewLineRule : public AbstractASTVisitorRule<BracesNewLineRule>
{
    string clearBraces(string source)
    {
        if (source.find("{")==string::npos)
        {
            return source;
        }else{
            size_t pos = source.find("{");
            string tmp = source.substr(pos+1,source.length()-pos-1);
            
            while (tmp.find("{") != string::npos)
            {
                pos = pos + tmp.find("{") + 1;
                tmp = source.substr(pos+1,source.length()-pos-1);
            }
            
            size_t end = tmp.find("}");
            string res = source.erase(pos,end+2);
            
            return clearBraces(res);
        }
    }
    
public:
    virtual const string name() const override
    {
        return "大括号换行";
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
        return "函数等大括号需要另起一行"; // TODO: fill in the description of the rule.
    }
    
    virtual const std::string example() const override
    {
        return R"rst(
        .. code-block:: cpp
        
        void example()
        {
        }
        )rst";
    }
    
#endif
    
    bool VisitCompoundStmt(CompoundStmt *node)
    {
        SourceLocation loc = node -> getLocStart();
        SourceLocation end = node -> getLocEnd();
        
        string p = _carrier->getSourceManager().getCharacterData(loc);
        int i=0;
        char tmp;
        
        bool indentationCheck = true;
        
        while (1)
        {
            SourceLocation left = loc.getLocWithOffset(-(++i));
            string left_p = _carrier->getSourceManager().getCharacterData(left);
            tmp = left_p[0];
            
            if (tmp == '^')
            {
                indentationCheck = false;
                break;
            }else if (tmp == '\n'){
                break;
            }
            else if (tmp == ' ')
            {
                continue;
            }
            else
            {
                indentationCheck = false;
                string des = "\"{\"前面需要换行";
                addViolation(node, this, des);
                break;
            }
        }
        
        int j=0;
        while (1)
        {
            tmp = p[++j];
            
            if (tmp == ' ')
            {
                continue;
            }
            else
            {
                if (tmp != '\n')
                {
                    string des = "\"{\"后面代码需要换行缩进";
                    addViolation(node, this, des);
                    indentationCheck = false;
                }
                
                break;
            }
        }
        
        int k=0;
        while (1)
        {
            SourceLocation left = end.getLocWithOffset(-(++k));
            string left_p = _carrier->getSourceManager().getCharacterData(left);
            tmp = left_p[0];
            
            if (tmp == '\n'){
                break;
            }
            else if (tmp == ' ')
            {
                continue;
            }
            else
            {
                string des = "\"}\"前面需要换行";
                addViolation(node, this, des);
                break;
            }
        }
        
        if (indentationCheck)
        {
            int count = i+3;
            
            string code = _carrier->getSourceManager().getCharacterData(node->getSourceRange().getBegin());
            size_t offet = node->getSourceRange().getEnd().getRawEncoding() - node->getSourceRange().getBegin().getRawEncoding() + 1;
            code = code.substr(1,offet-2);
            
            code = ";"+clearBraces(code);
            
            size_t break_pos;
            
            while (1)
            {
                break_pos = code.find(";\n");
                
                if (break_pos == string::npos)
                {
                    break;
                }
                
                code = code.erase(0,break_pos+2);
                
                if (code.find("\n") == string::npos)//最后一行
                {
                    count -= 4;
                }
                
                for (int index=0; index < count; index++)
                {
                    bool invalid = false;
                    if (code[index] == ' ')
                    {
                        if (index == count-1)
                        {
                            if (code[count] == ' ')
                            {
                                invalid = true;
                            }
                        }else{
                            continue;
                        }
                    }else if (code[index] == '/' || code[index] == '\n' || code[index] == '#'){
                        break;
                    }else{
                        invalid = true;
                    }

                    if (invalid)
                    {
                        string source = code.length()>50 ? (code.substr(0,49)+"..."):code;
                        string des = "代码：\"" + source + "\"需要" + to_string(count)+"个空格缩进";
                        addViolation(node, this, des);
                    }
                }
            }
        }
        
        return true;
    }
};

static RuleSet rules(new BracesNewLineRule());
