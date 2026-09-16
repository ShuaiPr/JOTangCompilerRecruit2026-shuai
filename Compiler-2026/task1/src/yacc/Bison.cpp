// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.



// First part of user prologue.
#line 1 "src/yacc/sysy.y"

#include "Frontend.hpp"
#include "lib/AST.hpp"

#include <iostream>
#include <string>

#line 49 "src/yacc/Bison.cpp"


#include "Bison.hpp"


// Unqualified %code blocks.
#line 26 "src/yacc/sysy.y"

// 由 Flex 生成的扫描器提供桥接函数：返回下一个 Token 并写入语义值。
int yylex(yy::parser::semantic_type *sem);

#line 61 "src/yacc/Bison.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 10 "src/yacc/sysy.y"
namespace yy {
#line 135 "src/yacc/Bison.cpp"

  /// Build a parser object.
  parser::parser ()
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr)
#else

#endif
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (value_type) v)
    : Base (t)
    , value (YY_MOVE (v))
  {}


  template <typename Base>
  parser::symbol_kind_type
  parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
  }

  // by_kind.
  parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
  parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  parser::symbol_kind_type
  parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  parser::symbol_kind_type
  parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YY_USE (yysym.kind ());
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;


      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // CompUnit: Decl
#line 116 "src/yacc/sysy.y"
         {
        (yylhs.value.comp_unit) = new CompUnit((yystack_[0].value.base_node));
        ASTRoot.reset((yylhs.value.comp_unit));
    }
#line 594 "src/yacc/Bison.cpp"
    break;

  case 3: // CompUnit: FuncDef
#line 120 "src/yacc/sysy.y"
            {
        (yylhs.value.comp_unit) = new CompUnit((yystack_[0].value.func_def));
        ASTRoot.reset((yylhs.value.comp_unit));
    }
#line 603 "src/yacc/Bison.cpp"
    break;

  case 4: // CompUnit: CompUnit Decl
#line 124 "src/yacc/sysy.y"
                  {
        (yystack_[1].value.comp_unit)->pushBack((yystack_[0].value.base_node));
        (yylhs.value.comp_unit) = (yystack_[1].value.comp_unit);
    }
#line 612 "src/yacc/Bison.cpp"
    break;

  case 5: // CompUnit: CompUnit FuncDef
#line 128 "src/yacc/sysy.y"
                     {
        (yystack_[1].value.comp_unit)->pushBack((yystack_[0].value.func_def));
        (yylhs.value.comp_unit) = (yystack_[1].value.comp_unit);
    }
#line 621 "src/yacc/Bison.cpp"
    break;

  case 6: // Decl: ConstDecl
#line 135 "src/yacc/sysy.y"
              { (yylhs.value.base_node) = (yystack_[0].value.const_decl); }
#line 627 "src/yacc/Bison.cpp"
    break;

  case 7: // Decl: VarDecl
#line 136 "src/yacc/sysy.y"
              { (yylhs.value.base_node) = (yystack_[0].value.var_decl); }
#line 633 "src/yacc/Bison.cpp"
    break;

  case 8: // ConstDecl: CONST INT ConstDefList ';'
#line 140 "src/yacc/sysy.y"
                               {
        (yylhs.value.const_decl) = new ConstDecl(SY_INT, (yystack_[1].value.const_def_list));
    }
#line 641 "src/yacc/Bison.cpp"
    break;

  case 9: // ConstDecl: CONST FLOAT ConstDefList ';'
#line 143 "src/yacc/sysy.y"
                                 {
        (yylhs.value.const_decl) = new ConstDecl(SY_FLOAT, (yystack_[1].value.const_def_list));
    }
#line 649 "src/yacc/Bison.cpp"
    break;

  case 10: // VarDecl: INT VarDefList ';'
#line 149 "src/yacc/sysy.y"
                       {
        (yylhs.value.var_decl) = new VarDecl(SY_INT, (yystack_[1].value.var_def_list));
    }
#line 657 "src/yacc/Bison.cpp"
    break;

  case 11: // VarDecl: FLOAT VarDefList ';'
#line 152 "src/yacc/sysy.y"
                         {
        (yylhs.value.var_decl) = new VarDecl(SY_FLOAT, (yystack_[1].value.var_def_list));
    }
#line 665 "src/yacc/Bison.cpp"
    break;

  case 12: // ConstDefList: ConstDef
#line 158 "src/yacc/sysy.y"
             {
        (yylhs.value.const_def_list) = new ConstDefList((yystack_[0].value.const_def));
    }
#line 673 "src/yacc/Bison.cpp"
    break;

  case 13: // ConstDefList: ConstDefList ',' ConstDef
#line 161 "src/yacc/sysy.y"
                              {
        (yystack_[2].value.const_def_list)->pushBack((yystack_[0].value.const_def));
        (yylhs.value.const_def_list) = (yystack_[2].value.const_def_list);
    }
#line 682 "src/yacc/Bison.cpp"
    break;

  case 14: // VarDefList: VarDef
#line 168 "src/yacc/sysy.y"
           {
        (yylhs.value.var_def_list) = new VarDefList((yystack_[0].value.var_def));
    }
#line 690 "src/yacc/Bison.cpp"
    break;

  case 15: // VarDefList: VarDefList ',' VarDef
#line 171 "src/yacc/sysy.y"
                          {
        (yystack_[2].value.var_def_list)->pushBack((yystack_[0].value.var_def));
        (yylhs.value.var_def_list) = (yystack_[2].value.var_def_list);
    }
