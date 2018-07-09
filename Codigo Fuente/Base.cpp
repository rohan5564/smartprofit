/*ARCHIVO QUE CONTIENE TODA LA INFORMACION DE LAS FUNCIONES DECLARADAS EN BASE.H*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>	/*Libreria de Windows para la creacion de carpeta y operaciones sobre la consola*/
#include <locale.h>
#include "base.h"


void preorden(struct NodoProducto *raiz){
    if(raiz != NULL){
        printf("\t-%s\t, Precio = $%d\n",raiz->productos->nombre,raiz->productos->precio);
		preorden(raiz->izq);
        preorden(raiz->der);
    }
}

void InfoProducto(struct NodoProducto *raiz, char *nombreProducto){
    if(!raiz){
        puts("Primero debe agregar productos");
        Sleep(1500);
        return;
    }
    char nombre[MAX];
    while(raiz && strcpy(nombre, raiz->productos->nombre)){
        if (strcmp(nombreProducto, nombre)>0)
            raiz = raiz->der;
        else if(strcmp(nombreProducto, nombre)<0)
            raiz = raiz->izq;
        else{
            mostrarFichaProducto(raiz->productos);
            break;
        }

    }
    system("pause");
    return;
}


/*contar ingredientes*/
int contarIngredientes(struct NodoIngrediente *ingredientes){
    int total = 0;
    while(ingredientes != NULL){
        total++;
        ingredientes = ingredientes->sig;
    }
    return total;
}

/*FUNCION PARA TRANSFORMAR TODOS LOS CARACTERES DE UN STRING A MINUSCULA*/
char* lowercase(char *cadena){
	int i;

	for(i = 0; cadena[i]; i++){
		cadena[i] = tolower(cadena[i]);
	}

	return cadena;
}

/*FUNCION QUE MUESTRA EL MENU DE LA OPCION AGREGAR*/
void menuAgregar(struct Tienda *tienda){
	struct NodoProducto *nuevoProd;
	struct NodoIngrediente *nuevoIng;
	char buffer[MAX];
	char* ptr;
	int opcion, result, totalIngredientes;

	do{
		printf("Que elemento va a agregar?\n");
		printf("[1] - Producto\n");
		printf("[2] - Ingrediente\n");
		printf("[0] - Cancelar\n");
		printf("Opcion : ");
		fgets(buffer,MAX,stdin);
		buffer[strlen(buffer)-1] = '\0';
		opcion = strtol(buffer,&ptr,10);
		system("cls");
		switch(opcion){
			case 1:{
				/*CREA Y AGREGA NUEVO PRODUCTO*/
				totalIngredientes = contarIngredientes(tienda->tablaIngredientes);
				if(totalIngredientes < 2){
                    printf("cantidad de ingredientes insuficiente, agregue al menos %d mas\n", 2-totalIngredientes );
                    break;
				}
				nuevoProd = (struct NodoProducto*)malloc(sizeof(struct NodoProducto));
				nuevoProd = nuevoProducto(tienda);
				if(nuevoProd == NULL)
                    break;
				result = insertarProducto(&(tienda->listaProductos),nuevoProd);
				if(result){
					printf("Producto: \"%s\" ha sido agregado a la lista de productos!\n",nuevoProd->productos->nombre);
				}
				else{
					printf("No se pudo agregar el producto a la lista\n");
				}
				Sleep(1200);
				system("cls");
				break;
			}
			case 2:{
				/*CREA Y AGREGA NUEVO INGREDIENTE*/
				nuevoIng = (struct NodoIngrediente*)malloc(sizeof(struct NodoIngrediente));
				nuevoIng = agregarIngredienteTabla(tienda->tablaIngredientes);
				enlazarIngrediente(&(tienda->tablaIngredientes),nuevoIng);
				printf("Ingrediente: \"%s\" ha sido agregado a la tabla de ingredientes!\n",nuevoIng->ingredientes->nombre);
				Sleep(1200);
				system("cls");
				break;
			}
			case 0:{
				/*CANCELA LA ACCION*/
				printf("Saliendo...\n");
				Sleep(1200);
				system("cls");
				break;
			}
			default:{
				/*OPCION INVALIDA / NO LISTADA*/
				printf("No es una opcion valida!\n");
				Sleep(1200);
				system("cls");
				break;
			}
		}
	}while(opcion);
}

/*FUNCION QUE MUESTRA EL MENU DE LA OPCION ELIMINAR*/
void menuEliminar(struct Tienda *tienda){
	char buffer[MAX], *ptr;
	int opcion;
	struct NodoProducto *result;

	do{
		printf("Que elemento desea eliminar?\n");
		printf("[1] - Producto\n");
		printf("[2] - Ingrediente\n");
		printf("[0] - Cancelar\n");
		printf("Opcion : ");
		fgets(buffer,MAX,stdin);
		buffer[strlen(buffer)-1] = '\0';
		opcion = strtol(buffer,&ptr,10);
		system("cls");
		switch(opcion){
			case 1:{
				if(tienda->listaProductos == NULL){
					printf("No hay productos en la lista!\n");
					Sleep(1200);
					system("cls");
					break;
				}
				/*ELIMINA PRODUCTO (SI LO ENCUENTRA)*/
				printf("Ingrese producto a eliminar: ");
				fgets(buffer,MAX,stdin);
				buffer[strlen(buffer)-1]='\0';
                tienda->listaProductos = eliminarProducto((tienda->listaProductos),buffer);

				Sleep(1200);
				system("cls");
				break;
			}
			case 2:{
				if(tienda->tablaIngredientes == NULL){
					printf("No hay ingredientes en la lista!\n");
					Sleep(1200);
					system("cls");
					break;
				}
				/*ELIMINA INGREDIENTE (SI LO ENCUENTRA)*/
				printf("Ingrese ingrediente a eliminar: ");
				fgets(buffer,MAX,stdin);
				buffer[strlen(buffer)-1] = '\0';
				quitarIngredienteProductos(&(tienda->listaProductos),buffer);
				eliminarIngrediente(&(tienda->tablaIngredientes),buffer);
				printf("Ingrediente eliminado exitosamente!\n");
				Sleep(1200);
				system("cls");
				break;
			}
			case 0:{
				/*CANCELA LA ACCION*/
				printf("Volviendo...\n");
				Sleep(1200);
				system("cls");
				break;
			}
			default:{
				/*OPCION INVALIDA / NO LISTADA*/
				printf("No es una opcion valida!\n");
				Sleep(1200);
				system("cls");
				break;
			}
		}
	}while(opcion);
}

