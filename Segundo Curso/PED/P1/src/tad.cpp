#include <iostream>
#include "tlistacom.h"
#include "tcomplejo.h" // Asumo que se llama así

using namespace std;

int main() {
    cout << "=== INICIO DEL TEST A PRUEBA DE FUEGO ===" << endl << endl;

    // 1. INSERCIONES AL LÍMITE
    cout << "--- 1. Inserciones y Punteros ---" << endl;
    TListaCom l1;
    TComplejo c1(1, 1), c2(2, 2), c3(3, 3), c4(4, 4);
    
    l1.InsCabeza(c2); // Lista: {2}
    l1.InsertarI(c1, l1.Primera()); // Inserta c1 a la izq de c2 (Nueva cabeza). Lista: {1 2}
    l1.InsertarD(c4, l1.Ultima());  // Inserta c4 a la der de c2 (Nueva cola). Lista: {1 2 4}
    l1.InsertarI(c3, l1.Ultima());  // Inserta c3 a la izq de c4 (Medio). Lista: {1 2 3 4}
    
    cout << "L1 esperada : {(1 1) (2 2) (3 3) (4 4)}" << endl;
    cout << "L1 obtenida : " << l1 << endl;
    cout << "Longitud    : " << l1.Longitud() << " (Esperado: 4)" << endl << endl;

    // 2. CONSTRUCTORES DE COPIA Y ASIGNACIÓN (Peligro de memoria compartida)
    cout << "--- 2. Copias y Auto-asignaciones ---" << endl;
    TListaCom l2(l1); // Constructor de copia
    l2.Borrar(c4);    // Modificamos l2 para ver si l1 se ve afectada (Deep copy check)
    
    TListaCom l3;
    l3 = l1;          // Operador de asignación
    l3 = l3;          // Auto-asignación (¡Aquí muchos programas explotan!)

    cout << "L1 (Intacta): " << l1 << endl;
    cout << "L2 (- tail) : " << l2 << endl;
    cout << "L3 (Copia)  : " << l3 << endl << endl;

    // 3. BORRADOS EXTREMOS
    cout << "--- 3. Borrados y BorrarTodos ---" << endl;
    TListaCom l4;
    l4.InsCabeza(c1); l4.InsCabeza(c1); l4.InsCabeza(c2); l4.InsCabeza(c1); l4.InsCabeza(c1);
    // l4 ahora es {(1 1) (1 1) (2 2) (1 1) (1 1)} - Repetidos consecutivos en cabeza y cola
    
    cout << "L4 original : " << l4 << endl;
    l4.BorrarTodos(c1); 
    cout << "L4 sin 'c1' : " << l4 << " (Esperado: {(2 2)})" << endl;
    
    l4.Borrar(c2); // Borrar el único elemento
    cout << "L4 vacia    : " << l4 << " (Esperado: {})" << endl;
    cout << "L4 EsVacia? : " << (l4.EsVacia() ? "SI" : "NO") << endl << endl;

    // 4. BORRAR POR POSICIÓN
    cout << "--- 4. Borrado por Posicion ---" << endl;
    TListaCom l5 = l1; // {(1 1) (2 2) (3 3) (4 4)}
    TListaPos pos = l5.Primera().Siguiente(); // Apunta a (2 2)
    l5.Borrar(pos);
    cout << "L5 sin (2 2): " << l5 << " (Esperado: {(1 1) (3 3) (4 4)})" << endl;
    cout << "Pos Vacia?  : " << (pos.EsVacia() ? "SI" : "NO") << " (Debe ser SI tras borrar)" << endl << endl;

    // 5. OPERADORES SUMA Y RESTA
    cout << "--- 5. Operadores + y - ---" << endl;
    TListaCom l6, l7;
    l6.InsCabeza(c2); l6.InsCabeza(c1); // {(1 1) (2 2)}
    l7.InsCabeza(c4); l7.InsCabeza(c3); // {(3 3) (4 4)}
    
    TListaCom suma = l6 + l7;
    cout << "L6 + L7     : " << suma << " (Esperado: {(1 1) (2 2) (3 3) (4 4)})" << endl;
    
    TListaCom resta = suma - l7;
    cout << "Suma - L7   : " << resta << " (Esperado: {(1 1) (2 2)})" << endl;

    cout << "\n=== FIN DEL TEST ===" << endl;
    return 0;
}