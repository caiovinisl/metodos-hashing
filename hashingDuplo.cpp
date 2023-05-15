#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Função de hashing
int hashFunction(int key, int size)
{
    return key % size;
}

// Função de probing usando duplo hashing
int doubleHashing(int key, int i, int size)
{
    int h1 = hashFunction(key, size);
    int h2 = 1 + (key % (size - 1));
    return (h1 + i * h2) % size;
}

// Inserção na tabela hash
void insert(vector<int>& hashTable, int key, int size)
{
    int index = hashFunction(key, size);

    // Verificar se o índice está ocupado
    if (hashTable[index] != -1)
    {
        // Probing até encontrar uma posição vazia
        int i = 1;
        while (hashTable[doubleHashing(key, i, size)] != -1)
            i++;
        index = doubleHashing(key, i, size);
    }

    // Inserir o valor na tabela
    hashTable[index] = key;
}

// Imprimir a tabela hash
void printHashTable(const vector<int>& hashTable, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (hashTable[i] != -1)
            cout << "Index " << i << ": " << hashTable[i] << endl;
    }
}

int main()
{
    // Abrir o arquivo de entrada
    ifstream inputFile("entrada.txt");
    if (!inputFile)
    {
        cout << "Erro ao abrir o arquivo de entrada." << endl;
        return 1;
    }

    int size;
    inputFile >> size;  // Tamanho da tabela hash

    // Inicializar a tabela hash com -1 para indicar posições vazias
    vector<int> hashTable(size, -1);

    int key;
    while (inputFile >> key)
    {
        // Inserir valores na tabela hash
        insert(hashTable, key, size);
    }

    // Imprimir a tabela hash
    printHashTable(hashTable, size);

    // Fechar o arquivo de entrada
    inputFile.close();

    return 0;
}
