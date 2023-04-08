// CS 101-001
// Maclane
// Griffin Blecke
// Due: 10/4/2020

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

void implementMergesortArray(int nodupes[], int i, int j);
void MergeArray(int nodupes[], int i, int k, int j);
int findDuplicatesArray(int array1[20000], int array2[20000], int array1Num, int array2Num, int(&nodupes)[20000]);
int findDuplicatesString(std::string file1[20000], std::string file2[20000], int numVals1, int numVals2, std::string noDupes[20000]);
void getStringfromFile(std::string readFile[], std::string fileName, int& numVals);
void getArrayfromFile(int readArr[], std::string fileName, int& numOfValues);
void implementMergesortString(std::string nodupes[20000], int i, int j);
void MergeString(std::string nodupes[20000], int i, int k, int j);

int main(int argc, char *argv[]) {
    int file1[20000], file2[20000];
    int file1NumVals = 0, file2NumVals = 0;
    std::string file1s[20000], file2s[20000];
    std::string letter = argv[1];
    if(letter == "i") {
        int sortedarray[20000];
        getArrayfromFile(file1, argv[2], file1NumVals);
        getArrayfromFile(file2, argv[3], file2NumVals);
        int sortedNum = findDuplicatesArray(file1, file2, file1NumVals, file2NumVals, sortedarray);
        implementMergesortArray(sortedarray, 0, sortedNum - 1);
        for(int i = 0; i < sortedNum; i++) {
            cout << sortedarray[i] << endl;
        }
    } else if(letter == "s") {
        string sortedString[20000];
        getStringfromFile(file1s, argv[2], file1NumVals);
        getStringfromFile(file2s, argv[3], file2NumVals);
        int sortedNum = findDuplicatesString(file1s, file2s, file1NumVals, file2NumVals, sortedString);
        implementMergesortString(sortedString, 0, sortedNum - 1);
        for(int i = 0; i < sortedNum; i++) {
            cout << sortedString[i] << endl;
        }
    }
    return 0;
}

void getStringfromFile(std::string readFile[], std::string fileName, int& numVals) {
	ifstream tempFile;
	std::string tempLine;

	tempFile.open(fileName);
    int i = 0;
	while(!tempFile.eof()) {
		tempFile >> tempLine;
        readFile[i] = tempLine;
        i++;
	}
    numVals = i;
    tempFile.close();
    return;
}

void getArrayfromFile(int readArr[], std::string fileName, int& numOfValues) {
    int i = 0;
    ifstream tempFile;
    int tempInt;

    tempFile.open(fileName);

    while(!tempFile.eof()) {
        tempFile >> tempInt;
        readArr[i] = tempInt;
        i++;
    }
    numOfValues = i - 1;
    tempFile.close();
    return;
}

int findDuplicatesArray(int array1[20000], int array2[20000], int array1Num, int array2Num, int(&nodupes)[20000]) {
    int numOfSortedVals = 0;
    for(int i = 0; i < array1Num; i++) {
        for(int j = 0; j < array2Num; j++) {
            if(array1[i] == array2[j]) {
                int k;
                for(k = 0; k <= numOfSortedVals; k++){ 
                    if(k == numOfSortedVals) {
                        break;
                    } else if(nodupes[k] == array1[i]) {
                        break;
                    }
                }
                if(k == numOfSortedVals) {
                    nodupes[numOfSortedVals] = array1[i];
                    numOfSortedVals++;
                }
            }
        }
    }
    return numOfSortedVals;
}

void implementMergesortArray(int nodupes[], int i, int j) {
    int k;
    if(i < j) {
        k = (i + j) / 2;

        implementMergesortArray(nodupes, i, k);
        implementMergesortArray(nodupes, k+1, j);

        MergeArray(nodupes, i, k, j);
    }
}

void MergeArray(int nodupes[], int i, int k, int j) {
    int size;
    int mergePos;
    int left;
    int right;

    mergePos = 0;
    size = j - i + 1;
    left = i;
    right = k + 1;
    int* merged = new int[size];

    while(left <= k && right <= j) {
        if(nodupes[left] < nodupes[right]) {
            merged[mergePos] = nodupes[left];
            left++;
        } else {
            merged[mergePos] = nodupes[right];
            right++;
        }
        mergePos++;
    }
    while(left <= k) {
        merged[mergePos] = nodupes[left];
        left++;
        mergePos++;
    }
    while(right <= j) {
        merged[mergePos] = nodupes[right];
        right++;
        mergePos++;
    }
    for(mergePos = 0; mergePos < size; mergePos++) {
        nodupes[i + mergePos] = merged[mergePos];
    }
    delete [] merged;
}

int findDuplicatesString(std::string file1[20000], std::string file2[20000], int numVals1, int numVals2, std::string noDupes[20000]) {
    int sortedValsNum = 0;
    for(int i = 0; i < numVals1; i++) {
        for(int j = 0; j < numVals2; j++) {
            if(file1[i] == file2[j]) {
                int k;
                for(k = 0; k <= sortedValsNum; k++) {
                    if(k == sortedValsNum) {
                        break;
                    } else if(file1[i] == noDupes[k]){
                        break;
                    }
                }
                if(k == sortedValsNum) {
                    noDupes[sortedValsNum] = file1[i];
                    sortedValsNum++;
                }
            }
        }
    }
    return sortedValsNum;
}

void implementMergesortString(std::string nodupes[20000], int i, int j) {
    int k;
    if(i < j) {
        k = (i + j) / 2;

        implementMergesortString(nodupes, i, k);
        implementMergesortString(nodupes, k+1, j);

        MergeString(nodupes, i, k, j);
    }
}

void MergeString(std::string nodupes[20000], int i, int k, int j) {
    int size;
    int mergePos;
    int left;
    int right;

    mergePos = 0;
    size = j - i + 1;
    left = i;
    right = k + 1;
    string merged[size];

    while(left <= k && right <= j) {
        if(nodupes[left] < nodupes[right]) {
            merged[mergePos] = nodupes[left];
            left++;
        } else {
            merged[mergePos] = nodupes[right];
            right++;
        }
        mergePos++;
    }
    while(left <= k) {
        merged[mergePos] = nodupes[left];
        left++;
        mergePos++;
    }
    while(right <= j) {
        merged[mergePos] = nodupes[right];
        right++;
        mergePos++;
    }
    for(mergePos = 0; mergePos < size; mergePos++) {
        nodupes[i + mergePos] = merged[mergePos];
    }
}