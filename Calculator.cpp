#include <cstring>
#include <deque>
#include "Token.h"
#include "Sequences.h"

bool debugMode = false;

void printCommands()
{
 printf ("The commands for this program are:\n\n");
 printf ("q - to quit the program\n");
 printf ("# - to list functions and descriptions\n");
 printf ("or any infix mathematical expression using operators of (), *, /, +, -, ^\n");
 printf ("all lists must be comma-separated\n");
}

void printFunctions() {
    printf ("The functions for this program are:\n\n");
    printf("!     - compute factorial.               E.g. a!\n");
    printf("abs   - compute absolute value.          E.g. abs(a)\n");
    printf("sqrt  - compute square root.             E.g. sqrt(a)\n");
    printf("log   - compute logarithm to base 10.    E.g. log(a)\n");
    printf("logb  - compute logarithm to base b.     E.g. log(b,a)\n");
    printf("ln    - compute logarithm to base e.     E.g. log(a)\n");
    printf("sin   - compute sine in degrees.         E.g. sin(a)\n");
    printf("cos   - compute cosine in degrees.       E.g. cos(a)\n");
    printf("tan   - compute tan in degrees.          E.g. tan(a)\n");
    printf("asin  - compute arc sine in degrees.     E.g. sin(a)\n");
    printf("acos  - compute arc cosine in degrees.   E.g. cos(a)\n");
    printf("atan  - compute arc tan in degrees.      E.g. tan(a)\n");
    printf("nCr   - compute nCr                      E.g. nCr(a,b)\n");
    printf("nPr   - compute nPr                      E.g. nPr(a,b)\n");
    printf("mean  - compute mean of a series         E.g. mean(a1, a2, ..., ak)\n");
    printf("stdev - compute std. dev. of a series    E.g. stdev(a1, a2, ..., ak)\n");
    printf("sum   - compute sum of a series          E.g. sum(1:n) User will be prompted for expression\n");
    printf("seq   - perform operations on a sequence E.g. seq(1, 1, 2, 3, 5)\n");
    printf("where 'a' & 'b' may be a number or an expression\n");
}

double processExpression (Token inputToken, TokenReader *tr, bool doPrint = true, double ans = 0);

double eval(double v1, double v2, char c) {
    switch(c) {
        case '+': return (v1 + v2);
        case '-': return (v1 - v2);
        case '*': return (v1 * v2);
        case '/': return (v1 / v2);
        case '^': return pow(v1, v2);
        default:
            printf ("Error here. Operator '%c' not recognized. Returned -999.0\n", c);
            return -999.0;
    }
}

void popAndEval(std::deque<double>& val_stack, std::deque<char>& op_stack) {
    char c = op_stack.front();
    op_stack.pop_front();
    double v2 = val_stack.front();
    val_stack.pop_front();
    double v1 = val_stack.front();
    val_stack.pop_front();
    val_stack.push_front(eval(v1, v2, c));
}

double factorial(int num, int breakpoint = 0) {
    if (num < 0) {
        printf("Can not perform factorial on negative numbers\n");
        return -999.0;
    }
    double result = 1.0;
    for (int j = breakpoint + 1; j <= num; j++) {
        result *= j;
    }
    return result;
}

double nCr(int n, int r) {
    if ((n-r) > r)
        return (factorial(n, n-r) / factorial(r));
    else
        return (factorial(n, r) / factorial(n-r));
}

double nPr(int n, int r) {
    return factorial(n, n-r);
}

double sum(int i, int n) {
    while (i < 1) {
        printf("Invalid index. Index must be greater than 0\n");
        scanf("%d",&i); getchar();
    }
    while (n >= 1000) {
        printf("Invalid index. End Index must be less than 1000\n");
        scanf("%d",&n); getchar();
    }
    int count = 0, index = 0, indexArr[20];
    char s[70];
    char *temp = new char[70];
    printf("Enter expression for sum in terms of 'j': ");
    fgets (temp, 70, stdin);
    for (int j = 0; temp[j] != '\0'; j++) {
        s[index++] = temp[j];
        if (temp[j] == 'j') {
            indexArr[count++] = index-1;
            s[index++] = ' ';
            s[index++] = ' ';
        }
    }
    s[index] = '\0';
    delete [] temp;
    Token inputToken;
    double result = 0;
    while (i <= n) {
        for (int j = 0; j < count; j++) {
            if (i < 10)
                s[indexArr[j]] = '0'+ i;
            else if (i < 100) {
                s[indexArr[j]] = '0'+ i/10; s[indexArr[j]+1] = '0'+ i%10; }
            else {
                s[indexArr[j]] = '0'+ i/100; s[indexArr[j]+1] = '0'+ (i%100)/10; s[indexArr[j]+2] = '0'+ i%10; }
        }
        TokenReader tr(s);
        inputToken = tr.getNextToken();
        result += processExpression(inputToken, &tr, false);
        ++i;
    }
    return result;
}