/*FUNCION QUE MUESTRA EL MENU DE LA OPCION MOSTRAR INFORMACION*/
void menuInformacion(struct Tienda *tienda){
	char buffer[MAX], *ptr;
	int opcion;

	do{
		system("cls");
		printf("Que desea saber?\n");
		printf("[1] - Productos Listados\n");
		printf("[2] - Datos especificos de un producto\n");
		printf("[3] - Ingredientes Disponibles\n");
		printf("[0] - Cancelar\n");
		printf("Opcion : ");
		fgets(buffer,MAX,stdin);
		opcion = strtol(buffer,&ptr,10);
		switch(opcion){
			case 1:{
				/*MUESTRA LA LISTA DE PRODUCTOS*/
				if(tienda->listaProductos == NULL){
                    puts("La lista de productos se encuentra vacia");
                    system("PAUSE");
                    break;
                }
                puts("INORDEN!!!:\n");
				inorden(tienda->listaProductos);
				puts("PREORDEN!!!:\n");
				preorden(tienda->listaProductos);
				system("PAUSE");
				break;
			}
			case 2:{
			    /*MUESTRA UN PRODUCTO ESPECIFICO*/
			    printf("Ingrese nombre del producto: ");
			    fgets(buffer, MAX, stdin);
			    buffer[strlen(buffer)-1]='\0';
			    InfoProducto(tienda->listaProductos, buffer);
                break;
			}
			case 3:{
				/*MUESTRA LA LISTA DE INGREDIENTES*/
				mostrarTablaIngredientes(tienda->tablaIngredientes);
				system("PAUSE");
				break;
			}
			case 0:{
				/*CANCELA LA ACCION*/
				printf("Volviendo...\n");
				Sleep(1200);
				system("cls");
				break;
			}
			default:{
				/*OPCION INVALIDA / NO LISTADA*/
				printf("No es una opcion valida\n");
				system("PAUSE");
				break;
			}
		}
	}while(opcion);
}

/*FUNCION QUE MUESTRA EL MENU DE BUSCAR -> PRODUCTO*/
void menuAccionProducto(struct Tienda *tienda){
	struct NodoProducto *busquedaProd;
	char buffer[MAX], *ptr;
	int opcion;

	printf("Escriba el producto a buscar: ");
	fgets(buffer,MAX,stdin);
	buffer[strlen(buffer)-1] = '\0';
	busquedaProd = (struct NodoProducto*)malloc(sizeof(struct NodoProducto));
	busquedaProd = buscarProducto(tienda->listaProductos,buffer);

	/*VERIFICA QUE SE ENCONTRO EL PRODUCTO*/
	if(busquedaProd != NULL){
		do{
			system("cls");
			printf("Producto encontrado.\n");
			printf("Realmente desea modificar el producto?\n");
			printf("[1] - Continuar\n");
			printf("[2] - Cancelar\n");
			printf("Opcion : ");
			fgets(buffer,MAX,stdin);
			opcion = strtol(buffer,&ptr,10);
			switch(opcion){
				case 1:{
					/*MODIFICA CAMPOS DEL PRODUCTO*/
					modificarProducto(busquedaProd->productos,tienda->tablaIngredientes);
					break;
				}
				case 2:{
					/*CANCELA LA ACCION*/
					printf("Saliendo...\n");
					Sleep(1200);
					system("cls");
					break;
				}
				default:{
					/*OPCION INVALIDA / NO lISTADA*/
					printf("No es una opcion valida, ingrese una opcion de la lista\n");
					Sleep(1200);
					system("cls");
					break;
				}
			}
		}while((opcion != 2) && (opcion != 3));
	}
	/*SI NO ENCONTRO EL PRODUCTO*/
	else{
		if(tienda->listaProductos == NULL){							//Si la lista de productos esta vacia
			printf("No hay productos en la lista\n");
		}
		else{														//Si existen productos en la lista, pero no el buscado
			printf("El producto no se encuentra en la lista\n");
		}
		Sleep(1200);
	}
}

/*FUNCION QUE ELIMINA INGREDIENTE ELEGIDO DE TODOS LOS PRODUCTOS EXISTENTES EN LA TIENDA*/
int quitarIngredienteProductos(struct NodoProducto **listaProductos, char *nombreIng){
	struct NodoProducto *rec = *listaProductos;
	struct NodoIngrediente *ing;
	int valor = 0;

	if((*listaProductos) == NULL)
		return valor;
	while(rec != NULL){
		ing = buscarIngrediente(rec->productos->listaIngrediente,nombreIng);
		if(ing != NULL){
			rec->productos->precio = (int) (rec->productos->precio - (rec->productos->listaIngrediente->ingredientes->precio + rec->productos->listaIngrediente->ingredientes->precio * 0.15));
			eliminarIngrediente(&(rec->productos->listaIngrediente),ing->ingredientes->nombre);
			valor = 1;
		}
		rec = rec->der;
	}

	return valor;
}

/*FUNCION QUE MUESTRA EL MENU DE BUSCAR -> INGREDIENTE*/
void menuAccionIngrediente(struct Tienda *tienda){
	struct NodoProducto *rec;
	struct NodoIngrediente *busquedaIng;
	char buffer[MAX], *ptr;
	int opcion,resultado,precio;

	printf("Escriba el ingrediente a buscar: ");
	fgets(buffer,MAX,stdin);
	buffer[strlen(buffer)-1]='\0';
	busquedaIng = (struct NodoIngrediente*)malloc(sizeof(struct NodoIngrediente));
	busquedaIng = buscarIngrediente(tienda->tablaIngredientes,buffer);

	/*VERIFICA SI ENCONTRO EL INGREDIENTE*/
	if(busquedaIng != NULL){
		do{
			system("cls");
			printf("Ingrediente encontrado.\n");
			printf("Realmente desea modificar el producto?\n");
			printf("[1] - Continuar\n");
			printf("[2] - Cancelar\n");
			printf("Opcion : ");
			fgets(buffer,MAX,stdin);
			opcion = strtol(buffer,&ptr,10);
			switch(opcion){
				case 1:{
					/*MODIFICA EL INGREDIENTE Y "ACTUALIZA" TODOS LOS PRODUCTOS QUE LO CONTENGAN*/
					modificarIngrediente(busquedaIng->ingredientes);
					rec = tienda->listaProductos;
					while(rec != NULL){
						precio = calculaPrecio(rec->productos->listaIngrediente);
						precio = precio + (10 - precio%10);
						rec->productos->precio = (int) (precio + (precio * 0.15));
						rec = rec->der;
					}
					system("cls");
					break;
				}
				case 2:{
					/*CANCELA LA ACCION*/
					printf("Saliendo...\n");
					Sleep(1200);
					system("cls");
					break;
				}
				default:{
					/*OPCION INVALIDA / NO LISTADA*/
					printf("No es una opcion valida, ingrese una opcion de la lista\n");
					Sleep(1200);
					system("cls");
					break;
				}
			}
		}while((opcion != 2) && (opcion != 3));
	}
	/*SI NO ENCONTRO EL INGREDIENTE*/
	else{
		if(tienda->tablaIngredientes == NULL){							//Si no hay ingredientes en la tabla de ingredientes
			printf("No hay ingredientes en la tabla\n");
		}
		else{															//Si hay ingredientes, pero no encuentra el requerido
			printf("El ingrediente no se encuentra en la tabla\n");
		}
		Sleep(1200);
	}
}

