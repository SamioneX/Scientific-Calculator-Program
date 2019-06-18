#ifndef SEQUENCES_H
#define SEQUENCES_H

#include <cmath>
#include <cstdio>

typedef unsigned long long sz;

void printSequence();
int stdfib(int n);
double fib(double x, double y, int index);
int stdfibSum(int n, int k = 0);
double fibSum(int n, double x, double y);
int sumStdFibSquares(int n, int k = 0);
double sumFibSquares(int n, double x = 1, double y = 1);
double sumFibCubes(int n, double x = 1, double y = 1);
double sumArrSquares(double a, double d, int n);
double sumArrCubes(double a, double d, int n);
double sumHarmonic(double a, double hd, int k);
double sumHarSquares(double a, double d, int n);
double sumHarCubes(double a, double d, int n);
char seqCalc(double val[], int size, double &next, double &prev, double &cd, double &cr, double &hd, 
             bool& isStdFib, double &x, double &y, int &k, bool checkBasic = false);
void seq(double vals[], int n);

#endif