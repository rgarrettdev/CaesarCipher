#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define LENGTH 10000

void decrypt(char cypher[], char text[], int key);
void count(char cypher[], int alphacount[]);
void count_alpha(char cypher[], int alphacount[]);
int find_key(int alphacount[], int key);
void print_alphacount(int alphacount[]);

int main(int argc, char *argv[]){
  FILE *in_file;
  FILE *out_file;
  char text[LENGTH] = {0};
  char* cypher = NULL;
  long file_size;
  in_file = fopen(argv[1], "r");
  out_file = fopen(argv[2],"w");
  int alphacount[26] = {0};
  int i = 0;
  int key=0;
  int userchoice=0;

  if(argc !=3){
   printf("Please enter an input file and an output file such as input.txt and output.txt!\n");
  }
  if(in_file == NULL){
    printf("Couldn't open the specified input file, please check the file name\n");
    return 1;
  }

  if(out_file == NULL){
    printf("Couldn't open the specified output file, please check the file name\n\n");
    return 2;
  }
    printf("File has been successfully inputed\n");
    fseek( in_file , 0L , SEEK_END); //sets the position of the stream to the end of file.
    file_size = ftell( in_file ); //Gets the total size of the file!
    rewind( in_file ); //sets the stream back to the beginning of the stream.

//calloc() -- Allocates space for an array elements, initializes to zero and then returns a pointer to memory.
   cypher = calloc( 1, file_size+1 );
   cypher = calloc( 1, file_size+1 );
if( !cypher ) fclose(in_file),fputs("memory alloc fails",stderr),exit(1);

//Test the for a valid input file. If valid file copy the file into the cypher.
if( 1!=fread( cypher , file_size, 1 , in_file) )
  fclose(in_file),free(cypher),fputs("entire read fails",stderr),exit(1); //free(cypher)-- deallocates the previously allocated space.
  printf("File data has been stored in an cypher array!\n\nWould you like to continue to decrypt the file?\n\nEnter 1 to continue and 2 to exit: ");
  scanf("%i", &userchoice);
  if(userchoice == 1){
  userchoice = 0;   //Allows the reuse of the userchoice variable for later if statements.
  printf("Counting letters....\n");
  count(cypher, alphacount); //count the lowercase letters.
  count_alpha(cypher, alphacount); //count the uppercase letters.
  print_alphacount(alphacount); //prints the amount of times a letter occurs and gives a key.
  key = find_key(alphacount, key); //Finds the key used for decryption.
  printf("\nWould you like to use the recommended key or you own?\n\nEnter 1 to use recommended key or Enter 2 to use your own key: ");
  scanf("%i", &userchoice);
  if(userchoice == 1){
  userchoice = 0;  //Allows the reuse of the userchoice variable for later if statements.
  decrypt(cypher, text, key);  //Decryption with the recommended key.
  }
  if(userchoice == 2){
  printf("Please enter your key: \n");
  scanf("%i", &key);  //Allows user to input key.
  userchoice = 0;    //Allows the reuse of the userchoice variable for later if statements.
  decrypt(cypher, text, key);  //Decryption with the user inputed key.
  }
  printf("\nEnter 1 to save the decrypted text to the output file or Enter 2 to return to key selection phase: ");
  scanf("%i", &userchoice);
  if(userchoice == 1){
  fprintf(out_file, "%s", text);
  }
  while(userchoice == 2){   //Allows user to view a preview, and redo the decryption cycle with a different key.
  printf("Please enter your key: \n");
  scanf("%i", &key);
  userchoice = 0; //Allows the reuse of the userchoice variable for later if statements.
  decrypt(cypher, text, key); //Decryption with the user inputed key.
  printf("\nEnter 1 to save the decrypted text to the output file or Enter 2 to return to key selection phase: ");
  scanf("%i", &userchoice);
  if(userchoice == 1){
  fprintf(out_file, "%s", text);
  break;
  }
  }
  printf("\nThe file has sucessfully been decrypted!\n\n");
  free(cypher); //free(cypher)-- deallocates the previously allocated space for cypher.
  fclose(in_file);
  fclose(out_file);
  exit(0);
}
 else{
 printf("\nERROR!\nPlease follow the on screen instructions!\n");  //Error message when userinputs anything but 1 or 2.
 fclose(in_file);
 free(cypher); //free(cypher)-- deallocates the previously allocated space for cypher.
 fclose(out_file);
 exit(0);
 }
}

void decrypt(char cypher[], char text[], int key){

  int length = strlen(cypher);
  for(int i=0; i<length; i++)
  {
     if(isalpha(cypher[i])){  //test if cypher[i] has character in the alphabet.
      if(isupper(cypher[i])){ //test if cypher[i] has an uppercase character.
	text[i]=(cypher[i]-90-key) %26+90;
      }
        else{
	text[i]=(cypher[i]-122-key) %26+122; //When character in cypher[i] is lowercase.
      }
      }
	else{
       text[i]=cypher[i]; //When character is not in the alphabet.
     }
     }
     text[length] = '\0'; //Adds the null terminator at the end of the loop.
     printf("\nThis is a preview of the decrpyted text:\n \n%.100s\n", text); //Shows the first 100 bits of the text array.

}

void count(char cypher[], int alphacount[]){
  int i=0;
   while (cypher[i] != '\0') {
      if (cypher[i] >= 'a' && cypher[i] <= 'z' ) //tests for lowercase characters.
         alphacount[cypher[i] -'a']++;
      i++;
      }
}
void count_alpha(char cypher[], int alphacount[]){
  int i=0;
   while (cypher[i] != '\0') {
      if (cypher[i] >= 'A' && cypher[i] <= 'Z' ) //tests for uppercase characters.
         alphacount[cypher[i] -'A']++;
      i++;
      }
}

int find_key(int alphacount[],int key){
    int max = 0;
    int index = 0;
    int value_of_e = 'e' - 'a';
	for(int i=0; i<26; ++i){
	   if(alphacount[i] > max){  //Finds the index of the largest element in the alphacount array.
          index = i;
          max = alphacount[i];
          }
	}
        printf("\nThe index the most frequent letter is stored = %i, the letter = %c\n\n", index, index + 'a');
          key = index - value_of_e;  //key is calculated via the index of the largest element - 'e'
             if(key > 0){ //if key is greater than 0, this prevents negative numbers occuring.
                key = index - value_of_e;
             }
          else{ //if key is less than 0, this prevents negative numbers occuring later in decrpyt.
            key= 26 + key;
          }
      printf("This is the recommended key to use: %i\n",key);
  return key;
}
void print_alphacount(int alphacount[]){
  int key = 0;
  for(int i = 0; i < 26; i++){
    key = i - 4;
    if(key > 0){
    key = i - 4;
    }
    else{
    key = 26 + key;
    }
    printf("%c occurs this amount of times %i - use key %i\n", i + 'a', alphacount[i], key); //prints the frequency of the letters for a-z.
  }
}
