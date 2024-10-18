/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp)
{
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, const char *msg)
{
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(SCF_ERROR);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ArithmeticExpr *create_arithmetic_expression(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ArithmeticExpr *expr = new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

UnboundAggregateExpr *create_aggregate_expression(const char *aggregate_name,
                                           Expression *child,
                                           const char *sql_string,
                                           YYLTYPE *llocp)
{
  UnboundAggregateExpr *expr = new UnboundAggregateExpr(aggregate_name, child);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

UnboundFunctionExpr *create_function_expression(const char *function_name,
                                           std::vector<std::unique_ptr<Expression>> *child,
                                           const char *sql_string,
                                           YYLTYPE *llocp)
{
  UnboundFunctionExpr *expr = new UnboundFunctionExpr(function_name, child);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}


#line 135 "yacc_sql.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc_sql.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_BY = 4,                         /* BY  */
  YYSYMBOL_CREATE = 5,                     /* CREATE  */
  YYSYMBOL_DROP = 6,                       /* DROP  */
  YYSYMBOL_GROUP = 7,                      /* GROUP  */
  YYSYMBOL_ORDER = 8,                      /* ORDER  */
  YYSYMBOL_TABLE = 9,                      /* TABLE  */
  YYSYMBOL_VIEW = 10,                      /* VIEW  */
  YYSYMBOL_TABLES = 11,                    /* TABLES  */
  YYSYMBOL_INDEX = 12,                     /* INDEX  */
  YYSYMBOL_UNIQUE = 13,                    /* UNIQUE  */
  YYSYMBOL_CALC = 14,                      /* CALC  */
  YYSYMBOL_SELECT = 15,                    /* SELECT  */
  YYSYMBOL_DESC = 16,                      /* DESC  */
  YYSYMBOL_ASC = 17,                       /* ASC  */
  YYSYMBOL_SHOW = 18,                      /* SHOW  */
  YYSYMBOL_SYNC = 19,                      /* SYNC  */
  YYSYMBOL_INSERT = 20,                    /* INSERT  */
  YYSYMBOL_DELETE = 21,                    /* DELETE  */
  YYSYMBOL_UPDATE = 22,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 23,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 24,                    /* RBRACE  */
  YYSYMBOL_COMMA = 25,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 26,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 27,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 28,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 29,                     /* INT_T  */
  YYSYMBOL_STRING_T = 30,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 31,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 32,                    /* DATE_T  */
  YYSYMBOL_NULL_T = 33,                    /* NULL_T  */
  YYSYMBOL_TEXT_T = 34,                    /* TEXT_T  */
  YYSYMBOL_HELP = 35,                      /* HELP  */
  YYSYMBOL_EXIT = 36,                      /* EXIT  */
  YYSYMBOL_DOT = 37,                       /* DOT  */
  YYSYMBOL_INTO = 38,                      /* INTO  */
  YYSYMBOL_VALUES = 39,                    /* VALUES  */
  YYSYMBOL_FROM = 40,                      /* FROM  */
  YYSYMBOL_WHERE = 41,                     /* WHERE  */
  YYSYMBOL_AND = 42,                       /* AND  */
  YYSYMBOL_SET = 43,                       /* SET  */
  YYSYMBOL_ON = 44,                        /* ON  */
  YYSYMBOL_LOAD = 45,                      /* LOAD  */
  YYSYMBOL_VECTOR_T = 46,                  /* VECTOR_T  */
  YYSYMBOL_INFILE = 47,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 48,                   /* EXPLAIN  */
  YYSYMBOL_STORAGE = 49,                   /* STORAGE  */
  YYSYMBOL_FORMAT = 50,                    /* FORMAT  */
  YYSYMBOL_EQ = 51,                        /* EQ  */
  YYSYMBOL_LT = 52,                        /* LT  */
  YYSYMBOL_GT = 53,                        /* GT  */
  YYSYMBOL_LE = 54,                        /* LE  */
  YYSYMBOL_GE = 55,                        /* GE  */
  YYSYMBOL_NE = 56,                        /* NE  */
  YYSYMBOL_SUM = 57,                       /* SUM  */
  YYSYMBOL_AVG = 58,                       /* AVG  */
  YYSYMBOL_MAX = 59,                       /* MAX  */
  YYSYMBOL_MIN = 60,                       /* MIN  */
  YYSYMBOL_COUNT = 61,                     /* COUNT  */
  YYSYMBOL_NOT = 62,                       /* NOT  */
  YYSYMBOL_NULLABLE = 63,                  /* NULLABLE  */
  YYSYMBOL_IS = 64,                        /* IS  */
  YYSYMBOL_HAVING = 65,                    /* HAVING  */
  YYSYMBOL_IN = 66,                        /* IN  */
  YYSYMBOL_LIKE = 67,                      /* LIKE  */
  YYSYMBOL_OR = 68,                        /* OR  */
  YYSYMBOL_INNER = 69,                     /* INNER  */
  YYSYMBOL_JOIN = 70,                      /* JOIN  */
  YYSYMBOL_LENGTH = 71,                    /* LENGTH  */
  YYSYMBOL_ROUND = 72,                     /* ROUND  */
  YYSYMBOL_DATE_FORMAT = 73,               /* DATE_FORMAT  */
  YYSYMBOL_AS = 74,                        /* AS  */
  YYSYMBOL_NUMBER = 75,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 76,                     /* FLOAT  */
  YYSYMBOL_ID = 77,                        /* ID  */
  YYSYMBOL_SSS = 78,                       /* SSS  */
  YYSYMBOL_DATE_STR = 79,                  /* DATE_STR  */
  YYSYMBOL_80_ = 80,                       /* '+'  */
  YYSYMBOL_81_ = 81,                       /* '-'  */
  YYSYMBOL_82_ = 82,                       /* '*'  */
  YYSYMBOL_83_ = 83,                       /* '/'  */
  YYSYMBOL_UMINUS = 84,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 85,                  /* $accept  */
  YYSYMBOL_commands = 86,                  /* commands  */
  YYSYMBOL_command_wrapper = 87,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 88,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 89,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 90,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 91,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 92,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 93,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 94,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 95,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 96,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 97,         /* create_index_stmt  */
  YYSYMBOL_IDList = 98,                    /* IDList  */
  YYSYMBOL_drop_index_stmt = 99,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 100,        /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 101,            /* attr_def_list  */
  YYSYMBOL_attr_def = 102,                 /* attr_def  */
  YYSYMBOL_create_view_stmt = 103,         /* create_view_stmt  */
  YYSYMBOL_idlist = 104,                   /* idlist  */
  YYSYMBOL_number = 105,                   /* number  */
  YYSYMBOL_type = 106,                     /* type  */
  YYSYMBOL_insert_stmt = 107,              /* insert_stmt  */
  YYSYMBOL_value = 108,                    /* value  */
  YYSYMBOL_storage_format = 109,           /* storage_format  */
  YYSYMBOL_delete_stmt = 110,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 111,              /* update_stmt  */
  YYSYMBOL_update_values = 112,            /* update_values  */
  YYSYMBOL_update_value = 113,             /* update_value  */
  YYSYMBOL_select_stmt = 114,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 115,                /* calc_stmt  */
  YYSYMBOL_from = 116,                     /* from  */
  YYSYMBOL_join_list = 117,                /* join_list  */
  YYSYMBOL_join_entry = 118,               /* join_entry  */
  YYSYMBOL_on = 119,                       /* on  */
  YYSYMBOL_as_alias = 120,                 /* as_alias  */
  YYSYMBOL_expression_list = 121,          /* expression_list  */
  YYSYMBOL_expression_with_alias = 122,    /* expression_with_alias  */
  YYSYMBOL_expression = 123,               /* expression  */
  YYSYMBOL_function_type = 124,            /* function_type  */
  YYSYMBOL_aggregate_type = 125,           /* aggregate_type  */
  YYSYMBOL_rel_attr = 126,                 /* rel_attr  */
  YYSYMBOL_relation = 127,                 /* relation  */
  YYSYMBOL_rel_list = 128,                 /* rel_list  */
  YYSYMBOL_where = 129,                    /* where  */
  YYSYMBOL_having_condition = 130,         /* having_condition  */
  YYSYMBOL_condition_list = 131,           /* condition_list  */
  YYSYMBOL_condition = 132,                /* condition  */
  YYSYMBOL_comp_op = 133,                  /* comp_op  */
  YYSYMBOL_group_by = 134,                 /* group_by  */
  YYSYMBOL_order_by_info = 135,            /* order_by_info  */
  YYSYMBOL_order_by_expression_list = 136, /* order_by_expression_list  */
  YYSYMBOL_order_by_type = 137,            /* order_by_type  */
  YYSYMBOL_sub_select = 138,               /* sub_select  */
  YYSYMBOL_load_data_stmt = 139,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 140,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 141,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 142             /* opt_semicolon  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  82
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   289

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  85
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  156
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  276

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   335


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    82,    80,     2,    81,     2,    83,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    84
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   254,   254,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   286,   292,   297,   303,   309,   315,
     321,   328,   334,   342,   357,   377,   380,   393,   403,   424,
     442,   463,   466,   479,   488,   498,   507,   517,   526,   536,
     545,   557,   570,   586,   587,   590,   593,   594,   595,   596,
     597,   598,   601,   613,   646,   650,   654,   660,   666,   672,
     675,   682,   694,   717,   720,   731,   739,   781,   790,   795,
     801,   806,   818,   830,   835,   843,   846,   852,   857,   870,
     874,   879,   882,   885,   888,   891,   895,   898,   905,   912,
     918,   923,   928,   932,   937,   943,   953,   957,   961,   969,
     972,   975,   978,   981,   985,   990,   997,  1006,  1012,  1020,
    1025,  1039,  1042,  1049,  1053,  1060,  1063,  1068,  1073,  1080,
    1093,  1094,  1095,  1096,  1097,  1098,  1099,  1100,  1101,  1102,
    1103,  1104,  1110,  1113,  1122,  1125,  1134,  1140,  1154,  1157,
    1161,  1168,  1182,  1195,  1203,  1213,  1214
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "BY",
  "CREATE", "DROP", "GROUP", "ORDER", "TABLE", "VIEW", "TABLES", "INDEX",
  "UNIQUE", "CALC", "SELECT", "DESC", "ASC", "SHOW", "SYNC", "INSERT",
  "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "DATE_T",
  "NULL_T", "TEXT_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM",
  "WHERE", "AND", "SET", "ON", "LOAD", "VECTOR_T", "INFILE", "EXPLAIN",
  "STORAGE", "FORMAT", "EQ", "LT", "GT", "LE", "GE", "NE", "SUM", "AVG",
  "MAX", "MIN", "COUNT", "NOT", "NULLABLE", "IS", "HAVING", "IN", "LIKE",
  "OR", "INNER", "JOIN", "LENGTH", "ROUND", "DATE_FORMAT", "AS", "NUMBER",
  "FLOAT", "ID", "SSS", "DATE_STR", "'+'", "'-'", "'*'", "'/'", "UMINUS",
  "$accept", "commands", "command_wrapper", "exit_stmt", "help_stmt",
  "sync_stmt", "begin_stmt", "commit_stmt", "rollback_stmt",
  "drop_table_stmt", "show_tables_stmt", "desc_table_stmt",
  "create_index_stmt", "IDList", "drop_index_stmt", "create_table_stmt",
  "attr_def_list", "attr_def", "create_view_stmt", "idlist", "number",
  "type", "insert_stmt", "value", "storage_format", "delete_stmt",
  "update_stmt", "update_values", "update_value", "select_stmt",
  "calc_stmt", "from", "join_list", "join_entry", "on", "as_alias",
  "expression_list", "expression_with_alias", "expression",
  "function_type", "aggregate_type", "rel_attr", "relation", "rel_list",
  "where", "having_condition", "condition_list", "condition", "comp_op",
  "group_by", "order_by_info", "order_by_expression_list", "order_by_type",
  "sub_select", "load_data_stmt", "explain_stmt", "set_variable_stmt",
  "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-233)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     214,   107,    19,   128,   128,   -55,    18,  -233,    -1,     7,
     -36,  -233,  -233,  -233,  -233,  -233,    -2,    21,   214,    81,
      98,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,    26,    32,    38,   100,    44,    50,     1,  -233,
    -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
      96,  -233,  -233,   128,  -233,  -233,  -233,   109,    25,   113,
     115,  -233,  -233,    95,  -233,  -233,    62,    63,   102,    90,
     108,  -233,  -233,  -233,  -233,   -20,   -19,   110,    80,  -233,
     118,   145,   -17,   -59,  -233,   128,    93,  -233,   128,   128,
     128,   128,  -233,   128,    71,    94,   104,    -9,   140,   105,
      35,   106,   114,   168,   119,   168,   120,   146,   121,  -233,
    -233,   128,  -233,  -233,  -233,  -233,   -12,   -12,  -233,  -233,
     178,  -233,     8,   -32,   183,  -233,   141,   140,   104,   119,
     128,   128,  -233,   161,   188,  -233,   177,   222,   191,   169,
     192,   197,  -233,   199,   148,  -233,   207,  -233,  -233,   128,
    -233,    94,    94,   216,  -233,   213,  -233,   112,  -233,   -30,
     128,   105,   140,   229,  -233,  -233,  -233,  -233,  -233,  -233,
     -14,   114,   215,   193,  -233,   119,   170,   171,   223,  -233,
     221,  -233,   203,   251,   195,   219,  -233,  -233,  -233,  -233,
    -233,  -233,    30,   201,  -233,  -233,   128,   128,   128,    43,
     188,  -233,   184,   189,  -233,   232,  -233,   191,    -5,   218,
    -233,   168,   241,   190,  -233,   128,  -233,   128,   128,   262,
     128,  -233,  -233,  -233,    43,  -233,  -233,  -233,  -233,  -233,
     247,  -233,  -233,  -233,   169,   196,  -233,   198,   248,   241,
    -233,  -233,  -233,   270,  -233,  -233,   -27,  -233,  -233,   241,
    -233,   252,   128,  -233,   244,  -233,  -233,  -233,     4,  -233,
    -233,  -233,  -233,   253,   128,  -233
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    26,     0,     0,
       0,    27,    28,    29,    25,    24,     0,     0,     0,     0,
     155,    23,    22,    15,    16,    17,    18,    10,    11,    12,
      13,    14,     8,     9,     5,     7,     6,     4,     3,    19,
      20,    21,     0,     0,     0,     0,     0,     0,     0,    68,
     109,   112,   110,   111,   113,   106,   107,   108,    64,    65,
     114,    66,    67,     0,   100,    97,    77,    87,    90,     0,
       0,    99,   104,    78,    32,    31,     0,     0,     0,     0,
       0,   153,     1,   156,     2,     0,     0,     0,     0,    30,
       0,     0,     0,     0,    96,     0,     0,    85,     0,     0,
       0,     0,    89,     0,     0,     0,    80,     0,   121,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   151,
      95,     0,   115,   116,    88,    86,    91,    92,    93,    94,
       0,   102,     0,   118,   119,    79,     0,   121,    80,     0,
       0,   125,    71,     0,    73,   154,     0,     0,    41,    69,
      53,     0,    51,     0,     0,    37,     0,   105,   101,     0,
     117,     0,     0,   142,    81,     0,    62,     0,   122,   126,
       0,     0,   121,     0,    56,    57,    58,    59,    60,    61,
      44,     0,     0,     0,    39,     0,     0,     0,     0,    98,
       0,   120,    83,     0,   123,     0,   130,   131,   132,   133,
     134,   135,     0,   136,   139,   138,     0,   125,   125,    75,
      73,    72,     0,     0,    48,     0,    46,    41,    69,     0,
      54,     0,    35,     0,   103,   125,    82,     0,   125,   144,
       0,   140,   141,   137,   129,   127,   128,    74,   152,    55,
       0,    50,    42,    38,    69,     0,    52,     0,     0,    35,
      84,   143,   124,     0,    76,    63,    43,    40,    70,    35,
      33,     0,     0,    47,     0,    45,    36,    34,   148,   145,
      49,   150,   149,   146,     0,   147
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -233,  -233,   261,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,  -233,  -232,  -233,  -233,    64,    99,  -233,  -128,
    -233,  -233,  -233,   172,  -205,  -233,  -233,    73,   116,   -46,
    -233,  -233,   147,  -233,  -233,   151,    -3,  -233,   -48,  -233,
    -233,  -233,   124,   127,  -132,  -233,  -182,  -233,  -233,  -233,
    -233,    15,  -233,  -233,  -233,  -233,  -233,  -233
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   248,    31,    32,   182,   148,    33,   151,
     240,   180,    34,    65,   184,    35,    36,   172,   144,    37,
      38,   106,   137,   138,   226,   102,    66,    67,    68,    69,
      70,    71,   134,   135,   142,   229,   168,   169,   206,   194,
     254,   269,   273,    72,    39,    40,    41,    84
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      92,    73,    91,   112,   114,   163,   263,   120,   121,   213,
       4,   165,   207,   243,   139,    94,     4,   261,   122,   214,
     271,   272,    74,   123,    48,   235,   236,   266,    46,    75,
     140,    47,   158,   159,    49,   264,   265,    76,   208,   257,
     211,    78,    96,   250,   183,    97,   252,    77,   215,   216,
     126,   127,   128,   129,   113,   115,   132,   220,    50,    51,
      52,    53,    54,    98,    99,   100,   101,   149,    49,   152,
     100,   101,    55,    56,    57,    79,    58,    59,    60,    61,
      62,    82,    63,    64,    98,    99,   100,   101,    98,    99,
     100,   101,   124,   167,    48,   131,   231,   232,    80,    96,
     130,    83,    97,    85,    49,    98,    99,   100,   101,    86,
      58,    59,    88,    61,    62,    87,    42,    43,   156,    44,
      45,    89,   209,    98,    99,   100,   101,    90,    50,    51,
      52,    53,    54,    93,    95,   105,   103,   166,   104,   107,
     108,   110,    55,    56,    57,   109,    58,    59,    60,    61,
      62,    48,    63,    64,   116,   111,   190,   117,   234,   167,
     167,    49,   118,   196,   197,   198,   199,   200,   201,   119,
     125,   133,   244,   136,   202,   246,   203,   167,   204,   205,
     167,   141,   143,     4,   146,    50,    51,    52,    53,    54,
     154,   147,    98,    99,   100,   101,   150,   153,   155,    55,
      56,    57,   157,    58,    59,    60,    61,    62,   161,    63,
      64,   162,   170,   171,   268,   173,   181,   185,   183,     1,
       2,   186,   187,   193,   251,   188,   268,   255,     3,     4,
       5,   189,     6,     7,     8,     9,    10,   195,   212,   218,
      11,    12,    13,   219,   221,   224,   223,   225,   222,    14,
      15,   174,   175,   176,   177,   227,   178,    16,   230,    17,
     228,   238,    18,   233,   239,   241,   247,   249,   179,   245,
     253,   256,   260,   258,   262,   259,   267,   270,   274,    81,
     217,   242,   145,   237,   160,   164,   192,   210,   191,   275
};

static const yytype_int16 yycheck[] =
{
      48,     4,    48,    23,    23,   137,    33,    24,    25,    23,
      15,   139,    42,   218,    23,    63,    15,   249,    77,    33,
      16,    17,    77,    82,    23,   207,   208,   259,     9,    11,
      39,    12,    24,    25,    33,    62,    63,    38,    68,   244,
     172,    77,    74,   225,    49,    77,   228,    40,    62,    63,
      98,    99,   100,   101,    74,    74,   104,   185,    57,    58,
      59,    60,    61,    80,    81,    82,    83,   113,    33,   115,
      82,    83,    71,    72,    73,    77,    75,    76,    77,    78,
      79,     0,    81,    82,    80,    81,    82,    83,    80,    81,
      82,    83,    95,   141,    23,    24,    66,    67,    77,    74,
     103,     3,    77,    77,    33,    80,    81,    82,    83,    77,
      75,    76,    12,    78,    79,    77,     9,    10,   121,    12,
      13,    77,   170,    80,    81,    82,    83,    77,    57,    58,
      59,    60,    61,    37,    25,    40,    23,   140,    23,    77,
      77,    51,    71,    72,    73,    43,    75,    76,    77,    78,
      79,    23,    81,    82,    44,    47,   159,    77,   206,   207,
     208,    33,    44,    51,    52,    53,    54,    55,    56,    24,
      77,    77,   218,    69,    62,   221,    64,   225,    66,    67,
     228,    41,    77,    15,    78,    57,    58,    59,    60,    61,
      44,    77,    80,    81,    82,    83,    77,    77,    77,    71,
      72,    73,    24,    75,    76,    77,    78,    79,    25,    81,
      82,    70,    51,    25,   262,    38,    25,    25,    49,     5,
       6,    24,    23,     7,   227,    77,   274,   230,    14,    15,
      16,    24,    18,    19,    20,    21,    22,    24,     9,    24,
      26,    27,    28,    50,    74,    24,    23,    44,    77,    35,
      36,    29,    30,    31,    32,     4,    34,    43,    39,    45,
      65,    77,    48,    62,    75,    33,    25,    77,    46,    51,
       8,    24,    24,    77,     4,    77,    24,    33,    25,    18,
     181,   217,   110,   210,   133,   138,   162,   171,   161,   274
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    14,    15,    16,    18,    19,    20,    21,
      22,    26,    27,    28,    35,    36,    43,    45,    48,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    99,   100,   103,   107,   110,   111,   114,   115,   139,
     140,   141,     9,    10,    12,    13,     9,    12,    23,    33,
      57,    58,    59,    60,    61,    71,    72,    73,    75,    76,
      77,    78,    79,    81,    82,   108,   121,   122,   123,   124,
     125,   126,   138,   121,    77,    11,    38,    40,    77,    77,
      77,    87,     0,     3,   142,    77,    77,    77,    12,    77,
      77,   114,   123,    37,   123,    25,    74,    77,    80,    81,
      82,    83,   120,    23,    23,    40,   116,    77,    77,    43,
      51,    47,    23,    74,    23,    74,    44,    77,    44,    24,
      24,    25,    77,    82,   121,    77,   123,   123,   123,   123,
     121,    24,   123,    77,   127,   128,    69,   117,   118,    23,
      39,    41,   129,    77,   113,   108,    78,    77,   102,   114,
      77,   104,   114,    77,    44,    77,   121,    24,    24,    25,
     120,    25,    70,   129,   117,   104,   121,   123,   131,   132,
      51,    25,   112,    38,    29,    30,    31,    32,    34,    46,
     106,    25,   101,    49,   109,    25,    24,    23,    77,    24,
     121,   128,   127,     7,   134,    24,    51,    52,    53,    54,
      55,    56,    62,    64,    66,    67,   133,    42,    68,   123,
     113,   129,     9,    23,    33,    62,    63,   102,    24,    50,
     104,    74,    77,    23,    24,    44,   119,     4,    65,   130,
      39,    66,    67,    62,   123,   131,   131,   112,    77,    75,
     105,    33,   101,   109,   114,    51,   114,    25,    98,    77,
     131,   121,   131,     8,   135,   121,    24,   109,    77,    77,
      24,    98,     4,    33,    62,    63,    98,    24,   123,   136,
      33,    16,    17,   137,    25,   136
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    85,    86,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    97,    98,    98,    99,   100,   100,
     100,   101,   101,   102,   102,   102,   102,   102,   102,   102,
     102,   103,   103,   104,   104,   105,   106,   106,   106,   106,
     106,   106,   107,   107,   108,   108,   108,   108,   108,   109,
     109,   110,   111,   112,   112,   113,   114,   115,   116,   116,
     117,   117,   118,   119,   119,   120,   120,   121,   121,   122,
     122,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   123,   123,   124,   124,   124,   125,
     125,   125,   125,   125,   126,   126,   126,   127,   127,   128,
     128,   129,   129,   130,   130,   131,   131,   131,   131,   132,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   134,   134,   135,   135,   136,   136,   137,   137,
     137,   138,   139,   140,   141,   142,   142
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     2,     9,    10,     0,     3,     5,     8,     6,
       9,     0,     3,     5,     2,     6,     3,     6,     3,     7,
       4,     5,     8,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     5,     8,     1,     1,     1,     1,     1,     0,
       4,     4,     6,     0,     3,     3,     8,     2,     0,     2,
       0,     2,     4,     0,     2,     1,     2,     1,     3,     2,
       1,     3,     3,     3,     3,     3,     2,     1,     5,     1,
       1,     4,     3,     6,     1,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     2,     1,     1,
       3,     0,     2,     0,     2,     0,     1,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       2,     2,     0,     3,     0,     3,     2,     4,     0,     1,
       1,     3,     7,     2,     4,     0,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, sql_string, sql_result, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), sql_string, sql_result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* commands: command_wrapper opt_semicolon  */
#line 255 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1877 "yacc_sql.cpp"
    break;

  case 24: /* exit_stmt: EXIT  */
#line 286 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1886 "yacc_sql.cpp"
    break;

  case 25: /* help_stmt: HELP  */
#line 292 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1894 "yacc_sql.cpp"
    break;

  case 26: /* sync_stmt: SYNC  */
#line 297 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1902 "yacc_sql.cpp"
    break;

  case 27: /* begin_stmt: TRX_BEGIN  */
#line 303 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1910 "yacc_sql.cpp"
    break;

  case 28: /* commit_stmt: TRX_COMMIT  */
#line 309 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1918 "yacc_sql.cpp"
    break;

  case 29: /* rollback_stmt: TRX_ROLLBACK  */
#line 315 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1926 "yacc_sql.cpp"
    break;

  case 30: /* drop_table_stmt: DROP TABLE ID  */
#line 321 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1936 "yacc_sql.cpp"
    break;

  case 31: /* show_tables_stmt: SHOW TABLES  */
#line 328 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1944 "yacc_sql.cpp"
    break;

  case 32: /* desc_table_stmt: DESC ID  */
#line 334 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1954 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE ID IDList RBRACE  */
#line 343 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-6].string);
      create_index.relation_name = (yyvsp[-4].string);
      if ((yyvsp[-1].IDList) != nullptr) {
        (yyval.sql_node)->create_index.attribute_name.swap(*(yyvsp[-1].IDList));
      }
      create_index.attribute_name.push_back((yyvsp[-2].string));
      std::reverse((yyval.sql_node)->create_index.attribute_name.begin(), (yyval.sql_node)->create_index.attribute_name.end());
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
    }
#line 1973 "yacc_sql.cpp"
    break;

  case 34: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE ID IDList RBRACE  */
#line 358 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-6].string);
      create_index.relation_name = (yyvsp[-4].string);
      create_index.is_unique = 1;

      if ((yyvsp[-1].IDList) != nullptr) {
        (yyval.sql_node)->create_index.attribute_name.swap(*(yyvsp[-1].IDList));
      }
      create_index.attribute_name.push_back((yyvsp[-2].string));
      std::reverse((yyval.sql_node)->create_index.attribute_name.begin(), (yyval.sql_node)->create_index.attribute_name.end());
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
    }
#line 1994 "yacc_sql.cpp"
    break;

  case 35: /* IDList: %empty  */
#line 377 "yacc_sql.y"
        {
          (yyval.IDList) =nullptr;
        }
#line 2002 "yacc_sql.cpp"
    break;

  case 36: /* IDList: COMMA ID IDList  */
#line 380 "yacc_sql.y"
                     {
        if((yyvsp[0].IDList)==nullptr){
          (yyval.IDList)= new std::vector<string>;
        }
        else{
          (yyval.IDList)=(yyvsp[0].IDList);
        }
        (yyval.IDList)->push_back((yyvsp[-1].string));
        free((yyvsp[-1].string));
      }
#line 2017 "yacc_sql.cpp"
    break;

  case 37: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 394 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2029 "yacc_sql.cpp"
    break;

  case 38: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 404 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-5].string);
      free((yyvsp[-5].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-2].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-3].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-3].attr_info);
      if ((yyvsp[0].string) != nullptr) {
        create_table.storage_format = (yyvsp[0].string);
        free((yyvsp[0].string));
      }
    }
