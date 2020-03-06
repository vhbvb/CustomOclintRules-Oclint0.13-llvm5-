OClint 环境部署与自定义规则
==

### 1、环境准备

1. homebrew 安装 CMake 和 Ninja 这2个编译工具

	```
	brew install cmake ninja
	```
2. 进入 Github 搜索 OCLint，clone 源码 (https://github.com/oclint/oclint)

3. 进入 oclint-scripts 目录，执行 ./make 命令。这一步的时间非常长。会下载 oclint-json-compilation-database、oclint-xcodebuild、llvm 源码以及 clang 源码。并进行相关的编译得到 oclint。且必须使用翻墙环境不然会报 timeout。
4. 编译结束，进入同级 build 文件夹，该文件夹下的内容即为 oclint。可以看到 build/oclint-release
5. cd 到根目录，编辑环境文件，比如我 zsh 对应的 .zshrc 文件,编辑下面的内容

	```
	OCLint_PATH=/Users/liubinpeng/Desktop/oclint/build/oclint-release
  	export PATH=$OCLint_PATH/bin:$PATH
	```

6. 验证下 OCLint 是否安装成功。输入 oclint --version
7. xcpretty 的安装

	```
	gem install xcpretty
	```


### 2、使用 oclint

**注意：**

1. 如果项目使用了 Cocopod，则需要指定 -workspace xxx.workspace， -e Pod排除第三方库扫描
2. 每次编译之前需要 clean

###### 第一步：编译

编译成功后，会在项目的文件夹下出现 compile_commands.json 文件

```sh
xcodebuild -scheme $scheme -workspace $workspace clean
xcodebuild -scheme $scheme -workspace $workspace -configuration Debug | xcpretty -r json-compilation-database -o compile_commands.json
```

###### 第二步：生成html

```
oclint-json-compilation-database -e Pods -- -report-type pmd -o oclintReport.xml \
    -rc LONG_LINE=200 \
    -disable-rule ShortVariableName \
    -disable-rule ObjCAssignIvarOutsideAccessors \
    -disable-rule AssignIvarOutsideAccessors \
    -disable-rule UnusedMethodParameter \
    -disable-rule UnusedLocalVariable \
    -max-priority-1=100000 \
    -max-priority-2=100000 \
    -max-priority-3=100000
```

- -e Pods 排除第三方pod的库
- -report-type 导出类型,有html,json,pmd,text,xcode,xml格式类型
- -rc 限制值
- -disable-rule 不希望开启的规则库
- max-priority 最大报告数限制

**注意：***如果出现 oclint: error: one compiler command contains multiple jobs:，将 Project 和 Targets 中 Building Settings 下的 COMPILER_INDEX_STORE_ENABLE 设置为 NO*


![](https://raw.githubusercontent.com/vhbvb/image_cloud/master/general20200226145747.png)

**参数说明**

- CYCLOMATIC_COMPLEXITY	: 方法的循环复杂性（圈负责度）	10
- LONG_CLASS:	C类或Objective-C接口，类别，协议和实现的行数	1000
- LONG_LINE:	一行代码的字符数	100
- LONG_METHOD	: 方法或函数的行数	50
- LONG_VARIABLE_NAME:	变量名称的字符数	20
- MAXIMUM_IF_LENGTH:	if语句的行数	15
- MINIMUM_CASES_IN_SWITCH:	switch语句中的case数	3
- NPATH_COMPLEXITY:	方法的NPath复杂性	200
- NCSS_METHOD	:一个没有注释的方法语句数	30
- NESTED_BLOCK_DEPTH:	块或复合语句的深度	5
- SHORT_VARIABLE_NAME:	变量名称的字符数	3
- TOO_MANY_FIELDS:	类的字段数	20
- TOO_MANY_METHODS:	类的方法数	30
- TOO_MANY_PARAMETERS:	方法的参数数	10

###### 三、在 Xcode 中使用

在项目的 TARGETS 下面，点击下方的 "+" ，选择 cross-platform 下面的 Aggregate。输入名字，这里命名为 Lint

sh脚本：

```
export LC_CTYPE=en_US.UTF-8
cd ${SRCROOT}
xcodebuild -scheme xxx -workspace xxx clean && xcodebuild -scheme xxx -workspace xxx -configuration Debug | xcpretty -r json-compilation-database -o compile_commands.json && oclint-json-compilation-database -e Pods -- -report-type xcode
```

### 3、自定义rules

OClint 提供了 70+ 项的检查规则，你可以直接去使用。但是某些时候你需要制作自己的检测规则，接下来就说说如何自定义 lint 规则。

##### 第一步：创建规则

进入 ~/Document/oclint 目录，执行下面的脚本

```sh
## 大部分情况，我们继承ASTVisitor就可以满足需求
oclint-scripts/scaffoldRule CustomLint -t ASTVisitor
```

其中，CustomLintRules 就是定义的检查规则的名字， ASTVisitor 就是你继承的 lint 规则

可以继承的规则有：ASTVisitor、SourceCodeReader、ASTMatcher。

- AbstractSourceCodeReaderRule：eachLine 方法，读取每行的代码，如果想编写的规则是需要针对每行的代码内容，则可以继承自该类
- AbstractASTVisitorRule：可以访问 AST 上特定类型的所有节点，可以检查特定类型的所有节点是递归实现的。在 apply 方法内可以看到代码实现。开发者只需要重载 bool visit* 方法来访问特定类型的节点。其值表明是否继续递归检查
- AbstractASTMatcherRule：实现 setUpMatcher 方法，在方法中添加 matcher，当检查发现匹配结果时会调用 callback 方法。然后通过 callback 方法来继续对匹配到的结果进行处理

##### 第二步：创建规则工程

```
 mkdir Lint-Rules
 cd Lint-Rules
 touch generate-lint-rules.sh
 chmod +x generate-lint-rules.sh
```

给上面的 generate-lint-rules.sh 里面添加下面的脚本

```
#! /bin/sh -e
cmake -G Xcode \
  -D CMAKE_CXX_COMPILER=../build/llvm-install/bin/clang++  \
  -D CMAKE_C_COMPILER=../build/llvm-install/bin/clang \
  -D OCLINT_BUILD_DIR=../build/oclint-core \
  -D OCLINT_SOURCE_DIR=../oclint-core \
  -D OCLINT_METRICS_SOURCE_DIR=../oclint-metrics \
  -D OCLINT_METRICS_BUILD_DIR=../build/oclint-metrics \
  -D LLVM_ROOT=../build/llvm-install/ ../oclint-rules

```

执行 generate-lint-rules.sh 脚本(./generate-lint-rules.sh)。如果出现下面的 Log 则说明生成 xcodeproj 项目成功

![](https://raw.githubusercontent.com/vhbvb/image_cloud/master/general20200226151841.png)

打开工程，可以看到很多oclint自带的规则，我们创建的CustomLintRule在最下面.

##### 第三步：编写自定义规则

然后我们就可以在cpp文件中添加自己的规则了

```sh
## 命令行查看语法树结构
clang -Xclang -ast-dump -fsyntax-only ./testOCLint/main.m
```

**示例：**

```c++
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
```

##### 第四步：使用自定义规则

修改自定义规则后就需要编译，成功后在 Products 目录下会看到对应名称的 CustomLintRulesRule.dylib 文件，需要复制到 /Documents/oclint/oclint-release/lib/oclint/rules 即可。

Scheme:ALL BUILD 会编译所有规则，可以把设置成Release,这样编译出来的包就是relesae包

无论是debug包还是release都可以正常链接使用

##### 五：如何调试

1. 参考第二步生成Driver xcode工程：

	```
	 mkdir Lint-Driver
	 cd Lint-Driver
	 touch generate-lint-rules.sh
	 chmod +x generate-lint-rules.sh
	```
	
	给上面的 generate-lint-rules.sh 里面添加下面的脚本
	
	```
	#! /bin/sh -e
	cmake -G Xcode \
	  -D CMAKE_CXX_COMPILER=../build/llvm-install/bin/clang++  \
	  -D CMAKE_C_COMPILER=../build/llvm-install/bin/clang \
	  -D OCLINT_BUILD_DIR=../build/oclint-core \
	  -D OCLINT_SOURCE_DIR=../oclint-core \
	  -D OCLINT_METRICS_SOURCE_DIR=../oclint-metrics \
	  -D OCLINT_METRICS_BUILD_DIR=../build/oclint-metrics \
	  -D LLVM_ROOT=../build/llvm-install/ ../oclint-driver
	
	```
	
	执行 generate-lint-rules.sh 脚本(./generate-lint-rules.sh)。如果出现下面的 Log 则说明生成 xcodeproj 项目成功

2. 由于我们需要调试自定义规则，就需要在刚能跑起来的oclint中调起规则，oclint有个参数-R，表示rule所在文件夹路径。通过Arguments Passed On Lanunch的方式，可以添加参数。

	```
	-R=/Users/max/oclint/Lint-XcodeProject/rules.dl/Debug -report-type html -o /Users/max/Desktop/OClint_Test/reporter.html /Users/max/Desktop/OClint_Test/OClintTest/OClintTest/VarRules.m -- -x objective-c -isystem /Users/max/oclint/build/oclint-release/lib/clang/9.0.0/include -iframework /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator.sdk/System/Library/Frameworks -isystem /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator.sdk/usr/include
	```

3. 创建WorkSpace，拉入Xcode工程 Driver和Rules。

	![](https://raw.githubusercontent.com/vhbvb/image_cloud/master/general20200226153848.png)
	
	配置好之后，在自定义规则里打好断点，运行起来，出现了一个问题：
	```
	cannot find dynamic library for report type:html
	```
	
	把oclint/build/oclint-reporters/reporters.dl下的库文件拷贝到
	oclint/oclint-xcode-driver/bin/Debug/../lib/oclint/reporters 即可
	
	然后就可以正常调试了
	
	![](https://raw.githubusercontent.com/vhbvb/image_cloud/master/general20200226154456.png)
	
	




