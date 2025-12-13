#include <iostream>
#include <vector>
#include <string>
#include "CadenaADN.h"
#include "ListaCadenasADN.h"
using namespace std;

/* ========= Clase auxiliar para pruebas ========= */
class TestSuite
{
    int total = 0;
    int passed = 0;

    // Formatea un vector<string> en "[elem1, elem2, ...]"
    static string vectorToStr(const vector<string> &v)
    {
        string s = "[";
        for (size_t i = 0; i < v.size(); i++)
        {
            s += v[i];
            if (i + 1 < v.size())
                s += ", ";
        }
        s += "]";
        return s;
    }

public:
    // Prueba genérica con condición booleana
    void check(bool condition, const string &desc)
    {
        total++;
        if (condition)
        {
            passed++;
            cout << "OK " << desc << endl;
        }
        else
        {
            cout << "ERROR " << desc << endl;
        }
    }

    // Prueba de igualdad entre dos valores escalares
    template <typename T>
    void expectEqual(const T &obtained, const T &expected, const string &desc)
    {
        total++;
        if (obtained == expected)
        {
            passed++;
            cout << "OK " << desc << endl;
        }
        else
        {
            cout << "ERROR " << desc << endl;
            cout << "   ├─ Obtenido: " << obtained << endl;
            cout << "   └─ Esperado: " << expected << endl;
        }
    }

    // Prueba de igualdad entre dos vectores<string>
    void expectEqualVec(const vector<string> &obt, const vector<string> &exp, const string &desc)
    {
        total++;
        if (obt == exp)
        {
            passed++;
            cout << "OK " << desc << endl;
        }
        else
        {
            cout << "ERROR " << desc << endl;
            cout << "   ├─ Obtenido: " << vectorToStr(obt) << endl;
            cout << "   └─ Esperado: " << vectorToStr(exp) << endl;
        }
    }

    // Resumen final
    void summary() const
    {
        cout << "\n=== RESULTADO FINAL: " << passed << "/" << total
             << " pruebas superadas (" << (100.0 * passed / total) << "%) ===" << endl;
    }

    ListaCadenasADN makeLista(std::initializer_list<CadenaADN> elems)
    {
        ListaCadenasADN l;
        for (const auto &e : elems)
        {
            l.insertarFinal(e);
        }
        return l;
    }

    // Returns iterator to n-th element in list, or end() if beyond range
    IteradorLista nth(ListaCadenasADN &lista, int pos)
    {
        IteradorLista it = lista.begin();
        for (int i = 0; i < pos && it != lista.end(); ++i)
        {
            it.step();
        }
        return it;
    }
};

/* ========= Funciones auxiliares ========= */

// Devuelve las secuencias de una lista en orden
vector<string> obtenerSecuencias(ListaCadenasADN &lista)
{
    vector<string> v;
    for (IteradorLista it = lista.begin(); it != lista.end(); it.step())
        v.push_back(lista.getCadenaADN(it).getSecuencia());

    return v;
}

// Devuelve las secuencias de una lista en orden inverso
vector<string> obtenerSecuenciasInversa(ListaCadenasADN &lista)
{
    vector<string> v;
    for (IteradorLista it = lista.rbegin(); it != lista.rend(); it.rstep())
        v.push_back(lista.getCadenaADN(it).getSecuencia());
    return v;
}

