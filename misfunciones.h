#ifndef _MISFUNCIONES_H_
#define _MISFUNCIONES_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
//#include <math.h> no la use
// math.h la uso para usar la funcion isnan  y ver si el valor ingresado es un numero o no (no me funciono, no la use)
#define IVA 0.21


struct datos{ //STRUCT DE TODA LA DATA DEL CVS + ANIDAMIENTO DE STRUCTS

    int orden; // UBICACION EN LA LISTA
    char nombre[40];
    char apellido[40];
    float importe; // IMPORTE DEL CREDITO
    char tipoCred[20]; // 2 opciones "CON GARANTIA" o "A SOLA FIRMA"
    int dia;
    char mes[4];
    int anio;
    int nroCuotas;
    float importeCuotas;
    float iva; // 21% al importe de cuotas
    float totalCuota;
    int activo;
};






int menu(){

    int control;

    printf("\n\n Operaciones disponibles:\n ");
    printf("\n 1: DATOS CARGADOS PREVIAMENTE.");
    printf("\n 2: CREAR NUEVO ARCHIVO CREDITOS.");
    printf("\n 3: MIGRAR DATOS PREVIOS AL NUEVO ARCHIVO.");
    printf("\n 4: VISUALIZAR LISTADO DE CLIENTES.");
    printf("\n 5: INGRESAR NUEVOS DATOS.");
    printf("\n 6: BUSCAR.");
    printf("\n 7: MODIFICACIONES.");
    printf("\n 8: BAJA LOGICA.");
    printf("\n 9: BAJA FISICA.");
    printf("\n 0: FINALIZAR PROGRAMA.\n");
    printf("\n Operacion a realizar: ");
    scanf("%d",&control);

        while (control<0||control>9){
                printf("\n\n Opcion no valida. Vuelva elija una de las opciones disponibles: ");
                scanf("%d",&control);
                }
        getchar();
return control;
}

void Bienvenida(){

    printf("\n -----------------------------------------------");
    printf("\n |               Bienvenido/a!                 |");
    printf("\n |     Ingreso al archivo de altas, bajas,     |");
    printf("\n |   modificaciones y listados de la Finaciera |");
    printf("\n -----------------------------------------------");
}

// VISUALIZA ARCHIVO CSV
void vista_datos_previos(){
    FILE *pA;
    char linea[200];
    char *aux; // tiene que ser puntero

    pA = fopen("prestamos.csv", "r");
    if (pA != NULL) {



    fgets(linea, sizeof(linea), pA);
    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("%-6s %-18s %-10s %-15s %-3s %-3s %-4s %-3s %-13s %-6s %-8s\n", "Orden", "Cliente", "Importe", "Tipo de Credito", "Dia", "Mes", "Anio", "Cuotas", "ImporteCuota", "IVA", "Total Cuota");
    printf("---------------------------------------------------------------------------------------------------------\n");

    // CON ESTE CICLO MUESTRO LOS DISTINTOS VALORES, CORRIENDO LUGARES DE FORMA MANUAL PARA ACOMODAR EN COLUMNAS ORDENADAS Y SEPARANDO POR EL ;
    // TAMBIEN USO LAS FUNCIONES DE LA LIBRERIA "STDLIB" PARA ANOTAR CORRECTAMENTE LOS VALORES TOMANDO EL CVD (entero, float, cadena,etc), asi
    // asi puedo mostrar correctamente los numeros con decimales y poder reducir su lognitud a 2 despues de la coma (punto).

    while (fgets(linea, sizeof(linea), pA) != NULL) {
        aux = strtok(linea, ";"); // orden
        printf("%-6d ", atoi(aux));

        aux = strtok(NULL, ";"); // cliente
        printf("%-20s ", aux);

        aux = strtok(NULL, ";"); // importe
        printf("%-10d ", atoi(aux));

        aux = strtok(NULL, ";"); // tipo de credito
        printf("%-13s ", aux);

        aux = strtok(NULL, ";"); // dia
        printf("%-4d ", atoi(aux));

        aux = strtok(NULL, ";"); // mes
        printf("%-2d ", atoi(aux));

        aux = strtok(NULL, ";"); // año
        printf("%-6d ", atoi(aux));

        aux = strtok(NULL, ";"); // nro. cuotas
        printf("%-4d ", atoi(aux));

        aux = strtok(NULL, ";"); // importe cuota
        float importeCuota = atof(aux);
        printf("%-12.2f ", importeCuota);

        aux = strtok(NULL, ";"); // IVA
        float iva = atof(aux);
        printf("%-6.2f ", iva);

        aux = strtok(NULL, ";"); // total cuota
        float totalCuota = atof(aux);
        printf("%10.2f\n", totalCuota);
    }
    fclose(pA);
}
 else printf("Error al abrir el archivo.\n");
}

// FUNCION PARA CREAR NUEVO ARCHIVO BINARIO
void crear_archivo_binario(FILE * pA, struct datos clientes){



    pA = fopen("creditos.dat", "wb");

    if (pA != NULL){

        printf("\n ---------------------------------------------");
        printf("\n | ARCHIVO CREDITOS CREADO DE FORMAR CORRECTA |");
        printf("\n ---------------------------------------------");

        fwrite(&clientes,sizeof(struct datos),100,pA); // 100 serian los numeros de registros que puedo guardar, en caso de necesitar mas se puede cambiar

        fclose(pA);
    } else{
        printf("\n Error en la creaci%cn del archivo binario.",162);
    }
}

int existe_registro(int num) { // funcion aux de acceso directo, devuelve 1 si existe y 0 si no existe
    FILE *pC;
    struct datos clientes;
    int valor = 0;

    pC = fopen("creditos.dat", "rb");

    if (pC != NULL) {

        fseek(pC, (num - 1) * sizeof(struct datos), SEEK_SET);
        fread(&clientes, sizeof(struct datos), 1, pC);

            if (clientes.orden == num && clientes.orden >0) {
                valor = 1; // Existe el número de registro

          }

        fclose(pC);
    } else {
        printf("Error al abrir el archivo\n");
    }

    return valor;
}


int contieneNumeros(const char* cadena) { // funcion auxiliar para validacion y ver si pasaron numeros en lugar de caracteres/cadenas,
    for (int i = 0; cadena[i] != '\0'; i++) {
        if (isdigit(cadena[i])) { // funcion de la biblioteca c.type
            return 1;  // La cadena contiene al menos un número
        }
    }
    return 0;  // La cadena no contiene números
}
/* INTENTE USAR ESTA FUNCION PARA VER SI PODIA VALIDAR LOS NUMEROS INGRESADOS, POR EJEMPLO INGRESO CARATER Y ME RETORNA 1, pero no funciono
int validoNumero (float numero) { // Devuelve 1 si el valor es NaN (not a number), 0 si es numérico de la biblioteca math.h


    if (isnan(numero)) {
    return 1;
} else {
    return 0;
}
}
*/


// FUNCION AUX QUE RECIBE EL MES COMO ENTERO Y retorna el Nombremes que corresponderia al campo cliente.mes
const char* obtener_nombre_mes(int mes) {
    const char* nombreMes = "";

    switch (mes) {
        case 1:
            nombreMes = "ene";
            break;
        case 2:
            nombreMes = "feb";
            break;
        case 3:
            nombreMes = "mar";
            break;
        case 4:
            nombreMes = "abr";
            break;
        case 5:
            nombreMes = "may";
            break;
        case 6:
            nombreMes = "jun";
            break;
        case 7:
            nombreMes = "jul";
            break;
        case 8:
            nombreMes = "ago";
            break;
        case 9:
            nombreMes = "sep";
            break;
        case 10:
            nombreMes = "oct";
            break;
        case 11:
            nombreMes = "nov";
            break;
        case 12:
            nombreMes = "dic";
            break;
        default:
            nombreMes = "";  // Si el mes no es válido, se devuelve una cadena vacía
            break;
    }

    return nombreMes;
}