#line 699 "src/yacc/Bison.cpp"
    break;

  case 16: // ConstDef: IDENT ArrayDims '=' InitVal
#line 178 "src/yacc/sysy.y"
                                {
        (yylhs.value.const_def) = new ConstDef((yystack_[3].value.ident_val)->name, (yystack_[2].value.array_list), (yystack_[0].value.init_val));
        delete (yystack_[3].value.ident_val);
    }
#line 708 "src/yacc/Bison.cpp"
    break;

  case 17: // VarDef: IDENT ArrayDims
#line 185 "src/yacc/sysy.y"
                    {
        (yylhs.value.var_def) = new VarDef((yystack_[1].value.ident_val)->name, (yystack_[0].value.array_list), nullptr);
        delete (yystack_[1].value.ident_val);
    }
#line 717 "src/yacc/Bison.cpp"
    break;

  case 18: // VarDef: IDENT ArrayDims '=' InitVal
#line 189 "src/yacc/sysy.y"
                                {
        (yylhs.value.var_def) = new VarDef((yystack_[3].value.ident_val)->name, (yystack_[2].value.array_list), (yystack_[0].value.init_val));
        delete (yystack_[3].value.ident_val);
    }
#line 726 "src/yacc/Bison.cpp"
    break;

  case 19: // FuncDef: INT IDENT '(' ')' Block
#line 196 "src/yacc/sysy.y"
                            {
        (yylhs.value.func_def) = new FuncDef(SY_INT, (yystack_[3].value.ident_val)->name, nullptr, (yystack_[0].value.block));
        delete (yystack_[3].value.ident_val);
    }
#line 735 "src/yacc/Bison.cpp"
    break;

  case 20: // FuncDef: FLOAT IDENT '(' ')' Block
#line 200 "src/yacc/sysy.y"
                              {
        (yylhs.value.func_def) = new FuncDef(SY_FLOAT, (yystack_[3].value.ident_val)->name, nullptr, (yystack_[0].value.block));
        delete (yystack_[3].value.ident_val);
    }
#line 744 "src/yacc/Bison.cpp"
    break;

  case 21: // FuncDef: VOID IDENT '(' ')' Block
#line 204 "src/yacc/sysy.y"
                             {
        (yylhs.value.func_def) = new FuncDef(SY_VOID, (yystack_[3].value.ident_val)->name, nullptr, (yystack_[0].value.block));
        delete (yystack_[3].value.ident_val);
    }
#line 753 "src/yacc/Bison.cpp"
    break;

  case 22: // FuncDef: INT IDENT '(' FuncParamList ')' Block
#line 208 "src/yacc/sysy.y"
                                          {
        (yylhs.value.func_def) = new FuncDef(SY_INT, (yystack_[4].value.ident_val)->name, (yystack_[2].value.func_param_list), (yystack_[0].value.block));
        delete (yystack_[4].value.ident_val);
    }
#line 762 "src/yacc/Bison.cpp"
    break;

  case 23: // FuncDef: FLOAT IDENT '(' FuncParamList ')' Block
#line 212 "src/yacc/sysy.y"
                                            {
        (yylhs.value.func_def) = new FuncDef(SY_FLOAT, (yystack_[4].value.ident_val)->name, (yystack_[2].value.func_param_list), (yystack_[0].value.block));
        delete (yystack_[4].value.ident_val);
    }
#line 771 "src/yacc/Bison.cpp"
    break;

  case 24: // FuncDef: VOID IDENT '(' FuncParamList ')' Block
#line 216 "src/yacc/sysy.y"
                                           {
        (yylhs.value.func_def) = new FuncDef(SY_VOID, (yystack_[4].value.ident_val)->name, (yystack_[2].value.func_param_list), (yystack_[0].value.block));
        delete (yystack_[4].value.ident_val);
    }
#line 780 "src/yacc/Bison.cpp"
    break;

  case 25: // FuncParamList: FuncParam
#line 223 "src/yacc/sysy.y"
              {
        (yylhs.value.func_param_list) = new FuncParamList((yystack_[0].value.func_param));
    }
#line 788 "src/yacc/Bison.cpp"
    break;

  case 26: // FuncParamList: FuncParamList ',' FuncParam
#line 226 "src/yacc/sysy.y"
                                {
        (yystack_[2].value.func_param_list)->pushBack((yystack_[0].value.func_param));
        (yylhs.value.func_param_list) = (yystack_[2].value.func_param_list);
    }
#line 797 "src/yacc/Bison.cpp"
    break;

  case 27: // FuncParam: INT IDENT
#line 233 "src/yacc/sysy.y"
              {
        (yylhs.value.func_param) = new FuncParam(SY_INT, (yystack_[0].value.ident_val)->name);
        delete (yystack_[0].value.ident_val);
    }
#line 806 "src/yacc/Bison.cpp"
    break;

  case 28: // FuncParam: FLOAT IDENT
#line 237 "src/yacc/sysy.y"
                {
        (yylhs.value.func_param) = new FuncParam(SY_FLOAT, (yystack_[0].value.ident_val)->name);
        delete (yystack_[0].value.ident_val);
    }
#line 815 "src/yacc/Bison.cpp"
    break;

  case 29: // FuncParam: INT IDENT '[' ']' ArrayDims
