//
//  structs.c
//  p_avanzada
//
//  Created by JOSELO on 9/17/15.
//  Copyright (c) 2015 Josel0. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char *name;
    int age;
    int height;
    int weight;
};

struct Person *Person_create(char *name, int age, int height, int weight)
{
    struct Person *who = malloc(sizeof(struct Person));
    assert(who != NULL);
    
    who->name = strdup(name);
    who->age = age;
    who->height = height;
    who->weight = weight;
    
    return who;
}



void Person_destroy(struct Person *who)
{
    assert(who != NULL);
    
    free(who->name);
    free(who);
}

void Person_print(struct Person *who)
{
    printf("Name: %s\n", who->name);
    printf("\tAge: %d\n", who->age);
    printf("\tHeight: %d\n", who->height);
    printf("\tWeight: %d\n", who->weight);
}

int main(int argc, char *argv[])
{
    // make two people structures
    struct Person *joe = Person_create("Joe Alex", 32, 64, 140);
    
    struct Person *frank = Person_create("Frank Blank", 20, 72, 180);
    
    struct Person* arreglo = (struct Person*)malloc(3*(sizeof(struct Person)));
    int edad=0;
    int heigth=0;
    int weight =0;
    
    *(arreglo)=*Person_create("p1", edad, heigth, weight);
    *(arreglo+1)=*Person_create("p2", edad, heigth, weight);
    *(arreglo+2)=*Person_create("p3", edad, heigth, weight);
    
    // print them out and where they are in memory
    printf("Joe is at memory location %p:\n", joe);
    Person_print(joe);
    
    printf("Frank is at memory location %p:\n", frank);
    Person_print(frank);
    
    // make everyone age 20 years and print them again
    joe->age += 20;
    joe->height -= 2;
    joe->weight += 40;
    Person_print(joe);
    
    frank->age += 20;
    frank->weight += 20;
    Person_print(frank);
    
    // destroy them both so we clean up
    Person_destroy(joe);
    Person_destroy(frank);
    
    printf("con aa\n");
    Person_print(arreglo);
    Person_print((arreglo+1));
    Person_print((arreglo+2));
    
    return 0;
}