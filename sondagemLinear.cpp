#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class HashTable {
private:
    vector<int> table;
    int size;
    
public:
    HashTable(int m) {
        size = m;
        table.resize(size, -1);
    }
    
    int hash(int key) {
        return key % size;
    }
    
    int probe(int key, int i) {
        return (hash(key) + i) % size;
    }
    
    void insert(int key) {
        int i = 0;
        int index;
        
        do {
            index = probe(key, i);
            if (table[index] == -1) {
                table[index] = key;
                return;
            }
            i++;
        } while (i != size);
        
        cout << "Tabela cheia, não foi possível inserir o valor: " << key << endl;
    }
    
    void display() {
        for (int i = 0; i < size; i++) {
            if (table[i] != -1) {
                cout << "Index " << i << ": " << table[i] << endl;
            }
        }
    }
};

int main() {
    int m, value;
    
    ifstream inputFile("entrada.txt");
    if (!inputFile) {
        cout << "Não foi possível abrir o arquivo." << endl;
        return 1;
    }
    
    inputFile >> m;
    HashTable hashtable(m);
    
    while (inputFile >> value) {
        hashtable.insert(value);
    }
    
    inputFile.close();
    
    cout << "Tabela Hash:" << endl;
    hashtable.display();
    
    return 0;
}