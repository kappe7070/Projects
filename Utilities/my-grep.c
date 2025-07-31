#define _GNU_SOURCE  //Getline()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int main(int argc, char* argv[]);


void search(char *look, char *read){

    //Getline variables

    size_t buff = 0;
    ssize_t num;
    char * input = NULL;



    FILE *fp;

    fp = fopen(read, "r");

    if (fp==NULL){
        fprintf(stderr,"my-grep: cannot open file '%s'\n", read);
        exit(1);
    }

    while ((num = getline(&input, &buff, fp)) > 0 ){ //Getting line from text and continuing to do so until getline encounters EOF or an error

        if (strstr(input, look)){   //Checking for substring 'look' inside string 'input'
            printf("%s", input);    //If found print current line
        }

    }

    //if (num==-1){
      //  fprintf(stderr,"Getline encountered an error");
    //}


    //Freeing memory and closing the file
    free(input);
    fclose(fp);

    return;
}


int main(int argc, char* argv[]){


    if (argc == 1){ //Checking if the user provided other inputs than just the execute command
        fprintf(stderr, "my-cat usage: ./my-grep <file> <term>");
    }

    int i;

    for (i=2; argc>i; i++){     //Repeating the search if multiple files were provided
        search(argv[1], argv[i]);
    }

    return 0;
}