#ifndef __CADENAADN__
#define __CADENAADN__

#include <string>
#include <vector>
using namespace std;

class CadenaADN
{

private:
    std::string sequence;
    std::string description;

public:
    // Constructor por defecto
    CadenaADN();
    // Constructor sobrecargado
    CadenaADN(const string &, const string &);
    // Constructor de copia
    CadenaADN(const CadenaADN &);
    // Destructor:
    ~CadenaADN();
    // Operador de asignación
    CadenaADN &operator=(const CadenaADN &);

    // Operadores de comparación
    bool operator==(const CadenaADN &) const;
    bool operator!=(const CadenaADN &) const;

    // Getters y setters
    string getSecuencia() const;
    string getDescripcion() const;
    int getLongitud() const;
    bool setSecuencia(const string &);
    void setDescripcion(const string &);

    // Cuentas de nucleótidos
    int cuentaA() const;
    int cuentaT() const;
    int cuentaC() const;
    int cuentaG() const;
    bool cumpleChargaff() const;
    double proporcionGC() const;

    // Búsqueda de codones
    int contarCodon(const string &) const;

    // Búsqueda de subsecuencias
    int buscarSubsecuencia(const string &) const;
    int posicionUltimaAparicion(const string &) const;

    // Búsqueda de elementos consecutivos
    int longitudMaximaConsecutiva(char) const;
    int longitudMaximaConsecutivaCualquiera() const;

    // Mutaciones
    bool mutar(int, char);
    int contarMutaciones(const CadenaADN &) const;

    // Secuencias complementarias
    bool esSecuenciaComplementaria(const CadenaADN &) const;

    // Modificaciones
    void invertir();

    // Almacenaje y lectura de fichero
    bool guardarEnFichero(const string &) const;
    bool cargarDesdeFichero(const string &);

    static bool is_valid_sequence(const std::string &);
    static bool is_valid_description(const std::string &);
    static bool are_complementary_nucleotides(char a, char b);
};

#endif