#line 2054 "yacc_sql.cpp"
    break;

  case 39: /* create_table_stmt: CREATE TABLE ID AS select_stmt storage_format  */
#line 425 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-3].string);
      free((yyvsp[-3].string));

      SelectSqlNode *sqlnode = new SelectSqlNode;
      (*sqlnode) = std::move((yyvsp[-1].sql_node)->selection);
      delete (yyvsp[-1].sql_node);
      Expression * expr = new UnboundSubSelectExpr(sqlnode);
      create_table.sub_select=std::unique_ptr<Expression>(expr);
      
      if ((yyvsp[0].string) != nullptr) {
        create_table.storage_format = (yyvsp[0].string);
        free((yyvsp[0].string));
      }
    }
#line 2076 "yacc_sql.cpp"
    break;

  case 40: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE select_stmt storage_format  */
#line 443 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-6].string);
      free((yyvsp[-6].string));

      SelectSqlNode *sqlnode = new SelectSqlNode;
      (*sqlnode) = std::move((yyvsp[-1].sql_node)->selection);
      delete (yyvsp[-1].sql_node);
      Expression * expr = new UnboundSubSelectExpr(sqlnode);
      create_table.sub_select=std::unique_ptr<Expression>(expr);
      
      if ((yyvsp[0].string) != nullptr) {
        create_table.storage_format = (yyvsp[0].string);
        free((yyvsp[0].string));
      }
    }