/*FUNCION QUE MUESTRA EL MENU DE LA OPCION BUSCAR*/
void menuBuscar(struct Tienda *tienda){
	char buffer[MAX];
	char* ptr;
	int opcion;

	do{
		printf("Que elemento va a modificar?\n");
		printf("[1] - Producto\n");
		printf("[2] - Ingrediente\n");
		printf("[0] - Cancelar\n");
		printf("Opcion : ");
		fgets(buffer,MAX,stdin);
		buffer[strlen(buffer)-1] = '\0';
		opcion = strtol(buffer,&ptr,10);
		switch(opcion){
			case 1:{
				/*LLAMA AL MENU DE ACCION PARA UN PRODUCTO*/
				system("cls");
				menuAccionProducto(tienda);
				break;
			}
			case 2:{
				/*LLAMA AL MENU DE ACCION PARA UN INGREDIENTE*/
				system("cls");
				menuAccionIngrediente(tienda);
				break;
			}
			case 0:{
				/*CANCELA LA ACCION*/
				printf("Volviendo...\n");
				Sleep(800);
				break;
			}
			default:{
				/*OPCION INVALIDA / NO LISTADA*/
				printf("No es una opcion valida!\n");
				Sleep(800);
				break;
			}
		}
		system("cls");
	}while(opcion);
}

/*FUNCION QUE CARGA UN INGREDIENTE DEL ARCHIVO DE INGREDIENTES*/
struct NodoIngrediente * cargaIngredienteTabla(FILE *file, char* nombreIng){
	struct NodoIngrediente *ingrediente;
	double cantidad;
	char medida[5], buffer[MAX], *ptr;
	int numero;

	/*OBTIENE LOS DATOS DEL INGREDIENTE SEGUN EL FORMATO EN QUE ESTA EN EL ARCHIVO TABLAINGREDIENTE.CSV*/

	ingrediente = (struct NodoIngrediente*) malloc(sizeof(struct NodoIngrediente));
	ingrediente->ingredientes = (struct Ingrediente*) malloc(sizeof(struct Ingrediente));
	ingrediente->ant = NULL;
	ingrediente->sig = NULL;

	strcpy(ingrediente->ingredientes->nombre,nombreIng);
	fscanf(file,"%[^;\n];",buffer);
	numero = strtol(buffer,&ptr,10);
	ingrediente->ingredientes->precio = numero;

	fscanf(file,"%[^;\n];",medida);
	strcpy(ingrediente->ingredientes->medida,medida);

	fscanf(file,"%[^;\n];",buffer);
	cantidad = strtod(buffer,&ptr);
	ingrediente->ingredientes->cantidad = cantidad;

	return ingrediente;
}

/*FUNCION QUE CARGA TODOS LOS INGREDIENTES DEL ARCHIVO DE INGREDIENTES EN UNA LISTA DOBLEMENTE ENLAZADA*/
void cargarTablaIngredientes(struct NodoIngrediente **lista){
	FILE *file;
	struct NodoIngrediente *ingrediente;
	char buffer[MAX],*username, directorio[MAX];

	/*VERIFICA QUE EL ARCHIVO EXISTE EN EL DIRECTORIO*/

	username = getenv("USERPROFILE");
	_snprintf(directorio,MAX,"%s\\SmartProfit\\TablaIngrediente.csv",username);

	file = fopen(directorio,"r");

	if(file == NULL){
		return;
	}

	ingrediente = (struct NodoIngrediente*) malloc(sizeof(NodoIngrediente));
	ingrediente->ingredientes = (struct Ingrediente*) malloc(sizeof(NodoIngrediente));

	ingrediente->ant = NULL;
	ingrediente->sig = NULL;

	/*CICLO QUE LEE TODO EL ARCHIVO*/
	fscanf(file,"%[^;];",buffer);
	while(strcmp(buffer,"EOF")!= 0){
		ingrediente = cargaIngredienteTabla(file,buffer);
		enlazarIngrediente(lista,ingrediente);
		fscanf(file," %[^;];",buffer);
	}

	fclose(file);
}

/*FUNCION QUE CARGA UN INGREDIENTE DEL PRODUCTO (DURANTE LA PRECARGA DE DATOS)*/
struct NodoIngrediente * cargarIngrediente(FILE *file, struct NodoIngrediente *tablaIng){
	struct NodoIngrediente *cargaIngrediente, *busqueda;
	char buffer[MAX], *ptr;
	double numero;
	int precio;

	/*OBTIENE LOS DATOS DE LOS INGREDIENTES COMPLEMENTANDO CON LA TABLA DE INGREDIENTES PRINCIPAL*/

	cargaIngrediente = (struct NodoIngrediente*) malloc(sizeof(NodoIngrediente));
	cargaIngrediente->ingredientes = (struct Ingrediente*) malloc(sizeof(Ingrediente));

	cargaIngrediente->sig = NULL;
	cargaIngrediente->ant = NULL;

	fscanf(file,"%[^;\n]",buffer);
	numero = strtod(buffer,&ptr);
	strcpy(cargaIngrediente->ingredientes->nombre,ptr);
	busqueda = buscarIngrediente(tablaIng,cargaIngrediente->ingredientes->nombre);

	strcpy(cargaIngrediente->ingredientes->medida,busqueda->ingredientes->medida);

	cargaIngrediente->ingredientes->cantidad = numero;
	precio = (int)((numero * busqueda->ingredientes->precio) / busqueda->ingredientes->cantidad);
	cargaIngrediente->ingredientes->precio = precio + 10 - precio%10;

	return cargaIngrediente;
}

/*FUNCION QUE CARGA UN PRODUCTO DEL ARCHIVO DE LISTAS.CSV (DURANTE LA PRECARGA DE DATOS)*/
struct NodoProducto * cargarProducto(FILE *file, char* nombreProd, struct NodoIngrediente *tablaIng){
	struct NodoProducto *cargaProducto;
	struct NodoIngrediente *ingCarga;
	int precio;
	char row = ';';
	char buffer[MAX], *ptr;

	cargaProducto = (struct NodoProducto*)malloc(sizeof(NodoProducto));
	cargaProducto->productos = (struct Producto*)malloc(sizeof(Producto));
	cargaProducto->productos->listaIngrediente = (struct NodoIngrediente*)malloc(sizeof(struct NodoIngrediente));
	cargaProducto->productos->listaIngrediente->ingredientes = (struct Ingrediente*)malloc(sizeof(struct Ingrediente));

	cargaProducto->der = NULL;
	cargaProducto->izq = NULL;
	cargaProducto->productos->listaIngrediente = NULL;


	strcpy(cargaProducto->productos->nombre,nombreProd);
	fscanf(file,"%[^;\n];",buffer);
	precio = strtol(buffer,&ptr,10);
	cargaProducto->productos->precio = precio;

