# smartprofit
Beta, proyecto grupal pucv iei gen2017.

ABRIR SMARTPROFIT.CBP PARA TRABAJAR PROYECTO CON CODE::BLOCKS

ABRIR SMARTPROFIT.DSP (O .DSW ABRIENDO EL VS PRIMERO) PARA TRABAJAR PROYECTO CON VISUAL STUDIO 6

.EXE EN CARPETA RELEASE TIENE LOS CAMBIOS, NO COMPILE EN VISUAL STUDIO (POR LO QUE EL .EXE PREVIO SE ENCUENTRA AFUERA)

Cambios:

Version 1: 

    +++ errores persistentes:
    
    -falta arreglar comprobaciones en funciones
    
    -mejorar funcion precio
    
    -y nome acuerdo q mas(by @felipe)
   

Version 1.2: compilado en Visual Studio (tira 2 warning pero igual funciona)

    +++ cambios:
    
    -funcion precio: ganancia del 10% por cada ingrediente del producto, ganancia minima del 20% (minimo 2 ingredientes por producto)
    
    -se cambio "[2] buscar elemento" solo a "[2] modificar elemento"
    
    -por lo anterior, la busqueda de productos se movio a "[4] mostrar informacion" en el menu, mostrando precio/ingredientes/etc.
    
    +++ errores persistentes:
    
    -no funciona correctamente el eliminar productos (probar con la lista subida eliminar un 3er producto)
    
    -a modo de testeo, la lista de productos se muestra de forma preorden e indorden (para ver que wea pasa con el eliminar). 
    
    -PARA CONSIDERAR AL TESTEAR: por defecto (inorden==preorden) ya que se carga el archivo cada vez que se abre el .exe, cuando se agregan weas sin cerrar el programa con la 'x' no se guarda nada. por ejemplo, la raiz era "fideos" pero al cerrar y abrir el programa marcando [0] la raiz paso a ser "abc"
    
    -hasta el momento nada mas esta fallando


Version 1.3: 

    - casi completo, falta testear
   
