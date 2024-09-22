#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

typedef unsigned long long (*Fib_Func)(int fib_index);

int read_file_int(char file_name[40]);
unsigned long long fibonacci_memoization(Fib_Func chosen_func, int fib_index);
unsigned long long fibonacci_iterative_core(int n);
unsigned long long fibonacci_recursive_core(int n);

unsigned long long fib_num[100] = {0};

/*
      INPUT: An integer, a character (r or i), and the name of a text file
      consisting of an integer

      OUTPUT: The Nth number of the fibonacci sequence (where N equals the sum
      of the two input integers), calculated using a recursive or iterative
      method depending in the input character.
*/
int main(int argc, char *argv[]) {

   int input_num;
   char input_char;
   char file_name[40];

   sscanf(argv[1], "%d", &input_num);
   sscanf(argv[2], "%c", &input_char);
   sscanf(argv[3], "%s", file_name);

   int file_num = read_file_int(file_name);
   int sum = input_num + file_num;
   unsigned long long result;

   if (input_char == 'i') {
      result = fibonacci_memoization(*fibonacci_iterative_core, sum);
   }
   else if (input_char == 'r') {
      result = fibonacci_memoization(*fibonacci_recursive_core, sum);
   }
   else {
      printf("Error: Input invalid.");
      exit(0);
   }

   printf("%" PRId64 "\n", result);

   return 0;
}


//Reads file consisting of 1 integer and returns value
int read_file_int(char file_name[40]) {
   FILE* file_pointer;
   file_pointer = fopen(file_name, "r");

   if (file_pointer == NULL) {
        printf("File could not be opened. Exiting program.");
        exit(0);
    }

   char file_data[10];
   fscanf(file_pointer, "%s", file_data);
   int file_num = atoi(file_data);

   fclose(file_pointer);

   return file_num;
}


//Uses memoization to recall values previously obtained, calling core fibonacci function if not calculated yet
unsigned long long fibonacci_memoization(Fib_Func chosen_func, int fib_index) {

    if (fib_num[fib_index] == 0) {
        fib_num[fib_index] = (*chosen_func)(fib_index);
    }
    return fib_num[fib_index];
}


//Computes Nth number in fibonacci series using an iterative technique
unsigned long long fibonacci_iterative_core(int n) {
   unsigned long long num1 = 0;
   unsigned long long num2 = 1;

   for (int i = 2; i < n; i++) {
      unsigned long long temp = num1 + num2;
      num1 = num2;
      num2 = temp;
   }

   return num2;
}


//Computes Nth number in fibonacci series using a recursive technique
unsigned long long fibonacci_recursive_core(int n) {

   if (n == 1) {
      return 0;
   }
   else if (n == 2) {
      return 1;
   }

   return fibonacci_memoization(*fibonacci_recursive_core, n-1) + fibonacci_memoization(*fibonacci_recursive_core, n-2);
}
