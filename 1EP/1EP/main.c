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
#define D 16
#define R 10


//Declaracion de Estructuras
typedef struct{
    char *nombre;
    char *tipo;
    int  niveles;
    int  *val_modales;
    int  periodo;
    int  ad_edif;
    int  *ad_torres;
    char *ad_nave;
    int  maxtrabajadores;
    int  conteo;
    int  ing_respon;
} edificacion;

typedef struct{
    char *nombre;
    char *apellidos;
    int  num_nomina;
    char *fecha_nac;
    char *fecha_ingr;
    int  salario;
    char *puesto;
    edificacion edif;
}trabajador;

//Declaración de Métodos
trabajador* addtrab(trabajador* trab, edificacion* edi, int * pobtrab, int * pobedifs);
edificacion* addedificacion(edificacion* edi, int * pobtrab, int * pobedifs);
void printtrab(trabajador* trab, int * pobtrab);
void printedifs(edificacion* edi, trabajador* trab, int * pobedifs, int * pobtrab);
//void buscarporfecha_t(trabajador * edi, char * fechas, int id, int * pobtrab)


int main(int argc, const char * argv[]) {
    int op=0, id = 0;
    char * fecha = (char *)malloc(sizeof(char) * R);
    int init         = 1;
    int * pobtrab    = &init;
    int * pobedifs   = &init;
    
    edificacion *edi = (edificacion *)malloc(sizeof(edificacion) * R); //variable donde se guardaran todas las edificaciones
    
    //char * inicio    = (char *)malloc( sizeof(char)* L);
    //strcpy(inicio,"Para iniciar se agregará una edificación a la BD.\nEsto para agregar trabajadores a alguna edificación.\n");
    //printf("%s",inicio);
    
    //edi              = addedificacion(edi, pobtrab, pobedifs);
    
    trabajador *trab = (trabajador *)malloc(sizeof(trabajador) * R); // variable donde se guardaran los trabajadores
    //strcpy(inicio,"Ahora se asignará el espacio para el primer trabajador a la primera edificación.\n");
    //printf("%s",inicio);
    
    //trab=addtrab(trab, edi, pobtrab, pobedifs);
    
    char * menu = (char *)malloc(sizeof(char)* O);
    strcpy(menu,"\n::::\tMenu Principal\t::::\n1. Nueva Edificación\n2. Nuevo trabajador\n3. Visualizar Edificaciones con trabajadores\n4.Visualizar trabajadores\n5. Salir\n\nFavor de ingresar una opción: ");
    
    while(op!=5){
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
                printedifs(edi, trab, pobedifs, pobtrab);
                break;
            case 4:
                printtrab(trab, pobtrab);
                break;
            case 5:
                printf("Finalizando menu. Gracias por utilizarlo.");
                break;
            default:
                printf("Opcion no valida, favor de ingresar otra opción");
                break;
        }
    }
    
    /*
    if(!fork()){
        //proceso hijo
        printf("Ver los modelos por numero de nomina\n");
        scanf("%d",&id);
        printf("Fecha en la que desea buscar formato dd-mm-yy\n");
        scanf("%s",fecha);
        buscarporfecha_t(edi,fecha,id, pobedifs);
        
        exit(0);
    }
    else{
        //proceso padre
        wait(0);
        
        printf("Ver los modelos por numero de nomina\n");
        scanf("%d",&id);
        printf("Fecha en la que desea buscar formato dd-mm-yy\n");
        scanf("%s",fecha);
        buscarporfecha_t(edi,fecha,id, pobedifs);

    }*/
    
    
    
    free(fecha);
    free(edi);
    free(trab);
    return (EXIT_SUCCESS);
}


