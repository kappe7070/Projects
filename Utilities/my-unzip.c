#define _GNU_SOURCE  //Getline()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 256



int main(int argc, char *argv[]);


void unzip(char *read){

    //fread variables

    size_t num;
    char buff[max];

    FILE *fp;

    fp = fopen(read, "rb");

    if (fp==NULL){
        fprintf(stderr,"my-zip: cannot open file '%s'\n", read);
        exit(1);
    }

    FILE *fp2;

    fp2 = fopen("kirjoitettava.txt", "w");

    if (fp2==NULL){
        fprintf(stderr, "my-zip: cannot open file '%s'\n", read);
        exit(1);
    }


    int i=0;
    //int counter=0;
    //char temp[1];

    while ((num = fread(buff , 1 , sizeof(buff), fp)) > 0 ){ //Getting line and continuing to do so until getline encounters EOF or an error



        for (i=0; i<=num; i++) {
            
            printf("%c", buff[]);
        
        }


    }
    

    fclose(fp);
    fclose(fp2);

    return;
}

int main(int argc, char *argv[]){
    

    unzip(argv[1]);


    return 0;
}