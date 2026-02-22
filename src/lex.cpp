#include <cctype>
#include <iostream>
#include <vector>
#include <string_view>

#include "lex.h"
#include "types.h"

const std::string source = "5i == 5i; true; false;";


void read_source()
{
  std::vector<token> t;

  // line: vertical line #
  // col: char offset (reset each newline)
  // pos: 0 based, never resets, from start of file
  u32 line = 1, col = 1;

  std::string_view sv = source;
  usize pos = 0;

  auto advance = [&]() {
    if (pos < sv.length()) {
      if (sv[pos] == '\n') {
        line++;
        col = 1;
      } else {
        col++;
      }
      pos++;
    }
  };

  while (pos < sv.length()) {
    char c = sv[pos];

    // whitespace
    if (std::isspace(c)) {
      advance();
      continue;
    }

    // integer literal (e.g. 5i)
    if (std::isdigit(c)) {
      usize start_pos = pos;
      u32 start_line = line;
      u32 start_col = col;

      while (pos < sv.length() && std::isdigit(sv[pos]))
        advance();

      while (pos < sv.length() && sv[pos] == 'i')
        advance();

      t.push_back({TOKEN_INT_LITERAL, sv.substr(start_pos, pos - start_pos),
          start_line, start_col});

      continue;
    }

    // dup of isdigit for idents (gotta start with letter)
    if (std::isalpha(c)) {
      usize start_pos = pos;
      u32 start_line = line;
      u32 start_col = col;

      while (pos < sv.length() && std::isalnum(sv[pos]))
        advance();

      std::string_view word = sv.substr(start_pos, pos - start_pos);

      if (word == "true" || word == "false")
        t.push_back({TOKEN_BOOL_LITERAL, word, start_line, start_col});
      else
        t.push_back({TOKEN_IDENT, word, start_line, start_col});

      continue;
    }

    u32 start_col = col;
    u32 start_line = line;
    // more manual with advance() but more control
    switch (c) {
    case ';':
      advance();
      t.push_back({TOKEN_SEMICOLON, ";", start_line, start_col});
      break;
    case '+':
      advance();
      t.push_back({TOKEN_PLUS, "+", start_line, start_col});
      break;
    case '(':
      advance();
      t.push_back({TOKEN_LPAREN, "(", start_line, start_col});
      break;
    case ')':
      advance();
      t.push_back({TOKEN_RPAREN, ")", start_line, start_col});
      break;
    case '-':
      advance();
      t.push_back({TOKEN_MINUS, "-", start_line, start_col});
      break;
    case '*':
      advance();
      t.push_back({TOKEN_STAR, "*", start_line, start_col});
      break;
    case '>':
      advance();
      t.push_back({TOKEN_GT, ">", start_line, start_col});
      break;
    case '<':
      advance();
      t.push_back({TOKEN_LT, "<", start_line, start_col});
      break;
    case '&':
      advance(); // first &
      if (pos < sv.length() && sv[pos] == '&') {
        advance(); // second &&
        t.push_back({TOKEN_AND, "&&", start_line, start_col});
      }
      break;
    case '|':
      advance();
      if (pos < sv.length() && sv[pos] == '|') {
        advance();
        t.push_back({TOKEN_OR, "||", start_line, start_col});
      }
      break;
    case '=':
      advance();
      if (pos < sv.length() && sv[pos] == '=') {
        advance();
        t.push_back({TOKEN_EQ, "==", start_line, start_col});
      } else {
        t.push_back({TOKEN_ASSIGN, "=", start_line, start_col});
      }
      break;
    case '/':
      advance();
      t.push_back({TOKEN_SLASH, "/", start_line, start_col});
      break;
    default:
      // advance(); // fixme: wait im i just skipping over invalid char?
      char bad = sv[pos];
      // list initialization very cool (C++11)
      t.push_back({TOKEN_INVALID, std::string{bad}, start_line, start_col});
      break;
    }
  }

  // end of file
  t.push_back({TOKEN_EOF, "EOF", line, col});

  for (const token& tok : t) {
    std::cout << "{\"type\": " << tok.type << ", \"lex\": \"" << tok.lex
              << "\", \"line\": " << tok.line
              << ", \"col\": "
              << tok.column << "}"
              << "\n";
  }
}
