#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

void InsertionSort(int* A, int n);
void MergeSort(int* A, int left, int right);
void Merge(int* A, int left, int mid, int right);

void GenerateRamdomIntegers(int* A, int n);
bool IsSorted(int* A, int n, bool accedingOrder);
void CheckTheResult(int* A, int n, bool accendingOrder);
void PrintArray(int* A, int n);
int GetCurrentUsec();

int main(void){
  int n = 3000;
  int* A = (int*)malloc(n*sizeof(int));
  GenerateRamdomIntegers(A, n);
  
  // New Array to Copy and Keep The Original Value of Array Input
  int* B = (int*)malloc(n*sizeof(int));
  B = A;
  
  // int A[] = {31, 41, 59, 26, 41, 58};
  // int n = sizeof(A)/sizeof(A[0]);

  // print input
  printf("Input : ");
  PrintArray(A, n);
  CheckTheResult(A, n, true);
  // Below are codes to check if copied array is same as original array
  // printf("Temp input: ");
  // PrintArray(B, n);
  // CheckTheResult(B, n, true);
  
  int t1, t2, t3, t4;
  float ratio;

  // Insertion Sort
  // With Original Array A
  t1 = GetCurrentUsec();
  InsertionSort(A, n);
  t2 = GetCurrentUsec();
  printf("Output : ");
  PrintArray(A, n);
  CheckTheResult(A, n, true);
  printf("It took %d usec\n", t2-t1);

  // Merge Sort
  // With Copied Array B
  t3 = GetCurrentUsec();
  MergeSort(B, 0, n-1);
  t4 = GetCurrentUsec();
  printf("Output : ");
  PrintArray(B, n);
  CheckTheResult(B, n, true);
  printf("It took %d usec\n", t4-t3);
  
  ratio = (float)(t4-t3) / (t2-t1);
  
  printf("Ratio of processing times of the two sorting functions: %.2f", ratio);

  return 0;
}

void GenerateRamdomIntegers(int* A, int n)
{
  srand(time(NULL));
  for (int i=0; i<n; i++)
  {
    A[i] = rand() %100;
  }
  return;
}

void InsertionSort(int* A, int n)
{
  int key;
  // implement your code here
  for (int j = 1; j < n; j++) {
    key = A[j];
    int i = j-1;
    while (i >= 0 && A[i] > key) {
      A[i+1] = A[i];
      i--;
    }
    A[i+1] = key;
  }
  return;
}

void MergeSort(int* A, int left, int right)
{
  int mid;
  // implement your code here
  if (left < right) {
    mid = floor((left + right) / 2);
    MergeSort(A, left, mid);
    MergeSort(A, mid + 1, right);
    Merge(A, left, mid, right);
  }
  return;
}

void Merge(int* A, int left, int mid, int right)
{
  // implement your code here
  int n1 = mid - left + 1;
  int n2 = right - mid;
  
  int* L = (int*)malloc((n1+1)*sizeof(int));
  int* R = (int*)malloc((n2+1)*sizeof(int));
  for (int i = 0; i < n1; i++) {
    L[i] = A[left + i];
  }
  for (int j = 0; j < n2; j++) {
    R[j] = A[mid + j + 1];
  }
  L[n1] = 1000000;
  R[n2] = 1000000;
  int i = 0, j = 0;
  for (int k = left; k <= right; k++) {
    if (L[i] <= R[j]) {
      A[k] = L[i];
      i++;
    }
    else {
      A[k] = R[j];
      j++;
    }
  }
  
  return;
}

void PrintArray(int* A, int n)
{
  printf("{");
  for (int i=0; i<n; i++)
  {
    printf("%d, ", A[i]);
  }
  printf("}\n");
}

int GetCurrentUsec()
{
  struct timeval tv;
  gettimeofday(&tv,NULL);
  return tv.tv_usec;
}

void CheckTheResult(int* A, int n, bool acsendingOrder)
{
  printf("The result is ");
  if(!IsSorted(A, n, true)) printf("not ");
  printf("sorted in ascending order.\n");
  return;
}

bool IsSorted(int* A, int n, bool acsendingOrder)
{
  for(int i=0; i<n-1; i++)
  {
    if(acsendingOrder)
    {
      if (A[i] > A[i+1]) return false;
    }
    else
    {
      if (A[i] < A[i+1]) return false;
    }
  }
  return true;
}