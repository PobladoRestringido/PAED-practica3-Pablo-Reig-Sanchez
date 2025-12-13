#pragma once
#include "CadenaADN.h"
#include <list>
#include <set>
#include <map>
using namespace std;

class ListaCadenasADN;

class IteradorLista
{
   friend class ListaCadenasADN;

private:
   list<CadenaADN>::iterator iter;
   void operator++();
   CadenaADN &operator*() const;

public:
   // Avanza una posición en la lista
   void step();
   // Retrocede una posición en la lista
   void rstep();
   // Operador de comparación
   bool operator==(const IteradorLista &) const;
   // Operador de comparación
   bool operator!=(const IteradorLista &) const;

   // NUEVO: comprueba si el iterador ha sido creado con su constructor por defecto
   bool esVacio() const;
};

class ListaCadenasADN
{
private:
   list<CadenaADN> data;
   std::map<std::string, int> orderedCodonesMap;

   void insertCodonesToMap(const CadenaADN &new_cadena);
   void removeCodonesFromMap(const CadenaADN &removed_cadena);

public:
   // Devuelve un iterador que apunta al primer elemento de la lista
   IteradorLista begin();
   // Devuelve un iterador que apunta después del
   // último elemento
   // de la lista: puntero a nullptr
   IteradorLista end();
   // Devuelve un iterador que apunta al último elemento de la lista
   IteradorLista rbegin();
   // Devuelve un iterador que apunta antes del
   // primer elemento de la lista: puntero a nullptr
   IteradorLista rend();
   // Devuelve la cadena de ADN apuntada por el iterador
   CadenaADN getCadenaADN(IteradorLista);
   // Comprueba si la lista está vacía
   bool esVacia();
   // Inserta una cadena de ADN al principio de la lista
   void insertarInicio(const CadenaADN &);
   // Inserta una cadena de ADN al final de la lista
   void insertarFinal(const CadenaADN &);
   // Inserta una cadena de ADN justo antes de la posición apuntada por el iterador
   bool insertar(IteradorLista, const CadenaADN &);
   // NUEVO: Inserta una cadena de ADN justo después de la posición apuntada por el iterador
   bool insertarDespues(IteradorLista, const CadenaADN &);
   // Asigna la cadena de ADN la posición apuntada por el iterador
   bool asignar(IteradorLista, const CadenaADN &);
   // Borra la primera cadena de ADN de la lista
   bool borrarPrimera();
   // Borra la última cadena de ADN de la lista
   bool borrarUltima();
   // Borra la cadena de ADN a la que apunta el iterador
   bool borrar(IteradorLista &);
   // Devuelve cuántos elementos hay en la lista
   int longitud();
   // Cuenta el número de apariciones de la cadena de ADN que se pasa como parámetro
   //(según su operador ==)
   int contar(const CadenaADN &);
   // Devuelve una nueva lista con todos los elementos de la lista actual y,
   // a continuación, todos los de la lista que se pasa como parámetro
   ListaCadenasADN concatenar(ListaCadenasADN &);
   // Devuelve una nueva lista con todos los elementos de la lista actual
   // que no están en la que se pasa como parámetro
   ListaCadenasADN diferencia(ListaCadenasADN &);
   // Devuelve una cadena de ADN con la concatenación de todas las secuencias de la lista
   // y la cadena vacía como descripción
   CadenaADN concatenar();
   // Devuelve una cadena de texto con el contenido completo de la lista
   string aCadena();

   // NUEVO: Devuelve la frecuencia del codón pasado como parámetro
   int frecuenciaCodon(const string &);
   // NUevo: Devuelve la frecuencia de la cadena de ADN pasada como parémtro
   int frecuenciaCadena(const CadenaADN &);

   // NUEVO:Lista los codones en orden alfabético
   string listaCodones();
   // NUEVO:Lista las cadenas en orden alfabétic
   string listaCadenasADN();

   // NUEVO:Lista las cadenas que contienen un codón determinado, sin repetidos
   string listaCadenasConCodon(const string &);

   // NUEVO:elimina las cadenas de ADN con la misma secuencia, dejando sólo la primera que aparezca en la lista
   void eliminaDuplicados();
};