#line 2098 "yacc_sql.cpp"
    break;

  case 41: /* attr_def_list: %empty  */
#line 463 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2106 "yacc_sql.cpp"
    break;

  case 42: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 467 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2120 "yacc_sql.cpp"
    break;

  case 43: /* attr_def: ID type LBRACE number RBRACE  */
#line 480 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-3].number);
      (yyval.attr_info)->name = (yyvsp[-4].string);
      (yyval.attr_info)->length = (yyvsp[-1].number);
      free((yyvsp[-4].string));
      (yyval.attr_info)->can_be_null = true;
    }
#line 2133 "yacc_sql.cpp"
    break;

  case 44: /* attr_def: ID type  */
#line 489 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[0].number);
      (yyval.attr_info)->name = (yyvsp[-1].string);
      (yyval.attr_info)->length = 4;
      free((yyvsp[-1].string));
      (yyval.attr_info)->can_be_null = true;
    }
#line 2146 "yacc_sql.cpp"
    break;

  case 45: /* attr_def: ID type LBRACE number RBRACE NULLABLE  */
#line 499 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      free((yyvsp[-5].string));
      (yyval.attr_info)->can_be_null = true;
    }
#line 2159 "yacc_sql.cpp"
    break;

  case 46: /* attr_def: ID type NULLABLE  */
