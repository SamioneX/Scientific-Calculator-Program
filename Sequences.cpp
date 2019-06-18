#include "Sequences.h"

void printSequence() {
    printf("\nThe sequence operations for this program are:\n");
    printf("1. Sequence type (arithmetic, geometric, harmonic, fibonacci, etc.)\n");
    printf("2. Common difference\n");
    printf("3. Common ratio\n");
    printf("4. Next term\n");
    printf("5. Nth term\n");
    printf("6. Value given index\n");
    printf("7. Sum\n\n");
    printf("Example: seq(2, 4, 6, 8)\n");
    printf("Enter operation to perform: 1\n");
    printf("Sequence type: arithmetic\n");
}

// Create an array for memoization of fibonacci numbers;
int f[1000] = {0};


// Returns n'th Fibonacci number using table f[] 
int stdfib(int n) 
{ 
    // Base cases 
    if (n == 0) 
        return 0; 
    if (n == 1 || n == 2) 
        return (f[n] = 1); 
  
    // If fib(n) is already computed 
    if (f[n]) 
        return f[n]; 
  
    int k = (n & 1)? (n+1)/2 : n/2; 
  
    // Applying above formula [Note value n&1 is 1 
    // if n is odd, else 0]. 
    f[n] = (n & 1)? (stdfib(k)*stdfib(k) + stdfib(k-1)*stdfib(k-1)) 
           : (2*stdfib(k-1) + stdfib(k))*stdfib(k); 
  
    return f[n]; 
}

// Returns n'th Fibonacci number of non-standard fibonacci sequence. i.e. a1 & a2 != 1

double fib(double x, double y, int index) {
    double next = x + y;
    double p, prev = y;
    for (int j = 3; j < index; ++j) {
        p = next;
        next = next + prev;
        prev = p;
    }
    return next;
}

// Computes value of sum of first n Fibonacci numbers 
int stdfibSum(int n, int k) 
{ 
    if (k == 0)
        return stdfib(n+2) - 1;
    return stdfibSum(n) - stdfibSum(k);
}

// Computes value of sum of first n Fibonacci numbers for non-standard sequence
double fibSum(int n, double x, double y) {
    if (n <= 0) 
       return 0; 
  
    double fibo[n];
    fibo[0] = x, fibo[1] = y; 
  
    // Initialize result 
    double sum = fibo[0] + fibo[1]; 
  
    // Add remaining terms 
    for (int i=2; i<n; i++) {
        fibo[i] = fibo[i-1]+fibo[i-2]; 
        sum += fibo[i]; 
    } 
    return sum; 
}

int sumStdFibSquares(int n, int k) 
{ 
    if (k == 0)
        return stdfib(n) * stdfib(n + 1);
    return sumStdFibSquares(n) - sumStdFibSquares(k);
}

double sumFibSquares(int n, double x, double y) 
{ 
    if (n <= 0) 
        return 0; 
  
    double fibo[n + 1]; 
    fibo[0] = sqrt(x), fibo[1] = sqrt(y);
  
    // Initialize result 
    double sum = (fibo[0] * fibo[0]) + (fibo[1] * fibo[1]);
    
    // Add remaining terms 
    for (int i = 2; i < n; i++) { 
        fibo[i] = fibo[i - 1] + fibo[i - 2];
        sum += (fibo[i] * fibo[i]); 
    } 
    return sum;
}

double sumFibCubes(int n, double x, double y) 
{ 
    if (n <= 0) 
        return 0; 
  
    double fibo[n + 1]; 
    fibo[0] = pow(x, 1.0/3), fibo[1] = pow(y, 1.0/3);
  
    // Initialize result 
    double sum = (fibo[0] * fibo[0] * fibo[0]) + (fibo[1] * fibo[1] * fibo[1]);
    
    // Add remaining terms 
    for (int i = 2; i < n; i++) { 
        fibo[i] = fibo[i - 1] + fibo[i - 2];
        sum += (fibo[i] * fibo[i] * fibo[i]); 
    } 
    return sum;
}

double sumArrSquares(double a, double d, int n) {
    return (n * pow((sqrt(a)-d),2)) + 2*(sqrt(a)-d)*d*(n*(n+1)/2) + pow(d, 2)*(n*(n+1)*(2*n+1)/6);
}

