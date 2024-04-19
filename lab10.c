#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
	struct Trie * children[26];
	int flag;
};

// Initializes a trie structure
struct Trie *createTrie() {
	struct Trie * trie = malloc(sizeof(struct Trie));
	trie->flag = 0;

	for (int i = 0; i < 26; i++) {
		trie->children[i] = NULL;
	}

	return trie;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word){

	for (int i = 0; i < strlen(word); i++) {
		if (pTrie->children[word[i]-'a'] == NULL) {
			pTrie->children[word[i]-'a'] = createTrie();
		}
		pTrie = pTrie->children[word[i]-'a'];
	}
	pTrie->flag++;
}

// // computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word) {

	for (int i = 0; i < strlen(word); i++) {
		pTrie = pTrie->children[word[i]-'a'];
		if (pTrie == NULL) return 0;
	}
	return pTrie->flag;
}

// // deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie) {

	if (pTrie == NULL) return NULL;

	for (int i = 0; i < 26; i++) {
		if (pTrie->children[i] != NULL) {
			pTrie->children[i] = deallocateTrie(pTrie->children[i]);
		}
	}
	free(pTrie);

	return NULL;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords){

	FILE * f = fopen(filename, "r");

	int words;

	for (int i = -1; i < words; i++) {
		if (i == -1) {
			fscanf(f, "%d", &words);
		} else {
			pInWords[i] = malloc(sizeof(char) * 30);
			fscanf(f, "%s", pInWords[i]);
		}
	}
	return words;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);

	// free words
	for (int i = 0; i < numWords; i++) {
		free(inWords[i]);
	}

	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}