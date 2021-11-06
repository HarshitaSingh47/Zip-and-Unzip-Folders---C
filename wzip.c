#include<stdio.h>
#include <sys/stat.h>
#include <sys/mman.h> 
#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>
#include <stdlib.h>
#include <ctype.h>



int compress(char* line){

    int count = 1; 
    int i = 0;
    
    while (line[i]!='\0'){
        while(line[i]==line[i+1]){
            count++;
            i++;
        }
      
            fwrite(count , 1 , sizeof(count) );
            printf("%c%c",count,line[i]);
            count = 1; 
            

        i++;

    }
}


int zip(char* file){


    char* filename;
    FILE* fptr;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    int fd;
    struct stat s;
    int status;
    size_t size;
    const char * mapped;
    int i;



    filename = (char *)malloc(50 * sizeof(char));
    if( filename == NULL)
    {
        perror("Unable to allocate buffer");
        exit(1);
    }
    filename = file;
    fptr = fopen(filename,"r+");
    if(fptr == NULL)
        {
            exit(1);             
        } 


    while ((read = getline(&line, &len, fptr)) != -1) {
        if(read>1){
            
            
                // printf("%s",line);
                compress(line);
                
            }
        }
    
    return 0; 


}


int main(int argc, char* argv[]){

    //check for input

    if(argc<2) {
        printf("Enter filename to zip!\n");
        return 1;
    }
    else{
    for (int i = 1 ; i < argc ; i++){
        // printf("Reading the file : %s", argv[i] );
        zip(argv[i]);
    }
    }


    return 0;
}


