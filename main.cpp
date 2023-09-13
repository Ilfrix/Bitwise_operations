#include <iostream>
#include <vector>
#include <experimental/random>
#include <ctime>
#include <fstream>

#define MAX_SIZE 1e3
#define MAX_READ 1e3

void task1();
void task2();
void task3();
void task4();
void task5();
void task6();
void task7();
void output(int);
void output_char(unsigned char);
void generate();
void sort_file();

int main() {
    task7();
    return 0;
}

void task1() {
    // int value = 0xfe85;
    int value = 0xfe35;
    output(value);
    int mask = 1 << (5 - 1);
    value |= mask;
    mask = 1 << (7 - 1);
    value |= mask;
    std::cout << '\n';
    output(value);
}

void task2() {
    int value = 0;
    std::cout << "Enter value in decimal system: ";
    std::cin >> value;
    std::cout << "You value in bin: ";
    output(value);
    std::cout << '\n';
    int mask = 0;
    for (int i = 0; i < 6; ++i) {
        mask += (1 << i);
    }
        for (int i = 10; i < 31; ++i) {
        mask += (1 << i);
    }
    
    for (int i = 7; i < 11; ++i) {
        mask = mask + (0 << i);
    }
    value &= mask;
    std::cout << "result: \t  ";
    output(value);
}

void task3() {
    int value = 0;
    std::cout << "Enter value in decimal system: ";
    std::cin >> value;
    std::cout << "You value in bin: ";
    output(value);
    std::cout << '\n';
    value <<= 4;
    std::cout << "result: \t  ";
    output(value);
    std::cout << "\nDecimal system:   " << value;
}

void task4() {
    int value = 0;
    std::cout << "Enter value in decimal system: ";
    std::cin >> value;
    std::cout << "You value in bin: ";
    output(value);
    std::cout << '\n';
    value >>= 3;
    std::cout << "result: \t  ";
    output(value);
    std::cout << "\nDecimal system:   " << value;
}

void task5() {
    int value = 0, n = 0, mask = 1;
    std::cout << "Enter value in decimal system: ";
    std::cin >> value;
    std::cout << "You value in bin: ";
    output(value);
    std::cout << "\nEnter n for move: ";
    std::cin >> n;
    value |= (mask << (n - 1));
    std::cout << "result: \t  ";
    output(value);
    std::cout << "\nDecimal system:   " << value;
}

void task6() {
    std::vector <unsigned char> storage;
    std::vector <int> values;
    std::experimental::reseed(std::time(nullptr));
    for (int i = 7; i >=0; --i) values.push_back(std::experimental::randint(0, 7));
    for (int a : values) std::cout << a << ' ';
    for (int i = 0; i < values.size(); ++i) {
        if (values[i] >= storage.size() * 8) {
            while (values[i] >= storage.size() * 8){
                storage.push_back(0);
            } 
        }
        storage[values[i] / 8] |= (1 << (values[i] % 8));
    }
    std::cout << "\nstart in left (0 - 63):\n";
    for (int i = storage.size() - 1; i >= 0; --i) {
        output_char(storage[i]);
    }
    std::cout << '\n' << "result: ";

    for (int i = storage.size() - 1; i >= 0; --i) {
        for (int j = 0; j < 8; ++j) {
            if ((storage[i] & (1 << j)) != 0)    std::cout << i * 8 + j << ' ';
        }
    }
}

void task7() {
    generate();
    sort_file();
    int start = clock(); 
    std::vector <unsigned char> storage;
    for (int i = 0; i < (MAX_SIZE + 7) / 8; ++i) storage.push_back(0);
    int tmp = 0;
    std::ifstream fin("value.txt");
    while (!fin.eof()) {
        fin >> tmp;
        storage[tmp / 8] |= (1 << (tmp % 8));
    }

    int end = clock();
    std::cout << "time: " << (double)(end - start) / CLOCKS_PER_SEC << '\n'; 

    for (int i = 0; i < storage.size(); ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((storage[i] & (1 << j)) != 0)    std::cout << i * 8 + j << ' ';
        }
    }
    
    fin.close();
    storage.clear();
    
}

void output(int n) {
    int i = 1073741824;
    while (true) {
        if (n & i)
            std::cout << 1;
        else
            std::cout << 0;
        if (i == 1)
            break;
        i >>= 1;
    }  
}

void output_char(unsigned char n) {
    unsigned char i = 128;
        while (true) {
        if (n & i)
            std::cout << 1;
        else
            std::cout << 0;
        if (i == 1)
            break;
        i >>= 1;
    }  
}

void generate() {
    std::ofstream fout("text.txt");
    for (int i = 0; i < MAX_SIZE; ++i) {
        fout << i << ' ';
    }
    fout.close();
}

void sort_file() {
    std::ifstream fin("text.txt");
    std::ofstream fout("value.txt");
    std::vector <int> buffer;
    buffer.resize(MAX_READ);
    std::experimental::reseed(std::time(nullptr));
    int tmp = 0, index = 0, maximum = MAX_READ;
    while (!fin.eof()) {
        for (int i = 0; i < MAX_READ; ++i) {
            fin >> tmp;
            buffer[i] = tmp;
        }
        char space = ' ';
        fin >> space;
        for (int i = 0; i < MAX_READ; ++i) {   
            index = std::experimental::randint(0, maximum - 1);
            int t = buffer[i];
            buffer[i] = buffer[index];
            buffer[index] = t;
        }
        for (int i = 0; i < MAX_READ; ++i) fout << buffer[i] << ' ';
    }
    fin.close();
    fout.close();
}