#line 241 "src/yacc/sysy.y"
                                {
        (yylhs.value.func_param) = new FuncParam(SY_INT, (yystack_[3].value.ident_val)->name, true, (yystack_[0].value.array_list));
        delete (yystack_[3].value.ident_val);
    }
#line 824 "src/yacc/Bison.cpp"
    break;

  case 30: // FuncParam: FLOAT IDENT '[' ']' ArrayDims
#line 245 "src/yacc/sysy.y"
                                  {
        (yylhs.value.func_param) = new FuncParam(SY_FLOAT, (yystack_[3].value.ident_val)->name, true, (yystack_[0].value.array_list));
        delete (yystack_[3].value.ident_val);
    }
#line 833 "src/yacc/Bison.cpp"
    break;

  case 31: // Block: '{' '}'
#line 252 "src/yacc/sysy.y"
            {
        (yylhs.value.block) = new Block(nullptr);
    }
#line 841 "src/yacc/Bison.cpp"
    break;

  case 32: // Block: '{' BlockItemList '}'
#line 255 "src/yacc/sysy.y"
                          {
        (yylhs.value.block) = new Block((yystack_[1].value.block_item_list));
    }
#line 849 "src/yacc/Bison.cpp"
    break;

  case 33: // BlockItemList: BlockItem
#line 261 "src/yacc/sysy.y"
              {
        (yylhs.value.block_item_list) = new BlockItemList((yystack_[0].value.base_node));
    }
#line 857 "src/yacc/Bison.cpp"
    break;

  case 34: // BlockItemList: BlockItemList BlockItem
#line 264 "src/yacc/sysy.y"
                            {
        (yystack_[1].value.block_item_list)->pushBack((yystack_[0].value.base_node));
        (yylhs.value.block_item_list) = (yystack_[1].value.block_item_list);
    }
#line 866 "src/yacc/Bison.cpp"
    break;

  case 35: // BlockItem: Decl
#line 271 "src/yacc/sysy.y"
         { (yylhs.value.base_node) = (yystack_[0].value.base_node); }
#line 872 "src/yacc/Bison.cpp"
    break;

  case 36: // BlockItem: Stmt
#line 272 "src/yacc/sysy.y"
         { (yylhs.value.base_node) = (yystack_[0].value.base_node); }
#line 878 "src/yacc/Bison.cpp"
    break;

  case 37: // Stmt: LVal '=' Exp ';'
#line 276 "src/yacc/sysy.y"
                     {
        (yylhs.value.base_node) = new AssignStmt((yystack_[3].value.lval), (yystack_[1].value.add_exp));
    }
#line 886 "src/yacc/Bison.cpp"
    break;

  case 38: // Stmt: Exp ';'
#line 279 "src/yacc/sysy.y"
            {
        (yylhs.value.base_node) = new ExpStmt((yystack_[1].value.add_exp));
    }
#line 894 "src/yacc/Bison.cpp"
    break;

  case 39: // Stmt: ';'
#line 282 "src/yacc/sysy.y"
        {
        (yylhs.value.base_node) = new ExpStmt(nullptr);
    }
#line 902 "src/yacc/Bison.cpp"
    break;

  case 40: // Stmt: Block
#line 285 "src/yacc/sysy.y"
          {
        (yylhs.value.base_node) = (yystack_[0].value.block);
    }
#line 910 "src/yacc/Bison.cpp"
    break;

  case 41: // Stmt: IF '(' Cond ')' Stmt
#line 288 "src/yacc/sysy.y"
                                               {
        (yylhs.value.base_node) = new IfStmt((yystack_[2].value.lor_exp), (yystack_[0].value.base_node));
    }
#line 918 "src/yacc/Bison.cpp"
    break;

  case 42: // Stmt: IF '(' Cond ')' Stmt ELSE Stmt
#line 291 "src/yacc/sysy.y"
                                   {
        (yylhs.value.base_node) = new IfStmt((yystack_[4].value.lor_exp), (yystack_[2].value.base_node), (yystack_[0].value.base_node));
    }
#line 926 "src/yacc/Bison.cpp"
    break;

  case 43: // Stmt: WHILE '(' Cond ')' Stmt
#line 294 "src/yacc/sysy.y"
                            {
        (yylhs.value.base_node) = new WhileStmt((yystack_[2].value.lor_exp), (yystack_[0].value.base_node));
    }
#line 934 "src/yacc/Bison.cpp"
    break;

  case 44: // Stmt: BREAK ';'
#line 297 "src/yacc/sysy.y"
              {
        (yylhs.value.base_node) = new BreakStmt();
    }
#line 942 "src/yacc/Bison.cpp"
    break;

  case 45: // Stmt: CONTINUE ';'
#line 300 "src/yacc/sysy.y"
                 {
        (yylhs.value.base_node) = new ContinueStmt();
    }
#line 950 "src/yacc/Bison.cpp"
    break;

  case 46: // Stmt: RETURN Exp ';'
#line 303 "src/yacc/sysy.y"
                   {
        (yylhs.value.base_node) = new ReturnStmt((yystack_[1].value.add_exp));
    }
#line 958 "src/yacc/Bison.cpp"
    break;

  case 47: // Stmt: RETURN ';'
#line 306 "src/yacc/sysy.y"
               {
        (yylhs.value.base_node) = new ReturnStmt();
    }
#line 966 "src/yacc/Bison.cpp"
    break;

  case 48: // Exp: AddExp
#line 312 "src/yacc/sysy.y"
           { (yylhs.value.add_exp) = (yystack_[0].value.add_exp); }
