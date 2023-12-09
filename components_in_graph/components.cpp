#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>

std::vector<std::vector<int>> createGraph(std::vector<std::vector<int>>& edges, int size) {
	std::vector<std::vector<int>> graph(size + 1);
	for (auto& edge : edges) {
		graph[edge[0]].emplace_back(edge[1]);
		graph[edge[1]].emplace_back(edge[0]);
	}

	return graph;
}

std::unordered_set<int> dfs(std::vector<std::vector<int>>& graph, int start) {
	std::unordered_set<int> visited;
	std::stack<int> nodesS;
	nodesS.push(start);
	while (!nodesS.empty()) {
		auto current = nodesS.top();
		nodesS.pop();
		visited.insert(current);
		for (auto neighbor : graph[current]) {
			if (visited.find(neighbor) == visited.end()) {
				nodesS.push(neighbor);
			}
		}
	}

	return visited;
}

std::vector<int> componentsInGraph(std::vector<std::vector<int>>& edges, int n) {
	std::vector<int> result(2);
	auto graph = createGraph(edges, 2*n);
	int max_size = 2;
	int min_size = INT32_MAX;
	std::unordered_set<int> allVisited;
	for (int i = 1; i < 2 * n; ++i) {
		if (allVisited.find(i) != allVisited.end()) {
			continue;
		}
		auto component = dfs(graph, i);
		allVisited.insert(component.begin(), component.end());
		if (component.size() > max_size) {
			max_size = component.size();
		}
		if (component.size() < min_size && component.size() != 1) {
			min_size = component.size();
		}
	}

	return { min_size, max_size };
}

int main() {
	int n;
	std::cin >> n;
	std::vector<std::vector<int>> edges(n);
	for (int i = 0; i < n; ++i) {
		int u, v;
		std::cin >> u >> v;
		edges[i] = { u, v };
	}

	auto result = componentsInGraph(edges, n);
	std::cout << result[0] << " " << result[1] << "\n";
	return 0;
}
