/*
Faustino Aguilar, 2015
Se desea elaborar un programa en C que permita desplegar
un informe ordenado por salario de los empleados de una empresa.
El informe debe incluir el nombre, el salario y años de servicios
en la empresa, con el encabezado correspondiente y haciendo pausa
cada 10 registros o personas desplegadas.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int servicio;
  float salario;
  char nombre[20];
} datos;


int main() {

  FILE *fp;

  void ordenar(datos estructura[], int n);
  void imprimir(datos estructura[], int n);

  int i=0, n=15, count=10;
  char res;
  datos empleados[n];

  #ifdef _WIN32
    system("cls");
  #elif linux
    system("clear");
  #endif
  fp = fopen("registro.txt", "r");

  if (fp!=NULL) {
    while ((!feof(fp)) && (i < n)) {
      fscanf(fp, "%s %f %i", empleados[i].nombre, &empleados[i].salario, &empleados[i].servicio);
      i++;
    }
    fclose (fp);
  } else {
    printf("Error al abrir el archivo\n");
  }

  ordenar(empleados, n);

  for(i = 0; i < n; i++) {
    imprimir(empleados, count);
    if (count < n) {
      printf("Desea ver mas empleados? s/n: ");
      scanf("%c", &res);
      if (res == 's') {
        count = count + (n-count);
        #ifdef _WIN32
          system("cls");
        #elif linux
          system("clear");
        #endif
      } else {
        i = n;
      }
    } else {
      i = n;
    }
  }

  printf("-------------------------------------\n");
  printf("El programa ha terminado...\n");
  #ifdef _WIN32
    system("pause");
  #endif

  return 0;
}


void ordenar(datos e[], int n) {
  datos aux;
  int i, j;
  for (i=0; i<n; i++) {
    for (j=0; j<n-i-1; j++) {
      if (e[j].salario > e[j+1].salario) {
        aux = e[j];
        e[j] = e[j+1];
        e[j+1] = aux;
      }
    }
  }
}


void imprimir(datos e[], int n) {
  int i;
  for(i=0; i<n; i++){
    if (i == 0) {
      printf("       Administracion de empleados \n");
      printf("    Nombre    Salario Servicio (años)\n");
      printf("-------------------------------------\n");
    }
    printf("%2d. %-9s %7.2f %5i\n", i+1, e[i].nombre, e[i].salario, e[i].servicio);
  }
}
