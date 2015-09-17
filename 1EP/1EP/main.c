//
//  main.c
//  1EP
//
//  Created by Jose Luis Garcia R on 9/17/15.
//  Copyright (c) 2015 Josel0. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 50
#define N 25
#define L 200
#define O 400
#define P 100


//Declaracion de Estructuras
typedef struct
{
    char *tipo;
    int  niveles;
    int  *val_modales;
    int  periodo;
    int  ad_edif;
    int  *ad_torres;
    char *ad_nave;
} edificacion;

typedef struct{
    char *nombre;
    char *apellidos;
    int  num_nomina;
    char *fecha_nac;
    char *fecha_ingr;
    int  salario;
    char *puesto;
    edificacion *edif;
    
}trabajador;

//Declaración de Métodos
trabajador* addtrab(trabajador* trab, edificacion* edi, int * pobtrab, int * pobedifs);
edificacion* addedificacion(edificacion* edi, int * pobtrab, int * pobedifs);
void printtrab(trabajador* trab);
void printedifs(edificacion* edi, trabajador* trab);


int main(int argc, const char * argv[]) {
    int op=0;
    int init         = 1;
    int * pobtrab    = &init;
    int * pobedifs   = &init;
    
    edificacion *edi = (edificacion *)malloc(sizeof(edificacion)); //variable donde se guardaran todas las edificaciones
    
    char * inicio    = (char *)malloc( sizeof(char)* L);
    strcpy(inicio,"Para iniciar se agregará una edificación a la BD.\nEsto para agregar trabajadores a alguna edificación.\n");
    printf("%s",inicio);
    
    edi              = addedificacion(edi, pobtrab, pobedifs);
    
    trabajador *trab = (trabajador *)malloc(sizeof(trabajador)); // variable donde se guardaran los trabajadores
    strcpy(inicio,"Ahora se agregará un trabajador a esta edificacion.\n");
    printf("%s",inicio);
    
    trab=addtrab(trab, edi, pobtrab, pobedifs);
    
    char * menu = (char *)malloc(sizeof(char)* O);
    strcpy(menu,"\n::::\tMenu Principal\t::::\n1. Nueva Edificación\n2. Nuevo trabajador\n3. Visualizar Edificaciones con trabajadores\n4.Visualizar trabajadores\n5. Salir\n\nFavor de ingresar una opción.\n");
    
    while(op!=5)
    {
        printf("%s",menu);
        scanf("%d", &op);
        switch(op)
        {
            case 1:
                edi  = addedificacion(edi, pobtrab, pobedifs);
                break;
            case 2:
                trab = addtrab(trab, edi, pobtrab, pobedifs);
                break;
            case 3:
                printedifs(edi, trab);
                break;
            case 4:
                printtrab(trab);
                break;
            case 5:
                printf("Finalizando programa. Gracias por utilizarlo.");
                break;
            default:
                printf("Opcion no valida, favor de ingresar otra opción");
                break;
        }
    }
    free(edi);
    free(trab);
    return (EXIT_SUCCESS);
}


trabajador* addtrab(trabajador *trab, edificacion *edi, int * pobtrab, int * pobedifs)
{
    int i, false=0, cancel=0;
    trabajador * temp;
    temp = trab;
    temp = (trabajador *)realloc(trab, sizeof(trabajador)*(*pobtrab));
    if(temp==NULL)
    {
        printf("Lo sentimos, ya no hay memoria para agregar trabajadores.");
        return trab;
    }
    trab = temp;
    free(temp);
    

    (trab + (*pobtrab))->nombre = (char * ) malloc(sizeof(char) * M);
    printf("Ingrese el nombre del trabajador. ");
    scanf("%s",(trab + (*pobtrab))->nombre);

    (trab + (*pobtrab))->apellidos = (char * ) malloc(sizeof(char) * M);
    printf("Ingrese los apellidos del trabajador. ");
    scanf("%s",(trab + (*pobtrab))->apellidos);

    printf("Ingrese el número de nómina del trabajador. ");
    scanf("%d",&((trab + (*pobtrab))->num_nomina));
  
    /*
    char *nombre;
    char *apellidos;
    int  num_nomina;
    char *fecha_nac;
    char *fecha_ingr;
    int  salario;
    char *puesto;
    edificacion *edif;
*/

    printf("Ingrese el rol del trabajador. ");
    scanf("%s",(trip+pobtrab)->rol);
    while(false==0||cancel==0)
    {
        printf("Ingrese a qué edificacion pertenece este trabajador.");
        scanf("%s",(trip+*pobtrab)->br.nombre);
        for(i=0;i<(*pobedifs);++i)
        {
            if((edi+i)->tipo == (trab+(*pobtrab))->br.tipo)
            {
                if((edi+i)->maxtrabajadores!=(emb+i)->conteo)
                {
                    ++(edi+i)->conteo;
                    false==1;
                }
                else
                {
                    printf("Esta edificacion ya no cuenta con lugares");
                    printf("Si desea eliminar este trabajador para agregar primero la edificacion, oprima 0");
                    scanf("%d",&cancel);
                    cancel==1;
                }
            }
            if(i==(pobbar-1))
            {
                printf("La edificacion no se encontro, se cancelará este trabajador ");
                cancel==1;
                break;
            }
        }
    }
    if(cancel==1)
    {
        trab = (trabajador *)realloc(trip, sizeof(trabajador)*(*pobtrab-1));
        return trab;
    }
    ++pobtrab;
    return trab;
}
