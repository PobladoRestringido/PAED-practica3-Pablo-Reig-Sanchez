#include "CadenaADN.h"
#include "ListaCadenasADN.h"
#include<fstream>
#include <iostream>
#include <chrono>
#include <vector>
using namespace std;


/* ========= Clase auxiliar para pruebas ========= */
class TestSuite {
    int total = 0;
    int passed = 0;

    // Formatea un vector<string> en "[elem1, elem2, ...]"
    static string vectorToStr(const vector<string> &v) {
        string s = "[";
        for (size_t i = 0; i < v.size(); i++) {
            s += v[i];
            if (i + 1 < v.size()) s += ", ";
        }
        s += "]";
        return s;
    }

public:
    // Prueba genérica con condición booleana
    void check(bool condition, const string &desc) {
        total++;
        if (condition) {
            passed++;
            cout << "OK " << desc << endl;
        } else {
            cout << "ERROR " << desc << endl;
        }
    }

    // Prueba de igualdad entre dos valores escalares
    template <typename T>
    void expectEqual(const T &obtained, const T &expected, const string &desc) {
        total++;
        if (obtained == expected) {
            passed++;
            cout << "OK " << desc << endl;
        } else {
            cout << "ERROR " << desc << endl;
            cout << "   ├─ Obtenido: " << obtained << endl;
            cout << "   └─ Esperado: " << expected << endl;
        }
    }

    // Prueba de igualdad entre dos vectores<string>
    void expectEqualVec(const vector<string> &obt, const vector<string> &exp, const string &desc) {
        total++;
        if (obt == exp) {
            passed++;
            cout << "OK " << desc << endl;
        } else {
            cout << "ERROR " << desc << endl;
            cout << "   ├─ Obtenido: " << vectorToStr(obt) << endl;
            cout << "   └─ Esperado: " << vectorToStr(exp) << endl;
        }
    }

    // Resumen final
    void summary() const {
        cout << "\n=== RESULTADO FINAL: " << passed << "/" << total
             << " pruebas superadas (" << (100.0 * passed / total) << "%) ===" << endl;
    }
};


