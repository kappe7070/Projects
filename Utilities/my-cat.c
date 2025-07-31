#define _GNU_SOURCE  //Getline()
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]);


void print(char *read){

    //Getline variables

    size_t buff = 0;
    ssize_t num;
    char * input = NULL;



    FILE *fp;

    fp = fopen(read, "r");

    if (fp==NULL){
        fprintf(stderr,"Unable to open file '%s'", read);
        exit(1);
    }

    while ((num = getline(&input, &buff, fp)) > 0 ){ //getting line from text and continuing to do so until getline encounters EOF or an error

        printf("%s", input);

    }

    if (num==-1){
        fprintf(stderr,"Getline encountered an error");
    }


    // Freeing memory and closing the file
    free(input);
    fclose(fp);

    return;
}


int main(int argc, char* argv[]){


    if (argc == 1){ // Checking if the user provided other inputs than just the execute command
        fprintf(stderr, "my-cat usage: ./my-cat <file>");
    }

    int i = 1;


    for (i=1; argc>i; i++){
        print(argv[i]);

    }


    return 0;
}