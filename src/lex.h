#pragma once

#include <string>
#include "types.h"

enum token_type {
  TOKEN_INVALID,
  TOKEN_INT_LITERAL, // 32i, 42i
  TOKEN_BOOL_LITERAL, // true, false
  TOKEN_IDENT,
  TOKEN_ASSIGN, // =
  TOKEN_PLUS, // +
  TOKEN_STAR, // *
  TOKEN_MINUS, // -
  TOKEN_SLASH, // /
  TOKEN_GT, // >
  TOKEN_LT, // <
  TOKEN_EQ, // ==
  TOKEN_AND, // &&
  TOKEN_OR, // ||
  TOKEN_LPAREN, // (
  TOKEN_RPAREN, // )
  TOKEN_SEMICOLON, // ;
  TOKEN_EOF, // end of line
};

struct token {
  token_type type;
  std::string lex;
  u32 line;
  u32 column;
};

void read_source();
