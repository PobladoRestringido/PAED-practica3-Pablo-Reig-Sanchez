#include "CadenaADN.h"
#include <fstream>
#include <algorithm>
#include <fstream>
#include <cctype>
using namespace std;

namespace utils
{
    std::string remove_newlines(std::string s)
    {
        /*
        Removes all the newline characters within a string.
        */
        auto new_string_end = std::remove(s.begin(), s.end(), '\n');
        s.erase(new_string_end, s.end());

        return s;
    }

    std::string to_uppercase(std::string s)
    {
        /*
        Turns all characters within a string to uppercase.
        */
        std::transform(
            s.begin(), s.end(),
            s.begin(),
            [](unsigned char c)
            {
                return std::toupper(c);
            });

        return s;
    }

    int count_substring(const std::string &super, const std::string &sub)
    {
        /*
        Returns the number of times a certain substring appears within a larger
        superstring.
        */

        if (sub.empty())
            return -1;

        int match_count = 0;
        std::size_t current_position = 0;

        while ((current_position = super.find(sub, current_position)) != std::string::npos)
        {
            ++match_count;
            current_position += sub.size();
        }

        return match_count;
    }

    int longest_run(const std::string &s, char target)
    {
        /*
        Counts the longest consecutive run of a given char within a string.

        If no `target` is provided, counts the longest consecutive run of ANY char
        within the string.
         */

        int max_len = 0, current = 0;
        char previous = '\0';

        for (char c : s)
        {
            if (target == '\0')
            {
                if (c == previous)
                {
                    ++current;
                }
                else
                {
                    current = 1;
                    previous = c;
                }
            }
            else if (c == target)
            {
                ++current;
            }
            else
            {
                current = 0;
            }
            if (current > max_len)
                max_len = current;
        }

        return max_len;
    }

    int count_mismatches(const std::string &a, const std::string &b)
    {
        /*
        Counts the number of mismatches between two strings of the same length.

        If the strings don't share the same length, -1 is returned instead.
        */
        if (a.size() != b.size())
            return -1;

        int mismatches = 0;
        for (size_t i = 0; i < a.size(); ++i)
        {
            if (a[i] != b[i])
                ++mismatches;
        }
        return mismatches;
    }

    /*int levenshtein_distance(const std::string &a, const std::string &b)
    {

        Computes the levenshtein distance between two strings.

        std::string larger_string, shorter_string;

        if (a.length() > b.length())
        {
            larger_string = a;
            shorter_string = b;
        }
        else
        {
            larger_string = b;
            shorter_string = a;
        }
    }*/

}

// Constructor por defecto
CadenaADN::CadenaADN()
{
    sequence = "ATG";
    description = "";
}

// Constructor sobrecargado
CadenaADN::CadenaADN(const string &sec, const string &desc)
{
    /*
    Notes
    -----
    The provided nucelotide sequence must be valid; otherwise defaults to "ATG".

    The provided description mustn't contain newline characters; otherwise they're removed.
    */
    std::string uppercase_sec = utils::to_uppercase(sec);
    if (is_valid_sequence(uppercase_sec))
    {
        sequence = uppercase_sec;
    }
    else
    {
        sequence = "ATG";
    }

    description = utils::remove_newlines(desc);
}

// Constructor de copia
CadenaADN::CadenaADN(const CadenaADN &other)
    : sequence(other.sequence),
      description(other.description)
{
}

// Destructor:
CadenaADN::~CadenaADN()
{
    /*
    Returns the current CadenaADN to the default state.

    `sequence` gets assigned "ATG"; `description` gets assigned "".
    */
    sequence = "ATG";
    description = "";
}

// Operador de asignación
CadenaADN &CadenaADN::operator=(const CadenaADN &other)
{
    if (this != &other)
    {
        this->sequence = other.sequence;
        this->description = other.description;
    }

    return *this;
}

// Operadores de comparación
bool CadenaADN::operator==(const CadenaADN &other) const
{
    return this->sequence == other.sequence;
}

bool CadenaADN::operator!=(const CadenaADN &other) const
{
    return !(*this == other);
}

// Getters y setters
string CadenaADN::getSecuencia() const
{
    return this->sequence;
}
string CadenaADN::getDescripcion() const
{
    return this->description;
}