	while(row != '\n'){
		ingCarga = cargarIngrediente(file,tablaIng);
		row = getc(file);
		enlazarIngrediente(&(cargaProducto->productos->listaIngrediente),ingCarga);
	}


	return cargaProducto;
}

/*FUNCION QUE CARGA LA LISTA DE PRODUCTOS CONTENIDA EN LISTAS.CSV (DURANTE LA PRECARGA DE DATOS)*/
void cargarLista(struct NodoProducto **lista,struct NodoIngrediente *tablaIng){
	FILE *file;
	struct NodoProducto *nodoCarga;
	char buffer[MAX],*username, directorio[MAX];

	/*VERIFICA QUE EL ARCHIVO EXISTE EN EL DIRECTORIO*/

	username = getenv("USERPROFILE");
	_snprintf(directorio,MAX,"%s\\SmartProfit\\Listas.csv",username);

	file = fopen(directorio,"r");
	if(file == NULL){
		return;
	}

	nodoCarga = (struct NodoProducto*) malloc(sizeof(NodoProducto));
	nodoCarga->productos = (struct Producto*) malloc(sizeof(Producto));
	nodoCarga->productos->listaIngrediente = (struct NodoIngrediente*) malloc(sizeof(NodoIngrediente));
	nodoCarga->productos->listaIngrediente->ingredientes = (struct Ingrediente*) malloc(sizeof(Ingrediente));

	nodoCarga->productos->listaIngrediente = NULL;

	/*CICLO QUE LEE TODO EL ARCHIVO*/
	fscanf(file," %[^;];",buffer);

	while(strcmp(buffer,"EOF")!= 0){
		nodoCarga = cargarProducto(file,buffer,tablaIng);
		insertarProducto(lista,nodoCarga);
		fscanf(file," %[^;];",buffer);
	}

	fclose(file);
}

/*FUNCION QUE INSERTA UN PRODUCTO DENTRO DEL ARBOL DE PRODUCTOS*/

int insertarProducto(struct NodoProducto **raiz, struct NodoProducto *nuevoNodo){
	if(*raiz == NULL){
		(*raiz) = nuevoNodo;
		(*raiz)->der = NULL;
		(*raiz)->izq = NULL;
		return 1;
	}

	if(strcmp(nuevoNodo->productos->nombre,(*raiz)->productos->nombre) < 0){
		return insertarProducto(&(*raiz)->izq, nuevoNodo);
	}
	else if(strcmp(nuevoNodo->productos->nombre,(*raiz)->productos->nombre) > 0){
		return insertarProducto(&(*raiz)->der, nuevoNodo);
	}

	return 0;
}

/*FUNCION QUE ENLAZA UN INGREDIENTE DENTRO DE LA LISTA DE INGREDIENTES DE UN PRODUCTO*/
void enlazarIngrediente(struct NodoIngrediente **head, struct NodoIngrediente *nuevo){
	struct NodoIngrediente *rec = *head;

	if(*head == NULL){
		*head = nuevo;
	}
	else{
		while(rec != NULL){
			if(rec->sig == NULL){
				rec->sig = nuevo;
				rec->sig->ant = rec;
				rec = nuevo;
			}
			rec = rec->sig;
		}
	}
}

/*FUNCION QUE BUSCA UN PRODUCTO EN LA LISTA DE PRODUCTOS*/
struct NodoProducto *buscarProducto(struct NodoProducto *raiz, char *nombreBuscado){
	char *comp = (char*)malloc(sizeof(char));
	strcpy(comp,nombreBuscado);

	if((raiz == NULL) || (strcmp(lowercase(raiz->productos->nombre),lowercase(comp)) == 0)){
		return raiz;
	}

	if(strcmp(raiz->productos->nombre,nombreBuscado) < 0){
		return buscarProducto(raiz->der,nombreBuscado);
	}
	else if (strcmp(raiz->productos->nombre,nombreBuscado) > 0){
		return buscarProducto(raiz->izq,nombreBuscado);
	}

	return NULL;
}

/*FUNCION QUE CREA UN INGREDIENTE PARA AGREGAR A LA LISTA DE INGREDIENTES PRINCIPAL*/
struct NodoIngrediente* agregarIngredienteTabla(struct NodoIngrediente *tablaIng){
	struct NodoIngrediente *nuevo, *busqueda;
	char buffer[MAX];
	char *ptr;
	int numero;
	double cantidad;

	nuevo = (struct NodoIngrediente*)malloc(sizeof(struct NodoIngrediente));
	nuevo->ingredientes = (struct Ingrediente*)malloc(sizeof(struct Ingrediente));

	/*VERIFICA QUE EL INGREDIENTE SEA NUEVO Y DE TAMAÑO VALIDO*/
	do{
		printf("Ingrese ingrediente: ");
		fgets(buffer,MAX,stdin);
		buffer[strlen(buffer)-1]='\0';
		busqueda = buscarIngrediente(tablaIng,lowercase(buffer));
		if(busqueda != NULL){
			printf("El ingrediente esta en la tabla!\n");
			Sleep(1200);
			system("cls");
		}
	}while((busqueda != NULL) || (strlen(buffer) <= 2));
	strcpy(nuevo->ingredientes->nombre,lowercase(buffer));

	/*ELIGE LA UNIDAD DE MEDIDA (SISTEMA INTERNACIONAL DE UNIDADES)*/

	do{
		printf("En que unidad se mide?\n");
		printf("[1] - Kilogramos [Kg]\n");
		printf("[2] - Litros [Lt]\n");
		printf("[3] - Unidades [U]\n");
		printf("Opcion: ");
		fgets(buffer,MAX,stdin);
		numero = strtol(buffer,&ptr,10);
		switch(numero){
			/*OPCIONES VALIDAS*/
			case 1:{
				strcpy(nuevo->ingredientes->medida,"Kg");
				break;
			}
			case 2:{
				strcpy(nuevo->ingredientes->medida,"Lt");
				break;
			}
			case 3:{
				strcpy(nuevo->ingredientes->medida,"U");
				break;
			}
			/*OPCION INVALIDA*/
			default:{
				printf("No es una opcion valida!\n");
				Sleep(800);
				system("cls");
				break;
			}
		}
	}while((numero != 1) && (numero != 2) && (numero!= 3));

	/*OBTIENE LA PORCION Y EL PRECIO POR PORCION DEL INGREDIENTE*/

	printf("Cuanto es una porcion del ingrediente y cuanto cuesta? (Ej: 1[Kg] de Harina cuesta $850 app.)\n");
	printf("Porcion/Unidad: ");
	do{
		fgets(buffer,MAX,stdin);
		cantidad = strtod(buffer,&ptr);
	}while(cantidad <= 0);
	nuevo->ingredientes->cantidad = cantidad;

	printf("Precio por porcion/unidad: ");
	do{
		fgets(buffer,MAX,stdin);
		numero = strtol(buffer,&ptr,10);
	}while(numero <= 0);
	nuevo->ingredientes->precio = numero;

