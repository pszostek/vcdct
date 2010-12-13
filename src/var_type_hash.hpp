/* C++ code produced by gperf version 3.0.3 */
/* Command-line: gperf -CGD -N IsValidVarType -L C++ -t var_type.gperf  */
/* Computed positions: -k'1,$' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#line 1 "var_type.gperf"

#include "var_type_code.h"
#line 4 "var_type.gperf"
struct VarType {
	const char *name;
	int  VarTypeCode;
};

#define TOTAL_KEYWORDS 17
#define MIN_WORD_LENGTH 3
#define MAX_WORD_LENGTH 9
#define MIN_HASH_VALUE 3
#define MAX_HASH_VALUE 34
/* maximum key range = 32, duplicates = 0 */

class Perfect_Hash
{
private:
  static inline unsigned int hash (const char *str, unsigned int len);
public:
  static const struct VarType *IsValidVarType (const char *str, unsigned int len);
};

inline unsigned int
Perfect_Hash::hash (register const char *str, register unsigned int len)
{
  static const unsigned char asso_values[] =
    {
      35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
      35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
      35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
      35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
      35, 35, 35, 35, 35, 35, 35, 35, 15, 10,
      35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
      35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
      35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
      35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
      35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
       0,  5, 35, 10, 35,  0, 35, 35, 30, 35,
      35, 35, 20, 35,  0,  0,  5, 35, 35,  0,
      35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
      35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
      35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
      35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
      35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
      35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
      35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
      35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
      35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
      35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
      35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
      35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
      35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
      35, 35, 35, 35, 35, 35
    };
  return len + asso_values[(unsigned char)str[len - 1]] + asso_values[(unsigned char)str[0]];
}

static const struct VarType wordlist[] =
  {
#line 25 "var_type.gperf"
    {"wor", VarTypeCode::wor},
#line 23 "var_type.gperf"
    {"wand", VarTypeCode::wand},
#line 10 "var_type.gperf"
    {"integer", VarTypeCode::integer},
#line 17 "var_type.gperf"
    {"tri", VarTypeCode::tri},
#line 24 "var_type.gperf"
    {"wire", VarTypeCode::wire},
#line 19 "var_type.gperf"
    {"trior", VarTypeCode::trior},
#line 18 "var_type.gperf"
    {"triand", VarTypeCode::triand},
#line 13 "var_type.gperf"
    {"reg", VarTypeCode::reg},
#line 16 "var_type.gperf"
    {"time", VarTypeCode::time},
#line 9 "var_type.gperf"
    {"event", VarTypeCode::event},
#line 15 "var_type.gperf"
    {"supply1", VarTypeCode::supply1},
#line 22 "var_type.gperf"
    {"tri1", VarTypeCode::tri1},
#line 20 "var_type.gperf"
    {"trireg", VarTypeCode::trireg},
#line 14 "var_type.gperf"
    {"supply0", VarTypeCode::supply0},
#line 21 "var_type.gperf"
    {"tri0", VarTypeCode::tri0},
#line 11 "var_type.gperf"
    {"parameter", VarTypeCode::parameter},
#line 12 "var_type.gperf"
    {"real", VarTypeCode::real}
  };

static const signed char lookup[] =
  {
    -1, -1, -1,  0,  1, -1, -1,  2,  3,  4,  5,  6, -1,  7,
     8,  9, -1, 10, -1, 11, -1, 12, 13, -1, 14, -1, -1, -1,
    -1, 15, -1, -1, -1, -1, 16
  };

const struct VarType *
Perfect_Hash::IsValidVarType (register const char *str, register unsigned int len)
{
  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register int index = lookup[key];

          if (index >= 0)
            {
              register const char *s = wordlist[index].name;

              if (*str == *s && !strcmp (str + 1, s + 1))
                return &wordlist[index];
            }
        }
    }
  return 0;
}

