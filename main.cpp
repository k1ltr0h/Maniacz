//////////////////////////////////////////////////////////////
// Maniacz script is OpenSource, anyone can use this code   //
// for whathever purpouse. Just leave your like or something//
// like that xd.                                            //
// I hope that school, college and university students can  //
// use this code for learn about chars and memory managment //
// in C/C++, regards.                                       //
//                                                          //
// Create by k1ltr0.                                        //
//////////////////////////////////////////////////////////////

#include <stdio.h> // printf
#include <stdlib.h> // EXIT_FAILURE, system()
#include <dirent.h> // DIR

#define MAX_LENGHT 1000

bool isCompressed(struct dirent* ent);
bool sameSize(char* ext, int ext_len);
char* getName(struct dirent* ent);
char* addPaths(char* arr, char* src, char* dst, bool unzip = false);

char* ext[] = {(char*)"rar", (char*)"7z", (char*)"zip"};
char* path = (char*)"";
int ext_len;

int main(int argc, char *argv[]){

    if(argc > 2){
        printf("'maniacz <path>' or just 'maniacz' for default path -> './'");
        return EXIT_FAILURE;
    }
    if(argc < 2){
        path = (char*)"./";
    }
    else{
        path = argv[1];
    }
    // argv[0] name of script
    printf("Path = %s\n", path);
    
    DIR *dir;
    struct dirent *ent;
    ext_len = sizeof(ext)/sizeof(*ext);
    char* unzip = (char*)"7z x "; // 7z 

    if(system(unzip) == EXIT_FAILURE){
        printf("Add 'rar.exe' and 'unrar.exe' to the path or may be something else happens D;\n\
in this case, please contact with code owner.");
        return EXIT_FAILURE;
    }
    
    //path = "../PSX";
    char* dir_name = NULL;
    char* move = (char*)"move ";

    char* command = NULL;
    if((dir = opendir(path)) != NULL){
        /* print all the files and directories within directory */
        while((ent = readdir(dir)) != NULL){
            if(isCompressed(ent)){

                printf("%s\n", ent->d_name);
                dir_name = getName(ent);
                //printf("%s\n", dir_name);
                command = addPaths(unzip, ent->d_name, dir_name, true);

                system(command);
                //printf("%s\n", command);

                command = addPaths(move, ent->d_name, dir_name);
                system(command);
                //printf("%s\n", command);

                delete[] command;
                delete[] dir_name;
            }
            
        }
        closedir (dir);
    } 
    else{
        /* could not open directory */
        perror("");
        return EXIT_FAILURE;
    }
}

bool isCompressed(struct dirent* ent){
    for(int i = 0; i < ent->d_namlen; i++){
        if(ent->d_name[i] == '.'){
            int len = ent->d_namlen - i - 1;
            for(int j = 0; j < ext_len; j++){
                if(sameSize(ext[j], len)){
                    for(int c = 0; c <= len; c++){
                        if(ext[j][c] != ent->d_name[i + c + 1]){
                            break;
                        }
                        else{
                            if(c == len){
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    // Else
    return false;
}

bool sameSize(char* ext_, int ext_len_){
    if(strlen(ext_) == (size_t)ext_len_){
        return true;
    }
    else{
        return false;
    }
}

char* getName(struct dirent* ent){
    char* tmp = new char[MAX_LENGHT];
    memset(tmp, 0, MAX_LENGHT*(sizeof(tmp[0])));

    for(int i = 0; i < ent->d_namlen; i++){
        if(ent->d_name[i] == '.'){
            return tmp;
        }
        tmp[i] = ent->d_name[i];
    }
    return tmp;
}

char* addPaths(char* arr, char* src, char* dst, bool unzip){
    char* tmp = new char[MAX_LENGHT];
    memset(tmp, 0, MAX_LENGHT*(sizeof(tmp[0])));

    strcat(tmp, arr);
    strcat(tmp, "\"");
    strcat(tmp, path);
    strcat(tmp, "/");
    strcat(tmp, src);
    strcat(tmp, "\" ");

    if(unzip){
        strcat(tmp, "-o");
    }

    strcat(tmp, "\"");
    strcat(tmp, path);
    strcat(tmp, "/");
    strcat(tmp, dst);
    strcat(tmp, "\"");

    return tmp;
}