trabajador* addtrab(trabajador *trab, edificacion *edi, int * pobtrab, int * pobedifs){

    trabajador * temp;
    temp = trab;
    
    int nuevot = (*pobtrab) + D;
    temp = (trabajador *)realloc(trab, nuevot * sizeof(trabajador));
    
    if(temp == NULL){
        printf("Lo sentimos, ya no hay memoria para agregar trabajadores.");
        return trab;
    }
    trab = temp;
    free(temp);
    

    (trab + (*pobtrab))->nombre = (char * ) malloc(sizeof(char) * M);
    printf("Ingrese el nombre del trabajador: ");
    scanf("%s",(trab + (*pobtrab))->nombre);

    (trab + (*pobtrab))->apellidos = (char * ) malloc(sizeof(char) * M);
    printf("Ingrese los apellidos del trabajador: ");
    scanf("%s",(trab + (*pobtrab))->apellidos);

    printf("Ingrese el número de nómina del trabajador: ");
    scanf("%d",&((trab + (*pobtrab))->num_nomina));
    
    (trab + (*pobtrab))->fecha_nac = (char * ) malloc(sizeof(char) * D);
    printf("Ingrese la fecha de nacimiento del trabajador [dd-mm-yy]: ");
    scanf("%s",(trab + (*pobtrab))->fecha_nac);
    
    (trab + (*pobtrab))->fecha_ingr = (char * ) malloc(sizeof(char) * D);
    printf("Ingrese la fecha de ingreso del trabajador [dd-mm-yy]: ");
    scanf("%s",(trab + (*pobtrab))->fecha_ingr);
    
    printf("Ingrese el salario del trabajador: ");
    scanf("%d",&((trab + (*pobtrab))->salario));
    
    (trab + (*pobtrab))->puesto = (char * ) malloc(sizeof(char) * N);
    printf("Ingrese el nombre del puesto del trabajador [Ing. Civil, Arquitecto, Técnico, Operador]: ");
    scanf("%s",(trab + (*pobtrab))->puesto);

    /*
    while(falso == 0 || cancel==0){
        ((trab + (*pobtrab))->edif.nombre) = (char * ) malloc(sizeof(char) * N);
        printf("Ingrese el nombre de la edificacion a la que pertenece este trabajador: ");
        scanf("%s",(trab + (*pobtrab))->edif.nombre);
        
        
        for(i = 0; i < ( *pobedifs-1); ++i){
            
            if((edi+i)->nombre == (trab +(*pobtrab))->edif.nombre){
                
                if((edi+i)->maxtrabajadores != (edi+i)->conteo){
                    
                    ++(edi+i)->conteo;
                    falso = 1;
                }
                else{
                    
                    printf("Esta edificacion ya no cuenta con lugares");
                    printf("Si desea eliminar este trabajador para agregar primero la edificacion, oprima 0");
                    scanf("%d",&cancel);
                    cancel = 1;
                }
            }
            if(i == ((*pobedifs)-1)){
                printf("La edificación no se encontró, se cancelará el registro de este trabajador ");
                cancel = 1;
                break;
            }
        }
    }
    if(cancel==1)
    {
        trab = (trabajador *)realloc(trab, sizeof(trabajador)*(*pobtrab-1));
        return trab;
    }
     */
    ++(*pobtrab);
    printf("Poblacion Trabajadores: %d ", *pobtrab);
    return trab;
}


edificacion* addedificacion(edificacion *edi, int * pobtrab, int * pobedifs){
    printf("Poblacion Edificaciones: %d ", *pobedifs);
    printf("Poblacion Trabajadores: %d ", *pobtrab);
    printf("\n");
    
    edificacion * temp;
    temp = edi;
    
    int nuevot = (*pobedifs) + R;
    temp = (edificacion *)realloc(edi, nuevot * sizeof(edificacion));
    
    if(temp == NULL){
        printf("Lo sentimos, ya no hay memoria para agregar edificaciones.");
        return edi;
    }
    
    edi = temp;
    free(temp);
    
    
    (edi + (*pobedifs))->nombre = (char * ) malloc(sizeof(char) * N);
    printf("Ingrese el nombre de la edificacion: ");
    scanf("%s",(edi + (*pobedifs))->nombre);
    
    (edi + (*pobedifs))->tipo = (char * ) malloc(sizeof(char) * D);
    printf("Ingrese el tipo de edificacion [edificio, torre, nave]: ");
    scanf("%s",(edi + (*pobedifs))->tipo);
    
    printf("Ingrese el número de niveles de la edificación: ");
    scanf("%d",&((edi + (*pobedifs))->niveles));
    
    int tam = (edi + (*pobedifs))->niveles;
    (edi + (*pobedifs))->val_modales = (int * ) malloc(sizeof(int) * tam );
    //*((aux)->modales)+i = 5+i;
    
    for (int j=0; j < (edi + (*pobedifs))->niveles; ++j) {
        printf("Valor modal del nivel %d: %d \n", j+1, 5+j);
        *((edi + (*pobedifs))->val_modales+j ) = 5 + j;
    }
    
    printf("Ingrese el periodo de la edificacion: ");
    scanf("%d",&((edi + (*pobedifs))->periodo));
    
    //Numero maximo de trabajadores por default
    ((edi + (*pobedifs))->maxtrabajadores ) = 5;
    
    //printf("Ingrese el número máximo de trabajadores [5]: ");
    //scanf("%d",&((edi + (*pobedifs))->maxtrabajadores));
    
    //conteo por default
    ((edi + (*pobedifs))->conteo) = 0;
   
    //printf("Ingrese la cantidad de trabajadores actuales [0]: ");
    //scanf("%d",&((edi + (*pobedifs))->conteo));

    char *tipo = (edi + (*pobedifs))->tipo;
    
    if( *tipo == 'e'){
        
        printf("Ingrese el tipo de edificación del Edificio Simétrico [0], Asimétrico[1]: ");
        scanf("%d",&((edi + (*pobedifs))->ad_edif));
        
        //valores default
        ((edi + (*pobedifs))->ad_torres) = 0;
        (edi + (*pobedifs))->ad_nave = (char * ) malloc(sizeof(char) * 1);
        *(edi + (*pobedifs))->ad_nave = '0';
        
    }else if (*tipo == 't'){
        //(edi + (*pobedifs))->niveles
        int * aux = (edi + (*pobedifs))->ad_torres;
        int tam = (edi + (*pobedifs))->niveles;
        tam *= tam;
        (edi + (*pobedifs))->ad_torres = (int * ) malloc(sizeof(int) * tam );
        int j = 0;
        while ( aux++ != '\0') {
            printf("Registrando diametro inferior de la torre: ");
            //scanf("%d",&((edi + (*pobedifs))->ad_edif));
            *((edi + (*pobedifs))->ad_torres + j ) = D;
            printf("Registrando diametro superior de la torre: ");
            //scanf("%d",&((edi + (*pobedifs))->ad_edif));
            *((edi + (*pobedifs))->ad_torres + j + 1 ) = N;
            j += 2;
        }
        
        //valores default
        ((edi + (*pobedifs))->ad_edif) = 0;
        (edi + (*pobedifs))->ad_nave = (char * ) malloc(sizeof(char) * 1);
        *(edi + (*pobedifs))->ad_nave = '0';
    
    }else if(*tipo == 'n'){
        
        (edi + (*pobedifs))->ad_nave = (char * ) malloc(sizeof(char) * D);
        printf("Ingrese el tipo de techo para la nave [Monitor, Dos Aguas, Creciente]: ");
        scanf("%s",(edi + (*pobedifs))->ad_nave);
 
        //valores default
        ((edi + (*pobedifs))->ad_edif) = 0;
        ((edi + (*pobedifs))->ad_torres) = 0;
    }
    
    if((*pobtrab)-1 != 0 ){
        printf("Ingrese el número de nómina del ingeniero o responsable a cargo: ");
        scanf("%d", &((edi + (*pobedifs))->ing_respon));
    }else{
        ((edi + (*pobedifs))->ing_respon) = 0;
    }
    
    free(tipo);
    
    *pobedifs = (*pobedifs)+1;
     printf("Poblacion Edificaciones: %d ", *pobedifs);
     printf("Poblacion Trabajadores: %d ", *pobtrab);
     printf("\n");
    
    
    return edi;
}


