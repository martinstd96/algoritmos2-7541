from heap import *
from grafo import *
from constantes import *
from kml import *

"""
Funcion que compara dos aristas.
Pre: recibe dos aristas con forma de tupla de dos elementos que contiene informacion
sobre el vertice y la distancia desde el origen para llegar hasta ese vertice.
Post: devuelve un numero, 0 si la distancia de la arista_a y la distancia de la
arista_b son iguales; 1 si la distancia de la arista_a es menor que la de la arista_b
y -1 si la distancia de la arista_a es mayor que la de la arista_b.
"""
def cmp_aristas(arista_a, arista_b):
    largo_1 = len(arista_a)
    largo_2 = len(arista_b)
    peso_arista_1 = arista_a[largo_1 - 1]
    peso_arista_2 = arista_b[largo_2 - 1]

    if peso_arista_1 < peso_arista_2: return 1

    if peso_arista_1 > peso_arista_2: return -1

    return 0

"""
Algortimo de Dijkstra para calcular el caminino minimo desde el origen.
Pre: recibe un grafo y un vertice de origen.
Post: devuelve dos diccionarios, uno de padres y otro de distancia.
"""
def dijkstra(grafo, origen):
    distancia = {}
    padre = {}

    for vertice in grafo:
        distancia[vertice] = INFINITO # Pongo una distancia muy grande para simular infinito

    distancia [origen] = 0
    padre[origen] = None
    heap = Heap(cmp_aristas)
    heap.heap_encolar( (origen, distancia[origen]) )

    while not heap.heap_esta_vacio():
        vertice, dist = heap.heap_desencolar()

        for adyacente in grafo.obtener_adyacentes(vertice):
            distancia_actual = distancia[vertice] + grafo.obtener_peso_arista(vertice, adyacente)

            if distancia_actual < distancia[adyacente]:
                padre[adyacente] = vertice
                distancia[adyacente] = distancia_actual
                heap.heap_encolar( (adyacente, distancia[adyacente]) )

    return padre, distancia

"""
Calcula el camino minimo entre desde y hasta.
Pre: recibe un grafo, una ciudad de origen (desde) y otra ciudad de destino (hasta)
que indica hasta donde se calculará el camino minimo.
Post: devuelve una lista, la cual representa el orden del camino minimo de desde a hasta.
"""
def camino_minimo(grafo, desde, hasta):
    padre, distancia = dijkstra(grafo, desde)
    resultado = []
    actual = hasta

    while actual != None:
        resultado.append(actual)
        actual = padre[actual]

    resultado.reverse()
    return resultado

"""
Ejecuta el comando ir.
Pre: recibe un grafo de ciudades, una ciudad de partida y otra de llegada, el nombre
de un archivo kml para poder visualizar en un mapa el camino minimo que calcula ir y un
diccionario de coordenadas para poder acceder a las coordenadas de las ciudades del
grafo de ciudades.
Post: calcula el camino minimo entre desde y hasta, lo imprime y lo exporta a un
archivo kml para poder mostrarlo en un mapa.
"""
def ir(grafo_ciudades, desde, hasta, archivo_kml, diccionario_coordenadas):
    lista_camino = camino_minimo(grafo_ciudades, desde, hasta)
    imprimir_caminos(lista_camino, grafo_ciudades)
    exportar_kml(IR, archivo_kml, diccionario_coordenadas, lista_camino, desde, hasta)