#line 508 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      free((yyvsp[-2].string));
      (yyval.attr_info)->can_be_null = true;
    }
#line 2172 "yacc_sql.cpp"
    break;

  case 47: /* attr_def: ID type LBRACE number RBRACE NULL_T  */
#line 518 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      free((yyvsp[-5].string));
      (yyval.attr_info)->can_be_null = true;
    }
#line 2185 "yacc_sql.cpp"
    break;

  case 48: /* attr_def: ID type NULL_T  */
#line 527 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      free((yyvsp[-2].string));
      (yyval.attr_info)->can_be_null = true;
    }
#line 2198 "yacc_sql.cpp"
    break;

  case 49: /* attr_def: ID type LBRACE number RBRACE NOT NULL_T  */
#line 537 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-5].number);
      (yyval.attr_info)->name = (yyvsp[-6].string);
      (yyval.attr_info)->length = (yyvsp[-3].number);
      free((yyvsp[-6].string));
      (yyval.attr_info)->can_be_null = false;
    }
#line 2211 "yacc_sql.cpp"
    break;

  case 50: /* attr_def: ID type NOT NULL_T  */
#line 546 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-2].number);
      (yyval.attr_info)->name = (yyvsp[-3].string);
      (yyval.attr_info)->length = 4;
      free((yyvsp[-3].string));
      (yyval.attr_info)->can_be_null = false;
    }