// Funcion similar a la lectura del CSV (por la separacion de lugares con strtok), con la diferencia que ahora voy a guardar todo en mi archivo binario
// creditos.dat, con la caracteristica que el binario tiene un struct clientes con leves modificaciones y creacion de campos con respecto al original
// (nombre/apellido/activo)
void migrar_datos() {
    FILE *pA, *pC;
    char linea[200];
    char *aux;
    struct datos cliente;
    int mes;

    pA = fopen("prestamos.csv", "r");
   // pC = fopen("creditos.dat", "r+b"); // abro el archivo en modo lectura y escritura
    pC = fopen("creditos.dat", "w+b"); // No es logico esto, tendria que crear el archivo con la funcion de crear binario, pero a veces me llena el binario con basura y otras veces sin basura, nose porque !! estuve probando pero no encuentro la solucion porque pasa a veces seguido u otras veces no
                                        // asi por lo menos me aseguro que el programa va a funcionar bien


    if (pA != NULL && pC != NULL) {
        fgets(linea, sizeof(linea), pA); // Leer y descartar la primera línea (encabezados)

        while (fgets(linea, sizeof(linea), pA) != NULL) { // recorre linea por linea hasta que no hay mas

            aux = strtok(linea, ";"); // orden
            cliente.orden = atoi(aux);

            aux = strtok(NULL, ";"); // Nombre y apellido
                char* espacio = strchr(aux, ' ');
                if (espacio != NULL) {
                    *espacio = '\0';  // Reemplazar el espacio por el carácter nulo para separar el nombre
                    strcpy(cliente.nombre, aux);
                    strcpy(cliente.apellido, espacio + 1);  // Apellido es lo que está después del espacio
                } else {
                    strcpy(cliente.nombre, aux);
                    strcpy(cliente.apellido, "");  // Si no hay espacio, dejar apellido vacío
                }
            strupr(cliente.apellido); // paso a mayuscula


            aux = strtok(NULL, ";"); // importe
            cliente.importe = atof(aux);

            aux = strtok(NULL, ";");  // tipo de credito
            strcpy(cliente.tipoCred, aux);
            strupr(cliente.tipoCred);

            aux = strtok(NULL, ";"); // dia
            cliente.dia = atoi(aux);

            aux = strtok(NULL, ";"); // mes
            mes = atoi(aux);
            strcpy(cliente.mes, obtener_nombre_mes(mes)); // funcion de pasar mes entero a abreviacion

            aux = strtok(NULL, ";"); // año
            cliente.anio = atoi(aux);

            aux = strtok(NULL, ";"); // Numero de cuotas
            cliente.nroCuotas = atoi(aux);

            aux = strtok(NULL, ";"); // importe de las cuotas
            cliente.importeCuotas = atof(aux);

            aux = strtok(NULL, ";"); // iva
            cliente.iva = atof(aux);

            aux = strtok(NULL, ";"); // total a pagar de las cuotas
            cliente.totalCuota = atof(aux);

            cliente.activo = 1; // por defecto activo = 1

            fwrite(&cliente, sizeof(struct datos), 1, pC);
        }
        printf ("-------------------------------\n");
        printf ("| DATOS MIGRADOS EXITOSAMENTE |\n");
        printf ("-------------------------------\n");

        fclose(pA);
        fclose(pC);
    } else {
        printf("Error al abrir los archivos. Pruebe usando la opcion 2 y vuelva a intentar\n");
    }
}
/*
// PROBANDO HACER CON UN DO WHILE (NO FUNCIONO, NO MIGRABA, ERRORES, CERRABA EL PROGRAMA, tenia otro codigo muy similar al de arriba pero lo borre y empece de cero)
void migrar_datos (FILE*pA, char *n, struct datos clientes){

FILE *pC; // archivo binario
    char nombre[40], apellido[40]; // variables aux locales para poder dividir guardar el str de nombre y apellido
    int mes, i; // variable que voy a usar de parametro para pasar a la funcion obtener_nombre_mes

    char linea[200]; // cadena donde se almancena la linea leida
    char *aux; // variable que uso para guardar los campos momentaneamente y copiarlo al binario

    pA = fopen(n, "r"); // abro
    pC = fopen("creditos.dat", "wb"); // abro

  //  fgets(linea, sizeof(linea), pA);

    //verifico si se crearon correctamente
       if (pA!=NULL){
            printf ("Archivo CSV abierto correctamente\n");

            if (pC!=NULL) {
                printf("Archivo Binario abierto corretemente\n");

                    do{
                            do{
                                    for(i=0;i<18;i++){
                                                    aux = strtok (linea, ";"); // campo ORDEN
                                                    clientes.orden = atoi(aux);

                                                    aux = strtok (NULL, ";"); // nombre y apellido

                                                    strcpy(nombre, strtok(aux, " "));

                                                    strcpy(apellido, strtok(NULL, " "));

                                                    strcpy(clientes.nombre, nombre);

                                                    strcpy(clientes.apellido, apellido);

                                                    for (int i = 0; clientes.apellido[i] != '\0'; i++) {
                                                    clientes.apellido[i] = tolower(clientes.apellido[i]); // recorro los espacios del campo apellido 1 a 1 y lo cambio a minuscula
                                                        }
                                                    aux = strtok(NULL, ";"); // importe
                                                    clientes.importe = atof(aux);

                                                    aux = strtok(NULL, ";"); // tipo de crédito
                                                    strcpy(clientes.tipoCred, aux);

                                                    for (int i = 0; clientes.tipoCred[i] != '\0'; i++) {
                                                    clientes.tipoCred[i] = tolower(clientes.tipoCred[i]);
                                                    }

                                                    aux = strtok(NULL, ";"); // dia
                                                    clientes.dia = atoi(aux);

                                                    aux = strtok(NULL, ";"); // mes
                                                    mes = atoi(aux);

                                                    obtener_nombre_mes(mes, clientes.mes); // Llamo a la funcion para cambiar el entero que optengo del CSV y cambiarlo por su sigla correspondiente

                                                    aux = strtok(NULL, ";"); // año
                                                    clientes.anio = atoi(aux);

                                                    aux = strtok(NULL, ";"); // nro. cuotas
                                                    clientes.nroCuotas = atoi(aux);

                                                    aux = strtok(NULL, ";"); // importe cuota
                                                    clientes.importeCuotas = atof(aux);

                                                    aux = strtok(NULL, ";"); // IVA
                                                    clientes.iva = atof(aux);

                                                    aux = strtok(NULL, ";"); // total cuota
                                                    clientes.totalCuota = atof(aux);

                                                    clientes.activo = 1;

                                                    fwrite(&clientes, sizeof(struct datos), 1, pC);
                                                        // Escribo en el archivo con su formato. - TENER EN CUENTA RE ACADA VES Q HACE UNA ESCRITURA ME CORRE AL SIGUIENTE BLOQUE
                                                    } // fin ciclo de lectura del csv y copiado al binario
                                                    fseek(pC, 0, SEEK_END); // posiciono el puntero al final del archivo
                                        }while (!EOF);
                            }while (!EOF);}


        printf("CREADO EXITOSAMENTE\n");
        fclose(pA);
        fclose(pC);
        }   else {printf("Error en la apertura de los archivos");}

}
*/
//FUNCION CON OPCIONES DE VISUALIZACION (lee el binario, se puede reusar muchas veces a medida que se llama a esta funcion para ver los cambios)

