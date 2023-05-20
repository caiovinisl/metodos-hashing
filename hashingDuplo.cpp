#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <filesystem>

using namespace std;

namespace fs = std::filesystem;

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
void printTable(const vector<int>& hashTable, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (hashTable[i] != -1) {
            cout << "Index " << i << ": " << hashTable[i] << endl;
        } else { 
            cout << "Index " << i << ": " << " " << endl;
        }
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
    inFile >> size;  // Tamanho da tabela hash
    cout << "Tamanho da tabela: " << size << endl;

    // Inicializar a tabela hash com -1 para indicar posições vazias
    vector<int> hashTable(size, -1);

    int key;
    int numElements = 0;  // Contador de elementos inseridos

    while (inFile >> key)
    {
        // Inserir valores na tabela hash
        insert(hashTable, key, size);
        numElements++;
    }

    cout << "Tabela Hash:" << endl;
    printTable(hashTable, size);

    double loadFactor = static_cast<double>(numElements) / size;
    cout << "Fator de Carga: " << loadFactor << endl;

    inFile.close();

    return 0;
}