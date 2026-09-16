%{
#include "Frontend.hpp"
#include "lib/AST.hpp"

#include <iostream>
#include <string>
%}

%language "C++"
%define api.namespace {yy}
%define api.parser.class {parser}
%define parse.error verbose

%code requires {
#include "lib/AST.hpp"

#include <string>

// 标识符 Token 同时携带名称与源码起始行号，供 FuncCall 记录被调函数行号。
struct IdentInfo {
    std::string name;
    int line;
};
}

%code {
// 由 Flex 生成的扫描器提供桥接函数：返回下一个 Token 并写入语义值。
int yylex(yy::parser::semantic_type *sem);
}

%union {
    int            int_val;
    float          float_val;
    IdentInfo     *ident_val;
    BaseAST       *base_node;
    CompUnit      *comp_unit;
    ConstDecl     *const_decl;
    VarDecl       *var_decl;
    ConstDefList  *const_def_list;
    VarDefList    *var_def_list;
    ConstDef      *const_def;
    VarDef        *var_def;
    FuncDef       *func_def;
    FuncParam     *func_param;
    FuncParamList *func_param_list;
    InitValList   *init_val_list;
    InitVal       *init_val;
    Block         *block;
    BlockItemList *block_item_list;
    LVal          *lval;
    FuncCall      *func_call;
    FuncRParamList *func_r_param_list;
    ArrayList     *array_list;
    UnaryExp      *unary_exp;
    MulExp        *mul_exp;
    AddExp        *add_exp;
    RelExp        *rel_exp;
    EqExp         *eq_exp;
    LAndExp       *land_exp;
    LOrExp        *lor_exp;
}

// 物理载荷
%token <int_val>   INT_CONST
%token <float_val> FLOAT_CONST
%token <ident_val> IDENT

// 关键字与运算符
%token CONST INT FLOAT VOID
%token IF ELSE WHILE BREAK CONTINUE RETURN
%token LE GE EQ NE AND OR
%token LEX_ERROR

// 非终结符
%type <comp_unit> CompUnit
%type <base_node> Decl BlockItem Stmt PrimaryExp Number
%type <const_decl> ConstDecl
%type <var_decl> VarDecl
%type <const_def_list> ConstDefList
%type <var_def_list> VarDefList
%type <const_def> ConstDef
%type <var_def> VarDef
%type <func_def> FuncDef
%type <func_param> FuncParam
%type <func_param_list> FuncParamList
%type <block> Block
%type <block_item_list> BlockItemList
%type <init_val> InitVal
%type <init_val_list> InitValList
%type <lval> LVal
%type <func_r_param_list> FuncRParams
%type <array_list> ArrayList ArrayDims
%type <unary_exp> UnaryExp
%type <mul_exp> MulExp
%type <add_exp> AddExp Exp
%type <rel_exp> RelExp
%type <eq_exp> EqExp
%type <land_exp> LAndExp
%type <lor_exp> LOrExp Cond

// else 就近匹配
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%left OR
%left AND
%left EQ NE
%left '<' '>' LE GE
%left '+' '-'
%left '*' '/' '%'
%right '!' UMINUS

%%

CompUnit:
    Decl {
        $$ = new CompUnit($1);
        ASTRoot.reset($$);
    }
  | FuncDef {
        $$ = new CompUnit($1);
        ASTRoot.reset($$);
    }
  | CompUnit Decl {
        $1->pushBack($2);
        $$ = $1;
    }
  | CompUnit FuncDef {
        $1->pushBack($2);
        $$ = $1;
    }
  ;

Decl:
    ConstDecl { $$ = $1; }
  | VarDecl   { $$ = $1; }
  ;

ConstDecl:
    CONST INT ConstDefList ';' {
        $$ = new ConstDecl(SY_INT, $3);
    }
  | CONST FLOAT ConstDefList ';' {
        $$ = new ConstDecl(SY_FLOAT, $3);
    }
  ;

VarDecl:
    INT VarDefList ';' {
        $$ = new VarDecl(SY_INT, $2);
    }
  | FLOAT VarDefList ';' {
        $$ = new VarDecl(SY_FLOAT, $2);
    }
  ;

