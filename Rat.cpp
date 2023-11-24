#include<bits/stdc++.h>
using namespace std;

bool solve_maze(vector<vector<int>>& maze, int x, int y, vector<vector<int>>& path) {
    int n = maze.size();
    if (x < 0 || y < 0 || x >= n || y >= n || maze[x][y] == 0 || path[x][y] == 1) {
        return false;
    }
    path[x][y] = 1;
    if (x == n - 1 && y == n - 1) {
        return true;
    }
    if (solve_maze(maze, x - 1, y, path)) {
        return true;
    }
    if (solve_maze(maze, x, y + 1, path)) {
        return true;
    }
    if (solve_maze(maze, x + 1, y, path)) {
        return true;
    }
    if (solve_maze(maze, x, y - 1, path)) {
        return true;
    }
    path[x][y] = 0;
    return false;
}

vector<vector<int>> generate_maze(int n) {
    vector<vector<int>> maze(n, vector<int>(n, 1));
    for (int i = 1; i < n - 1; i += 2) {
        for (int j = 1; j < n - 1; j += 2) {
            maze[i][j] = 0;
        }
    }
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    for (int i = 1; i < n - 1; i += 2) {
        for (int j = 1; j < n - 1; j += 2) {
            vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
            shuffle(directions.begin(), directions.end(), rng);
            for (auto [dx, dy] : directions) {
                int x = i + dx, y = j + dy;
                if (maze[x][y] == 1) {
                    maze[x - dx / 2][y - dy / 2] = 0;
                    maze[x][y] = 0;
                    break;
                }
            }
        }
    }
    return maze;
}

int main() {
    while(true){
        cout<<endl<<"0 to exit otherwise 1 to continue"<<endl;
        int temp; cin>>temp;
        if(temp == 0) break;
        cout<<"Enter size of maze"<<endl;
        int n; cin>>n;
        vector<vector<int>> maze = generate_maze(n);
        cout<<"The generated matrix is: "<<endl;
        for (auto row : maze) {
            for (int x : row) {
                cout << (x == 1 ? "#" : ".");
            }
           cout << endl;
        }
        vector<vector<int>> path(maze.size(), vector<int>(maze[0].size(), 0));
        if (solve_maze(maze, 0, 0, path)) {
            cout<<endl<<endl;
            cout<<"The following path found: "<<endl;
            for (auto row : path) {
                for (int x : row) {
                    cout << (x == 1 ? "#" : ".");
                }
                cout << endl;
            }
        } else {
            cout << "No solution exists." << endl;
        }
    }
    return 0;
}