void vista_archivo_nuevo(struct datos clientes){
FILE * pC;
int control, NroReg, i=0, j=0, num, repetir, confirmar;

//int anio,dia,mes; para case 5 (no me funciono lo hice distinto)
// char NombreBaja[100], linea[200]; para case 5 (no me funciono lo hice distinto)


do{

            printf("\n *** ACCEDIO A LA SECCION DE LISTADOS  ***",162);
            printf("\n ***   Tiene las siguientes opciones  ***",162);
            printf("\n 1: visualizar todos los datos.");
            printf("\n 2: visualizar solo los activos.");
            printf("\n 3: visualizar tipo de credito");
            printf("\n 4: visualizar por rango de tiempo.");
            //printf("\n 5: visualizar las bajas fisicas."); intente visualizarlo aca ingresando tal cual los valores pero no me funciono, ver case 5
            printf("\n Su seleccion: ");
            scanf("%d",&control);

             while (control<1||control>4){
                    printf("\nError. Valor invalido. Ingrese nuevamente\n");
                    scanf("%d", &control);
                    }





        switch (control){
    case 1:  //VEO LOS QUE ESTAN ACTIVOS E INACTIVOS (se puede interpretar como todos los registros)



                    printf("\n Visualizar activos e inactivos.\n");
                        i=0;
                        pC=fopen("creditos.dat","rb");
                            if(pC!=NULL){

                                printf("---------------------------------------------------------------------------------------------------------------\n");
                                printf("%-6s %-10s %-10s %-8s %-15s %-2s %-3s %-4s %-3s %-13s %-6s %-8s %-6s\n", "Orden", "Nombre","Apellido", "Importe", "Tipo de Credito", "Dia", "Mes", "Anio", "Cuotas", "ImporteCuota", "IVA", "Total Cuota", "Activo");
                                printf("---------------------------------------------------------------------------------------------------------------\n");
                                        fseek(pC,0,SEEK_END); // Me posiciono al final del archivo
                                        NroReg=ftell(pC)/sizeof(struct datos); // obtengo numero de registros totales
                                        fseek(pC,0,SEEK_SET);
                                            while( i < NroReg ){ // recorro con un while los registros que obtuve
                                                fseek(pC,i*sizeof(struct datos),SEEK_SET);
                                                fread(&clientes,sizeof(struct datos),1,pC); // cada vez que hago un fread o fwrite el puntero del archivo avanza 1 posicion por eso no hace falta que acumente la posicion por cada vuelta del ciclo
                                                printf("%-6d %-10s %-10s %-10.2f %-15s %-3d %-3s %-4d %-3d %-13.2f %-8.2f %-11.2f %-6d\n", clientes.orden, clientes.nombre, clientes.apellido, clientes.importe, clientes.tipoCred, clientes.dia, clientes.mes, clientes.anio, clientes.nroCuotas, clientes.importeCuotas, clientes.iva, clientes.totalCuota, clientes.activo);

                                                i++;
                                                }

                                fclose(pC);
                                }else{printf("\nError al abrir los archivos");}
                            break;

    case 2: // VEO SOLO LOS QUE ESTAN CON EL CAMPO ACTIVO = 1
            printf("\n Visualizar solo activos.\n");
                    i=0;
                    pC=fopen("creditos.dat","rb");
                        if(pC!=NULL){
                                printf("---------------------------------------------------------------------------------------------------------------\n");
                                printf("%-6s %-10s %-10s %-10s %-15s %-3s %-3s %-4s %-3s %-13s %-6s %-8s %-6s\n", "Orden", "Nombre","Apellido", "Importe", "Tipo de Credito", "Dia", "Mes", "Anio", "Cuotas", "ImporteCuota", "IVA", "Total Cuota", "Activo");
                                printf("---------------------------------------------------------------------------------------------------------------\n");


                        fseek(pC,0,SEEK_END);
                        NroReg=ftell(pC)/sizeof(struct datos);
                        fseek(pC,0,SEEK_SET);
                            while( i < NroReg ){
                                    fseek(pC,i*sizeof(struct datos),SEEK_SET);
                                    fread(&clientes,sizeof(struct datos),1,pC);

                                    if(clientes.activo == 1){ // imprimo cuando es =1
                                        printf("%-6d %-10s %-10s %-10.2f %-15s %-3d %-3s %-4d %-3d %-13.2f %-8.2f %-11.2f %-6d\n", clientes.orden, clientes.nombre, clientes.apellido, clientes.importe, clientes.tipoCred, clientes.dia, clientes.mes, clientes.anio, clientes.nroCuotas, clientes.importeCuotas, clientes.iva, clientes.totalCuota, clientes.activo);

                                        i++;
                                    }
                                    else if(clientes.activo !=1){
                                        i++;
                                        j++;
                                        }else{i++;}

                                            }
                                        if(j==NroReg){
                                            printf("\n --------------------");
                                            printf("\n |  NO HAY ACTIVOS  |");
                                            printf("\n --------------------");}
                                            fclose(pC);
                            }else{printf("\nError al abrir los archivos");}

        break;

    case 3: // VEO SEGUN QUE TIPO DE CREDITO SEPARO "CON CARANTIA"=1 , "A SOLA FIRMA"=0

            // Valido el valor que desea buscar el usuario
            printf("\n***Busqueda segun tipo de credito***\n");
            printf ("\n1 : Busqueda CON GARANTIA");
            printf ("\n2 : Busqueda A SOLA FIRMA");
            printf("\n Su seleccion: ");
                    scanf("%d", &num);
                    do {
                        if ((num != 1) && (num != 2)) {
                            printf("ERROR - NUMERO INVALIDO\n");
                            printf ("\n1 : Busqueda CON GARANTIA");
                            printf ("\n2 : Busqueda A SOLA FIRMA");
                            printf("\n Su seleccion: ");
                            scanf("%d", &num);

                        } else {
                            printf("Su seleccion fue %d, Esta seguro? - para confirmar pulse nuevamente seguido de enter.\n", num);
                            printf("\n Su seleccion: ");
                            scanf("%d", &num);
                        }
                    } while ((num != 1) && (num != 2));

                    i = 0;

                    pC = fopen("creditos.dat", "rb");
                        if (pC != NULL) {
                            printf("---------------------------------------------------------------------------------------------------------------\n");
                            printf("%-6s %-10s %-10s %-10s %-15s %-3s %-3s %-4s %-3s %-13s %-6s %-8s %-6s\n", "Orden", "Nombre", "Apellido", "Importe", "Tipo de Crédito", "Dia", "Mes", "Anio", "Cuotas", "Importe Cuota", "IVA", "Total Cuota", "Activo");
                            printf("---------------------------------------------------------------------------------------------------------------\n");

                                fseek(pC, 0, SEEK_END);
                                NroReg = ftell(pC) / sizeof(struct datos);
                                fseek(pC, 0, SEEK_SET);

                                    while (i < NroReg) {
                                        fseek(pC,i*sizeof(struct datos),SEEK_SET);
                                        fread(&clientes, sizeof(struct datos), 1, pC);

                                        // Con el strcmp, comparando el valor que eligio el cliente y el ya existente en el binario separo  los registros segun el tiempo de garantia.

                                        if ((num == 1 && strcmp(clientes.tipoCred, "CON GARANTIA") == 0) || (num == 2 && strcmp(clientes.tipoCred, "A SOLA FIRMA") == 0)) {
                                                    printf("%-6d %-10s %-10s %-10.2f %-15s %-3d %-3s %-4d %-3d %-13.2f %-8.2f %-11.2f %-6d\n", clientes.orden, clientes.nombre, clientes.apellido, clientes.importe, clientes.tipoCred, clientes.dia, clientes.mes, clientes.anio, clientes.nroCuotas, clientes.importeCuotas, clientes.iva, clientes.totalCuota, clientes.activo);

                                        }

                                        i++;
                                    }

                                    fclose(pC);

                                        }else{printf("\nError al abrir los archivos");}


                                    break;

    case 4: // FILTRO SEGUN UN RANGO DE TIEMPO DIA/MES/AÑO MAXIMO Y MINIMO QUE ELIJA EL CLIENTE. A REVISAR

                        printf("\nFiltrar por rango de tiempo.\n");
                        int minDia, maxDia; // rangos de dias a buscar
                        int minAnio, maxAnio,minMes,maxMes; // rango de meses y años a buscar
                        int encontrado = 0; // variable para verificar si se encontraron registros

                        printf("\n*Ingrese los rangos de tiempo a buscar*\n");

                        printf("\nDia minimo: ");
                        scanf("%d", &minDia);
                                    while (minDia < 1 || minDia > 31 ) {
                                    printf("\nError. Ingreso un numero invalido o fuera de rango. Ingrese nuevamente: ");
                                    scanf("%d", &minDia);
                                    }

                        printf("\nDia maximo: ");
                        scanf("%d", &maxDia);
                                     while (maxDia < 1 || maxDia > 31 ) {
                                    printf("\nError. Ingreso un numero invalido o fuera de rango. Ingrese nuevamente: ");
                                    scanf("%d", &maxDia);
                                    }

                        printf("\nMes minimo (numero): ");
                        scanf("%d", &minMes);
                                    while (minMes < 1 || minMes > 12 ) {
                                    printf("\nError. Ingreso un numero invalido o fuera de rango. Ingrese nuevamente: ");
                                    scanf("%d", &minMes);
                                    }

                        printf("\nMes maximo (numero): ");
                        scanf("%d", &maxMes);
                                    while (maxMes < 1 || maxMes > 12 ) {
                                    printf("\nError. Ingreso un numero invalido o fuera de rango. Ingrese nuevamente: ");
                                    scanf("%d", &maxMes);
                                    }

                        printf("\nAnio minimo: ");
                        scanf("%d", &minAnio);
                                    while (minAnio< 2022 || minAnio > 2023){
                                    printf("\nError. Ingreso un numero invalido o fuera del rango. Ingrese nuevamente: ");
                                    scanf("%d", &minAnio);
                                    }


                        printf("\nAnio maximo: ");
                        scanf("%d", &maxAnio);
                                    while (maxAnio< 2022 || maxAnio > 2023){
                                    printf("\nError. Ingreso un numero invalido o fuera del rango. Ingrese nuevamente: ");
                                    scanf("%d", &maxAnio);
                                    }


                                i = 0;
                                j = 0;
                                pC = fopen("creditos.dat", "rb");
                                if (pC != NULL) {
                                    printf("---------------------------------------------------------------------------------------------------------------\n");
                                    printf("%-6s %-10s %-10s %-10s %-15s %-3s %-3s %-4s %-3s %-13s %-6s %-8s %-6s\n", "Orden", "Nombre", "Apellido", "Importe", "Tipo de Crédito", "Dia", "Mes", "Anio", "Cuotas", "Importe Cuota", "IVA", "Total Cuota", "Activo");
                                    printf("---------------------------------------------------------------------------------------------------------------\n");

                                    fseek(pC, 0, SEEK_END);
                                    NroReg = ftell(pC) / sizeof(struct datos);
                                    fseek(pC, 0, SEEK_SET);

                                    while (i < NroReg) {
                                        fseek(pC,i*sizeof(struct datos),SEEK_SET);
                                        fread(&clientes, sizeof(struct datos), 1, pC);

                                            if (clientes.dia >= minDia && clientes.dia <= maxDia && strcmp(clientes.mes, obtener_nombre_mes(minMes)) >= 0 && strcmp(clientes.mes, obtener_nombre_mes(maxMes)) <= 0 && clientes.anio >= minAnio && clientes.anio <= maxAnio) {
                                                printf("%-6d %-10s %-10s %-10.2f %-15s %-3d %-3s %-4d %-3d %-13.2f %-8.2f %-11.2f %-6d\n", clientes.orden, clientes.nombre, clientes.apellido, clientes.importe, clientes.tipoCred, clientes.dia, clientes.mes, clientes.anio, clientes.nroCuotas, clientes.importeCuotas, clientes.iva, clientes.totalCuota, clientes.activo);

                                                encontrado = 1;
                                            }

                                            i++;
                                        } if (encontrado==0) {
                                            printf("\nNo se encontraron registros en el rango de tiempo especificado.\n");
                                        }

                                        fclose(pC);

                                    } else printf("\nError al abrir el archivo.\n");


        break;
/*
        case 5: //ARME ESTE CASE PARA MOSTRAR EL XYZ SI BIEN CON EL sprintf ARMO IGUAL EL NOMBRE DEL ARCHIVO NO ME LO LEE ME TIRA ERROR NOSE QUE PASA, Asi que lo
                //liste directamente, despues de guardar el archivo en la ultima funcion de baja_fisica


                printf("\n***LISTADO DE BAJAS PERMANENTES***\n");
                printf("\nPara ver el listado ingrese la fecha de baja\n");
                // pido la fecha de la bajada, el usuario tuvo que tomar nota de la fecha previamente

                printf ("Ingrese el numero de Anio (2022-2023)");
                printf("\n Su seleccion: ");
                scanf ("%d", &anio);

                            while (anio< 2022 || anio > 2023){
                            printf("\nError. Ingreso un numero invalido o fuera del rango. Ingrese nuevamente\n");
                            scanf("%d", &anio);
                            }

                printf("\nIngrese el numero de mes");
                printf("\n Su Seleccion: ");
                scanf("%d",&mes);

                           while (mes < 1 || mes > 12 ) {
                            printf("\nError. Ingreso un numero invalido o fuera de rango. Ingrese nuevamente\n");
                            scanf("%f", &mes);
                            }

                printf("\nIngrese el dia");
                printf("\n Su Seleccion: ");
                scanf("%d",&dia);

                           while (dia < 1 || dia > 31 ) {
                            printf("\nError. Ingreso un numero invalido o fuera de rango. Ingrese nuevamente\n");
                            scanf("%f", &dia);
                            }

                sprintf(NombreBaja, "clientes_bajas_%02d_%02d_%04d.xyz\n", dia, mes, anio);
                printf ("%s", NombreBaja);

                FILE* archivo = fopen(NombreBaja, "r");

                if (archivo != NULL) {

                                    printf("---------------------------------------------------------------------------------------------------------------\n");
                                    printf("%-6s %-10s %-10s %-10s %-15s %-3s %-3s %-4s %-3s %-13s %-6s %-8s %-6s\n", "Orden", "Nombre", "Apellido", "Importe", "Tipo de Crédito", "Dia", "Mes", "Anio", "Cuotas", "Importe Cuota", "IVA", "Total Cuota", "Activo");
                                    printf("---------------------------------------------------------------------------------------------------------------\n");

                                    while (fgets(linea, sizeof(linea), archivo)) {
                                        printf("%s", linea);
                                    }




                   } else  printf("Error al abrir el archivo\n");


        break;
*/

        }

        printf ("\nDesea ver algo mas? pulse 1 para continuar o 0 para salir");
        printf ("\nSu seleccion: ");
        scanf ("%d",&repetir);
         while (repetir<0||repetir>1){
                    printf("\nError. Valor invalido. Ingrese nuevamenten");
                    printf ("\nSu seleccion: ");
                    scanf("%d", &repetir);
                    }



}while (repetir == 1);


}

