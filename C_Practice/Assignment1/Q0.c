/* CS261- Assignment 1 - Q. 0*/
/* Name: Zachary Wetekamm
 * Date: 10/8/18
 * Solution description: Program uses two functions to manipulate
 * pointer values.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fooA(int *iptr){

    /*Print the value and address of the integer pointed to by iptr*/
    printf("Value of the integer pointed to by iptr: %d\n", *iptr);
    printf("Address of the integer pointed to by iptr: %p\n", iptr);

    /*Increment the value of the integer pointed to by iptr by 5*/
    *iptr += 5;

    /*Print the address of iptr itself*/
    printf("The address of iptr: %p\n", &iptr);
}


void fooB(int *jptr){

    /*Print the value and address of the integer pointed to by jptr*/
    printf("Value of integer pointed to by jptr: %d\n", *jptr);
    printf("Address of integer pointed to by jptr: %p\n", jptr);

    /*Decrement jptr by 1*/
    --*jptr;

    /*Print the address of jptr itself*/
    printf("Address of jptr: %p\n", &jptr);
}


int main(){

    srand(time(NULL));

    /*Declare an integer x and initialize it randomly to a value in [0,10] */
    int x = rand() % 11;

    /*Print the value and address of x*/
    printf("Value of x: %d\n", x);
    printf("Address of x: %p\n", &x);

    /*Call fooA() with the address of x*/
    fooA(&x);

    /*Print the value of x*/
    printf("Value of x after fooA() call: %d\n", x);

    /*Call fooB() with the address of x*/
    fooB(&x);

    /*Print the value and address of x*/
    printf("Value of x after fooB() call: %d\n", x);
    printf("Address of x after fooB() call: %p\n", &x);

    /* Are the value and address of x different than the value and address
     * that were printed before the call to fooB()? Why or why not?
     *
     * Only the value is different because the function directly changes
     * the pointer value.  The address does not change.
     */

    return 0;
}
