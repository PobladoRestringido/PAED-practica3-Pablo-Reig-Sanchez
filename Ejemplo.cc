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
    /*
    test.expectEqualVec(obtenerSecuenciasInversa(lista), {"AGTCAA", "GATATC", "ATG", "TTGCAA"}, "Orden inverso correcto tras inserciones");*/

    // --- Resultado global ---
    test.summary();
    return 0;
}