	nuevo->ant = NULL;
	nuevo->sig = NULL;

	return nuevo;
}

/*FUNCION QUE CREA UN INGREDIENTE PARA AGREGAR AL PRODUCTO*/
struct NodoIngrediente* agregarIngrediente(struct NodoIngrediente *listaIng ,struct NodoIngrediente *tablaIng){
	struct NodoIngrediente *nuevo, *busqueda, *repetido;
	char buffer[MAX];
	char *ptr;
	int precio;
	double cantidad;

	nuevo = (struct NodoIngrediente*)malloc(sizeof(struct NodoIngrediente));
	nuevo->ingredientes = (struct Ingrediente*)malloc(sizeof(struct Ingrediente));

	/*VERIFICA QUE EL INGREDIENTE EXISTE EN LA LISTA PRINCIPAL Y QUE NO ES REPETIDO EN EL PRODUCTO*/

	do{
		printf("Ingrese ingrediente: ");
		fgets(buffer,MAX,stdin);
		buffer[strlen(buffer)-1]='\0';
		busqueda = buscarIngrediente(tablaIng,buffer);
		repetido = buscarIngrediente(listaIng,buffer);
		if(busqueda == NULL){
			printf("El ingrediente no se encuentra en la lista de ingredientes validos!\n");
			Sleep(1200);
			system("cls");
		}
		if(repetido != NULL){
			printf("El ingrediente ya fue agregado!\n");
			Sleep(1200);
			system("cls");
		}
	}while((busqueda == NULL) || (repetido != NULL) || (strlen(buffer) < 2));

	strcpy(nuevo->ingredientes->nombre,busqueda->ingredientes->nombre);
	strcpy(nuevo->ingredientes->medida,busqueda->ingredientes->medida);

	printf("Que cantidad necesita? (En [%s]): ",nuevo->ingredientes->medida);
	do{
		fgets(buffer,MAX,stdin);
		cantidad = strtod(buffer,&ptr);
	}while(cantidad <= 0);

	nuevo->ingredientes->cantidad = cantidad;
	precio = (int)( busqueda->ingredientes->precio/busqueda->ingredientes->cantidad );
	nuevo->ingredientes->precio = (int)(precio*cantidad);

	nuevo->ant = NULL;
	nuevo->sig = NULL;

	return nuevo;
}

/*FUNCION QUE CALCULA EL PRECIO DE UN PRODUCTO*/
int calculaPrecio(struct NodoIngrediente *ingredientes){
	int precio = 0;
    int i = 100;
	while(ingredientes != NULL){
		precio +=  ingredientes->ingredientes->precio;
		i += 10;
		ingredientes = ingredientes->sig;
	}

	return (precio*i)/100;
}

/*FUNCION QUE CREA UN PRODUCTO PARA AGREGAR A LA LISTA DE PRODUCTOS*/
struct NodoProducto* nuevoProducto(struct Tienda *tienda){
	struct NodoProducto *nuevo, *busqueda;
	struct NodoIngrediente *nuevoIngrediente;
	char buffer[MAX];
	char *ptr;
	int datos,i = 0,precio;

	nuevo = (struct NodoProducto *)malloc(sizeof(struct NodoProducto));
	nuevo->productos = (struct Producto *)malloc(sizeof(struct Producto));
	nuevo->productos->listaIngrediente = (struct NodoIngrediente *)malloc(sizeof(struct NodoIngrediente));
	nuevo->productos->listaIngrediente->ingredientes = (struct Ingrediente *)malloc(sizeof(struct Ingrediente));

	nuevo->productos->listaIngrediente = NULL;

	/*VERIFICA QUE EL PRODUCTO NO HAYA SIDO INGRESADO ANTES / SEA REPETIDO*/

	do{
		printf("Ingrese nombre de su producto: ");
		fgets(buffer,MAX,stdin);
		buffer[strlen(buffer)-1] = '\0';
		busqueda = buscarProducto(tienda->listaProductos,buffer);
		if(busqueda != NULL){
			printf("No se permiten productos repetidos!\n");
			Sleep(750);
			system("cls");
		}
	}while((busqueda != NULL) || (strlen(buffer) < 2));

	strcpy(nuevo->productos->nombre,lowercase(buffer));

	printf("\nDe que esta hecho su producto?\n");
	printf("Cantidad de Ingredientes (Minimo 2), ingrese 0 para volver al menu anterior: ");
	do{
		fgets(buffer,MAX,stdin);
		datos = strtol(buffer,&ptr,10);
		system("cls");
		if(datos > contarIngredientes(tienda->tablaIngredientes))
            printf("faltan %d ingredientes por ingresar a la lista, ponga una cantidad valida o introduzca 0 para volver al menu anterior: ", datos-contarIngredientes(tienda->tablaIngredientes));
        else if(datos<2){
            if(!datos){
                puts("volviendo...");
                Sleep(700);
                system("cls");
                free(nuevo);
                return NULL;
            }
            puts("debe contener al menos 2 ingredientes, ponga una cantidad valida o introduzca 0 para volver al menu anterior: ");
        }
	}while( (datos < 2 && datos ) || (datos > contarIngredientes(tienda->tablaIngredientes)));
	nuevo->productos->cantIngredientes = datos;

	while(i < (nuevo->productos->cantIngredientes)){
		nuevoIngrediente = agregarIngrediente(nuevo->productos->listaIngrediente,tienda->tablaIngredientes);
		enlazarIngrediente(&(nuevo->productos->listaIngrediente),nuevoIngrediente);
		i++;
		system("cls");
	}
	nuevo->productos->precio = calculaPrecio(nuevo->productos->listaIngrediente);;

	nuevo->der=NULL;
	nuevo->izq=NULL;

	return nuevo;
}

/*FUNCION QUE ELIMINA UNA LISTA DE INGREDIENTES COMPLETA*/
void eliminarListaIng(struct NodoIngrediente **head){
	struct NodoIngrediente *rec = *head, *next;

	while(rec != NULL){
		next = rec->sig;
		free(rec);
		rec = next;
	}

	*head = NULL;
}

/*FUNCION QUE BUSCA UN INGREDIENTE EN LA LISTA DE INGREDIENTES DE UN PRODUCTO*/
struct NodoIngrediente* buscarIngrediente(struct NodoIngrediente *head, char *nombreIng){
    struct NodoIngrediente *rec = head;

	while(rec != NULL){
		if(strcmp(rec->ingredientes->nombre,nombreIng) == 0){
			return rec;
		}
		rec = rec->sig;
	}
	return NULL;
}

