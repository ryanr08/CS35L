#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){

if (argc != 3){
fprintf(stderr, "Invalid number of arguments. Exactly 2 arguments are allowed.");
exit(1);
}

char* from = argv[1];
char* to = argv[2];
int from_length = 0;
int to_length = 0;

while(from[from_length] != '\0'){
from_length++;
}
while(to[to_length] != '\0'){
to_length++;
}
if (from_length != to_length){
fprintf(stderr, "The length of the two arguments must be the same.");
exit(1);
}

for (int i = 0; i < from_length; i++){
for (int j = i + 1; j < from_length; j++){
if (from[i] == from[j]){
fprintf(stderr, "Duplicate bytes are not allowed in the first argument.");
exit(1);
}
}
}

while(!feof(stdin)){
char ch = getchar();
if (ferror(stdin)){
fprintf(stderr, "Error with reading from standard input.");
exit(1);
}
for (int i = 0; i < from_length; i++){
if (ch == from[i]){
ch = to[i];
break;
}
}
putchar(ch);
}

return 0;
}