double sumArrCubes(double a, double d, int n) {
    a = pow(a, 1.0/3);
    int x = pow(n*(n+1)/2, 2);       //Sum n^3
    int y = n*(n+1)*(2*n+1)/6;       //Sum n^2
    int z = n*(n+1)/2;               //Sum n
    int b = pow(d,3);
    int c = pow(d,2);
    int e = pow(a,2);
    return (x*b - 3*y*b + 3*z*b - b + 3*a*c*y - 6*z*a*c + 3*a*c + 3*z*e*d - 3*e*d + pow(a,3));
}

double sumHarmonic(double a, double hd, int k) {
    double sum = a;
    double next = 1/(1/a + hd);
    for (int j = 0; j < k-1; j++) {
        sum += next;
        next = 1/(1/next + hd);
    }
    return sum;
}

double sumHarSquares(double a, double d, int n) {
    double result = 0;
    a = 1/sqrt(a);
    for (int j = 1; j <= n; j++) {
        result += 1/pow(a+(j-1)*d, 2);
    }
    return result;
}

double sumHarCubes(double a, double d, int n) {
    double result = 0;
    a = 1/pow(a, 1.0/3);
    for (int j = 1; j <= n; j++) {
        result += 1/pow(a+(j-1)*d, 3);
    }
    return result;
}

char seqCalc(double val[], int size, double &next, double &prev, double &cd, double &cr, double &hd, 
             bool& isStdFib, double &x, double &y, int &k, bool checkBasic) {
    bool isArr, isGeo, isHar, isFib;
    isArr = isGeo = isHar = isFib = true;
    for (int i = size - 1; i > 1; i--) {
        if (fabs((val[i - 1]/val[i]) - (val[i-2]/val[i-1])) > 0.0000001) {
            isGeo = false;
            break;
        }
    }
    if (isGeo) {
        cr = (val[0]/val[1]);
        next = val[0] * cr;
        return 'g';
    }
    for (int i = size - 1; i > 1; i--) {
        if (fabs((val[i-1] - val[i]) - (val[i-2] - val[i-1])) > 0.0000001) {
            isArr = false;
            break;
        }
    }
    if (isArr) {
        cd = (val[0] - val[1]);
        next = val[0] + cd;
        return 'a';
    }
    for (int i = size - 1; i > 1; i--) {
        if (fabs((1/val[i-1] - 1/val[i]) - (1/val[i-2] - 1/val[i-1])) > 0.0000001) {
            isHar = false;
            break;
        }
    }
    if (isHar) {
        hd = (1/val[0] - 1/val[1]);
        next = 1/(1/val[0] + hd);
        return 'h';
    }
    for (int i = size - 3; i >= 0; i--) {
        if (fabs(val[i] - (val[i+1] + val[i+2])) > 0.0000001) {
            isFib = false;
            break;
        }
    }
    if(isFib) {
        next = val[0] + val[1];
        prev = val[0];
        x = val[size - 1], y = val[size - 2];
        double a = y - x;
        while (a > 0.0000001) {y = x; x = a; a = y - x; k++;}
        if ((fabs(x - 1) < 0.0000001) && (fabs(y - 1) < 0.0000001)) {
            isStdFib = true;
        }
        return 'f';
    }
    if (checkBasic)
        return '$';
    double* sqrts = new double[size];
    for (int i = size - 1; i >= 0; i--) {
        sqrts[i] = sqrt(val[i]);
    }
    char ch = seqCalc(sqrts, size, next, prev, cd, cr, hd, isStdFib, x, y, k, true);
    delete [] sqrts;
    switch(ch) {
        case 'a': return 'x';
        case 'h': return 'y';
        case 'f': return 'z';
    }
    double* cubes = new double[size];
    for (int i = size - 1; i >= 0; i--) {
        cubes[i] = pow(val[i], 1.0/3);
    }
    ch = seqCalc(cubes, size, next, prev, cd, cr, hd, isStdFib, x, y, k, true);
    delete [] cubes;
    switch(ch) {
        case 'a': return 't';
        case 'h': return 'u';
        case 'f': return 'v';
    }
    return '$';
}


