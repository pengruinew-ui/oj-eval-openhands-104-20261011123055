#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};

vector<vector<int>> bfs(int n, int m, const vector<vector<int>>& grid, Point start) {
    vector<vector<int>> dist(m, vector<int>(n, -1));
    queue<Point> q;
    
    dist[start.x][start.y] = 0;
    q.push(start);
    
    while (!q.empty()) {
        Point curr = q.front();
        q.pop();
        
        for (int dir = 0; dir < 4; dir++) {
            int nx = curr.x + dx[dir];
            int ny = curr.y + dy[dir];
            
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && 
                grid[nx][ny] != 1 && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[curr.x][curr.y] + 1;
                q.push(Point(nx, ny));
            }
        }
    }
    
    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> grid(m, vector<int>(n));
    Point start(-1, -1), home(-1, -1);
    vector<Point> shops;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 2) {
                start = Point(i, j);
            } else if (grid[i][j] == 3) {
                home = Point(i, j);
            } else if (grid[i][j] == 4) {
                shops.push_back(Point(i, j));
            }
        }
    }
    
    // BFS from start
    vector<vector<int>> distFromStart = bfs(n, m, grid, start);
    
    // BFS from home
    vector<vector<int>> distFromHome = bfs(n, m, grid, home);
    
    int minDistance = INT_MAX;
    
    // Check each umbrella shop
    for (const Point& shop : shops) {
        if (distFromStart[shop.x][shop.y] != -1 && 
            distFromHome[shop.x][shop.y] != -1) {
            int totalDist = distFromStart[shop.x][shop.y] + distFromHome[shop.x][shop.y];
            minDistance = min(minDistance, totalDist);
        }
    }
    
    if (minDistance == INT_MAX) {
        cout << -1 << endl;
    } else {
        cout << minDistance << endl;
    }
    
    return 0;
}