ConstDefList:
    ConstDef {
        $$ = new ConstDefList($1);
    }
  | ConstDefList ',' ConstDef {
        $1->pushBack($3);
        $$ = $1;
    }
  ;

VarDefList:
    VarDef {
        $$ = new VarDefList($1);
    }
  | VarDefList ',' VarDef {
        $1->pushBack($3);
        $$ = $1;
    }
  ;

ConstDef:
    IDENT ArrayDims '=' InitVal {
        $$ = new ConstDef($1->name, $2, $4);
        delete $1;
    }
  ;

VarDef:
    IDENT ArrayDims {
        $$ = new VarDef($1->name, $2, nullptr);
        delete $1;
    }
  | IDENT ArrayDims '=' InitVal {
        $$ = new VarDef($1->name, $2, $4);
        delete $1;
    }
  ;

FuncDef:
    INT IDENT '(' ')' Block {
        $$ = new FuncDef(SY_INT, $2->name, nullptr, $5);
        delete $2;
    }
  | FLOAT IDENT '(' ')' Block {
        $$ = new FuncDef(SY_FLOAT, $2->name, nullptr, $5);
        delete $2;
    }
  | VOID IDENT '(' ')' Block {
        $$ = new FuncDef(SY_VOID, $2->name, nullptr, $5);
        delete $2;
    }
  | INT IDENT '(' FuncParamList ')' Block {
        $$ = new FuncDef(SY_INT, $2->name, $4, $6);
        delete $2;
    }
  | FLOAT IDENT '(' FuncParamList ')' Block {
        $$ = new FuncDef(SY_FLOAT, $2->name, $4, $6);
        delete $2;
    }
  | VOID IDENT '(' FuncParamList ')' Block {
        $$ = new FuncDef(SY_VOID, $2->name, $4, $6);
        delete $2;
    }
  ;

FuncParamList:
    FuncParam {
        $$ = new FuncParamList($1);
    }
  | FuncParamList ',' FuncParam {
        $1->pushBack($3);
        $$ = $1;
    }
  ;

FuncParam:
    INT IDENT {
        $$ = new FuncParam(SY_INT, $2->name);
        delete $2;
    }
  | FLOAT IDENT {
        $$ = new FuncParam(SY_FLOAT, $2->name);
        delete $2;
    }
  | INT IDENT '[' ']' ArrayDims {
        $$ = new FuncParam(SY_INT, $2->name, true, $5);
        delete $2;
    }
  | FLOAT IDENT '[' ']' ArrayDims {
        $$ = new FuncParam(SY_FLOAT, $2->name, true, $5);
        delete $2;
    }
  ;

Block:
    '{' '}' {
        $$ = new Block(nullptr);
    }
  | '{' BlockItemList '}' {
        $$ = new Block($2);
    }
  ;

BlockItemList:
    BlockItem {
        $$ = new BlockItemList($1);
    }
  | BlockItemList BlockItem {
        $1->pushBack($2);
        $$ = $1;
    }
  ;

BlockItem:
    Decl { $$ = $1; }
  | Stmt { $$ = $1; }
  ;

Stmt:
    LVal '=' Exp ';' {
        $$ = new AssignStmt($1, $3);
    }
  | Exp ';' {
        $$ = new ExpStmt($1);
    }
  | ';' {
        $$ = new ExpStmt(nullptr);
    }
  | Block {
        $$ = $1;
    }
  | IF '(' Cond ')' Stmt %prec LOWER_THAN_ELSE {
        $$ = new IfStmt($3, $5);
    }
  | IF '(' Cond ')' Stmt ELSE Stmt {
        $$ = new IfStmt($3, $5, $7);
    }
  | WHILE '(' Cond ')' Stmt {
        $$ = new WhileStmt($3, $5);
    }
  | BREAK ';' {
        $$ = new BreakStmt();
    }
  | CONTINUE ';' {
        $$ = new ContinueStmt();
    }
  | RETURN Exp ';' {
        $$ = new ReturnStmt($2);
    }
  | RETURN ';' {
        $$ = new ReturnStmt();
    }
  ;

Exp:
    AddExp { $$ = $1; }
  ;

Cond:
    LOrExp { $$ = $1; }
  ;

