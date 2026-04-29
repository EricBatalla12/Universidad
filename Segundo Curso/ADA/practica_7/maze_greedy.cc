//Eric Batalla Ortúzar 24503990C
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int maze_greedy(const vector<vector<int>>& maze, vector<string>& out_maze) {
    int n = static_cast<int>(maze.size());
    if (n == 0) return 0;
    int m = static_cast<int>(maze[0].size());
    if (m == 0 || maze[0][0] == 0) return 0;

    int i = 0, j = 0;
    int length = 1;
    out_maze[i][j] = '*';

    while (i != n - 1 || j != m - 1) {

        if (i + 1 < n && j + 1 < m && maze[i + 1][j + 1] == 1) {
            i++; j++;
        } else if (j + 1 < m && maze[i][j + 1] == 1) {
            j++;
        } else if (i + 1 < n && maze[i + 1][j] == 1) {
            i++;
        } else {
            return 0; 
        }
        out_maze[i][j] = '*';
        length++;
    }
    return length;
}

int main(int argc, char* argv[]) {
    bool p2D = false;
    bool has_f = false;
    string filename;

    if (argc == 1) {
        cerr << "Usage:\nmaze_greedy [--p2D] -f file\n";
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "--p2D") {
            p2D = true;
        } else if (arg == "-f") {
            has_f = true;
            if (i + 1 < argc) {
                filename = argv[++i];
            } else {
                cerr << "ERROR: missing filename.\nUsage:\nmaze_greedy [--p2D] -f file\n";
                return 1;
            }
        } else {
            cerr << "ERROR: unknown option " << arg << ".\nUsage:\nmaze_greedy [--p2D] -f file\n";
            return 1;
        }
    }

    if (!has_f) {
        cerr << "Usage:\nmaze_greedy [--p2D] -f file\n";
        return 1;
    }

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "ERROR: can't open file: " << filename << ".\nUsage:\nmaze_greedy [--p2D] -f file\n";
        return 1;
    }

    int n, m;
    if (!(file >> n >> m)) return 0;

    vector<vector<int>> maze(n, vector<int>(m));
    vector<string> out_maze(n, string(m, '0'));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            file >> maze[i][j];
            out_maze[i][j] = (maze[i][j] == 1) ? '1' : '0';
        }
    }

    int path_length = maze_greedy(maze, out_maze);
    
    cout << path_length << "\n";

    if (p2D) {
        for (int i = 0; i < n; ++i) {
            cout << out_maze[i] << "\n";
        }
    }
    return 0;
}