void ingresar_clientes (FILE*pC, struct datos clientes){ // Se podria mejorar usando la librearia time.h me se me complico para desarrollar y lo hice mas directo.
int i, ID, NroReg, control, opcion, mes, confirmar, repetir;

do{
pC = fopen ("creditos.dat", "r+b");



  if (pC != NULL){

                printf("   *** ALTA DE NUEVO CLIENTE  ***\n");
                printf("**Completar los siguientes campos**\n");

        // INGRESO NUMERO DE ORDEN


        printf("\n\nIngrese el Orden del cliente. No puede ser menor o igual a cero: ");
        scanf("%d",&ID);


         while (existe_registro(ID) ==1 || ID <= 0){
                        printf("\nError. Ingreso un numero invalido o inexistente en el registro. Ingrese nuevamente: ");
                        scanf("%d", &ID);
                        }

             /* Pruebo la nueva funcion asi la reutilizo mas adelante

                fseek(pC,0,SEEK_END);
                NroReg=ftell(pC)/sizeof(struct datos);
                fseek(pC,0,SEEK_SET);
                i=0;
                control = 1;
                    while( i < NroReg ){
                        fseek(pC,i*sizeof(struct datos),SEEK_SET);
                        fread(&clientes,sizeof(struct datos),1,pC); // voy a la posicion 0
                        i++;
                        if (clientes.orden==ID){ // veo si ya esta
                            printf("\n Este Cliente ya se encuentra registrado.");
                            control = 0;
                        }

*/


        clientes.orden = ID; // guardo el nuevo numero de orden

        printf ("\nIngrese el Nombre: "); // cargo nombre
        scanf ("%s", clientes.nombre);

            while (contieneNumeros(clientes.nombre) != 0) { //uso funcion aux
            printf("Ingreso un nombre invalido. No puede contener numeros. Ingrese nuevamente: ");
            scanf("%s", clientes.nombre);
                }

        printf ("\nIngrese el Apellido: "); // cargo apellido
        scanf ("%s", clientes.apellido);

           while (contieneNumeros(clientes.apellido) != 0) {
            printf("Ingreso un apellido invalido. No puede contener numeros. Ingrese nuevamente: ");
            scanf("%s", clientes.apellido);
                }
            strupr(clientes.apellido); // mantengo el apelldio en mayuscula

        printf ("\nIngrese el importe del prestamo: "); // cargo importe
        scanf ("%f", &clientes.importe);

            while (clientes.importe<=0){
                printf("\nError. Ingreso un numero invalido. Ingrese nuevamente: ");
                scanf("%f", &clientes.importe);
            }

        printf("\nIngrese el tipo de credito que necesita segun:\n ");// cargo tipo de prestamo
        printf("\n0 : CON GARANTIA");
        printf("\n1 : SOLA FIRMA");
        printf("\n Su seleccion: ");
        scanf("%d", &opcion);

              while (opcion<0||opcion>1){
                    printf("\nError. Ingreso un numero invalido. Ingrese nuevamente: ");
                    scanf("%d", &opcion);
                }

                switch (opcion){
                case 0:
                    strcpy(clientes.tipoCred, "CON GARANTIA");
                    break;
                case 1:
                    strcpy(clientes.tipoCred, "A SOLA FIRMA");
                    break;
                }

        // CAMPOS DE FECHA, CON CORRESPONDIENTE VALIDACIONES (de ingreso de datos, rango de valores, rango de meses, etc)
        // AÑO MES DIA

        printf ("Ingrese el numero de Anio (2022-2023): "); // ES LO QUE ENTENDI DE LA CONSIGNA, año mas viejo 2022 segun el csv , año actual 2023, si quiero mas es cuestion de cambiar el rango
        scanf ("%d", &clientes.anio);

                while (clientes.anio< 2022 || clientes.anio > 2023){
                    printf("\nError. Ingreso un numero invalido o fuera del rango. Ingrese nuevamente\n");
                    scanf("%d", &clientes.anio);
                }



        printf("\nINGRESE EL NUMERO DE MES CORRESPONDIENTE:\n"); //

            printf        ("\n 1: Enero");
            printf        ("\n 2: Febrero");
            printf        ("\n 3: Marzo");
            printf        ("\n 4: Abril");
            printf        ("\n 5: Mayo");
            printf        ("\n 6: Junio");
            printf        ("\n 7: Julio");
            printf        ("\n 8: Agosto");
            printf        ("\n 9: Septiembre");
            printf        ("\n 10: Octubre");
            printf        ("\n 11: Noviembre");
            printf        ("\n 12: Diciembre");
            printf("\n Su Seleccion: ");
            scanf("%d",&mes);

               while (mes < 1 || mes > 12 ) {
                printf("\nError. Ingreso un numero invalido o fuera de rango. Ingrese nuevamente\n");
                scanf("%f", &mes);
                }
            switch (mes){
            case 1://ENERO
                    strcpy (clientes.mes, obtener_nombre_mes(mes)); // reutilizo la funcion obtener mes
                    printf      ("\n *** ENERO ***");
                    printf      ("\n Seleccione el dia: ");
                    printf      ("\n 1|2|3|4|5|6|7|8|9|10");
                    printf      ("\n 11|12|13|14|15|16|17|18|19|20");
                    printf      ("\n 21|22|23|24|25|26|27|28|29|30");
                    printf      ("\n 31|");
                    printf("\n Su Seleccion: ");
                    scanf ("%d", &clientes.dia);

                            while (clientes.dia < 1 || clientes.dia > 31){
                        printf("\nError. Ingreso un numero invalido o fuera de rango. Ingrese nuevamente\n");
                        scanf("%d", &clientes.dia);
                        }

                break;
            case 2: // FEBRERO
                strcpy (clientes.mes, obtener_nombre_mes(mes)); // reutilizo la funcion obtener mes
                    printf      ("\n *** FEBRERO ***");
                    printf      ("\n Seleccione el dia: ");
                    printf      ("\n 1|2|3|4|5|6|7|8|9|10");
                    printf      ("\n 11|12|13|14|15|16|17|18|19|20");
                    printf      ("\n 21|22|23|24|25|26|27|28");
                    printf("\n Su Seleccion: ");
                    scanf ("%d", &clientes.dia);

                            while (clientes.dia < 1 || clientes.dia > 28){
                        printf("\nError. Ingreso un numero invalido o fuera de rango. Ingrese nuevamente\n");
                        scanf("%d", &clientes.dia);
                        }
                break;
            case 3: // MARZO
                strcpy (clientes.mes, obtener_nombre_mes(mes)); // reutilizo la funcion obtener mes
                    printf      ("\n *** MARZO ***");
                    printf      ("\n Seleccione el dia: ");
                    printf      ("\n 1|2|3|4|5|6|7|8|9|10");
                    printf      ("\n 11|12|13|14|15|16|17|18|19|20");
                    printf      ("\n 21|22|23|24|25|26|27|28|29|30");
                    printf      ("\n 31|");
                    printf("\n Su Seleccion: ");
                    scanf ("%d", &clientes.dia);

                            while (clientes.dia < 1 || clientes.dia > 31){
                        printf("\nError. Ingreso un numero invalido o fuera de rango. Ingrese nuevamente\n");
                        scanf("%d", &clientes.dia);
                        }
                break;
            case 4: // ABRIL
                strcpy (clientes.mes, obtener_nombre_mes(mes)); // reutilizo la funcion obtener mes
                    printf      ("\n *** ABRIL ***");
                    printf      ("\n Seleccione el dia: ");
                    printf      ("\n 1|2|3|4|5|6|7|8|9|10");
                    printf      ("\n 11|12|13|14|15|16|17|18|19|20");
                    printf      ("\n 21|22|23|24|25|26|27|28|29|30");
                    printf("\n Su Seleccion: ");
                    scanf ("%d", &clientes.dia);

                            while (clientes.dia < 1 || clientes.dia > 30){
                        printf("\nError. Ingreso un numero invalido o fuera de rango. Ingrese nuevamente\n");
                        scanf("%d", &clientes.dia);
                        }
                break;
            case 5: // MAYO
                strcpy (clientes.mes, obtener_nombre_mes(mes)); // reutilizo la funcion obtener mes
                    printf      ("\n *** MAYO ***");
                    printf      ("\n Seleccione el dia: ");
                    printf      ("\n 1|2|3|4|5|6|7|8|9|10");
                    printf      ("\n 11|12|13|14|15|16|17|18|19|20");
                    printf      ("\n 21|22|23|24|25|26|27|28|29|30");
                    printf      ("\n 31|");
                    printf("\n Su Seleccion: ");
                    scanf ("%d", &clientes.dia);

                            while (clientes.dia < 1 || clientes.dia > 31){
                        printf("\nError. Ingreso un numero invalido o fuera de rango. Ingrese nuevamente\n");
                        scanf("%d", &clientes.dia);
                        }
                break;
            case 6: // JUNIO
                strcpy (clientes.mes, obtener_nombre_mes(mes)); // reutilizo la funcion obtener mes
                    printf      ("\n *** JUNIO ***");
                    printf      ("\n Seleccione el dia: ");
                    printf      ("\n 1|2|3|4|5|6|7|8|9|10");
                    printf      ("\n 11|12|13|14|15|16|17|18|19|20");
                    printf      ("\n 21|22|23|24|25|26|27|28|29|30");
                    printf("\n Su Seleccion: ");
                    scanf ("%d", &clientes.dia);

                            while (clientes.dia < 1 || clientes.dia > 30){
                        printf("\nError. Ingreso un numero invalido o fuera de rango. Ingrese nuevamente\n");
                        scanf("%d", &clientes.dia);
                        }
                break;
            case 7: // JULIO
                strcpy (clientes.mes, obtener_nombre_mes(mes)); // reutilizo la funcion obtener mes
                    printf      ("\n *** JULIO ***");
                    printf      ("\n Seleccione el dia: ");
                    printf      ("\n 1|2|3|4|5|6|7|8|9|10");
                    printf      ("\n 11|12|13|14|15|16|17|18|19|20");
                    printf      ("\n 21|22|23|24|25|26|27|28|29|30");
                    printf      ("\n 31|");
                    printf("\n Su Seleccion: ");
                    scanf ("%d", &clientes.dia);

                            while (clientes.dia < 1 || clientes.dia > 31){
                        printf("\nError. Ingreso un numero invalido o fuera de rango. Ingrese nuevamente\n");
                        scanf("%d", &clientes.dia);
                        }
                break;
            case 8: // AGOSTO
                strcpy (clientes.mes, obtener_nombre_mes(mes)); // reutilizo la funcion obtener mes
                    printf      ("\n *** AGOSTO ***");
                    printf      ("\n Seleccione el dia: ");
                    printf      ("\n 1|2|3|4|5|6|7|8|9|10");
                    printf      ("\n 11|12|13|14|15|16|17|18|19|20");
                    printf      ("\n 21|22|23|24|25|26|27|28|29|30");
                    printf      ("\n 31|");
                    printf("\n Su Seleccion: ");
                    scanf ("%d", &clientes.dia);

                            while (clientes.dia < 1 || clientes.dia > 31){
                        printf("\nError. Ingreso un numero invalido o fuera de rango. Ingrese nuevamente\n");
                        scanf("%d", &clientes.dia);
                        }
                break;
            case 9: // SEPTIEMBRE
                strcpy (clientes.mes, obtener_nombre_mes(mes)); // reutilizo la funcion obtener mes
                    printf      ("\n *** SEPTIEMBRE ***");
                    printf      ("\n Seleccione el dia: ");
                    printf      ("\n 1|2|3|4|5|6|7|8|9|10");
                    printf      ("\n 11|12|13|14|15|16|17|18|19|20");
                    printf      ("\n 21|22|23|24|25|26|27|28|29|30");
                    printf("\n Su Seleccion: ");
                    scanf ("%d", &clientes.dia);

                            while (clientes.dia < 1 || clientes.dia > 30){
                        printf("\nError. Ingreso un numero invalido o fuera de rango. Ingrese nuevamente\n");
                        scanf("%d", &clientes.dia);
                        }
                break;
            case 10: // OCTUBRE
                strcpy (clientes.mes, obtener_nombre_mes(mes)); // reutilizo la funcion obtener mes
                    printf      ("\n *** OCTUBRE ***");
                    printf      ("\n Seleccione el dia: ");
                    printf      ("\n 1|2|3|4|5|6|7|8|9|10");
                    printf      ("\n 11|12|13|14|15|16|17|18|19|20");
                    printf      ("\n 21|22|23|24|25|26|27|28|29|30");
                    printf      ("\n 31|");
                    printf("\n Su Seleccion: ");
                    scanf ("%d", &clientes.dia);

                            while (clientes.dia < 1 || clientes.dia > 31){
                        printf("\nError. Ingreso un numero invalido o fuera de rango. Ingrese nuevamente\n");
                        scanf("%d", &clientes.dia);
                        }
                break;
            case 11: // NOVIEMBRE
                strcpy (clientes.mes, obtener_nombre_mes(mes)); // reutilizo la funcion obtener mes
                    printf      ("\n *** NOVIEMBRE ***");
                    printf      ("\n Seleccione el dia: ");
                    printf      ("\n 1|2|3|4|5|6|7|8|9|10");
                    printf      ("\n 11|12|13|14|15|16|17|18|19|20");
                    printf      ("\n 21|22|23|24|25|26|27|28|29|30");
                    printf("\n Su Seleccion: ");
                    scanf ("%d", &clientes.dia);

                            while (clientes.dia < 1 || clientes.dia > 30){
                        printf("\nError. Ingreso un numero invalido o fuera de rango. Ingrese nuevamente\n");
                        scanf("%d", &clientes.dia);
                        }
                break;
            case 12: // DICIEMBRE
                strcpy (clientes.mes, obtener_nombre_mes(mes)); // reutilizo la funcion obtener mes
                    printf      ("\n *** DICIEMBRE ***");
                    printf      ("\n Seleccione el dia: ");
                    printf      ("\n 1|2|3|4|5|6|7|8|9|10");
                    printf      ("\n 11|12|13|14|15|16|17|18|19|20");
                    printf      ("\n 21|22|23|24|25|26|27|28|29|30");
                    printf      ("\n 31|");
                    printf("\n Su Seleccion: ");
                    scanf ("%d", &clientes.dia);

                            while (clientes.dia < 1 || clientes.dia > 31){
                        printf("\nError. Ingreso un numero invalido o fuera de rango. Ingrese nuevamente\n");
                        scanf("%d", &clientes.dia);
                        }
                break;

            }

            // FIN INGRESO FECHA (DIA MES AÑO)

            printf ("\nIngrese el numero de cuotas: "); // Numero de cuotas
            scanf ("%d", &clientes.nroCuotas);

            while (clientes.nroCuotas<0){
                printf("\nError. Ingreso un numero invalido. Ingrese nuevamente");
                scanf("%d", &clientes.nroCuotas);
                }

            // operaciones

            clientes.importeCuotas=clientes.importe/clientes.nroCuotas; // Importe cuotas

            clientes.iva= clientes.importeCuotas*IVA; // IVA

            clientes.totalCuota = clientes.importeCuotas + clientes.iva; // total a pagar de cuotas

            clientes.activo = 1; // por defecto = 1

            // vista previa de todo lo que se cargo.

            printf ("**CONFIRMACION DE DATOS**\n\n");

            printf("---------------------------------------------------------------------------------------------------------------\n");
            printf("%-6s %-10s %-10s %-10s %-15s %-3s %-3s %-4s %-3s %-13s %-6s %-8s %-6s\n", "Orden", "Nombre","Apellido", "Importe", "Tipo de Credito", "Dia", "Mes", "Anio", "Cuotas", "ImporteCuota", "IVA", "Total Cuota", "Activo");
            printf("---------------------------------------------------------------------------------------------------------------\n");

            printf("%-6d %-10s %-10s %-10.2f %-15s %-3d %-3s %-4d %-3d %-13.2f %-8.2f %-11.2f %-6d\n", clientes.orden, clientes.nombre, clientes.apellido, clientes.importe, clientes.tipoCred, clientes.dia, clientes.mes, clientes.anio, clientes.nroCuotas, clientes.importeCuotas, clientes.iva, clientes.totalCuota, clientes.activo);

            printf ("\nDesea agregar los datos al archivo?\n");
            printf ("\nSI = 1 - NO = 0");
            printf("\n Su Seleccion: ");

            scanf  ("%d", &confirmar);

               while (confirmar<0 || confirmar >1){
                printf("\nError. Ingreso un numero invalido. Ingrese nuevamente");
                scanf("%d", &confirmar);
                }

                if (confirmar == 1){ // guardo todo en orden correspondiente, recordar que si hay campos entre medio sin valores se crean posicions =0 y campos en blanco

                    fseek(pC, (clientes.orden-1) * sizeof(struct datos), SEEK_SET);
                    fwrite(&clientes, sizeof(struct datos), 1, pC);
                    printf("\n -----------------------------------");
                    printf("\n |  DATOS GUARDADOS EXITOSAMENTE!  |");
                    printf("\n -----------------------------------");


                    fclose(pC);
                }

                else{
                    printf ("\n***OPERACION CANCELADA***\n");
                    fclose(pC);
                }


}else printf ("Error al abrir el archivo\n");

        printf ("\nDesea ingresar otro cliente? pulse 1 para continuar o 0 para salir");
        printf ("\nSu seleccion: ");
        scanf ("%d",&repetir);
         while (repetir<0||repetir>1){
                    printf("\nError. Valor invalido. Ingrese nuevamente");
                    printf ("\nSu seleccion: ");
                    scanf("%d", &repetir);
                    }

}while (repetir == 1);



}