/*FUNCION QUE ELIMINA UN INGREDIENTE DE UNA LISTA DE INGREDIENTES*/
void eliminarIngrediente(struct NodoIngrediente **head, char* nombreIng){
	struct NodoIngrediente *elim = NULL;

	/*VERIFICA LA EXISTENCIA DE INGREDIENTES*/
	if(*head == NULL)
		printf("No hay elementos para eliminar\n");
	else{
		elim = buscarIngrediente(*head,nombreIng);

		/*VERIFICA SI ENCONTRO EL INGREDIENTE*/
		if(elim != NULL){
			if(elim == *head){											//Es el primer elemento de la lista
				if(elim->sig == NULL){										//Si es el unico elemento
					printf("No se puede quedar sin ingredientes!\n");
				}
				else{														//Hay mas elementos
					*head = elim->sig;
					elim->sig->ant = NULL;
					free(elim);
				}
			}
			else{
				if(elim->sig == NULL){									//Ultimo elemento de la Lista
					elim->ant->sig = NULL;
					free(elim);
				}
				else{													//Es un elemento entremedio
					elim->ant->sig = elim->sig;
					elim->sig->ant = elim->ant;
					free(elim);
				}
			}
		}
		else{
			printf("No se encontro el ingrediente");
		}
	}
	Sleep(750);
}

/*FUNCION QUE BUSCA EL ULTIMO NODO DEL SUBARBOL PARA REEMPLAZAR EL NODO A ELIMINAR*/
struct NodoProducto *cambioNodo(struct NodoProducto *raizBusqueda){
	if((raizBusqueda->izq == NULL) && (raizBusqueda->der == NULL)){
		return raizBusqueda;
	}

	if(raizBusqueda->izq){
		return cambioNodo(raizBusqueda->izq);
	}
	else{
		return cambioNodo(raizBusqueda->der);
	}
}


/*FUNCION QUE ELIMINA UN PRODUCTO DE LA LISTA DE PRODUCTOS*/
struct NodoProducto* eliminarProducto(struct NodoProducto *raizProductos, char *nombreProducto){

	if(!raizProductos){
        puts("elemento no encontrado");
        return raizProductos;
	}

	if(strcmp(raizProductos->productos->nombre, nombreProducto) < 0 )
        raizProductos->der = eliminarProducto(raizProductos->der, nombreProducto);
    else if(strcmp(raizProductos->productos->nombre, nombreProducto) > 0 )
        raizProductos->izq = eliminarProducto(raizProductos->izq, nombreProducto);
	else{
        if(!raizProductos->izq){
            struct NodoProducto *tmp = raizProductos->der;
            free(raizProductos);
            return tmp;
        }
        else if(!raizProductos->der){
            struct NodoProducto *tmp = raizProductos->izq;
            free(raizProductos);
            return tmp;
        }
        struct NodoProducto *mayor = raizProductos->izq;
        while(mayor->der)
            mayor = mayor->der;
        memcpy( &(raizProductos->productos), &(mayor->productos), sizeof(struct Producto));
        raizProductos->izq = eliminarProducto(raizProductos->izq, mayor->productos->nombre);
	}

	return raizProductos;
}

/*FUNCION QUE MUESTRA LA FICHA DE UN PRODUCTO (NOMBRE, PRECIO, INGREDIENTES)*/
void mostrarFichaProducto(struct Producto *producto){
	struct NodoIngrediente *rec = producto->listaIngrediente;

	printf("\t-------------------------------------\n");
	printf("\t|Nombre:\t%s\n",producto->nombre);
	printf("\t|Precio:\t$%d\n",producto->precio);
	printf("\t|Ingredientes:\n");
	while(rec != NULL){
		printf("\t|° %.3lf[%s] de %s\n",rec->ingredientes->cantidad, rec->ingredientes->medida, rec->ingredientes->nombre);
		rec = rec->sig;
	}
	printf("\t-------------------------------------\n");
}

/*FUNCION QUE MUESTRA LA FICHA DE UN INGREDIENTE (NOMBRE, PRECIO POR PORCION, UNIDAD DE MEDIDA (SISTEMA INTERNACIONAL), PORCION)*/
void mostrarFichaIngrediente(struct Ingrediente *ingrediente){

	printf("\t-------------------------------------\n");
	printf("\t|Nombre:\t%s\n",ingrediente->nombre);
	printf("\t|Precio por porcion:\t$%d\n",ingrediente->precio);
	printf("\t|Unidad Medida:\t[%s]\n",ingrediente->medida);
	printf("\t|Porcion:\t%.3lf\n",ingrediente->cantidad);
	printf("\t-------------------------------------\n");
}

/*FUNCION QUE PERMITE MODIFICAR LA FICHA DE UN INGREDIENTE DE LA LISTA DE INGREDIENTES PRINCIPAL*/
void modificarIngrediente(struct Ingrediente *ingrediente){
	char buffer[MAX], *ptr;
	int opcion, precio;
	double cantidad;

	do{
		/*MUESTRA LOS DATOS DEL INGREDIENTE ELEGIDO*/
		mostrarFichaIngrediente(ingrediente);

		printf("Que campo desea modificar?\n");
		printf("[1] - Nombre Ingrediente\n");
		printf("[2] - Precio por porcion\n");
		printf("[3] - Unidad de medida\n");
		printf("[4] - Porcion\n");
		printf("[5] - Cancelar\n");
		printf("Opcion : ");
		fgets(buffer,MAX,stdin);
		opcion = strtol(buffer,&ptr,10);
		switch(opcion){
			case 1:{
				/*CAMBIO DE NOMBRE DEL INGREDIENTE*/
				printf("Ingrese nuevo nombre: ");
				fgets(buffer,MAX,stdin);
				buffer[strlen(buffer)-1] = '\0';
				strcpy(ingrediente->nombre,buffer);
				system("cls");
				break;
			}
			case 2:{
				/*CAMBIO DE PRECIO DEL INGREDIENTE*/
				do{
					printf("Ingrese nuevo precio: ");
					fgets(buffer,MAX,stdin);
					precio = strtol(buffer,&ptr,10);
				}while(precio <= 0);
				ingrediente->precio = precio;
				system("cls");
				break;
			}
			case 3:{
				/*CAMBIO DE UNIDAD DE MEDIDA (SISTEMA INTERNACIONAL DE UNIDADES)*/
				do{
					printf("Elija una unidad de medida\n");
					printf("[1] - Kilogramos [Kg]\n");
					printf("[2] - Litros [Lt]\n");
					printf("[3] - Unidades [U]\n");
					printf("Opcion : ");
					fgets(buffer,MAX,stdin);
					opcion = strtol(buffer,&ptr,10);
					switch(opcion){
						/*OPCIONES VALIDAS*/
						case 1:{
							strcpy(ingrediente->medida,"Kg");
							break;
						}
						case 2:{
							strcpy(ingrediente->medida,"Lt");
							break;
						}
						case 3:{
							strcpy(ingrediente->medida,"U");
							break;
						}
						/*OPCION INVALIDA*/
						default:{
							printf("No es una opcion valida!\n");
							Sleep(800);
							break;
						}
					}
					system("cls");
				}while((opcion != 1) && (opcion != 2) && (opcion != 3));
				break;
			}
			case 4:{
				/*CAMBIO DE PORCION DE INGREDIENTE*/
				printf("Ingrese nueva porcion (numero, decimal si es necesario): ");
				fgets(buffer,MAX,stdin);
				cantidad = strtod(buffer,&ptr);
				ingrediente->cantidad = cantidad;
				system("cls");
				break;
			}
			case 5:{
				/*CANCELA LA ACCION*/
				printf("Saliendo...\n");
				Sleep(800);
				system("cls");
				break;
			}
			default:{
				/*OPCION INVALIDA / NO LISTADA*/
				printf("No es una opcion valida!\n");
				Sleep(800);
				system("cls");
				break;
			}
		}
	}while(opcion != 5);
}

