#ifndef CHECKEXPRESSION_H
#define CHECKEXPRESSION_H

#include <cstring>
#include <cstdio>
#include <deque>

std::pair<char, char> pairs[4] = {std::pair<char, char>('(', ')'),
                                  std::pair<char, char>('[', ']'),
                                  std::pair<char, char>('{', '}'),
                                  std::pair<char, char>('<', '>') };

bool isBalancedExpression(char input[], int spaces)
{
   std::deque<char> st;
   bool errorFree = true;
   
   // Loop through the string and check for errors
   int i;
   for (i = 0; i < strlen(input)-1; ++i) {
     
     // Push all firsting signs into the stack
     if ((input[i] == pairs[0].first) || (input[i] == pairs[1].first) || (input[i] == pairs[2].first) || (input[i] == pairs[3].first)) {
       st.push_front(input[i]);
     }

     // Check for errors when a closing sign is encountered
     else if ((input[i] == pairs[0].second) || (input[i] == pairs[1].second) || (input[i] == pairs[2].second) || (input[i] == pairs[3].second)) {
       int j;

       // Determine which closing sign was encountered
       for (j = 0; j < 4; ++j) {
         if (pairs[j].second == input[i]) {
           break;
         }
       }

       // Error #1
       if ((st.front() != pairs[j].first) && (!st.empty())) {
         int k;
         for (k = 0; k < i + spaces; ++k) {
           printf(" ");
         }
         for (k = 0; k < 4; ++k) {
           if (pairs[k].first == st.front())
             break;
         }
         printf("^ expecting %c\n", pairs[k].second);
         errorFree = false;
         break;
       }

       // Error #2
       else if (st.empty()) {
         for (int k = 0; k < i + spaces; ++k) {
           printf(" ");
         }
         printf("^ missing %c\n", pairs[j].first);
         errorFree = false;
         break;
       }
       else if (st.front() == pairs[j].first) {
         st.pop_front();
       }
     }
   }

   // Error #3
   if (!st.empty() && errorFree) {
     int m;
     for (m = 0; m <= i + spaces; ++m) {
       printf(" ");
     }
     printf("^ missing ");
     while(!st.empty()) {
       for (m = 0; m < 4; ++m) {
         if (pairs[m].first == st.front())
           break;
       }
       printf("%c ", pairs[m].second);
       st.pop_front();
     }
     printf("\n");
     errorFree = false;
   }
    
   // Expression is balanced if no errors were encountered
   if (errorFree) {
       return true;
   }
 return false;
}

#endif