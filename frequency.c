#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//////////// VARIABLE DECLARATION ///////////
#define MAX_TEXT_INPUT 1200
#define MAX_WORD_SIZE 64
#define MAX_WORDS 50
char arr[2][MAX_WORD_SIZE][MAX_WORDS]={0};
FILE *fptr;
/////////////////////////////////////////////
////////// Descending OR Ascending //////////
int MODE = 1;
/////////////////////////////////////////////
/////////// UPPER/LOWER EASY CASE FIX ///////
static char isLegitimateChar (char c) {
	if ((c>=65 && c<=90)){
		return c+32;
		}else if (c<65 || c>122){
			return 0;
			}else if ((c>=91&&c<=96))
			{
				return 0;
			}
return c;
}
/////////////////////////////////////////////
//////////////////////// STRUCT STUFF //////////////////////////////////////
struct Trie{
	char c;
    int isLeaf;
    int appearance;
    struct Trie* character[26];
};
struct Trie* getNewTrieNode(){
    struct Trie* node = (struct Trie*)malloc(sizeof(struct Trie));
    node->isLeaf = 0;
    for (int i = 0; i < 26; i++){
        node->character[i] = NULL;
    }
    return node;
}
void insert(struct Trie *head, char* str){
    struct Trie* curr = head;
    while (*str){
        if (curr->character[*str - 'a'] == NULL){
            curr->character[*str - 'a'] = getNewTrieNode();
        }
        curr = curr->character[*str - 'a'];
        str++;
    }
    curr->isLeaf = 1;
    curr->appearance = 1;
}
void insertPlus(struct Trie *head, char* str){
    struct Trie* curr = head;
    while (*str){
        curr = curr->character[*str - 'a'];
        str++;
    }
    if ((curr->isLeaf = 1))
    {
        curr->appearance = curr->appearance+1;
    }
}
int search(struct Trie* head, char* str){
    if (head == NULL){return 0;}
    struct Trie* curr = head;
    while (*str){
        curr = curr->character[*str - 'a'];
        if (curr == NULL){return 0;}
        str++;
    }
    return curr->isLeaf;
}
int searchApp(struct Trie* head, char* str){
    if (head == NULL){return 0;}
    struct Trie* curr = head;
    while (*str){
        curr = curr->character[*str - 'a'];
        if (curr == NULL){return 0;}
        str++;
    }
    return curr->appearance;
}
int haveChildren(struct Trie* curr){
    for (int i = 0; i < 26; i++)
        if (curr->character[i]!=0){
            return 1;
        }
    return 0;
}
int isLeafNode(struct Trie* root) { 
    return root->isLeaf != 1; 
} 
//////////////// PRINT TRIE TRAVERSE ////////////////////////////////////
void printTrieContents(struct Trie *root, char *buffer, int buffIndex){
int i;
    for(i = 0; i < 26 ; i++){
        if(root->character[i] != 0){
        buffer[buffIndex] = i + 'a';
        printTrieContents(root->character[i], buffer, buffIndex + 1);
        }
        if(haveChildren(root)==0){
        	buffer[buffIndex] = 0;
        	if(strlen(buffer) > 0 && root->appearance > 0){
        		printf("[%s]: %d\n", buffer, root->appearance);
        		for (int q = 0; q < MAX_WORD_SIZE; q++){buffer[q] = '\0';}
        		buffIndex = 0;
        	}
        }   
    }
}
/////////// DELETION OF A TRIE ///////////////////////////////////////
int deletion(struct Trie* *curr, char* str){
    if (*curr == NULL){
        return 0;
    }
    if (*str)
    {
        if (*curr != NULL && (*curr)->character[*str - 'a'] != NULL &&
            deletion(&((*curr)->character[*str - 'a']), str + 1) &&
            (*curr)->isLeaf == 0)
        {
            if (!haveChildren(*curr))
            {
                free(*curr);
                (*curr) = NULL;
                return 1;
            }
            else {
                return 0;
            }
        }
    }
    if (*str == '\0' && (*curr)->isLeaf)
    {
        if (!haveChildren(*curr))
        {
            free(*curr);
            (*curr) = NULL;
            return 1; 
        }
        else
        {
            (*curr)->isLeaf = 0;
            return 0; 
        }
    }
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////   MAIN  //////////////////////////////////////////////
int main(const int argc,char *argv[]){
///////////////// FIGURING OUT IF argv[1] EQUALS TO "r" IF EXISTS //////////////////////
if (argc == 1){
	MODE = 1;
	}else if ((strcmp(argv[1], "r")==0)&&(argc>=2)){
		MODE = 0;
}else{
	MODE = 1;
}
////////////////////////////////////////////////////////////////////////////////////////
//////////////////////// READING INPUT /////////////////////////////////////////////////
fptr = stdin;
int j = 0;int i = 0;int index;
if(fptr == NULL){printf("---- Error opening the file ---- \n");}
for (int l = 0; l < MAX_WORD_SIZE; l++){arr[0][l][0] = 0;}
struct Trie* head = getNewTrieNode();
char Test[MAX_TEXT_INPUT];
char WORD[MAX_WORD_SIZE];
char LINE[MAX_TEXT_INPUT];
int is = 0;
for (int q = 0; q < MAX_WORD_SIZE; q++){WORD[q] = '\0';}
//~~~~~~~ reading ... ~~~~~~~~//
while(fgets(Test, MAX_TEXT_INPUT, fptr)!=NULL){   // ~~~ READ UNTIL NO MORE LINES
////////////////////////////////////////////////////////////////////////
///////////////////// MAIN LOOP READS TEXT UNTIL EOF ///////////////////
//  LINE - Gets single line stream
//  WORD - Focus on single word
// arr[0][n] - final result
//~~~~~~ fixes the upper letter number etc.. ~~~~~~~~~/
for (i = 0; Test[i+1] != 0; i++){if (isLegitimateChar(Test[i])==0){Test[i] = 32;}else{Test[i] = isLegitimateChar(Test[i]);}}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
strcpy(LINE, Test); //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ take line
for (int q = 0; q < MAX_WORD_SIZE; q++){WORD[q] = '\0';} //~~~~~~~~~~~~~~~~~~~~~~ clean
for (j = 0; LINE[j] != 0 && LINE[j] != '\n'&& LINE[j] != '.'  ; j++){WORD[j] = LINE[j];}  //~~~~~~~ clean
 const char s[2] = " ";
 char *token;
 token = strtok(WORD, s);
 while( token != NULL ) {
	if (search(head,token)==0){ //~~~~~~~~ if new word then insert
		insert(head,token);
    	sprintf(arr[1][is], "%d", searchApp(head,token));
    	strcpy(arr[0][is],token);
    	is++;
			}else{ //~~~~~~~~~ else if exict then apearance++
			insertPlus(head,token);
			sprintf(arr[1][is-1], "%d", searchApp(head,token));
			}
	token = strtok(NULL, s);
 	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//////////////////////////////////////////////////////////////////////
///////////// SELECTION SORT ///////////////////////////
int jendex, position;
char swap2[MAX_WORD_SIZE];
char swap;
for(index = 0; arr[0][index][0]!=0; index++){
	position=index;
	for(jendex = index + 1; jendex < 25; jendex++){
		if((strcmp(arr[0][position],arr[0][jendex]))>0)
			position=jendex;
	}
	if(position != index){
		swap=arr[1][index][0];
		arr[1][index][0]=arr[1][position][0];
		arr[1][position][0]=swap;
		strcpy(swap2,arr[0][index]);
		strcpy(arr[0][index],arr[0][position]);
		strcpy(arr[0][position],swap2);
	}
}
if (MODE==1){
//~~~~~~~~~~~~ Printing only if not NULL ~~~~~~~~~~~~~~~~~~~~~~~//
for(index = 0; index < MAX_WORDS; index++){
	if (arr[0][index][0]!=0){
	printf("%s %d\n",arr[0][index],searchApp(head,arr[0][index]));
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
}else{
//~~~~~~~~~~~ Reverse Printing only if not NULL ~~~~~~~~~~~~~~~~~//

for(index = MAX_WORDS; index > 0 ; index=index-1){
	if (arr[0][index][0]!=0){
	printf("%s %d\n",arr[0][index], searchApp(head,arr[0][index]));
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
}
return 0;
}