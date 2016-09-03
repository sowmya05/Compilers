/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "new.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.c"

extern char * x;
extern int num;
FILE *fp;
int non = 0;
int type = 0;
struct node{
	char *name;
	struct node* child[100];
	struct node* parent;
	int num;
	int id;
	int type; /*int = 1, float = 2, char = 3*/
}*nodes[20000];
int len=0; int check = 0; int nameflag = 0, numflag = 0;
void recurse(struct node * temp, int);
void create_leaf(char * name1, char * name2){
	//printf("1 %s %s %d\n",name1,name2,len);
	struct node* temp1, *temp2;
	int flag = 0,i,k1,k2;
	if(len>0){
		k1=0;k2=0;
		for(i=0;i<len;i++){
			if(strcmp(nodes[i]->name,name1)==0){
				flag = 1;
				temp1 = nodes[i];
				k1 = i;
				break;
			}
		}
		for(i=0;i<len;i++){
			if(strcmp(nodes[i]->name,name2) == 0){
				if(flag == 1)
					flag = 3;
				else
					flag = 2;
				temp2 = nodes[i];
				k2 = i;
				if(k2 == k1){
					if(check == 1)
						flag = 3;
					else
						flag = 2;
				}
				break;
			}
		}
		if(check ==3)
			flag = 0;
	}
	//printf("%d\n",flag);
	if(len == 0 || flag == 0){
		//printf("1\n");
		temp1 = (struct node*)malloc(sizeof(struct node));
		temp1->name = (char*)malloc(100);
		strcpy(temp1->name,name1);
		non++;
		temp1->id = non;
		temp1->type = type;
		temp2 = (struct node*)malloc(sizeof(struct node));
		temp2->name = (char*)malloc(100);
		strcpy(temp2->name,name2);
		non++;
		temp2->id = non;
		temp2->type = type;
		temp1->parent = NULL;
		temp2->parent = temp1;
		temp1->child[temp1->num] = temp2;
		temp1->num = temp1->num + 1;
		nodes[len] =  temp1;
		len++;
	}
	else if(flag == 1){
		//printf("2\n");
		temp2 = (struct node*)malloc(sizeof(struct node));
		temp2->name = (char*)malloc(100);
		strcpy(temp2->name,name2);
		non++;
		temp2->id = non;
		temp2->type = type;
		if(temp2->type != temp1->type)
			printf("Error: type mismatch at %d", num);
		temp1->child[temp1->num] = temp2;
		temp1->num = temp1->num + 1;
		temp2->parent = temp1;
	}
	else if(flag == 2){
		//printf("3\n");
		temp1 = (struct node*)malloc(sizeof(struct node));
		temp1->name = (char*)malloc(100);
		strcpy(temp1->name,name1);
		non++;
		temp1->id = non;
		temp1->type = type;
		if(temp2->type != temp1->type)
			printf("Error: type mismatch at %d", num);
		temp1->child[temp1->num] = temp2;
		temp2->parent = temp1;
		temp1->num = temp1->num + 1;
		nodes[k2] =  temp1;
	}
	else if(flag == 3){
		//printf("4\n");
		temp1->child[temp1->num] = temp2;
		temp2-> parent = temp1;
		temp1->num = temp1->num + 1;
		for(i=k2;i<len-1;i++)
			nodes[i] = nodes[i+1];
		len--;
		if(temp2->type != temp1->type)
			printf("Error: type mismatch at %d", num);
	}
	if(nameflag == 1 || numflag == 1){
		struct node * temp3;
		temp3 = (struct node*)malloc(sizeof(struct node));
		temp3->name = (char*)malloc(100);
		strcpy(temp3->name,x);
		non++;
		temp3->id = non;
		temp3->type = type;
		temp2->child[temp2->num] = temp3;
		temp2->num = temp2->num + 1;
		temp3->parent = temp2; 
	}
}
void printtree(){
	int i; struct node* temp;
	temp = (struct node*)malloc(sizeof(struct node));
	for(i=0;i<len;i++){
		temp = nodes[i];
		recurse(temp,1);
	}
}
void recurse(struct node * temp, int level){
	int i;
	/*if(temp->parent != NULL)
		printf("Level %d: %s, Root ID: %d, Parent : %s, Parent ID : %d\n",level,temp->name,temp->id,temp->parent->name,temp->parent->id);
	else
		printf("Level %d: %s, Root ID: %d, Parent : NULL, Parent ID: 0\n",level,temp->name,temp->id);*/
	printf("Root ID: %d (%s) -> ",temp->id,temp->name);
	if(temp->num != 0){
		for(i=0;i<temp->num;i++)
			printf("%d, ", temp->child[i]->id);
		printf("\n");
		for(i=0;i<temp->num;i++)
			recurse(temp->child[i],level+1);
	}
	else
		printf("NULL\n");
}