/*FUNCION QUE PERMITE MODIFICAR LA FICHA DE UN PRODUCTO*/
void modificarProducto(struct Producto *producto, struct NodoIngrediente *listaIng){
	struct NodoIngrediente *nuevo;
	char buffer[MAX], *ptr;
	int opcion,opcionIng,precio;

	do{
		/*MUESTRA LOS DATOS DEL PRODUCTO ELEGIDO*/
		mostrarFichaProducto(producto);

		printf("Que desea modificar?\n");
		printf("[1] - Nombre Producto\n");
		printf("[2] - Ingredientes\n");
		printf("[3] - Cancelar\n");
		printf("Opcion : ");
		fgets(buffer,MAX,stdin);
		opcion = strtol(buffer,&ptr,10);
		switch(opcion){
			case 1:{
				/*CAMBIO DE NOMBRE INGREDIENTE*/
				printf("Ingrese nuevo nombre: ");
				fgets(buffer,MAX,stdin);
				buffer[strlen(buffer)-1] = '\0';
				strcpy(producto->nombre,buffer);
				break;
			}
			case 2:{
				/*CAMBIO EN LA LISTA DE INGREDIENTES DEL PRODUCTO*/
				do{
					system("cls");
					printf("Como quiere modificar los ingredientes?\n");
					printf("[1] - Agregar\n");
					printf("[2] - Eliminar\n");
					printf("[3] - Cancelar\n");
					printf("Opcion: ");
					fgets(buffer,MAX,stdin);
					opcionIng = strtol(buffer,&ptr,10);
					switch(opcionIng){
						case 1:{
							/*AGREGA UN INGREDIENTE AL PRODUCTO*/
							nuevo = (struct NodoIngrediente*)malloc(sizeof(struct NodoIngrediente));
							nuevo = agregarIngrediente(producto->listaIngrediente,listaIng);
							enlazarIngrediente(&(producto->listaIngrediente),nuevo);
							printf("Ingrediente agregado!\n");
							Sleep(800);
							break;
						}
						case 2:{
							/*ELIMINA UN INGREDIENTE DEL PRODUCTO*/
							printf("Ingrese ingrediente a eliminar: ");
							fgets(buffer,MAX,stdin);
							buffer[strlen(buffer)-1]='\0';
							eliminarIngrediente(&(producto->listaIngrediente),buffer);
							printf("Ingrediente eliminado exitosamente!\n");
							Sleep(800);
							break;
						}
						case 3:{
							/*CANCELA LA ACCION*/
							printf("Volviendo...\n");
							Sleep(800);
							break;
						}
						default:{
							/*OPCION INVALIDA / NO LISTADA*/
							printf("No es una opcion valida\n");
							break;
						}
					}
					/*ACTUALIZA EL PRECIO DEL PRODUCTO*/ //No funciona bien
					precio = calculaPrecio(producto->listaIngrediente);
					precio = (int) (precio + (10 - precio%10) + (precio * 0.15));
					producto->precio = precio;
				}while(opcionIng != 3);
				break;
			}
		}
		system("cls");
	}while(opcion != 3);
}

/*FUNCION QUE ESCRIBE LOS DATOS EN EL ARCHIVO*/

void escrituraDatos(struct NodoProducto *raiz, FILE *file){
	struct NodoIngrediente *rec;

	if(raiz != NULL){
		escrituraDatos(raiz->izq,file);
		fprintf(file,"%s;%d",raiz->productos->nombre,raiz->productos->precio);
		rec = raiz->productos->listaIngrediente;
		while(rec != NULL){
			fprintf(file,";%.3lf%s", rec->ingredientes->cantidad, rec->ingredientes->nombre);
			rec = rec->sig;
		}
		fprintf(file,"\n");
		escrituraDatos(raiz->der,file);
	}
}

/*FUNCION QUE PERMITE GUARDAR LA LISTA DE PRODUCTOS EN UN ARCHIVO (LISTAS.CSV)*/

void guardar(struct NodoProducto *raiz){
	FILE *file;
	char *username, directorio[MAX];

	/*ABRE EL ARCHIVO EN EL DIRECTORIO INDICADO (DEFAULT)*/
	username = getenv("USERPROFILE");
	_snprintf(directorio,MAX,"%s\\SmartProfit\\Listas.csv",username);

	file = fopen(directorio,"w");

	/*VERIFICA SI EL ARBOL ESTA VACIO*/
	if(raiz == NULL){
		fprintf(file,"EOF;");
		return;
	}
	else{
		escrituraDatos(raiz,file);
		fprintf(file,"EOF;");
	}

	fclose(file);
}

/*FUNCION QUE PERMITE GUARDAR LA LISTA O TABLA DE INGREDIENTES PRINCIPAL EN UN ARCHIVO (TABLAINGREDIENTES.CSV)*/
void guardarTablaIngredientes(struct NodoIngrediente *head){
	FILE *file;
	struct NodoIngrediente *rec = head;
	char *username, directorio[MAX];

	/*ABRE EL ARCHIVO EN EL DIRECTORIO INDICADO (DEFAULT)*/
	username = getenv("USERPROFILE");
	_snprintf(directorio,MAX,"%s\\SmartProfit\\TablaIngrediente.csv",username);

	file = fopen(directorio,"w");

	/*VERIFICA SI LA TABLA ESTA VACIA*/
	if(head == NULL){
		fprintf(file,"EOF;");
		fclose(file);
		return;
	}
	while(rec != NULL){
		fprintf(file,"%s;%d;%s;%.3lf\n",rec->ingredientes->nombre,rec->ingredientes->precio,rec->ingredientes->medida,rec->ingredientes->cantidad);
		rec = rec->sig;
	}
	fprintf(file,"EOF;");

	fclose(file);
}

/*FUNCION QUE MUESTRA TODA LA LISTA DE PRODUCTOS DISPONIBLES JUNTO CON SU PRECIO*/
void inorden(struct NodoProducto *raiz){
    if(raiz != NULL){
		inorden(raiz->izq);
        printf("\t-%s\t, Precio = $%d\n",raiz->productos->nombre,raiz->productos->precio);
        inorden(raiz->der);
    }
}

