// Ejemplo.cc
// Programa de pruebas exhaustivas para la práctica CadenaADN
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio> // std::remove
#include <cmath>  // fabs
#include "CadenaADN.h"

using namespace std;

class Tester
{
private:
    int total;
    int passed;

public:
    Tester()
    {
        total = 0;
        passed = 0;
    }

    void expectBool(const string &name, bool actual, bool expected)
    {
        total++;
        if (actual == expected)
        {
            passed++;
            cout << "[OK]   " << name << endl;
        }
        else
        {
            cout << "[FALLO] " << name << " -> esperado: " << (expected ? "true" : "false")
                 << ", obtenido: " << (actual ? "true" : "false") << endl;
        }
    }

    void expectInt(const string &name, int actual, int expected)
    {
        total++;
        if (actual == expected)
        {
            passed++;
            cout << "[OK]   " << name << endl;
        }
        else
        {
            cout << "[FALLO] " << name << " -> esperado: " << expected
                 << ", obtenido: " << actual << endl;
        }
    }

    void expectStr(const string &name, const string &actual, const string &expected)
    {
        total++;
        if (actual == expected)
        {
            passed++;
            cout << "[OK]   " << name << endl;
        }
        else
        {
            cout << "[FALLO] " << name << " -> esperado: \"" << expected
                 << "\", obtenido: \"" << actual << "\"" << endl;
        }
    }

    void expectDouble(const string &name, double actual, double expected, double eps = 1e-6)
    {
        total++;
        if (fabs(actual - expected) <= eps)
        {
            passed++;
            cout << "[OK]   " << name << endl;
        }
        else
        {
            cout << "[FALLO] " << name << " -> esperado: " << expected
                 << ", obtenido: " << actual << endl;
        }
    }

    void summary()
    {
        cout << "\n=== RESUMEN: " << passed << " / " << total << " pruebas superadas ===" << endl;
    }
};