// funcion busqueda, recorre de forma secuencial el registro hasta encontrar el correcto
void busqueda (FILE *pC, struct datos clientes){
int opcion, NroReg, orden, i, j, repetir;
char apellido[40];


printf ("                 *** BUSQUEDA ***                 \n");
printf ("  **Ingreso al menu de busqueda elija una opcion**\n");
do{

printf ("1  : Busqueda de un registro por Nro de Orden\n");
printf ("2  : Busqueda de un registro por Apellido\n");
printf ("\nSu Seleccion: ");
scanf ("%d", &opcion);

                    while (opcion < 0 || opcion > 2){
                    printf("\nError. Ingreso un numero invalido. Ingrese nuevamente: ");
                    scanf("%d", &opcion);
                    }


switch (opcion){
case 1: // busqueda por numero de orden / ID
        printf ("\n- Busqueda por Nro Orden -\n");
        printf ("Ingrese el numero que desea buscar (No ingresar valore menores a 0)\n");
        printf ("\nSu Seleccion: ");
        scanf ("%d", &orden);

        while (existe_registro(orden) == 0 || orden <= 0){
                        printf("\nError. Ingreso un numero invalido o inexistente en el registro. Ingrese nuevamente: ");
                        scanf("%d", &orden);
                        }

        pC = fopen ("creditos.dat", "rb");

        if (pC != NULL){
                    fseek(pC,0,SEEK_END);
                    NroReg=ftell(pC)/sizeof(struct datos);
                    fseek(pC,0,SEEK_SET);
                    i=0;j=0;
                    while( i < NroReg ){
                        fseek(pC,i*sizeof(struct datos),SEEK_SET);
                        fread(&clientes,sizeof(struct datos),1,pC);
                        i++;
                            if(clientes.orden==orden){
                                printf("---------------------------------------------------------------------------------------------------------------\n");
                                printf("%-6s %-10s %-10s %-10s %-15s %-3s %-3s %-4s %-3s %-13s %-6s %-8s %-6s\n", "Orden", "Nombre","Apellido", "Importe", "Tipo de Credito", "Dia", "Mes", "Anio", "Cuotas", "ImporteCuota", "IVA", "Total Cuota", "Activo");
                                printf("---------------------------------------------------------------------------------------------------------------\n");

                                printf("%-6d %-10s %-10s %-10.2f %-15s %-3d %-3s %-4d %-3d %-13.2f %-8.2f %-11.2f %-6d\n", clientes.orden, clientes.nombre, clientes.apellido, clientes.importe, clientes.tipoCred, clientes.dia, clientes.mes, clientes.anio, clientes.nroCuotas, clientes.importeCuotas, clientes.iva, clientes.totalCuota, clientes.activo);

                                j=1; // bandera para informar en caso de que no se encuentre ningun valor.
                                }
                    }
                            if(j==0){
                                printf("\nNo existen registros con ese numero de orden.\n");
                                }

                                fclose(pC);


        } else printf ("Error al abrir el archivo\n");


    break;
case 2: // busqueda por apellido

         printf ("\n- Busqueda por Apellido -\n");
         printf ("\nIngrese el Apellido: "); // cargo apellido
         scanf("%s", apellido);

           while (contieneNumeros(apellido) != 0) {
            printf("Ingreso un apellido invalido. No puede contener numeros. Ingrese nuevamente: ");
            scanf("%s", apellido);
                }
            strupr(apellido);
            pC = fopen ("creditos.dat", "rb");



          if (pC != NULL){
                    fseek(pC,0,SEEK_END);
                    NroReg=ftell(pC)/sizeof(struct datos);
                    fseek(pC,0,SEEK_SET);
                    i=0;j=0;
                    while( i < NroReg ){
                        fseek(pC,i*sizeof(struct datos),SEEK_SET);
                        fread(&clientes,sizeof(struct datos),1,pC);
                        i++;
                            if(strcmp(clientes.apellido, apellido)==0){
                                printf("---------------------------------------------------------------------------------------------------------------\n");
                                printf("%-6s %-10s %-10s %-10s %-15s %-3s %-3s %-4s %-3s %-13s %-6s %-8s %-6s\n", "Orden", "Nombre","Apellido", "Importe", "Tipo de Credito", "Dia", "Mes", "Anio", "Cuotas", "ImporteCuota", "IVA", "Total Cuota", "Activo");
                                printf("---------------------------------------------------------------------------------------------------------------\n");

                                printf("%-6d %-10s %-10s %-10.2f %-15s %-3d %-3s %-4d %-3d %-13.2f %-8.2f %-11.2f %-6d\n", clientes.orden, clientes.nombre, clientes.apellido, clientes.importe, clientes.tipoCred, clientes.dia, clientes.mes, clientes.anio, clientes.nroCuotas, clientes.importeCuotas, clientes.iva, clientes.totalCuota, clientes.activo);

                                j=1; // bandera para informar en caso de que no se encuentre ningun valor.
                                }
                    }
                            if(strcmp(clientes.apellido, apellido)!=0 && j==0){
                                printf("\nNo existen el apellido buscado\n");
                                }

                                fclose(pC);


        } else printf ("Error al abrir el archivo\n");

    break;
}

        printf ("\nDesea realizar otra busqueda? 1 para continuar o 0 para salir");
        printf ("\nSu seleccion: ");
        scanf ("%d",&repetir);
         while (repetir<0||repetir>1){
                    printf("\nError. Valor invalido. Ingrese nuevamente");
                    printf ("\nSu seleccion: ");
                    scanf("%d", &repetir);
                    }

}while (repetir == 1);


}