#line 2224 "yacc_sql.cpp"
    break;

  case 51: /* create_view_stmt: CREATE VIEW ID AS select_stmt  */
#line 558 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_VIEW);
      CreateViewSqlNode &create_view = (yyval.sql_node)->create_view;
      create_view.relation_name = (yyvsp[-2].string);
      free((yyvsp[-2].string));

      SelectSqlNode *sqlnode = new SelectSqlNode;
      (*sqlnode) = std::move((yyvsp[0].sql_node)->selection);
      delete (yyvsp[0].sql_node);
      Expression * expr = new UnboundSubSelectExpr(sqlnode);
      create_view.sub_select=std::unique_ptr<Expression>(expr);      
    }
#line 2241 "yacc_sql.cpp"
    break;

  case 52: /* create_view_stmt: CREATE VIEW ID LBRACE idlist RBRACE AS select_stmt  */
#line 571 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_VIEW);
      CreateViewSqlNode &create_view = (yyval.sql_node)->create_view;
      create_view.relation_name = (yyvsp[-5].string);
      free((yyvsp[-5].string));

      SelectSqlNode *sqlnode = new SelectSqlNode;
      (*sqlnode) = std::move((yyvsp[0].sql_node)->selection);
      delete (yyvsp[0].sql_node);
      Expression * expr = new UnboundSubSelectExpr(sqlnode);
      create_view.sub_select=std::unique_ptr<Expression>(expr);      
    }
#line 2258 "yacc_sql.cpp"
    break;

  case 55: /* number: NUMBER  */
#line 590 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2264 "yacc_sql.cpp"
    break;

  case 56: /* type: INT_T  */
#line 593 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2270 "yacc_sql.cpp"
    break;

  case 57: /* type: STRING_T  */
#line 594 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2276 "yacc_sql.cpp"
    break;

  case 58: /* type: FLOAT_T  */
#line 595 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2282 "yacc_sql.cpp"
    break;

  case 59: /* type: DATE_T  */
#line 596 "yacc_sql.y"
             { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2288 "yacc_sql.cpp"
    break;

  case 60: /* type: TEXT_T  */
#line 597 "yacc_sql.y"
             { (yyval.number) = static_cast<int>(AttrType::TEXTS); }
#line 2294 "yacc_sql.cpp"
    break;

  case 61: /* type: VECTOR_T  */
#line 598 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2300 "yacc_sql.cpp"
    break;

  case 62: /* insert_stmt: INSERT INTO ID VALUES expression_list  */
#line 602 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-2].string);
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[0].expression_list));
        delete (yyvsp[0].expression_list);
      }
      free((yyvsp[-2].string));
    }
#line 2314 "yacc_sql.cpp"
    break;

  case 63: /* insert_stmt: INSERT INTO ID LBRACE idlist RBRACE VALUES expression_list  */
#line 614 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-5].string);
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[0].expression_list));
        delete (yyvsp[0].expression_list);
      }
      free((yyvsp[-5].string));
    }