#line 972 "src/yacc/Bison.cpp"
    break;

  case 49: // Cond: LOrExp
#line 316 "src/yacc/sysy.y"
           { (yylhs.value.lor_exp) = (yystack_[0].value.lor_exp); }
#line 978 "src/yacc/Bison.cpp"
    break;

  case 50: // LVal: IDENT ArrayDims
#line 320 "src/yacc/sysy.y"
                    {
        (yylhs.value.lval) = new LVal((yystack_[1].value.ident_val)->name, (yystack_[0].value.array_list));
        delete (yystack_[1].value.ident_val);
    }
#line 987 "src/yacc/Bison.cpp"
    break;

  case 51: // PrimaryExp: '(' Exp ')'
#line 327 "src/yacc/sysy.y"
                { (yylhs.value.base_node) = (yystack_[1].value.add_exp); }
#line 993 "src/yacc/Bison.cpp"
    break;

  case 52: // PrimaryExp: LVal
#line 328 "src/yacc/sysy.y"
                { (yylhs.value.base_node) = (yystack_[0].value.lval); }
#line 999 "src/yacc/Bison.cpp"
    break;

  case 53: // PrimaryExp: Number
#line 329 "src/yacc/sysy.y"
                { (yylhs.value.base_node) = (yystack_[0].value.base_node); }
#line 1005 "src/yacc/Bison.cpp"
    break;

  case 54: // Number: INT_CONST
#line 333 "src/yacc/sysy.y"
                { (yylhs.value.base_node) = new ConValue<int>((yystack_[0].value.int_val)); }
#line 1011 "src/yacc/Bison.cpp"
    break;

  case 55: // Number: FLOAT_CONST
#line 334 "src/yacc/sysy.y"
                { (yylhs.value.base_node) = new ConValue<float>((yystack_[0].value.float_val)); }
#line 1017 "src/yacc/Bison.cpp"
    break;

  case 56: // UnaryExp: PrimaryExp
#line 338 "src/yacc/sysy.y"
               { (yylhs.value.unary_exp) = new UnaryExp((yystack_[0].value.base_node)); }
#line 1023 "src/yacc/Bison.cpp"
    break;

  case 57: // UnaryExp: IDENT '(' ')'
#line 339 "src/yacc/sysy.y"
                  {
        (yylhs.value.unary_exp) = new UnaryExp(new FuncCall((yystack_[2].value.ident_val)->name, (yystack_[2].value.ident_val)->line));
        delete (yystack_[2].value.ident_val);
    }
#line 1032 "src/yacc/Bison.cpp"
    break;

  case 58: // UnaryExp: IDENT '(' FuncRParams ')'
#line 343 "src/yacc/sysy.y"
                              {
        (yylhs.value.unary_exp) = new UnaryExp(new FuncCall((yystack_[3].value.ident_val)->name, (yystack_[1].value.func_r_param_list), (yystack_[3].value.ident_val)->line));
        delete (yystack_[3].value.ident_val);
    }
#line 1041 "src/yacc/Bison.cpp"
    break;

  case 59: // UnaryExp: '+' UnaryExp
#line 347 "src/yacc/sysy.y"
                              { (yystack_[0].value.unary_exp)->pushFront(SY_ADD); (yylhs.value.unary_exp) = (yystack_[0].value.unary_exp); }
#line 1047 "src/yacc/Bison.cpp"
    break;

  case 60: // UnaryExp: '-' UnaryExp
#line 348 "src/yacc/sysy.y"
                              { (yystack_[0].value.unary_exp)->pushFront(SY_SUB); (yylhs.value.unary_exp) = (yystack_[0].value.unary_exp); }
#line 1053 "src/yacc/Bison.cpp"
    break;

  case 61: // UnaryExp: '!' UnaryExp
#line 349 "src/yacc/sysy.y"
                              { (yystack_[0].value.unary_exp)->pushFront(SY_NOT); (yylhs.value.unary_exp) = (yystack_[0].value.unary_exp); }
#line 1059 "src/yacc/Bison.cpp"
    break;

  case 62: // FuncRParams: Exp
#line 353 "src/yacc/sysy.y"
        {
        (yylhs.value.func_r_param_list) = new FuncRParamList((yystack_[0].value.add_exp));
    }
#line 1067 "src/yacc/Bison.cpp"
    break;

  case 63: // FuncRParams: FuncRParams ',' Exp
#line 356 "src/yacc/sysy.y"
                        {
        (yystack_[2].value.func_r_param_list)->pushBack((yystack_[0].value.add_exp));
        (yylhs.value.func_r_param_list) = (yystack_[2].value.func_r_param_list);
    }
#line 1076 "src/yacc/Bison.cpp"
    break;

  case 64: // ArrayList: '[' Exp ']'
#line 363 "src/yacc/sysy.y"
                {
        (yylhs.value.array_list) = new ArrayList((yystack_[1].value.add_exp));
    }
#line 1084 "src/yacc/Bison.cpp"
    break;

  case 65: // ArrayList: ArrayList '[' Exp ']'
#line 366 "src/yacc/sysy.y"
                          {
        (yystack_[3].value.array_list)->pushBack((yystack_[1].value.add_exp));
        (yylhs.value.array_list) = (yystack_[3].value.array_list);
    }
#line 1093 "src/yacc/Bison.cpp"
    break;

  case 66: // ArrayDims: %empty
