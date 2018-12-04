/* CS261- Assignment 1 - Q.2*/
/* Name: Zachary Wetekamm
 * Date: 10/8/18
 * Solution description: Program demonstrates an address--not value--
 * swap for two pointers.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int foo(int* a, int* b, int c){

    /*Swap the addresses stored in the pointer variables a and b*/
    printf("Old addresses: a: %p, b: %p\n", a, b);
    // swap using a temporary pointer
    int *temp = a;
    a = b;
    b = temp;
    printf("New addresses: a: %p, b: %p\n", a, b);

    /*Decrement the value of integer variable c*/
    c--;

    /*Return c*/
    return c;
}

int main(){

    srand(time(NULL));

    /*Declare three integers x,y and z and initialize them randomly to values in [0,10] */
    int x = rand() % 11;
    int y = rand() % 11;
    int z = rand() % 11;

    /*Print the values of x, y and z*/
    printf("x = %d\n", x);
    printf("y = %d\n", y);
    printf("z = %d\n", z);
    
    /*Call foo() appropriately, passing x,y,z as parameters*/
    int value = foo(&x, &y, z);

    /*Print the values of x, y and z*/
    printf("After foo() call, x = %d\n", x);
    printf("After foo() call, y = %d\n", y);
    printf("After foo() call, z = %d\n", z);

    /*Print the value returned by foo*/
    printf("Value returned by foo(): %d\n", value);

    /* Is the return value different than the value of integer z?
     * Yes, because z was passed as an argument to the foo() function, but it's value
     * was not reassigned.  The foo() function uses and returns a different variable (c)
     * and the value of z remains unchanged.
     *
     * Are the values of integers x and y different before and after calling foo()?
     * The values of x and y are unchanged because their addresses are passed as
     * arguments.  Inside the foo() function, pointers are used to swap the
     * addresses and not dereference the values of those pointers.
     */
    
    return 0;
}
    
    