#line 2328 "yacc_sql.cpp"
    break;

  case 64: /* value: NUMBER  */
#line 646 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2337 "yacc_sql.cpp"
    break;

  case 65: /* value: FLOAT  */
#line 650 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2346 "yacc_sql.cpp"
    break;

  case 66: /* value: SSS  */
#line 654 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2357 "yacc_sql.cpp"
    break;

  case 67: /* value: DATE_STR  */
#line 660 "yacc_sql.y"
              {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp,-1);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2368 "yacc_sql.cpp"
    break;

  case 68: /* value: NULL_T  */
#line 666 "yacc_sql.y"
           {
      (yyval.value) = new Value("null",-2);  // -2 表示null类型
    }
#line 2376 "yacc_sql.cpp"
    break;

  case 69: /* storage_format: %empty  */
#line 672 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2384 "yacc_sql.cpp"
    break;

  case 70: /* storage_format: STORAGE FORMAT EQ ID  */
#line 676 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2392 "yacc_sql.cpp"
    break;

  case 71: /* delete_stmt: DELETE FROM ID where  */
#line 683 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2406 "yacc_sql.cpp"
    break;

  case 72: /* update_stmt: UPDATE ID SET update_value update_values where  */
#line 695 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-4].string);
      
      if((yyvsp[-1].update_values) != nullptr){
        (yyval.sql_node)->update.update_values.swap(*(yyvsp[-1].update_values));
        delete (yyvsp[-1].update_values);
      }
      

      (yyval.sql_node)->update.update_values.push_back(std::move(*(yyvsp[-2].update_value)));


      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-4].string));
    }
#line 2430 "yacc_sql.cpp"
    break;

  case 73: /* update_values: %empty  */
#line 717 "yacc_sql.y"
        {
          (yyval.update_values) =nullptr;
        }
#line 2438 "yacc_sql.cpp"
    break;

  case 74: /* update_values: COMMA update_value update_values  */
#line 720 "yacc_sql.y"
                                      {
        if((yyvsp[0].update_values)==nullptr){
          (yyval.update_values)= new std::vector<UpdateValueNode>;
        }
        else{
          (yyval.update_values)=(yyvsp[0].update_values);
        }
        (yyval.update_values)->push_back(std::move(*(yyvsp[-1].update_value)));
      }
#line 2452 "yacc_sql.cpp"
    break;

  case 75: /* update_value: ID EQ expression  */
#line 731 "yacc_sql.y"
                    {
      UpdateValueNode *updatevalue =new UpdateValueNode();
      updatevalue->attribute_name = (yyvsp[-2].string);
      updatevalue->expr = std::unique_ptr<Expression>((yyvsp[0].expression));
      (yyval.update_value) = updatevalue;
    }
#line 2463 "yacc_sql.cpp"
    break;

  case 76: /* select_stmt: SELECT expression_list from join_list where group_by having_condition order_by_info  */
#line 740 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-6].expression_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-6].expression_list));
        delete (yyvsp[-6].expression_list);
      }

      if ((yyvsp[-5].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-5].relation_list));
        delete (yyvsp[-5].relation_list);
      }

      if ((yyvsp[-4].join_list) != nullptr) {
        (yyval.sql_node)->selection.join_info.swap(*(yyvsp[-4].join_list));
        delete (yyvsp[-4].join_list);
      }

      if ((yyvsp[-3].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-3].condition_list));
        delete (yyvsp[-3].condition_list);
      }

      if ((yyvsp[-2].expression_list) != nullptr) {
        (yyval.sql_node)->selection.group_by.swap(*(yyvsp[-2].expression_list));
        delete (yyvsp[-2].expression_list);
      }
      
      if ((yyvsp[-1].condition_list) != nullptr) {
        (yyval.sql_node)->selection.group_by_conditions.swap(*(yyvsp[-1].condition_list));
        delete (yyvsp[-1].condition_list);
      }

      if ((yyvsp[0].order_by_info) != nullptr) {
        (yyval.sql_node)->selection.order_by.order_by_attrs.swap((yyvsp[0].order_by_info)->order_by_attrs);
        (yyval.sql_node)->selection.order_by.order_by_types.swap((yyvsp[0].order_by_info)->order_by_types);
        delete (yyvsp[0].order_by_info);
      }

    }
#line 2507 "yacc_sql.cpp"
    break;

  case 77: /* calc_stmt: CALC expression_list  */
#line 782 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2517 "yacc_sql.cpp"
    break;

  case 78: /* from: %empty  */
#line 790 "yacc_sql.y"
  {
    // empty
    (yyval.relation_list) = nullptr;
  }
#line 2526 "yacc_sql.cpp"
    break;

  case 79: /* from: FROM rel_list  */
#line 795 "yacc_sql.y"
               {
    (yyval.relation_list) = (yyvsp[0].relation_list);
  }
#line 2534 "yacc_sql.cpp"
    break;

  case 80: /* join_list: %empty  */
#line 801 "yacc_sql.y"
  {
    /*empty*/
    (yyval.join_list) = nullptr;
  }
#line 2543 "yacc_sql.cpp"
    break;

  case 81: /* join_list: join_entry join_list  */
#line 806 "yacc_sql.y"
                      {
    if ((yyvsp[0].join_list) != nullptr) {
      (yyval.join_list) = (yyvsp[0].join_list);
    }
    else {
      (yyval.join_list) = new std::vector<JoinEntry>;
    }
    (yyval.join_list)->push_back(std::move(*(yyvsp[-1].join_entry)));
  }
#line 2557 "yacc_sql.cpp"
    break;

  case 82: /* join_entry: INNER JOIN relation on  */
#line 818 "yacc_sql.y"
                         {
    (yyval.join_entry) = new JoinEntry;
    (yyval.join_entry)->join_table = *(yyvsp[-1].relation);
    delete((yyvsp[-1].relation));
    if ((yyvsp[0].condition_list) != nullptr) {
      (yyval.join_entry)->join_conditions.swap(*(yyvsp[0].condition_list));
      delete (yyvsp[0].condition_list);
    }
  }
#line 2571 "yacc_sql.cpp"
    break;

  case 83: /* on: %empty  */
#line 830 "yacc_sql.y"
  {
    /*empty*/
    (yyval.condition_list) = nullptr;
  }
#line 2580 "yacc_sql.cpp"
    break;

  case 84: /* on: ON condition_list  */
#line 836 "yacc_sql.y"
  {
    (yyval.condition_list) = (yyvsp[0].condition_list);
  }
#line 2588 "yacc_sql.cpp"
    break;

  case 85: /* as_alias: ID  */
#line 843 "yacc_sql.y"
      {
    (yyval.string) = (yyvsp[0].string);
  }
#line 2596 "yacc_sql.cpp"
    break;

  case 86: /* as_alias: AS ID  */
#line 846 "yacc_sql.y"
          {
    (yyval.string) = (yyvsp[0].string);
  }
#line 2604 "yacc_sql.cpp"
    break;

  case 87: /* expression_list: expression_with_alias  */
#line 853 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2613 "yacc_sql.cpp"
    break;

  case 88: /* expression_list: expression_with_alias COMMA expression_list  */
