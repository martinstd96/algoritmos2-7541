from camino_minimo import *
from itinerario import *
from reducir_caminos import *
from viaje import *
from constantes import *
from grafo import *

"""
Ejejcuta los comandos pasados, incluidos en linea.
Pre: recibe un linea de comandos, un grafo de ciudades, un diccionario de coordenadas
y el nombre de un archivo kml.
Post: ejecuta los comandos de la linea, en caso de error en alguno de los comandos
se deja de ejecutar.
"""
def consola(linea, grafo_ciudades, diccionario_coordenadas, archivo_kml):

    if len(linea) == 1: return

    comando = linea.rstrip('\n')
    lista_comandos = comando.split()

    if lista_comandos[0] in TUPLA_IR_VIAJE:

        if lista_comandos[0] == IR:
            _comando = [ lista_comandos[0] ]
            lista_ciudades = obtener_lista_ciudades_deseada( lista_comandos[1 : ] )
            lista_comandos = _comando + lista_ciudades

        else:
            lista_comandos = obtener_lista_viaje_deseada(lista_comandos)

    if not es_valida(lista_comandos): return

    if lista_comandos[0] == IR:
        ir(grafo_ciudades, lista_comandos[1], lista_comandos[2], archivo_kml, diccionario_coordenadas)
        return

    if lista_comandos[0] == VIAJE:
        ejecutar_viaje(lista_comandos[1])(grafo_ciudades, lista_comandos[2], archivo_kml, diccionario_coordenadas)
        return

    if lista_comandos[0] == ITINERARIO:
        itinerario(grafo_ciudades, lista_comandos[1], archivo_kml, diccionario_coordenadas)
        return

    reducir_caminos(grafo_ciudades, lista_comandos[1], diccionario_coordenadas)

"""
Ejecuta un tipo de viaje.
Pre: recibe un tipo de viaje a ser ejecutado.
Post: devulve la funcion que se encarga de ejecutar dicho tipo de viaje.
"""
def ejecutar_viaje(tipo_viaje):
    funciones = { OPTIMO : viaje_optimo,
                  APROXIMADO : viaje_aproximado
                  }

    return funciones[tipo_viaje]

"""
Valida si lista_comandos es valida.
Pre: recibe una lista de comados, la cual se quiere validar.
Post: devuelve False si la cantidad de elementos para cada comando es erronea, True
caso contrario.
"""
def es_valida(lista_comandos):
    comando = lista_comandos[0]
    largo = len(lista_comandos)

    if comando == "ir" and largo != 3: return False

    if comando == "viaje" and largo != 3: return False

    if comando == "itinerario" and largo != 2: return False

    if comando == "reducir_caminos" and largo != 2: return False

    return True

"""
Obtiene una lista de ciudades bien formada.
Pre: recibe una lista de ciudades, la cual puede estar mal formada por tener el
nombre de una ciudad que usa espacios de separacion.
Post: devulve una lista nueva con los nombres de las ciudades bien conformados.
"""
def obtener_lista_ciudades_deseada(lista_ciudades):
    posicion = None

    for i in range( len(lista_ciudades) ):
        ciudad = lista_ciudades[i]

        if ciudad[-1] == ',':
            posicion = i
            break

    lista_ciudades_nueva = lista_ciudades[ : posicion + 1]
    ciudad_parcial = " ".join(lista_ciudades_nueva)
    ciudad_1 = ciudad_parcial[ : -1]
    resto = lista_ciudades[posicion + 1 : ]
    ciudad_2 = " ".join(resto)
    _lista_ciudades = []
    _lista_ciudades.append(ciudad_1)
    _lista_ciudades.append(ciudad_2)
    return _lista_ciudades

"""
Obtiene una lista de ciudades para los tipos de viajes.
Pre: recibe una lista de comandos, la cual contiene los comandos para ejecutar un
tipo de viaje.
Post: devuelve una lista nueva con los comandos bien conformados.
"""
def obtener_lista_viaje_deseada(lista_comandos):
    tipo_viaje = lista_comandos[1]
    tipo_viaje = tipo_viaje[ : len(tipo_viaje) - 1]
    lista_comandos[1] = tipo_viaje
    lista_ciudades = lista_comandos[2 : ]
    ciudad = " ".join(lista_ciudades)
    viaje = lista_comandos[0]
    tipo = lista_comandos[1]
    _lista_comandos = []
    _lista_comandos.append(viaje)
    _lista_comandos.append(tipo)
    _lista_comandos.append(ciudad)
    return _lista_comandos