// variable que modifica los campos importe o tipo de credito de un numero de orden ingresado por el usuario, lo hago de forma directa (me posiciono con el puntero al comienzo del registro a modificar)


void modificar (FILE *pC, struct datos clientes){

int opcion, NroReg, orden, i, j, tipoCred, confirmar, repetir;
float importe;
printf ("\n            *** MODIFICACION ***\n");
printf ("***Ingreso al menu modificaciones elija una opcion***\n");

do{
printf("\n");
printf ("1  =  Para modificar el Importe\n");
printf ("2  =  Para modificar el tipo de credito\n");
printf ("Seleccion : ");
scanf ("%d", &opcion);

        switch (opcion){
        case 1:
            printf ("\n- Modificacion de importe segun Nro Orden -");
            printf ("\nIngrese el numero que desea modificar (No ingresar valore menores a 0)\n");
            printf ("\nSu seleccion: ");
            scanf ("%d", &orden);

           while (existe_registro(orden) == 0 || orden <= 0){
                        printf("\nError. Ingreso un numero invalido o inexistente en el registro. Ingrese nuevamente: ");
                        scanf("%d", &orden);
                        }

            pC = fopen ("creditos.dat", "r+b");

                if (pC != NULL && (existe_registro(orden)==1)){
                    fseek(pC,0,SEEK_SET);
                    fseek(pC,(orden-1)*sizeof(struct datos),SEEK_SET);
                    fread(&clientes,sizeof(struct datos),1,pC);
                    printf("\n Datos previos a modificar:\n");
                    printf("---------------------------------------------------------------------------------------------------------------\n");
                    printf("%-6s %-10s %-10s %-10s %-15s %-3s %-3s %-4s %-3s %-13s %-6s %-8s %-6s\n", "Orden", "Nombre","Apellido", "Importe", "Tipo de Credito", "Dia", "Mes", "Anio", "Cuotas", "ImporteCuota", "IVA", "Total Cuota", "Activo");
                    printf("---------------------------------------------------------------------------------------------------------------\n");

                    printf("%-6d %-10s %-10s %-10.2f %-15s %-3d %-3s %-4d %-3d %-13.2f %-8.2f %-11.2f %-6d\n", clientes.orden, clientes.nombre, clientes.apellido, clientes.importe, clientes.tipoCred, clientes.dia, clientes.mes, clientes.anio, clientes.nroCuotas, clientes.importeCuotas, clientes.iva, clientes.totalCuota, clientes.activo);

                    printf ("\nEsta seguro que desea modificar el valor del importe de %s %s?\n", clientes.nombre, clientes.apellido);
                    printf ("SI = 1 - NO = 0\n");
                    printf ("\nSu seleccion: ");
                    scanf  ("%d", &confirmar);

                    while (confirmar<0 || confirmar >1){
                        printf("\nError. Ingreso un numero invalido. Ingrese nuevamente: ");
                        scanf("%d", &confirmar);
                        }

                        if (confirmar == 1){

                            printf ("\nIngrese el nuevo importe: ");
                            scanf ("%f", &clientes.importe);

                            while (clientes.importe<0){
                            printf("\nError. Ingreso un numero invalido. Ingrese nuevamente: ");
                            scanf("%d", &clientes.importe);
                            }


                            fseek(pC, (orden-1) * sizeof(struct datos), SEEK_SET);
                            fwrite(&clientes, sizeof(struct datos), 1, pC);
                            printf("\n -----------------------------------");
                            printf("\n |  DATOS GUARDADOS EXITOSAMENTE!  |");
                            printf("\n -----------------------------------");

                                        printf("\n\n Datos Modificados:\n");
                                        printf("---------------------------------------------------------------------------------------------------------------\n");
                                        printf("%-6s %-10s %-10s %-10s %-15s %-3s %-3s %-4s %-3s %-13s %-6s %-8s %-6s\n", "Orden", "Nombre","Apellido", "Importe", "Tipo de Credito", "Dia", "Mes", "Anio", "Cuotas", "ImporteCuota", "IVA", "Total Cuota", "Activo");
                                        printf("---------------------------------------------------------------------------------------------------------------\n");

                                        printf("%-6d %-10s %-10s %-10.2f %-15s %-3d %-3s %-4d %-3d %-13.2f %-8.2f %-11.2f %-6d\n", clientes.orden, clientes.nombre, clientes.apellido, clientes.importe, clientes.tipoCred, clientes.dia, clientes.mes, clientes.anio, clientes.nroCuotas, clientes.importeCuotas, clientes.iva, clientes.totalCuota, clientes.activo);



                            fclose(pC);
                        }

                        else{
                            printf ("\n***OPERACION CANCELADA***\n");
                            fclose(pC);
                        }


               }else printf ("Error al abrir el archivo\n");


            break;

        case 2:
            printf ("\n- Modificacion del tipo de credito segun Nro Orden -\n");
            printf ("\nIngrese el numero que desea modificar (No ingresar valore menores a 0)\n");
            printf ("\nSu seleccion: ");
            scanf ("%d", &orden);

           while (existe_registro(orden) == 1 || orden <= 0){
                        printf("\nError. Ingreso un numero invalido o inexistente en el registro. Ingrese nuevamente: ");
                        scanf("%d", &orden);
                        }
               pC = fopen ("creditos.dat", "r+b");

                if (pC != NULL && (existe_registro(orden)==1)){

                        fseek(pC,0,SEEK_SET);
                        fseek(pC,(orden-1)*sizeof(struct datos),SEEK_SET);
                        fread(&clientes,sizeof(struct datos),1,pC);
                        printf("\n Datos previos a modificar:\n");
                        printf("---------------------------------------------------------------------------------------------------------------\n");
                        printf("%-6s %-10s %-10s %-10s %-15s %-3s %-3s %-4s %-3s %-13s %-6s %-8s %-6s\n", "Orden", "Nombre","Apellido", "Importe", "Tipo de Credito", "Dia", "Mes", "Anio", "Cuotas", "ImporteCuota", "IVA", "Total Cuota", "Activo");
                        printf("---------------------------------------------------------------------------------------------------------------\n");

                        printf("%-6d %-10s %-10s %-10.2f %-15s %-3d %-3s %-4d %-3d %-13.2f %-8.2f %-11.2f %-6d\n", clientes.orden, clientes.nombre, clientes.apellido, clientes.importe, clientes.tipoCred, clientes.dia, clientes.mes, clientes.anio, clientes.nroCuotas, clientes.importeCuotas, clientes.iva, clientes.totalCuota, clientes.activo);

                        printf ("\nEsta seguro que desea modificar el tipo de credito de %s %s?\n", clientes.nombre, clientes.apellido);;
                        printf ("SI = 1 - NO = 0\n");
                        printf ("\nSu seleccion: ");
                        scanf  ("%d", &confirmar);

                           if (confirmar == 1){

                            printf("\nIngrese el tipo de credito");
                            printf("\n0 : CON GARANTIA");
                            printf("\n1 : A SOLA FIRMA");
                            printf ("\nSu seleccion: ");
                            scanf("%d", &tipoCred);

                                  while (tipoCred < 0 || tipoCred > 1){
                                        printf("\nError. Ingreso un numero invalido. Ingrese nuevamente: ");
                                        scanf("%d", &tipoCred);
                                    }

                                    switch (tipoCred){
                                    case 0:
                                        strcpy(clientes.tipoCred, "CON GARANTIA");
                                        break;
                                    case 1:
                                        strcpy(clientes.tipoCred, "A SOLA FIRMA");
                                        break;
                                    }

                            fseek(pC, (orden-1) * sizeof(struct datos), SEEK_SET);
                            fwrite(&clientes, sizeof(struct datos), 1, pC);
                            printf("\n -----------------------------------");
                            printf("\n |  DATOS GUARDADOS EXITOSAMENTE!  |");
                            printf("\n -----------------------------------");

                                       printf("\n Datos Modificados:\n");
                                        printf("---------------------------------------------------------------------------------------------------------------\n");
                                        printf("%-6s %-10s %-10s %-10s %-15s %-3s %-3s %-4s %-3s %-13s %-6s %-8s %-6s\n", "Orden", "Nombre","Apellido", "Importe", "Tipo de Credito", "Dia", "Mes", "Anio", "Cuotas", "ImporteCuota", "IVA", "Total Cuota", "Activo");
                                        printf("---------------------------------------------------------------------------------------------------------------\n");

                                        printf("%-6d %-10s %-10s %-10.2f %-15s %-3d %-3s %-4d %-3d %-13.2f %-8.2f %-11.2f %-6d\n", clientes.orden, clientes.nombre, clientes.apellido, clientes.importe, clientes.tipoCred, clientes.dia, clientes.mes, clientes.anio, clientes.nroCuotas, clientes.importeCuotas, clientes.iva, clientes.totalCuota, clientes.activo);



                            fclose(pC);

                            } else{
                            printf ("\n***OPERACION CANCELADA***\n");
                            fclose(pC);
                        }



                }else printf ("Error al abrir el archivo\n");


            break;
        }

        printf ("\nDesea realizar otra modificacion? 1 para continuar o 0 para salir");
        printf ("\nSu seleccion: ");
        scanf ("%d",&repetir);
         while (repetir<0||repetir>1){
                    printf("\nError. Valor invalido. Ingrese nuevamente");
                    printf ("\nSu seleccion: ");
                    scanf("%d", &repetir);
                    }

}while (repetir == 1);



}