/*FUNCION QUE MUESTRA TODOS LOS INGREDIENTES DE LA LISTA DE INGREDIENTES PRINCIPAL JUNTO CON SU PRECIO POR PORCION*/
void mostrarTablaIngredientes(struct NodoIngrediente *tablaIng){
	struct NodoIngrediente *rec = tablaIng;

	/*VERIFICA SI LA TABLA DE INGREDIENTES ESTA VACIA*/
	if(tablaIng == NULL){
		printf("No hay ingredientes en la tabla, se recomienda crear tabla de ingredientes antes de seguir usando SmartProfit!\n");
	}
	else{
        printf("\t%100s\t||\tPRECIO POR UNIDAD\n\n", "INGREDIENTES");

		while(rec != NULL){
			printf("\t%100s\t||\t$%d [%.3lf %s]\n",rec->ingredientes->nombre,rec->ingredientes->precio, rec->ingredientes->cantidad,rec->ingredientes->medida);
			rec = rec->sig;
		}
	}
}
/*
void ordenar(struct NodoProducto **listaProducto){
	struct NodoProducto *rec = *listaProducto;
	struct Producto *data;

	if(*listaProducto == NULL){
		return;
	}
	while(rec->sig != NULL){
		if(strcmp(rec->productos->nombre,rec->sig->productos->nombre) > 0){
			data = rec->productos;
			rec->productos = rec->sig->productos;
			rec->sig->productos = data;
		}
		rec = rec->sig;
	}
}


*/







//----------------------------------------------------------------------
/*FUNCION QUE ENLAZA UN PRODUCTO DENTRO DE LA LISTA DE PRODUCTOS
void _enlazarProducto(struct NodoProducto **head, struct NodoProducto *nuevo){
	struct NodoProducto *rec = *head;

	if(*head == NULL){
		*head = nuevo;
	}
	else{
		while(rec != NULL){
			if(rec->sig == NULL){
				rec->sig = nuevo;
				nuevo->ant = rec;
				rec = nuevo;
			}
			rec = rec->sig;
		}
	}
}
//-----------------------------------------------------------------------

struct NodoProducto* _buscarProducto(struct NodoProducto *head, char *nombreProd){
    struct NodoProducto *rec = head;
    nombreProd[strlen(nombreProd)-1]='\0';

	while(rec != NULL){
		if(strcmp(rec->productos->nombre,nombreProd) == 0){
			return rec;
		}
		rec = rec->sig;
	}
	return NULL;
}

//_----------------------------------------------------------------------

void _eliminarProducto(struct NodoProducto **head, char* nombreProd){
	struct NodoProducto *elim=NULL;

	//VERIFICA LA EXISTENCIA DE PRODUCTOS
	if(*head == NULL)
		printf("No hay elementos para eliminar\n");
	else{
		elim = buscarProducto(*head,nombreProd);

		//VERIFICA SI ENCONTRO EL PRODUCTO
		if(elim != NULL){
			eliminarListaIng(&(elim->productos->listaIngrediente));
			if(elim == *head){											//Es el primer elemento de la lista
				if(elim->sig == NULL){										//Si es el unico elemento
					*head = NULL;
					free(elim);
				}
				else{														//Hay mas elementos
					*head = elim->sig;
					elim->sig->ant = NULL;
					free(elim);
				}
			}
			else{
				if(elim->sig == NULL){									//Ultimo elemento de la Lista
					elim->ant->sig = NULL;
					free(elim);
				}
				else{													//Es un elemento entremedio
					elim->ant->sig = elim->sig;
					elim->sig->ant = elim->ant;
					free(elim);
				}
			}
		}
		else{
			printf("No se encontro el producto");
		}
	}
}

//-----------------------------------------------------------------------------

void _guardar(struct NodoProducto *head){
	FILE *file;
	struct NodoProducto *rec = head;
	struct NodoIngrediente *lista;
	char *username, directorio[MAX];

	//ABRE EL ARCHIVO EN EL DIRECTORIO INDICADO (DEFAULT)
	username = getenv("USERPROFILE");
	_snprintf(directorio,MAX,"%s\\SmartProfit\\Listas.csv",username);

	file = fopen(directorio,"w");

	//VERIFICA SI LA LISTA ESTA VACIA
	if(head == NULL){
		fprintf(file,"EOF;");
		return;
	}
	while(rec != NULL){
		lista = rec->productos->listaIngrediente;
		fprintf(file,"%s;%lf",rec->productos->nombre,rec->productos->precio);
		while(lista != NULL){
			fprintf(file,";%.3lf%s", lista->ingredientes->cantidad, lista->ingredientes->nombre);
			lista = lista->sig;
		}
		fprintf(file,"\n");
		rec = rec->sig;
	}
	fprintf(file,"EOF;");

	fclose(file);
}

//----------------------------------------------------------------------

void _mostrarListaProductos(struct NodoProducto *lista){
	struct NodoProducto *rec = lista;

	ordenar(&lista);

	//VERIFICA SI LA LISTA ESTA VACIA
	if(lista == NULL){
		printf("No hay productos para mostrar\n");
	}
	else{
		printf("Productos:\n");
		while(rec != NULL){
			printf("\t-%s\t, Precio = $%d\n",rec->productos->nombre,rec->productos->precio);
			rec = rec->sig;
		}
	}
}

//------------------------------------------------------------------------

/*FUNCION QUE PERMITE EXPORTAR UNA LISTA SIMPLE CON NOMBRE Y PRECIO A UNA DIRECCION DESEADA
void exportarListaProductos(struct Tienda *tienda){
	FILE *file;
	struct NodoProducto *rec = tienda->listaProductos;
	char *username, directorio[MAX], buffer[MAX];

	//VERIFICA SI HAY PRODUCTOS EN LA LISTA
	if(tienda->listaProductos == NULL){
		printf("No hay productos en la lista!\n");
		Sleep(800);
		system("cls");
		return;
	}

	//PIDE AL USUARIO ELEGIR UNA DIRECCION EXISTENTE PARA GUARDAR EL ARCHIVO
	username = getenv("USERPROFILE");
	do{
		printf("Elija el destino del archivo (Default : %s\\SmartProfit):\n",username);
		printf("%s\\",username);
		fgets(buffer,MAX,stdin);
		buffer[strlen(buffer)-1] = '\0';
		_snprintf(directorio,MAX,"%s\\%s\\Productos.csv",username,buffer);
		file = fopen(directorio,"w");
		if(file == NULL){
			printf("La direccion no existe, elija una direccion valida/existente!\n");
			Sleep(1200);
			system("cls");
		}
	}while(file == NULL);

	while(rec != NULL){
		fprintf(file,"%s;%d\n",rec->productos->nombre, rec->productos->precio);
		rec = rec->sig;
	}

	printf("Lista exportada exitosamente!\n");
	printf("Su archivo se encuentra en: %s\n",directorio);

	system("PAUSE");
	system("cls");

	fclose(file);
}*/
