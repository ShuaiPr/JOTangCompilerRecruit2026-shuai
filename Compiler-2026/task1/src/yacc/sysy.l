%{
#include "lib/AST.hpp"
#include "yacc/Bison.hpp"

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

extern int yylineno;

// Bison 的 C++ 解析器逐 Token 传入语义值；Flex 生成的是 C 风格
// int yylex(void)，这里用全局指针桥接，词法动作写法保持不变。
static yy::parser::semantic_type *g_yylval = nullptr;
#define yylval (*g_yylval)

// 数值转换：报告异常与越界。
static int parse_int(const char *text, int base);
static float parse_float(const char *text);
%}

%option noyywrap
%option yylineno

/* 注释 */
LINE_COMMENT  "//"[^\n]*
BLOCK_COMMENT "/*"([^*]|\*+[^*/])*\*+"/"

/* 整数：十进制、八进制、十六进制 */
DEC_INT   [1-9][0-9]*|0
OCT_INT   0[0-7]+
HEX_INT   0[xX][0-9a-fA-F]+

/* 浮点：十进制与十六进制 */
DEC_FLOAT ([0-9]+\.[0-9]*|\.[0-9]+)([eE][+-]?[0-9]+)?|[0-9]+[eE][+-]?[0-9]+
HEX_FLOAT 0[xX]([0-9a-fA-F]+\.[0-9a-fA-F]*|\.[0-9a-fA-F]+)([pP][+-]?[0-9]+)?|0[xX][0-9a-fA-F]+[pP][+-]?[0-9]+

IDENT   [_a-zA-Z][_a-zA-Z0-9]*

%%

{LINE_COMMENT}  ;
{BLOCK_COMMENT} ;
[ \t\r\n]+      ;

"const"     { return yy::parser::token::CONST; }
"int"       { return yy::parser::token::INT; }
"float"     { return yy::parser::token::FLOAT; }
"void"      { return yy::parser::token::VOID; }
"if"        { return yy::parser::token::IF; }
"else"      { return yy::parser::token::ELSE; }
"while"     { return yy::parser::token::WHILE; }
"break"     { return yy::parser::token::BREAK; }
"continue"  { return yy::parser::token::CONTINUE; }
"return"    { return yy::parser::token::RETURN; }

"<="    { return yy::parser::token::LE; }
">="    { return yy::parser::token::GE; }
"=="    { return yy::parser::token::EQ; }
"!="    { return yy::parser::token::NE; }
"&&"    { return yy::parser::token::AND; }
"||"    { return yy::parser::token::OR; }

{HEX_INT}       { yylval.int_val = parse_int(yytext, 16); return yy::parser::token::INT_CONST; }
{OCT_INT}       { yylval.int_val = parse_int(yytext, 8);  return yy::parser::token::INT_CONST; }
{DEC_INT}       { yylval.int_val = parse_int(yytext, 10); return yy::parser::token::INT_CONST; }
0[0-9]+         {
                    std::fprintf(stderr, "Lexical Error at Line %d: 非法八进制整数 %s\n", yylineno, yytext);
                    return yy::parser::token::LEX_ERROR;
                }

{HEX_FLOAT}     { yylval.float_val = parse_float(yytext); return yy::parser::token::FLOAT_CONST; }
{DEC_FLOAT}     { yylval.float_val = parse_float(yytext); return yy::parser::token::FLOAT_CONST; }

{IDENT}         { yylval.ident_val = new IdentInfo{std::string(yytext), yylineno}; return yy::parser::token::IDENT; }

"+"             { return '+'; }
"-"             { return '-'; }
"*"             { return '*'; }
"/"             { return '/'; }
"%"             { return '%'; }
"<"             { return '<'; }
">"             { return '>'; }
"!"             { return '!'; }
"="             { return '='; }
";"             { return ';'; }
","             { return ','; }
"("             { return '('; }
")"             { return ')'; }
"["             { return '['; }
"]"             { return ']'; }
"{"             { return '{'; }
"}"             { return '}'; }

"/*"            {
                    std::fprintf(stderr, "Lexical Error at Line %d: 多行注释未闭合\n", yylineno);
                    return yy::parser::token::LEX_ERROR;
                }

.               {
                    std::fprintf(stderr, "Lexical Error at Line %d: 未知字符 %s\n", yylineno, yytext);
                    return yy::parser::token::LEX_ERROR;
                }

%%

// Bison C++ 解析器调用此重载；它驱动 Flex 生成的 C 风格 yylex()。
int yylex(yy::parser::semantic_type *sem) {
    g_yylval = sem;
    return yylex();
}

static int parse_int(const char *text, int base) {
    errno = 0;
    char *end = nullptr;
    long value = std::strtol(text, &end, base);
    if (errno == ERANGE || value > 2147483647L || value < -2147483648L) {
        std::fprintf(stderr, "Lexical Error at Line %d: 整数字面量越界 %s\n", yylineno, text);
    }
    return static_cast<int>(value);
}

static float parse_float(const char *text) {
    errno = 0;
    float value = std::strtof(text, nullptr);
    if (errno == ERANGE) {
        std::fprintf(stderr, "Lexical Error at Line %d: 浮点字面量越界 %s\n", yylineno, text);
    }
    return value;
}
