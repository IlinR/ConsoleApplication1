#pragma once
#include <iostream>

#define B 29
using namespace std;
class Hash_table
{
		
	struct Ht_item {
		char* key;
		char* value;
	};
	Ht_item** items;
	int size;
	int count;
	unsigned long hash_function(char* str);
	Ht_item* create_item(char* key, char* value);
	Hash_table* create_table(int size);
	void free_item(Ht_item* item);

	void ht_insert(Hash_table* table, char* key, char* value);
	void handle_collision(Hash_table* table, Ht_item* item);

	void free_table(Hash_table* table);
	char* ht_search(Hash_table* table, char* key);
	void print_search(Hash_table* table, char* key);
	void print_table(Hash_table* table);
};