void evaluateFunction(std::deque<double>& val_stack, std::deque<char>& op_stack, std::deque<char>& func_stack) {
    double PI = 22.0/7.0;
    char c = func_stack.front();
    func_stack.pop_front();
    double v, mean, *vals, b;
    int n, r, size, *val;
    switch(c) {
        case 'b':
            v = fabs(val_stack.front());
            val_stack.pop_front();
            val_stack.push_front(v);
            break;
        case 'r':
            v = sqrt(val_stack.front());
            val_stack.pop_front();
            val_stack.push_front(v);
            break;
        case 'e':
            v = exp(val_stack.front());
            val_stack.pop_front();
            val_stack.push_front(v);
            break;
        case 'l':
            v = log10(val_stack.front());
            val_stack.pop_front();
            val_stack.push_front(v);
            break;
        case 'k':
            v = val_stack.front();
            val_stack.pop_front();
            b = val_stack.front();
            val_stack.pop_front();
            val_stack.push_front(log10(v)/log10(b));
            break;
        case 'n':
            v = log(val_stack.front());
            val_stack.pop_front();
            val_stack.push_front(v);
            break;
        case 's':
            v = sin((val_stack.front()) * PI/180);
            val_stack.pop_front();
            val_stack.push_front(v);
            break;
        case 'c':
            v = cos((val_stack.front()) * PI/180);
            val_stack.pop_front();
            val_stack.push_front(v);
            break;
        case 't':
            v = tan((val_stack.front()) * PI/180);
            val_stack.pop_front();
            val_stack.push_front(v);
            break;
        case 'x':
            v = asin(val_stack.front()) * 180.0 / PI;
            val_stack.pop_front();
            val_stack.push_front(v);
            break;
        case 'y':
            v = acos(val_stack.front()) * 180.0 / PI;
            val_stack.pop_front();
            val_stack.push_front(v);
            break;
        case 'z':
            v = atan(val_stack.front()) * 180.0 / PI;
            val_stack.pop_front();
            val_stack.push_front(v);
            break;
        case 'p':
            r = int(val_stack.front());
            val_stack.pop_front();
            n = int(val_stack.front());
            val_stack.pop_front();
            val_stack.push_front(nCr(n, r));
            break;
        case 'q':
            r = int(val_stack.front());
            val_stack.pop_front();
            n = int(val_stack.front());
            val_stack.pop_front();
            val_stack.push_front(nPr(n, r));
            break;
        case 'm':
            n = 1;
            v = val_stack.front();
            val_stack.pop_front();
            while (op_stack.front() == ',') {
                v += val_stack.front();
                val_stack.pop_front();
                n++;
                op_stack.pop_front();
            }
            val_stack.push_front(v/n);
            break;
        case 'u':
            n = int(round(val_stack.front()));
            val_stack.pop_front();
            r = int(round(val_stack.front()));
            val_stack.pop_front();
            val_stack.push_front(sum(r,n));
            break;
        case 'd':
            n = 0;
            size = 5;
            v = val_stack.front();
            vals = (double*)malloc(sizeof(double)*size);
            vals[n++] = val_stack.front();
            val_stack.pop_front();
            while (op_stack.front() == ',') {
                if (n == size) {
                    size += 5;
                    vals = (double *)realloc(vals, (sizeof(double) * size));
                }
                v += val_stack.front();
                vals[n++] = val_stack.front();
                val_stack.pop_front();
                op_stack.pop_front();
            }
            mean = v/n;
            v = 0;
            for (int j = 0; j < n; j++) {
                v += pow(vals[j] - mean, 2);
            }
            val_stack.push_front(sqrt(v/(n-1)));
            free(vals);
            break;
        case 'w':
            n = 0;
            size = 5;
            vals = (double*)malloc(sizeof(double)*size);
            vals[n++] = val_stack.front();
            val_stack.pop_front();
            while (op_stack.front() == ',') {
                if (n == size) {
                    size += 5;
                    vals = (double *)realloc(vals, (sizeof(double) * size));
                }
                vals[n++] = val_stack.front();
                val_stack.pop_front();
                op_stack.pop_front();
            }
            seq(vals, n);
            free(vals);
            break;
        default:
            printf ("Error here. Invalid Function\n");
            break;
    }
    
}

