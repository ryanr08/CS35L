#include <stdio.h>
#include <stdlib.h>

char defrob(char const a)
{
return a^42;
}

int frobcmp(const void* a, const void* b){
const char* string1 = *(const char**)a;
const char* string2 = *(const char**)b;

for (int i = 0; string1[i] != ' ' && string2[i] != ' '; i++)
	{
		if (string1[i] == '\0' | string2[i] == '\0') continue;
		if (defrob(string1[i]) > defrob(string2[i])) return 1;
		else if (defrob(string1[i]) < defrob(string2[i])) return -1;
		else if (string1[i+1] == ' ' && string2[i+1] != ' ') return -1;
		else if (string2[i+1] == ' ' && string1[i+1] != ' ') return 1;
	}
return 0;
}

int main()
{
char* word = NULL;
char** data = NULL;
int word_length = 0;
int data_length = 0;
char ch = ' ';
char prevCh = ' ';

while(!feof(stdin)){

prevCh = ch;
ch = getchar();
if (ferror(stdin)){
	free(word);
	free(data);
	fprintf(stderr, "I/O error.");
	exit(1);
}

if (prevCh == ' ' && ch == ' ')
	continue;
if (word == NULL){
	word = (char*)malloc(sizeof(char));
}
else
{
word = (char*)realloc(word, (word_length+1)*sizeof(char));
}
if (word == NULL)
{
free(word);
free(data);
fprintf(stderr, "Memory allocation failure.");
exit(1);
}
if(ch != ' ' && ch != EOF){
word[word_length] = ch;
word_length++;
}

if (ch == ' ' | ch == EOF)
{
if (word != NULL)
{
word = (char*)realloc(word, (word_length+1)*sizeof(char));
word[word_length] = ' ';
word_length++;
if (data == NULL)
{
data = (char**)malloc(sizeof(char*));
}
else
{
data = (char**)realloc(data, (data_length + 1)*sizeof(char*));
}
if (data == NULL)
{
free(word);
free(data);
fprintf(stderr, "Memory allocation failure.");
exit(1);
}
data[data_length] = word;
data_length++;
word = NULL;
word_length = 0;
}}}
qsort(data, data_length, sizeof(char*), frobcmp);
for (int i = 0; i < data_length; i++){
for (int j = 0; data[i][j] != ' '; j++){
	printf("%c", data[i][j]);
}
printf(" ");
free(data[i]);
}
free(data);
free(word);
return 0;
}
