"""
Escribe un archivo kml a partir del nombre del archivo (archivo) pasado por parametro.
Pre: recibe un comando, el nombre de un archivo, un diccionario de coordenadas,
una lista de soluciones, un origen y un destino (puede ser pasado o no).
Post: escribe en archivo las ciudades de lista_soluciones para luego verlas en el mapa.
"""
def exportar_kml(comando, archivo, diccionario_coordenadas, lista_soluciones, origen, destino = None):
    _comando = None

    if destino == None: _comando = "{}, {}".format(comando, origen)

    else: _comando = "{} {}, {}".format(comando, origen, destino)

    f = open(archivo, "w")

    f.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")
    f.write("<kml xmlns=\"http://earth.google.com/kml/2.1\">\n")
    f.write("\t<Document>\n")
    f.write( "\t\t<name>{}</name>\n".format(_comando) )
    f.write("\n")

    for ciudad in lista_soluciones:
        lista_coordenadas = diccionario_coordenadas[ciudad]
        latitud, longitud = lista_coordenadas

        f.write("\t\t<Placemark>\n")
        f.write( "\t\t\t<name>{}</name>\n".format(ciudad) )
        f.write("\t\t\t<Point>\n")
        f.write( "\t\t\t\t<coordinates>{}, {}</coordinates>\n".format(latitud, longitud) )
        f.write("\t\t\t</Point>\n")
        f.write("\t\t</Placemark>\n")

    f.write("\n")

    for i in range( len(lista_soluciones) - 1 ):
        lista_coordenadas_1 = diccionario_coordenadas[ lista_soluciones[i] ]
        lista_coordenadas_2 = diccionario_coordenadas[ lista_soluciones[i + 1] ]
        latitud_1, longitud_1 = lista_coordenadas_1
        latitud_2, longitud_2 = lista_coordenadas_2

        f.write("\t\t<Placemark>\n")
        f.write("\t\t\t<LineString>\n")
        f.write( "\t\t\t\t<coordinates>{}, {} {}, {}</coordinates>\n".format(latitud_1, longitud_1, latitud_2, longitud_2) )
        f.write("\t\t\t</LineString>\n")
        f.write("\t\t</Placemark>\n")

    f.write("\t</Document>\n")
    f.write("</kml>\n")

    f.close()
