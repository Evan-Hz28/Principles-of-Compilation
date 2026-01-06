// --- START OF FILE cgen.cc ---

#include "cgen.h"
#include "cgen_gc.h"

extern void emit_string_constant(ostream& str, char *s);
extern int cgen_debug;

// 全局符号定义
Symbol
       arg,
       arg2,
       Bool,
       concat,
       cool_abort,
       copy,
       Int,
       in_int,
       in_string,
       IO,
       length,
       Main,
       main_meth,
       No_class,
       No_type,
       Object,
       out_int,
       out_string,
       prim_slot,
       self,
       SELF_TYPE,
       Str,
       str_field,
       substr,
       type_name,
       val;

static void initialize_constants(void)
{
  arg         = idtable.add_string("arg");
  arg2        = idtable.add_string("arg2");
  Bool        = idtable.add_string("Bool");
  concat      = idtable.add_string("concat");
  cool_abort  = idtable.add_string("abort");
  copy        = idtable.add_string("copy");
  Int         = idtable.add_string("Int");
  in_int      = idtable.add_string("in_int");
  in_string   = idtable.add_string("in_string");
  IO          = idtable.add_string("IO");
  length      = idtable.add_string("length");
  Main        = idtable.add_string("Main");
  main_meth   = idtable.add_string("main");
  No_class    = idtable.add_string("_no_class");
  No_type     = idtable.add_string("_no_type");
  Object      = idtable.add_string("Object");
  out_int     = idtable.add_string("out_int");
  out_string  = idtable.add_string("out_string");
  prim_slot   = idtable.add_string("_prim_slot");
  self        = idtable.add_string("self");
  SELF_TYPE   = idtable.add_string("SELF_TYPE");
  Str         = idtable.add_string("String");
  str_field   = idtable.add_string("_str_field");
  substr      = idtable.add_string("substr");
  type_name   = idtable.add_string("type_name");
  val         = idtable.add_string("_val");
}

static char *gc_init_names[] =
  { "_NoGC_Init", "_GenGC_Init", "_ScnGC_Init" };
static char *gc_collect_names[] =
  { "_NoGC_Collect", "_GenGC_Collect", "_ScnGC_Collect" };


BoolConst falsebool(FALSE);
BoolConst truebool(TRUE);

// --- Environment Implementation ---
// 在 cgen.h 中声明，在这里实现，因为它依赖 CgenNode 的完整定义
int Environment::LookUpAttrib(Symbol sym) {
    if (m_class_node) {
        std::map<Symbol, int>& idx_tab = m_class_node->GetAttribIdxTab();
        if (idx_tab.find(sym) != idx_tab.end()) {
            return idx_tab[sym];
        }
    }
    return -1;
}

// 确保引用了全局变量
extern CgenClassTable *global_classtable;

void program_class::cgen(ostream &os) 
{
  initialize_constants();
  // 正确！将 new 出来的对象赋值给全局变量
  global_classtable = new CgenClassTable(classes,os);
}

// --- 汇编指令辅助函数 (emit_*) ---
static void emit_load(char *dest_reg, int offset, char *source_reg, ostream& s)
{
  s << LW << dest_reg << " " << offset * WORD_SIZE << "(" << source_reg << ")" 
    << endl;
}

static void emit_store(char *source_reg, int offset, char *dest_reg, ostream& s)
{
  s << SW << source_reg << " " << offset * WORD_SIZE << "(" << dest_reg << ")"
      << endl;
}

static void emit_load_imm(char *dest_reg, int val, ostream& s)
{ s << LI << dest_reg << " " << val << endl; }

static void emit_load_address(char *dest_reg, char *address, ostream& s)
{ s << LA << dest_reg << " " << address << endl; }

static void emit_partial_load_address(char *dest_reg, ostream& s)
{ s << LA << dest_reg << " "; }

static void emit_load_bool(char *dest, const BoolConst& b, ostream& s)
{
  emit_partial_load_address(dest,s);
  b.code_ref(s);
  s << endl;
}

static void emit_load_string(char *dest, StringEntry *str, ostream& s)
{
  emit_partial_load_address(dest,s);
  str->code_ref(s);
  s << endl;
}

static void emit_load_int(char *dest, IntEntry *i, ostream& s)
{
  emit_partial_load_address(dest,s);
  i->code_ref(s);
  s << endl;
}

static void emit_move(char *dest_reg, char *source_reg, ostream& s)
{ s << MOVE << dest_reg << " " << source_reg << endl; }

static void emit_neg(char *dest, char *src1, ostream& s)
{ s << NEG << dest << " " << src1 << endl; }

static void emit_add(char *dest, char *src1, char *src2, ostream& s)
{ s << ADD << dest << " " << src1 << " " << src2 << endl; }

static void emit_addu(char *dest, char *src1, char *src2, ostream& s)
{ s << ADDU << dest << " " << src1 << " " << src2 << endl; }

static void emit_addiu(char *dest, char *src1, int imm, ostream& s)
{ s << ADDIU << dest << " " << src1 << " " << imm << endl; }

static void emit_div(char *dest, char *src1, char *src2, ostream& s)
{ s << DIV << dest << " " << src1 << " " << src2 << endl; }

static void emit_mul(char *dest, char *src1, char *src2, ostream& s)
{ s << MUL << dest << " " << src1 << " " << src2 << endl; }

static void emit_sub(char *dest, char *src1, char *src2, ostream& s)
{ s << SUB << dest << " " << src1 << " " << src2 << endl; }

static void emit_sll(char *dest, char *src1, int num, ostream& s)
{ s << SLL << dest << " " << src1 << " " << num << endl; }

static void emit_jalr(char *dest, ostream& s)
{ s << JALR << "\t" << dest << endl; }

