#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

std::vector<std::string> answer;
// v = 'brown' => g['brown'] = ['deen', 'john'];
void dfs(std::string v, const std::map<std::string, std::vector<std::string>>& g,
         std::map<std::string, bool>& visited, std::vector<std::string>& ans) {
    visited[v] = true;
    if (g.find(v) != g.end()) {
        for (const auto& subname : g.find(v)->second) { // ? g[v] это же {str1, str2, str3, ...}
            if (!visited[subname])
                dfs(subname, g, visited, ans);
        }
    }
    ans.push_back(v);
    // Dean, Thomas, Evans, Morgan, John, Brown, Morris, Khalid, Nick  -->
    // Nick, Khalid, Morris, Brown, (Dean) John, Morgan, Evans, Thomas, (Dean)
}

void topological_sort(const std::map<std::string, std::vector<std::string>>& g,
                      std::map<std::string, bool>& visited, std::vector<std::string>& ans) {
    std::vector<std::string> keys;
    for (auto iterator = g.begin(); iterator != g.end(); iterator++) {
        std::string name = iterator->first;
        keys.push_back(name);
        visited[name] = false;
    }
    ans.clear();
    for (const auto& name : keys)
        if (!visited[name])
            dfs(name, g, visited, ans);
    std::reverse(ans.begin(), ans.end());
}

void reversed_max_path(const std::string& last,
                       const std::map<std::string, std::vector<std::string>>& rev_g,
                       const std::map<std::string, int>& dist,
                       std::map<std::string, bool>& rev_visited) {
    rev_visited[last] = true;
    answer.push_back(last);
    int min_dist = 1000;
    std::string new_last;
    if (rev_g.count(last) == 0)
        return;
    else {
        for (const auto& neighbour : rev_g.find(last)->second) {
            if (!rev_visited[neighbour]) {
                if (min_dist > dist.find(neighbour)->second) {
                    min_dist = dist.find(neighbour)->second;
                    new_last = neighbour;
                }
            }
            //min_dist = std::min(min_dist, dist.find(neighbour)->second);
        }
        reversed_max_path(new_last, rev_g, dist, rev_visited);
    }
}

/*std::vector<std::string>*/void find_longest_path(
        const std::map<std::string, std::vector<std::string>>& g,
        const std::map<std::string, std::vector<std::string>>& rev_g,
        const std::vector<std::string>& top_sorted,
        std::map<std::string, bool>& rev_visited
) {
    std::map<std::string, int> dist;
    std::vector<std::string> longest_path; // список строк из самой длинной цепи
    //std::string first_in = top_sorted[0];
    //longest_path.push_back(first_in);
    std::pair<int, std::string> last_in_path;
    int max_of_the_max = -1;
    for (const auto& name : top_sorted) {
        int max = -1;
        if (rev_g.count(name) == 0)
            dist[name] = 0;
        else {
            for (const auto& neighbour : rev_g.find(name)->second)
                max = std::max(dist[neighbour] + 1, max);
            dist[name] = max;
        }
        if (max > max_of_the_max) {
            last_in_path = { max, name };
            max_of_the_max = max;
        }
    }

    reversed_max_path(last_in_path.second, rev_g, dist, rev_visited);
    /*for (auto v : dist)
        std::cout << v.first << " with the distance " << v.second << std::endl;
    std::cout << last_in_path.first << " " << last_in_path.second << std::endl;*/
}


void print_final(){
    std::reverse(answer.begin(), answer.end());
    for (size_t i = 0; i < answer.size() - 1; i++){
        if (i != answer.size() - 2)
            std::cout << answer[i] << " " << answer[i+1] << ", ";
        else
            std::cout << answer[i] << " " << answer[i+1];
    }
}
/*
Morgan Evans
Brown John
Khaled Morris
Evans Thomas
Nick Brown
Brown Dean
John Morgan
 */
int main() {
    int n; // кол-во пар <имя-фамилия>(ребер)
    std::cin >> n;
    std::string name, surname;
    std::map<std::string, std::vector<std::string> > graph_str; // граф??
    std::map<std::string, std::vector<std::string> > reversed_graph;
    std::map<std::string, bool> rev_visited;
    for (int i = 0; i < n; i++) {
        std::cin >> name >> surname;
        graph_str[name].push_back(surname);
        reversed_graph[surname].push_back(name);
        rev_visited[surname] = false;
    }
    std::map<std::string, bool> visited;
    std::vector<std::string> top_sorted;
    topological_sort(graph_str, visited, top_sorted);

    //for (size_t i = 0; i < top_sorted.size(); i++)
    //    std::cout << top_sorted[i] << " ";
    //std::cout << std::endl;
    find_longest_path(graph_str, reversed_graph, top_sorted, rev_visited);
    print_final();
    //for (auto v : answer)
    //    std::cout << v << " ";
}
