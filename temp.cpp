#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

struct entry_s {
	char *key;
	char *value;
	struct entry_s *next;
};

typedef struct entry_s entry_t;

struct hashtable_s {
	int size;
	struct entry_s **table;	
};

typedef struct hashtable_s hashtable_t;

hashtable_t *ht_create( int size ) {

	hashtable_t *hashtable = NULL;
	int i;

	if( size < 1 ) return NULL;

	if( ( hashtable = (hashtable_t*) malloc( sizeof( hashtable_t ) ) ) == NULL ) {
		return NULL;
	}

	if( ( hashtable->table = (entry_s**) malloc( sizeof( entry_t * ) * size ) ) == NULL ) {
		return NULL;
	}
	for( i = 0; i < size; i++ ) {
		hashtable->table[i] = NULL;
	}

	hashtable->size = size;

	return hashtable;	
}

int ht_hash( hashtable_t *hashtable, char *key ) {

	unsigned long int hashval = 1234567;
	int i = 0;

	while( hashval < ULONG_MAX && i < strlen( key ) ) {
		hashval = hashval << 8;
		hashval += key[ i ];
		i++;
	}

	return hashval % hashtable->size;
}

entry_t *ht_newpair( char *key, char *value ) {
	entry_t *newpair;

	if( ( newpair = (entry_t*) malloc( sizeof( entry_t ) ) ) == NULL ) {
		return NULL;
	}

	if( ( newpair->key = strdup( key ) ) == NULL ) {
		return NULL;
	}

	if( ( newpair->value = strdup( value ) ) == NULL ) {
		return NULL;
	}

	newpair->next = NULL;

	return newpair;
}

void ht_del( hashtable_t *hashtable, char *key){
    
    int bin = 0;
    int flag =0;
    
    entry_t *temp,*pair;
    
    bin = ht_hash (hashtable,key);
    
    pair = hashtable->table[bin];
   
    temp = pair;
    while(pair != NULL) {
        if(strcmp(key,pair->key) == 0 ){
            flag = 1;
            if(pair == hashtable->table[bin]){
                hashtable->table[bin] = pair->next;
            }
            else{
                temp->next = pair->next;
            }
            free(pair);
            break;
        }
        temp = pair;
        pair = pair->next;
    }
}

void ht_set( hashtable_t *hashtable, char *key, char *value ) {
	int bin = 0;
	entry_t *newpair = NULL;
	entry_t *next = NULL;
	entry_t *last = NULL;

	bin = ht_hash( hashtable, key );

	next = hashtable->table[ bin ];

	while( next != NULL && next->key != NULL && strcmp( key, next->key ) > 0 ) {
		last = next;
		next = next->next;
	}

	if( next != NULL && next->key != NULL && strcmp( key, next->key ) == 0 ) {

		free( next->value );
		next->value = strdup( value );

	} else {
		newpair = ht_newpair( key, value );

		if( next == hashtable->table[ bin ] ) {
			newpair->next = next;
			hashtable->table[ bin ] = newpair;
	
		} else if ( next == NULL ) {
			last->next = newpair;
	
		} else  {
			newpair->next = next;
			last->next = newpair;
		}
	}
}

char *ht_get( hashtable_t *hashtable, char *key ) {
	int bin = 0;
	entry_t *pair;

	bin = ht_hash( hashtable, key );

	pair = hashtable->table[ bin ];
	while( pair != NULL && pair->key != NULL && strcmp( key, pair->key ) > 0 ) {
		pair = pair->next;
	}

	if( pair == NULL || pair->key == NULL || strcmp( key, pair->key ) != 0 ) {
		return NULL;

	} else {
		return pair->value;
	}
	
}

char* m_strcpy(char* base) {
    if (base == NULL) return NULL;
    int ln = strlen(base);
    char* ret_val = (char*) malloc((ln + 1) * sizeof(char));
    strcpy(ret_val, base);
    return ret_val;
}

int main() {

	hashtable_t *hashtable = ht_create(300007);

	size_t oper_cnt = 0;
    scanf("%lu", &oper_cnt);

    char buff[4097];
    char buff2[4097];
    
    for (size_t it = 0; it < oper_cnt; ++it) {
        scanf("%s %s", buff, buff2);

         if (strcmp(buff, "ADD") == 0) {
            // root = AVLTreePush(root, buff, buff2);
            scanf("%s", buff);
            char* get_res = ht_get(hashtable, buff2);
            if (get_res != NULL) {
                printf("ERROR\n");
            } else {
                char* key = m_strcpy(buff2);
                char* val = m_strcpy(buff);
                ht_set(hashtable, key, val);
            }
        } else if (strcmp(buff, "DELETE") == 0) {
            char* get_res = ht_get(hashtable, buff2);
            if (get_res == NULL) {
                printf("ERROR\n");
            } else {
                ht_del(hashtable, buff2);
            }
        } else if (strcmp(buff, "UPDATE") == 0) {
            scanf("%s", buff);
            // printf("'%s'", buff2);
            char* get_res = ht_get(hashtable, buff2);
            if (get_res == NULL) {
                printf("ERROR\n");
            } else {
                char* key = m_strcpy(buff2);
                char* val = m_strcpy(buff);
                ht_set(hashtable, key, val);
            }
        } else if (strcmp(buff, "PRINT") == 0) {
            char* get_res = ht_get(hashtable, buff2);
            if (get_res == NULL) {
                printf("ERROR\n");
            } else {
                printf("%s %s\n", buff2, get_res);
            }
        }


    }

	return 0;
}