#line 223 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    BOOL = 259,
    TRUE = 260,
    FALSE = 261,
    VOID = 262,
    REAL = 263,
    CHAR = 264,
    FOR = 265,
    WHILE = 266,
    DO = 267,
    IF = 268,
    ELSE = 269,
    SWITCH = 270,
    CASE = 271,
    DEFAULT = 272,
    NUM = 273,
    ID = 274,
    SEMICOLON = 275,
    COM = 276,
    OB = 277,
    closedbrac = 278,
    OCB = 279,
    closedcurly = 280,
    COL = 281,
    PLUS = 282,
    SUB = 283,
    MUL = 284,
    DIV = 285,
    AND = 286,
    OR = 287,
    NEG = 288,
    EQ = 289,
    NEQ = 290,
    GT = 291,
    GE = 292,
    LT = 293,
    LE = 294,
    RETURN = 295,
    BREAK = 296,
    CONTINUE = 297,
    SCAN = 298,
    PRINT = 299,
    ASSIGN = 300
  };
#endif
/* Tokens.  */
#define INT 258
#define BOOL 259
#define TRUE 260
#define FALSE 261
#define VOID 262
#define REAL 263
#define CHAR 264
#define FOR 265
#define WHILE 266
#define DO 267
#define IF 268
#define ELSE 269
#define SWITCH 270
#define CASE 271
#define DEFAULT 272
#define NUM 273
#define ID 274
#define SEMICOLON 275
#define COM 276
#define OB 277
#define closedbrac 278
#define OCB 279
#define closedcurly 280
#define COL 281
#define PLUS 282
#define SUB 283
#define MUL 284
#define DIV 285
#define AND 286
#define OR 287
#define NEG 288
#define EQ 289
#define NEQ 290
#define GT 291
#define GE 292
#define LT 293
#define LE 294
#define RETURN 295
#define BREAK 296
#define CONTINUE 297
#define SCAN 298
#define PRINT 299
#define ASSIGN 300

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 361 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   258

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  110
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  200

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   167,   167,   169,   170,   172,   173,   177,   179,   180,
     181,   183,   187,   189,   190,   192,   193,   195,   196,   197,
     198,   202,   204,   205,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   220,   222,   223,   226,   227,   230,
     231,   234,   235,   236,   237,   238,   239,   240,   243,   244,
     247,   248,   251,   252,   255,   256,   259,   260,   264,   265,
     266,   270,   271,   273,   275,   276,   278,   279,   281,   283,
     284,   286,   288,   289,   291,   292,   296,   297,   298,   300,
     302,   303,   305,   306,   308,   309,   311,   312,   314,   316,
     318,   322,   324,   325,   329,   330,   332,   333,   335,   337,
     338,   340,   341,   345,   349,   353,   354,   356,   357,   359,
     360
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "BOOL", "TRUE", "FALSE", "VOID",
  "REAL", "CHAR", "FOR", "WHILE", "DO", "IF", "ELSE", "SWITCH", "CASE",
  "DEFAULT", "NUM", "ID", "SEMICOLON", "COM", "OB", "closedbrac", "OCB",
  "closedcurly", "COL", "PLUS", "SUB", "MUL", "DIV", "AND", "OR", "NEG",
  "EQ", "NEQ", "GT", "GE", "LT", "LE", "RETURN", "BREAK", "CONTINUE",
  "SCAN", "PRINT", "ASSIGN", "$accept", "Start", "global_dec_list",
  "decl_set", "function_definition", "parameter_list", "parameter",
  "variable_decl", "variable_list", "variable", "variable_dtype",
  "statement_block", "statement_list", "statement", "assignment_statement",
  "logical_expression", "and_expression", "unary_expression",
  "relational_expression", "sum_expression", "sum_operation", "term",
  "mulop", "unary_expr", "factor", "conditional_statement", "if_statement",
  "else_cond", "statements", "switch_statement", "switch_cases",
  "switch_case", "switch_labels", "switch_label", "loop_statement",
  "for_loop", "init_condition", "init_list", "term_condition",
  "term_condition_list", "iterator", "while_loop", "do_while_loop",
  "return_statement", "return_value", "function_call",
  "assign_function_call", "argument_list", "arg_list", "argument",
  "print_statement", "read_statement", "DEL", "CCB", "CB", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300
};
# endif

