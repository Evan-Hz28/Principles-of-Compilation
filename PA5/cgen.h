#ifndef CGEN_H
#define CGEN_H

#include <assert.h>
#include <stdio.h>
#include "emit.h"
#include "cool-tree.h"
#include "symtab.h"
#include <vector>
#include <map>
#include <algorithm>

enum Basicness     {Basic, NotBasic};
#define TRUE 1
#define FALSE 0

class CgenClassTable;
typedef CgenClassTable *CgenClassTableP;

class CgenNode;
typedef CgenNode *CgenNodeP;

//
// Environment: 用于代码生成过程中的上下文管理
// 跟踪 Let 变量、方法参数、属性以及当前类
//
class Environment {
private:
    // 变量名 -> 栈偏移(offset from SP)
    // 使用 vector 模拟栈式符号表，方便 push/pop
    std::vector<std::pair<Symbol, int> > vars; 
    
    // 参数名 -> 帧指针偏移(offset from FP)
    std::map<Symbol, int> params;
    
    int var_offset; // 当前 Let 变量在栈上的累计偏移

public:
    CgenNode* m_class_node; // 当前代码生成所在的类

    Environment() : var_offset(0), m_class_node(NULL) {}

    // 作用域管理
    void EnterScope() { 
      // 标记当前作用域开始的位置
      vars.push_back(std::make_pair((Symbol)NULL, 0)); // <--- 修改了这里，加上 (Symbol)
   }
    
    void ExitScope() {
        // 弹出直到遇到分隔符
        while (!vars.empty()) {
            std::pair<Symbol, int> p = vars.back();
            vars.pop_back();
            if (p.first == NULL) break;
            var_offset--; // 退出作用域，释放栈空间计数
        }
    }

    // 查找 Let 变量 (返回 offset from SP, -1 if not found)
    int LookUpVar(Symbol sym) {
        for (int i = vars.size() - 1; i >= 0; --i) {
            if (vars[i].first == sym) return vars[i].second;
        }
        return -1;
    }

    // 查找参数 (返回 offset from FP, -1 if not found)
    int LookUpParam(Symbol sym) {
        if (params.find(sym) != params.end()) return params[sym];
        return -1;
    }

    // 查找属性 (返回 offset from SELF, -1 if not found)
    int LookUpAttrib(Symbol sym); // 实现需依赖 m_class_node

    // 添加变量
    void AddVar(Symbol sym) {
        vars.push_back(std::make_pair(sym, var_offset));
        var_offset++;
    }

    // 添加参数
    void AddParam(Symbol sym) {
        // 参数在 FP 上的偏移计算通常在 method_class::code 中预先处理好
        // 这里只是存储映射。实际偏移由调用者计算。
        // 但通常我们按顺序添加。
        // 为了简单，我们提供一个可以直接设置偏移的接口，或者在 Loop 中添加
    }
    
    void AddParam(Symbol sym, int offset) {
        params[sym] = offset;
    }

    // 标记栈上有临时对象（障碍物），用于计算偏移
    void AddObstacle() {
        var_offset++;
    }
    
    // 移除障碍物
    void RemoveObstacle() {
        var_offset--;
    }
    
    int GetNextVarOffset() const { return var_offset; }
};

class CgenClassTable : public SymbolTable<Symbol,CgenNode> {
private:
   List<CgenNode> *nds;
   ostream& str;
   int stringclasstag;
   int intclasstag;
   int boolclasstag;

   // 辅助数据结构
   std::vector<CgenNode*> m_class_nodes; // 扁平化的类列表
   std::map<Symbol, int> m_class_tags;   // 类名 -> 类标签

   void SetClassTags(CgenNode* node, int& tag);

   // 以下方法用于生成常量和全局声明
   void code_global_data();
   void code_global_text();
   void code_bools(int);
   void code_select_gc();
   void code_constants();
   
   // PA5 新增：特定的代码生成阶段
   void code_class_nameTab();
   void code_class_objTab();
   void code_dispatchTabs();
   void code_protObjs();
   void code_class_inits();
   void code_class_methods();

   // 构建继承图
   void install_basic_classes();
   void install_class(CgenNodeP nd);
   void install_classes(Classes cs);
   void build_inheritance_tree();
   void set_relations(CgenNodeP nd);
   
public:
   CgenClassTable(Classes, ostream& str);
   void code();
   CgenNodeP root();
   
   // 获取类节点
   CgenNodeP GetClassNode(Symbol name) { return probe(name); }
   
   // 获取所有类节点（扁平化）
   std::vector<CgenNode*> GetClassNodes();
   
   // 获取类标签映射
   std::map<Symbol, int>& GetClassTags() { return m_class_tags; }
};

class CgenNode : public class__class {
private: 
   CgenNodeP parentnd;                        // Parent of class
   List<CgenNode> *children;                  // Children of class
   Basicness basic_status;                    // `Basic' if class is basic
                                              // `NotBasic' otherwise
   
   // 缓存分析结果，避免重复计算
   std::vector<CgenNode*> m_inheritance;
   std::vector<attr_class*> m_full_attribs;
   std::vector<method_class*> m_full_methods;
   std::map<Symbol, int> m_dispatch_idx_tab;      // 方法名 -> 分发表索引
   std::map<Symbol, Symbol> m_dispatch_class_tab; // 方法名 -> 定义该方法的类名
   std::map<Symbol, int> m_attrib_idx_tab;        // 属性名 -> 对象内偏移索引

public:
   int class_tag; // 由 CgenClassTable 分配
   int max_child_tag; // <--- 新增这行

   CgenNode(Class_ c,
            Basicness bstatus,
            CgenClassTableP class_table);

   void add_child(CgenNodeP child);
   List<CgenNode> *get_children() { return children; }
   void set_parentnd(CgenNodeP p);
   CgenNodeP get_parentnd() { return parentnd; }
   int basic() { return (basic_status == Basic); }
   
   // 代码生成辅助方法
   void code_protObj(ostream& s);
   void code_init(ostream& s);
   void code_methods(ostream& s); // 生成该类所有方法的代码

   // 分析辅助方法
   std::vector<CgenNode*> GetInheritance();       // 获取继承链 [Object, ..., Self]
   std::vector<attr_class*> GetFullAttribs();     // 获取所有属性（包括继承的）
   std::vector<method_class*> GetFullMethods();   // 获取所有方法（包括继承的，处理重写）
   
   std::vector<method_class*> GetMethods();       // 仅获取当前类定义的方法
   std::vector<attr_class*> GetAttribs();         // 仅获取当前类定义的属性
   
   std::map<Symbol, int>& GetDispatchIdxTab();
   std::map<Symbol, Symbol>& GetDispatchClassTab();
   std::map<Symbol, int>& GetAttribIdxTab();
};

class BoolConst 
{
 private: 
  int val;
 public: 
  BoolConst(int);
  void code_def(ostream&, int boolclasstag);
  void code_ref(ostream&) const;
};

#endif