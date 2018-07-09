#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "base.h"
#include <locale.h>


int main(){

    setlocale(LC_ALL, ".OCP");   ///separador decimal a coma, locale.h

	struct Tienda *tienda;
	char buffer[MAX], *ptr, path[MAX_PATH];
	int opcion;
	/*CREACION DE UNA CARPETA DEL PROYECTO*/
	_snprintf(path,MAX_PATH,"%s\\SmartProfit",getenv("USERPROFILE"));
	CreateDirectory(path,NULL);

	tienda = (struct Tienda*) malloc(sizeof(struct Tienda));
	tienda->listaProductos = NULL;
	tienda->tablaIngredientes = NULL;
	tienda->cantProductos = 0;

	/*PRECARGA DE ARCHIVOS*/
	cargarTablaIngredientes(&(tienda->tablaIngredientes));
	cargarLista(&(tienda->listaProductos),tienda->tablaIngredientes);
    printf("Bienvenido a SmartProfit\n");
    Sleep(1700);
    system("cls");
	/*MENU PRINCIPAL*/
	do{
		printf("Que desea hacer:\n");
		printf("[1] - Agregar un elemento\n");
		printf("[2] - Modificar un elemento\n");
		printf("[3] - Eliminar un elemento\n");
		printf("[4] - Mostrar Informacion\n");
		printf("[0] - Salir\n");
		printf("Opcion : ");
		fgets(buffer,MAX,stdin);
		buffer[strlen(buffer)-1] = '\0';
		opcion = strtol(buffer,&ptr,10);
		system("cls");
		switch(opcion){
			case 1:{
				menuAgregar(tienda);
				break;
			}
			case 2:{
				menuBuscar(tienda);
				break;
			}
			case 3:{
				menuEliminar(tienda);
				break;
			}
			case 4:{
				menuInformacion(tienda);
				break;
			}
			case 0:{
				break;
			}
			default:{
				printf("No es una opcion valida, ingrese una opcion de la lista\n");
				Sleep(1200);
				system("cls");
				break;
			}
		}
	}while(opcion != 0 || ((opcion == 0) && (strcmp(buffer,"") == 0)));

	printf("Gracias por usar SmartProfit!\n\n");
	Sleep(1200);
	system("cls");

	/*GUARDADO DE DATOS*/
	guardar(tienda->listaProductos);
	guardarTablaIngredientes(tienda->tablaIngredientes);

	return 0;
}