#line 373 "src/yacc/sysy.y"
                { (yylhs.value.array_list) = nullptr; }
#line 1099 "src/yacc/Bison.cpp"
    break;

  case 67: // ArrayDims: ArrayList
#line 374 "src/yacc/sysy.y"
                { (yylhs.value.array_list) = (yystack_[0].value.array_list); }
#line 1105 "src/yacc/Bison.cpp"
    break;

  case 68: // InitVal: Exp
#line 378 "src/yacc/sysy.y"
                          { (yylhs.value.init_val) = new InitVal((yystack_[0].value.add_exp)); }
#line 1111 "src/yacc/Bison.cpp"
    break;

  case 69: // InitVal: '{' '}'
#line 379 "src/yacc/sysy.y"
                          { (yylhs.value.init_val) = new InitVal(); }
#line 1117 "src/yacc/Bison.cpp"
    break;

  case 70: // InitVal: '{' InitValList '}'
#line 380 "src/yacc/sysy.y"
                          { (yylhs.value.init_val) = new InitVal((yystack_[1].value.init_val_list)); }
#line 1123 "src/yacc/Bison.cpp"
    break;

  case 71: // InitValList: InitVal
#line 384 "src/yacc/sysy.y"
            { (yylhs.value.init_val_list) = new InitValList((yystack_[0].value.init_val)); }
#line 1129 "src/yacc/Bison.cpp"
    break;

  case 72: // InitValList: InitValList ',' InitVal
#line 385 "src/yacc/sysy.y"
                            { (yystack_[2].value.init_val_list)->pushBack((yystack_[0].value.init_val)); (yylhs.value.init_val_list) = (yystack_[2].value.init_val_list); }
#line 1135 "src/yacc/Bison.cpp"
    break;

  case 73: // MulExp: UnaryExp
#line 389 "src/yacc/sysy.y"
             { (yylhs.value.mul_exp) = new MulExp((yystack_[0].value.unary_exp)); }
#line 1141 "src/yacc/Bison.cpp"
    break;

  case 74: // MulExp: MulExp '*' UnaryExp
#line 390 "src/yacc/sysy.y"
                        { (yystack_[2].value.mul_exp)->pushBack(SY_MUL); (yystack_[2].value.mul_exp)->pushBack((yystack_[0].value.unary_exp)); (yylhs.value.mul_exp) = (yystack_[2].value.mul_exp); }
#line 1147 "src/yacc/Bison.cpp"
    break;

  case 75: // MulExp: MulExp '/' UnaryExp
#line 391 "src/yacc/sysy.y"
                        { (yystack_[2].value.mul_exp)->pushBack(SY_DIV); (yystack_[2].value.mul_exp)->pushBack((yystack_[0].value.unary_exp)); (yylhs.value.mul_exp) = (yystack_[2].value.mul_exp); }
#line 1153 "src/yacc/Bison.cpp"
    break;

  case 76: // MulExp: MulExp '%' UnaryExp
#line 392 "src/yacc/sysy.y"
                        { (yystack_[2].value.mul_exp)->pushBack(SY_MOD); (yystack_[2].value.mul_exp)->pushBack((yystack_[0].value.unary_exp)); (yylhs.value.mul_exp) = (yystack_[2].value.mul_exp); }
#line 1159 "src/yacc/Bison.cpp"
    break;

  case 77: // AddExp: MulExp
#line 396 "src/yacc/sysy.y"
           { (yylhs.value.add_exp) = new AddExp((yystack_[0].value.mul_exp)); }
#line 1165 "src/yacc/Bison.cpp"
    break;

  case 78: // AddExp: AddExp '+' MulExp
#line 397 "src/yacc/sysy.y"
                      { (yystack_[2].value.add_exp)->pushBack(SY_ADD); (yystack_[2].value.add_exp)->pushBack((yystack_[0].value.mul_exp)); (yylhs.value.add_exp) = (yystack_[2].value.add_exp); }
#line 1171 "src/yacc/Bison.cpp"
    break;

  case 79: // AddExp: AddExp '-' MulExp
#line 398 "src/yacc/sysy.y"
                      { (yystack_[2].value.add_exp)->pushBack(SY_SUB); (yystack_[2].value.add_exp)->pushBack((yystack_[0].value.mul_exp)); (yylhs.value.add_exp) = (yystack_[2].value.add_exp); }
#line 1177 "src/yacc/Bison.cpp"
    break;

  case 80: // RelExp: AddExp
#line 402 "src/yacc/sysy.y"
           { (yylhs.value.rel_exp) = new RelExp((yystack_[0].value.add_exp)); }
#line 1183 "src/yacc/Bison.cpp"
    break;

  case 81: // RelExp: RelExp '<' AddExp
#line 403 "src/yacc/sysy.y"
                       { (yystack_[2].value.rel_exp)->pushBack(SY_LESS);    (yystack_[2].value.rel_exp)->pushBack((yystack_[0].value.add_exp)); (yylhs.value.rel_exp) = (yystack_[2].value.rel_exp); }
#line 1189 "src/yacc/Bison.cpp"
    break;

  case 82: // RelExp: RelExp '>' AddExp
#line 404 "src/yacc/sysy.y"
                       { (yystack_[2].value.rel_exp)->pushBack(SY_GREAT);   (yystack_[2].value.rel_exp)->pushBack((yystack_[0].value.add_exp)); (yylhs.value.rel_exp) = (yystack_[2].value.rel_exp); }
