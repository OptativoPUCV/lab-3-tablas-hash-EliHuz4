#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
    long Indice = hash(key, map->capacity);
    if(map->buckets[Indice] == NULL)
    {
        map->buckets[Indice] = (Pair *)malloc(sizeof(Pair));
        map->buckets[Indice]->key = key;
        map->buckets[Indice]->value = value;
        map->size++;
    }
    else{
        for(int i = (Indice + 1) % map->capacity; i != Indice; i = (i + 1) % map->capacity)
        {
            if(map->buckets[i] == NULL)
            {
                map->buckets[i] = (Pair *)malloc(sizeof(Pair));
                map->buckets[i]->key = key;
                map->buckets[i]->value = value;
                map->size++;
                return;
            }
        }
    }
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)
}


HashMap * createMap(long capacity) {
    HashMap * Mapa = (HashMap *) malloc(sizeof(HashMap));
    if(Mapa == NULL) return NULL;

    Mapa->buckets = (Pair **) malloc(sizeof(Pair *) * capacity);
    if(Mapa->buckets == NULL){
        free(Mapa);
        return NULL;
    }

    for(int i = 0; i < capacity; i++){
        Mapa->buckets[i] = NULL;
    }

    Mapa->capacity = capacity;
    Mapa->size = 0;
    Mapa->current = -1;

    return Mapa;
}

void eraseMap(HashMap * map,  char * key) {    
    long Indice = hash(key, map->capacity);
    for (int i = 0; i < map->capacity; i++) {

        long PosAux = (Indice + i) % map->capacity;

        if (map->buckets[PosAux] != NULL && map->buckets[PosAux]->key != NULL) {

            if (strcmp(map->buckets[PosAux]->key, key) == 0) {

                map->buckets[PosAux]->key = NULL;
                map->size--;
            }
        }
    }
}

Pair * searchMap(HashMap * map, char * key) {
    long Indice = hash(key, map->capacity);

    for (int i = 0; i < map->capacity; i++) {

        long PosAux = (Indice + i) % map->capacity;

        if (map->buckets[PosAux] != NULL && map->buckets[PosAux]->key != NULL) {

            if (strcmp(map->buckets[PosAux]->key, key) == 0) {

                map->current = PosAux;
                return map->buckets[PosAux];
            }

        }
    }
    return NULL;
}

Pair * firstMap(HashMap * map) {
    for (int i = 0; i < map->capacity; i++) {
        if(map->buckets[i]->key != NULL)
        {
            map->current = i;
            return map->buckets[i];
        }
    }
    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