LVal:
    IDENT ArrayDims {
        $$ = new LVal($1->name, $2);
        delete $1;
    }
  ;

PrimaryExp:
    '(' Exp ')' { $$ = $2; }
  | LVal        { $$ = $1; }
  | Number      { $$ = $1; }
  ;

Number:
    INT_CONST   { $$ = new ConValue<int>($1); }
  | FLOAT_CONST { $$ = new ConValue<float>($1); }
  ;

UnaryExp:
    PrimaryExp { $$ = new UnaryExp($1); }
  | IDENT '(' ')' {
        $$ = new UnaryExp(new FuncCall($1->name, $1->line));
        delete $1;
    }
  | IDENT '(' FuncRParams ')' {
        $$ = new UnaryExp(new FuncCall($1->name, $3, $1->line));
        delete $1;
    }
  | '+' UnaryExp %prec UMINUS { $2->pushFront(SY_ADD); $$ = $2; }
  | '-' UnaryExp %prec UMINUS { $2->pushFront(SY_SUB); $$ = $2; }
  | '!' UnaryExp              { $2->pushFront(SY_NOT); $$ = $2; }
  ;

FuncRParams:
    Exp {
        $$ = new FuncRParamList($1);
    }
  | FuncRParams ',' Exp {
        $1->pushBack($3);
        $$ = $1;
    }
  ;

ArrayList:
    '[' Exp ']' {
        $$ = new ArrayList($2);
    }
  | ArrayList '[' Exp ']' {
        $1->pushBack($3);
        $$ = $1;
    }
  ;

ArrayDims:
    /* empty */ { $$ = nullptr; }
  | ArrayList   { $$ = $1; }
  ;

InitVal:
    Exp                   { $$ = new InitVal($1); }
  | '{' '}'               { $$ = new InitVal(); }
  | '{' InitValList '}'   { $$ = new InitVal($2); }
  ;

InitValList:
    InitVal { $$ = new InitValList($1); }
  | InitValList ',' InitVal { $1->pushBack($3); $$ = $1; }
  ;

MulExp:
    UnaryExp { $$ = new MulExp($1); }
  | MulExp '*' UnaryExp { $1->pushBack(SY_MUL); $1->pushBack($3); $$ = $1; }
  | MulExp '/' UnaryExp { $1->pushBack(SY_DIV); $1->pushBack($3); $$ = $1; }
  | MulExp '%' UnaryExp { $1->pushBack(SY_MOD); $1->pushBack($3); $$ = $1; }
  ;

AddExp:
    MulExp { $$ = new AddExp($1); }
  | AddExp '+' MulExp { $1->pushBack(SY_ADD); $1->pushBack($3); $$ = $1; }
  | AddExp '-' MulExp { $1->pushBack(SY_SUB); $1->pushBack($3); $$ = $1; }
  ;

RelExp:
    AddExp { $$ = new RelExp($1); }
  | RelExp '<' AddExp  { $1->pushBack(SY_LESS);    $1->pushBack($3); $$ = $1; }
  | RelExp '>' AddExp  { $1->pushBack(SY_GREAT);   $1->pushBack($3); $$ = $1; }
  | RelExp LE  AddExp  { $1->pushBack(SY_LESSEQ);  $1->pushBack($3); $$ = $1; }
  | RelExp GE  AddExp  { $1->pushBack(SY_GREATEQ); $1->pushBack($3); $$ = $1; }
  ;

EqExp:
    RelExp { $$ = new EqExp($1); }
  | EqExp EQ RelExp { $1->pushBack(SY_EQ);    $1->pushBack($3); $$ = $1; }
  | EqExp NE RelExp { $1->pushBack(SY_NOTEQ); $1->pushBack($3); $$ = $1; }
  ;

LAndExp:
    EqExp { $$ = new LAndExp($1); }
  | LAndExp AND EqExp { $1->pushBack(SY_AND); $1->pushBack($3); $$ = $1; }
  ;

LOrExp:
    LAndExp { $$ = new LOrExp($1); }
  | LOrExp OR LAndExp { $1->pushBack(SY_OR); $1->pushBack($3); $$ = $1; }
  ;

%%

void yy::parser::error(const std::string& msg) {
    std::cerr << "Parser Error: " << msg << std::endl;
}