#line 1195 "src/yacc/Bison.cpp"
    break;

  case 83: // RelExp: RelExp LE AddExp
#line 405 "src/yacc/sysy.y"
                       { (yystack_[2].value.rel_exp)->pushBack(SY_LESSEQ);  (yystack_[2].value.rel_exp)->pushBack((yystack_[0].value.add_exp)); (yylhs.value.rel_exp) = (yystack_[2].value.rel_exp); }
#line 1201 "src/yacc/Bison.cpp"
    break;

  case 84: // RelExp: RelExp GE AddExp
#line 406 "src/yacc/sysy.y"
                       { (yystack_[2].value.rel_exp)->pushBack(SY_GREATEQ); (yystack_[2].value.rel_exp)->pushBack((yystack_[0].value.add_exp)); (yylhs.value.rel_exp) = (yystack_[2].value.rel_exp); }
#line 1207 "src/yacc/Bison.cpp"
    break;

  case 85: // EqExp: RelExp
#line 410 "src/yacc/sysy.y"
           { (yylhs.value.eq_exp) = new EqExp((yystack_[0].value.rel_exp)); }
#line 1213 "src/yacc/Bison.cpp"
    break;

  case 86: // EqExp: EqExp EQ RelExp
#line 411 "src/yacc/sysy.y"
                    { (yystack_[2].value.eq_exp)->pushBack(SY_EQ);    (yystack_[2].value.eq_exp)->pushBack((yystack_[0].value.rel_exp)); (yylhs.value.eq_exp) = (yystack_[2].value.eq_exp); }
#line 1219 "src/yacc/Bison.cpp"
    break;

  case 87: // EqExp: EqExp NE RelExp
#line 412 "src/yacc/sysy.y"
                    { (yystack_[2].value.eq_exp)->pushBack(SY_NOTEQ); (yystack_[2].value.eq_exp)->pushBack((yystack_[0].value.rel_exp)); (yylhs.value.eq_exp) = (yystack_[2].value.eq_exp); }
#line 1225 "src/yacc/Bison.cpp"
    break;

  case 88: // LAndExp: EqExp
#line 416 "src/yacc/sysy.y"
          { (yylhs.value.land_exp) = new LAndExp((yystack_[0].value.eq_exp)); }
#line 1231 "src/yacc/Bison.cpp"
    break;

  case 89: // LAndExp: LAndExp AND EqExp
#line 417 "src/yacc/sysy.y"
                      { (yystack_[2].value.land_exp)->pushBack(SY_AND); (yystack_[2].value.land_exp)->pushBack((yystack_[0].value.eq_exp)); (yylhs.value.land_exp) = (yystack_[2].value.land_exp); }
#line 1237 "src/yacc/Bison.cpp"
    break;

  case 90: // LOrExp: LAndExp
#line 421 "src/yacc/sysy.y"
            { (yylhs.value.lor_exp) = new LOrExp((yystack_[0].value.land_exp)); }
#line 1243 "src/yacc/Bison.cpp"
    break;

  case 91: // LOrExp: LOrExp OR LAndExp
#line 422 "src/yacc/sysy.y"
                      { (yystack_[2].value.lor_exp)->pushBack(SY_OR); (yystack_[2].value.lor_exp)->pushBack((yystack_[0].value.land_exp)); (yylhs.value.lor_exp) = (yystack_[2].value.lor_exp); }
#line 1249 "src/yacc/Bison.cpp"
    break;


