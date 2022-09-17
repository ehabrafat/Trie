#include <iostream>
#include <vector>
using namespace std;

const int ASCII_LEN = 256;
struct Node {
	vector<Node*> child;
	int count;
	bool end;
	Node() : child(ASCII_LEN), count{0}, end{ false } {}
};


class Trie {
	Node* root;
	bool _remove(Node*& root, const string& word, int idx) {
		if (idx == word.size()) {
			if (!root->end) return false;
			root->end = false;
			if (root->count == 0) {
				delete root;
				root = nullptr;
			}
			return true;
		}
		char d = word[idx];
		if (!root->child[d]) return false;
		if (_remove(root->child[d], word, idx + 1)) {
			--root->count;
			if (root->count == 0)
			{
				delete root;
				root = nullptr;
			}
			return true;
		}
		return false;
	}
	void _autoComplete(Node* root, vector<string>& res, string& cur) {
		if (root->end)
		{
			res.push_back(cur);
		}
		for (int i = 0; i < ASCII_LEN; ++i) {
			if (!root->child[i]) continue;
			cur.push_back(i);
			_autoComplete(root->child[i], res, cur);
			cur.pop_back();
		}
	}

public:
	Trie() :root{ new Node() } {}
	bool insert(const string& word) {
		Node* temp = root;
		for (char d : word) {
			if (!temp->child[d]) {
				temp->child[d] = new Node();	
				++temp->count;
			}
			temp = temp->child[d];
		}
		if (!temp->end)
		{
			temp->end = true;
			return true;
		}
		return false;
	}
	bool remove(const string& word) {
		if (word.empty()) return false;
		bool ans = _remove(root, word, 0);
		if (!root) root = new Node();
		return ans;
	}
	bool find(const string& word) {
		Node* temp = root;
		for (char d : word) {
			if (!temp->child[d]) return false;
			temp = temp->child[d];
		}
		return temp->end;
	}
	vector<string> autoComplete(const string& prefix) {
		Node* temp = root;
		for (char d : prefix) {
			if (!temp->child[d]) return {};
			temp = temp->child[d];
		}
		vector<string> res{};
		string cur = prefix;
		_autoComplete(temp, res, cur);
		return res;
	}
};


int main() {
	Trie tree;
	tree.insert("Google");
	tree.insert("Gool");
	tree.insert("Go");
	tree.insert("Golf");
	tree.insert("Grow");
	for (const string& word : tree.autoComplete("Goo"))
		cout << word << '\n';  // Google, Gool
}
