#include "ListaCadenasADN.h"

// Constructor por defecto: puntero a nullptr
IteradorLista::IteradorLista()
{
}

// Constructor de copia
IteradorLista::IteradorLista(const IteradorLista &)
{
}

// Destructor: puntero a nullptr
IteradorLista::~IteradorLista()
{
}

// Operador de asignación
IteradorLista &IteradorLista::operator=(const IteradorLista &)
{
}

// Avanza una posición en la lista
void IteradorLista::step()
{
}

// Retrocede una posición en la lista
void IteradorLista::rstep()
{
}

// Operador de comparación
bool IteradorLista::operator==(const IteradorLista &) const
{
}

// Operador de comparación
bool IteradorLista::operator!=(const IteradorLista &) const
{
}

// NUEVO: comprueba si el iterador ha sido creado con su constructor por defecto
bool IteradorLista::esVacio() const
{
}

// Constructor por defecto: lista vacía
ListaCadenasADN::ListaCadenasADN()
{
}
// Constructor de copia
ListaCadenasADN::ListaCadenasADN(const ListaCadenasADN &)
{
}

// Operador de asignación
ListaCadenasADN &ListaCadenasADN::operator=(const ListaCadenasADN &)
{
}

// Destructor
ListaCadenasADN::~ListaCadenasADN()
{
}

// Devuelve un iterador que apunta al primer elemento de la lista
IteradorLista ListaCadenasADN::begin()
{
}

// Devuelve un iterador que apunta después del
// último elemento
// de la lista: puntero a nullptr
IteradorLista ListaCadenasADN::end()
{
}

// Devuelve un iterador que apunta al último elemento de la lista
IteradorLista ListaCadenasADN::rbegin()
{
}

// Devuelve un iterador que apunta antes del
// primer elemento de la lista: puntero a nullptr
IteradorLista ListaCadenasADN::rend()
{
}

// Devuelve la cadena de ADN apuntada por el iterador
CadenaADN ListaCadenasADN::getCadenaADN(IteradorLista)
{
}

// Comprueba si la lista está vacía
bool ListaCadenasADN::esVacia()
{
}

// Inserta una cadena de ADN al principio de la lista
void ListaCadenasADN::insertarInicio(const CadenaADN &)
{
}

// Inserta una cadena de ADN al final de la lista
void ListaCadenasADN::insertarFinal(const CadenaADN &)
{
}

// Inserta una cadena de ADN justo antes de la posición apuntada por el iterador
bool ListaCadenasADN::insertar(IteradorLista, const CadenaADN &)
{
}

// NUEVO: Inserta una cadena de ADN justo después de la posición apuntada por el iterador
bool ListaCadenasADN::insertarDespues(IteradorLista, const CadenaADN &)
{
}

// Asigna la cadena de ADN la posición apuntada por el iterador
bool ListaCadenasADN::asignar(IteradorLista, const CadenaADN &)
{
}

// Borra la primera cadena de ADN de la lista
bool ListaCadenasADN::borrarPrimera()
{
}

// Borra la última cadena de ADN de la lista
bool ListaCadenasADN::borrarUltima()
{
}

// Borra la cadena de ADN a la que apunta el iterador
bool ListaCadenasADN::borrar(IteradorLista &)
{
}

// Devuelve cuántos elementos hay en la lista
int ListaCadenasADN::longitud()
{
}

// Cuenta el número de apariciones de la cadena de ADN que se pasa como parámetro
//(según su operador ==)
int ListaCadenasADN::contar(const CadenaADN &)
{
}

// Devuelve una nueva lista con todos los elementos de la lista actual y,
// a continuación, todos los de la lista que se pasa como parámetro
ListaCadenasADN ListaCadenasADN::concatenar(ListaCadenasADN &)
{
}

// Devuelve una nueva lista con todos los elementos de la lista actual
// que no están en la que se pasa como parámetro
ListaCadenasADN ListaCadenasADN::diferencia(ListaCadenasADN &)
{
}

// Devuelve una cadena de ADN con la concatenación de todas las secuencias de la lista
// y la cadena vacía como descripción
CadenaADN ListaCadenasADN::concatenar()
{
}

// Devuelve una cadena de texto con el contenido completo de la lista
string ListaCadenasADN::aCadena()
{
}

// NUEVO: Devuelve la frecuencia del codón pasado como parámetro
int ListaCadenasADN::frecuenciaCodon(const string &)
{
}

// NUevo: Devuelve la frecuencia de la cadena de ADN pasada como parémtro
int ListaCadenasADN::frecuenciaCadena(const CadenaADN &)
{
}

// NUEVO:Lista los codones en orden alfabético
string ListaCadenasADN::listaCodones()
{
}

// NUEVO:Lista las cadenas en orden alfabétic
string ListaCadenasADN::listaCadenasADN()
{
}

// NUEVO:Lista las cadenas que contienen un codón determinado, sin repetidos
string ListaCadenasADN::listaCadenasConCodon(const string &)
{
}

// NUEVO:elimina las cadenas de ADN con la misma secuencia, dejando sólo la primera que aparezca en la lista
void ListaCadenasADN::eliminaDuplicados()
{
}