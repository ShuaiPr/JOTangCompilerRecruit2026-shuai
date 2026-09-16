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
