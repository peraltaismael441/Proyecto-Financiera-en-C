/*
NOMBRE y APELLIDO: ISMAEL PERALTA
TP FINAL INTEGRADOR LABORATORIO 2, AÑO 2023, PRIMER CUATRIMESTRE - ENTREGADO 20-06-2023
ARCHIVOS PARTE DEL PROGRAMA:
 - Documentacion (Resumen funciones)
 - MANUAL DE USUARIO - FINANCIERA EL VALLE
 - misfunciones.h
 - prestamos.csv
 - Ayudar y funtes:
 https://www.tutorialspoint.com/c_standard_library
 Material visto en clase Autora: Monica Hencek

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "misfunciones.h"



int main(){
    FILE * pA;
    FILE * pC;
    struct datos clientes;

            int control;
          Bienvenida();
        do{
            control = menu();
                    switch (control){
                        case 1: vista_datos_previos();
                            break;
                        case 2: crear_archivo_binario(pA, clientes);
                            break;
                        case 3: migrar_datos();
                            break;
                         case 4: vista_archivo_nuevo(clientes);
                            break;
                        case 5: ingresar_clientes(pC,clientes);
                            break;
                        case 6: busqueda(pC,clientes);
                            break;
                        case 7: modificar(pC,clientes);
                            break;
                        case 8: baja_logica(pC,clientes);
                            break;
                        case 9: baja_fisica(pC,clientes);
                            break;
                             }

            }while (control!=0);

        printf("\n *** PROGRAMA FINALIZADO ***\n");

return 0;
}