#line 858 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2626 "yacc_sql.cpp"
    break;

  case 89: /* expression_with_alias: expression as_alias  */
#line 870 "yacc_sql.y"
                       {
      (yyvsp[-1].expression)->set_name((yyvsp[0].string));
      (yyval.expression) = (yyvsp[-1].expression);
    }
#line 2635 "yacc_sql.cpp"
    break;

  case 90: /* expression_with_alias: expression  */
#line 874 "yacc_sql.y"
                 {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2643 "yacc_sql.cpp"
    break;

  case 91: /* expression: expression '+' expression  */
#line 879 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2651 "yacc_sql.cpp"
    break;

  case 92: /* expression: expression '-' expression  */
#line 882 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2659 "yacc_sql.cpp"
    break;

  case 93: /* expression: expression '*' expression  */
#line 885 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2667 "yacc_sql.cpp"
    break;

  case 94: /* expression: expression '/' expression  */
#line 888 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2675 "yacc_sql.cpp"
    break;

  case 95: /* expression: LBRACE expression RBRACE  */
#line 891 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2684 "yacc_sql.cpp"
    break;

  case 96: /* expression: '-' expression  */
#line 895 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2692 "yacc_sql.cpp"
    break;

  case 97: /* expression: value  */
#line 898 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2702 "yacc_sql.cpp"
    break;

  case 98: /* expression: LBRACE expression COMMA expression_list RBRACE  */
#line 905 "yacc_sql.y"
                                                     {
      (yyvsp[-1].expression_list)->emplace((yyvsp[-1].expression_list)->begin(),(yyvsp[-3].expression));
      Value values(*(yyvsp[-1].expression_list));
      (yyval.expression) = new ValueExpr(values);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[-1].expression_list); // 不用delete $2 因为 $2 包含在$4里
    }
#line 2714 "yacc_sql.cpp"
    break;

  case 99: /* expression: rel_attr  */