void seq(double vals[], int n) {
    if (n < 3) {
        printf("sequence must have at least 3 arguments\n");
        return;
    }
    double cd, cr, next, prev, hd, x, y;
    int k = 0;
    bool isStdFib = false;
    char ch = seqCalc(vals, n, next, prev, cd, cr, hd, isStdFib, x, y, k);
    if (ch == '$') {
        printf("Sequence type: Unknown\n");
        return;
    }
    while (true) {
        printf("\nEnter operation to perform, < to go back, or ? to view instructions: ");
        char c = getchar(); getchar(); 
        if (c == '<')
            return;
        if (c == '?')
            printSequence();
        else if (c == '1') {
            switch(ch) {
                case 'g': printf("Sequence type: geometric\n"); break;
                case 'a': printf("Sequence type: arithmetic\n"); break;
                case 'h': printf("Sequence type: harmonic\n"); break;
                case 'f': printf("Sequence type: fibonacci, with a1 = %f, and a2 = %f\n", y, x); break;
                case 'x': printf("Sequence type: arithmetic squares\n"); break;
                case 'y': printf("Sequence type: harmonic squares\n"); break;
                case 'z': printf("Sequence type: fibonacci squares, with a1 = %f, and a2 = %f\n", pow(y,2), pow(x,2)); break;
                case 't': printf("Sequence type: arithmetic cubes\n"); break;
                case 'u': printf("Sequence type: harmonic cubes\n"); break;
                case 'v': printf("Sequence type: fibonacci cubes, with a1 = %f, and a2 = %f\n", pow(y,3), pow(x,3)); break;
            }
        }
        else if (c == '2') {
            if (ch == 'a') {
                printf("Common difference: %f\n", cd);
            }
            else
                printf("Sequence is not an arithmetic sequence. Enter 1 to view type\n");
        }
        else if (c == '3') {
            if (ch == 'g') {
                printf("Common ratio: %f\n", cr);
            }
            else
                printf("Sequence is not a geometric sequence. Enter 1 to view type\n");
        }
        else if (c == '4') {
            double p;
            switch(ch) {
                case 'g': printf("Next term: %f\n", next); next = next * cr; break;
                case 'a': printf("Next term: %f\n", next); next = next + cd; break;
                case 'h': printf("Next term: 1/%d\n", int(round(1/next))); next = 1/(1/next + hd); break;
                case 'f':
                    if (isStdFib)
                        printf("Next term is: %d\n", int(round(next)));
                    else
                        printf("Next term: %f\n", next);
                    p = next; next += prev; prev = p; break;
                case 'x': printf("Next term: %f\n", pow(next,2)); next = next + cd; break;
                case 'y': printf("Next term: 1/%d\n", int(pow(round(1/next),2))); next = 1/(1/next + hd); break;
                case 'z':
                    if (isStdFib)
                        printf("Next term is: %d\n", int(pow(round(next),2)));
                    else
                        printf("Next term: %f\n", pow(next, 2));
                    p = next; next += prev; prev = p; break;
                case 't': printf("Next term: %f\n", pow(next,3)); next = next + cd; break;
                case 'u': printf("Next term: 1/%d\n", int(pow(round(1/next),3))); next = 1/(1/next + hd); break;
                case 'v':
                    if (isStdFib)
                        printf("Next term is: %d\n", int(pow(round(next),3)));
                    else
                        printf("Next term: %f\n", pow(next, 3));
                    p = next; next += prev; prev = p; break;
            }
        }
        else if (c == '5') {
            double f;
            switch(ch) {
                case 'g':
                    f = vals[n-1]/cr;
                    if (fabs(f - 1) < 0.0000001)
                        printf("Nth term: %f ^ n\n", cr);
                    else
                        printf("Nth term: %f * (%f ^ n)\n", f, cr);
                    break;
                case 'a':
                    f = vals[n-1] - cd;
                    if (fabs(f - 0.0) < 0.0000001)
                        printf("Nth term: %f * n\n", cd);
                    else
                        printf("Nth term: %f + (%f * n)\n", f, cd);
                    break;
                case 'h':
                    f = 1/vals[n-1] - hd;
                    if (fabs(f - 0.0) < 0.0000001)
                        printf("Nth term: 1/(%f * n)\n", hd);
                    else
                        printf("Nth term: 1/(%f + (%f * n))\n", f, hd);
                    break;
                case 'f':
                    if (isStdFib)
                        printf("Nth term: (phi^(n+%d) - (-phi)^(n+%d))/sqrt(5) where phi = (1+sqrt(5))/2 and -phi = (1-sqrt(5))/2\n", k,k);
                    else
                        printf("Nth term: (N - 1)th term - (N - 2)th term\n");
                    break;
                case 'x':
                    f = sqrt(vals[n-1]) - cd;
                    if (fabs(f - 0.0) < 0.0000001)
                        printf("Nth term: (%f * n)^2\n", cd);
                    else
                        printf("Nth term: (%f + (%f * n))^2\n", f, cd);
                    break;
                case 'y':
                    f = 1/sqrt(vals[n-1]) - hd;
                    if (fabs(f - 0.0) < 0.0000001)
                        printf("Nth term: 1/(%f * n)^2\n", hd);
                    else
                        printf("Nth term: 1/(%f + (%f * n))^2\n", f, hd);
                    break;
                case 'z':
                    if (isStdFib)
                        printf("Nth term: ((phi^(n+%d) - (-phi)^(n+%d))^2)/5 where phi = (1+sqrt(5))/2 and -phi = (1-sqrt(5))/2\n", k, k);
                    else
                        printf("Nth term: (sqrt(N - 1)th term - sqrt(N - 2)th term)^2\n");
                    break;
                case 't':
                    f = pow(vals[n-1], 1.0/3) - cd;
                    if (fabs(f - 0.0) < 0.0000001)
                        printf("Nth term: (%f * n)^3\n", cd);
                    else
                        printf("Nth term: (%f + (%f * n))^3\n", f, cd);
                    break;
                case 'u':
                    f = 1/pow(vals[n-1], 1.0/3) - hd;
                    if (fabs(f - 0.0) < 0.0000001)
                        printf("Nth term: 1/(%f * n)^3\n", hd);
                    else
                        printf("Nth term: 1/(%f + (%f * n))^3\n", f, hd);
                    break;
                case 'v':
                    if (isStdFib)
                        printf("Nth term: ((phi^(n+%d) - (-phi)^(n+%d))/sqrt(5))^3 where phi = (1+sqrt(5))/2 and -phi = (1-sqrt(5))/2\n" , k, k);
                    else
                        printf("Nth term: (cbrt(N - 1)th term - cbrt(N - 2)th term)^3\n");
                    break;
            }
        }
        else if (c == '6') {
            printf("Enter index: ");
            int v; scanf("%d",&v);
            getchar();
            while (v < 1) {
                printf("Index can not be less than 1. Enter an index: ");
                scanf("%d",&v); getchar();
            }
            double f;
            switch(ch) {
                case 'g':
                    f = vals[n-1] * pow(cr, v-1);
                    printf("Value at index %d is: %f\n", v, f); break;
                case 'a':
                    f = vals[n-1] + (cd * (v-1));
                    printf("Value at index %d is: %f\n", v, f); break;
                case 'h':
                    f = 1/vals[n-1] + (hd * (v-1));
                    printf("Value at index %d is: 1/%d\n", v, int(round(f))); break;
                case 'f':
                    if (isStdFib) {
                        printf("Value at index %d is: %d\n", v, stdfib(v+k));
                    }
                    else
                        printf("Value at index %d is: %f\n", v, fib(vals[n-1], vals[n-2], v));
                    break;
                case 'x':
                    f = sqrt(vals[n-1]) + (cd * (v-1));
                    printf("Value at index %d is: %f\n", v, pow(f,2)); break;
                case 'y':
                    f = 1/sqrt(vals[n-1]) + (hd * (v-1));
                    printf("Value at index %d is: 1/%d\n", v, int(round(pow(f,2)))); break;
                case 'z':
                    if (isStdFib) {
                        printf("Value at index %d is: %d\n", v, int(pow(stdfib(n+k+1), 2)));
                    }
                    else
                        printf("Value at index %d is: %f\n", v, pow(fib(sqrt(vals[n-1]), sqrt(vals[n-2]), v), 2));
                    break;
                case 't':
                    f = pow(vals[n-1], 1.0/3) + (cd * (v-1));
                    printf("Value at index %d is: %f\n", v, pow(f,3)); break;
                case 'u':
                    f = 1/pow(vals[n-1], 1.0/3) + (hd * (v-1));
                    printf("Value at index %d is: 1/%d\n", v, int(round(pow(f,3)))); break;
                case 'v':
                    if (isStdFib) {
                        printf("Value at index %d is: %d\n", v, int(pow(stdfib(n+k+1), 3)));
                    }
                    else
                        printf("Value at index %d is: %f\n", v, pow(fib(pow(vals[n-1], 1.0/3), pow(vals[n-2], 1.0/3), v), 3));
                    break;
            }
        }
        else if (c == '7') {
            printf("Enter end index. Enter -999 for infinity: ");
            int v;
            bool isINF = false;
            scanf("%d",&v); getchar();
            if (v == -999)
                isINF = true;
            while ((v <= 0) && !isINF) {
                printf("Invalid index. Enter an index > 0 or -999 for infinity");
                scanf("%d",&v); getchar();
                if (v == -999)
                    isINF = true;
            }
            double f, gamma;
            switch(ch) {
                case 'g':
                    if (fabs(cr - 1) < 0.0000001) {
                        printf("Unable to calculate sum. Common ratio cannot be equal to 1\n");
                        continue;
                    }
                    if(!isINF)
                        f = (vals[n-1] * (1 - pow(cr, v)))/(1-cr);
                    else
                        f = (vals[n-1])/(1-cr);
                    printf("Sum: %.10e\n", f);
                    break;
                case 'a':
                    if (isINF) {
                        printf("Sum of an arithmetic sequence requires a finite endpoint\n");
                        continue;
                    }
                    f = v * (vals[n-1] + (cd * (v-1))/2);
                    printf("Sum: %.10e\n", f);
                    break;
                case 'h':
                    if (isINF) {
                        printf("Sum of a harmonic sequence requires a finite endpoint\n");
                        continue;
                    }
                    if (v < 100000000) {
                        printf("Sum: %.10e\n", sumHarmonic(vals[n-1], hd, v));
                        continue;
                    }
                    if (fabs(hd - 1) < 0.0000001) {
                        gamma = 0.577215664901532860606512090082;   //Euler–Mascheroni constant
                        f = log(v) + gamma + 1.0/(2*v);             //Sum(1:k, 1/n) = ln(k) + gamma + Ek (Ek ~= 1/2k)
                        printf("Sum is approximately: %.10e\n", f);
                        continue;
                    }
                    printf("Can not perform calculation. End Index must be less than 10^8\n");
                    break;
                case 'f':
                    if (isINF) {
                        printf("Sum of a fibonacci sequence requires a finite endpoint\n");
                        continue;
                    }
                    if (v < 1000) {
                        if (isStdFib)
                            printf("Sum: %d\n", stdfibSum(v+k, k));
                        else
                            printf("Sum: %.10e\n", fibSum(v, vals[n-1], vals[n-2]));
                        continue;
                    }
                    printf("Can not perform calculation. End Index must be less than 1000\n");
                    break;
                case 'x':
                    if (isINF) {
                        printf("Sum of arithmetic squares sequence requires a finite endpoint\n");
                        continue;
                    }
                    printf("Sum: %.10e\n", sumArrSquares(vals[n-1], cd, v)); break;
                case 'y':
                    if (isINF) {
                        printf("Sum of harmonic squares sequence requires a finite endpoint\n");
                        continue;
                    }
                    if (v > 30000)
                        printf("Sum is approximately: %f\n", sumHarSquares(vals[n-1], hd, 30000));
                    else
                        printf("Sum is: %f", sumHarSquares(vals[n-1], hd, v)); break;
                case 'z':
                    if (isINF) {
                        printf("Sum of fibonacci squares sequence requires a finite endpoint\n");
                        continue;
                    }
                    if (v < 1000) {
                        if (isStdFib)
                            printf("Sum: %d\n", sumStdFibSquares(v+k, k));
                        else
                            printf("Sum: %.10e\n", sumFibSquares(v, vals[n-1], vals[n-2]));
                        continue;
                    }
                    printf("Can not perform calculation. End Index must be less than 1000\n");
                    break;
                case 't':
                    if (isINF) {
                        printf("Sum of arithmetic cubes sequence requires a finite endpoint\n");
                        continue;
                    }
                    printf("Sum: %.10e\n", sumArrCubes(vals[n-1], cd, v)); break;
                case 'u':
                    if (isINF) {
                        printf("Sum of harmonic cubes sequence requires a finite endpoint\n");
                        continue;
                    }
                    if (v < 100000000) {
                        printf("Sum: %.10e\n", sumHarCubes(vals[n-1], hd, v));
                        continue;
                    }
                    else
                        printf("Can not perform calculation. End Index must be less than 10^8\n"); break;
                case 'v':
                    if (isINF) {
                        printf("Sum of fibonacci cubes sequence requires a finite endpoint\n");
                        continue;
                    }
                    if (v < 1000) {
                        printf("Sum: %.10e\n", sumFibCubes(v, vals[n-1], vals[n-2]));
                        continue;
                    }
                    printf("Can not perform calculation. End Index must be less than 1000\n");
                    break;
            }
            
        }
        else
            printf("Invalid selection. Enter # to view options\n");
    }
}