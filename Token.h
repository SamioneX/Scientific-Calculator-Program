#ifndef TOKEN_H
#define TOKEN_H

#include <cctype>
#include <cstdlib>

enum TokenType{
  ERROR, OPERATOR, VALUE, FUNCTION, EOLN, QUIT, HELP, FUNCTION_HELP, SEQUENCE_HELP, EOFILE
};

char interpretFunct(char input[]);
const char* interpretFunct(char c);

class Token
{
  private:
    TokenType type;
    char    op;       // using '$' as undefined/error
    char    funct;    // using '$' as undefined/error
    double   val;      // using -999 as undefined/error
    
  public:
    Token();
    Token (TokenType t);
    void setToType(TokenType t);
    void setToOperator(char c);
    void setToValue(double v);
    void setToFunction(char c);
    bool equalsType(TokenType t);
    bool equalsOperator(char c);
    char getOperator();
    double getValue();
    char getFunction();
};

class TokenReader
{
  private:
     char inputline[300];  // this assumes that all input lines are 300 characters or less in length
     bool needline;
     int pos;
     char getPrev(int curr);
    
  public:
    TokenReader(char input[] = NULL);
    void clearToEoln();
    Token getNextToken();
};

#endif