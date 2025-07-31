#define _GNU_SOURCE  //Getline()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 256


int main(int argc, char *argv[]);


void compress(char *argv[], int argc){

    //Getline variables

    size_t buff = 0;
    ssize_t num;
    char * input = NULL;


    // Variables for for loops and counting the characters
    int j=1;
    int i=0;
    int counter=0;


    // File pointers for read and write
    FILE *fp;
    FILE *fp2;

    // To test if pipe > is used for an output file
    char test='>';
    int a=(int)test; //Assigning the pipe character an ascii value for comparison

    for (j=2; j<argc; j++){     //Going trough all the terminal inputs

        int b=(int)argv[j][0];  //Assigning terminal inputs first characters ascii values. This is done to avoid issues with strcmp null comparisons
                                //which cause segmentation faults

        if ( a == b){   //If > pipe is used
            
            fp2 = fopen(argv[2], "wb"); //Open file for writing

            if (fp2==NULL){     //Error handling
                fprintf(stderr,"my-zip: cannot open file '%s'\n", argv[j]);
                exit(1);
            }
            j=-1;   //Assigning negative value to check if writing elsewhere than stdout
        }
    }

    if (j != -1){   //If not writing to file then assigning write output to stdout
        fp2=stdout;
    }
    
    for (j=1; j<argc; j++){

        fp = fopen(argv[j], "r");   //Opening read file in a format that supports going trough multiple files

        if (fp==NULL){
            fprintf(stderr, "my-zip: cannot open file '%s'\n", argv[j]);
            exit(1);
        }

        while ((num = getline(&input, &buff, fp)) > 0 ){ //Getting line from text and continuing to do so until getline encounters EOF or an error
            
            input[strcspn(input, "\n")] = 0;    //Remove newline
            counter=1;

            for (i=1; i<=num; i++) {    //Going trough each line
            

                if (input[i]==input[i-1]){  //Checking if character matches to previous
                    
                    counter +=1;

                }
            
                else {  //If character does not match previous, then writing the encoded version to file or stdout
                    
                    fwrite(&counter, sizeof(int), 1, fp2);
                    fwrite(&input[i-1], sizeof(char), 1, fp2);
                    counter = 1;

                }
            }

            fwrite("\n", sizeof(char), 1, fp2);  //Writing newline to file or stdout after going trough the whole line

            free(input);    //Freeing and initializing input for the use of getline after each iteration
            input=NULL;
        }

        fclose(fp); //Closing file here incase multiple files to encode were given
    
    }

    free(input);
    fclose(fp2);

    return;
}

int main(int argc, char *argv[]){

    if (argc == 1){
        fprintf(stderr, "my-zip: file1 [file2...]\n");
        exit(1);
    }
    else {
        compress(argv, argc);
    }

    return 0;
}