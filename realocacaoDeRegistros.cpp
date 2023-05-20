#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <filesystem>

using namespace std;

namespace fs = std::filesystem;

class HashTable {
private:
    vector<int> table;
    int size;
    int numElements;

public:
    HashTable(int m) {
        size = m;
        table.resize(size, -1);  // Inicializa a tabela com -1 em todas as posições
        numElements = 0;
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
        numElements++;
    }

    void printTable() {
        for (int i = 0; i < size; i++) {
            if (table[i] != -1) {
                cout << "Index " << i << ": " << table[i] << endl;
            } else { 
                cout << "Index " << i << ": " << " " << endl;
            }
        }
    }

    double calculateLoadFactor() {
        return static_cast<double>(numElements) / size;
    }
};

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

    HashTable hashtable(size);

    int value;
    while (inFile >> value) {
        hashtable.insert(value);
    }

    cout << "Tabela Hash:" << endl;
    hashtable.printTable();

    double loadFactor = hashtable.calculateLoadFactor();
    cout << "Fator de Carga: " << loadFactor << endl;

    inFile.close();

    return 0;
}
