#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>

std::unordered_map<char, std::string> codes;

struct Node {
    int frequency;
    char symbol;
    std::string str = "";
    Node* left, * right;
    Node(Node &first, Node &second) : frequency(first.frequency + second.frequency),
                                      left(&first), right(&second), symbol('&'), str("") {};
    Node(int freq, char ch) : frequency(freq), symbol(ch),
                              left(nullptr), right(nullptr) {};
};


bool operator<(const Node& first, const Node& second) {
    return first.frequency > second.frequency;
}


void encode_tree(Node* node) {
    if (!node)
        return;
    if (node->left == nullptr && node->right == nullptr) {
        codes[node->symbol] = node->str;
        return;
    }
    else {
        node->left->str = node->str;
        node->right->str = node->str;
        if (node->left) {
            node->left->str.push_back('0');
            encode_tree(node->left);
        }
        if (node->right) {
            node->right->str.push_back('1');
            encode_tree(node->right);
        }
    }
}

int main() {
    int k, size = 0;
    std::string s, code;
    std::cin >> s;
    if (s.size() > 1) {
        std::unordered_map<char, int> frequencies;
        for (size_t i = 0; i < s.size(); i++) {
            if (frequencies.count(s[i]) == 0) {
                frequencies.emplace(s[i], 1);
            }
            else
                frequencies[s[i]]++;
        }
        k = frequencies.size();
        if (k > 1) {
            std::priority_queue<Node> priorityQueue;
            for (const auto& pair : frequencies)
                priorityQueue.push(Node(pair.second, pair.first));

            while (priorityQueue.size() != 1) {
                Node* first = new Node(0, '!');
                *first = priorityQueue.top();
                priorityQueue.pop();
                Node* second = new Node(0, '!');
                *second = priorityQueue.top();
                priorityQueue.pop();
                priorityQueue.push(Node(*first, *second));
            }

            Node result = priorityQueue.top();
            encode_tree(&result);

            for (auto ch : frequencies)
                size += codes[ch.first].size() * ch.second;

            std::cout << k << " " << size << "\n";
            for (auto pairs : codes)
                std::cout << pairs.first << ": " << pairs.second << '\n';

            for (auto chars : s)
                code += codes[chars];

            std::cout << code;
        }
        else {
            std::cout << 1 << " " << s.size() << '\n' << s[0] << ": " << 0 << '\n';
            for (size_t i = 0; i < s.size(); i++)
                std::cout << 0;
        }
    }
    else
        std::cout << 1 << ' ' << 1 << '\n' << s << ": " << 0 << '\n' << 0;
    return 0;
}