#line 1253 "src/yacc/Bison.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short parser::yypact_ninf_ = -152;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
      98,    27,     3,    19,    50,     4,  -152,  -152,  -152,  -152,
      63,    63,    37,   110,  -152,    54,   116,    23,  -152,  -152,
    -152,   -21,   124,  -152,   132,    12,   225,    39,    45,  -152,
      67,    29,  -152,    74,    51,  -152,    63,  -152,   108,   111,
      53,   -16,  -152,  -152,  -152,    88,   225,   225,   225,   225,
      69,  -152,  -152,  -152,  -152,   103,   144,   225,   164,   -21,
    -152,    53,    -4,    53,    20,   164,  -152,    96,   101,    38,
    -152,   165,    53,   189,  -152,  -152,  -152,  -152,   123,  -152,
     225,   225,   225,   225,   225,   106,    58,  -152,  -152,  -152,
      53,  -152,    53,  -152,   135,   140,    67,    67,   145,   152,
     114,   163,   214,  -152,  -152,  -152,  -152,   115,  -152,  -152,
     166,   167,  -152,  -152,  -152,  -152,    33,  -152,  -152,  -152,
    -152,   103,   103,  -152,  -152,  -152,   -19,  -152,  -152,   -21,
     -21,   225,   225,  -152,  -152,  -152,   170,  -152,  -152,  -152,
     225,   225,  -152,   164,  -152,  -152,  -152,   176,   144,    71,
     168,   181,   193,   184,  -152,   190,  -152,  -152,   149,   225,
     225,   225,   225,   225,   225,   225,   225,   149,  -152,   211,
     144,   144,   144,   144,    71,    71,   168,   181,  -152,   149,
    -152
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     2,     6,     7,     3,
       0,     0,    66,     0,    14,    66,     0,     0,     1,     4,
       5,    66,     0,    12,     0,     0,     0,    67,    17,    10,
       0,     0,    11,     0,     0,     8,     0,     9,     0,     0,
       0,     0,    25,    54,    55,    66,     0,     0,     0,     0,
       0,    52,    56,    53,    73,    77,    48,     0,     0,    66,
      15,     0,     0,     0,     0,     0,    13,    27,    28,     0,
      19,     0,     0,     0,    50,    59,    60,    61,     0,    64,
       0,     0,     0,     0,     0,     0,     0,    68,    18,    20,
       0,    21,     0,    16,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    39,    31,    35,    40,     0,    33,    36,
       0,    52,    26,    22,    57,    62,     0,    51,    74,    75,
      76,    78,    79,    65,    69,    71,     0,    23,    24,    66,
      66,     0,     0,    44,    45,    47,     0,    32,    34,    38,
       0,     0,    58,     0,    70,    29,    30,     0,    80,    85,
      88,    90,    49,     0,    46,     0,    63,    72,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    37,    41,
      83,    84,    81,    82,    86,    87,    89,    91,    43,     0,
      42
  };

  const short
  parser::yypgoto_[] =
  {
    -152,  -152,     9,  -152,  -152,   213,     0,   191,   201,   227,
     107,   162,   -34,  -152,   127,  -151,   -26,   104,   -67,  -152,
    -152,    55,  -152,  -152,   -20,   -60,  -152,   100,    46,    34,
      70,    72,  -152
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     5,   105,     7,     8,    22,    13,    23,    14,     9,
      41,    42,   106,   107,   108,   109,   110,   147,    51,    52,
      53,    54,   116,    27,    28,    88,   126,    55,    56,   149,
     150,   151,   152
  };

  const unsigned char
  parser::yytable_[] =
  {
      50,    34,   111,    16,    18,    93,    70,   169,    12,     6,
       1,     2,     3,     4,    19,   143,   178,    26,    71,    38,
      39,    72,   144,    78,    15,    74,   125,    89,   180,    91,
      71,    85,    87,    90,    10,    11,    38,    39,   113,    87,
     111,    43,    44,    45,     1,    96,    97,   115,    98,    40,
      99,   100,   101,   102,    71,    17,   127,    92,   128,    33,
      87,    43,    44,    45,    46,    47,    61,   141,    21,    48,
     142,   103,    59,    25,    49,    26,   136,    57,    69,   104,
      58,    38,    39,   157,    46,    47,    65,   159,   160,    48,
      31,   111,    26,    69,    49,   161,   162,    16,    86,   124,
     111,    75,    76,    77,     1,     2,     3,     4,    79,   145,
     146,    63,   111,    67,   155,   156,    68,    87,    43,    44,
      45,     1,    96,    97,    73,    98,    26,    99,   100,   101,
     102,    80,    81,    82,    94,   118,   119,   120,    62,    95,
      64,    46,    47,    29,    30,   123,    48,   133,   103,    32,
      30,    49,    43,    44,    45,    69,   137,    35,    36,    98,
     117,    99,   100,   101,   102,    37,    36,    43,    44,    45,
      83,    84,    38,    39,   129,    46,    47,   148,   148,   130,
      48,   131,   103,   121,   122,    49,   163,   164,   132,    69,
      46,    47,    43,    44,    45,    48,   134,   174,   175,   139,
      49,   165,   140,   154,    86,   170,   171,   172,   173,   148,
     148,   148,   148,   158,   166,    46,    47,    43,    44,    45,
      48,   167,   179,   168,    24,    49,   114,    66,    43,    44,
      45,    60,    20,   112,   138,   176,   153,     0,   177,     0,
      46,    47,     0,     0,     0,    48,     0,   135,     0,     0,
      49,    46,    47,     0,     0,     0,    48,     0,     0,     0,
       0,    49
  };

  const short
  parser::yycheck_[] =
  {
      26,    21,    69,     3,     0,    65,    40,   158,     5,     0,
       6,     7,     8,     9,     5,    34,   167,    38,    34,     7,
       8,    37,    41,    49,     5,    45,    86,    61,   179,    63,
      34,    57,    58,    37,     7,     8,     7,     8,    72,    65,
     107,     3,     4,     5,     6,     7,     8,    73,    10,    37,
      12,    13,    14,    15,    34,     5,    90,    37,    92,    36,
      86,     3,     4,     5,    26,    27,    37,    34,     5,    31,
      37,    33,     5,    36,    36,    38,   102,    38,    40,    41,
      35,     7,     8,   143,    26,    27,    35,    16,    17,    31,
      36,   158,    38,    40,    36,    24,    25,    97,    40,    41,
     167,    46,    47,    48,     6,     7,     8,     9,    39,   129,
     130,    37,   179,     5,   140,   141,     5,   143,     3,     4,
       5,     6,     7,     8,    36,    10,    38,    12,    13,    14,
      15,    28,    29,    30,    38,    80,    81,    82,    31,    38,
      33,    26,    27,    33,    34,    39,    31,    33,    33,    33,
      34,    36,     3,     4,     5,    40,    41,    33,    34,    10,
      37,    12,    13,    14,    15,    33,    34,     3,     4,     5,
      26,    27,     7,     8,    39,    26,    27,   131,   132,    39,
      31,    36,    33,    83,    84,    36,    18,    19,    36,    40,
      26,    27,     3,     4,     5,    31,    33,   163,   164,    33,
      36,    20,    35,    33,    40,   159,   160,   161,   162,   163,
     164,   165,   166,    37,    21,    26,    27,     3,     4,     5,
      31,    37,    11,    33,    11,    36,    37,    36,     3,     4,
       5,    30,     5,    71,   107,   165,   132,    -1,   166,    -1,
      26,    27,    -1,    -1,    -1,    31,    -1,    33,    -1,    -1,
      36,    26,    27,    -1,    -1,    -1,    31,    -1,    -1,    -1,
      -1,    36
  };

  const signed char
  parser::yystos_[] =
  {
       0,     6,     7,     8,     9,    43,    44,    45,    46,    51,
       7,     8,     5,    48,    50,     5,    48,     5,     0,    44,
      51,     5,    47,    49,    47,    36,    38,    65,    66,    33,
      34,    36,    33,    36,    66,    33,    34,    33,     7,     8,
      37,    52,    53,     3,     4,     5,    26,    27,    31,    36,
      58,    60,    61,    62,    63,    69,    70,    38,    35,     5,
      50,    37,    52,    37,    52,    35,    49,     5,     5,    40,
      54,    34,    37,    36,    66,    63,    63,    63,    58,    39,
      28,    29,    30,    26,    27,    58,    40,    58,    67,    54,
      37,    54,    37,    67,    38,    38,     7,     8,    10,    12,
      13,    14,    15,    33,    41,    44,    54,    55,    56,    57,
      58,    60,    53,    54,    37,    58,    64,    37,    63,    63,
      63,    69,    69,    39,    41,    67,    68,    54,    54,    39,
      39,    36,    36,    33,    33,    33,    58,    41,    56,    33,
      35,    34,    37,    34,    41,    66,    66,    59,    70,    71,
      72,    73,    74,    59,    33,    58,    58,    67,    37,    16,
      17,    24,    25,    18,    19,    20,    21,    37,    33,    57,
      70,    70,    70,    70,    71,    71,    72,    73,    57,    11,
      57
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    42,    43,    43,    43,    43,    44,    44,    45,    45,
      46,    46,    47,    47,    48,    48,    49,    50,    50,    51,
      51,    51,    51,    51,    51,    52,    52,    53,    53,    53,
      53,    54,    54,    55,    55,    56,    56,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    58,    59,
      60,    61,    61,    61,    62,    62,    63,    63,    63,    63,
      63,    63,    64,    64,    65,    65,    66,    66,    67,    67,
      67,    68,    68,    69,    69,    69,    69,    70,    70,    70,
      71,    71,    71,    71,    71,    72,    72,    72,    73,    73,
      74,    74
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     1,     2,     2,     1,     1,     4,     4,
       3,     3,     1,     3,     1,     3,     4,     2,     4,     5,
       5,     5,     6,     6,     6,     1,     3,     2,     2,     5,
       5,     2,     3,     1,     2,     1,     1,     4,     2,     1,
       1,     5,     7,     5,     2,     2,     3,     2,     1,     1,
       2,     3,     1,     1,     1,     1,     1,     3,     4,     2,
       2,     2,     1,     3,     3,     4,     0,     1,     1,     2,
       3,     1,     3,     1,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       1,     3
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "INT_CONST",
  "FLOAT_CONST", "IDENT", "CONST", "INT", "FLOAT", "VOID", "IF", "ELSE",
  "WHILE", "BREAK", "CONTINUE", "RETURN", "LE", "GE", "EQ", "NE", "AND",
  "OR", "LEX_ERROR", "LOWER_THAN_ELSE", "'<'", "'>'", "'+'", "'-'", "'*'",
  "'/'", "'%'", "'!'", "UMINUS", "';'", "','", "'='", "'('", "')'", "'['",
  "']'", "'{'", "'}'", "$accept", "CompUnit", "Decl", "ConstDecl",
  "VarDecl", "ConstDefList", "VarDefList", "ConstDef", "VarDef", "FuncDef",
  "FuncParamList", "FuncParam", "Block", "BlockItemList", "BlockItem",
  "Stmt", "Exp", "Cond", "LVal", "PrimaryExp", "Number", "UnaryExp",
  "FuncRParams", "ArrayList", "ArrayDims", "InitVal", "InitValList",
  "MulExp", "AddExp", "RelExp", "EqExp", "LAndExp", "LOrExp", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   116,   116,   120,   124,   128,   135,   136,   140,   143,
     149,   152,   158,   161,   168,   171,   178,   185,   189,   196,
     200,   204,   208,   212,   216,   223,   226,   233,   237,   241,
     245,   252,   255,   261,   264,   271,   272,   276,   279,   282,
     285,   288,   291,   294,   297,   300,   303,   306,   312,   316,
     320,   327,   328,   329,   333,   334,   338,   339,   343,   347,
     348,   349,   353,   356,   363,   366,   373,   374,   378,   379,
     380,   384,   385,   389,   390,   391,   392,   396,   397,   398,
     402,   403,   404,   405,   406,   410,   411,   412,   416,   417,
     421,   422
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  parser::symbol_kind_type
  parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    31,     2,     2,     2,    30,     2,     2,
      36,    37,    28,    26,    34,    27,     2,    29,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    33,
      24,    35,    25,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    38,     2,    39,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,     2,    41,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    32
    };
    // Last valid token kind.
    const int code_max = 279;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 10 "src/yacc/sysy.y"
} // yy
#line 1905 "src/yacc/Bison.cpp"

#line 425 "src/yacc/sysy.y"


void yy::parser::error(const std::string& msg) {
    std::cerr << "Parser Error: " << msg << std::endl;
}
