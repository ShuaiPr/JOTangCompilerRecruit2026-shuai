# QA

## 1. 什么是 Flex/Bison？二者分别对应前端的什么流程？

**<span style="color:#d73a49">Flex</span>**：词法分析器生成器；`yylex()` 按**最长匹配**把字符流切成 **Token** 流 —— **词法分析**。

**<span style="color:#d73a49">Bison</span>**：语法分析器生成器；以**移进-归约**分析 Token 流 —— **语法分析**（本任务同时构造 AST）。

## 2. 什么是正则表达式？终结符？非终结符？

- **<span style="color:#d73a49">正则表达式</span>**：描述 Token 的字符模式，等价于**有限自动机**。
- **<span style="color:#d73a49">终结符</span>**：不可再分的 Token，语法树的叶子。
- **<span style="color:#d73a49">非终结符</span>**：需继续展开的语法范畴（如 `Exp`、`Stmt`），语法树的内部节点。

## 3. 什么是文法？

**<span style="color:#d73a49">文法</span>**：`G = (V_N, V_T, P, S)`，用产生式 `A → α` 递归定义合法句子集合。

**<span style="color:#d73a49">上下文无关文法</span>**：产生式左部为单个非终结符，Bison 即处理此类。

## 4. 请你简述 Bison 与 Flex 协作生成 AST 的过程

1. Flex `yylex()` 取词，返回 **Token**（附 `yylval`、行号）。
2. Bison **移进** Token，匹配产生式后**归约**。
3. 归约动作 `new` 节点，`$$` 上交父节点；括号/逗号/分号不建节点。
4. 归约至 `CompUnit` → 交 **`ASTRoot`** → `ASTPrinter` 输出。

## 5. 可复现的构建命令

```bash
cd Compiler-2026/task1

# 构建
mkdir -p include/yacc src/yacc
bison --defines=include/yacc/Bison.hpp --output=src/yacc/Bison.cpp src/yacc/sysy.y
flex  --header-file=include/yacc/Flex.hpp --outfile=src/yacc/Flex.cpp src/yacc/sysy.l
cmake -S . -B build && cmake --build build -j

# 验收
python3 test_frontend.py --examples
python3 test_frontend.py

# 再清零（保留生成物则只留 rm -rf build）
rm -rf build
rm -f src/yacc/Bison.cpp src/yacc/Flex.cpp src/yacc/stack.hh
rm -f include/yacc/Bison.hpp include/yacc/Flex.hpp
```

## 6. 解析及适配流程

```text
.sy 源文件
  └─ Flex 生成的 yylex()：DFA 最长匹配切词 → Token + yylval/yylineno
       └─ Bison LALR(1) 移进-归约
            └─ 每条产生式归约时执行语义动作 new 出 AST 节点（$$ 上交父节点）
                 └─ 归约到开始符号 CompUnit → 移交全局 ASTRoot(std::unique_ptr<CompUnit>)
                      └─ ASTPrinter(Visitor) → 单行 S-expression + 恰好一个 LF
```

## 7. 适配要点

`main.cpp`、`CMakeLists.txt` 与输出协议固定，适配全部落在 `sysy.l` / `sysy.y` 内：

 **解析器**：`main.cpp` 固定使用 `yy::parser`，故 `.y` 需声明 `%language "C++"`、`api.namespace {yy}`、`api.parser.class {parser}`。
