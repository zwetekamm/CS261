/* CS261- Assignment 1 - Q.1*/
/* Name: Zachary Wetekamm
 * Date: 10/8/18
 * Solution description: Program generates a struct of 10 students, each
 * with a unique id and random test score.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct student{
	int id;
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
     struct student *stud = (struct student*) malloc(10*(sizeof(struct student)));

     /*Return the pointer*/
    return stud;
}

void generate(struct student* students){
    /*Generate random and unique IDs and random scores for ten students,
    IDs being between 1 and 10, scores between 0 and 100 */
    int i, temp;
    int flag = 1;

    // Random number 1-100 for score and initialize id
    for (int i = 0; i < 10; i++) {
        students[i].id = 0;
        students[i].score = rand() % 101;
    }

    i = 0;

    // using a flag variable, loop through the array
    // and create a random number; flag if already used
    while (i < 10) {
        temp = rand() % 10 + 1;

        for (int j = 0; j < 10; j++) {
            if (temp == students[j].id) {
                flag = 0;
                break;
            }
            else {
                flag = 1;
            }
        }

        if (flag == 1) {
            students[i].id = temp;
            i++;
        }
    }
}
void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
     for (int i = 0; i < 10; i++) {
         printf("ID%d  Score: %d\n", students[i].id, students[i].score);
     }
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
     int min, max, n;
     float avg;

     // placeholders
     min = students[0].score;
     max = students[0].score;

     for (int i = 0; i < 10; i++) {

         // minimum score
         if (students[i].score < min) {
             min = students[i].score;
         }

         // maximum score
         if (students[i].score > max) {
             max = students[i].score;
         }

         // average score
         n += students[i].score;
     }

     // calculate average score
     avg = n / 10.0;

     // print min, max, and average
     printf("Minimum: %d\nMaximum: %d\nAverage: %f\n", min, max, avg);

}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
     if (stud != NULL) {
         free(stud);
     }
}

int main(){

    srand(time(NULL));

    struct student* stud = NULL;
    
    /*Call allocate*/
    stud = allocate();

    /*Call generate*/
    generate(stud);

    /*Call output*/
    output(stud);

    /*Call summary*/
    summary(stud);

    /*Call deallocate*/
    deallocate(stud);

    return 0;
}

