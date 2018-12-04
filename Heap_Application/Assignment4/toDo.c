/*
 * CS 261 Assignment 4
 * Name: Zachary Wetekamm
 * Date: 11/19/18
 */

#include "dynamicArray.h"
#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Loads into heap a list from a file with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listLoad(DynamicArray* heap, FILE* file)
{
    const int FORMAT_LENGTH = 256;
    char format[FORMAT_LENGTH];
    snprintf(format, FORMAT_LENGTH, "%%d, %%%d[^\n]", TASK_NAME_SIZE);

    Task temp;
    while (fscanf(file, format, &temp.priority, &temp.name) == 2)
    {
        dyHeapAdd(heap, taskNew(temp.priority, temp.name), taskCompare);
    }
}

/**
 * Writes to a file all tasks in heap with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listSave(DynamicArray* heap, FILE* file)
{
    for (int i = 0; i < dySize(heap); i++)
    {
        Task* task = dyGet(heap, i);
        fprintf(file, "%d, %s\n", task->priority, task->name);
    }
}

/**
 * Prints every task in heap.
 * @param heap
 */
void listPrint(DynamicArray* heap)
{
    DynamicArray* temp = dyNew(1);
    dyCopy(heap, temp);
    while (dySize(temp) > 0)
    {
        Task* task = dyHeapGetMin(temp);
        printf("\n");
        taskPrint(task);
        printf("\n");
        dyHeapRemoveMin(temp, taskCompare);
    }
    dyDelete(temp);
}

/**
 * Handles the given command.
 * @param list
 * @param command
 */
void handleCommand(DynamicArray* list, char command)
{
    char *fileName = malloc(sizeof(char) * 256);
    char *newTask = malloc(sizeof(char) * 256);
    int priority;

    switch(command) {
        case 'l':
            printf("Enter the file name to load: ");
            fgets(fileName, 100, stdin);

            // Establish the 0 terminator
            if (fileName[strlen(fileName) - 1] == '\n') {
                fileName[strlen(fileName) - 1] = 0;
            }

            FILE *read = fopen(fileName, "r");
            listLoad(list, read);

            printf("The list has loaded from the file.\n");
            fclose(read);
            break;

        case 's':
            printf("Enter the file name to save: ");
            fgets(fileName, 100, stdin);

            // Establish the 0 terminator
            if (fileName[strlen(fileName) - 1] == '\n') {
                fileName[strlen(fileName) - 1] = 0;
            }

            FILE *write = fopen(fileName, "w");
            listSave(list, write);

            printf("The list has saved to the file '%s'.\n", fileName);
            fclose(write);
            break;

        case 'a':
            printf("Enter a description of the new task: ");
            fgets(newTask, 100, stdin);

            if (newTask[strlen(newTask) - 1] == '\n') {
                newTask[strlen(newTask) - 1] = 0;
            }

            printf("Enter the task priority: ");
            scanf("%d", &priority);
            while (getchar() != '\n');
            Task *task = taskNew(priority, newTask);

            dyHeapAdd(list, task, taskCompare);

            printf("'%s' has been added to the task list.\n", newTask);
            break;

        case 'g':
            if (dySize(list) == 0) {
                printf("The list is empty.\n");
            } else {
                printf("The first task is: %s\n", ((struct Task*)dyHeapGetMin(list))->name);
            }
            break;

        case 'r':
            if (dySize(list) == 0) {
                printf("The list is empty.\n");
            } else {
                struct Task *temp = (struct Task*)dyHeapGetMin(list);
                dyHeapRemoveMin(list, taskCompare);
                taskDelete(temp);

                printf("The first task has been removed.\n");
            }
            break;

        case 'p':
            if (dySize(list) == 0) {
                printf("The list is empty.\n");
            } else {
                listPrint(list);
            }
            break;

        case 'e':
            printf("Exiting...\n");
            break;
    }

    free(fileName);
    free(newTask);
}

int main()
{
    // Implement
    printf("\n\n** TO-DO LIST APPLICATION **\n\n");
    DynamicArray* list = dyNew(8);
    char command = ' ';
    do
    {
        printf("Press:\n"
               "'l' to load to-do list from a file\n"
               "'s' to save to-do list to a file\n"
               "'a' to add a new task\n"
               "'g' to get the first task\n"
               "'r' to remove the first task\n"
               "'p' to print the list\n"
               "'e' to exit the program\n"
        );
        command = getchar();
        // Eat newlines
        while (getchar() != '\n');
        handleCommand(list, command);
    }
    while (command != 'e');
    dyDelete(list);
    return 0;
}
