/*LIBRERIA PROPIA DEL PROYECTO*/
#ifndef ___Base__H__
#define ___Base__H__

#define MAX 100

struct Ingrediente{
	char nombre[MAX];
	int precio;
	char medida[5];
	double cantidad;
};

struct NodoIngrediente{
	struct Ingrediente *ingredientes;
	struct NodoIngrediente *ant, *sig;
};

struct Producto{
	struct NodoIngrediente *listaIngrediente;
	char nombre[MAX];
	int precio;
	int cantIngredientes;
};

struct NodoProducto{
	struct Producto *productos;
	struct NodoProducto *izq, *der;
};

struct Tienda{
	struct NodoProducto *listaProductos;
	struct NodoIngrediente *tablaIngredientes;
	int cantProductos;
};

//Funciones de Carga y Guardado
void cargarTablaIngredientes(struct NodoIngrediente **);
void cargarLista(struct NodoProducto **, struct NodoIngrediente *);
void guardar(struct NodoProducto *);
void guardarTablaIngredientes(struct NodoIngrediente *);
struct NodoIngrediente * cargaIngredienteTabla(FILE *, char*);
struct NodoIngrediente * cargarIngrediente(FILE *, struct NodoIngrediente *);
struct NodoProducto * cargarProducto(FILE *, char*, struct NodoIngrediente *);
//void exportarListaProductos(struct Tienda *);

//Funciones Operacion sobre Producto
struct NodoProducto* nuevoProducto(struct Tienda *tienda);
struct NodoProducto* buscarProducto(struct NodoProducto *, char *);
struct NodoProducto* eliminarProducto(struct NodoProducto *, char *);
int insertarProducto(struct NodoProducto **raiz, struct NodoProducto *nuevoNodo);
void modificarProducto(struct Producto *, struct NodoIngrediente *);
void mostrarFichaProducto(struct Producto *);
int calculaPrecio(struct NodoIngrediente *);
int quitarIngredienteProductos(struct NodoProducto **, char *);
void actualizarProductos(struct NodoProducto **, char *);



//void ordenar(struct NodoProducto **);

//Funciones Operacion sobre Ingrediente
struct NodoIngrediente* agregarIngredienteTabla(struct NodoIngrediente *);
struct NodoIngrediente* agregarIngrediente(struct NodoIngrediente * ,struct NodoIngrediente *);
struct NodoIngrediente* buscarIngrediente(struct NodoIngrediente *, char *);
void eliminarIngrediente(struct NodoIngrediente **, char*);
void modificarIngrediente(struct Ingrediente *);
void enlazarIngrediente(struct NodoIngrediente **, struct NodoIngrediente *);
void eliminarListaIng(struct NodoIngrediente **);
void mostrarFichaIngrediente(struct Ingrediente *);

//Funciones Menu
void menuAgregar(struct Tienda *);
void menuEliminar(struct Tienda *);
void menuBuscar(struct Tienda *);
void menuAccionProducto(struct Tienda *);
void menuAccionIngrediente(struct Tienda *);
void menuInformacion(struct Tienda *);
//void mostrarListaProductos(struct NodoProducto *);
void mostrarTablaIngredientes(struct NodoIngrediente *);

//void enlazarProducto(struct NodoProducto **, struct NodoProducto *);

//Funciones Nuevas

void inorden(struct NodoProducto *raiz);
char *lowercase(char *cadena);
void escrituraDatos(struct NodoProducto *raiz, FILE *file);
struct NodoProducto *cambioNodo(struct NodoProducto *raizBusqueda);

///
int contarIngredientes(struct NodoIngrediente *ingredientes);
void InfoProducto(struct NodoProducto *raiz, char *nombreProducto);
void preorden(struct NodoProducto *raiz);
#endif
