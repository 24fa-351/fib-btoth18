#include <stdio.h>
#include <stdlib.h>

int read_file_int(char file_name[40]);
long fibonacci_iterative(int n);
long fibonacci_recursive(int n);

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
   long result;

   if (input_char == 'i') {
      result = fibonacci_iterative(sum);
   }
   else if (input_char == 'r') {
      result = fibonacci_recursive(sum);
   }
   else {
      printf("Error: Input invalid.");
      exit(0);
   }

   printf("%ld", result);

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


//Computes Nth number in fibonacci series using an iterative technique
long fibonacci_iterative(int n) {
   long num1 = 0;
   long num2 = 1;

   for (int i = 2; i < n; i++) {
      long temp = num1 + num2;
      num1 = num2;
      num2 = temp;
   }

   return num2;
}


//Computes Nth number in fibonacci series using a recursive technique
long fibonacci_recursive(int n) {

   if (n == 1) {
      return 0;
   }
   else if (n == 2) {
      return 1;
   }

   return fibonacci_recursive(n-1) + fibonacci_recursive(n-2);
}
