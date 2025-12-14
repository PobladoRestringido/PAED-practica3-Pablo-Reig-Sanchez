#include "ListaCadenasADN.h"
#include <sstream>
#include <unordered_set>
#include <set>
#include <map>

// Avanza una posición en la lista
void IteradorLista::step()
{
    ++(*this);
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

void IteradorLista::operator++()
{
    ++iter;
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

/*
Inserting new Cadenas
---------------------
*/

void ListaCadenasADN::registerCadenaInIndexes(const CadenaADN &new_cadena)
{
    addCodonsToIndex(new_cadena);
    insertCadenaInMap(new_cadena);
    insertCadenaConCodonMap(new_cadena);
}

void ListaCadenasADN::addCodonsToIndex(const CadenaADN &new_cadena)
{
    for (const auto &cur_codon : new_cadena.exposeCodones())
    {
        codonToFrequency[cur_codon] += 1;
    }
}

void ListaCadenasADN::insertCadenaInMap(const CadenaADN &new_cadena)
{

    cadenaToFrequency[new_cadena] += 1;
}

void ListaCadenasADN::insertCadenaConCodonMap(const CadenaADN &newCadena)
{
    for (const auto &cur_codon : newCadena.exposeCodones())
    {
        codonToCadenas[cur_codon][newCadena] += 1;
    }
}

// Inserta una cadena de ADN al principio de la lista
void ListaCadenasADN::insertarInicio(const CadenaADN &cadena)
{
    data.push_front(cadena);
    registerCadenaInIndexes(cadena);
}

// Inserta una cadena de ADN al final de la lista
void ListaCadenasADN::insertarFinal(const CadenaADN &cadena)
{
    data.push_back(cadena);
    registerCadenaInIndexes(cadena);
}

// Inserta una cadena de ADN justo antes de la posición apuntada por el iterador
bool ListaCadenasADN::insertar(IteradorLista it, const CadenaADN &cadena)
{
    if (it.esVacio())
        return false;

    data.insert(it.iter, cadena);
    registerCadenaInIndexes(cadena);

    return true;
}

// NUEVO: Inserta una cadena de ADN justo después de la posición apuntada por el iterador
bool ListaCadenasADN::insertarDespues(IteradorLista it, const CadenaADN &new_cadena)
{
    if (it.esVacio())
        return false;

    ++it;

    if (it == end())
    {
        insertarFinal(new_cadena);
        return true;
    }
    return insertar(it, new_cadena);
}

// Asigna la cadena de ADN la posición apuntada por el iterador
bool ListaCadenasADN::asignar(IteradorLista it, const CadenaADN &new_cadena)
{
    if (it.esVacio())
        return false;

    *it = new_cadena;
    return true;
}

void ListaCadenasADN::unregisterCadenaFromIndexes(const CadenaADN &deletedCadena)
{
    removeCodonsFromIndex(deletedCadena);
    removeCadenaFromMap(deletedCadena);
    removeFromCadenaConCodonMap(deletedCadena);
}

void ListaCadenasADN::removeCodonsFromIndex(const CadenaADN &deletedCadena)
{
    for (const auto &cur_codon : deletedCadena.exposeCodones())
    {
        codonToFrequency[cur_codon] -= 1;

        if (codonToFrequency[cur_codon] == 0)
            codonToFrequency.erase(cur_codon);
    }
}

void ListaCadenasADN::removeCadenaFromMap(const CadenaADN &deletedCadena)
{

    cadenaToFrequency[deletedCadena] -= 1;

    if (cadenaToFrequency[deletedCadena] == 0)
        cadenaToFrequency.erase(deletedCadena);
}

void ListaCadenasADN::removeFromCadenaConCodonMap(const CadenaADN &deletedCadena)
{
    for (const auto &cur_codon : deletedCadena.exposeCodones())
    {
        codonToCadenas[cur_codon][deletedCadena] -= 1;

        if (codonToCadenas[cur_codon][deletedCadena] == 0)
            codonToCadenas[cur_codon].erase(deletedCadena);
    }
}

// Borra la primera cadena de ADN de la lista
bool ListaCadenasADN::borrarPrimera()
{
    if (esVacia())
        return false;

    CadenaADN deletedCadena = data.front();
    unregisterCadenaFromIndexes(deletedCadena);

    data.pop_front();
    return true;
}

// Borra la última cadena de ADN de la lista
bool ListaCadenasADN::borrarUltima()
{
    if (esVacia())
        return false;

    CadenaADN deletedCadena = data.back();
    unregisterCadenaFromIndexes(deletedCadena);

    data.pop_back();
    return true;
}

// Borra la cadena de ADN a la que apunta el iterador
bool ListaCadenasADN::borrar(IteradorLista &it)
{
    if (it.esVacio())
        return false;

    CadenaADN deletedCadena = getCadenaADN(it);
    unregisterCadenaFromIndexes(deletedCadena);

    data.erase(it.iter);
    it = IteradorLista();
    return true;
}

// Devuelve cuántos elementos hay en la lista
int ListaCadenasADN::longitud()
{
    return data.size();
}

// Cuenta el número de apariciones de la cadena de ADN que se pasa como parámetro
//(según su operador ==)
int ListaCadenasADN::contar(const CadenaADN &cadena)
{
    int count = 0;
    for (const auto &cur_cadena : *this)
    {
        if (cur_cadena == cadena)
            ++count;
    }

    return count;
}

// Devuelve una nueva lista con todos los elementos de la lista actual y,
// a continuación, todos los de la lista que se pasa como parámetro
ListaCadenasADN ListaCadenasADN::concatenar(ListaCadenasADN &other)
{
    ListaCadenasADN new_list = ListaCadenasADN(*this);

    new_list.data.insert(new_list.data.end(), other.data.begin(), other.data.end());

    return new_list;
}

// Devuelve una nueva lista con todos los elementos de la lista actual
// que no están en la que se pasa como parámetro
ListaCadenasADN ListaCadenasADN::diferencia(ListaCadenasADN &other_lista)
{
    ListaCadenasADN difference_list;
    for (const auto &cur_cadena : *this)
    {
        if (other_lista.contar(cur_cadena) == 0)
            difference_list.insertarFinal(cur_cadena);
    }

    return difference_list;
}

// Devuelve una cadena de ADN con la concatenación de todas las secuencias de la lista
// y la cadena vacía como descripción
CadenaADN ListaCadenasADN::concatenar()
{
    std::string concat;
    for (const auto &cadena : *this)
        concat += cadena.getSecuencia();

    return CadenaADN(concat, "");
}

// Devuelve una cadena de texto con el contenido completo de la lista
string ListaCadenasADN::aCadena()
{
    std::ostringstream oss;
    IteradorLista it = this->begin();
    IteradorLista end = this->end();

    while (it != end)
    {
        const CadenaADN &cur_cadena = getCadenaADN(it);
        oss << cur_cadena.getDescripcion() << ':' << cur_cadena.getSecuencia();
        ++it;

        if (it != end)
            oss << '\n';
    }
    return oss.str();
}

// NUEVO: Devuelve la frecuencia del codón pasado como parámetro
int ListaCadenasADN::frecuenciaCodon(const string &codon)
{
    int count = 0;

    for (const auto &cur_cadena : *this)
    {
        count += cur_cadena.contarCodon(codon);
    }

    return count;
}

// NUevo: Devuelve la frecuencia de la cadena de ADN pasada como parémtro
int ListaCadenasADN::frecuenciaCadena(const CadenaADN &cadena)
{
    int count = 0;

    for (const auto &cur_cadena : *this)
    {
        if (cur_cadena == cadena)
            ++count;
    }

    return count;
}

template <typename MapType, typename KeyToString>
std::string dumpMapContentsToString(const MapType &m, KeyToString keyToString);

// NUEVO:Lista los codones en orden alfabético
string ListaCadenasADN::listaCodones()
{

    return dumpMapContentsToString(
        codonToFrequency,
        [](const std::string &codon)
        { return codon; });
}

// NUEVO:Lista las cadenas en orden alfabético
string ListaCadenasADN::listaCadenasADN()
{
    return dumpMapContentsToString(
        cadenaToFrequency,
        [](const CadenaADN &cadena)
        { return cadena.getSecuencia(); });
}

// NUEVO:Lista las cadenas que contienen un codón determinado, sin repetidos
string ListaCadenasADN::listaCadenasConCodon(const string &targetCodon)
{

    return dumpMapContentsToString(codonToCadenas[targetCodon], [](const CadenaADN &curCadena)
                                   { return curCadena.getSecuencia(); });
}

// NUEVO:elimina las cadenas de ADN con la misma secuencia, dejando sólo la primera que aparezca en la lista
void ListaCadenasADN::eliminaDuplicados()
{
}

/*
Dumps map keys to a string, separated by newlines.

Last key isn't newline-terminated.
*/
template <typename MapType, typename KeyToString>
std::string dumpMapContentsToString(const MapType &m, KeyToString keyToString)
{
    std::string result;
    auto it = m.begin();
    while (it != m.end())
    {
        result += keyToString(it->first);
        ++it;
        if (it != m.end())
            result += "\n";
    }
    return result;
}