#include <iostream>
#include <fstream>

using namespace std;

const int MAX_SIZE = 100;

struct Node {
    int data;
    Node* next;
};

void insert(Node** table, int size, int value) {
    int index = value % size;
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;

    if (table[index] == nullptr) {
        table[index] = newNode;
    } else {
        Node* curr = table[index];
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
}

void printTable(Node** table, int size) {
    for (int i = 0; i < size; i++) {
        cout << "Index " << i << ": ";
        Node* curr = table[i];
        while (curr != nullptr) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }
}

int main() {
    ifstream inputFile("entrada.txt");
    if (!inputFile) {
        cout << "Erro ao abrir o arquivo de entrada." << endl;
        return 1;
    }

    int size;
    inputFile >> size;
    if (size <= 0 || size > MAX_SIZE) {
        cout << "Tamanho inválido para a tabela." << endl;
        return 1;
    }

    Node* table[MAX_SIZE];
    for (int i = 0; i < size; i++) {
        table[i] = nullptr;
    }

    int value;
    while (inputFile >> value) {
        insert(table, size, value);
    }

    printTable(table, size);

    inputFile.close();

    return 0;
}