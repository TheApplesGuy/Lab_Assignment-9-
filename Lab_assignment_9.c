
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define hashsize 23

// RecordType
struct RecordType {
    int id;
    char name;
    int order;
    struct RecordType* next;
};

// Fill out this structure
struct HashType {
    struct RecordType* records[hashsize];
};

struct HashType hash_Table;

void HashTable(struct HashType* hashTable) {
    for (int i = 0; i < hashsize; ++i) {
        hashTable->records[i] = NULL;
    }
    
}

// Compute the hash function
int hash(int x) {
    return x % hashsize;
}

void insertRecord(struct HashType* hashTable, struct RecordType* newRecord) {
    int index = hash(newRecord->id);
    newRecord->next = hashTable->records[index];
    hashTable->records[index] = newRecord;
}




// prints the records
void printRecords(struct RecordType pData[], int dataSz) {
    printf("\nRecords:\n");
    for (int i = 0; i < dataSz; ++i) {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
        // Implement parse data block
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }

        fclose(inFile);
    }

    return dataSz;
}


// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType* hashTable) {
    int i;
        for (i = 0; i < hashsize; ++i) {
            // if index is occupied with any records, print all
            struct RecordType* current = hashTable->records[i];
            while (current != NULL) {
                printf("Index %d -> ", i);
                printf("id: %d name: %c order: %d -> ", current->id, current->name, current->order);
                current = current->next;
            }
            printf("\n");
        }
    }




int main(void) {
    struct RecordType* pRecords;
    int recordSz = 0;
    
    recordSz = parseData("input_lab_9.txt", &pRecords);
    HashTable(&hash_Table);
    
    printRecords(pRecords, recordSz);
    // Your hash implementation
    
    for (int i = 0; i < recordSz; ++i) {
        insertRecord(&hash_Table, &pRecords[i]);
    }

    displayRecordsInHash(&hash_Table);

    free(pRecords);
    return 0;
}
