#include <cctype>
#include <iostream>
#include <vector>
#include <string_view>

#include "lex.h"
#include "types.h"

const std::string source = "5i + 6i;";

void read_source()
{
  std::vector<token> t;
  u32 line = 1, col = 0;

  std::string_view sv = source;
  
  for (usize pos = 0; pos < sv.length(); ++pos) {
    char c = sv[pos];
    col++;

    if (std::isspace(c)) {
      if (c == '\n') {
        line++;
        col = 0;
      }
      continue;
    }

    if (std::isdigit(c)) {
      // todo: int 
    }

    switch (c) {
    case ';': t.push_back({TOKEN_SEMICOLON, ";", line, col}); break;
    case '+': t.push_back({TOKEN_PLUS, "+", line, col}); break;
    case '(': t.push_back({TOKEN_LPAREN, "(", line, col}); break;
    case ')': t.push_back({TOKEN_RPAREN, ")", line, col}); break;
    case '-': t.push_back({TOKEN_MINUS, "-", line, col}); break;
    case '*': t.push_back({TOKEN_STAR, "+", line, col}); break;
    case '>': t.push_back({TOKEN_GT, ">", line, col}); break;
    case '<': t.push_back({TOKEN_LT, "<", line, col}); break;
    case '=':
      // todo: look forward for another equal
      //TOKEN_EQ
      t.push_back({TOKEN_ASSIGN, "=", line, col});
      break;
    }
  }

  for (const token& tok : t) {
    std::cout << "{\"type\": " << tok.type << ", \"lex\": \"" << tok.lex << "\", \"line\": " << tok.line << ", \"col\": " << tok.column << "}" << "\n";
  }
}
