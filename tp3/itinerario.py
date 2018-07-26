from cola import *
from grafo import *
from kml import *
from funciones_en_comun import *
from constantes import *

"""
Calcula el orden topologico de un grafo dirigido pasado por parametro.
Pre: recibe un grafo dirigido.
Post: devuleve un lista que contiene el orden topologico de las ciudades o None
si la lista esta vacia.
"""
def orden_topologico(grafo):
    grados = {}

    for vertice in grafo:
        grados[vertice] = 0

    for vertice in grafo:

        for adyacente in grafo.obtener_adyacentes(vertice):
            grados[adyacente] += 1

    resultado = []
    cola = Cola()

    for vertice in grafo:

        if grados[vertice] == 0: cola.encolar(vertice)

    while not cola.esta_vacia():
        vertice = cola.desencolar()
        resultado.append(vertice)

        for adyacente in grafo.obtener_adyacentes(vertice):
            grados[adyacente] -= 1

            if grados[adyacente] == 0: cola.encolar(adyacente)

    return None if len(resultado) == 0 else resultado

"""
Ejecuta el comando itinerario.
Pre: recibe un grafo de ciudades, el nombre de un archivo de recomendaciones (archivo),
el nombre de un archivo kml y un diccionario de coordenadas para poder acceder a las
cordenadas de las ciudades del grafo de ciudades.
Post: imprime un itinerario teniendo en cuenta las ciudades del archivo de recomendaciones y
lo exporta a un archivo kml para poder mostrarlo en un mapa.
"""
def itinerario(grafo_ciudades, archivo, archivo_kml, diccionario_coordenadas):
    grafo = Grafo()

    for vertice in grafo_ciudades:
        grafo.agregar_vertice(vertice)

    with open(archivo) as archivo_entrada:

        for linea in archivo_entrada:
            vertice, adyacente = linea.rstrip('\n').split(',')
            grafo.agregar_arista(vertice, adyacente)

    lista_orden_topologico = orden_topologico(grafo)
    imprimir_caminos(lista_orden_topologico, grafo_ciudades)
    exportar_kml(ITINERARIO, archivo_kml, diccionario_coordenadas, lista_orden_topologico, archivo)
