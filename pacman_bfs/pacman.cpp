#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
using namespace std;


struct Point {
    int r;
    int c;

    Point() = default;
    Point(int r, int c) : r(r), c(c){}
    Point UP() {return Point(this->r - 1, this->c);}
    Point LEFT() {return Point(this->r, this->c - 1);}
    Point RIGHT() {return Point(this->r, this->c + 1);}
    Point DOWN() {return Point(this->r + 1, this->c);}
    bool operator==(const Point& p1) const{
        return p1.r == r && p1.c == c;
    }
};

template<> struct std::hash<Point>{
    std::size_t operator()(const Point& p) const{
        std::hash<int> hasher;
        return hasher(p.r) ^ hasher(p.c);
    }
};

void nextMove( int r, int c, int pacman_r, int pacman_c, int food_r, int food_c,
         std::vector<std::string> grid){
    std::queue<std::vector<Point>> pathsQ;
    std::vector<Point> start = {Point(pacman_r, pacman_c)};
    pathsQ.emplace(start);
    std::unordered_set<Point> visited;
    std::vector<Point> all;
    all.emplace_back(pacman_r, pacman_c);
    std::vector<Point> resultPath;
    while(!pathsQ.empty()) {
        auto singlePath = pathsQ.front();
        pathsQ.pop();
        auto lastPoint = singlePath.back();
        auto nextPoint = lastPoint.UP();
        if (grid[nextPoint.r][nextPoint.c] == '-' && visited.insert(nextPoint).second) {
            std::vector<Point> newPath(singlePath);
            newPath.push_back(nextPoint);
            pathsQ.push(newPath);
            all.push_back(nextPoint);
        }
        if (grid[nextPoint.r][nextPoint.c] == '.') {
            if (resultPath.empty()) {
                singlePath.push_back(nextPoint);
                resultPath = singlePath;
                all.push_back(nextPoint);
            }
            break;
        }
        nextPoint = lastPoint.LEFT();
        if (grid[nextPoint.r][nextPoint.c] == '-' && visited.insert(nextPoint).second) {
            std::vector<Point> newPath(singlePath);
            newPath.push_back(nextPoint);
            pathsQ.push(newPath);
            all.push_back(nextPoint);
        }
        if (grid[nextPoint.r][nextPoint.c] == '.') {
            if (resultPath.empty()) {
                singlePath.push_back(nextPoint);
                resultPath = singlePath;
                all.push_back(nextPoint);
            }
            break;
        }
        nextPoint = lastPoint.RIGHT();
        if (grid[nextPoint.r][nextPoint.c] == '-' && visited.insert(nextPoint).second) {
            std::vector<Point> newPath(singlePath);
            newPath.push_back(nextPoint);
            pathsQ.push(newPath);
            all.push_back(nextPoint);
        }
        if (grid[nextPoint.r][nextPoint.c] == '.') {
            if (resultPath.empty()) {
                singlePath.push_back(nextPoint);
                resultPath = singlePath;
                all.push_back(nextPoint);
            }
            break;
        }
        nextPoint = lastPoint.DOWN();
        if (grid[nextPoint.r][nextPoint.c] == '-' && visited.insert(nextPoint).second) {
            std::vector<Point> newPath(singlePath);
            newPath.push_back(nextPoint);
            pathsQ.push(newPath);
            all.push_back(nextPoint);
        }
        if (grid[nextPoint.r][nextPoint.c] == '.') {
            if (resultPath.empty()) {
                singlePath.push_back(nextPoint);
                resultPath = singlePath;
                all.push_back(nextPoint);
            }
            break;
        }
    }

    std::cout << all.size() << "\n";
    for (auto elem : all) {
        std::cout << elem.r << " " << elem.c << "\n";
    }
    std::cout << resultPath.size()-1 << "\n";
    for (auto elem : resultPath) {
        std::cout << elem.r << " " << elem.c << "\n";
    }
}

int main(void) {

    int r,c, pacman_r, pacman_c, food_r, food_c;
    
    cin >> pacman_r >> pacman_c;
    cin >> food_r >> food_c;
    cin >> r >> c;
    vector <string> grid;

    for(int i=0; i<r; i++) {
        string s; cin >> s;
        grid.push_back(s);
    }

    nextMove( r, c, pacman_r, pacman_c, food_r, food_c, grid);

    return 0;
}
