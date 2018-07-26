import sys
from grafo import *
from consola import *
from constantes import *

"""
Funcion principal del programa, carga los datos del archivo csv que recibe como parametro
a un grafo y lee de la entrada estandar los comandos para que sean ejecutados.
"""
def main():

    if len(sys.argv) != 3: sys.exit(0)

    grafo_ciudades = Grafo(False)
    diccionario_coordenadas = {}
    cargar_datos(grafo_ciudades, sys.argv[1], diccionario_coordenadas)

    for linea in sys.stdin:
        consola(linea, grafo_ciudades, diccionario_coordenadas, sys.argv[2])

"""
Carga los datos de archivo al grafo_ciudades y las coordenadas de las ciudades a
diccionario_coordenadas.
Pre: recibe un grafo no dirigido, el nombre de un archivo csv y un diccionario.
Post: carga las cuidades y sus coordenadas a diccionario_coordenadas y las ciudades
con la distacia entre ellas a grafo_ciudades.
"""
def cargar_datos(grafo_ciudades, archivo, diccionario_coordenadas):

    with open(archivo) as archivo_entrada:
        cantidad_ciudades = int( archivo_entrada.readline().rstrip('\n') )
        diccionario_coordenadas[CIUDADES] = cantidad_ciudades

        for x in range(cantidad_ciudades):
            ciudad, latitud, longitud = archivo_entrada.readline().rstrip('\n').split(',')
            diccionario_coordenadas[ciudad] = [ float(latitud), float(longitud) ]
            grafo_ciudades.agregar_vertice(ciudad)

        cantidad_aristas = int( archivo_entrada.readline().rstrip('\n') )

        for y in range(cantidad_aristas):
            origen, destino, tiempo = archivo_entrada.readline().rstrip('\n').split(',')
            grafo_ciudades.agregar_arista(origen, destino, int(tiempo) )


main()
