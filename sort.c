#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define ST_BLOKOV 21

/*
Drugače so ID-ji zapisani v inode-ih, a tu sem jih vključil zaradi ilustracijskih namenov
*/
typedef struct block{
    uint8_t id;
    uint8_t data[4096];
}Block;

uint8_t* counter(Block disk[], int length, int maxId){

    uint8_t* counts = (uint8_t*)calloc(maxId+1, sizeof(uint8_t));
    uint8_t* sums = (uint8_t*)calloc(maxId+1, sizeof(uint8_t));

    for(int i = 0; i < length; i++){
        counts[disk[i].id]++;
    }

    for(int i = 1; i <= maxId; i++){
        sums[i] = sums[i-1] + counts[i-1];
    }

    return sums;
}

void swap(Block disk[], int i, int j){
    Block tempBlock;

    tempBlock.id = disk[i].id;
    
    disk[i] = disk[j];
    disk[j] = tempBlock;
}

void swapIndex(uint8_t* indexes, int i, int j){
    uint8_t tempIndex = indexes[i];
    indexes[i] = indexes[indexes[i]];
    indexes[j] = tempIndex;
}

void sort(Block disk[], int length, uint8_t* indexes){
    int counter = 0;
    for(int i = 0; i < length; i++){
        
        while(i != indexes[i]){
            counter++;
            swap(disk, i, indexes[i]);
            swapIndex(indexes, i, indexes[i]);
        }
    }
    printf("Number of swaps during sorting: %d\n", counter);
    printf("\n");
}

int main(){

    Block b;
    
    int data[ST_BLOKOV] = {1,2,3,1,1,3,3,2,4,3,1,4,3,1,4,4,4,1,2,1,2};

    Block disk[ST_BLOKOV];

    for(int i = 0; i < ST_BLOKOV; i++){
        uint8_t id = data[i];
        disk[i].id = id;
    }

    uint8_t* sums = counter(disk, ST_BLOKOV, 4);

    uint8_t* indexes = (uint8_t*)calloc(ST_BLOKOV, sizeof(uint8_t));

    for(int i = 0; i < ST_BLOKOV; i++){
        indexes[i] = sums[disk[i].id];
        sums[disk[i].id]++;
    }
    printf("Data before being sorted: \n");
    for(int i = 0; i < ST_BLOKOV; i++){
        printf("%d ", disk[i].id);
    }
    printf("\n");
    printf("\n");

    printf("Indexes for fragments: \n");
    for(int i = 0; i < ST_BLOKOV; i++){
        printf("%d ", indexes[i]);
    }
    printf("\n");
    printf("\n");

    sort(disk, ST_BLOKOV, indexes);

    printf("Data after being sorted in in-place fashion: \n");
    for(int i = 0; i < ST_BLOKOV; i++){
        printf("%d ", disk[i].id);
    }
    printf("\n");

    return  0;
}