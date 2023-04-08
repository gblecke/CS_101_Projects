#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
unsigned long djb2(string str);
int getNumLines(string FileName);
void initialize2D(int array[][100], int Dim1, int Dim2);
void insertInto2D(int array[][100], int key, int numLines, unsigned long bucket);
void clearSCharacters(string &tempString);
void countUniqueWords(vector<string> table, int len);

class HashTable {
    public: 
        HashTable(int len, string strat, int lines); //constructor for qp and lp
        HashTable(int len, string strat, int lines, int DHK); //dh constructor

        int hashInsert(string key, int lineNum, int indices[][100]);
        void hashSearch(string key, int indices[][100]);
        void BuildTable(string fileName, int DDarray[][100]);
        
    private:
        vector<string> HashNames;
        string colStrat;
        int size;
        int DHkey;
        int numLines;
        unsigned long LP(unsigned long bucket, int i);
        unsigned long QP(unsigned long bucket, int i);
        unsigned long DH(string key, int i);
};

int main(int argc, char *argv[]) {
    int numLines = getNumLines(argv[1]);
    int hashLineNums[stoi(argv[3])][100];
    initialize2D(hashLineNums, stoi(argv[3]), numLines);
    string strat = argv[4];
    if(argc == 5) {
        HashTable Hash(stoi(argv[3]), strat, numLines);
        ifstream searchFile;
        Hash.BuildTable(argv[1], hashLineNums);
        searchFile.open(argv[2]);
        string key;
        searchFile >> key;
        while(!searchFile.eof()) {
            Hash.hashSearch(key, hashLineNums);
            searchFile >> key;
        }
    } else {
        HashTable Hash(stoi(argv[3]), strat, numLines, stoi(argv[5]));
        ifstream searchFile;
        Hash.BuildTable(argv[1], hashLineNums);
        searchFile.open(argv[2]);
        string key;
        searchFile >> key;
        while(!searchFile.eof()) {
            Hash.hashSearch(key, hashLineNums);
            searchFile >> key;
        }
    }
    return 0;
}

unsigned long djb2(string str) {
   const char *ptr = str.c_str();
   unsigned long hash = 5381;
   int c;
   while ((c = *ptr++)) {
      hash = ((hash << 5) + hash) + c;
   }
   return hash;
}

int getNumLines(string FileName) {
    int numLines = 0;
    ifstream File;
    File.open(FileName);
    string tempLine;
    while(getline(File, tempLine)) {
        numLines++;
    }
    File.close();
    return numLines;
}

void initialize2D(int array[][100], int Dim1, int Dim2) {
    for(int i = 0; i < Dim1; i++) {
        for(int j = 0; j < Dim2; j++) {
            array[i][j] = -1;
        }
    }
}

void insertInto2D(int array[][100], int key, int numLines, unsigned long bucket) {
    for(int i = 0; i < numLines; i++) {
        if(array[bucket][i] < 0) {
            array[bucket][i] = key;
            return;
        }
    }
}

void clearSCharacters(string &tempString) {
    int tempLen = tempString.length();
    for(int i = 0; i < tempLen; i++) {
        if(tempString.at(i) >= 65 && tempString.at(i) <= 90) {
            tempString.at(i) = tempString.at(i) + 32;
        } else if(tempString.at(i) < 97 || tempString.at(i) > 122) {
            tempString.at(i) = ' ';
        }
   }
}

void countUniqueWords(vector<string> table, int len) {
    int unique = 0;
    for(int i = 0; i < len; i++) {
        if(table.at(i) != "NoString") {
            unique++;
        }
    }
    cout << "The number of unique words found in the file was " << unique << endl;
}

HashTable::HashTable(int len, string strat, int lines) {
    size = len;
    colStrat = strat;
    HashNames.resize(size);
    DHkey = -1;
    for(int i = 0; i < size; i++) {
        HashNames.at(i) = "NoString";
    }
    numLines = lines;
}

HashTable::HashTable(int len, string strat, int lines, int DHK) {
    size = len;
    colStrat = strat;
    HashNames.resize(size);
    DHkey = DHK;
    for(int i = 0; i < size; i++) {
        HashNames.at(i) = "NoString";
    }
    numLines = lines;
}

int HashTable::hashInsert(string key, int lineNum, int indices[][100]) {
    unsigned long bucket = djb2(key) % size;
    unsigned long newBucket = bucket;
    int collisions = 0;
    for(int i = 1; i < 100; i++) {
        if(HashNames.at(newBucket) == "NoString") {
            HashNames.at(newBucket) = key;
            insertInto2D(indices, lineNum, numLines, newBucket);
            return collisions;
        } else if(HashNames.at(newBucket) == key) {
            insertInto2D(indices, lineNum, numLines, newBucket);
            return collisions;
        } else {
            if(colStrat == "lp") {
                newBucket = LP(bucket, i);
            } else if(colStrat == "qp") {
                newBucket = QP(bucket, i);
            } else {
                newBucket = DH(key, i);
            }
            collisions++;
        }
    }
    return collisions;
}

void HashTable::hashSearch(string key, int hashArray[][100]) {
    int collisions = 0;
    int bucket = djb2(key) % size;
    int newBucket = bucket;
    for(int i = 1; i < 100; i++) {
        if(HashNames.at(newBucket) == key || HashNames.at(newBucket) == "NoString") {
            cout << endl << key << " appears on lines [";
            for(int j = 0; j < 100; j++) {
                if(hashArray[newBucket][j] == -1) {break;}
                cout << hashArray[newBucket][j] + 1;
                if(hashArray[newBucket][j + 1] != -1) { cout << ","; }
            }
            cout << "]" << endl;
            cout << "The search had " << collisions << " collisions" << endl;
            return;
        } else {
            if(colStrat == "lp") {
                newBucket = LP(bucket, i);
            } else if(colStrat == "qp") {
                newBucket = QP(bucket, i);
            } else {
                newBucket = DH(key, i);
            }
            collisions++;
        }
    }
    return;
}

void HashTable::BuildTable(string fileName, int DDarray[][100]) {
    int NumCols = 0;
    ifstream File;
    File.open(fileName);
    string lineByLine[numLines];
    for(int i = 0; i < numLines; i++) {
        getline(File, lineByLine[i]);
        clearSCharacters(lineByLine[i]);
    }
    File.close();
    int numWords = 0;
    string tempWord;
    istringstream lines;
    for(int i = 0; i < numLines; i++) {
        lines.clear();
        lines.str(lineByLine[i]);
        while(lines >> tempWord) {
            numWords++;
            NumCols = NumCols + hashInsert(tempWord, i, DDarray);
        }
    }
    cout << "The number of words found in the file was " << numWords << endl;
    countUniqueWords(HashNames, size);
    cout << "The number of collisions was " << NumCols << endl;
}

unsigned long HashTable::LP(unsigned long bucket, int i) {
    bucket = (bucket + i) % size;
    return bucket;
} //linear probing

unsigned long HashTable::QP(unsigned long bucket, int i) {
    bucket = (bucket + (i * i)) % size;
    return bucket;
} //quadratic probing

unsigned long HashTable::DH(string key, int i) {
    int key1 = djb2(key) % size;
    int key2 = DHkey - (djb2(key) % DHkey);
    int bucket = (key1 + (i * key2)) % size;
    return bucket;
}