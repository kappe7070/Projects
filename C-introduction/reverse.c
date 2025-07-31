#define _GNU_SOURCE  //Getline()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define max 256     //Buffer

typedef struct list list;  

struct list {

    char *row;

    struct list* next;

};

list* insert (struct list* head, char *data){       // Insert to the beginning of a linked list

    struct list *link = (struct list*) malloc(sizeof(struct list)); //New node
    link->row = (char*) malloc (sizeof(char)*strlen(data)+1);   //Malloc to equal bytes of data

    if (link->row == NULL){     //Error handling for malloc
        fprintf(stderr, "Malloc failed\n");
        exit(1);
    }

    strcpy(link->row, data);    //Copy data into node
    link->next = head;          //Link to next node
    head = link;

    return head; 
}

void print (struct list* link){ 

    while (link != NULL){   
        fprintf(stdout, "\n%s", link->row); //Print to stdout until list is empty
        link = link->next;  //Pointing to next node

    }

    return;
}

void printtofile (struct list* link, FILE *fp2){ 

    while (link != NULL){
        fprintf(fp2, "%s\n", link->row);    //Printing to file until list is empty
        link = link->next;  //Pointing to next node
    }   

    return;
}

void freelist(struct list* head){

    struct list* temporary; //Helper variable

      while (head != NULL){
        temporary = head;   
        head = head->next;
        free(temporary->row);  //Freeing data stored
        free(temporary);       //Freeing the node as a whole
    }
}

int zero(){  //When the program is run with 0 arguments given


    struct list *head = NULL;   

    int i = 1;
    printf("Type the text to be reversed, input: 0 to exit program\n");



    // Getline variables
    size_t buff = 0;
    ssize_t read = 0;
    char * input = NULL;


    while ( i == 1){

        read = getline(&input, &buff, stdin);  //Grab input

        if (read == -1){    //Checking if getline encountered an error
            fprintf(stderr, "Couldn't read stdin input");
            exit(1);
        }
        
        input[strcspn(input, "\n")] = 0;    //Remove newline

        if (strcmp(input, "0") == 0){   // Check for program terminating character
            i = 0;
        }
        else {
            head = insert(head, input); //Insert to beginning of list
        }
    }

    free(input);    //Free malloc'd

    print(head);    //Print to stdout

    freelist(head);

    return 0;
}

int one (char *lue){ //For when the program is run with one argument given

    int stop=0;
    int i=1;
    int a=0;
    int b=0;
    int counter=0;
    char rivi [max];
    char c;

    //Opening the file and error handling
    
    FILE *fp;

    fp = fopen(lue, "r");

    if (fp==NULL){
        fprintf(stderr, "Unable to open file '%s'", lue);
        exit(1);
    }


    fseek(fp, 0, SEEK_END); // Setting the file pointer to the end of the file
    fseek(fp, -2, SEEK_CUR); // Moving the pointer to the second to the last character in the file


    while (i==1){

        counter = 0;
        stop +=1;


        if(stop>=500000){
            i=0;
            printf("Infinite loop exit\n");
        }

        else if (b == 0){ //Checking if this is the first time the while loop is running (Reading the last line of the file), for adding the '\n' to the fprint 

            while (fgetc(fp) !='\n'){ // Counting how many characters are in the last line of the file

                counter +=1;
                fseek(fp, -2, SEEK_CUR); //Moving the pointer location inside the file 2 characters backwars, since fgetc moves it one forward

                if (ftell(fp) == 0 ){  //Checking if the file pointer arrived at the beginning of the file (The read file only contains one line)
                    i=0;
                    break;
                }
            }
            for (a = 0; a<=counter; a++){ //Printing the characters in the file line with the knowledge of how many characters the line has -->
                c=fgetc(fp);              //until it ends to a '\n' character. This is done with the help of the counter variable
                fprintf(stdout, "%c", c);
            }

            fprintf(stdout, "\n");
            counter = counter + 3; //Adding to the counter the value of the newline (2 characters) + 1
            fseek(fp, -counter, SEEK_CUR);  //Moving the file pointer to the second to last character of the previous line (this is why the +1 is needed)
            b+=1;
        }

        else if ( ftell(fp) != 0){ //Checking if the file pointer has arrived at the beginning of the file

            while (fgetc(fp) !='\n' ){ //Counting the number of characters in the current line

                counter +=1;
                fseek(fp, -2, SEEK_CUR); 
                if (ftell(fp) == 0 ){
                    i=0;
                    break;
                }

            }
            for (a = 0; a<=counter; a++){ //Printing the number of characters in the current line
                c=fgetc(fp);
                fprintf(stdout, "%c", c);
            }
            counter = counter + 3;
            fseek(fp, -counter, SEEK_CUR); //Moving to previous line
        }
        else {
            fgets(rivi, max, fp); //Grabbing the first line of the file
            fprintf(stdout, "%s", rivi); //Printing the first line of the file
            i=0;
        }
    }

    fclose(fp);  
    return 0;
    }

int two (char *lue, char *kirjoita){ //If the program given two arguments
    
    //Don't worry, i made this part like a normal person using: Using a linked list


    if ((strcmp(lue, kirjoita))==0){   //Checking that the read and write files are not the same file
        fprintf(stderr, "Input and Output files must be different\n");
        exit(1);
    }
  
    //File opening and error handlings

    FILE *fp;
    fp = fopen(lue, "r");

    if (fp==NULL){
        fprintf(stderr,"Unable to open file '%s'", lue);
        exit(1);
    }

    FILE *fp2;

    fp2 = fopen(kirjoita, "w");

    if (fp2==NULL){
        fprintf(stderr,"Unable to open file '%s'", kirjoita);
        exit(1);
    }

    //Getline variables

    size_t buff = 0;
    ssize_t read;
    char * input = NULL;

    // Node head
    struct list *head = NULL;


    while ( (read = getline(&input, &buff, fp)) > 0 ){ //Reading from file as long as getline() returns valid values meaning it successfully read a line from the file

        input[strcspn(input, "\n")] = 0;    //Remove newline
        head = insert(head, input);         //Insert line to the beginning of a linked list

    }
    

    printtofile(head, fp2);    
    freelist(head); 
    fclose(fp);
    fclose(fp2);
    free(input);

    return 0;
    }

int main (int argc, char* argv[]) {

    clock_t t;      //Clock variables and functions are used to measure time to completion. 
    t = clock();    //Interestingly enough, in the function one() there wasn't much of a time difference when using fgets() compared to fgetc()
                    //The function one() takes around 7 seconds on my laptop for a file containing 100k lines, when the function two() only takes about 0.1 seconds

    if (argc == 1){
        zero();
    }
    else if (argc == 2){
        one(argv[1]);
    }
    else if (argc == 3){
        two(argv[1], argv[2]);
    }
    else {
        fprintf(stderr,"Program must be used with './reverse <read.txt> <write.txt>'\n");
        exit(1);
    }
    

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("\nTime to completion %f\n", time_taken);

    return 0;
}