#define YYPACT_NINF -144

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-144)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      17,  -144,  -144,  -144,  -144,    14,    17,  -144,  -144,  -144,
       0,  -144,  -144,    -4,    30,  -144,  -144,    17,   100,  -144,
    -144,     8,  -144,    56,  -144,    29,  -144,  -144,   100,  -144,
    -144,   152,    89,    25,  -144,  -144,   213,   -13,   152,  -144,
    -144,    20,  -144,  -144,    17,  -144,    35,  -144,     7,   100,
    -144,  -144,   102,  -144,  -144,   152,   152,   152,   152,   152,
     152,   152,   152,  -144,  -144,   202,  -144,   102,  -144,    22,
    -144,    54,    54,    54,    54,    54,    54,   -13,  -144,    51,
      73,    35,    75,    85,     2,   102,    89,    89,   106,   102,
    -144,   107,   143,  -144,  -144,  -144,  -144,  -144,  -144,  -144,
    -144,  -144,  -144,  -144,  -144,  -144,  -144,     9,   108,   102,
     104,   102,   102,    87,   147,  -144,    89,  -144,  -144,    89,
      89,    83,  -144,  -144,  -144,  -144,  -144,    91,    89,    22,
     112,    22,    22,  -144,  -144,    22,   116,   118,  -144,  -144,
    -144,   201,   102,   102,   185,   102,   185,   117,    89,    87,
    -144,    87,   120,   124,   128,    89,  -144,  -144,  -144,    22,
     136,    96,  -144,  -144,    22,    87,   108,  -144,   102,  -144,
     108,    89,   185,  -144,   139,   133,    27,  -144,    59,  -144,
      89,    22,  -144,  -144,  -144,    22,  -144,  -144,   135,  -144,
    -144,  -144,  -144,  -144,  -144,    89,   185,  -144,  -144,  -144
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    17,    18,    20,    19,     0,     2,     4,     5,     6,
       0,     1,     3,    16,     0,    14,    15,    10,     0,   106,
     105,     0,    12,     0,     9,     0,    60,    58,     0,    54,
      55,     0,     0,    36,    38,    40,    47,    49,     0,    53,
      57,    16,    13,   110,     0,   109,     0,    11,     0,     0,
      39,    34,     0,    50,    51,     0,     0,     0,     0,     0,
       0,     0,     0,    56,     8,     0,     7,     0,    59,     0,
      37,    43,    46,    41,    44,    42,    45,    48,    52,     0,
       0,     0,     0,     0,     0,    93,     0,     0,     0,     0,
      33,     0,     0,    23,    24,    25,    61,    62,    26,    76,
      77,    78,    29,    30,    95,    31,    32,     0,    81,     0,
       0,     0,     0,     0,     0,    92,     0,    27,    28,     0,
       0,    16,   108,   107,    22,    21,    35,     0,     0,     0,
       0,     0,     0,   102,   101,     0,   100,    58,    91,   104,
     103,     0,     0,    85,     0,     0,     0,     0,     0,     0,
      98,     0,    58,    83,    87,     0,    66,    67,    89,     0,
      65,     0,    94,    99,     0,     0,    81,    80,    85,    84,
      81,     0,     0,    63,     0,     0,     0,    69,     0,    72,
       0,     0,    82,    86,    88,     0,    90,    64,     0,    75,
      70,    68,    71,    73,    97,     0,     0,    74,    96,    79
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -144,  -144,  -144,   161,  -144,  -144,   129,    98,  -144,   151,
       5,   -39,  -144,   -56,    -6,   -16,   111,   -51,   144,   198,
    -144,   130,   -31,   -25,  -144,  -144,  -144,  -144,  -143,  -144,
    -144,     3,  -144,    12,  -144,  -144,   -77,  -144,    24,  -144,
    -144,  -144,  -144,  -144,  -144,  -144,  -144,   -85,  -144,  -144,
    -144,  -144,   -32,    23,   -21
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,     6,     7,     8,    23,    24,    90,    14,    15,
      91,   156,    92,   157,    94,    32,    33,    34,    35,    36,
      61,    37,    38,    39,    40,    95,    96,   173,   158,    97,
     176,   177,   178,   179,    98,    99,   128,   167,   155,   169,
     185,   100,   101,   102,   116,   103,   104,   135,   150,   136,
     105,   106,    22,   125,    68
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      51,    70,    46,   160,    16,    10,    62,    66,    43,    93,
      43,    10,    48,    63,    11,    16,    29,    30,    17,    13,
       1,     2,    25,    43,   113,     3,     4,    41,   122,   187,
      45,    19,    45,    69,   115,   192,   124,    78,   120,    67,
      52,    18,   110,   174,   175,    45,    62,   114,    47,    25,
      20,    21,   123,   199,   117,   118,    52,    43,   129,    65,
     131,   132,     1,     2,   163,    18,   164,     3,     4,    79,
      80,    81,    82,   108,    83,   174,   175,    44,    84,    45,
     181,    53,    54,    65,   138,    16,   126,   139,   140,   182,
      19,   153,   154,   184,   159,   109,   143,   111,     9,    85,
      86,    87,    88,    89,     9,   133,   134,   112,   144,    20,
     146,   147,   174,   175,   148,   130,   162,   154,    26,    27,
      26,    27,    28,   170,    49,   119,   121,   127,   141,    29,
      30,    29,    30,    31,   145,    31,   142,   149,   171,   186,
     151,   161,   165,   180,   122,   166,     1,     2,   194,   168,
     172,     3,     4,    79,    80,    81,    82,   188,    83,   189,
     195,   197,    84,   198,   196,    26,   137,    12,   123,    28,
      26,    27,    42,    64,    49,    50,    29,    30,   107,   190,
      31,    29,    30,    85,    86,    87,    88,    89,     1,     2,
     193,    77,   183,     3,     4,    79,    80,    81,    82,   191,
      83,     0,     0,     0,    84,     1,     2,     0,     0,    65,
       3,     4,    79,    80,    81,    82,     0,    83,     0,    26,
     152,    84,     0,    28,     0,    85,    86,    87,    88,    89,
      29,    30,     0,     0,    31,     0,     0,     0,     0,     0,
      53,    54,    85,    86,    87,    88,    89,    55,    56,    57,
      58,    59,    60,    71,    72,    73,    74,    75,    76
};

