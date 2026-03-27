//Eric Batalla Ortúzar 24503990C

#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <algorithm>
using namespace std;


void print_usage() {
    cerr << "Usage:" << endl;
    cerr << "maze [--p2D] [-t] [--ignore-naive] -f file" << endl;
}

bool cargar_laberinto(const string& filename, vector<vector<int>>& maze, int& n, int& m) {
    ifstream file(filename);
    
    // Si el archivo no se pudo abrir, devolvemos false
    if (!file.is_open()) {
        return false;
    }

    // Leemos la primera línea: número de filas (n) y columnas (m)
    file >> n >> m;

    // Redimensionamos la matriz para que tenga tamaño n x m
    maze.assign(n, vector<int>(m));

    // Leemos los 0s y 1s
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            file >> maze[i][j];
        }
    }

    file.close();
    return true;
}

int maze_naive(
    const vector<vector<int>> &maze,
    int fila_actual,                           
    int columna_actual,                           
    int total_filas,                           
    int total_columnas                         
) {
    //Caso base en caso de salirse del laberinto o no llegar a la salida
    if( fila_actual >= total_filas || columna_actual >= total_columnas || maze[fila_actual][columna_actual] == 0 )
        return numeric_limits<int>::max();

    // Caso base de éxito
    // Si llegamos a la casilla de destino (n-1, m-1)
    if( fila_actual == total_filas - 1 && columna_actual == total_columnas - 1 )
        return 1;  // Un camino de una sola casilla tiene longitud 1

    //derecha
    int S1 = maze_naive( maze, fila_actual, columna_actual + 1, total_filas, total_columnas );

    //Abajo
    int S2 = maze_naive( maze, fila_actual + 1, columna_actual, total_filas, total_columnas );

    //Diagonal
    int S3 = maze_naive( maze, fila_actual + 1, columna_actual + 1, total_filas, total_columnas );

    //Mejor camino
    int best = min({S1, S2, S3});

    //Si el mejor es infinito, el camino no tiene salida
    if( best == numeric_limits<int>::max() )
        return numeric_limits<int>::max();

    // Sumamos 1 por la casilla actual
    return 1 + best;
}

// Constante para saber qué casillas no hemos visitado aún
const int SENTINEL = -1;

// --- 2. VERSIÓN RECURSIVA CON MEMOIZACIÓN ---

int maze_memo(
    vector<vector<int>> &M,
    const vector<vector<int>> &maze, 
    int r, int c, int n, int m
) {
    // Si nos salimos del laberinto o la casilla es inaccesible (0)
    // Devolvemos "infinito" pero NO lo guardamos en la tabla (no es una celda válida)
    if( r >= n || c >= m || maze[r][c] == 0 )
        return numeric_limits<int>::max();

    // 1. Si la solución ya es conocida, retornarla (como en tu diapositiva)
    if( M[r][c] != SENTINEL ) 
        return M[r][c];

    // Caso base de éxito
    if( r == n - 1 && c == m - 1 )
        return M[r][c] = 1;

    // Llamadas recursivas (S1, S2, S3)
    int S1 = maze_memo( M, maze, r, c + 1, n, m );
    int S2 = maze_memo( M, maze, r + 1, c, n, m );
    int S3 = maze_memo( M, maze, r + 1, c + 1, n, m );

    int best = min({S1, S2, S3});

    // 2. Almacenar y retornar la solución
    if( best == numeric_limits<int>::max() )
        return M[r][c] = numeric_limits<int>::max(); // Marcamos como camino sin salida
        
    return M[r][c] = 1 + best;
}

// -----------------------------------------------------------------
// Función "envoltorio" para inicializar la matriz (como en la diapositiva)
int maze_memo(const vector<vector<int>> &maze, int n, int m, vector<vector<int>> &M) {
    // Inicializamos la matriz M con el tamaño n x m y rellena de SENTINEL (-1)
    M.assign(n, vector<int>(m, SENTINEL)); 
    return maze_memo(M, maze, 0, 0, n, m);
}

int main(int argc, char* argv[]) {
    bool usa_t, usa_p2D, usa_ignore_naive, usa_f = false;
    string nombre_archivo = "";

    //Empieza en 1 porque el primero es el nombre del programa
    for (int i = 1; i < argc; ++i) {
        string argumento = argv[i];

        if (argumento == "-t") {
            usa_t = true;
        } 
        else if (argumento == "--p2D") {
            usa_p2D = true;
        } 
        else if (argumento == "--ignore-naive") {
            usa_ignore_naive = true;
        } 
        else if (argumento == "-f") {
            // Comprobamos si hay un argumento después de -f
            if (i + 1 < argc) {
                nombre_archivo = argv[++i]; // Avanzamos 'i' para guardar el nombre del fichero
                usa_f = true;
            } else {
                // Error: se puso -f pero no se dio un nombre de archivo
                cerr << "ERROR: missing filename." << endl;
                print_usage();
                return 1;
            }
        } 
        else {
            // Error: detectada una opción que no existe (ej. -a, --hola)
            cerr << "ERROR: unknown option " << argumento << "." << endl;
            print_usage();
            return 1;
        }
    }

    // Comprobamos si faltó por completo la opción obligatoria -f
    if (!usa_f) {
        // Aunque el PDF no muestra el mensaje exacto para esto, 
        // mostrar el uso es lo correcto si no hay fichero de entrada.
        print_usage();
        return 1;
    }

    //CÁLCULO DE RESULTADOS
   int n, m;
    vector<vector<int>> maze;

    // Intentamos cargar el archivo
    if (!cargar_laberinto(nombre_archivo, maze, n, m)) {
        cerr << "ERROR: can't open file: " << nombre_archivo << "." << endl;
        print_usage();
        return 1;
    }

    // ¡Aquí ya tenemos la matriz 'maze' lista para usar!
    
    // Vamos a probar a llamar a nuestra función naive (si no han puesto --ignore-naive)
    if (!usa_ignore_naive) {
        int resultado_naive = maze_naive(maze, 0, 0, n, m);
        
        // Si el resultado es "infinito", significa que no hay salida, imprimimos 0
        if (resultado_naive == numeric_limits<int>::max()) {
            cout << "0 ";
        } else {
            cout << resultado_naive << " ";
        }
    } else {
        // Si pusieron la opción --ignore-naive, imprimimos un guion
        cout << "- ";
    }

   vector<vector<int>> M; // Creamos la matriz de memoria vacía
    int resultado_memo = maze_memo(maze, n, m, M); // Llamamos al envoltorio
    
    if (resultado_memo == numeric_limits<int>::max()) {
        cout << "0 ";
    } else {
        cout << resultado_memo << " ";
    }
    
    // Imprimimos '?' para las dos iterativas que faltan (Entrega 2)
    cout << "? ?" << endl;

    // --- IMPRESIÓN DE TABLAS (Opción -t) ---
    if (usa_t) {
        cout << "Memoization table:" << endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                // Formateamos la salida según las normas del PDF
                if (M[i][j] == SENTINEL) {
                    cout << "- ";
                } else if (M[i][j] == numeric_limits<int>::max()) {
                    cout << "X ";
                } else {
                    cout << M[i][j] << " ";
                }
            }
            cout << endl; // Salto de línea al acabar la fila
        }
        // Nota: La "Iterative table" la haremos en la Entrega 2.
    }

    return 0;
}

