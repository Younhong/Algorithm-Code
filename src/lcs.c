
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

void GenSeq(char* s, int n);
const int num_alphabet = 5;
void PrintSeq(char* s, int n);
int LCS(char* X, char* Y, int i, int j);
int LCS_Length(char* X, char* Y, int i, int j);
int** c;
int** b; // 0: '↖', -1: '↑', 1: '←'
void PRINT_LCS(char* X, int i, int j);
int FindMax(int a, int b);
void GET_ALL_LCSs(int* index1, int* index2, char* X, int i, int j);
void PRINT_ALL_LCSs2(int index1);
void PRINT_ALL_LCSs(char* X, int i, int j);
int GetCurrentUsec();
int count = 1;
char temp[20][4] = {""};

int main(void) { 
  int i = 6; // length of X
  int j = 7; // length of Y
  
  char* X, * Y; // sequences
  X = (char*)malloc(sizeof(char)*i);
  Y = (char*)malloc(sizeof(char)*j);

  c = (int**)malloc(sizeof(int*)*(i+1));
  for (int k=0; k<i+1; k++) c[k] = (int*)malloc(sizeof(int)*(j+1));
  b = (int**)malloc(sizeof(int*)*(i+1));
  for (int k=0; k<i+1; k++) b[k] = (int*)malloc(sizeof(int)*(j+1));
  
  srand(time(NULL));
  GenSeq(X, i);
  GenSeq(Y, j);
  // runs fine with those cases
  // X = "BDCABA";
  // Y = "ABCBDAB";
  
  PrintSeq(X, i);
  PrintSeq(Y, j);

  int t1, t2, result;

  // Divide and Conquer
  t1 = GetCurrentUsec();
  result = LCS(X, Y, i, j);
  t2 = GetCurrentUsec();
  printf("Then length of LCS is %d.\n", result);
  printf("Divide and Conquer took %d usec.\n", t2-t1);

  // Dynaic Programming
  t1 = GetCurrentUsec();
  result = LCS_Length(X, Y, i, j);
  t2 = GetCurrentUsec();
  printf("Then length of LCS is %d.\n", result);
  printf("Dynamic Programming took %d usec.\n", t2-t1);
  
  printf("<");
  PRINT_LCS(X, i, j);
  printf(">\n");

  int index1 = 0;
  int index2 = 0;
  // additional point: see the assignment description
  printf("Printing Out All LCS\n");
  // Getting all cases
  for (int k = 0; k < count; k++) {
    printf("<");
    PRINT_ALL_LCSs(X, i, j);
    printf(">\n");
  }
  
  /* 
  Removing Duplicates -> 
    Partially done but not for all cases
    So, commented out for temporally
  */
  // for (int k = 0; k < count * 2; k++) {
  //   // printf("<");
  //   GET_ALL_LCSs(&index1, &index2, X, i, j);
  //   index1++;
  //   // printf(">\n");
  // }
  
  // // removing duplicates
  // PRINT_ALL_LCSs2(index1);
  
  return 0;
}

//////////////////////////////
//  write your answer below //
//////////////////////////////
/*

for i = 2, j = 2
Divide and Conquer took : 1 usec.
Dynamic Programming took : 0 usec.

for i = 5, j = 5
Divide and Conquer took : 2 usec.
Dynamic Programming took : 1 usec.

for i = 10, j = 10
Divide and Conquer took : 400 usec.
Dynamic Programming took : 3 usec.

for i = 15, j = 15
Divide and Conquer took : 50000 usec.
Dynamic Programming took : 7 usec.

*/
//////////////////////////////


int LCS(char* X, char* Y, int i, int j)
{
  int c;
  if ((i==0) || (j==0))
    c = 0;
  else if (X[i-1] == Y[j-1])
    c = LCS(X, Y, i-1, j-1) + 1;
  else
    c = FindMax(LCS(X, Y, i-1, j), LCS(X, Y, i, j-1));
    
  return c;
}

int FindMax(int a, int b)
{
  if (a >= b) 
    return a;
  else
    return b;
}