int CadenaADN::getLongitud() const
{
    /*
    Returns the length of the object's DNA sequence.
    */
    return this->sequence.size();
}

bool CadenaADN::setSecuencia(const string &sec)
{
    /*
    Setter for sequence attribute.

    Notes
    -----
    Provided `sec` is internally converted to uppercase.
    */
    std::string uppercase_sec = utils::to_uppercase(sec);

    if (is_valid_sequence(uppercase_sec))
    {
        this->sequence = uppercase_sec;
        return true;
    }
    return false;
}

void CadenaADN::setDescripcion(const string &desc)
{
    /*
    Setter for description attribute.

    Notes
    -----
    Provided `desc` is internally stripped of any newline characters.
    */
    std::string stripped_desc = utils::remove_newlines(desc);

    this->description = stripped_desc;
}

// Cuentas de nucleótidos
int CadenaADN::cuentaA() const
{
    /*
    Number of times nucleotide A appears within the sequence.
    */

    return utils::count_substring(this->sequence, "A");
}
int CadenaADN::cuentaT() const
{
    /*
    Number of times nucleotide T appears within the sequence.
    */

    return utils::count_substring(this->sequence, "T");
}
int CadenaADN::cuentaC() const
{
    /*
    Number of times nucleotide C appears within the sequence.
    */

    return utils::count_substring(this->sequence, "C");
}
int CadenaADN::cuentaG() const
{
    /*
    Number of times nucleotide G appears within the sequence.
    */

    return utils::count_substring(this->sequence, "G");
}

bool CadenaADN::cumpleChargaff() const
{
    /*
    Whether the sequence meets all the criteria laid down by Chargaff's rules.
    */
    int a_count = this->cuentaA();
    int t_count = this->cuentaT();
    int g_count = this->cuentaG();
    int c_count = this->cuentaC();

    return a_count == t_count && g_count == c_count && a_count + g_count == t_count + c_count;
}

double CadenaADN::proporcionGC() const
{
    /*
    Returns the proportion of G and C nucleotides with respect to all nucleotides in the sequence.
    */
    int g_count = this->cuentaG();
    int c_count = this->cuentaC();

    return (double)(g_count + c_count) / this->sequence.length();
}

// Búsqueda de codones
int CadenaADN::contarCodon(const string &codon) const
{
    /*
    Returns the number of times a certain codon appears in the sequence.

    Notes
    -----
    If codon length isn't exactly 3, a count of 0 is always returned.
    */

    if (codon.length() != 3)
        return 0;

    int count = 0;

    std::vector<std::string> codones = exposeCodones();

    for (const auto &cur_codon : codones)
    {
        if (cur_codon == codon)
            count += 1;
    }
    return count;
}

// Búsqueda de subsecuencias
int CadenaADN::buscarSubsecuencia(const string &sub) const
{
    /*
    Returns the position of the first found instance of a certain substring within the
    sequence.

    If `sub` can't be found, -1 is returned.
    If `sub` is empty, -1 is also returned.
    */
    if (sub.empty())
        return -1;

    size_t position = this->sequence.find(sub);

    if (position == std::string::npos)
        return -1;

    return (int)position;
}

int CadenaADN::posicionUltimaAparicion(const string &sub) const
{
    /*
    Returns the position of the last found instance of a certain substring within the
    sequence.

    If `sub` can't be found, -1 is returned.
    If `sub` is empty, -1 is also returned.
    */
    if (sub.empty())
        return -1;

    size_t position = this->sequence.rfind(sub);

    if (position == std::string::npos)
        return -1;

    return (int)position;
}

// Búsqueda de elementos consecutivos
int CadenaADN::longitudMaximaConsecutiva(char nucleotide) const
{
    /*
    Counts the longest consecutive run of a given nucleotide within the object's sequence.
    */

    return utils::longest_run(this->sequence, nucleotide);
}
int CadenaADN::longitudMaximaConsecutivaCualquiera() const
{
    return utils::longest_run(this->sequence, '\0');
}