#line 912 "yacc_sql.y"
              {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2725 "yacc_sql.cpp"
    break;

  case 100: /* expression: '*'  */
#line 918 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2733 "yacc_sql.cpp"
    break;

  case 101: /* expression: aggregate_type LBRACE expression RBRACE  */
#line 923 "yacc_sql.y"
                                             {
       (yyval.expression) = new UnboundAggregateExpr((yyvsp[-3].const_string), (yyvsp[-1].expression));
       (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2742 "yacc_sql.cpp"
    break;

  case 102: /* expression: aggregate_type LBRACE RBRACE  */
#line 928 "yacc_sql.y"
                                   {
       (yyval.expression) = new UnboundAggregateExpr("Failure", nullptr);
       (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2751 "yacc_sql.cpp"
    break;

  case 103: /* expression: aggregate_type LBRACE expression COMMA expression_list RBRACE  */
#line 932 "yacc_sql.y"
                                                                   {
       (yyval.expression) = new UnboundAggregateExpr("Failure", nullptr);
       (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2760 "yacc_sql.cpp"
    break;

  case 104: /* expression: sub_select  */
#line 937 "yacc_sql.y"
                {
      (yyval.expression) = new UnboundSubSelectExpr((yyvsp[0].sub_select));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));

    }
#line 2770 "yacc_sql.cpp"
    break;

  case 105: /* expression: function_type LBRACE expression_list RBRACE  */
#line 943 "yacc_sql.y"
                                                {
      (yyval.expression) = create_function_expression((yyvsp[-3].const_string), (yyvsp[-1].expression_list), sql_string, &(yyloc));
      //if ($5 != nullptr) {
      //  $$->set_name($5);
        //delete $5;
      //}
    }
#line 2782 "yacc_sql.cpp"
    break;

  case 106: /* function_type: LENGTH  */
#line 953 "yacc_sql.y"
           {
      (yyval.const_string) = "length";
    }
#line 2790 "yacc_sql.cpp"
    break;

  case 107: /* function_type: ROUND  */
#line 957 "yacc_sql.y"
          {
      (yyval.const_string) = "round";
    }
#line 2798 "yacc_sql.cpp"
    break;

  case 108: /* function_type: DATE_FORMAT  */
#line 961 "yacc_sql.y"
                {
      (yyval.const_string) = "date_format";
    }
#line 2806 "yacc_sql.cpp"
    break;

  case 109: /* aggregate_type: SUM  */
#line 969 "yacc_sql.y"
       {
      (yyval.const_string) = "sum";
    }
#line 2814 "yacc_sql.cpp"
    break;

  case 110: /* aggregate_type: MAX  */
#line 972 "yacc_sql.y"
       {
      (yyval.const_string) = "max";
    }
#line 2822 "yacc_sql.cpp"
    break;

  case 111: /* aggregate_type: MIN  */
#line 975 "yacc_sql.y"
       {
      (yyval.const_string) = "min";
    }
#line 2830 "yacc_sql.cpp"
    break;

  case 112: /* aggregate_type: AVG  */
#line 978 "yacc_sql.y"
       {
      (yyval.const_string) = "avg";
    }
#line 2838 "yacc_sql.cpp"
    break;

  case 113: /* aggregate_type: COUNT  */
#line 981 "yacc_sql.y"
         {
      (yyval.const_string) = "count";
    }
#line 2846 "yacc_sql.cpp"
    break;

  case 114: /* rel_attr: ID  */
#line 985 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2856 "yacc_sql.cpp"
    break;

  case 115: /* rel_attr: ID DOT ID  */
#line 990 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2868 "yacc_sql.cpp"
    break;

  case 116: /* rel_attr: ID DOT '*'  */
#line 997 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = '*';
      free((yyvsp[-2].string));
    }
#line 2879 "yacc_sql.cpp"
    break;

  case 117: /* relation: ID as_alias  */
#line 1006 "yacc_sql.y"
                {
      (yyval.relation) = new std::pair<std::string,std::string>();
      (*(yyval.relation)) = std::make_pair(std::string((yyvsp[0].string)),std::string((yyvsp[-1].string)));
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 2890 "yacc_sql.cpp"
    break;

  case 118: /* relation: ID  */
#line 1012 "yacc_sql.y"
      {
      (yyval.relation) = new std::pair<std::string,std::string>();
      (*(yyval.relation)) = std::make_pair(std::string((yyvsp[0].string)),std::string((yyvsp[0].string)));
      free((yyvsp[0].string));
      
    }
#line 2901 "yacc_sql.cpp"
    break;

  case 119: /* rel_list: relation  */
#line 1020 "yacc_sql.y"
             {
      (yyval.relation_list) = new std::vector<std::pair<std::string,std::string>>();
      (yyval.relation_list)->push_back(*(yyvsp[0].relation));
      delete((yyvsp[0].relation));
    }
#line 2911 "yacc_sql.cpp"
    break;

  case 120: /* rel_list: relation COMMA rel_list  */
#line 1025 "yacc_sql.y"
                              {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::pair<std::string,std::string>>();
      }

      (yyval.relation_list)->insert((yyval.relation_list)->begin(), *(yyvsp[-2].relation));
      delete((yyvsp[-2].relation));
    }
#line 2926 "yacc_sql.cpp"
    break;

  case 121: /* where: %empty  */
#line 1039 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2934 "yacc_sql.cpp"
    break;

  case 122: /* where: WHERE condition_list  */
#line 1042 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 2942 "yacc_sql.cpp"
    break;

  case 123: /* having_condition: %empty  */
#line 1049 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2950 "yacc_sql.cpp"
    break;

  case 124: /* having_condition: HAVING condition_list  */
#line 1053 "yacc_sql.y"
                          {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 2958 "yacc_sql.cpp"
    break;

  case 125: /* condition_list: %empty  */
#line 1060 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2966 "yacc_sql.cpp"
    break;

  case 126: /* condition_list: condition  */
#line 1063 "yacc_sql.y"
                {
      (yyvsp[0].condition)->conjunction_type = 0;
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->push_back(std::move(*(yyvsp[0].condition)));
    }
#line 2976 "yacc_sql.cpp"
    break;

  case 127: /* condition_list: condition AND condition_list  */
#line 1068 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->conjunction_type = 0;
      (yyval.condition_list)->push_back(std::move(*(yyvsp[-2].condition)));
    }
#line 2986 "yacc_sql.cpp"
    break;

  case 128: /* condition_list: condition OR condition_list  */
#line 1073 "yacc_sql.y"
                                  {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->conjunction_type = 1;
      (yyval.condition_list)->push_back(std::move(*(yyvsp[-2].condition)));
    }
#line 2996 "yacc_sql.cpp"
    break;

  case 129: /* condition: expression comp_op expression  */
#line 1081 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_expression.emplace_back((yyvsp[-2].expression));
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_expression.emplace_back((yyvsp[0].expression));
      (yyval.condition)->comp = (yyvsp[-1].comp);

    }
#line 3010 "yacc_sql.cpp"
    break;

  case 130: /* comp_op: EQ  */
#line 1093 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3016 "yacc_sql.cpp"
    break;

  case 131: /* comp_op: LT  */
#line 1094 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3022 "yacc_sql.cpp"
    break;

  case 132: /* comp_op: GT  */
#line 1095 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3028 "yacc_sql.cpp"
    break;

  case 133: /* comp_op: LE  */
#line 1096 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3034 "yacc_sql.cpp"
    break;

  case 134: /* comp_op: GE  */
#line 1097 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3040 "yacc_sql.cpp"
    break;

  case 135: /* comp_op: NE  */
#line 1098 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3046 "yacc_sql.cpp"
    break;

  case 136: /* comp_op: IS  */
#line 1099 "yacc_sql.y"
         { (yyval.comp) = IS_NULL;}
#line 3052 "yacc_sql.cpp"
    break;

  case 137: /* comp_op: IS NOT  */
#line 1100 "yacc_sql.y"
             { (yyval.comp) = IS_NOT;}
#line 3058 "yacc_sql.cpp"
    break;

  case 138: /* comp_op: LIKE  */
#line 1101 "yacc_sql.y"
           { (yyval.comp) = LIKE_OP;}
#line 3064 "yacc_sql.cpp"
    break;

  case 139: /* comp_op: IN  */
#line 1102 "yacc_sql.y"
         { (yyval.comp) = IN_VALUELIST;}
#line 3070 "yacc_sql.cpp"
    break;

  case 140: /* comp_op: NOT IN  */
#line 1103 "yacc_sql.y"
             { (yyval.comp) = NOT_IN_VALUELIST;}
#line 3076 "yacc_sql.cpp"
    break;

  case 141: /* comp_op: NOT LIKE  */
#line 1104 "yacc_sql.y"
               {(yyval.comp) = NOT_LIKE_OP;}
#line 3082 "yacc_sql.cpp"
    break;

  case 142: /* group_by: %empty  */
#line 1110 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3090 "yacc_sql.cpp"
    break;

  case 143: /* group_by: GROUP BY expression_list  */
#line 1114 "yacc_sql.y"
    {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 3098 "yacc_sql.cpp"
    break;

  case 144: /* order_by_info: %empty  */
#line 1122 "yacc_sql.y"
      {
        (yyval.order_by_info) = nullptr;
      }
#line 3106 "yacc_sql.cpp"
    break;

  case 145: /* order_by_info: ORDER BY order_by_expression_list  */
#line 1126 "yacc_sql.y"
      { 
        (yyval.order_by_info) = (yyvsp[0].order_by_info);
        std::reverse((yyval.order_by_info)->order_by_attrs.begin(),(yyval.order_by_info)->order_by_attrs.end());
        std::reverse((yyval.order_by_info)->order_by_types.begin(),(yyval.order_by_info)->order_by_types.end());
      }
#line 3116 "yacc_sql.cpp"
    break;

  case 146: /* order_by_expression_list: expression order_by_type  */
#line 1135 "yacc_sql.y"
    {
      (yyval.order_by_info) = new OrderByInfo();
      (yyval.order_by_info)->order_by_attrs.emplace_back((yyvsp[-1].expression));
      (yyval.order_by_info)->order_by_types.push_back((yyvsp[0].order_by_type));
    }
#line 3126 "yacc_sql.cpp"
    break;

  case 147: /* order_by_expression_list: expression order_by_type COMMA order_by_expression_list  */
#line 1141 "yacc_sql.y"
    {
      if ((yyvsp[0].order_by_info) != nullptr) {
        (yyval.order_by_info) = (yyvsp[0].order_by_info);
      } else {
        (yyval.order_by_info) = new OrderByInfo();
      }
      (yyval.order_by_info)->order_by_attrs.emplace_back((yyvsp[-3].expression));
      (yyval.order_by_info)->order_by_types.push_back((yyvsp[-2].order_by_type));
    }
#line 3140 "yacc_sql.cpp"
    break;

  case 148: /* order_by_type: %empty  */
#line 1154 "yacc_sql.y"
      {
        (yyval.order_by_type) = ASC_SORT;
      }
#line 3148 "yacc_sql.cpp"
    break;

  case 149: /* order_by_type: ASC  */
#line 1158 "yacc_sql.y"
      { 
        (yyval.order_by_type) = ASC_SORT;
      }
#line 3156 "yacc_sql.cpp"
    break;

  case 150: /* order_by_type: DESC  */
#line 1162 "yacc_sql.y"
      { 
        (yyval.order_by_type) = DESC_SORT;
      }
#line 3164 "yacc_sql.cpp"
    break;

  case 151: /* sub_select: LBRACE select_stmt RBRACE  */
#line 1169 "yacc_sql.y"
  {
    (yyval.sub_select) = new SelectSqlNode;
    (*(yyval.sub_select)) = std::move((yyvsp[-1].sql_node)->selection);
    delete (yyvsp[-1].sql_node);

  }
#line 3175 "yacc_sql.cpp"
    break;

  case 152: /* load_data_stmt: LOAD ID INFILE SSS INTO TABLE ID  */
#line 1183 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3189 "yacc_sql.cpp"
    break;

  case 153: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1196 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3198 "yacc_sql.cpp"
    break;

  case 154: /* set_variable_stmt: SET ID EQ value  */
#line 1204 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3210 "yacc_sql.cpp"
    break;


#line 3214 "yacc_sql.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 1216 "yacc_sql.y"

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}