int LCS_Length(char* X, char* Y, int i, int j)
{
  for (int k=0; k<i+1; k++) c[k][0] = 0;
  for (int k=0; k<j+1; k++) c[0][k] = 0;

  for (int x = 1; x <= i; x++) {
    for (int y = 1; y <= j; y++) {
      if (X[x-1] == Y[y-1]) {
        c[x][y] = c[x-1][y-1] + 1;
        b[x][y] = 0;
      }
      else if (c[x-1][y] >= c[x][y-1]) {
        c[x][y] = c[x-1][y];
        b[x][y] = -1;
      }
      else if (c[x-1][y] < c[x][y-1]) {
        c[x][y] = c[x][y-1];
        b[x][y] = 1;
      };
    }
  }
  
  return c[i][j];
}

void PRINT_ALL_LCSs(char* X, int i, int j) {
  if ((i==0) || (j==0)) return;
  /// X[x-1] == Y[y-1]
  if (b[i][j] == 0) {
    PRINT_ALL_LCSs(X, i-1, j-1);
    printf("%c, ", X[i-1]);
  }
  /// c[x-1][y] > c[x][y-1]
  else if (b[i][j] == -1) {
    PRINT_ALL_LCSs(X, i-1, j);
    if (c[i-1][j] == c[i][j-1]) {
      b[i][j] = 1;
    }
  }
  /// c[x-1][y] < c[x][y-1]
  else if (b[i][j] == 1) {
    PRINT_ALL_LCSs(X, i, j-1);
    if (c[i-1][j] == c[i][j-1]) {
      b[i][j] = -1;
    }
  }
  
  return;
}

void GET_ALL_LCSs(int* index1, int* index2, char* X, int i, int j) {
  if ((i==0) || (j==0)) return;
  /// X[x-1] == Y[y-1]
  if (b[i][j] == 0) {
    GET_ALL_LCSs(index1, index2, X, i-1, j-1);

    temp[*index1][*index2] = X[i-1];
    *index2 = *index2 + 1;
    //printf("%d %d %c, ", *index1, *index2, temp[*index1][*index2-1]);
  }
  /// c[x-1][y] > c[x][y-1]
  else if (b[i][j] == -1) {
    GET_ALL_LCSs(index1, index2, X, i-1, j);
    if (c[i-1][j] == c[i][j-1]) {
      b[i][j] = 1;
    }
  }
  /// c[x-1][y] < c[x][y-1]
  else if (b[i][j] == 1) {
    GET_ALL_LCSs(index1, index2, X, i, j-1);
    if (c[i-1][j] == c[i][j-1]) {
      b[i][j] = -1;
    }
  }
  
  return;
}

void PRINT_ALL_LCSs2(int index1) {
  int isDuplicated = 0;
  printf("%s",temp[0]);
  
  for (int i = 1; i < index1;i++) {
    // isDuplicated = 0 -> Not repeated
    isDuplicated = 0;
    for (int j = i-1; j >= 0; j--) {
      // if dupulicated
      if (strcmp(temp[i], temp[j]) == 0) {
        isDuplicated = 1;
        continue;
      }
      else if(strcmp(temp[i], temp[j]) != 0)  {
        isDuplicated = 0;
      }
    }
    if (isDuplicated == 0) {
      printf(" %s", temp[i]);
    }
  }
  
  return;
}

void PRINT_LCS(char* X, int i, int j)
{
  if ((i==0) || (j==0)) return;
  if (b[i][j] == 0) {
    PRINT_LCS(X, i-1, j-1);
    printf("%c, ", X[i-1]);
  }
  else if (b[i][j] == -1) {
    if (c[i-1][j] == c[i][j-1]) {
      count++;
    }
    PRINT_LCS(X, i-1, j);
  }
  else if (b[i][j] == 1)
    PRINT_LCS(X, i, j-1);
    
  return;
}

int GetCurrentUsec()
{
  struct timeval tv;
  gettimeofday(&tv,NULL);
  
  return tv.tv_usec;
}

void GenSeq(char* s, int n)
{
  for (int i=0; i<n; i++)
  {
    s[i] = (char)((random() % num_alphabet)+ 'A');
  }
  return;
}

void PrintSeq(char* s, int n)
{
  printf("<");
  for (int i=0; i<n; i++)
  {
    printf("%c, ", s[i]);
  }
  printf(">\n");
  return;
}