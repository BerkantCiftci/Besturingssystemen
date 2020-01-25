/*
 * Berkant Ciftci
 * 0979368
 * TINBES-01
 * TI1D
 */ 


// Copyright: GEATEC engineering
// License: Apache 2

// To compile:
// gcc race_prio.c -l pthread -o race_prio

#include <pthread.h>
#include <sched.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


// ============ Car type and what you can do with cars

typedef struct
{

    // Things that pertain to cars
    char name[256];
    double distPerRev;
    double position;
    bool brake; 

    // Things that pertain to real time computer simulations
    int priority;
    pthread_t threadId;
} Car;

Car *constructCar(char *name, double distPerRev, int priority)
{
    Car *result = (Car *)malloc(sizeof(Car));

    strcpy(result->name, name);
    result->position = 0;
    result->distPerRev = distPerRev;
    result->brake = true;

    result->priority = priority;
    result->threadId = 0; // As a good habit, initialize all variables

    return result;
}

void destroyCar(Car *car)
{
    free(car);
}

void *driveCar(void *carrish)
{                              // Thread function MUST have void parameter
    Car *car = (Car *)carrish; // Avoid void as much as possible, so convert to decent type
    while (!car->brake)
    {
        // Update position with distance per revolution
        car->position += car->distPerRev;
    }
    return 0;
}

void startCar(Car *car)
{
    pthread_attr_t threadAttributes;
    struct sched_param schedulingParameters;

    // TO DO
    pthread_attr_init(&threadAttributes); // Initialize thread attributes

    // Set round robin scheduling
    pthread_attr_setschedpolicy(&threadAttributes, SCHED_RR);

    // Get current scheduling parameters from thread attributes
    pthread_attr_getschedparam(&threadAttributes, &schedulingParameters);

    // Modify priority field of scheduling parameters
    schedulingParameters.sched_priority = car->priority; // replace xxx with desired priority

    // Store new scheduling parameters in thread attributes
    pthread_attr_setschedparam(&threadAttributes, &schedulingParameters);

    car->brake = false;
    pthread_create(&car->threadId, &threadAttributes, driveCar, car); // Create thread with right priority
}

void finishCar(Car *car)
{
    car->brake = true;
    pthread_join(car->threadId, 0);
}

// ============ Create two cars and have them race against each other

int main()
{
    // Get min and max priority values
    int schedMin = sched_get_priority_min(SCHED_RR);
    int schedMax = sched_get_priority_max(SCHED_RR);
    printf("min: %d\nmax: %d\n", schedMin, schedMax);

    // Make two cars on the heap
    Car *electricCar = constructCar("Tesla", 0.001, schedMin);    // Maximum priority
    Car *combustionCar = constructCar("Jaguar", 0.001, schedMax); // Minimum priority

    // Start their threads
    startCar(electricCar);
    startCar(combustionCar);

    printf("Race started\n");

    // Report how they're doing
    for (int sampleIndex = 0; sampleIndex < 10; sampleIndex++)
    {
        printf(
            "Index: %d\t\t%s pos: %10.2f\t\t%s pos: %10.2f\n", sampleIndex,

            electricCar->name,
            electricCar->position,

            combustionCar->name,
            combustionCar->position);
        sleep(1);
    }

    // Wait for their threads to end
    finishCar(electricCar);
    finishCar(combustionCar);

    printf("Race finished. %s wins!\n",
           electricCar->position > combustionCar->position ? electricCar->name : combustionCar->name);

    // Clean up the (scrap)heap
    destroyCar(electricCar);
    destroyCar(combustionCar);

    return 0;
}