/*
void buscarporfecha_t(trabajador * edi, char * fechas, int id, int * pobtrab){
    //edificacion* aux = edi;
    trabajador * aux2 = trab;
    int i =0;
    while(i < (*pobtrab))
    {
        if(aux2->fecha == fechas && aux2->num_nomina == id)
        {
            if(aux2->type ==1)
            {
                printf("una torre de : %d pisos\n", aux2->torre->pisos);
            }else if(aux2->type ==2){
                printf("una torre de : 1 pisos\n");
            }else if(aux2->type ==3){
                printf("una torre de : %d pisos\n", aux2->edificio->pisos);
            }
        }
        i++;
        if(i<c)
        {aux++;}
    }
}*/


void printtrab(trabajador *trab, int * pobtrab )
{
    if((*pobtrab-1) != 0){
        int i;
        for(i = 0; i < (*pobtrab); ++i){
            printf("El trabajador se llama: %s %s\n",(trab+i)->nombre,(trab+i)->apellidos);
            printf("El número de nómina es: %d\n",(trab+i)->num_nomina);
            printf("El puesto del tripulante es: %s\n",(trab+i)->puesto);
            printf("Edificaciones a la que pertence es: %s\n\n",(trab+i)->edif.nombre);
        }
    }else{
        printf("No existen trabajadores guardados");
    }
    
    printf("\n\n");
    
    return;
}

void printedifs(edificacion * edi, trabajador *trab, int * pobedifs, int * pobtrab){
    
    if((*pobtrab -1) != 0){
    
     int i, j;
     for(i = 0; i < (*pobedifs); ++i){
        printf("El nombre del barco es: %s\n",(edi+i)->nombre);
        printf("El tipo de edificación es: %s\n",(edi+i)->tipo);
        printf("Los valores modales son:\n");
        int temp = (edi+i)->niveles;
        for( j = 0; j < temp; ++j){
            printf("Valor Modal %d.- %d",j+1,*(edi + i)->val_modales+j);
        }
        printf("El máximo número de trabajadores de la edificación es: %d\n",(edi+i)->maxtrabajadores);
        printf("La edificación lleva %d puestos asignados, los trabajadores son:\n",(edi+i)->conteo);
        if((edi+i)->conteo == 0){
            printf("No existen trabajadores en esta edificacion");
        }else if((edi+i)->conteo >1){
            for( j = 0; j < (*pobtrab); ++j){
                if((trab + j)->edif.nombre == (edi + i)->nombre)
                    printf("%d.- %s %s",j+1,(trab + j)->nombre,(trab + j)->apellidos);
            }
        }
        
     }
    }else{
        printf("No existen edificaciones guardadas");
    }
    
    printf("\n\n");
    return;
}