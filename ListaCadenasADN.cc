#include "ListaCadenasADN.h"

// Avanza una posición en la lista
void IteradorLista::step()
{
    ++iter;
}

// Retrocede una posición en la lista
void IteradorLista::rstep()
{
    --iter;
}

// Operador de comparación
bool IteradorLista::operator==(const IteradorLista &other) const
{
    return this->iter == other.iter;
}

// Operador de comparación
bool IteradorLista::operator!=(const IteradorLista &other) const
{
    return !(*this == other);
}

CadenaADN &IteradorLista::operator*() const
{
    return *iter;
}

// NUEVO: comprueba si el iterador ha sido creado con su constructor por defecto
bool IteradorLista::esVacio() const
{
    IteradorLista defaultIt;

    return *this == defaultIt;
}

// Devuelve un iterador que apunta al primer elemento de la lista
IteradorLista ListaCadenasADN::begin()
{
    IteradorLista it;
    it.iter = data.begin();
    return it;
}

// Devuelve un iterador que apunta después del
// último elemento
// de la lista: puntero a nullptr
IteradorLista ListaCadenasADN::end()
{
    IteradorLista it;
    it.iter = data.end();
    return it;
}

// Devuelve un iterador que apunta al último elemento de la lista
IteradorLista ListaCadenasADN::rbegin()
{
    IteradorLista it;
    it.iter = data.end();
    it.iter--;
    return it;
}

// Devuelve un iterador que apunta antes del
// primer elemento de la lista: puntero a nullptr
IteradorLista ListaCadenasADN::rend()
{
    IteradorLista it;
    it.iter = data.begin();
    it.iter--;
    return it;
}

// Devuelve la cadena de ADN apuntada por el iterador
CadenaADN ListaCadenasADN::getCadenaADN(IteradorLista it)
{
    return *it;
}

// Comprueba si la lista está vacía
bool ListaCadenasADN::esVacia()
{
    return data.empty();
}

// Inserta una cadena de ADN al principio de la lista
void ListaCadenasADN::insertarInicio(const CadenaADN &cadena)
{
    data.push_front(cadena);
}

// Inserta una cadena de ADN al final de la lista
void ListaCadenasADN::insertarFinal(const CadenaADN &cadena)
{
    data.push_back(cadena);
}

// Inserta una cadena de ADN justo antes de la posición apuntada por el iterador
bool ListaCadenasADN::insertar(IteradorLista, const CadenaADN &)
{
    return true;
}

// NUEVO: Inserta una cadena de ADN justo después de la posición apuntada por el iterador
bool ListaCadenasADN::insertarDespues(IteradorLista, const CadenaADN &)
{
    return true;
}

// Asigna la cadena de ADN la posición apuntada por el iterador
bool ListaCadenasADN::asignar(IteradorLista it, const CadenaADN &new_cadena)
{
    if (it.esVacio())
        return false;

    *it = new_cadena;
    return true;
}

// Borra la primera cadena de ADN de la lista
bool ListaCadenasADN::borrarPrimera()
{
    if (!esVacia())
    {
        data.pop_front();
    }
    return true;
}

// Borra la última cadena de ADN de la lista
bool ListaCadenasADN::borrarUltima()
{
    if (!esVacia())
    {
        data.pop_back();
    }
    return true;
}

// Borra la cadena de ADN a la que apunta el iterador
bool ListaCadenasADN::borrar(IteradorLista &)
{
    return true;
}

// Devuelve cuántos elementos hay en la lista
int ListaCadenasADN::longitud()
{
    return data.size();
}

// Cuenta el número de apariciones de la cadena de ADN que se pasa como parámetro
//(según su operador ==)
int ListaCadenasADN::contar(const CadenaADN &)
{
    return 0;
}

// Devuelve una nueva lista con todos los elementos de la lista actual y,
// a continuación, todos los de la lista que se pasa como parámetro
ListaCadenasADN ListaCadenasADN::concatenar(ListaCadenasADN &)
{
    return ListaCadenasADN();
}

// Devuelve una nueva lista con todos los elementos de la lista actual
// que no están en la que se pasa como parámetro
ListaCadenasADN ListaCadenasADN::diferencia(ListaCadenasADN &)
{
    return ListaCadenasADN();
}

// Devuelve una cadena de ADN con la concatenación de todas las secuencias de la lista
// y la cadena vacía como descripción
CadenaADN ListaCadenasADN::concatenar()
{
    return CadenaADN();
}

// Devuelve una cadena de texto con el contenido completo de la lista
string ListaCadenasADN::aCadena()
{
    return "";
}

// NUEVO: Devuelve la frecuencia del codón pasado como parámetro
int ListaCadenasADN::frecuenciaCodon(const string &)
{
    return 0;
}

// NUevo: Devuelve la frecuencia de la cadena de ADN pasada como parémtro
int ListaCadenasADN::frecuenciaCadena(const CadenaADN &)
{
    return 0;
}

// NUEVO:Lista los codones en orden alfabético
string ListaCadenasADN::listaCodones()
{
    return "";
}

// NUEVO:Lista las cadenas en orden alfabétic
string ListaCadenasADN::listaCadenasADN()
{
    return "";
}

// NUEVO:Lista las cadenas que contienen un codón determinado, sin repetidos
string ListaCadenasADN::listaCadenasConCodon(const string &)
{
    return "";
}

// NUEVO:elimina las cadenas de ADN con la misma secuencia, dejando sólo la primera que aparezca en la lista
void ListaCadenasADN::eliminaDuplicados()
{
}