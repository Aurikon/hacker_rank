#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'shortestReach' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY edges
 *  3. INTEGER s
 */

int getShortestDistanceNode(std::vector<int>& distances, std::unordered_set<int>& considered) {
    int min = INT32_MAX;
    int min_node = -1;
    for (int i = 0; i < distances.size(); ++i) {
        if (considered.find(i) != considered.end()) {
            continue;
        }
        if (distances[i] < min) {
            min = distances[i];
            min_node = i;
        }
    }
    return min_node;
}

std::vector<std::vector<std::pair<int, int>>> 
                                    createGraph(std::vector<std::vector<int>>& edges, int n) {
    std::vector<std::vector<std::pair<int, int>>> graph(n+1);
    for (auto& edge : edges) {
        graph[edge[0]].emplace_back(edge[1], edge[2]);
        graph[edge[1]].emplace_back(edge[0], edge[2]);
    }

    return graph;
}

vector<int> shortestReach(int n, vector<vector<int>> edges, int s) {
    auto graph = createGraph(edges, n);
    std::queue<int> nodesQ;
    nodesQ.push(s);
    std::vector<int> distances(n+1, INT32_MAX);
    distances[s] = 0;
    std::unordered_set<int> considered;
    while(!nodesQ.empty()) {
        auto u = nodesQ.front();
        nodesQ.pop();
        considered.insert(u);
        for (auto &v : graph[u]) {
            if (distances[v.first] > distances[u]+v.second) {
                distances[v.first] = distances[u]+v.second;
            }
        }
        int nextNode = getShortestDistanceNode(distances, considered);
        if (nextNode != -1) {
            nodesQ.push(nextNode);
        }
    }

    for (auto& elem : distances) {
        if (elem == INT32_MAX) {
            elem = -1;
        }
    }
    distances.erase(distances.begin() + s);
    distances.erase(distances.begin());

    return distances;
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        vector<vector<int>> edges(m);

        for (int i = 0; i < m; i++) {
            edges[i].resize(3);

            string edges_row_temp_temp;
            getline(cin, edges_row_temp_temp);

            vector<string> edges_row_temp = split(rtrim(edges_row_temp_temp));

            for (int j = 0; j < 3; j++) {
                int edges_row_item = stoi(edges_row_temp[j]);

                edges[i][j] = edges_row_item;
            }
        }

        string s_temp;
        getline(cin, s_temp);

        int s = stoi(ltrim(rtrim(s_temp)));

        vector<int> result = shortestReach(n, edges, s);

        for (size_t i = 0; i < result.size(); i++) {
            fout << result[i];

            if (i != result.size() - 1) {
                fout << " ";
            }
        }

        fout << "\n";
    }

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}

