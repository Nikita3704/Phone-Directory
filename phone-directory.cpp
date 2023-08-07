#include <iostream>
#include <vector>
using namespace std;

class TrieNode {
public:
    char data;
    TrieNode* child[26];
    bool isterminal;

    TrieNode(char d) {
        data = d;

        for (int i = 0; i < 26; i++)
            child[i] = NULL;

        isterminal = false;
    }
};

class Trie {
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode('\0');
    }

    void insertUtil(TrieNode* root, string word) {
        // base case
        if (word.length() == 0) {
            root->isterminal = true;
            return;
        }

        // assuming that word is in all lowercase
        int index = word[0] - 'a';
        TrieNode* newCharNode;

        // character already present
        if (root->child[index] != NULL) {
            newCharNode = root->child[index];
        }
        else {
            newCharNode = new TrieNode(word[0]);
            root->child[index] = newCharNode;
        }

        // recursion call
        insertUtil(newCharNode, word.substr(1)); // word.substr(1) gives sub-string from index 1 to the last index
    }

    void insert(string word) {
        insertUtil(root, word);
    }

    void printsuggestion(TrieNode* curr, vector<string>& temp, string prefix) {
        if (curr->isterminal) {
            temp.push_back(prefix);
        }

        for (char ch = 'a'; ch <= 'z'; ch++) {
            TrieNode* next = curr->child[ch - 'a'];

            if (next != NULL) {
                prefix.push_back(ch);
                printsuggestion(next, temp, prefix);
                prefix.pop_back();
            }
        }
    }

    vector<vector<string>> getsuggestion(string str) {
        TrieNode* prev = root;
        vector<vector<string>> output;
        string prefix = "";

        for (int i = 0; i < str.length(); i++) {
            char lastchar = str[i];

            prefix.push_back(lastchar);
            TrieNode* curr = prev->child[lastchar - 'a'];

            if (curr == NULL)
                break;

            vector<string> temp;
            printsuggestion(curr, temp, prefix);

            output.push_back(temp);
            temp.clear();

            prev = curr;
        }
        return output;
    }
};

vector<vector<string>> phoneDirectory(vector<string>& contactList, string& queryStr) {
    Trie* t = new Trie();
    for (auto it : contactList)
        t->insert(it);

    return t->getsuggestion(queryStr);
}

int main() {
    vector<string> contactList = { "john", "jane", "jack", "jill", "jordan", "james", "jerry" };
    string queryStr = "ja";

    vector<vector<string>> suggestions = phoneDirectory(contactList, queryStr);

    for (const auto& suggestion : suggestions) {
        for (const auto& name : suggestion) {
            cout << name << " ";
        }
        cout << endl;
    }

    return 0;
}