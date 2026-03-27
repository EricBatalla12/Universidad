/* Prueba:
    - Borrar (TComplejo) en una lista TListaCom
*/

#include <iostream>
<<<<<<< HEAD
#include "tlistacom.h"
#include "tcomplejo.h"

using namespace std;

int main() {
    cout << "=== TEST DE ESTRÉS: OPERADORES SUMA Y RESTA ===" << endl << endl;

    TComplejo c1(1, 1), c2(2, 2), c3(3, 3), c4(4, 4), c5(5, 5);
    
    // --- 1. OPERADOR SUMA (+) AL LÍMITE ---
    cout << "--- 1. Operador Suma (+) ---" << endl;
    
    TListaCom lVac;
    TListaCom l1; l1.InsCabeza(c1); l1.InsCabeza(c2); // {(2 2) (1 1)}
    
    // Caso A: Suma con lista vacía (izquierda y derecha)
    cout << "Suma con vacia (Der): " << (l1 + lVac) << " (Esperado: {(2 2) (1 1)})" << endl;
    cout << "Suma con vacia (Izq): " << (lVac + l1) << " (Esperado: {(2 2) (1 1)})" << endl;
    
    // Caso B: Suma de dos listas vacías
    TListaCom lVac2 = lVac + lVac;
    cout << "Vacia + Vacia: " << (lVac2.EsVacia() ? "OK (Vacia)" : "ERROR") << endl;

    // Caso C: Auto-suma (l1 = l1 + l1)
    // Esto comprueba si al copiar elementos de la misma lista hay conflictos de punteros
    TListaCom lAuto = l1 + l1;
    cout << "Auto-suma (L1+L1): " << lAuto << " (Esperado: {(2 2) (1 1) (2 2) (1 1)})" << endl;
    cout << "Longitud Auto-suma: " << lAuto.Longitud() << " (Esperado: 4)" << endl << endl;


    // --- 2. OPERADOR RESTA (-) CASOS CRÍTICOS ---
    cout << "--- 2. Operador Resta (-) ---" << endl;
    
    // Preparar L_Base: {1, 2, 3, 2, 4, 1}
    TListaCom lBase;
    lBase.InsCabeza(c1); lBase.InsCabeza(c4); lBase.InsCabeza(c2);
    lBase.InsCabeza(c3); lBase.InsCabeza(c2); lBase.InsCabeza(c1);
    
    cout << "L_Base original: " << lBase << endl;

    // Caso A: Restar elementos que NO existen
    TListaCom lInexistente; lInexistente.InsCabeza(c5);
    cout << "Restar inexistente (c5): " << (lBase - lInexistente) << " (Debe ser igual a L_Base)" << endl;

    // Caso B: Restar una lista vacía
    cout << "L_Base - Vacia: " << (lBase - lVac) << " (Debe ser igual a L_Base)" << endl;

    // Caso C: Restar a una lista vacía
    cout << "Vacia - L_Base: " << (lVac - lBase) << " (Debe ser vacia)" << endl;

    // Caso D: Restar elementos repetidos (RELEVANTE)
    // Si restamos {1, 2}, ¿borra todas las apariciones o solo la primera? 
    // (Depende de tu especificación, usualmente es una sola vez por cada elemento en la lista derecha)
    TListaCom lRestar; lRestar.InsCabeza(c2); lRestar.InsCabeza(c1); // {1, 2}
    TListaCom resD = lBase - lRestar;
    cout << "L_Base - {1, 2}: " << resD << endl;
    cout << "Longitud tras resta: " << resD.Longitud() << " (Si borra una ocurrencia: 4, si borra todas: 2)" << endl;

    // Caso E: Restar la lista a sí misma (L - L)
    TListaCom resE = lBase - lBase;
    cout << "L_Base - L_Base: " << resE << " (Esperado: {})" << endl;
    cout << "Es vacia? " << (resE.EsVacia() ? "SI" : "NO") << endl << endl;


    // --- 3. COMBINACIÓN Y MEMORIA ---
    cout << "--- 3. Combinaciones (L1 + L2) - L3 ---" << endl;
    
    TListaCom la; la.InsCabeza(c1); // {1}
    TListaCom lb; lb.InsCabeza(c2); // {2}
    TListaCom lc; lc.InsCabeza(c1); // {1}
    
    TListaCom comb = (la + lb) - lc;
    cout << "({1} + {2}) - {1} = " << comb << " (Esperado: {(2 2)})" << endl;

    // --- 4. CHEQUEO DE INDEPENDENCIA (Deep Copy) ---
    cout << "\n--- 4. Chequeo de Independencia de Memoria ---" << endl;
    TListaCom lOriginal; lOriginal.InsCabeza(c1);
    TListaCom lSuma = lOriginal + lOriginal; // {1, 1}
    
    // Modificar lOriginal no debería afectar a lSuma
    lOriginal.Borrar(c1);
    cout << "L_Original tras borrar: " << lOriginal << " (Vacia)" << endl;
    cout << "L_Suma tras modificar original: " << lSuma << " (Debe seguir siendo {(1 1) (1 1)})" << endl;

    cout << "\n=== FIN DEL TEST PROFUNDO ===" << endl;

    return 0;
}
=======

using namespace std;

#include "tlistacom.h"

int
main(void)
{
  TComplejo a, b(1), c(2, 3), d(b);
  TListaCom l1;
  
  l1.InsCabeza(a);
  l1.InsCabeza(b);
  l1.InsCabeza(c);
  l1.InsCabeza(d);
  l1.Borrar(d);
  cout<<"l1 = "<<l1<<endl;
  l1.Borrar(a);
  l1.Borrar(b);
  cout<<"l1 = "<<l1<<endl;
   
  return 0;
}
>>>>>>> 50d5663f6a544f118c6b225cf1581fd58a51cd7a
