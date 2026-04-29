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

bool cargar_laberinto(const string& filename, vector<vector<int>>& maze, int& total_filas, int& total_columnas) {
    ifstream file(filename);
    
    if (!file.is_open()) {
        return false;
    }

    //Primera linea del archivo para saber total filas y columnas
    file >> total_filas >> total_columnas;

    for (int i = 0; i < total_filas; ++i) {
    
    vector<int> fila_nueva(total_columnas, 0); 
    maze.push_back(fila_nueva);
}

    for (int i = 0; i < total_filas; ++i) {
        for (int j = 0; j < total_columnas; ++j) {
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

    //Caso base si se llega al final
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

//Constante para saber qué casillas no hemos visitado aún
const int SENTINEL = -1;

int maze_memo(
    vector<vector<int>> &M,
    const vector<vector<int>> &maze, 
    int fila_actual, int columna_actual, int total_filas, int total_columnas
) {
    //Si se sale devolver infinito
    if( fila_actual >= total_filas || columna_actual >= total_columnas || maze[fila_actual][columna_actual] == 0 )
        return numeric_limits<int>::max();

    //Devolver conocida
    if( M[fila_actual][columna_actual] != SENTINEL ) 
        return M[fila_actual][columna_actual];

    //Caso base de llegar al final
    if( fila_actual == total_filas - 1 && columna_actual == total_columnas - 1 )
        return M[fila_actual][columna_actual] = 1;

    //Movimiento
    int S1 = maze_memo( M, maze, fila_actual, columna_actual + 1, total_filas, total_columnas );
    int S2 = maze_memo( M, maze, fila_actual + 1, columna_actual, total_filas, total_columnas );
    int S3 = maze_memo( M, maze, fila_actual + 1, columna_actual + 1, total_filas, total_columnas );

    int best = min({S1, S2, S3});

    //Almacén y devolver solución
    if( best == numeric_limits<int>::max() )
        return M[fila_actual][columna_actual] = numeric_limits<int>::max(); // Marcamos como camino sin salida
        
    return M[fila_actual][columna_actual] = 1 + best;
}

//Iniciar matríz
int maze_memo(const vector<vector<int>> &maze, int total_filas, int total_columnas, vector<vector<int>> &M) {
    M.assign(total_filas, vector<int>(total_columnas, SENTINEL)); 
    return maze_memo(M, maze, 0, 0, total_filas, total_columnas);
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
            //Si hay un argumento después de -f
            if (i + 1 < argc) {
                nombre_archivo = argv[++i]; //Avanzar i para guardar el nombre del fichero
                usa_f = true;
            } else {
                //Si no pones nombre archivo
                cerr << "ERROR: missing filename." << endl;
                print_usage();
                return 1;
            }
        } 
        else {
            //Si no existe la opción
            cerr << "ERROR: unknown option " << argumento << "." << endl;
            print_usage();
            return 1;
        }
    }

    //Por si falta -f
    if (!usa_f) {
        print_usage();
        return 1;
    }

    //CÁLCULO DE RESULTADOS
    int total_filas, total_columnas;
    vector<vector<int>> maze;

    //Cargar el archivo
    if (!cargar_laberinto(nombre_archivo, maze, total_filas, total_columnas)) {
        cerr << "ERROR: can't open file: " << nombre_archivo << "." << endl;
        print_usage();
        return 1;
    }
    
    if (!usa_ignore_naive) {
        int resultado_naive = maze_naive(maze, 0, 0, total_filas, total_columnas);
        
        //Si el resultado es infinito, significa que no hay salida, se imprime 0
        if (resultado_naive == numeric_limits<int>::max()) {
            cout << "0 ";
        } else {
            cout << resultado_naive << " ";
        }
    } else {
        cout << "- ";
    }

   vector<vector<int>> M;
    int resultado_memo = maze_memo(maze, total_filas, total_columnas, M);
    
    if (resultado_memo == numeric_limits<int>::max()) {
        cout << "0 ";
    } else {
        cout << resultado_memo << " ";
    }
    
    //Tareas restantes
    cout << "? ?" << endl;

    if (usa_t) {
        cout << "Memoization table:" << endl;
        for (int i = 0; i < total_filas; ++i) {
            for (int j = 0; j < total_columnas; ++j) {
                if (M[i][j] == SENTINEL) {
                    cout << "- ";
                } else if (M[i][j] == numeric_limits<int>::max()) {
                    cout << "X ";
                } else {
                    cout << M[i][j] << " ";
                }
            }
            cout << endl;
        }
    }

    return 0;
}

    