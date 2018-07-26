from conjuntos import *
from grafo import *
from constantes import *
from funciones_en_comun import *

"""
Calcula el arbol de tendido minimo de un grafo.
Pre: recibe un grafo de ciudades, el cual es no dirigido.
Post: devulve un grafo, el cual representa al arbol de tendido minimo del grafo
recibido.
"""
def arbol_tendido_minimo(grafo):
    conjuntos = Conjuntos()

    for vertice in grafo:
        conjuntos.agregar(vertice)

    aristas = sorted( grafo.obtener_todas_las_aristas() )
    arbol = Grafo(False)

    for vertice in grafo:
        arbol.agregar_vertice(vertice)

    for arista in aristas:
        peso, vertice, adyacente = arista

        if conjuntos.buscar(vertice) == conjuntos.buscar(adyacente): continue

        arbol.agregar_arista(vertice, adyacente, peso)
        conjuntos.union(vertice, adyacente)

    return arbol

"""
Ejecuta el comando reducir camininos.
Pre: recibe un graafo de ciudades, el nombre de un archivo (archivo) y un
diccionario de coordenadas para poder acceder a las coordenadas de las ciudades
del grafo de ciudades.
Post: escribe en el archivo recibido (archivo) los caminos que minimizan el recorrido
sobre el grafo de ciudades con el mismo formato que el archivo de ciudades
 que recibe el programa.
"""
def reducir_caminos(grafo_ciudades, archivo, diccionario_coordenadas):
    arbol = arbol_tendido_minimo(grafo_ciudades)
    costo_total = 0
    lista_aristas = []

    with open(archivo, "w") as archivo_salida:
        archivo_salida.write( "{}\n".format(diccionario_coordenadas[CIUDADES]) )

        for ciudad in diccionario_coordenadas:

            if ciudad == CIUDADES: continue

            lista_coordenadas = diccionario_coordenadas[ciudad]
            latitud, longitud = lista_coordenadas
            archivo_salida.write( "{},{},{}\n".format(ciudad, latitud, longitud) )

        cantidad_aristas = grafo_ciudades.obtener_cantidad_vertices() - 1
        archivo_salida.write( "{}\n".format(cantidad_aristas) )

        for vertice in arbol:

            for adyacente in arbol.obtener_adyacentes(vertice):

                if estan(lista_aristas, vertice, adyacente): continue

                peso_arista = arbol.obtener_peso_arista(vertice, adyacente)
                arista = (peso_arista, vertice, adyacente)
                lista_aristas.append(arista)
                costo_total += peso_arista
                archivo_salida.write( "{},{},{}\n".format(vertice, adyacente, peso_arista) )

    print( "Peso total: {}".format(costo_total) )
