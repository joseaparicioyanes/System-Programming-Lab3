/*
*******************************************************************************************************************************************
 *Purpose/Description:      The purpose of this program is to provide the user with three options, all related to words saved in a file. 
                        The first option is to display on the screen the words ordered according to the ASCII table. The second option is 
			to count the number of words in the file. The last option is to find the number of occurrences of a substring.  To 
			be able to carry out all the aforementioned operations, the program has three functions apart from the main function, 
			which is responsible for calling the other functions depending on the arguments entered by the user. The sort function 
			receives as a parameter an array of characters that represents the name of the file from which the information should 
			be read. In this function a 2-dimensional array of characters is created where the first dimension is the number of 
			words that exist in the file, and the second dimension is a fixed number for the length of the words (In this case a 
			previously defined number [50] that can be modified). Then this array is filled with all the words in the file, it is 
			ordered using a sorting algorithm, and finally it is displayed on the screen for the user. The counter function also 
			receives as a parameter an array of characters that represent the name of the file from which the information must be 
			extracted. Then it reads character by character and if it finds any of the characters that divide two words, either a 	
			space or a punctuation mark, it increases the counter and at the end it returns that number, which is the total number 	
			of words that exist in the file. Last, the function occurrences, which receives as parameters two arrays of characters, 
			one for the name of the file that contains the words and another for the substring entered by the user. This function 
			uses an array of characters of the size of the substring entered by the user, this array is updated with each new character 
			extracted from the file, and is compared with the substring entered by the user, and if they are the same, the counter 
			will be increased, the counter will be returned at the end.

 * Author’s Name: Jose Aparicio
 * Author’s Panther ID: 6186111 
 * Certification: I hereby certify that this work is my own and none of it is the work of any other person.
*********************************************************************************************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define wordSize 50                                            //defining a value to set the size of the char arrays used to store words                            

int counter(char fileName[wordSize]);                          //declaring the function counter
int occurrences(char fileName[wordSize], char substring[20]);  //declaring the function occurrences
void sort(char fileName[wordSize]);                            //declaring the function sort

int  main(int argc, char ** argv)                              //main function
{
	extern char *optarg;                                   //external variable (getopt)
	extern int optind;				       //external variable (getopt)
	int c;                                                 //variables to be used in the while loop
	char fileName[wordSize];			       //char array used to store the input file name
	char substring[wordSize];                              //char array to store de substing to find occurrences
	
	
		
	if(argc < 2){                                                                //if the program has too few arguments, diplay the user a message
		printf("Please enter the correct arguments!\n");
		printf("Try something like: mywords -s -c -f th testfile\n");
		return 0;
	}
	
	strcpy(fileName, argv[argc-1]);
	printf("\n\n");                                                            
	while ((c = getopt(argc, argv, "s :c :fls")) != -1){                        //while loop to iterate through all the arguments
		switch (c) {
			case 's':
				sort(fileName);                                     //calling the function sort to sort the words in ASCII order
				break;
			case 'c':
				printf("\n*********************\n*Number of words: %d\n*********************\n", counter(fileName)); // calling the function counter to count the number of words in the file
				break;
			case 'f':
			        strcpy(substring, argv[argc-2]);                    //asigning substring with the value entered by the user
				printf("\n*************************************************\n*Number of occurrences (*NOT CASE SENSITIVE*): %d\n*************************************************\n",occurrences(fileName, substring)); /*calling the function occurrences */
				break;
			case '?':
				break;
		}
	}
	printf("\n\n");
	
	return 0;
}