static void emit_jal(char *address,ostream &s)
{ s << JAL << address << endl; }

static void emit_return(ostream& s)
{ s << RET << endl; }

static void emit_gc_assign(ostream& s)
{ s << JAL << "_GenGC_Assign" << endl; }

static void emit_disptable_ref(Symbol sym, ostream& s)
{  s << sym << DISPTAB_SUFFIX; }

static void emit_init_ref(Symbol sym, ostream& s)
{ s << sym << CLASSINIT_SUFFIX; }

static void emit_label_ref(int l, ostream &s)
{ s << "label" << l; }

static void emit_protobj_ref(Symbol sym, ostream& s)
{ s << sym << PROTOBJ_SUFFIX; }

static void emit_method_ref(Symbol classname, Symbol methodname, ostream& s)
{ s << classname << METHOD_SEP << methodname; }

static void emit_label_def(int l, ostream &s)
{
  emit_label_ref(l,s);
  s << ":" << endl;
}

static void emit_beqz(char *source, int label, ostream &s)
{
  s << BEQZ << source << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_beq(char *src1, char *src2, int label, ostream &s)
{
  s << BEQ << src1 << " " << src2 << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_bne(char *src1, char *src2, int label, ostream &s)
{
  s << BNE << src1 << " " << src2 << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_bleq(char *src1, char *src2, int label, ostream &s)
{
  s << BLEQ << src1 << " " << src2 << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_blt(char *src1, char *src2, int label, ostream &s)
{
  s << BLT << src1 << " " << src2 << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_blti(char *src1, int imm, int label, ostream &s)
{
  s << BLT << src1 << " " << imm << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_bgti(char *src1, int imm, int label, ostream &s)
{
  s << BGT << src1 << " " << imm << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_branch(int l, ostream& s)
{
  s << BRANCH;
  emit_label_ref(l,s);
  s << endl;
}

static void emit_push(char *reg, ostream& str)
{
  emit_store(reg,0,SP,str);
  emit_addiu(SP,SP,-4,str);
}


static void emit_fetch_int(char *dest, char *source, ostream& s)
{ emit_load(dest, DEFAULT_OBJFIELDS, source, s); }


static void emit_store_int(char *source, char *dest, ostream& s)
{ emit_store(source, DEFAULT_OBJFIELDS, dest, s); }


static void emit_test_collector(ostream &s)
{
  emit_push(ACC, s);
  emit_move(ACC, SP, s); // stack end
  emit_move(A1, ZERO, s); // allocate nothing
  s << JAL << gc_collect_names[cgen_Memmgr] << endl;
  emit_addiu(SP,SP,4,s);
  emit_load(ACC,0,SP,s);
}

static void emit_gc_check(char *source, ostream &s)
{
  if (source != (char*)A1) emit_move(A1, source, s);
  s << JAL << "_gc_check" << endl;
}


// --- 常量表 Entry 方法 ---
void StringEntry::code_ref(ostream& s)
{
  s << STRCONST_PREFIX << index;
}

void StringEntry::code_def(ostream& s, int stringclasstag)
{
  IntEntryP lensym = inttable.add_int(len);
  s << WORD << "-1" << endl;
  code_ref(s);  s  << LABEL 
      << WORD << stringclasstag << endl 
      << WORD << (DEFAULT_OBJFIELDS + STRING_SLOTS + (len+4)/4) << endl 
      << WORD;
      s << Str << DISPTAB_SUFFIX << endl; 
      s << WORD;  lensym->code_ref(s);  s << endl;
  emit_string_constant(s,str);
  s << ALIGN; 
}

void StrTable::code_string_table(ostream& s, int stringclasstag)
{  
  for (List<StringEntry> *l = tbl; l; l = l->tl())
    l->hd()->code_def(s,stringclasstag);
}

void IntEntry::code_ref(ostream &s)
{
  s << INTCONST_PREFIX << index;
}

void IntEntry::code_def(ostream &s, int intclasstag)
{
  s << WORD << "-1" << endl;
  code_ref(s);  s << LABEL 
      << WORD << intclasstag << endl 
      << WORD << (DEFAULT_OBJFIELDS + INT_SLOTS) << endl 
      << WORD; 
      s << Int << DISPTAB_SUFFIX << endl; 
      s << WORD << str << endl; 
}

void IntTable::code_string_table(ostream &s, int intclasstag)
{
  for (List<IntEntry> *l = tbl; l; l = l->tl())
    l->hd()->code_def(s,intclasstag);
}

BoolConst::BoolConst(int i) : val(i) { assert(i == 0 || i == 1); }

void BoolConst::code_ref(ostream& s) const
{
  s << BOOLCONST_PREFIX << val;
}
  
void BoolConst::code_def(ostream& s, int boolclasstag)
{
  s << WORD << "-1" << endl;
  code_ref(s);  s << LABEL 
      << WORD << boolclasstag << endl 
      << WORD << (DEFAULT_OBJFIELDS + BOOL_SLOTS) << endl 
      << WORD;
      s << Bool << DISPTAB_SUFFIX << endl; 
      s << WORD << val << endl; 
}

// --- CgenClassTable 方法 ---

CgenClassTable::CgenClassTable(Classes classes, ostream& s) : nds(NULL) , str(s)
{
  extern CgenClassTable *global_classtable;
  global_classtable = this;

   stringclasstag = 4;
   intclasstag =    2;
   boolclasstag =   3;

   enterscope();
   if (cgen_debug) cout << "Building CgenClassTable" << endl;
   install_basic_classes();
   install_classes(classes);
   build_inheritance_tree();

   // 分配标签 (DFS)
   int tag = 0;
   SetClassTags(root(), tag);

   code();
   exitscope();
}

void CgenClassTable::install_basic_classes()
{
  Symbol filename = stringtable.add_string("<basic class>");
  
  addid(No_class, new CgenNode(class_(No_class,No_class,nil_Features(),filename), Basic,this));
  addid(SELF_TYPE, new CgenNode(class_(SELF_TYPE,No_class,nil_Features(),filename), Basic,this));
  addid(prim_slot, new CgenNode(class_(prim_slot,No_class,nil_Features(),filename), Basic,this));

  install_class(new CgenNode(class_(Object, No_class,
	   append_Features(append_Features(
           single_Features(method(cool_abort, nil_Formals(), Object, no_expr())),
           single_Features(method(type_name, nil_Formals(), Str, no_expr()))),
           single_Features(method(copy, nil_Formals(), SELF_TYPE, no_expr()))),
	   filename), Basic,this));

   install_class(new CgenNode(class_(IO, Object,
            append_Features(append_Features(append_Features(
            single_Features(method(out_string, single_Formals(formal(arg, Str)), SELF_TYPE, no_expr())),
            single_Features(method(out_int, single_Formals(formal(arg, Int)), SELF_TYPE, no_expr()))),
            single_Features(method(in_string, nil_Formals(), Str, no_expr()))),
            single_Features(method(in_int, nil_Formals(), Int, no_expr()))),
	   filename), Basic,this));

   install_class(new CgenNode(class_(Int, Object, single_Features(attr(val, prim_slot, no_expr())), filename), Basic,this));
   install_class(new CgenNode(class_(Bool, Object, single_Features(attr(val, prim_slot, no_expr())),filename), Basic,this));
   install_class(new CgenNode(class_(Str, Object,
             append_Features(append_Features(append_Features(append_Features(
             single_Features(attr(val, Int, no_expr())),
            single_Features(attr(str_field, prim_slot, no_expr()))),
            single_Features(method(length, nil_Formals(), Int, no_expr()))),
            single_Features(method(concat, single_Formals(formal(arg, Str)), Str, no_expr()))),
	    single_Features(method(substr, append_Formals(single_Formals(formal(arg, Int)), 
						  single_Formals(formal(arg2, Int))), Str, no_expr()))),
	     filename), Basic,this));
}

void CgenClassTable::install_class(CgenNodeP nd)
{
  Symbol name = nd->get_name();
  if (probe(name)) return;
  nds = new List<CgenNode>(nd,nds);
  addid(name,nd);
}

void CgenClassTable::install_classes(Classes cs)
{
  for(int i = cs->first(); cs->more(i); i = cs->next(i))
    install_class(new CgenNode(cs->nth(i),NotBasic,this));
}

void CgenClassTable::build_inheritance_tree()
{
  for(List<CgenNode> *l = nds; l; l = l->tl())
      set_relations(l->hd());
}

void CgenClassTable::set_relations(CgenNodeP nd)
{
  CgenNode *parent_node = probe(nd->get_parent());
  nd->set_parentnd(parent_node);
  parent_node->add_child(nd);
}

void CgenNode::add_child(CgenNodeP n)
{
  children = new List<CgenNode>(n,children);
}

void CgenNode::set_parentnd(CgenNodeP p)
{
  assert(parentnd == NULL);
  assert(p != NULL);
  parentnd = p;
}

// 深度优先分配标签，以支持子类范围检查
void CgenClassTable::SetClassTags(CgenNode* node, int& tag) {
    node->class_tag = tag++;
    if (node->name == Str) stringclasstag = node->class_tag;
    else if (node->name == Int) intclasstag = node->class_tag;
    else if (node->name == Bool) boolclasstag = node->class_tag;
    
    m_class_tags[node->name] = node->class_tag;
    
    // 递归处理子类
    List<CgenNode>* children = node->get_children();
    for (List<CgenNode>* l = children; l; l = l->tl()) {
        SetClassTags(l->hd(), tag);
    }
    node->max_child_tag = tag - 1; // 记录该子树的最大标签值
}

std::vector<CgenNode*> CgenClassTable::GetClassNodes() {
    if (m_class_nodes.empty()) {
        for (List<CgenNode> *l = nds; l; l = l->tl()) {
            m_class_nodes.push_back(l->hd());
        }
        // 反转以保持定义的顺序（虽然不太重要，但为了确定性）
        std::reverse(m_class_nodes.begin(), m_class_nodes.end());
    }
    return m_class_nodes;
}

void CgenClassTable::code()
{
  if (cgen_debug) cout << "coding global data" << endl;
  code_global_data();

  if (cgen_debug) cout << "choosing gc" << endl;
  code_select_gc();

  if (cgen_debug) cout << "coding constants" << endl;
  code_constants();

  code_class_nameTab();
  code_class_objTab();
  code_dispatchTabs();
  code_protObjs();

  if (cgen_debug) cout << "coding global text" << endl;
  code_global_text();
  
  code_class_inits();
  code_class_methods();
}

CgenNodeP CgenClassTable::root()
{
   return probe(Object);
}

// --- 数据生成方法 ---

void CgenClassTable::code_global_data()
{
  Symbol main    = idtable.lookup_string(MAINNAME);
  Symbol string  = idtable.lookup_string(STRINGNAME);
  Symbol integer = idtable.lookup_string(INTNAME);
  Symbol boolc   = idtable.lookup_string(BOOLNAME);

  str << "\t.data\n" << ALIGN;
  str << GLOBAL << CLASSNAMETAB << endl;
  str << GLOBAL; emit_protobj_ref(main,str);    str << endl;
  str << GLOBAL; emit_protobj_ref(integer,str); str << endl;
  str << GLOBAL; emit_protobj_ref(string,str);  str << endl;
  str << GLOBAL; falsebool.code_ref(str);  str << endl;
  str << GLOBAL; truebool.code_ref(str);   str << endl;
  str << GLOBAL << INTTAG << endl;
  str << GLOBAL << BOOLTAG << endl;
  str << GLOBAL << STRINGTAG << endl;

  str << INTTAG << LABEL
      << WORD << intclasstag << endl;
  str << BOOLTAG << LABEL 
      << WORD << boolclasstag << endl;
  str << STRINGTAG << LABEL 
      << WORD << stringclasstag << endl;    
}

void CgenClassTable::code_select_gc()
{
  str << GLOBAL << "_MemMgr_INITIALIZER" << endl;
  str << "_MemMgr_INITIALIZER:" << endl;
  str << WORD << gc_init_names[cgen_Memmgr] << endl;
  str << GLOBAL << "_MemMgr_COLLECTOR" << endl;
  str << "_MemMgr_COLLECTOR:" << endl;
  str << WORD << gc_collect_names[cgen_Memmgr] << endl;
  str << GLOBAL << "_MemMgr_TEST" << endl;
  str << "_MemMgr_TEST:" << endl;
  str << WORD << (cgen_Memmgr_Test == GC_TEST) << endl;
}

void CgenClassTable::code_constants()
{
  stringtable.add_string("");
  inttable.add_string("0");
  stringtable.code_string_table(str,stringclasstag);
  inttable.code_string_table(str,intclasstag);
  code_bools(boolclasstag);
}

void CgenClassTable::code_class_nameTab() {
    str << CLASSNAMETAB << LABEL;
    // 需要按照 tag 的顺序输出
    std::vector<CgenNode*> ordered_nodes(GetClassNodes().size());
    for (CgenNode* n : GetClassNodes()) {
        ordered_nodes[n->class_tag] = n;
    }
    
    for (CgenNode* node : ordered_nodes) {
        str << WORD;
        stringtable.lookup_string(node->name->get_string())->code_ref(str);
        str << endl;
    }
}

void CgenClassTable::code_class_objTab() {
    str << CLASSOBJTAB << LABEL;
    std::vector<CgenNode*> ordered_nodes(GetClassNodes().size());
    for (CgenNode* n : GetClassNodes()) {
        ordered_nodes[n->class_tag] = n;
    }

    for (CgenNode* node : ordered_nodes) {
        str << WORD; emit_protobj_ref(node->name, str); str << endl;
        str << WORD; emit_init_ref(node->name, str); str << endl;
    }
}

void CgenClassTable::code_dispatchTabs() {
    std::vector<CgenNode*> nodes = GetClassNodes();
    for (CgenNode* node : nodes) {
        emit_disptable_ref(node->name, str); str << LABEL;
        std::vector<method_class*> methods = node->GetFullMethods();
        std::map<Symbol, Symbol> class_map = node->GetDispatchClassTab();
        for (method_class* m : methods) {
            str << WORD;
            emit_method_ref(class_map[m->name], m->name, str);
            str << endl;
        }
    }
}

void CgenClassTable::code_protObjs() {
    std::vector<CgenNode*> nodes = GetClassNodes();
    for (CgenNode* node : nodes) {
        node->code_protObj(str);
    }
}

void CgenClassTable::code_global_text()
{
  str << GLOBAL << HEAP_START << endl
      << HEAP_START << LABEL 
      << WORD << 0 << endl
      << "\t.text" << endl
      << GLOBAL;
  emit_init_ref(idtable.add_string("Main"), str);
  str << endl << GLOBAL;
  emit_init_ref(idtable.add_string("Int"),str);
  str << endl << GLOBAL;
  emit_init_ref(idtable.add_string("String"),str);
  str << endl << GLOBAL;
  emit_init_ref(idtable.add_string("Bool"),str);
  str << endl << GLOBAL;
  emit_method_ref(idtable.add_string("Main"), idtable.add_string("main"), str);
  str << endl;
}

void CgenClassTable::code_class_inits() {
    std::vector<CgenNode*> nodes = GetClassNodes();
    for (CgenNode* node : nodes) {
        node->code_init(str);
    }
}

void CgenClassTable::code_class_methods() {
    std::vector<CgenNode*> nodes = GetClassNodes();
    for (CgenNode* node : nodes) {
        if (!node->basic()) {
            node->code_methods(str);
        }
    }
}

void CgenClassTable::code_bools(int boolclasstag)
{
  falsebool.code_def(str,boolclasstag);
  truebool.code_def(str,boolclasstag);
}

// --- CgenNode 方法 ---

CgenNode::CgenNode(Class_ nd, Basicness bstatus, CgenClassTableP ct) :
   class__class((const class__class &) *nd),
   parentnd(NULL),
   children(NULL),
   basic_status(bstatus)
{ 
   stringtable.add_string(name->get_string());
}

std::vector<CgenNode*> CgenNode::GetInheritance() {
    if (m_inheritance.empty()) {
        CgenNode* curr = this;
        while (curr->name != No_class) {
            m_inheritance.push_back(curr);
            curr = curr->get_parentnd();
        }
        std::reverse(m_inheritance.begin(), m_inheritance.end());
    }
    return m_inheritance;
}

std::vector<attr_class*> CgenNode::GetFullAttribs() {
    if (m_full_attribs.empty()) {
        std::vector<CgenNode*> chain = GetInheritance();
        int offset = 0;
        for (CgenNode* node : chain) {
            Features fs = node->features;
            for (int i = fs->first(); fs->more(i); i = fs->next(i)) {
                if (!fs->nth(i)->IsMethod()) {
                    attr_class* a = (attr_class*)fs->nth(i);
                    m_full_attribs.push_back(a);
                    m_attrib_idx_tab[a->name] = offset++;
                }
            }
        }
    }
    return m_full_attribs;
}

std::vector<method_class*> CgenNode::GetFullMethods() {
    if (m_full_methods.empty()) {
        std::vector<CgenNode*> chain = GetInheritance();
        for (CgenNode* node : chain) {
            Features fs = node->features;
            for (int i = fs->first(); fs->more(i); i = fs->next(i)) {
                if (fs->nth(i)->IsMethod()) {
                    method_class* m = (method_class*)fs->nth(i);
                    if (m_dispatch_idx_tab.find(m->name) == m_dispatch_idx_tab.end()) {
                        m_dispatch_idx_tab[m->name] = m_full_methods.size();
                        m_full_methods.push_back(m);
                        m_dispatch_class_tab[m->name] = node->name;
                    } else {
                        int idx = m_dispatch_idx_tab[m->name];
                        m_full_methods[idx] = m;
                        m_dispatch_class_tab[m->name] = node->name;
                    }
                }
            }
        }
    }
    return m_full_methods;
}

// 确保在返回映射表之前，相关的数据已经被初始化（通过调用 GetFull...）
std::map<Symbol, int>& CgenNode::GetDispatchIdxTab() {
  GetFullMethods(); // 确保分发表已构建
  return m_dispatch_idx_tab;
}

std::map<Symbol, Symbol>& CgenNode::GetDispatchClassTab() {
  GetFullMethods(); // 确保分发表已构建
  return m_dispatch_class_tab;
}

std::map<Symbol, int>& CgenNode::GetAttribIdxTab() {
  GetFullAttribs(); // 确保属性表已构建
  return m_attrib_idx_tab;
}

std::vector<method_class*> CgenNode::GetMethods() {
  std::vector<method_class*> methods;
  for(int i = features->first(); features->more(i); i = features->next(i)) {
      if (features->nth(i)->IsMethod())
          methods.push_back((method_class*)features->nth(i));
  }
  return methods;
}

std::vector<attr_class*> CgenNode::GetAttribs() {
  std::vector<attr_class*> attribs;
  for(int i = features->first(); features->more(i); i = features->next(i)) {
      if (!features->nth(i)->IsMethod())
          attribs.push_back((attr_class*)features->nth(i));
  }
  return attribs;
}


void CgenNode::code_protObj(ostream& s) {
    std::vector<attr_class*> attrs = GetFullAttribs();
    s << WORD << "-1" << endl;
    emit_protobj_ref(name, s); s << LABEL;
    s << WORD << class_tag << "\t# class tag" << endl;
    s << WORD << (DEFAULT_OBJFIELDS + attrs.size()) << "\t# size" << endl;
    s << WORD; emit_disptable_ref(name, s); s << endl;
    for (attr_class* a : attrs) {
        s << WORD;
        if (a->type_decl == Int) inttable.lookup_string("0")->code_ref(s);
        else if (a->type_decl == Str) stringtable.lookup_string("")->code_ref(s);
        else if (a->type_decl == Bool) falsebool.code_ref(s);
        else s << "0";
        s << endl;
    }
}

void CgenNode::code_init(ostream& s) {
    emit_init_ref(name, s); s << LABEL;
    emit_addiu(SP, SP, -12, s);
    emit_store(FP, 3, SP, s);
    emit_store(SELF, 2, SP, s);
    emit_store(RA, 1, SP, s);
    emit_addiu(FP, SP, 4, s);
    emit_move(SELF, ACC, s);

    if (parentnd && name != Object) {
        s << JAL; emit_init_ref(parentnd->name, s); s << endl;
    }

    Features fs = features;
    for (int i = fs->first(); fs->more(i); i = fs->next(i)) {
        if (!fs->nth(i)->IsMethod()) {
            attr_class* a = (attr_class*)fs->nth(i);
            if (!(a->init->get_type() == NULL)) { 
                Environment env;
                env.m_class_node = this;
                a->init->code(s, env);
                int idx = m_attrib_idx_tab[a->name];
                emit_store(ACC, idx + DEFAULT_OBJFIELDS, SELF, s);
                // GC Assign
                if (cgen_Memmgr == 1) {
                    emit_addiu(A1, SELF, 4 * (idx + DEFAULT_OBJFIELDS), s);
                    emit_gc_assign(s);
                }
            }
        }
    }

    emit_move(ACC, SELF, s);
    emit_load(FP, 3, SP, s);
    emit_load(SELF, 2, SP, s);
    emit_load(RA, 1, SP, s);
    emit_addiu(SP, SP, 12, s);
    emit_return(s);
}

void CgenNode::code_methods(ostream& s) {
    Features fs = features;
    for (int i = fs->first(); fs->more(i); i = fs->next(i)) {
        if (fs->nth(i)->IsMethod()) {
            method_class* m = (method_class*)fs->nth(i);
            emit_method_ref(name, m->name, s); s << LABEL;
            
            emit_addiu(SP, SP, -12, s);
            emit_store(FP, 3, SP, s);
            emit_store(SELF, 2, SP, s);
            emit_store(RA, 1, SP, s);
            emit_addiu(FP, SP, 4, s);
            emit_move(SELF, ACC, s);

            Environment env;
            env.m_class_node = this;
            for (int j = 0; j < m->GetArgNum(); ++j) {
                formal_class* f = (formal_class*)m->formals->nth(j);
                env.AddParam(f->GetName(), m->GetArgNum() - 1 - j);
            }

            m->expr->code(s, env);

            emit_load(FP, 3, SP, s);
            emit_load(SELF, 2, SP, s);
            emit_load(RA, 1, SP, s);
            emit_addiu(SP, SP, 12, s);
            emit_addiu(SP, SP, m->GetArgNum() * 4, s); 
            

            emit_return(s);
        }
    }
}

// --- 表达式代码生成 (Expression Code Generation) ---

int labelnum = 0;

void assign_class::code(ostream &s, Environment env) {
  expr->code(s, env);
  int idx;
  if ((idx = env.LookUpVar(name)) != -1) {
      // --- 核心修复：使用动态偏移 ---
      int offset = env.GetNextVarOffset() - idx;
      emit_store(ACC, offset, SP, s);
      // ---------------------------
      
      if (cgen_Memmgr == 1) {
          emit_addiu(A1, SP, 4 * offset, s);
          emit_gc_assign(s);
      }
  } else if ((idx = env.LookUpParam(name)) != -1) {
      emit_store(ACC, idx + 3, FP, s);
      if (cgen_Memmgr == 1) {
          emit_addiu(A1, FP, 4 * (idx + 3), s);
          emit_gc_assign(s);
      }
  } else if ((idx = env.LookUpAttrib(name)) != -1) {
      emit_store(ACC, idx + DEFAULT_OBJFIELDS, SELF, s);
      if (cgen_Memmgr == 1) {
          emit_addiu(A1, SELF, 4 * (idx + DEFAULT_OBJFIELDS), s);
          emit_gc_assign(s);
      }
  }
}

void static_dispatch_class::code(ostream &s, Environment env) {
    std::vector<Expression> actuals = GetActuals();
    for (Expression e : actuals) {
        e->code(s, env);
        emit_push(ACC, s);
        env.AddObstacle();
    }
    
    expr->code(s, env);
    
    int not_void_label = labelnum++;
    emit_bne(ACC, ZERO, not_void_label, s);
    emit_load_string(ACC, stringtable.lookup_string(env.m_class_node->get_filename()->get_string()), s);
    emit_load_imm(T1, 1, s);
    emit_jal("_dispatch_abort", s);
    emit_label_def(not_void_label, s);

    std::string class_name_str = type_name->get_string();
    std::string disp_tab_str = class_name_str + DISPTAB_SUFFIX;
    emit_load_address(T1, (char*)disp_tab_str.c_str(), s);
    
    // 假设 CgenClassTable 是全局可访问的，或者我们需要传递它。
    // 在这个架构中，我们通常需要查找 type_name 对应的 Node。
    // 由于 CgenClassTable 没有全局实例，我们这里简化假设:
    // 我们必须从 type_name 对应的类节点获取方法索引。
    // 这是一个常见的困难点。通常 codegen_classtable 是在 cgen 方法中定义的局部变量。
    // 解决方案：使用全局变量或者假定方法索引在编译期确定。
    // 这里我们 Hack 一下：我们无法直接获取 CgenNode，但我们知道 dispatch table 布局是确定的。
    // 我们需要一个全局指针指向 codegen_classtable。
    // 为了通过编译，我们需要在文件头部加一个全局指针（在 initialize_constants 后）
    // 并在 program_class::cgen 中赋值。
    
    // *注意*：为了让下面的代码工作，请在文件顶部 initialize_constants 下方添加：
    // CgenClassTable *global_classtable;
    // 并在 program_class::cgen 中： global_classtable = new CgenClassTable...;
    
    // 这里假设已经有了 global_classtable:
    extern CgenClassTable *global_classtable;
    CgenNode* target_node = global_classtable->GetClassNode(type_name);
    int idx = target_node->GetDispatchIdxTab()[name];
    
    emit_load(T1, idx, T1, s);
    emit_jalr(T1, s);


    for (size_t i = 0; i < actuals.size(); ++i) env.RemoveObstacle();
}

void dispatch_class::code(ostream &s, Environment env) {
    std::vector<Expression> actuals = GetActuals();
    for (Expression e : actuals) {
        e->code(s, env);
        emit_push(ACC, s);
        env.AddObstacle();
    }

    expr->code(s, env);

    int not_void_label = labelnum++;
    emit_bne(ACC, ZERO, not_void_label, s);
    emit_load_string(ACC, stringtable.lookup_string(env.m_class_node->get_filename()->get_string()), s);
    emit_load_imm(T1, 1, s);
    emit_jal("_dispatch_abort", s);
    emit_label_def(not_void_label, s);

    extern CgenClassTable *global_classtable;
    Symbol type = expr->get_type();
    Symbol class_name = (type == SELF_TYPE) ? env.m_class_node->name : type;
    CgenNode* node = global_classtable->GetClassNode(class_name);
    int idx = node->GetDispatchIdxTab()[name];

    emit_load(T1, 2, ACC, s); // load dispatch table
    emit_load(T1, idx, T1, s);
    emit_jalr(T1, s);


    for (size_t i = 0; i < actuals.size(); ++i) env.RemoveObstacle();
}

void cond_class::code(ostream &s, Environment env) {
    pred->code(s, env);
    emit_fetch_int(T1, ACC, s);
    int false_label = labelnum++;
    int end_label = labelnum++;
    emit_beq(T1, ZERO, false_label, s);
    then_exp->code(s, env);
    emit_branch(end_label, s);
    emit_label_def(false_label, s);
    else_exp->code(s, env);
    emit_label_def(end_label, s);
}

void loop_class::code(ostream &s, Environment env) {
    int start_label = labelnum++;
    int end_label = labelnum++;
    emit_label_def(start_label, s);
    pred->code(s, env);
    emit_fetch_int(T1, ACC, s);
    emit_beq(T1, ZERO, end_label, s);
    body->code(s, env);
    emit_branch(start_label, s);
    emit_label_def(end_label, s);
    emit_move(ACC, ZERO, s);
}

void typcase_class::code(ostream &s, Environment env) {
  expr->code(s, env);
  
  int not_void = labelnum++;
  emit_bne(ACC, ZERO, not_void, s);
  emit_load_string(ACC, stringtable.lookup_string(env.m_class_node->get_filename()->get_string()), s);
  emit_load_imm(T1, 1, s);
  emit_jal("_case_abort2", s);
  emit_label_def(not_void, s);
  
  emit_load(T1, 0, ACC, s); // T1 = class tag
  
  std::vector<Case> cases_vec = GetCases();
  extern CgenClassTable *global_classtable;

  // 排序：使用 branch_class* 进行访问
  std::sort(cases_vec.begin(), cases_vec.end(), [&](Case a, Case b) {
      branch_class* b1 = (branch_class*)a;
      branch_class* b2 = (branch_class*)b;
      CgenNode* nodeA = global_classtable->GetClassNode(b1->type_decl);
      CgenNode* nodeB = global_classtable->GetClassNode(b2->type_decl);
      return nodeA->GetInheritance().size() > nodeB->GetInheritance().size();
  });

  int end_label = labelnum++;
  
  for (Case c : cases_vec) {
      // 强制转换
      branch_class* b = (branch_class*)c;

      int next_case = labelnum++;
      CgenNode* typeNode = global_classtable->GetClassNode(b->type_decl);
      int min_tag = typeNode->class_tag;
      int max_tag = typeNode->max_child_tag;
      
      // Range Check: min_tag <= tag <= max_tag
      emit_blti(T1, min_tag, next_case, s);
      emit_bgti(T1, max_tag, next_case, s);
      
      // Match!
      env.EnterScope();
      env.AddVar(b->name);
      emit_push(ACC, s); // bind variable
      b->expr->code(s, env);
      emit_addiu(SP, SP, 4, s); // unbind
      env.ExitScope();
      
      emit_branch(end_label, s);
      emit_label_def(next_case, s);
  }
  
  emit_jal("_case_abort", s);
  emit_label_def(end_label, s);
}

void block_class::code(ostream &s, Environment env) {
    for (int i = body->first(); body->more(i); i = body->next(i))
        body->nth(i)->code(s, env);
}

void let_class::code(ostream &s, Environment env) {
  // 1. 计算初始值
  // 修复：检查 init 是否为 no_expr (类型为 No_type)
  if (init->get_type() == No_type) {
      // Default init
      if (type_decl == Int) emit_load_int(ACC, inttable.lookup_string("0"), s);
      else if (type_decl == Str) emit_load_string(ACC, stringtable.lookup_string(""), s);
      else if (type_decl == Bool) emit_load_bool(ACC, BoolConst(0), s);
      else emit_move(ACC, ZERO, s); // Object/Class defaults to void (0)
  } else {
      // User init
      init->code(s, env);
  }
  
  // 2. 进入作用域
  env.EnterScope();
  env.AddVar(identifier);
  
  // 3. 压栈 (保存变量)
  emit_push(ACC, s);
  
  // 4. 生成 body
  body->code(s, env);
  
  // 5. 弹栈 (清理变量)
  emit_addiu(SP, SP, 4, s);
  
  // 6. 退出作用域
  env.ExitScope();
}

void plus_class::code(ostream &s, Environment env) {
    e1->code(s, env);
    emit_push(ACC, s);
    env.AddObstacle();
    e2->code(s, env);
    emit_jal("Object.copy", s);
    emit_load(T1, 1, SP, s);
    emit_addiu(SP, SP, 4, s);
    env.RemoveObstacle();
    emit_load(T1, DEFAULT_OBJFIELDS, T1, s);
    emit_load(T2, DEFAULT_OBJFIELDS, ACC, s);
    emit_add(T3, T1, T2, s);
    emit_store(T3, DEFAULT_OBJFIELDS, ACC, s);
}

void sub_class::code(ostream &s, Environment env) {
    e1->code(s, env);
    emit_push(ACC, s);
    env.AddObstacle();
    e2->code(s, env);
    emit_jal("Object.copy", s);
    emit_load(T1, 1, SP, s);
    emit_addiu(SP, SP, 4, s);
    env.RemoveObstacle();
    emit_load(T1, DEFAULT_OBJFIELDS, T1, s);
    emit_load(T2, DEFAULT_OBJFIELDS, ACC, s);
    emit_sub(T3, T1, T2, s);
    emit_store(T3, DEFAULT_OBJFIELDS, ACC, s);
}

void mul_class::code(ostream &s, Environment env) {
    e1->code(s, env);
    emit_push(ACC, s);
    env.AddObstacle();
    e2->code(s, env);
    emit_jal("Object.copy", s);
    emit_load(T1, 1, SP, s);
    emit_addiu(SP, SP, 4, s);
    env.RemoveObstacle();
    emit_load(T1, DEFAULT_OBJFIELDS, T1, s);
    emit_load(T2, DEFAULT_OBJFIELDS, ACC, s);
    emit_mul(T3, T1, T2, s);
    emit_store(T3, DEFAULT_OBJFIELDS, ACC, s);
}

void divide_class::code(ostream &s, Environment env) {
    e1->code(s, env);
    emit_push(ACC, s);
    env.AddObstacle();
    e2->code(s, env);
    emit_jal("Object.copy", s);
    emit_load(T1, 1, SP, s);
    emit_addiu(SP, SP, 4, s);
    env.RemoveObstacle();
    emit_load(T1, DEFAULT_OBJFIELDS, T1, s);
    emit_load(T2, DEFAULT_OBJFIELDS, ACC, s);
    emit_div(T3, T1, T2, s);
    emit_store(T3, DEFAULT_OBJFIELDS, ACC, s);
}

void neg_class::code(ostream &s, Environment env) {
    e1->code(s, env);
    emit_jal("Object.copy", s);
    emit_load(T1, DEFAULT_OBJFIELDS, ACC, s);
    emit_neg(T1, T1, s);
    emit_store(T1, DEFAULT_OBJFIELDS, ACC, s);
}

void lt_class::code(ostream &s, Environment env) {
    e1->code(s, env);
    emit_push(ACC, s);
    env.AddObstacle();
    e2->code(s, env);
    emit_load(T1, 1, SP, s);
    emit_addiu(SP, SP, 4, s);
    env.RemoveObstacle();
    emit_load(T1, DEFAULT_OBJFIELDS, T1, s);
    emit_load(T2, DEFAULT_OBJFIELDS, ACC, s);
    emit_load_bool(ACC, BoolConst(1), s);
    int label = labelnum++;
    emit_blt(T1, T2, label, s);
    emit_load_bool(ACC, BoolConst(0), s);
    emit_label_def(label, s);
}

void eq_class::code(ostream &s, Environment env) {
    e1->code(s, env);
    emit_push(ACC, s);
    env.AddObstacle();
    e2->code(s, env);
    emit_move(T2, ACC, s);
    emit_load(T1, 1, SP, s);
    emit_addiu(SP, SP, 4, s);
    env.RemoveObstacle();
    
    int true_label = labelnum++;
    int end_label = labelnum++;
    
    // 如果直接指针相等，则为真
    emit_beq(T1, T2, true_label, s);
    
    // 调用 equality_test
    emit_load_bool(ACC, BoolConst(1), s);
    emit_load_bool(A1, BoolConst(0), s);
    emit_jal("equality_test", s);
    emit_branch(end_label, s);
    
    emit_label_def(true_label, s);
    emit_load_bool(ACC, BoolConst(1), s);
    emit_label_def(end_label, s);
}

void leq_class::code(ostream &s, Environment env) {
    e1->code(s, env);
    emit_push(ACC, s);
    env.AddObstacle();
    e2->code(s, env);
    emit_load(T1, 1, SP, s);
    emit_addiu(SP, SP, 4, s);
    env.RemoveObstacle();
    emit_load(T1, DEFAULT_OBJFIELDS, T1, s);
    emit_load(T2, DEFAULT_OBJFIELDS, ACC, s);
    emit_load_bool(ACC, BoolConst(1), s);
    int label = labelnum++;
    emit_bleq(T1, T2, label, s);
    emit_load_bool(ACC, BoolConst(0), s);
    emit_label_def(label, s);
}

void comp_class::code(ostream &s, Environment env) {
    e1->code(s, env);
    emit_load(T1, DEFAULT_OBJFIELDS, ACC, s);
    int label = labelnum++;
    emit_load_bool(ACC, BoolConst(1), s);
    emit_beqz(T1, label, s);
    emit_load_bool(ACC, BoolConst(0), s);
    emit_label_def(label, s);
}

void int_const_class::code(ostream& s, Environment env)  
{
  emit_load_int(ACC,inttable.lookup_string(token->get_string()),s);
}

void string_const_class::code(ostream& s, Environment env)
{
  emit_load_string(ACC,stringtable.lookup_string(token->get_string()),s);
}

void bool_const_class::code(ostream& s, Environment env)
{
  emit_load_bool(ACC, BoolConst(val), s);
}

void new__class::code(ostream &s, Environment env) {
    if (type_name == SELF_TYPE) {
        emit_load_address(T1, "class_objTab", s);
        emit_load(T2, 0, SELF, s); // class tag
        emit_sll(T2, T2, 3, s);
        emit_addu(T1, T1, T2, s);
        emit_push(T1, s);
        emit_load(ACC, 0, T1, s); // protObj
        emit_jal("Object.copy", s);
        emit_load(T1, 1, SP, s);
        emit_addiu(SP, SP, 4, s);
        emit_load(T1, 1, T1, s); // init
        emit_jalr(T1, s);
    } else {
        std::string proto = type_name->get_string();
        proto += PROTOBJ_SUFFIX;
        emit_load_address(ACC, (char*)proto.c_str(), s);
        emit_jal("Object.copy", s);
        std::string init = type_name->get_string();
        init += CLASSINIT_SUFFIX;
        emit_jal((char*)init.c_str(), s);
    }
}

void isvoid_class::code(ostream &s, Environment env) {
    e1->code(s, env);
    emit_move(T1, ACC, s);
    emit_load_bool(ACC, BoolConst(1), s);
    int label = labelnum++;
    emit_beqz(T1, label, s);
    emit_load_bool(ACC, BoolConst(0), s);
    emit_label_def(label, s);
}

void no_expr_class::code(ostream &s, Environment env) {
    // No code needed, usually handled by caller (like let init)
    // Or return 0/void
    emit_move(ACC, ZERO, s);
}

void object_class::code(ostream &s, Environment env) {
  if (name == self) {
      emit_move(ACC, SELF, s);
      return;
  }
  int idx;
  if ((idx = env.LookUpVar(name)) != -1) {
      // --- 核心修复：使用动态偏移 ---
      int offset = env.GetNextVarOffset() - idx;
      emit_load(ACC, offset, SP, s);
      // ---------------------------
  } else if ((idx = env.LookUpParam(name)) != -1) {
      emit_load(ACC, idx + 3, FP, s);
  } else if ((idx = env.LookUpAttrib(name)) != -1) {
      emit_load(ACC, idx + DEFAULT_OBJFIELDS, SELF, s);
  }
}

// 定义全局 ClassTable 指针，供 Expressions 使用
CgenClassTable *global_classtable = NULL;