int main(){
    ListaCadenasADN lista;
    CadenaADN cad1;
    int i=0;

    cout << "Insertando elementos ..." << flush;
    ifstream f;
    f.open("inserciones.txt");
    if(f.is_open()){
        string s;
        while(getline(f,s)){
            cad1.setSecuencia(s);
            if(i%2 == 0)
            	lista.insertarInicio(cad1);
            else
            	lista.insertarFinal(cad1);
            i++;
        }
        f.close();
        cout << " OK" << endl << flush;
    }else
    	cout << " ERROR" << endl << flush;
    
    
    
    cout << "Borrando elementos ... " << flush;
    f.open("borrados.txt");
    if(f.is_open()){
        int pos_borrado;
        while(f >> pos_borrado){
            if(pos_borrado> 0){
            	IteradorLista it=lista.begin();
            	for(int i=0; i< pos_borrado && it!=lista.end(); i++)
            		it.step();
            	lista.borrar(it);
            }
            if(pos_borrado<0){
            	IteradorLista it=lista.rbegin();
            	for(int i=0; i< -pos_borrado && it!= lista.rend(); i++)
            		it.rstep();
            	lista.borrar(it);
            }
        }
        f.close();
        
        for(int i=0; i < 10000; i++){
        	lista.borrarPrimera();
        	lista.borrarUltima();
        }
        cout << " OK" << endl << flush;
    }else
    	cout << " ERROR" << endl << flush;
    
    
    cout << "Insertando de elementos otra vez ... " << flush;
    i=0;
    f.open("inserciones.txt");
    if(f.is_open()){
        string s;
        IteradorLista it=lista.begin();
        while(getline(f,s)){
            it.step();
            cad1.setSecuencia(s);
            if(i%2 == 0)
            	lista.insertar(it,cad1);
            else
            	lista.insertarDespues(it,cad1);
            i++;
            if(i>=1000)
            	break;
        }
        f.close();
        cout << " OK" << endl << flush;
    }else
    	cout << " ERROR" << endl << flush;
    
    
    cout << "Modificando elementos ... " << flush;
    i=0;
    f.open("inserciones.txt");
    if(f.is_open()){
        string s;
        IteradorLista it=lista.rbegin();
        while(getline(f,s)){
            it.rstep();
            cad1.setSecuencia(s);
            lista.asignar(it,cad1);
            i++;
            if(i>=1000)
            	break;
        }
        f.close();
        cout << " OK" << endl << flush;
    }else
    	cout << " ERROR" << endl << flush;
    
    cout << endl;
    
    TestSuite test;
    
    test.expectEqual(lista.longitud() , 971498, "longitud");
    
    cout << endl;
    
    int frecuenciaCodon;
    auto start = chrono::high_resolution_clock::now();
    frecuenciaCodon=lista.frecuenciaCodon("ACT");
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);   
    test.expectEqual( frecuenciaCodon, 76251, "frecuenciaCodon ACT");
    cout << "Duración (<100 microsegundos): " << duration.count() << " microsegundos ";
    if(duration.count() < 100)
    	cout << "OK";
    else
    	cout << "Demasiado lento";
    cout << endl;
    
    
    cout << endl;

    int frecuenciaCadena;    
    CadenaADN cadPrueba;
    cadPrueba.setSecuencia(string("ACGCTATGTTGCCAT"));
    start = chrono::high_resolution_clock::now();
    frecuenciaCadena=lista.frecuenciaCadena(cadPrueba);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);   
    test.expectEqual( frecuenciaCadena, 3, "frecuenciaCadena ACGCTATGTTGCCAT");
    cout << "Duración (<100 microsegundos): " << duration.count() << " microsegundos ";
    if(duration.count() < 100)
    	cout << "OK";
    else
    	cout << "Demasiado lento";
    cout << endl;
    
    cout << endl;
    
    string listaCodones;
    start = chrono::high_resolution_clock::now();
    listaCodones=lista.listaCodones();
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);   
    test.expectEqual( listaCodones, string("AAA\nAAC\nAAG\nAAT\nACA\nACC\nACG\nACT\nAGA\nAGC\nAGG\nAGT\nATA\nATC\nATG\nATT\nCAA\nCAC\nCAG\nCAT\nCCA\nCCC\nCCG\nCCT\nCGA\nCGC\nCGG\nCGT\nCTA\nCTC\nCTG\nCTT\nGAA\nGAC\nGAG\nGAT\nGCA\nGCC\nGCG\nGCT\nGGA\nGGC\nGGG\nGGT\nGTA\nGTC\nGTG\nGTT\nTAA\nTAC\nTAG\nTAT\nTCA\nTCC\nTCG\nTCT\nTGA\nTGC\nTGG\nTGT\nTTA\nTTC\nTTG\nTTT"), "listaCodones");
    cout << "Duración (<200 microsegundos): " << duration.count() << " microsegundos ";
    if(duration.count() < 200)
    	cout << "OK";
    else
    	cout << "Demasiado lento";
    cout << endl;
    
    cout << endl;
    
    string listaCadenas;
    start = chrono::high_resolution_clock::now();
    listaCadenas=lista.listaCadenasADN();
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);   
    test.expectEqual( listaCadenas.substr(0,15),string("AAAAAAAAAAGCTGC"), "listaCadenasADN");
    test.expectEqual( listaCadenas.size(), (long unsigned int) 15504943, "listaCadenasADN size");
    cout << "Duración (<500000 microsegundos): " << duration.count() << " microsegundos ";
    if(duration.count() < 500000)
    	cout << "OK";
    else
    	cout << "Demasiado lento";
    cout << endl;
 
    cout << endl;
    
    string listaCadenasCodon;
    start = chrono::high_resolution_clock::now();
    listaCadenasCodon=lista.listaCadenasConCodon("ACT");
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);   
    test.expectEqual( listaCadenasCodon.substr(0,15),string("AAAAAAACACCTACT"), "listaCadenasConCodon");
    test.expectEqual( listaCadenasCodon.size(), (long unsigned int) 1179615, "listaCadenasConCodon size");
    cout << "Duración (<50000 microsegundos): " << duration.count() << " microsegundos ";
    if(duration.count() < 50000)
    	cout << "OK";
    else
    	cout << "Demasiado lento";
    cout << endl;
    
    



    return 0;
}
