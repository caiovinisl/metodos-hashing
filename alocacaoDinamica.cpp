#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <filesystem>

using namespace std;

namespace fs = std::filesystem;

const int MAX_SIZE = 1000;

struct Node {
    int data;
    Node* next;
};

int insert(Node** table, int size, int value) {
    int i = 1;
    int index = value % size;
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;

    if (table[index] == nullptr) {
        table[index] = newNode;
    } else {
        Node* curr = table[index];
        while (curr->next != nullptr) {
            i++;
            curr = curr->next;
        }
        i++;
        curr->next = newNode;
    }
    return i;
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

std::string getRandomFile(const std::string& directory) {
    std::vector<std::string> fileNames;
    
    // Percorre todos os arquivos do diretório
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            std::string fileName = entry.path().filename().string();
            
            // Verifica se o formato do nome do arquivo está correto
            if (fileName.length() >= 13 && fileName.substr(fileName.length() - 10) == "-input.txt") {
                fileNames.push_back(fileName);
            }
        }
    }
    
    // Verifica se existem arquivos que seguem o formato especificado
    if (fileNames.empty()) {
        std::cout << "Nenhum arquivo válido encontrado no diretório." << std::endl;
        return "";
    }
    
    // Gera um índice aleatório para selecionar um arquivo
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(0, fileNames.size() - 1);
    int randomIndex = uni(rng);
    
    // Retorna o nome do arquivo selecionado
    return fileNames[randomIndex];
}

bool isFileEmpty(const std::string& filePath) {
    std::ifstream file(filePath);
    return file.peek() == std::ifstream::traits_type::eof();
}

int countElements(Node** table, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        Node* curr = table[i];
        while (curr != nullptr) {
            count++;
            curr = curr->next;
        }
    }
    return count;
}

float calculateLoadFactor(int numElements, int size) {
    return static_cast<float>(numElements) / size;
}

double calculateMedianEntries(int entries, int numElem){
    return static_cast<double>(entries) / numElem;
}

int main() {
    std::string directory = "entradas";
    std::string inputFile = "entrada.txt";

    // Verifica se o arquivo "entrada.txt" está vazio
    if (isFileEmpty(inputFile)) {
        std::string randomFile = getRandomFile(directory);
        if (randomFile.empty()) {
            std::cout << "Nenhum arquivo válido encontrado no diretório." << std::endl;
            return 1;
        }

        inputFile = directory + "/" + randomFile;
    }

    ifstream inFile(inputFile);
    if (!inFile.is_open()) {
        cout << "Erro ao abrir o arquivo de entrada: " << inputFile << endl;
        return 1;
    }

    std::cout << "Arquivo selecionado: " << inputFile << std::endl;

    int size;
    inFile >> size;
    cout << "Tamanho da tabela: " << size << endl;
    if (size <= 0 || size > MAX_SIZE) {
        cout << "Tamanho inválido para a tabela." << endl;
        inFile.close();
        return 1;
    }

    Node* table[MAX_SIZE];
    for (int i = 0; i < size; i++) {
        table[i] = nullptr;
    }

    int value;
    int entries;
    while (inFile >> value) {
        entries += insert(table, size, value);
    }

    cout << "Tabela Hash:" << endl;
    printTable(table, size);
    
    int numElements = countElements(table, size);
    float loadFactor = calculateLoadFactor(numElements, size);
    double medianEntries = calculateMedianEntries(entries, numElements);
    cout << "Fator de carga: " << loadFactor << endl;

    cout << "Média de acessos: " << medianEntries << endl;
    
    inFile.close();

    return 0;
}
