"""
Imprime las ciudades que hay en lista_caminos en un formato definido y luego
el costo que tiene ese camino.
Pre: recibe una lista de caminos y un grafo de ciudades.
Post: muestra las ciudades en el orden que aparecen en lista_caminos y luego el
costo que tiene ese camino.
"""
def imprimir_caminos(lista_caminos, grafo_ciudades):
    largo = len(lista_caminos)

    for i in range(largo):

        if i == 0: print( "{}".format(lista_caminos[i]), end = " " )

        elif i == (largo - 1): print( "-> {}".format(lista_caminos[i]) )

        else: print( "-> {}".format(lista_caminos[i]), end = " " )

    costo_total = 0

    for i in range(largo - 1):
        costo_total += grafo_ciudades.obtener_peso_arista(lista_caminos[i], lista_caminos[i + 1])

    print( "Costo total: {}".format(costo_total) )

"""
Valida que vertice y adyacente esten en lista_aristas.
Pre: recibe una lista de aristas, un vertice y un adyacente al vertice.
Post: devuleve False en caso de que la lista este vacia o si los conjugados de
vertice y adyacente no existen, caso contrario devuelve True.
"""
def estan(lista_aristas, vertice, adyacente):

    if len(lista_aristas) == 0: return False

    for arista in lista_aristas:
        _peso, _vertice, _adyacente = arista

        if vertice == _adyacente and adyacente == _vertice: return True

    return False
