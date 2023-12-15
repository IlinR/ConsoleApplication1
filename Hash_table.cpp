#include "Hash_table.h"

unsigned long Hash_table::hash_function(char* str) {
	unsigned long h = 0;
	for (int i = 0; str[i]; i++)
		h += str[i];
	return (h % B);
}
Hash_table::Ht_item* Hash_table::create_item(char* key, char* value) {
	// Creates a pointer to a new hash table item
	Ht_item* item = (Ht_item*)malloc(sizeof(Ht_item));
	item->key = (char*)malloc(strlen(key) + 1);
	item->value = (char*)malloc(strlen(value) + 1);

	strcpy(item->key, key);
	strcpy(item->value, value);

	return item;
}
Hash_table* Hash_table::create_table(int size) {
	// Creates a new HashTable
	Hash_table* table = (Hash_table*)malloc(sizeof(Hash_table));
	table->size = size;
	table->count = 0;
	table->items = (Ht_item**)calloc(table->size, sizeof(Ht_item*));
	for (int i = 0; i < table->size; i++)
		table->items[i] = NULL;
	return table;
}
void Hash_table::free_item(Ht_item* item) {
	// Frees an item
	free(item->key);
	free(item->value);
	free(item);
}

void Hash_table::ht_insert(Hash_table* table, char* key, char* value) {
	// Create the item
	Ht_item* item = create_item(key, value);
	int index = hash_function(key);

	Ht_item* current_item = table->items[index];

	if (current_item == NULL) {
		// Key does not exist.
		if (table->count == table->size) {
			// Hash Table Full
			printf("Insert Error: Hash Table is full\n");
			return;
		}


		// Insert directly
		table->items[index] = item;
		table->count++;
	}

	else {
		// Scenario 1: We only need to update value
		if (strcmp(current_item->key, key) == 0) {
			strcpy(table->items[index]->value, value);
			return;
		}

		else {
			// Scenario 2: Collision
			 // We will handle case this a bit later
			handle_collision(table, item);
			return;
		}
	}
}
void Hash_table::handle_collision(Hash_table* table, Ht_item* item) {


};

void Hash_table::free_table(Hash_table* table) {
	// Frees the table
	for (int i = 0; i < table->size; i++) {
		Ht_item* item = table->items[i];
		if (item != NULL)
			free_item(item);
	}

	free(table->items);
	free(table);
}

char* Hash_table::ht_search(Hash_table* table, char* key) {
	// Searches the key in the hashtable
	// and returns NULL if it doesn't exist
	int index = hash_function(key);
	Ht_item* item = table->items[index];

	// Ensure that we move to a non NULL item
	if (item != NULL) {
		if (strcmp(item->key, key) == 0)
			return item->value;
	}
	return NULL;
}

void Hash_table::print_search(Hash_table* table, char* key) {
	char* val;
	if ((val = ht_search(table, key)) == NULL) {
		printf("Key:%s does not exist\n", key);
		return;
	}
	else {
		printf("Key:%s, Value:%s\n", key, val);
	}
}

void Hash_table::print_table(Hash_table* table) {
	printf("\nHash Table\n-------------------\n");
	for (int i = 0; i < table->size; i++) {
		if (table->items[i]) {
			printf("Index:%d, Key:%s, Value:%s\n", i, table->items[i]->key, table->items[i]->value);
		}
	}
	printf("-------------------\n\n");
}