int counter(char fileName[wordSize]){                              //function to count the number of words in the file
	int count=1;
	FILE* inputFile;
	char character;
	char preChar='\0';

	if((inputFile = fopen(fileName,"r")) == NULL){            //opening the file or displaying a message if it cannot be open
		printf("Error opening %s\n", fileName);    
		exit(100);
	}

	while((character = fgetc(inputFile)) != EOF ){            //while loop to iterate through the file and count word by word
		if(character==' ' || character==',' || character=='.' || character==':' || character==';'){
			count++;
		        if ( preChar==' ' || preChar==',' || preChar== '.' || preChar==':' || preChar==';')
                		count--;
                }
		preChar=character>40?character:preChar;
	}

	if ( preChar==' ' || preChar==',' || preChar== '.' || preChar==':' || preChar==';') //decrementing the count if the las character is a punctuation mark
		count--;

	if(fclose(inputFile) == EOF){                                                       //closing the file or displaying a message if it cannot be close
		printf("Error closing %s\n", fileName);
		exit(102);
	}
	return count;                                                                       //returning count (number of words)
}


int occurrences(char fileName[wordSize], char substring[wordSize]){            //function to count the occurences
	const int size = strlen(substring);                                    //constant variable to be used as the size of the array
	char substr[size];                                                     //char array to store substring
	int counter=0;
	FILE* inputFile;
        char character;
        int i;
	strcpy(substr,substring);

	if((inputFile = fopen(fileName,"r")) == NULL){                        //opening the file or displaying a message if it cannot be open
                printf("Error opening %s\n", fileName);
                exit(100);
        }

	for(i=0; i<size;i++){
		substr[i]=fgetc(inputFile);                                   //getting the first characters on the array depending on the size of the substring entered by the user
	}

	if(strcasecmp(substr, substring)==0)                                  //comparing the substring entered by the user with the first characters on the file 
                        counter++;
	
        while((character = fgetc(inputFile)) != EOF ){                        //for loop to iterarate through the file comparing the substrings
                for(i=0;i<size-1;i++)
			substr[i]=substr[i+1];
		substr[size-1]=character;
		
		if(strcasecmp(substr, substring)==0)
                        counter++;
        }

        if(fclose(inputFile) == EOF){                                         //closing the file or displaying a message if it cannot be close
                printf("Error closing %s\n", fileName);
                exit(102);
        }

	return counter;                                                       //returning the counter
}

void sort(char fileName[wordSize]){                                           //function to sort the words in ASCII order
        FILE* inputFile;
	const int numberOfWords = counter(fileName);                          //getting the number of words in the file to create an array of that size to store the words
	char words[numberOfWords][wordSize];                                  //char 2d array to store the words
	int wordIndex = 0;
	int charIndex = 0;
	char character;
	char temp[wordSize];
	int i;
	int j;
	int boolean =0;

        if((inputFile = fopen(fileName,"r")) == NULL){                       //opening the file or displaying a message if it cannot be open
                printf("Error opening %s\n", fileName);
                exit(100);
        }

        while((character = fgetc(inputFile)) != EOF ){                      //for loop to iterate through the file storing the words in the 2d array
                if((character>=65 && character<=90 ) || (character>=97 && character<=122) || character == 39 || character == 45){
			words[wordIndex][charIndex++]=character;
			boolean=1;
		}else if (boolean==1){
			words[wordIndex][charIndex++]='\0';
			wordIndex++;
                        charIndex=0;
			boolean=0;
		}
			
                        
        }

        if(fclose(inputFile) == EOF){                                            //closing the file or displaying a message if it cannot be close
                printf("Error closing %s\n", fileName);
                exit(102);
        }
	
	for(i=0;i<numberOfWords;i++){                                            //sorting the words in the array
		for(j=i;j<numberOfWords;j++){
			if(strcmp(words[i],words[j])>0){
				strcpy(temp,words[i]);
				strcpy(words[i],words[j]);
				strcpy(words[j],temp);
			}
		}
        }
 	printf("********************************\n**Words Sorted in ASCII order.**\n********************************\n");
	for(i=0;i<numberOfWords;i++)                                             //displaying the words in ASCII order
		printf("%s\n",words[i]);
	printf("\n");
}