int main(int argc, char *argv[])
{
    /***************************************************************/
    /* Add code for checking command line arguments for debug mode */
    for (int n = 0; n < argc; ++n) {
        if (strcmp(argv[n], "-d") == 0) {
            debugMode = true;
            printf("Debugging mode ON\n");
        }
    }
    
    double ans = 0;

    Token inputToken;
    TokenReader tr;

    printf ("Starting Expression Evaluation Program. Enter '?' to list the accepted commands\n\n");
    printf ("Enter Expression: ");


    inputToken = tr.getNextToken ();

    while (inputToken.equalsType(QUIT) == false)
    {
      /* check first Token on Line of input */
      if(inputToken.equalsType(HELP))
      {
       printCommands();
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(FUNCTION_HELP))
      {
       printFunctions();
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(SEQUENCE_HELP))
      {
       printSequence();
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(ERROR))
      {
       printf ("Invalid Input - For a list of valid commands, type ?\n");
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(EOLN))
      {
       printf ("Blank Line - Do Nothing\n");
       /* blank line - do nothing */
      }
      else
      {
       ans = processExpression(inputToken, &tr, true, ans);
      }

      printf ("\nEnter Expression: ");
      inputToken = tr.getNextToken ();
    }

  printf ("Quitting Program\n");
  return 1;
}

double processExpression (Token inputToken, TokenReader *tr, bool doPrint, double ans)
{
 std::deque<double> val_stack;
 std::deque<char> op_stack, func_stack;
    
 double result;
 
 /* Loop until the expression reaches its End */
 while (inputToken.equalsType(EOLN) == false)
   {
    /* The expression contain a VALUE */
    if (inputToken.equalsType(VALUE))
      {
        double num = inputToken.getValue();
        /* Print out the number when in debugMode */
        if (debugMode) {
            printf ("Val: %f, ", num);
        }
        val_stack.push_front(num);
      }
     
    /* The expression contains a FUNCTION */
    else if (inputToken.equalsType(FUNCTION)) {
        char c = inputToken.getFunction();
        if (c == 'a') {
            val_stack.push_front(ans);
            if (debugMode)
                printf ("Val: %f, ", ans);
        }
        else {
            if (debugMode)
               printf ("Funct: %s, ", interpretFunct(c));
            func_stack.push_front(c);
        }
    }
    
    /* The expression contains an OPERATOR */
    else if (inputToken.equalsType(OPERATOR))
      {
       char val = inputToken.getOperator();
       // Print out the operator when in debugMode
       if (debugMode) {
           printf ("OP: %c, ", val);
       }
       if (val == '(')
           op_stack.push_front(val);
       if (val == '+' || val == '-') {
           while (!(op_stack.empty()) && ((op_stack.front() == '+') || (op_stack.front() == '-') || (op_stack.front() == '*')
                 || (op_stack.front() == '/') || (op_stack.front() == '^')) && (op_stack.front() != ',')&& (op_stack.front() != ':'))
               popAndEval(val_stack, op_stack);
           op_stack.push_front(val);
       }
       if (val == '*' || val == '/') {
           while (!(op_stack.empty()) && ((op_stack.front() == '*') || (op_stack.front() == '/') || (op_stack.front() == '^'))
                 && (op_stack.front() != ',') && (op_stack.front() != ':'))
               popAndEval(val_stack, op_stack);
           op_stack.push_front(val);
       }
       if (val == '^') {
           while (!(op_stack.empty()) && (op_stack.front() == '^') && (op_stack.front() != ',') && (op_stack.front() != ':'))
               popAndEval(val_stack, op_stack);
           op_stack.push_front(val);
       }
       if (val == '!') {
           double val = factorial(int(round(val_stack.front())));
           if (fabs(val-999.0) < 0.0001) {
               break;
           }
           val_stack.pop_front();
           val_stack.push_front(val);
       }
       if ((val == ',') || (val == ':')) {
           while (!(op_stack.empty()) && ((op_stack.front() != '(') && (op_stack.front() != ',') && (op_stack.front() != ':'))) {
               popAndEval(val_stack, op_stack);
           }
           op_stack.push_front(val);
       }
       if (val == ')') {
           while (!(op_stack.empty()) && (op_stack.front() != '(') && (op_stack.front() != ',') && (op_stack.front() != ':'))
               popAndEval(val_stack, op_stack);
           if (!(func_stack.empty())) {
               evaluateFunction(val_stack, op_stack, func_stack);
               while ((op_stack.front() == ',') || (op_stack.front() == ':'))
                   op_stack.pop_front();
           }
           if (op_stack.empty())
               printf("There was an error in your input please try again\n");
           else
               op_stack.pop_front();
       }
      }
    /* get next token from input */
    inputToken = tr->getNextToken();
   }
 while (!(op_stack.empty()))
     popAndEval(val_stack, op_stack);

 if(!(val_stack.empty())) {
     if (doPrint) {
         if (val_stack.front() > 10000)
             printf("Result: %.10e\n", val_stack.front());
         else
             printf("Result: %f\n", val_stack.front());
     }
     result = val_stack.front();
     val_stack.pop_front();
 }
 if (!(val_stack.empty())) {
     printf("Error here. Values Stack is not empty.\n");
 }
 return result;
}