// baja de usuarlo de forma logica cambia el campo activo a 0. Se sigue mostrando en los listados pero no se borro por completo del archivo final, podria ser una pre-baja
// Es de acceso directo la busqueda del ID y correspondiente baja
void baja_logica(FILE * pC,struct datos clientes){
int i, j, NroReg, confirmar, orden, repetir;

    printf ("\n       *** BAJA LOGICA ***");
    printf ("\n*** Se realiza una baja del sistema ***\n");

    do{

            printf ("\nIngrese el numero de registro que desea modificar (No ingresar valore menores a 0)\n");
            printf ("\nSu seleccion: ");
            scanf ("%d", &orden);

           while (existe_registro(orden) != 1 || orden <= 0){
                        printf("\nError. Ingreso un numero invalido o inexistente en el registro. Ingrese nuevamente: ");
                        scanf("%d", &orden);
                        }

            pC = fopen ("creditos.dat", "r+b");

                if (pC != NULL && (existe_registro(orden)==1)){

                    fseek(pC,0,SEEK_SET);
                    fseek(pC,(orden-1)*sizeof(struct datos),SEEK_SET); // FORMA DIRECTA
                    fread(&clientes,sizeof(struct datos),1,pC);
                    printf("\n Datos previos a modificar:\n");
                    printf("---------------------------------------------------------------------------------------------------------------\n");
                    printf("%-6s %-10s %-10s %-10s %-15s %-3s %-3s %-4s %-3s %-13s %-6s %-8s %-6s\n", "Orden", "Nombre","Apellido", "Importe", "Tipo de Credito", "Dia", "Mes", "Anio", "Cuotas", "ImporteCuota", "IVA", "Total Cuota", "Activo");
                    printf("---------------------------------------------------------------------------------------------------------------\n");

                    printf("%-6d %-10s %-10s %-10.2f %-15s %-3d %-3s %-4d %-3d %-13.2f %-8.2f %-11.2f %-6d\n", clientes.orden, clientes.nombre, clientes.apellido, clientes.importe, clientes.tipoCred, clientes.dia, clientes.mes, clientes.anio, clientes.nroCuotas, clientes.importeCuotas, clientes.iva, clientes.totalCuota, clientes.activo);

                    printf ("\nEsta seguro que quiere dar la baja a %s %s", clientes.nombre, clientes.apellido);
                    printf ("\nSI = 1 - NO = 0\n");
                    printf ("\nSu seleccion: ");
                    scanf  ("%d", &confirmar);

                    while (confirmar<0 || confirmar >1){
                        printf("\nError. Ingreso un numero invalido. Ingrese nuevamente: ");
                        scanf("%d", &confirmar);
                        }

                        if (confirmar == 1 && clientes.activo==1){

                            clientes.activo=0;

                            fseek(pC,0,SEEK_SET);
                            fseek(pC, (orden-1) * sizeof(struct datos), SEEK_SET);
                            fwrite(&clientes, sizeof(struct datos), 1, pC);

                            printf("\n- Bajada realizado correctamente -\n");
                            fflush(stdin);
                            getchar();

                            printf("\n**CLIENTES ACTIVOS**\n");
                                            printf("---------------------------------------------------------------------------------------------------------------\n");
                                            printf("%-6s %-10s %-10s %-10s %-15s %-3s %-3s %-4s %-3s %-13s %-6s %-8s %-6s\n", "Orden", "Nombre","Apellido", "Importe", "Tipo de Credito", "Dia", "Mes", "Anio", "Cuotas", "ImporteCuota", "IVA", "Total Cuota", "Activo");
                                            printf("---------------------------------------------------------------------------------------------------------------\n");

                                fseek(pC,0,SEEK_END);
                                NroReg=ftell(pC)/sizeof(struct datos);
                                fseek(pC,0,SEEK_SET);
                                i=0;j=0;
                                while( i < NroReg ){
                                    fseek(pC,i*sizeof(struct datos),SEEK_SET);
                                    fread(&clientes,sizeof(struct datos),1,pC);
                                    i++;
                                        if(clientes.activo==1){

                                            printf("%-6d %-10s %-10s %-10.2f %-15s %-3d %-3s %-4d %-3d %-13.2f %-8.2f %-11.2f %-6d\n", clientes.orden, clientes.nombre, clientes.apellido, clientes.importe, clientes.tipoCred, clientes.dia, clientes.mes, clientes.anio, clientes.nroCuotas, clientes.importeCuotas, clientes.iva, clientes.totalCuota, clientes.activo);

                                            j=1; // bandera para informar en caso de que no se encuentre ningun valor.
                                            }
                                }
                                        if(j==0){
                                            printf("\n- No existen registros con ese numero de orden -\n");
                                            }

                                            fclose(pC);





                                }else if (confirmar == 1 && clientes.activo ==0){
                                    printf ("\nEl campo que desea modificar ya esta dado de baja\n");
                                    fclose(pC);
                                    }

                                        else{
                                            printf ("\n***OPERACION CANCELADA***\n");
                                            fclose(pC);
                                            }

                }else printf ("Error al abrir el archivo\n");

                printf ("\nDesea realizar otra baja? 1 para continuar o 0 para salir");
                printf ("\nSu seleccion: ");
                scanf ("%d",&repetir);
                 while (repetir<0||repetir>1){
                            printf("\nError. Valor invalido. Ingrese nuevamente");
                            printf ("\nSu seleccion: ");
                            scanf("%d", &repetir);
                            }

        }while (repetir == 1);

}
// Baja fisica y permanente del archivo binario, solamente para los que tiene campo activo = 0, donde se crea un nuevo archivo .xyz y se guarda ahi.
void baja_fisica(FILE *pC,struct datos clientes){
    /*El programa funciona correctamente, modifica el archivo original sacando los valores con campo activo = 0, PERO al realizar en el mismo dia 2 veces la creacion del archivo
    se me desconfigura las posiciones del binario creditos cuando se crea el nuevo renombrado, ademas que no se guarda correactamente el archivo se mueven las posiciones, tengo que agregar una condicion si ya existe no se pueda crear por mas que el
    usuario que si esta creado el archivo con la fecha de actual no se cree otro y asi tenga que esperar al siguiente dia.
      */
    int confirmar, i,j, NroReg;
    char linea[200], fecha[50];

    //Uso libreria time.h para sacar dia / mes / año
    time_t hoy = time(NULL);
    struct tm *t = localtime(&hoy);
    strftime(fecha, sizeof(fecha)-1, "%d_%m_%Y", t);

    char NombreBaja[]="clientes_bajas_";
    char xyz[10]=".xyz";

    //CONCATENO NombreBaja + fecha
    strcat(NombreBaja,fecha);
    strcat(NombreBaja,xyz);

                printf ("\n -------------------------------- BAJA FISICA -------------------------------------------\n");
                printf ("\n*Es una modificacion PERMANENTE (si ya se creo el archivo el dia de hoy porfavor pulse 0)\n");
                printf ("\nDesea continuar?\n");
                    printf ("SI = 1 - NO = 0\n");
                    printf ("\nSu seleccion: ");
                    scanf  ("%d", &confirmar);

                    while (confirmar<0 || confirmar >1){
                        printf("\nError. Ingreso un numero invalido. Ingrese nuevamente\n");
                        scanf("%d", &confirmar);
                        }



                    if (confirmar == 1){

                        pC=fopen("creditos.dat","rb");

                        if (pC!=NULL){

                            FILE *temp,*temp2;

                            temp = fopen("creditos.temp","wb");// ACA MIGRO DATOS ACTIVOS AL TEMP
                            temp2 = fopen("creditos.temp2","w");//ACA MIGRO DATOS INACTIVOS AL TEMP2
                            fseek(pC,0,SEEK_SET);

                            fseek(pC,0,SEEK_END);
                            NroReg=ftell(pC)/sizeof(struct datos);
                            fseek(pC,0,SEEK_SET);
                            i=0;j=0;
                                while( i < NroReg ){
                                    fseek(pC,i*sizeof(struct datos),SEEK_SET);
                                    fread(&clientes,sizeof(struct datos),1,pC);
                                    i++;

                                        if(clientes.activo==1){ // SI ESTA ACTIVO SE GUARDA EN EL NUEVO BINARIO TEMPORARIO
                                        fwrite(&clientes,sizeof(struct datos),1,temp);

                                        }else if(clientes.activo==0 && clientes.orden !=0){ // SI ESTA INACTIVO Y EL CAMPO DE ORDEN ES DISTINTO DE 0 (ya que se crean campos asi al saltear posiciones sino se me guardaban tambien) SE GUARDA EN EL TEMPO 2
                                            j++;
                                            clientes.orden=j; // importante para marcar bien las posiciones en el nuevo archivo xyz
                                            fprintf(temp2,"%-6d %-10s %-10s %-10.2f %-15s %-3d %-3s %-4d %-3d %-13.2f %-8.2f %-11.2f %-6d\n", clientes.orden, clientes.nombre, clientes.apellido, clientes.importe, clientes.tipoCred, clientes.dia, clientes.mes, clientes.anio, clientes.nroCuotas, clientes.importeCuotas, clientes.iva, clientes.totalCuota, clientes.activo);
                                        }
                                }
                            fclose(temp2);
                            fclose(temp);
                            fclose(pC);

                            remove("creditos.dat");//BORRO EL ORIGINAL (previamente ya sacado los datos)
                            rename("creditos.temp","creditos.dat"); //LE CAMBIO EL NOMBRE AL CREDITOS TEMP CON SOLO LOS ACTIVOS
                            remove("creditos.temp");
                            rename("creditos.temp2",NombreBaja);//ARCHIVO CON SOLO INACTIVOS = 0
                            remove("creditos.temp2");

                            printf("\n ---------------------------");
                            printf("\n | REGISTROS ACTUALIZADOS! |");
                            printf("\n ---------------------------");

                            printf("\n Clientes eliminados permanentemente en: %s\n\n",NombreBaja);
                            getchar();

                            FILE * pD;
                            pD = fopen (NombreBaja, "r");


                            printf("---------------------------------------------------------------------------------------------------------------\n");
                            printf("%-6s %-10s %-10s %-10s %-15s %-3s %-3s %-4s %-3s %-13s %-6s %-8s %-6s\n", "Orden", "Nombre", "Apellido", "Importe", "Tipo de Credito", "Dia", "Mes", "Anio", "Cuotas", "Importe Cuota", "IVA", "Total Cuota", "Activo");
                            printf("---------------------------------------------------------------------------------------------------------------\n");

                                    while (fgets(linea, sizeof(linea), pD)) {
                                        printf("%s", linea);
                                    }

                            fclose(pD);

                        }else printf ("Error al abrir el archivo\n");



                    }else {
                        printf("\n *** OPERACION CANCELADA ***");
                        }



}



#endif
