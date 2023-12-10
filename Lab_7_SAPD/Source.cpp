#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdexcept>

class Record 
{
public:
    int key;
    int index;
    std::string product;

    Record(int key, int index, const std::string& product) : key(key), index(index), product(product) {}

    bool operator<(const Record& r) const 
    {
        return key < r.key;
    }
};

class IndexFile 
{
private:
    std::vector<Record> records;

public:
    IndexFile(const std::string& filename) 
    {
        std::ifstream file(filename);
        if (!file.is_open()) 
            throw std::runtime_error("Не удалось открыть файл");
        
        int key;
        std::string product;
        int index = 0;
        while (file >> key >> product) 
        {
            if (index % 10 == 0) 
                records.push_back(Record(key, index, product));
            
            index++;
        }
        std::sort(records.begin(), records.end());
    }

    Record search(int key) 
    {
        int left = 0;
        int right = records.size() - 1;
        while (left <= right) 
        {
            int mid = left + (right - left) / 2;

            if (records[mid].key == key) 
                return records[mid];
            if (records[mid].key < key) 
                left = mid + 1;
            else 
                right = mid - 1;
            
        }
        throw std::runtime_error("Запись с ключевым полем " +  std::to_string(key) + " не найдена");
    }
};

int main() 
{
    system("chcp 1251");
    try 
    {
        IndexFile indexFile("records.txt");
        int searchKey;
        std::cout << "Введите ключевое поле для поиска: ";
        std::cin >> searchKey;
        Record record = indexFile.search(searchKey);
        std::cout << "Запись с ключевым полем " << searchKey << " найдена на позиции " << record.index << ". Продукт: " << record.product << std::endl;
    }
    catch (const std::exception& e) 
    {
        std::cerr << "Произошла ошибка: " << e.what() << std::endl;
    }
    return 0;
}
