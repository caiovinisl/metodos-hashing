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
        table.resize(size, -1);  // Inicializa a tabela com -1 em todas as posições
    }

    int hash(int key) {
        return key % size;  // Função de hash simples usando o operador de resto (%)
    }

    int probe(int key, int i) {
        return (hash(key) + i) % size;  // Técnica de linear probing para resolução de colisões
    }

    void insert(int key) {
        int i = 0;
        int index = hash(key);

        while (table[index] != -1) {
            index = probe(key, ++i);  // Encontra a próxima posição disponível usando linear probing
        }

        table[index] = key;
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
    ifstream inputFile("entrada.txt");

    if (!inputFile.is_open()) {
        cout << "Erro ao abrir o arquivo de entrada." << endl;
        return 0;
    }

    int m;
    inputFile >> m;

    HashTable hashtable(m);

    int value;
    while (inputFile >> value) {
        hashtable.insert(value);
    }

    inputFile.close();

    hashtable.display();

    return 0;
}