static const yytype_int16 yycheck[] =
{
      32,    52,    23,   146,    10,     0,    37,    46,     1,    65,
       1,     6,    28,    38,     0,    21,    29,    30,    22,    19,
       3,     4,    17,     1,    22,     8,     9,    19,     1,   172,
      23,     1,    23,    49,    85,   178,    92,    62,    89,    32,
      31,    45,    81,    16,    17,    23,    77,    45,    19,    44,
      20,    21,    25,   196,    86,    87,    31,     1,   109,    24,
     111,   112,     3,     4,   149,    45,   151,     8,     9,    10,
      11,    12,    13,    22,    15,    16,    17,    21,    19,    23,
     165,    27,    28,    24,   116,    91,   107,   119,   120,   166,
       1,   142,   143,   170,   145,    22,   128,    22,     0,    40,
      41,    42,    43,    44,     6,    18,    19,    22,   129,    20,
     131,   132,    16,    17,   135,    11,   148,   168,    18,    19,
      18,    19,    22,   155,    22,    19,    19,    19,    45,    29,
      30,    29,    30,    33,    22,    33,    45,    21,   159,   171,
      22,    24,    22,   164,     1,    21,     3,     4,   180,    21,
      14,     8,     9,    10,    11,    12,    13,    18,    15,    26,
     181,    26,    19,   195,   185,    18,    19,     6,    25,    22,
      18,    19,    21,    44,    22,    31,    29,    30,    67,   176,
      33,    29,    30,    40,    41,    42,    43,    44,     3,     4,
     178,    61,   168,     8,     9,    10,    11,    12,    13,   176,
      15,    -1,    -1,    -1,    19,     3,     4,    -1,    -1,    24,
       8,     9,    10,    11,    12,    13,    -1,    15,    -1,    18,
      19,    19,    -1,    22,    -1,    40,    41,    42,    43,    44,
      29,    30,    -1,    -1,    33,    -1,    -1,    -1,    -1,    -1,
      27,    28,    40,    41,    42,    43,    44,    34,    35,    36,
      37,    38,    39,    55,    56,    57,    58,    59,    60
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     8,     9,    47,    48,    49,    50,    53,
      56,     0,    49,    19,    54,    55,    60,    22,    45,     1,
      20,    21,    98,    51,    52,    56,    18,    19,    22,    29,
      30,    33,    61,    62,    63,    64,    65,    67,    68,    69,
      70,    19,    55,     1,    21,    23,   100,    19,    61,    22,
      64,    98,    31,    27,    28,    34,    35,    36,    37,    38,
      39,    66,    68,    69,    52,    24,    57,    32,   100,    61,
      63,    65,    65,    65,    65,    65,    65,    67,    69,    10,
      11,    12,    13,    15,    19,    40,    41,    42,    43,    44,
      53,    56,    58,    59,    60,    71,    72,    75,    80,    81,
      87,    88,    89,    91,    92,    96,    97,    62,    22,    22,
      57,    22,    22,    22,    45,    63,    90,    98,    98,    19,
      63,    19,     1,    25,    59,    99,   100,    19,    82,    63,
      11,    63,    63,    18,    19,    93,    95,    19,    98,    98,
      98,    45,    45,    98,   100,    22,   100,   100,   100,    21,
      94,    22,    19,    63,    63,    84,    57,    59,    74,    63,
      74,    24,    98,    93,    93,    22,    21,    83,    21,    85,
      98,   100,    14,    73,    16,    17,    76,    77,    78,    79,
     100,    93,    82,    84,    82,    86,    98,    74,    18,    26,
      77,    99,    74,    79,    98,   100,   100,    26,    98,    74
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    48,    48,    49,    49,    50,    51,    51,
      51,    52,    53,    54,    54,    55,    55,    56,    56,    56,
      56,    57,    58,    58,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    60,    61,    61,    62,    62,    63,
      63,    64,    64,    64,    64,    64,    64,    64,    65,    65,
      66,    66,    67,    67,    68,    68,    69,    69,    70,    70,
      70,    71,    71,    72,    73,    73,    74,    74,    75,    76,
      76,    77,    78,    78,    79,    79,    80,    80,    80,    81,
      82,    82,    83,    83,    84,    84,    85,    85,    86,    87,
      88,    89,    90,    90,    91,    91,    92,    92,    93,    94,
      94,    95,    95,    96,    97,    98,    98,    99,    99,   100,
     100
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     6,     3,     1,
       0,     2,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     2,     1,     1,     1,     1,     2,     2,     1,
       1,     1,     1,     1,     4,     5,     1,     3,     1,     2,
       1,     3,     3,     3,     3,     3,     3,     1,     3,     1,
       1,     1,     3,     1,     1,     1,     2,     1,     1,     3,
       1,     1,     1,     6,     2,     0,     1,     1,     7,     1,
       2,     2,     1,     2,     3,     2,     1,     1,     1,     9,
       4,     0,     2,     0,     2,     0,     2,     0,     1,     5,
       7,     3,     1,     0,     5,     1,     8,     7,     2,     2,
       0,     1,     1,     3,     3,     1,     1,     1,     1,     1,
       1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
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
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 167 "new.y" /* yacc.c:1646  */
    {printtree();}
#line 1602 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 169 "new.y" /* yacc.c:1646  */
    {printf("prod 2\n"); create_leaf("global_dec_list", "global_dec_list"); create_leaf("global_dec_list","decl_set"); }
#line 1608 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 170 "new.y" /* yacc.c:1646  */
    {printf("prod 3\n"); create_leaf("global_dec_list","decl_set"); }
#line 1614 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 172 "new.y" /* yacc.c:1646  */
    {printf("prod 4\n"); create_leaf("decl_set","function_definition");}
#line 1620 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 173 "new.y" /* yacc.c:1646  */
    {printf("prod 5\n"); create_leaf("decl_set", "variable_decl");}
#line 1626 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 177 "new.y" /* yacc.c:1646  */
    {printf("prod 6\n"); create_leaf("function_definition","variable_dtype"); nameflag = 1; create_leaf("function_definition","ID"); nameflag = 0; create_leaf("function_definition","OB"); create_leaf("function_definition","parameter_list"); create_leaf("function_definition","CB"); create_leaf("function_definition","statement_block");}
#line 1632 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 179 "new.y" /* yacc.c:1646  */
    {printf("prod 7\n"); create_leaf("parameter_list","parameter_list"); create_leaf("parameter_list","COM"); create_leaf("parameter_list","parameter");}
#line 1638 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 180 "new.y" /* yacc.c:1646  */
    {printf("prod 8\n"); create_leaf("parameter_list","parameter");}
#line 1644 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 181 "new.y" /* yacc.c:1646  */
    {printf("prod 9\n");}
#line 1650 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 183 "new.y" /* yacc.c:1646  */
    {printf("prod 10\n"); create_leaf("parameter","variable_dtype"); nameflag = 1; create_leaf("parameter","ID"); nameflag = 0;}
#line 1656 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 187 "new.y" /* yacc.c:1646  */
    {printf("prod 11\n"); create_leaf("variable_decl","variable_dtype"); create_leaf("variable_decl","variable_list"); create_leaf("variable_decl","DEL");}
#line 1662 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 189 "new.y" /* yacc.c:1646  */
    {printf("prod 12\n"); create_leaf("variable_list","variable_list"); create_leaf("variable_list","COM"); create_leaf("variable_list","variable");}
#line 1668 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 190 "new.y" /* yacc.c:1646  */
    {printf("prod 13\n"); create_leaf("variable_list","variable");}
#line 1674 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 192 "new.y" /* yacc.c:1646  */
    {printf("prod 14\n"); create_leaf("variable","assignment_statement");}
#line 1680 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 193 "new.y" /* yacc.c:1646  */
    {printf("prod 15\n"); check = 3; nameflag = 1; create_leaf("variable","ID"); nameflag = 0; check = 0;}
#line 1686 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 195 "new.y" /* yacc.c:1646  */
    {printf("prod 16\n"); check = 3; type = 1; create_leaf("variable_dtype","INT"); check = 0;}
#line 1692 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 196 "new.y" /* yacc.c:1646  */
    {printf("prod 17\n"); check = 3; type = 4; create_leaf("variable_dtype","BOOL"); check = 0;}
#line 1698 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 197 "new.y" /* yacc.c:1646  */
    {printf("prod 17\n"); check = 3; type = 3; create_leaf("variable_dtype","CHAR"); check = 0;}
#line 1704 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 198 "new.y" /* yacc.c:1646  */
    {printf("prod 17\n"); check = 3; type = 2; create_leaf("variable_dtype","REAL"); check = 0;}
#line 1710 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 202 "new.y" /* yacc.c:1646  */
    {printf("prod 18\n"); create_leaf("statement_block","OCB"); create_leaf("statement_block","statement_list"); create_leaf("statement_block","CCB");}
#line 1716 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 204 "new.y" /* yacc.c:1646  */
    {printf("prod 19\n"); create_leaf("statement_list","statement_list"); create_leaf("statement_list","statement");}
#line 1722 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 205 "new.y" /* yacc.c:1646  */
    {printf("prod 20\n"); create_leaf("statement_list","statement");}
#line 1728 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 207 "new.y" /* yacc.c:1646  */
    {printf("prod 21\n"); create_leaf("statement","assignment_statement");}
#line 1734 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 208 "new.y" /* yacc.c:1646  */
    {printf("prod 22\n"); create_leaf("statement","conditional_statement");}
#line 1740 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 209 "new.y" /* yacc.c:1646  */
    {printf("prod 23\n"); create_leaf("statement","loop_statement");}
#line 1746 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 210 "new.y" /* yacc.c:1646  */
    {printf("prod 24\n"); create_leaf("statement","BREAK");create_leaf("statement","DEL");}
#line 1752 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 211 "new.y" /* yacc.c:1646  */
    {printf("prod 25\n"); create_leaf("statement","CONTINUE");create_leaf("statement","DEL");}
#line 1758 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 212 "new.y" /* yacc.c:1646  */
    {printf("prod 26\n"); create_leaf("statement","return_statement");}
#line 1764 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 213 "new.y" /* yacc.c:1646  */
    {printf("prod 27\n"); create_leaf("statement","function_call");}
#line 1770 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 214 "new.y" /* yacc.c:1646  */
    {printf("prod 28\n"); create_leaf("statement","print_statement");}
#line 1776 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 215 "new.y" /* yacc.c:1646  */
    {printf("prod 29\n"); create_leaf("statement","read_statement");}
#line 1782 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 216 "new.y" /* yacc.c:1646  */
    {printf("prod 30\n"); create_leaf("statement","variable_decl");}
#line 1788 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 220 "new.y" /* yacc.c:1646  */
    {printf("prod 31\n"); nameflag = 1; create_leaf("assignment_statement","ID"); nameflag = 0; create_leaf("assignment_statement","ASSIGN"); create_leaf("assignment_statement","logical_expression"); create_leaf("assignment_statement","DEL");}
#line 1794 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 222 "new.y" /* yacc.c:1646  */
    {printf("prod 32\n"); create_leaf("logical_expression","OB"); check = 1; create_leaf("logical_expression","logical_expression"); check = 0; create_leaf("logical_expression","OR"); create_leaf("logical_expression","and_expression"); create_leaf("logical_expression","CB");}
#line 1800 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 223 "new.y" /* yacc.c:1646  */
    {printf("prod 33\n"); create_leaf("logical_expression","and_expression");}
#line 1806 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 226 "new.y" /* yacc.c:1646  */
    {printf("prod 34\n"); create_leaf("and_expression","and_expression"); create_leaf("and_expression","AND"); create_leaf("and_expression","unary_expression");}
#line 1812 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 227 "new.y" /* yacc.c:1646  */
    {printf("prod 35\n"); create_leaf("and_expression","unary_expression");}
#line 1818 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 230 "new.y" /* yacc.c:1646  */
    {printf("prod 36\n"); create_leaf("unary_expression", "NEG"); check = 1; create_leaf("unary_expression", "relational_expression"); check = 0;}
#line 1824 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 231 "new.y" /* yacc.c:1646  */
    {printf("prod 37\n"); create_leaf("unary_expression", "relational_expression");}
#line 1830 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 234 "new.y" /* yacc.c:1646  */
    {printf("prod 38\n"); create_leaf("relational_expression","sum_expression"); create_leaf("relational_expression","GT"); create_leaf("relational_expression","sum_expression");}
#line 1836 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 235 "new.y" /* yacc.c:1646  */
    {printf("prod 38\n"); create_leaf("relational_expression","sum_expression"); create_leaf("relational_expression","LT"); create_leaf("relational_expression","sum_expression");}
#line 1842 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 236 "new.y" /* yacc.c:1646  */
    {printf("prod 38\n"); create_leaf("relational_expression","sum_expression"); create_leaf("relational_expression","EQ"); create_leaf("relational_expression","sum_expression");}
#line 1848 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 237 "new.y" /* yacc.c:1646  */
    {printf("prod 38\n"); create_leaf("relational_expression","sum_expression"); create_leaf("relational_expression","GE"); create_leaf("relational_expression","sum_expression");}
#line 1854 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 238 "new.y" /* yacc.c:1646  */
    {printf("prod 38\n"); create_leaf("relational_expression","sum_expression"); create_leaf("relational_expression","LE"); create_leaf("relational_expression","sum_expression");}
#line 1860 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 239 "new.y" /* yacc.c:1646  */
    {printf("prod 38\n"); create_leaf("relational_expression","sum_expression"); create_leaf("relational_expression","NEQ"); create_leaf("relational_expression","sum_expression");}
#line 1866 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 240 "new.y" /* yacc.c:1646  */
    {printf("prod 38\n"); create_leaf("relational_expression","sum_expression");}
#line 1872 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 243 "new.y" /* yacc.c:1646  */
    {printf("prod 39\n"); create_leaf("sum_expression","sum_expression"); create_leaf("sum_expression","sum_operation"); create_leaf("sum_expression","term");}
#line 1878 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 244 "new.y" /* yacc.c:1646  */
    {printf("prod 40\n"); create_leaf("sum_expression","term");}
#line 1884 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 247 "new.y" /* yacc.c:1646  */
    {printf("prod 41\n"); create_leaf("sum_operation","PLUS");}
#line 1890 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 248 "new.y" /* yacc.c:1646  */
    {printf("prod 42\n"); create_leaf("sum_operation","SUB");}
#line 1896 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 251 "new.y" /* yacc.c:1646  */
    {printf("prod 43\n"); create_leaf("term","term"); create_leaf("term","mulop"); create_leaf("term","unary_expr");}
#line 1902 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 252 "new.y" /* yacc.c:1646  */
    {printf("prod 44\n"); create_leaf("term","unary_expr");}
#line 1908 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 255 "new.y" /* yacc.c:1646  */
    {printf("prod 45\n"); create_leaf("mulop","MUL");}
#line 1914 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 256 "new.y" /* yacc.c:1646  */
    {printf("prod 46\n"); create_leaf("mulop","DIV");}
#line 1920 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 259 "new.y" /* yacc.c:1646  */
    {printf("prod 47\n"); create_leaf("unary_expr","mulop"); create_leaf("unary_expr","unary_expr");}
#line 1926 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 260 "new.y" /* yacc.c:1646  */
    {printf("prod 48\n"); create_leaf("unary_expr","factor");}
#line 1932 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 264 "new.y" /* yacc.c:1646  */
    {printf("prod 49\n"); check = 3; nameflag = 1; create_leaf("factor","ID"); nameflag = 0; check = 0;}
#line 1938 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 265 "new.y" /* yacc.c:1646  */
    {printf("prod 50\n"); create_leaf("factor","OB"); create_leaf("factor","logical_expression"); create_leaf("factor","CB");}
#line 1944 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 266 "new.y" /* yacc.c:1646  */
    {printf("prod 51\n"); numflag = 1; create_leaf("factor","NUM"); numflag = 0;}
#line 1950 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 270 "new.y" /* yacc.c:1646  */
    {printf("prod 58\n"); create_leaf("conditional_statement","if_statement");}
#line 1956 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 271 "new.y" /* yacc.c:1646  */
    {printf("prod 59\n"); create_leaf("conditional_statement","switch_statement");}
#line 1962 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 273 "new.y" /* yacc.c:1646  */
    {printf("prod 60\n"); create_leaf("if_statement","IF"); create_leaf("if_statement","OB"); create_leaf("if_statement","unary_expression"); create_leaf("if_statement","CB"); create_leaf("if_statement","statements"); create_leaf("if_statement","else_cond");}
#line 1968 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 275 "new.y" /* yacc.c:1646  */
    {printf("prod 61\n"); create_leaf("else_cond","ELSE"); create_leaf("else_cond","statements");}
#line 1974 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 276 "new.y" /* yacc.c:1646  */
    {printf("prod 62\n");}
#line 1980 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 278 "new.y" /* yacc.c:1646  */
    {printf("prod 63\n"); create_leaf("statements","statement_block");}
#line 1986 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 279 "new.y" /* yacc.c:1646  */
    {printf("prod 64\n"); create_leaf("statements","statement");}
#line 1992 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 281 "new.y" /* yacc.c:1646  */
    {printf("prod 65\n"); create_leaf("switch_statement","SWITCH");}
#line 1998 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 283 "new.y" /* yacc.c:1646  */
    {printf("prod 66\n"); create_leaf("switch_cases","switch_case");}
#line 2004 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 284 "new.y" /* yacc.c:1646  */
    {printf("prod 67\n"); create_leaf("switch_cases","switch_cases"); create_leaf("switch_cases","switch_case");}
#line 2010 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 286 "new.y" /* yacc.c:1646  */
    {printf("prod 68\n"); create_leaf("switch_case","switch_labels"); create_leaf("switch_case","statements");}
#line 2016 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 288 "new.y" /* yacc.c:1646  */
    {printf("prod 69\n"); create_leaf("switch_labels","switch_label");}
#line 2022 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 289 "new.y" /* yacc.c:1646  */
    {printf("prod 70\n"); create_leaf("switch_labels","switch_labels"); create_leaf("switch_labels","switch_label");}
#line 2028 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 291 "new.y" /* yacc.c:1646  */
    {printf("prod 71\n"); create_leaf("switch_label","CASE"); numflag = 1; create_leaf("switch_label","NUM"); numflag = 0; create_leaf("switch_label","COL");}
#line 2034 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 292 "new.y" /* yacc.c:1646  */
    {printf("prod 72\n"); create_leaf("switch_label","DEFAULT"); create_leaf("switch_label","COL");}
#line 2040 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 296 "new.y" /* yacc.c:1646  */
    {printf("prod 73\n"); create_leaf("loop_statement","for_loop");}
#line 2046 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 297 "new.y" /* yacc.c:1646  */
    {printf("prod 74\n"); create_leaf("loop_statement","while_loop");}
#line 2052 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 298 "new.y" /* yacc.c:1646  */
    {printf("prod 75\n"); create_leaf("loop_statement","do_while_loop");}
#line 2058 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 300 "new.y" /* yacc.c:1646  */
    {printf("prod 76\n"); create_leaf("for_loop","FOR"); create_leaf("for_loop","OB"); create_leaf("for_loop","init_condition"); create_leaf("for_loop","DEL"); create_leaf("for_loop","term_condition"); create_leaf("for_loop","DEL"); create_leaf("for_loop","iterator"); create_leaf("for_loop","CB"); create_leaf("for_loop","statements");}
#line 2064 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 302 "new.y" /* yacc.c:1646  */
    {printf("prod 77\n"); nameflag = 1; create_leaf("init_condition","ID"); nameflag = 0; create_leaf("init_condition","ASSIGN"); create_leaf("init_conditon","unary_expression"); create_leaf("init_condition","init_list");}
#line 2070 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 303 "new.y" /* yacc.c:1646  */
    {printf("prod 78\n");}
#line 2076 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 305 "new.y" /* yacc.c:1646  */
    {printf("prod 79\n"); create_leaf("init_list","COM"); create_leaf("init_condition","init_condition");}
#line 2082 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 306 "new.y" /* yacc.c:1646  */
    {printf("prod 80\n");}
#line 2088 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 308 "new.y" /* yacc.c:1646  */
    {printf("prod 81\n"); create_leaf("term_condition","unary_expression"); create_leaf("term_condition","term_condition_list");}
#line 2094 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 309 "new.y" /* yacc.c:1646  */
    {printf("prod 82\n");}
#line 2100 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 311 "new.y" /* yacc.c:1646  */
    {printf("prod 83\n"); create_leaf("term_condition_list","COM"); create_leaf("term_condition_list","term_condition");}
#line 2106 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 312 "new.y" /* yacc.c:1646  */
    {printf("prod 84\n");}
#line 2112 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 314 "new.y" /* yacc.c:1646  */
    {printf("prod 85\n"); create_leaf("iterator","init_condition");}
#line 2118 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 316 "new.y" /* yacc.c:1646  */
    {printf("prod 86\n"); create_leaf("while_loop","WHILE"); create_leaf("while_loop","OB"); create_leaf("while_loop","unary_expression"); create_leaf("while_loop","CB"); create_leaf("while_loop","statements");}
#line 2124 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 318 "new.y" /* yacc.c:1646  */
    {printf("prod 87\n"); create_leaf("do_while_loop","DO"); create_leaf("do_while_loop","statement_block"); create_leaf("do_while_loop","WHILE"); create_leaf("do_while_loop","OB"); create_leaf("do_while_loop","unary_expression"); create_leaf("do_while_loop","CB"); create_leaf("do_while_loop","DEL");}
#line 2130 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 322 "new.y" /* yacc.c:1646  */
    {printf("prod 88\n"); create_leaf("return_statement","RETURN"); create_leaf("return_statement","return_value"); create_leaf("return_statement","DEL");}
#line 2136 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 324 "new.y" /* yacc.c:1646  */
    {printf("prod 89\n"); create_leaf("return_value","unary_expression");}
#line 2142 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 325 "new.y" /* yacc.c:1646  */
    {printf("prod 90\n");}
#line 2148 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 329 "new.y" /* yacc.c:1646  */
    {printf("prod 91\n"); nameflag = 1; create_leaf("function_call","ID"); nameflag = 0; create_leaf("function_call","OB"); create_leaf("function_call","argument_list"); create_leaf("function_call","CB"); create_leaf("function_call","DEL");}
#line 2154 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 330 "new.y" /* yacc.c:1646  */
    {printf("prod 92\n"); create_leaf("function_call","assign_function_call");}
#line 2160 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 332 "new.y" /* yacc.c:1646  */
    {printf("prod 93\n"); create_leaf("assign_function_call","variable_dtype"); nameflag = 1; create_leaf("assign_function_call","ID"); nameflag = 0; create_leaf("assign_function_call","ASSIGN"); nameflag = 1; create_leaf("assign_function_call","ID"); nameflag = 0; create_leaf("assign_function_call","OB"); create_leaf("assign_function_call","argument_list"); create_leaf("assign_function_call","CB"); create_leaf("assign_function_call","DEL");}
#line 2166 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 333 "new.y" /* yacc.c:1646  */
    {printf("prod 94\n"); nameflag = 1; create_leaf("assign_function_call","ID"); nameflag = 0;  create_leaf("assign_function_call","ASSIGN"); nameflag = 1; create_leaf("assign_function_call","ID"); nameflag = 0; create_leaf("assign_function_call","OB"); create_leaf("assign_function_call","argument_list"); create_leaf("assign_function_call","CB"); create_leaf("assign_function_call","DEL");}
#line 2172 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 335 "new.y" /* yacc.c:1646  */
    {printf("prod 95\n"); create_leaf("argument_list","argument"); create_leaf("argument_list","arg_list");}
#line 2178 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 337 "new.y" /* yacc.c:1646  */
    {printf("prod 96\n"); create_leaf("arg_list","COM"); create_leaf("arg_list","argument_list");}
#line 2184 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 340 "new.y" /* yacc.c:1646  */
    {printf("prod 98\n"); check = 3; nameflag = 1; create_leaf("argument","ID"); nameflag = 0; check = 0;}
#line 2190 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 341 "new.y" /* yacc.c:1646  */
    {printf("prod 99\n"); check = 3; numflag = 1; create_leaf("argument","NUM"); numflag = 0; check = 0;}
#line 2196 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 345 "new.y" /* yacc.c:1646  */
    {printf("prod 100\n"); create_leaf("print_statement","PRINT"); create_leaf("print_statement","unary_expression"); create_leaf("print_statement","DEL");}
#line 2202 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 349 "new.y" /* yacc.c:1646  */
    {printf("prod 101\n"); create_leaf("read_statement","SCAN"); nameflag = 1; create_leaf("read_statement","ID"); nameflag = 0; create_leaf("read_statement","DEL");}
#line 2208 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 354 "new.y" /* yacc.c:1646  */
    {printf("1\n"); fp = fopen("error.txt", "a+"); fprintf(fp,"Warning: Missing semicolon in line %d\n", num); fclose(fp);}
#line 2214 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 357 "new.y" /* yacc.c:1646  */
    {printf("2\n"); fp = fopen("error.txt", "a+"); fprintf(fp,"Warning: Missing } in line %d\n", num); fclose(fp);}
#line 2220 "y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 360 "new.y" /* yacc.c:1646  */
    {printf("3\n"); fp = fopen("error.txt", "a+"); fprintf(fp,"Warning: Missing ) in line %d\n", num); fclose(fp);}
#line 2226 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2230 "y.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



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
                      yytoken, &yylval);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 363 "new.y" /* yacc.c:1906  */

#include"lex.yy.c"
#include<ctype.h>
int count=0;

int main(int argc, char *argv[])
{
	fp = fopen("error.txt","w");
	fclose(fp);
	yyin = fopen(argv[1], "r");
	
   if(!yyparse())
		printf("\nParsing complete\n");
	else
		printf("\nParsing failed\n");
	
	fclose(yyin);
    return 0;
}
         
yyerror(char *s) {
	//fp = fopen("error.txt", "a+"); fprintf(fp,"%d : %s %s\n", num + 1, s, yytext ); fclose(fp);
}
