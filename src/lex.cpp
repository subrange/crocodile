#include <cctype>
#include <iostream>
#include <vector>

#include "lex.h"
#include "types.h"

const std::string source = "5i + 6i;";

//struct token {
//  token_type type;
//  std::string lex;
//  u32 line;
//  u32 column;
//};

void read_source()
{
  std::vector<token> t;
  u32 line = 0, col = 0;
  for (usize pos = 0; pos < source.length(); ++pos) {
    char c = source[pos];
    if (std::isspace(c)) continue;

    if (c == '\n') {
      line++;
      col = 0;
      continue;
    }

    switch (c) {
    case '+':
      t.push_back({ TOKEN_PLUS, "+", line, col });
    }
  }

  for (const token& tok : t) {
    std::cout << "{\"type\": " << tok.type << ", \"lex\": \"" << tok.lex << "\", \"line\": " << tok.line << ", \"col\": " << tok.column << "}" << "\n";
  }
}
