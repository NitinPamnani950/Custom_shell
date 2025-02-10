#include <stdlib.h>
#include <stdio.h>
long long compute_factorial(int x);

int main(int argc, char *argv[]) {
    if (argc == 2) {
        int input_num = atoi(argv[1]); 

        if (input_num >= 0) {
            long long factorial_result = compute_factorial(input_num); 
            printf("Factorial of %d is = %lld\n", input_num, factorial_result);
            return 0;
        }
        else {
            fprintf(stderr, "Cannot compute Factorial of negative integer. So, Please Enter a non-negative integer.\n");
            return 1;
        }
    }
    else if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }
    return 0;
}

long long compute_factorial(int x) {
    long long result = 1;
    if(x == 0){
        return 1;
    }
    do{
        result *= x;
        x--;
    }while (x > 0);
    return result;
}
