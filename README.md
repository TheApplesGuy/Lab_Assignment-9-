// This number can be switched to anything i just saw that the sample size needed to be 23 on the projector while in the lab

#define hashsize 23

// this is just for convienence, works effectively 

struct HashType {
    struct RecordType* records[hashsize];
};

struct HashType hash_Table;

void HashTable(struct HashType* hashTable) {
    for (int i = 0; i < hashsize; ++i) {
        hashTable->records[i] = NULL;
    }
    
}
