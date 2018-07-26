from grafo import *
from cola import *
from constantes import *
from kml import *
from funciones_en_comun import *

"""
Resuelve el problema del viajante de una forma aproximada.
Pre: recibe un grafo de ciudades y un origen de donde empezar.
Post: devulve una lista, la cual tiene las ciudades que conforman el camino aproximado.
"""
def viajante_aproximado(grafo_ciudades, origen):
    distancia = INFINITO # seteo una distancia grande para simular el infinito
    proximo = None
    visitados = []
    visitados.append(origen)
    cola = Cola()
    cola.encolar(origen)

    while not cola.esta_vacia():
        vertice = cola.desencolar()

        for adyacente in grafo_ciudades.obtener_adyacentes(vertice):

            if adyacente not in visitados:
                peso_arista = grafo_ciudades.obtener_peso_arista(vertice, adyacente)

                if peso_arista < distancia:
                    distancia = peso_arista
                    proximo = adyacente

        if proximo in visitados:
            visitados.append(origen)
            break

        visitados.append(proximo)
        cola.encolar(proximo)
        distancia = INFINITO

    return visitados

"""
Resuelve el problema del viajante de una forma optima.
Pre: recibe un grafo de ciudades y un origen de donde empezar.
Post: devulve una lista, la cual tiene las ciudades que conforman el camino optimo.
"""
def viajante_optimo(grafo_ciudades, origen):
    visitados = []
    resultado = [ (INFINITO, []) ] # Pongo una lista vacia para que se entienda el formato.
    lista_vertices = grafo_ciudades.obtener_todos_los_vertices()
    distancia = 0
    DFS(grafo_ciudades, origen, visitados, distancia, lista_vertices, resultado)
    mejor_camino = resultado[0][1]
    return mejor_camino

"""
Modo de busqueda del grafo, modificado para resolver el problema del viajante
optimo.
Pre: recibe un grafo, un vertice, una lista de visitados, la distancia recorrda,
una lista de vertices y el resultado que es una lista de una tupla.
Post: muta la lista de resultado, obteniendo la del menor camino que resuelve el
problema del viajante.
"""
def DFS(grafo, vertice, visitados, distancia, lista_vertices, resultado):

    if distancia > resultado[0][0]: return

    _visitados = visitados[ : ]
    _visitados.append(vertice)

    for adyacente in grafo.obtener_adyacentes(vertice):

        if adyacente in visitados and adyacente == _visitados[0] and estan_todos_visitados(_visitados, lista_vertices):
            _visitados.append(adyacente)
            peso_arista = grafo.obtener_peso_arista(vertice, adyacente)
            distancia_actual = distancia + peso_arista

            if distancia_actual < resultado[0][0]: resultado[0] = (distancia_actual, _visitados)

            return

        if adyacente not in _visitados:
            peso_arista = grafo.obtener_peso_arista(vertice, adyacente)
            distancia_actual = distancia + peso_arista
            DFS(grafo, adyacente, _visitados, distancia_actual, lista_vertices, resultado)

def estan_todos_visitados(lista_visitados, lista_vertices):
    return len(lista_visitados) == len(lista_vertices) 

"""
Ejecuta el comando viaje aproximado.
Pre: recibe un grafo de ciudades, un origen de donde empieza el viaje, el nombre
de un archivo kml para visualizar le viaje en un mapa y un diccionario de
coordenadas.
Post: calcula el viaje aproximado partiendo del origen, lo imprime y lo exporta a un
archivo kml para poder mostrarlo en un mapa.
"""
def viaje_aproximado(grafo_ciudades, origen, archivo_kml, diccionario_coordenadas):
    lista_viajante = viajante_aproximado(grafo_ciudades, origen)
    imprimir_caminos(lista_viajante, grafo_ciudades)
    exportar_kml(VIAJE_APROXIMADO, archivo_kml, diccionario_coordenadas, lista_viajante, origen)

"""
Ejecuta el comando viaje optimo.
Pre: recibe un grafo de ciudades, un origen de donde empieza el viaje, el nombre
de un archivo kml para visualizar le viaje en un mapa y un diccionario de
coordenadas.
Post: calcula el viaje optimo partiendo del origen, lo imprime y lo exporta a un
archivo kml para poder mostrarlo en un mapa.
"""
def viaje_optimo(grafo_ciudades, origen, archivo_kml, diccionario_coordenadas):
    lista_viajante = viajante_optimo(grafo_ciudades, origen)
    imprimir_caminos(lista_viajante, grafo_ciudades)
    exportar_kml(VIAJE_OPTIMO, archivo_kml, diccionario_coordenadas, lista_viajante, origen)