/* ========= Programa principal ========= */
int main()
{
    TestSuite test;
    cout << "=== PRUEBAS DE ListaCadenasADN ===" << endl;

    // --- Crear cadenas base ---
    CadenaADN c1("ATG", "Inicio");
    CadenaADN c2("GATATC", "EcoRV");
    CadenaADN c3("AGTCAA", "Otra cadena");
    CadenaADN c4("GATGAT", "Cadena1");
    CadenaADN c4bis("GATGAT", "Otra descripción");
    CadenaADN c5("TTGCAA", "Final");

    // --- Lista vacía ---
    ListaCadenasADN lista;
    test.check(lista.esVacia(), "Lista vacía inicial");
    test.expectEqual(lista.longitud(), 0, "Longitud inicial = 0");

    // --- Inserciones al inicio y final ---
    lista.insertarInicio(c1); // [ATG]
    lista.insertarFinal(c2);  // [ATG, GATATC]
    lista.insertarFinal(c3);  // [ATG, GATATC, AGTCAA]
    lista.insertarInicio(c5); // [ TTGCAA, ATG, GATATC, AGTCAA]
    test.expectEqual(lista.longitud(), 4, "Longitud tras 4 inserciones");

    test.expectEqualVec(obtenerSecuencias(lista), {"TTGCAA", "ATG", "GATATC", "AGTCAA"}, "Orden correcto tras inserciones");
    test.expectEqualVec(obtenerSecuenciasInversa(lista), {"AGTCAA", "GATATC", "ATG", "TTGCAA"}, "Orden inverso correcto tras inserciones");

    // --- Copia y operador de asignación ---
    ListaCadenasADN copia(lista);
    ListaCadenasADN asignada;
    asignada = lista;
    test.expectEqualVec(obtenerSecuencias(copia), obtenerSecuencias(lista), "Constructor de copia correcto");
    test.expectEqualVec(obtenerSecuencias(asignada), obtenerSecuencias(lista), "Operador de asignación correcto");

    lista.insertarFinal(c4);
    test.check(obtenerSecuencias(lista) != obtenerSecuencias(copia), "Copia independiente del original");
    test.check(obtenerSecuencias(lista) != obtenerSecuencias(asignada), "Asignada independiente del original");

    // --- Asignar en posición ---
    IteradorLista it = copia.begin();
    copia.asignar(it, c4); // reemplaza el primero
    test.expectEqualVec(obtenerSecuencias(copia), {"GATGAT", "ATG", "GATATC", "AGTCAA"}, "asignar() modifica nodo correcto");
    IteradorLista badIterator;
    test.check(!copia.asignar(badIterator, c1), "`ListaCadenasADN::asignar()` returns False for invalid iterator");

    // --- BorrarPrimera y BorrarUltima ---
    copia.borrarPrimera();
    copia.borrarUltima();
    test.expectEqualVec(obtenerSecuencias(copia), {"ATG", "GATATC"}, "Borrado de extremos correcto");

    ListaCadenasADN vacia;
    test.check(!vacia.borrarPrimera(), "BorrarPrimera de lista vacía correcto");
    test.check(!vacia.borrarUltima(), "BorrarUltima de lista vacía correcto");

    // --- Insertar en posición intermedia ---
    ListaCadenasADN lista2;
    lista2.insertarFinal(c1); // [ATG]
    lista2.insertarFinal(c2); // [ATG, GATATC]
    lista2.insertarFinal(c3); // [ATG, GATATC, AGTCAA]
    IteradorLista itpos = lista2.begin();
    itpos.step();               // posición intermedia
    lista2.insertar(itpos, c4); // [ATG, GATGAT, GATATC, AGTCAA]
    test.expectEqualVec(obtenerSecuencias(lista2), {"ATG", "GATGAT", "GATATC", "AGTCAA"},
                        "Inserción intermedia correcta");
    test.expectEqualVec(obtenerSecuenciasInversa(lista2), {"AGTCAA", "GATATC", "GATGAT", "ATG"},
                        "Inserción intermedia correcta (orden inverso)");

    test.check(!lista2.insertar(badIterator, c1), "`ListaCadenasADN::insertar()` returns False for invalid iterator");

    // --- Contar() ---
    test.expectEqual(lista2.contar(c4), 1, "Contar() encuentra 1 coincidencia");
    lista2.insertarFinal(c4);
    test.expectEqual(lista2.contar(c4), 2, "Contar() encuentra 2 coincidencias tras duplicar");

    test.expectEqual(lista2.contar(c4bis), 2, "Contar() encuentra 2 coincidencias con distina descripción");

    // --- diferencia() ---
    ListaCadenasADN lista3;
    lista3.insertarInicio(c3);
    lista3.insertarInicio(c2); // [GATATC, AGTCAA]
    ListaCadenasADN dif = lista2.diferencia(lista3);
    test.expectEqualVec(obtenerSecuencias(dif), {"ATG", "GATGAT", "GATGAT"},
                        "diferencia() devuelve elementos esperados");
    test.expectEqualVec(obtenerSecuenciasInversa(dif), {"GATGAT", "GATGAT", "ATG"},
                        "diferencia() devuelve elementos esperados (orden inverso)");

    // --- concatenar(Lista) ---
    ListaCadenasADN concat;
    concat = lista2.concatenar(lista3);
    test.expectEqualVec(obtenerSecuencias(concat),
                        {"ATG", "GATGAT", "GATATC", "AGTCAA", "GATGAT", "GATATC", "AGTCAA"},
                        "concatenar(Lista) mantiene orden");
    test.expectEqualVec(obtenerSecuenciasInversa(concat),
                        {"AGTCAA", "GATATC", "GATGAT", "AGTCAA", "GATATC", "GATGAT", "ATG"},
                        "concatenar(Lista) mantiene orden inverso");

    test.expectEqualVec(obtenerSecuencias(lista2),
                        {"ATG", "GATGAT", "GATATC", "AGTCAA", "GATGAT"},
                        "`ListaCadenasADN::concatenar(Lista)` doesn't modify object it's called on");
    test.expectEqualVec(obtenerSecuenciasInversa(lista2),
                        {"GATGAT", "AGTCAA", "GATATC", "GATGAT", "ATG"},
                        "`ListaCadenasADN::concatenar(Lista)` doesn't modify object "
                        "it's called on (inverse check)");

    test.expectEqualVec(obtenerSecuencias(lista3),
                        {"GATATC", "AGTCAA"},
                        "`ListaCadenasADN::concatenar(Lista)` doesn't modify other object "
                        "passed as parameter");
    test.expectEqualVec(obtenerSecuenciasInversa(lista3),
                        {"AGTCAA", "GATATC"},
                        "`ListaCadenasADN::concatenar(Lista)` doesn't modify other object "
                        "passed as parameter (inverse check)");

    // --- concatenar() genera CadenaADN con secuencia total ---
    CadenaADN total = lista2.concatenar();
    string esperado = "ATGGATGATGATATCAGTCAAGATGAT";
    test.expectEqual(total.getSecuencia(), esperado,
                     "concatenar() crea secuencia completa correcta");
    test.check(total.getDescripcion() == "",
               "`ListaCadenasADN::concatenar()` returns empty description");

    ListaCadenasADN listaVacia;
    CadenaADN cadenaVacia = listaVacia.concatenar();
    CadenaADN cadenaEsperado;
    test.check(cadenaVacia == cadenaEsperado,
               "`ListaCadenasADN::concatenar()` returns expected for empty case");

    // ---  borrar(Iterador) ---
    IteradorLista itb = lista2.begin();
    itb.step(); // GATGAT
    lista2.borrar(itb);
    test.expectEqual(lista2.contar(c4), 1, "borrar(Iterador) elimina un nodo");
    test.expectEqualVec(obtenerSecuencias(lista2), {"ATG", "GATATC", "AGTCAA", "GATGAT"},
                        "borrar (Iterador): resultado correcto");
    test.expectEqualVec(obtenerSecuenciasInversa(lista2), {"GATGAT", "AGTCAA", "GATATC", "ATG"},
                        "borrar (Iterador): resultado correcto (orden inverso)");
    test.check(
        itb.esVacio(),
        "`ListaCadenasADN::borrar(it)` invalidates iterator passed as parameter");

    IteradorLista emptyIterator;
    test.check(
        !lista2.borrar(emptyIterator),
        "`ListaCadenasADN::borrar(it)` returns false for empty iterator");

    // --- aCadena() ---
    ListaCadenasADN lista4;
    lista4.insertarFinal(c1);
    lista4.insertarFinal(c2);
    string salida = lista4.aCadena();
    test.check(
        salida == "Inicio:ATG\nEcoRV:GATATC",
        "aCadena devuelve la salida correcta");
    // cout << "Salida `lista4.aCadena()`\n" << salida;

    ListaCadenasADN lista5;
    salida = lista5.aCadena();
    test.check(
        salida == "",
        "aCadena devuelve la salida correcta para lista vacía");

    // --- Vaciar---
    while (!lista2.esVacia())
        lista2.borrarPrimera();
    test.expectEqual(lista2.longitud(), 0, "Borrado completo de lista correcto");

    /*  PRUEBAS QUE DEBEN SER ESCRITAS POR EL ALUMNADO  */

    // --- InsertarDespues en posición intermedia ---
    /*Inserta en la lista 10 las cadenas c1, c2 y c3,
    de manera que la lista resultante sea [ATG, GATATC, AGTCAA] */
    ListaCadenasADN lista10 = test.makeLista({c1, c2, c3});

    /* Haz que el iterador it10 apunte al segundo elemento de la lista (GATATC) */
    IteradorLista it10 = lista10.begin();
    it10.step();

    /* Llama a insertarDespues para insertar después de la posición
    apuntada por it10 la cadena c4 */
    lista10.insertarDespues(it10, c4);

    test.expectEqualVec(
        obtenerSecuencias(lista10),
        {"ATG", "GATATC", "GATGAT", "AGTCAA"},
        "Inserción intermedia (después) correcta");
    test.expectEqualVec(
        obtenerSecuenciasInversa(lista10),
        {"AGTCAA", "GATGAT", "GATATC", "ATG"},
        "Inserción intermedia (después) correcta (orden inverso)");

    test.check(
        lista10.insertarDespues(it10, c1),
        "`ListaCadenasADN::insertarDespues()` returns True for valid iterator");

    test.check(
        !lista10.insertarDespues(emptyIterator, c1),
        "`ListaCadenasADN::insertarDespues()` returns False for empty iterator");

    // --- InsertarDespues en posición final ---

    /*Inserta en la lista11 las cadenas c1, c2 y c3,
    de manera que la lista resultante sea [ATG, GATATC, AGTCAA] */
    ListaCadenasADN lista11 = test.makeLista({c1, c2, c3});

    /* Haz que el iterador it11 apunte al último elemento de la lista (AGTCAA) */
    IteradorLista it11 = lista11.end();
    it11.rstep();

    /* Llama a insertarDespues para insertar después de la posición
    apuntada por it11 la cadena c4 */
    lista11.insertarDespues(it11, c4);

    test.expectEqualVec(
        obtenerSecuencias(lista11),
        {"ATG", "GATATC", "AGTCAA", "GATGAT"},
        "Inserción intermedia (después) correcta");
    test.expectEqualVec(
        obtenerSecuenciasInversa(lista11),
        {"GATGAT", "AGTCAA", "GATATC", "ATG"},
        "Inserción intermedia (después) correcta (orden inverso)");

    // --- Cuentas de codones y cadenas ---
    CadenaADN cc1("ATG", "Cadena 1");
    CadenaADN cc2("GATATCATC", "Cadena 2");
    CadenaADN cc3("GCATCG", "Borrar 1");
    CadenaADN cc4("GCATCG", "Cadena 3");
    CadenaADN cc5("CCTAGAATC", "Cadena 4");
    CadenaADN cc6("GCATCG", "Otra cadena");
    CadenaADN cc7("CCCATC", "Borrar 2");

    /* Inserta en la lista11 las cadenas cc1, ...,cc6
    de manera que la lista resultante sea:
    [ATG, GATATCATC, GCATCG, GCATCG, CCTAGAATC, GCATCG, CCCATC] */
    ListaCadenasADN lista12 = test.makeLista({cc1, cc2, cc3, cc4, cc5, cc6, cc7});

    /*
    Borra las cadenas cc3 y cc7, de manera que la lista resultante sea:
    [ATG, GATATCATC, GCATCG, CCTAGAATC, GCATCG]
    */
    auto itcc3 = test.nth(lista12, 2);
    auto itcc7 = test.nth(lista12, 6);
    lista12.borrar(itcc3);
    lista12.borrar(itcc7);

    test.expectEqualVec(
        obtenerSecuencias(lista12),
        {"ATG", "GATATCATC", "GCATCG", "CCTAGAATC", "GCATCG"},
        "Inserción y borrado pre probar cuentas correcta");
    test.expectEqualVec(
        obtenerSecuenciasInversa(lista12),
        {"GCATCG", "CCTAGAATC", "GCATCG", "GATATCATC", "ATG"},
        "Inserción y borrado pre probar cuentas (orden inverso)");

    test.expectEqual(lista12.frecuenciaCodon("ATC"), 3, "frecuenciaCodon");
    /*test.expectEqual(lista12.frecuenciaCadena(cc3), 2, "frecuenciaCadena");

    test.expectEqual(
        lista12.listaCodones(),
        string("AGA\nATC\nATG\nCCT\nGAT\nGCA\nTCG"),
        "listaCodones");
    test.expectEqual(
        lista12.listaCadenasADN(),
        string("ATG\nCCTAGAATC\nGATATCATC\nGCATCG"),
        "listaCadenasADN");

    test.expectEqual(
        lista12.listaCadenasConCodon("ATC"),
        string("CCTAGAATC\nGATATCATC"),
        "listaCadenasConCodon");*/

    // --- Resultado global ---
    test.summary();
    return 0;
}