int main()
{
    Tester T;
    cout << "=== INICIO DE PRUEBAS CadenaADN ===\n"
         << endl;

    // 1) Constructores básicos
    CadenaADN d_default; // debe ser ATG y descripción vacía
    T.expectStr("Ctor por defecto - secuencia", d_default.getSecuencia(), "ATG");
    T.expectStr("Ctor por defecto - descripcion", d_default.getDescripcion(), "");

    // Constructor sobrecargado: minúsculas -> mayúsculas, eliminar \n en descripción
    CadenaADN d_over("aGgcta", "desc\nwith\nnewlines");
    T.expectStr("Ctor sobrecargado - secuencia en mayúsculas", d_over.getSecuencia(), "AGGCTA");
    T.expectStr("Ctor sobrecargado - descripción sin saltos", d_over.getDescripcion(), "descwithnewlines");

    // Constructor sobrecargado con secuencia inválida -> inicializa a ATG (no se asume comportamiento sobre descripción)
    CadenaADN d_bad("XYZ", "otra desc");
    T.expectStr("Ctor sobrecargado con secuencia inválida -> secuencia ATG", d_bad.getSecuencia(), "ATG");
    T.expectStr("Ctor sobrecargado con secuencia inválida -> descripción", d_bad.getDescripcion(), "otra desc");

    // Constructor copia
    CadenaADN d_copy(d_over);
    T.expectBool("Ctor copia - igualdad secuencia (==)", d_copy == d_over, true);

    // Operador asignación
    CadenaADN d_assig;
    d_assig = d_over;
    T.expectBool("Operador= - igualdad secuencia", d_assig == d_over, true);

    // Operadores !=
    T.expectBool("Operador!= (distintas secuencias)", (d_default != d_over), true);

    // 2) Getters / Setters y validaciones
    CadenaADN s;
    bool ok;

    ok = s.setSecuencia("ATGCGC"); // válida
    T.expectBool("setSecuencia válida devuelve true", ok, true);
    T.expectStr("getSecuencia tras set válido", s.getSecuencia(), "ATGCGC");
    T.expectInt("getLongitud tras set", s.getLongitud(), 6);

    // setSecuencia inválida (carácter no válido)
    ok = s.setSecuencia("ATX");
    T.expectBool("setSecuencia inválida (carácter X) -> false", ok, false);
    T.expectStr("secuencia no cambiada tras set inválido", s.getSecuencia(), "ATGCGC");

    // setSecuencia longitud inválida (no múltiplo de 3)
    ok = s.setSecuencia("ATGA"); // len 4
    T.expectBool("setSecuencia inválida (longitud no múltiplo de 3) -> false", ok, false);

    // setSecuencia con minúsculas -> debe almacenarse en mayúsculas
    ok = s.setSecuencia("gggccc");
    T.expectBool("setSecuencia minúsculas -> true", ok, true);
    T.expectStr("setSecuencia minúsculas -> almacenada en mayúsculas", s.getSecuencia(), "GGGCCC");

    // setDescripcion: eliminar saltos de línea
    s.setDescripcion("L1\nL2\nL3");
    T.expectStr("setDescripcion elimina saltos de linea", s.getDescripcion(), "L1L2L3");

    // 3) Cuentas de nucleótidos y Chargaff
    CadenaADN seq_counts("AATCGG", "cuentas"); // A=2 T=1 C=1 G=2
    T.expectInt("cuentaA", seq_counts.cuentaA(), 2);
    T.expectInt("cuentaT", seq_counts.cuentaT(), 1);
    T.expectInt("cuentaC", seq_counts.cuentaC(), 1);
    T.expectInt("cuentaG", seq_counts.cuentaG(), 2);
    T.expectBool("cumpleChargaff (debe ser false)", seq_counts.cumpleChargaff(), false);

    CadenaADN seq_charg("AAATTTCCCGGG", "charg"); // A=3,T=3,C=3,G=3 -> cumple
    T.expectBool("cumpleChargaff (debe ser true)", seq_charg.cumpleChargaff(), true);
    T.expectDouble("proporcionGC (0.5)", seq_charg.proporcionGC(), 0.5);

    // 4) contarCodon
    CadenaADN seq_cod("ATGAAAGGC", "codons"); // codones: ATG, AAA, GGC
    T.expectInt("contarCodon GGC -> 1", seq_cod.contarCodon("GGC"), 1);
    T.expectInt("contarCodon AAA -> 1", seq_cod.contarCodon("AAA"), 1);
    T.expectInt("contarCodon ATG -> 1", seq_cod.contarCodon("ATG"), 1);
    T.expectInt("contarCodon con longitud !=3 -> 0", seq_cod.contarCodon("AG"), 0);

    // 5) buscarSubsecuencia y posicionUltimaAparicion
    CadenaADN seq_sub("TAAGGC", "sub"); // AGG en pos 2
    T.expectInt("buscarSubsecuencia AGG -> 2", seq_sub.buscarSubsecuencia("AGG"), 2);
    T.expectInt("buscarSubsecuencia inexistente -> -1", seq_sub.buscarSubsecuencia("TTT"), -1);
    T.expectInt("buscarSubsecuencia cadena vacía -> -1", seq_sub.buscarSubsecuencia(""), -1);

    CadenaADN seq_multi("TAGGCCAGG", "multi"); // AGG en pos 1 y 6
    T.expectInt("buscarSubsecuencia primera AGG -> 1", seq_multi.buscarSubsecuencia("AGG"), 1);
    T.expectInt("posicionUltimaAparicion AGG -> 6", seq_multi.posicionUltimaAparicion("AGG"), 6);

    // 6) longitudMaximaConsecutiva y cualquiera
    CadenaADN seq_cons("CGAAAAAATTTCCTT", "consec");
    T.expectInt("longitudMaximaConsecutiva('T') -> 3", seq_cons.longitudMaximaConsecutiva('T'), 3);
    T.expectInt("longitudMaximaConsecutiva('A') -> 6", seq_cons.longitudMaximaConsecutiva('A'), 6);
    T.expectInt("longitudMaximaConsecutiva('X') -> 0", seq_cons.longitudMaximaConsecutiva('X'), 0);
    T.expectInt("longitudMaximaConsecutivaCualquiera -> 6", seq_cons.longitudMaximaConsecutivaCualquiera(), 6);

    // 7) Mutaciones
    CadenaADN seq_mut("ATGCGA", "mut");
    T.expectBool("mutar pos 2 -> 'T' (válido)", seq_mut.mutar(2, 'T'), true);
    T.expectStr("mutación aplicada - secuencia ahora ATTCGA", seq_mut.getSecuencia(), "ATTCGA");
    // mutación fuera de rango
    T.expectBool("mutar pos 100 -> false", seq_mut.mutar(100, 'A'), false);
    // mutación con nucleótido inválido
    string before = seq_mut.getSecuencia();
    T.expectBool("mutar con 'X' -> false", seq_mut.mutar(1, 'X'), false);
    T.expectStr("secuencia no cambia tras mutación inválida", seq_mut.getSecuencia(), before);

    // 8) contarMutaciones
    CadenaADN m1("AAAAAA", "m1");
    CadenaADN m2("AAATAA", "m2"); // difiere en 1 posición
    T.expectInt("contarMutaciones m1 vs m2 -> 1", m1.contarMutaciones(m2), 1);
    CadenaADN m3("AAA", "m3");
    T.expectInt("contarMutaciones longitudes distintas -> -1", m1.contarMutaciones(m3), -1);

    // 9) Secuencias complementarias
    CadenaADN c1("ACTGAC", "c1");
    CadenaADN c2("TGACTG", "c2"); // complementaria de c1
    T.expectBool("esSecuenciaComplementaria c1 vs c2 -> true", c1.esSecuenciaComplementaria(c2), true);
    T.expectBool("esSecuenciaComplementaria c2 vs c1 -> true", c2.esSecuenciaComplementaria(c1), true);
    CadenaADN c_diff("TGACAC", "no");
    T.expectBool("esSecuenciaComplementaria (no complementaria) -> false", c1.esSecuenciaComplementaria(c_diff), false);
    CadenaADN c_short("TGAC", "corto");
    T.expectBool("esSecuenciaComplementaria longitudes distintas -> false", c1.esSecuenciaComplementaria(c_short), false);

    // 10) invertir
    CadenaADN inv("ACTGAG", "inv");
    inv.invertir();
    T.expectStr("invertir ACTGAG -> GAGTCA", inv.getSecuencia(), "GAGTCA");

    // 11) Guardar y cargar fichero
    const string fichero_ok = "tmp_test_adn.txt";
    const string fichero_unline = "tmp_one_line.txt";
    const string fichero_no = "no_existe_este_fichero.txt";

    // asegurarnos de que no existen los ficheros previos
    std::remove(fichero_ok.c_str());
    std::remove(fichero_unline.c_str());

    CadenaADN to_save("AATTCCGG", "miDescripcion");
    bool save_ok = to_save.guardarEnFichero(fichero_ok);
    T.expectBool("guardarEnFichero (archivo inexistente) -> true", save_ok, true);
    // segundo guardado debe fallar (archivo ya existe)
    T.expectBool("guardarEnFichero con fichero ya existente -> true", to_save.guardarEnFichero(fichero_ok), true);

    // cargar desde fichero correcto
    CadenaADN loaded;
    T.expectBool("cargarDesdeFichero fichero correcto -> true", loaded.cargarDesdeFichero(fichero_ok), true);
    T.expectStr("lectura secuencia guardada", loaded.getSecuencia(), to_save.getSecuencia());
    T.expectStr("lectura descripción guardada", loaded.getDescripcion(), to_save.getDescripcion());

    // crear fichero con una sola línea (solo descripcion) -> cargar debe devolver false
    {
        ofstream o(fichero_unline);
        o << "solo_una_linea" << endl;
        o.close();
    }
    CadenaADN loaded_bad;
    T.expectBool("cargarDesdeFichero fichero 1 linea -> false", loaded_bad.cargarDesdeFichero(fichero_unline), false);

    // cargar fichero inexistente -> false
    T.expectBool("cargarDesdeFichero fichero inexistente -> false", loaded_bad.cargarDesdeFichero(fichero_no), false);

    // limpieza de ficheros temporales
    std::remove(fichero_ok.c_str());
    std::remove(fichero_unline.c_str());

    // 12) getLongitud ya testado en setSecuencia; confirmamos en otro objeto
    CadenaADN gl("ATGATGATG", "long");
    T.expectInt("getLongitud 9", gl.getLongitud(), 9);

    // FIN resumen
    T.summary();

    cout << "\n=== FIN PRUEBAS ===" << endl;
    return 0;
}
