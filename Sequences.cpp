#include "Sequences.h"

void printSequence() {
    std::cout << "\nThe sequence operations for this program are:\n"
              << "2. Common difference\n"
              << "3. Common ratio\n"
              << "4. Next term\n"
              << "5. Nth term\n"
              << "6. Value given index\n"
              << "7. Sum\n\n"
              << "Example: seq(2, 4, 6, 8)\n"
              << "Enter operation to perform: 1\n"
              << "Sequence type: arithmetic\n";
}

// Create an array for memoization of fibonacci numbers;
sz f[1000] = {0};


// Returns n'th Fibonacci number using table f[] 
sz stdfib(int n) 
{ 
    // Base cases 
    if (n == 0) 
        return 0; 
    if (n == 1 || n == 2) 
        return (f[n] = 1); 
  
    // If fib(n) is already computed 
    if (f[n]) 
        return f[n]; 
  
    sz k = (n & 1)? (n+1)/2 : n/2; 
  
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
sz stdfibSum(int n, int k) 
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

sz sumStdFibSquares(int n, int k) 
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
    sz x = pow(n*(n+1)/2, 2);       //Sum n^3
    sz y = n*(n+1)*(2*n+1)/6;       //Sum n^2
    sz z = n*(n+1)/2;               //Sum n
    sz b = pow(d,3);
    sz c = pow(d,2);
    sz e = pow(a,2);
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
        std::cout <<"sequence must have at least 3 arguments\n";
        return;
    }
    double cd, cr, next, prev, hd, x, y;
    int k = 0;
    bool isStdFib = false;
    char ch = seqCalc(vals, n, next, prev, cd, cr, hd, isStdFib, x, y, k);
    if (ch == '$') {
        std::cout <<"Sequence type: Unknown\n";
        return;
    }
    while (true) {
        std::cout <<"\nEnter operation to perform, < to go back, or ? to view instructions: ";
        char c;
        std::cin >> c;
        if (c == '<')
            return;
        if (c == '?')
            printSequence();
        else if (c == '1') {
            switch(ch) {
                case 'g': std::cout << "Sequence type: geometric\n"; break;
                case 'a': std::cout << "Sequence type: arithmetic\n"; break;
                case 'h': std::cout << "Sequence type: harmonic\n"; break;
                case 'f': std::cout << "Sequence type: fibonacci, with a1 = " << y << ", and a2 = " << x << '\n'; break;
                case 'x': std::cout << "Sequence type: arithmetic squares\n"; break;
                case 'y': std::cout << "Sequence type: harmonic squares\n"; break;
                case 'z': std::cout << "Sequence type: fibonacci squares, with a1 = " << pow(y,2) << ", and a2 = " << pow(x,2) << '\n'; break;
                case 't': std::cout << "Sequence type: arithmetic cubes\n"; break;
                case 'u': std::cout << "Sequence type: harmonic cubes\n"; break;
                case 'v': std::cout << "Sequence type: fibonacci cubes, with a1 = " << pow(y,3) << ", and a2 = " << pow(x,3) << '\n'; break;
            }
        }
        else if (c == '2') {
            if (ch == 'a') {
                std::cout << "Common difference: " << cd << '\n';
            }
            else
                std::cout << "Sequence is not an arithmetic sequence. Enter 1 to view type\n";
        }
        else if (c == '3') {
            if (ch == 'g') {
                std::cout << "Common ratio: " << cr << '\n';
            }
            else
                std::cout << "Sequence is not a geometric sequence. Enter 1 to view type\n";
        }
        else if (c == '4') {
            double p;
            switch(ch) {
                case 'g': std::cout << "Next term: " << next << '\n'; next = next * cr; break;
                case 'a': std::cout << "Next term: " << next << '\n'; next = next + cd; break;
                case 'h': std::cout << "Next term: 1/" << (sz)(round(1/next)) << '\n'; next = 1/(1/next + hd); break;
                case 'f':
                    if (isStdFib)
                        std::cout << "Next term: " << (sz)(round(next)) << '\n';
                    else
                        std::cout << "Next term: " << next << '\n';
                    p = next; next += prev; prev = p; break;
                case 'x': std::cout << "Next term: " << pow(next,2) << '\n'; next = next + cd; break;
                case 'y': std::cout << "Next term: 1/" << (sz)(pow(round(1/next),2)) << '\n'; next = 1/(1/next + hd); break;
                case 'z':
                    if (isStdFib)
                        std::cout << "Next term: " << (sz)(pow(round(next),2)) << '\n';
                    else
                        std::cout << "Next term: " << pow(next, 2) << '\n';
                    p = next; next += prev; prev = p; break;
                case 't': std::cout << "Next term: " << pow(next,3) << '\n'; next = next + cd; break;
                case 'u': std::cout << "Next term: 1/" << (sz)(pow(round(1/next),3)) << '\n'; next = 1/(1/next + hd); break;
                case 'v':
                    if (isStdFib)
                        std::cout << "Next term: " << (sz)(pow(round(next),3)) << '\n';
                    else
                        std::cout << "Next term: " << pow(next, 3) << '\n';
                    p = next; next += prev; prev = p; break;
            }
        }
        else if (c == '5') {
            double f;
            switch(ch) {
                case 'g':
                    f = vals[n-1]/cr;
                    if (fabs(f - 1) < 0.0000001)
                        std::cout << "Nth term: " << cr << "^ n\n";
                    else
                        std::cout << "Nth term: " << f << " * (" << cr << " ^ n)\n";
                    break;
                case 'a':
                    f = vals[n-1] - cd;
                    if (fabs(f - 0.0) < 0.0000001)
                        std::cout << "Nth term: " << cd << " * n\n";
                    else
                        std::cout << "Nth term: " << f << " + (" << cd << " * n)\n";
                    break;
                case 'h':
                    f = 1/vals[n-1] - hd;
                    if (fabs(f - 0.0) < 0.0000001)
                        std::cout << "Nth term: 1/(" << hd << " * n)\n";
                    else
                        std::cout << "Nth term: 1/(" << f << " + (" << hd << " * n))\n";
                    break;
                case 'f':
                    if (isStdFib)
                        std::cout << "Nth term: (phi^(n+" << k << ") - (-phi)^(n+" << k << "))/sqrt(5) where phi = (1+sqrt(5))/2 and -phi = (1-sqrt(5))/2\n";
                    else
                        std::cout << "Nth term: (N - 1)th term - (N - 2)th term\n";
                    break;
                case 'x':
                    f = sqrt(vals[n-1]) - cd;
                    if (fabs(f - 0.0) < 0.0000001)
                        std::cout << "Nth term: (" << cd << " * n)^2\n";
                    else
                        std::cout << "Nth term: (" << f << " + (" << cd << " * n))^2\n";
                    break;
                case 'y':
                    f = 1/sqrt(vals[n-1]) - hd;
                    if (fabs(f - 0.0) < 0.0000001)
                        std::cout << "Nth term: 1/" << hd << " * n)^2\n";
                    else
                        std::cout << "Nth term: 1/(" << f << " + (" << hd << " * n))^2\n";
                    break;
                case 'z':
                    if (isStdFib)
                        std::cout << "Nth term: ((phi^(n+" << k << ") - (-phi)^(n+" << k << "))^2)/5 where phi = (1+sqrt(5))/2 and -phi = (1-sqrt(5))/2\n";
                    else
                        std::cout << "Nth term: (sqrt(N - 1)th term - sqrt(N - 2)th term)^2\n";
                    break;
                case 't':
                    f = pow(vals[n-1], 1.0/3) - cd;
                    if (fabs(f - 0.0) < 0.0000001)
                        std::cout << "Nth term: " << cd << " * n)^3\n";
                    else
                        std::cout << "Nth term: (" << f << " + (" << cd << " * n))^3\n";
                    break;
                case 'u':
                    f = 1/pow(vals[n-1], 1.0/3) - hd;
                    if (fabs(f - 0.0) < 0.0000001)
                        std::cout << "Nth term: 1/(" << hd << " * n)^3\n";
                    else
                        std::cout << "Nth term: 1/(" << f << " + (" << hd << " * n))^3\n";
                    break;
                case 'v':
                    if (isStdFib)
                        std::cout << "Nth term: ((phi^(n+" << k << ") - (-phi)^(n+" << k << "))/sqrt(5))^3 where phi = (1+sqrt(5))/2 and -phi = (1-sqrt(5))/2\n";
                    else
                        std::cout << "Nth term: (cbrt(N - 1)th term - cbrt(N - 2)th term)^3\n";
                    break;
            }
        }
        else if (c == '6') {
            std::cout << "Enter index: ";
            int v;
            std::cin >> v;
            while (v < 1) {
                std::cout << "Index can not be less than 1. Enter an index: ";
                std::cin >> v;
            }
            double f;
            switch(ch) {
                case 'g':
                    f = vals[n-1] * pow(cr, v-1);
                    std::cout << "Value at index " << v << " is: " << f << '\n'; break;
                case 'a':
                    f = vals[n-1] + (cd * (v-1));
                    std::cout << "Value at index " << v << " is: " << f << '\n'; break;
                case 'h':
                    f = 1/vals[n-1] + (hd * (v-1));
                    std::cout << "Value at index " << v << " is: 1/" << (sz)(round(f)) << '\n'; break;
                case 'f':
                    if (isStdFib) {
                        std::cout << "Value at index " << v << " is: " << stdfib(v+k) << '\n';
                    }
                    else
                        std::cout << "Value at index " << v << " is: " << fib(vals[n-1], vals[n-2], v) << '\n';
                    break;
                case 'x':
                    f = sqrt(vals[n-1]) + (cd * (v-1));
                    std::cout << "Value at index " << v << " is: " << pow(f,2) << '\n'; break;
                case 'y':
                    f = 1/sqrt(vals[n-1]) + (hd * (v-1));
                    std::cout << "Value at index " << v << " is: 1/" << (sz)(round(pow(f,2))) << '\n'; break;
                case 'z':
                    if (isStdFib) {
                        std::cout << "Value at index " << v << " is: " << (sz)(pow(stdfib(n+k+1), 2)) << '\n';
                    }
                    else
                        std::cout << "Value at index " << v << " is: " << pow(fib(sqrt(vals[n-1]), sqrt(vals[n-2]), v), 2) << '\n';
                    break;
                case 't':
                    f = pow(vals[n-1], 1.0/3) + (cd * (v-1));
                    std::cout << "Value at index " << v << " is: " << pow(f,3) << '\n'; break;
                case 'u':
                    f = 1/pow(vals[n-1], 1.0/3) + (hd * (v-1));
                    std::cout << "Value at index " << v << " is: 1/" << (sz)(round(pow(f,3))) << '\n'; break;
                case 'v':
                    if (isStdFib) {
                        std::cout << "Value at index " << v << " is: " << (sz)(pow(stdfib(n+k+1), 3)) << '\n';
                    }
                    else
                        std::cout << "Value at index " << v << " is: " << pow(fib(sqrt(vals[n-1]), sqrt(vals[n-2]), v), 3) << '\n';
                    break;
            }
        }
        else if (c == '7') {
            std::cout << "Enter end index. Enter -999 for infinity: ";
            int v;
            bool isINF = false;
            std::cin >> v;
            if (v == -999)
                isINF = true;
            while ((v <= 0) && !isINF) {
                std::cout << "Invalid index. Enter an index > 0 or -999 for infinity";
                std::cin >> v;
                if (v == -999)
                    isINF = true;
            }
            double f, gamma;
            switch(ch) {
                case 'g':
                    if (fabs(cr - 1) < 0.0000001) {
                        std::cout << "Unable to calculate sum. Common ratio cannot be equal to 1\n";
                        continue;
                    }
                    if(!isINF)
                        f = (vals[n-1] * (1 - pow(cr, v)))/(1-cr);
                    else
                        f = (vals[n-1])/(1-cr);
                    std::cout << "Sum: " << f << '\n'; break;
                case 'a':
                    if (isINF) {
                        std::cout << "Sum of an arithmetic sequence requires a finite endpoint\n";
                        continue;
                    }
                    f = v * (vals[n-1] + (cd * (v-1))/2);
                    std::cout << "Sum: " << f << '\n'; break;
                case 'h':
                    if (isINF) {
                        std::cout << "Sum of a harmonic sequence requires a finite endpoint\n";
                        continue;
                    }
                    if (v < 100000000) {
                        std::cout << "Sum: " << sumHarmonic(vals[n-1], hd, v) << '\n';
                        continue;
                    }
                    if (fabs(hd - 1) < 0.0000001) {
                        gamma = 0.577215664901532860606512090082;   //Euler–Mascheroni constant
                        f = log(v) + gamma + 1.0/(2*v);             //Sum(1:k, 1/n) = ln(k) + gamma + Ek (Ek ~= 1/2k)
                        std::cout << "Sum is approximately: " << f << '\n';
                        continue;
                    }
                    std::cout << "Can not perform calculation. End Index must be less than 10^8\n";
                    break;
                case 'f':
                    if (isINF) {
                        std::cout << "Sum of a fibonacci sequence requires a finite endpoint\n";
                        continue;
                    }
                    if (v < 1000) {
                        if (isStdFib)
                            std::cout << "Sum: " << stdfibSum(v+k, k) << '\n';
                        else
                            std::cout << "Sum: " << fibSum(v, vals[n-1], vals[n-2]) << '\n';
                        continue;
                    }
                    std::cout << "Can not perform calculation. End Index must be less than 1000\n";
                case 'x':
                    if (isINF) {
                        std::cout << "Sum of arithmetic squares sequence requires a finite endpoint\n";
                        continue;
                    }
                    std::cout << "Sum: " << sumArrSquares(vals[n-1], cd, v) << '\n'; break;
                case 'y':
                    if (isINF) {
                        std::cout << "Sum of harmonic squares sequence requires a finite endpoint\n";
                        continue;
                    }
                    if (v > 30000)
                        std::cout << "Sum is approximately: " << sumHarSquares(vals[n-1], hd, 30000) << '\n';
                    else
                        std::cout << "Sum: " << sumHarSquares(vals[n-1], hd, v) << '\n'; break;
                case 'z':
                    if (isINF) {
                        std::cout << "Sum of fibonacci squares sequence requires a finite endpoint\n";
                        continue;
                    }
                    if (v < 1000) {
                        if (isStdFib)
                            std::cout << "Sum: " << sumStdFibSquares(v+k, k) << '\n';
                        else
                            std::cout << "Sum: " << sumFibSquares(v, vals[n-1], vals[n-2]) << '\n';
                        continue;
                    }
                    std::cout << "Can not perform calculation. End Index must be less than 1000\n";
                    break;
                case 't':
                    if (isINF) {
                        std::cout << "Sum of arithmetic cubes sequence requires a finite endpoint\n";
                        continue;
                    }
                    std::cout << "Sum: " << sumArrCubes(vals[n-1], cd, v) << '\n'; break;
                case 'u':
                    if (isINF) {
                        std::cout << "Sum of harmonic cubes sequence requires a finite endpoint\n";
                        continue;
                    }
                    if (v < 100000000) {
                        std::cout << "Sum: " << sumHarCubes(vals[n-1], hd, v) << '\n';
                        continue;
                    }
                    else
                        std::cout << "Can not perform calculation. End Index must be less than 10^8\n"; break;
                case 'v':
                    if (isINF) {
                        std::cout << "Sum of fibonacci cubes sequence requires a finite endpoint\n";
                        continue;
                    }
                    if (v < 1000) {
                        std::cout << "Sum: " << sumFibCubes(v, vals[n-1], vals[n-2]) << '\n';
                        continue;
                    }
                    std::cout << "Can not perform calculation. End Index must be less than 1000\n";
                    break;
            }
        }
        else
            std::cout << "Invalid selection. Enter ? to view options\n";
    }
}
