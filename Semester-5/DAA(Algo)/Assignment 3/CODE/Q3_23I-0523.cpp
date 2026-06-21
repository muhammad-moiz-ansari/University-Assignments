#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

vector<int> shifts;
vector<int> pind;

void toLowercase(string& str)
{
    for (int i = 0; i < str.length(); ++i)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 'a' - 'A';
    }
}

void printResultString(const string& T, const vector<string>& p)
{
    int ind = 0;
    bool b;
    for (int i = 0; i < T.length(); ++i)
    {
        if (ind < shifts.size() && i == shifts[ind])
        {
            ind++;
            cout << "\033[31m";
            int j;
            b = false;
            for (j = i; j < i + p[pind[ind - 1]].length(); ++j)
            {
                if (ind < shifts.size() && j == shifts[ind])
                {
                    --j;
                    b = true;
                    break;
                }
                cout << T[j];
            }
            if (!b)
                i = j - 1;
            cout << "\033[0m";
        }
        else
            cout << T[i];
    }
    cout << endl;
}

// AHO-CORASICK Node
struct TrieNode
{
    unordered_map<char, TrieNode*> children;
    TrieNode* failure;      // Failure link
    vector<int> output;     // Pattern IDs ending at this node
    bool isWildcard;

    // Constructor
    TrieNode(bool wildcard = false)
    {
        failure = NULL;
        isWildcard = wildcard;
    }
};

// AHO-CORASICK Class
class AhoCorasick {
private:
    TrieNode* root;
    vector<string> patterns;

public:
    // Constructor
    AhoCorasick(const vector<string>& ptrns)
    {
        patterns = ptrns;
        for (int i = 0; i < patterns.size(); ++i)
            toLowercase(patterns[i]);
        root = new TrieNode();
    }

    // Get root
    TrieNode* getRoot()
    {
        return root;
    }

    // Building trie
    void buildTrie()
    {
        TrieNode* current = NULL;
        bool isWildcard = false;
        for (int i = 0; i < patterns.size(); ++i)   // for each pattern
        {
            current = root;
            for (int j = 0; j < patterns[i].size(); ++j) // for each character
            {
                isWildcard = false;
                char ch = patterns[i][j];
                if (ch == '?')
                    isWildcard = true;
                
                if (current->children.find(ch) == current->children.end())     // if character not found
                    current->children.insert({ ch, new TrieNode(isWildcard) });
                
                // if char already present, then no insertion
                current = current->children[ch];
            }
            current->output.push_back(i);
        }
    }

    // Building failure links
    void buildFailureLinks(TrieNode* root)
    {
        queue<TrieNode*> q;
        for (auto& [ch, child] : root->children)
        {
            child->failure = root;
            q.push(child);
        }

        while (!q.empty())
        {
            TrieNode* parent = q.front();
            q.pop();
            for (auto& [ch, child] : parent->children)
            {
                q.push(child);

                TrieNode* ptr = parent->failure;

                // Finding match
                while (ptr != root && ptr->children.find(ch) == ptr->children.end())
                    ptr = ptr->failure;

                // If match found follow
                if (ptr->children.find(ch) != ptr->children.end() && ptr->children[ch] != child)
                    child->failure = ptr->children[ch];
                else
                    child->failure = root;

                // Combine output indexes of failure link too
                for (int out : child->failure->output)
                {
                    if (find(child->output.begin(), child->output.end(), out) == child->output.end())
                        child->output.push_back(out);
                }
            }
        }
    }

    void initializeTree()
    {
        buildTrie();
        buildFailureLinks(root);
    }

    // Searching for all patterns in text
    void search(const string& text)
    {
        string lowertext = text;
        toLowercase(lowertext);

        TrieNode* current = root;
        for (int i = 0; i < lowertext.length(); ++i)
        {
            char ch = lowertext[i];

            // If char found
            if (current->children.find(ch) != current->children.end())
            {
                current = current->children[ch];
            }
            else    // if char not found
            {
                // Char/wildcard not found or current is not root
                while (current->children.find(ch) == current->children.end() && current->children.find('?') == current->children.end() && current != root)
                {
                    current = current->failure;
                }
                if (current->children.find(ch) != current->children.end())
                    current = current->children[ch];
                else if (current->children.find('?') != current->children.end())
                    current = current->children['?'];  // If wildcard found
            }
            if (!current->output.empty())
            {
                for (int out : current->output)
                {
                    //cout << "Output at current: " << out << endl;
                    cout << "Pattern \"" << patterns[out] << "\" found at shift " << i - patterns[out].length() + 1 << endl;
                    shifts.push_back(i - patterns[out].length() + 1);
                    pind.push_back(out);
                }
            }
        }
    }

    // Clean tree memory
    void deleteTrie(TrieNode* node)
    {
        if (node == NULL)
            return;

        for (auto& entry : node->children)
            deleteTrie(entry.second);

        delete node;
    }

    // Destructor
    ~AhoCorasick()
    {
        deleteTrie(root);
    }
};

int main() 
{
    int testno = 1;
    int k;
    bool takeInput = false;

    string text;
    vector<string> patterns;

    if (!takeInput)
    {
        if (testno == 1)
        {
            text = "She sells SEASHELLS by the seashore. HIS sister says SHE has Hershey's";
            patterns = {
                "she",      
                "sea",       
                "shells",   
                "HIS",      
                "hers",     
                "he",       
                "sh?",      // Wildcard
                "h?s",      // Wildcard
                "s?a"       // Wildcard
            };
        }
        else if (testno == 2)
        {
            text = "She has HIS seashells";
            patterns = {
                "she",
                "he",
                "his",
                "sea",
                "?h"   // Wildcard
            };
        }
    }
    else 
    {
        // Input
        string temp;
        cout << "Enter the text: ";
        getline(cin, text);
        cout << "Enter number of patterns: ";
        cin >> k;
        cout << "Enter the patterns: \n";
        for (int i = 0; i < k; ++i)
        {
            cout << "Pattern " << i << ": ";
            getline(cin, temp);
            patterns.push_back(temp);
        };
    }

    AhoCorasick matcher(patterns);
    matcher.initializeTree();

    cout << "---------- MULTI STRING MATCHER ----------\n\n"
        << "Text: " << text << endl
        << "Patterns: \n";
    for (int i = 0; i < patterns.size(); ++i)
    {
        cout << i + 1 << ". " << patterns[i] << endl;
    }
    cout << "Finding string patterns...\n\n"
        << "=== String Finding Results ===\n\n";
    
    matcher.search(text);

    //cout << "\nResult String: ";
    //printResultString(text, patterns);

    return 0;
}
