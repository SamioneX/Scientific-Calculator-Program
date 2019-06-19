  #include "Token.h"
  #include "CheckExpression.h"

  char interpretFunct(char input[]) {
      if ((strcmp(input, "ans") == 0) || (strcmp(input, "ANS") == 0) || (strcmp(input, "Ans") == 0))
          return 'a';
      if (strcmp(input, "abs") == 0)
          return 'b';
      if (strcmp(input, "sqrt") == 0)
          return 'r';
      if (strcmp(input, "exp") == 0)
          return 'e';
      if (strcmp(input, "log") == 0)
          return 'l';
      if (strcmp(input, "logb") == 0)
          return 'k';
      if (strcmp(input, "ln") == 0)
          return 'n';
      if (strcmp(input, "sin") == 0)
          return 's';
      if (strcmp(input, "cos") == 0)
          return 'c';
      if (strcmp(input, "tan") == 0)
          return 't';
      if (strcmp(input, "asin") == 0)
          return 'x';
      if (strcmp(input, "acos") == 0)
          return 'y';
      if (strcmp(input, "atan") == 0)
          return 'z';
      if (strcmp(input, "nCr") == 0)
          return 'p';
      if (strcmp(input, "nPr") == 0)
          return 'q';
      if (strcmp(input, "mean") == 0)
          return 'm';
      if (strcmp(input, "stdev") == 0)
          return 'd';
      if (strcmp(input, "seq") == 0)
          return 'w';
      if (strcmp(input, "sum") == 0)
          return 'u';
      return '$';
  }

  const char* interpretFunct(char c) {
      switch(c) {
        case 'b': return "abs()";
        case 'r': return "sqrt()";
        case 'e': return "exp()";
        case 'l': return "log()";
        case 'k': return "logb()";
        case 'n': return "ln()";
        case 's': return "sin()";
        case 'c': return "cos()";
        case 't': return "tan()";
        case 'x': return "asin()";
        case 'y': return "acos()";
        case 'z': return "atan";
        case 'p': return "nCr()";
        case 'q': return "nPr()";
        case 'm': return "mean()";
        case 'd': return "stdev()";
        case 'w': return "seq()";
        case 'u': return "sum()";
        default:  return "Invalid Function";
      }
  }
  // Default to initialize to the ERROR TokenType
  Token::Token()
  {
    type = ERROR;
    op = '$';
    funct = '$';
    val = -999;
  }

  // Initialize to a specific TokenType
  Token::Token(TokenType t)
  {
    type = t;
    op = '$';
    funct = '$';
    val = -999;
  }

  // Set to a specific TokenType
  void Token::setToType(TokenType t)
  {
    type = t;
    op = '$';
    funct = '$';
    val = -999;
  }

  // Set to a OPERATOR TokenType with specific operator value
  void Token::setToOperator(char c)
  {
    type = OPERATOR;
    op = c;
    funct = '$';
    val = -999;
  }

  // Set to a VALUE TokenType with a specific numeric value
  void Token::setToValue(double v)
  {
    type = VALUE;
    op = '$';
    funct = '$';
    val = v;
  }

  void Token::setToFunction(char c)
  {
    type = FUNCTION;
    op = '$';
    val = -999;
    funct = c;
  }

  // return true if the Current Token is of the given TokenType
  bool Token::equalsType(TokenType t)
  {
    if (type == t)
      return true;
    else
      return false;
  }

  // return true if the Current Token is of the OPERATOR TokenType
  //     and contains the given operator character
  bool Token::equalsOperator(char c)
  {
    if (type == OPERATOR && op == c)
      return true;
    else
      return false;
  }

  // Return the Operator for the current Token
  //   verify the current Token is of the OPERATOR TokenType
  char Token::getOperator ()
  {
    if (type == OPERATOR)
      return op;
    else
      return '$';   // using $ to indicate an error value
  }

  // Return the Value for the current Token
  //   verify the current token is of the value TokenType
  double Token::getValue()
  {
    if (type == VALUE)
      return val;
    else
      return -999.0;  // using -999 to indicate an error value
  }

  char Token::getFunction()
  {
    if (type == FUNCTION)
        return funct;
    else
        return '$';
  }

  // initialize the TokenReader class to read from Standard Input
  TokenReader::TokenReader(const char* input)
  {
    // set to read from Standard Input
    if (input != NULL) {
        strcpy(inputline, input);
        needline = false;
    }
    else {
        inputline[0] = '\0';
        needline = true;
    }
    pos = 0;
  }

  // Force the next getNextToken to read in a line of input
  void TokenReader::clearToEoln()
  {
    needline = true;
  }

  char TokenReader::getPrev(int curr) {
      int c = curr - 1;
      while (isspace(inputline[c]) && (c > 0)) c--;
      return inputline[c];
  }

  // Return the next Token from the input line
  Token TokenReader::getNextToken()
  {
    char* endCheck;

    //printf ("getToken %d, %d, %s\n", pos, needline, inputline);

    // get a new line of input from user
    if (needline)
    {
      endCheck = fgets ( inputline, 300, stdin);

      if (endCheck == NULL )
      {
        printf ("Error in reading");
        Token t(EOFILE);
        return t;
      }
      if (!isBalancedExpression(inputline, 18)) {   // check if expression is balanced and return error if not
          return Token (ERROR);
      }

      for (int i = 0 ; i < strlen(inputline) ; i++)
          if ('\n' == inputline[i])
              inputline[i] = ' ';
      strcat (inputline , " ");    // add a space at end to help deal with digit calculation
      needline = false;
      pos = 0;
    }

    // skip over any white space characters in the beginning of the input
    while ( pos < strlen(inputline) && isspace(inputline[pos]) )
    {
      pos++;
    }

    // check for the end of the current line of input
    if (pos >= strlen(inputline))
    { // at end of line
      needline = true;
      Token t(EOLN);
      return t;
    }

    // Get the next character from the input line
    char ch = inputline[pos]; pos++;
      
    // check if 'q' or 'Q' was entered ==> QUIT Token
    if ( 'q' == ch || 'Q' == ch )
    {
      return Token (QUIT);
    }
    // check if "?" was entered ==> HELP Token
    if ( '?' == ch )
    {
      return Token (HELP);
    }
    // check if "#" was entered ==> FUNCTION_HELP Token
    if ('#' == ch) {
        return Token (FUNCTION_HELP);
    }
    // check if "s" was encounters ==> SEQUENCE_HELP Token
    if (('s' == ch) && (!isalpha(inputline[pos]))) {
        return Token (SEQUENCE_HELP);
    }
    // check for an input of e (the natural number)
    if ((ch == 'e') && (inputline[pos] != 'x')){
        Token t;
        t.setToValue (2.7182818284590);
        return t;
    }
    // check for an input of pi
    if ((ch == 'p' || ch == 'P') && (inputline[pos] == 'i' || inputline[pos] == 'I')) {
        Token t;
        t.setToValue (22.0/7);
        pos++;
        return t;
    }
    // check for functions like sqrt, log, ln, sin, etc. ==> FUNCTION Token
    if (isalpha(ch)) {
        char ops[20];
        int j = 0;
        ops[j] = ch; j++;
        ch = inputline[pos]; pos++;
        while (isalpha(ch)) {
            ops[j] = ch; j++;
            ch = inputline[pos]; pos++;
        }
        pos--;
        ops[j] = '\0';
        char a = interpretFunct(ops);
        if (a != '$') {
            Token t;
            t.setToFunction(a);
            return t;
        }
        printf("\"%s\" not recognized\n", ops);
        return Token (ERROR);
    }
      
    //check for negative numbers ==> VALUE Token
    if (('-' == ch) && isdigit(inputline[pos])) {
        if (((pos - 1) == 0) || !isdigit(getPrev(pos - 1))) {
            char vals[25];
            int j = 0;
            bool seenPoint = false;
            vals[j] = ch; j++;
            vals[j] = inputline[pos]; pos++; j++;
            ch = inputline[pos]; pos++;
            while (isdigit(ch) || (ch == '.')) {
                if ((ch == '.') && seenPoint)
                    return Token (ERROR);
                if (ch == '.')
                    seenPoint = true;
                vals[j] = ch; j++;
                ch = inputline[pos]; pos++;
            }
            pos--;
            vals[j] = '\0';
            double temp = atof(vals);
            Token t;
            t.setToValue(temp);
            return t;
        }
    }

    // check for Operators  ==> OPERATOR Token
    if (('+' == ch) || ('-' == ch) || ('*' == ch) ||
      ('/' == ch) || ('(' == ch) || (')' == ch) || ('^' == ch) || ('!' == ch) || (',' == ch) || (':' == ch))
    {
      Token t;
      t.setToOperator( ch );
      return t;
    }

    // check for a positive number  ==> VALUE Token
    if (isdigit(ch))
    {
      char vals[25];
      int j = 0;
      bool seenPoint = false;
      vals[j] = ch; j++;
      ch = inputline[pos]; pos++;
      while (isdigit(ch) || (ch == '.')) {
          if ((ch == '.') && seenPoint)
              return Token (ERROR);
          if (ch == '.')
              seenPoint = true;
          vals[j] = ch; j++;
          ch = inputline[pos]; pos++;
      }
      pos--;
      vals[j] = '\0';
      double temp = atof(vals);
      Token t;
      t.setToValue(temp);
      return t;
    }

    // Input in not valid if code get to this part ==> ERROR Token
    return Token (ERROR);
  }
