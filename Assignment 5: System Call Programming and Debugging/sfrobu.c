#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>

int dash_f = 0;

char defrob(char const a)
{
if (dash_f)
{
char b = toupper((unsigned char)(a^42)); 
return b;
}
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

int main(int argc, char** argv)
{

if(argc > 2){
	write(2, "Only up to two arguments allowed.\n", 34);
	exit(1);
}

const char* arg1 = argv[1];
const char* dashF = "-f";

if (argc == 2 && strcmp(argv[1], dashF) == 0){
dash_f = 1;
}
else if (argc == 2 && strcmp(arg1, dashF) != 0){
write(2, "Error, only optional argument is -f.\n", 37);
exit(1);
}


struct stat buffer2;
struct stat buffer;
int status = fstat(0, &buffer);
if (status < 0){
	write(2, "Error reading in file\n", 22);
	exit(1);
}

char* word = NULL;
char** data = NULL;
int word_length = 0;
int data_length = 0;
char ch = ' ';
char prevCh = ' ';


if (S_ISREG(buffer.st_mode)){
char* input = (char*)malloc((buffer.st_size + 1) * sizeof(char));
if (input == NULL){
	write(2, "Memory allocation error\n", 24);
	free(input);
}
int inputSize = buffer.st_size;

int err = read(0, input, inputSize);
if (err < 0){
	write(2, "Error reading in file\n", 22);
	free(input);
	exit(1);
}
input[inputSize] = EOF;
inputSize++;

int charCounter = 0;

while(1){
prevCh = ch;
ch = input[charCounter];
charCounter++;

fstat(0, &buffer);
//printf("%d", buffer.st_size);
if (buffer.st_size >= inputSize){
	//status = fstat(0, &buffer);
	//if(status < 0){	
        //	write(2, "Error reading in file\n", 22);
	//	free(input);
        //	exit(1);
	//}
	printf("YUHHH");
	input = (char*)realloc(input, (inputSize+1)*sizeof(char));
	if (input==NULL)	
	{
		write(2, "Memory allocation error\n", 24);
		free(data);
		free(word);
		free(input);
	}
	//inputSize++;
	char tempIn;
	int r1 = read(0, &tempIn, 1);
	if (r1 < 0){
	write(2, "Error reading in file\n", 22);
	free(input);
	free(word);
	free(data);
	exit(1);
	}
	input[inputSize] = tempIn;
	inputSize++;
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
	free(input);
	write(2, "Memory allocation failure.\n", 27);
	exit(1);
}
if(ch != ' ' && ch != EOF){
	word[word_length] = ch;
	word_length++;
	continue;
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
	free(input);
	write(2, "Memory allocation failure.\n", 27);
	exit(1);
}
data[data_length] = word;
data_length++;
word = NULL;
word_length = 0;
if (ch == EOF)
{
	break;
}
}}}
free(input);
}
else{
char input[1];

while(1){
int r = read(0, input, 1);
if (r < 0)
{
	write(2, "Error reading from standard input.\n", 35);
	exit(1);
}
prevCh = ch;
ch = input[0];
if (prevCh == ' ' && ch == ' ')
	continue;
if (word == NULL){
	word = (char*)malloc(sizeof(char));
}
else{
	word = (char*)realloc(word, (word_length+1)*sizeof(char));
}
if (word == NULL){
	free(word);
	free(data);
	write(2, "Memory allocation failure.\n", 27);
	exit(1);
}
if (ch != ' ' && ch != EOF){
	word[word_length] = ch;
	word_length++;
}
if (ch == ' ' | ch == EOF){
	if (word != NULL){
	word = (char*)realloc(word, (word_length+1)*sizeof(char));
	word[word_length] = ' ';
	word_length++;
	}
	if (data == NULL){
	data = (char**)malloc(sizeof(char*));
	}
	else{
	data = (char**)realloc(data, (data_length+1)*sizeof(char*));
	}
	if (data == NULL){
	free(word);
	free(data);
	write(2, "Memory allocation failure.\n", 27);
	exit(1);
	}
	data[data_length] = word;
	data_length++;
	word = NULL;
	word_length = 0;
}
if (r == 0){
break;
}
}
}

qsort(data, data_length, sizeof(char*), frobcmp);
char spaceCh = ' ';
for (int i = 0; i < data_length; i++){
for (int j = 0; data[i][j] != ' '; j++){
	write(1, &data[i][j], 1);
}
write(1, &spaceCh, 1);
free(data[i]);
}
free(data);
free(word);
return 0;
}