// Mutaciones
bool CadenaADN::mutar(int posicion, char nucleotide)
{
    /*
    Replaces the nucleotide at a specified position.
    */
    nucleotide = toupper(nucleotide);

    if (posicion < 0 || posicion > this->getLongitud() - 1 || (nucleotide != 'A' && nucleotide != 'T' && nucleotide != 'C' && nucleotide != 'G'))
        return false;

    this->sequence[posicion] = nucleotide;
    return true;
}

int CadenaADN::contarMutaciones(const CadenaADN &other_cad) const
{
    /*
    Returns the number of mismatching nucleotides between two sequences.

    If the sequences don't share the same length, -1 is returned.
    */
    return utils::count_mismatches(this->sequence, other_cad.getSecuencia());
}

// Secuencias complementarias
bool CadenaADN::esSecuenciaComplementaria(const CadenaADN &other_cad) const
{
    /*
    Returns whether two dna sequences are complementary.

    Two sequences are complementary if all their nucleotides are complementary 1:1
    */

    const std::string &other_sequence = other_cad.getSecuencia();

    if (this->sequence.length() != other_sequence.length())
        return false;

    char this_nucleotide = '\0';
    char other_nucleotide = '\0';

    for (size_t i = 0; i < this->sequence.length(); i++)
    {
        this_nucleotide = this->sequence[i];
        other_nucleotide = other_sequence[i];

        if (!CadenaADN::are_complementary_nucleotides(this_nucleotide, other_nucleotide))
        {
            return false;
        }
    }
    return true;
}

// Modificaciones
void CadenaADN::invertir()
{
    /*
    Inverts the order of the current object's sequence.
    */
    std::reverse(this->sequence.begin(), this->sequence.end());
}

// Almacenaje y lectura de fichero
bool CadenaADN::guardarEnFichero(const string &file_path) const
{
    /*
    Stores information about the current object's state at a specified file.

    Returns false if something went wrong somewhere along the process.
    */

    std::ofstream file(file_path);
    if (!file.is_open())
        return false;

    file << this->sequence << '\n'
         << this->description << '\n';

    return file.good();
}

bool CadenaADN::cargarDesdeFichero(const string &file_path)
{
    /*
    Changes the state of current object by reading the contents of a file.

    Returns false if something goes wrong.
    */

    std::ifstream file(file_path);
    if (!file.is_open())
        return false;

    std::string temporary_sequence, temporary_description;

    if (!std::getline(file, temporary_sequence))
        return false;

    if (!std::getline(file, temporary_description))
        return false;

    this->sequence = temporary_sequence;
    this->description = temporary_description;

    return true;
}

bool CadenaADN::is_valid_sequence(const std::string &sequence)
{
    /*
    Checks whether a given string is a valid nucleotide sequence.

    A nucleotide sequencec is valid if it's not empty and contains only valid nucleotides, in
    groups of 3.
    */

    if (sequence.empty() || sequence.size() % 3 != 0)
    {
        return false;
    }

    for (size_t i = 0; i < sequence.length(); ++i)
    {
        char nucleotide = sequence[i];

        if (nucleotide != 'A' && nucleotide != 'T' && nucleotide != 'C' && nucleotide != 'G')
        {
            return false;
        }
    }

    return true;
}

bool CadenaADN::are_complementary_nucleotides(char a, char b)
{
    /*
    Checks whether two nucleotides are complementary.

    If parameters aren't valid nucleotides, `false` is returned.
    */
    a = toupper(a);
    b = toupper(b);

    switch (a)
    {
    case 'A':
        return b == 'T';
    case 'T':
        return b == 'A';
    case 'C':
        return b == 'G';
    case 'G':
        return b == 'C';
    default:
        return false;
    }
}

std::vector<std::string> CadenaADN::exposeCodones() const
{
    std::vector<std::string> codonesVector;
    codonesVector.reserve(getLongitud() / 3);

    for (int i = 0; i < getLongitud(); i += 3)
    {
        std::string cur_codon = sequence.substr(i, 3);

        codonesVector.push_back(cur_codon);
    }

    return codonesVector;
}

/*bool CadenaADN::is_valid_description(const std::string &description)
{

   Checks whether a given description is valid (can't contain newline characters).


   if (description.find('\n') != std::string::npos)
   {
      return true;
   }
   return false;
}*/
