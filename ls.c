#include "ls.h"

extern int errno;

void ls_command(char* tokenS, char* homeDirectory) {

    tokenS = strtok(NULL, " ");
    if (tokenS != NULL) {
        if (strcmp(tokenS, "..") == 0) {                        
            // Pointer for directory entry
            struct dirent *de;
            //Used to open the directory
            DIR *dr = opendir("..");
            while ((de = readdir(dr)) != NULL) {
                if ((strcmp(de->d_name,".") != 0) && (strcmp(de->d_name,"..") != 0)) {
                    printf("\033[01;32m%s\n", de->d_name);
                }
            }
            closedir(dr);
        } else if (strcmp(tokenS, "-a") == 0) {
            tokenS = strtok(NULL, " ");
            if (tokenS != NULL) {
                if (strcmp(tokenS, "-l") == 0) {
                    tokenS = strtok(NULL, " ");
                    if (tokenS != NULL) {
                        // Pointer for directory entry
                        struct dirent *de;
                        //Used to open the directory
                        DIR *dr = opendir(tokenS);   
                        char *filename;
                        struct passwd* owner;
                        struct group* grp;
                        while ((de = readdir(dr)) != NULL) {
                            filename = de->d_name;
                            struct stat fs;
                            int r;
                            r = stat(filename, &fs);
                            if (r == -1) {
                                fprintf(stderr,"File error\n");
                                exit(1);
                            }
                            FILE* fptr = fopen(filename, "r");
                            fseek(fptr, 0L, SEEK_END);
                            int sz = ftell(fptr);
                            fclose(fptr);
                            // file permissions belong to the st_mode member
                            // The S_ISREG() macro tests for regular files
                            if (S_ISREG(fs.st_mode)) {
                                printf("-");
                            } else if(S_ISDIR(fs.st_mode)) {
                                printf("d");
                            } else if(S_ISCHR(fs.st_mode)) {
                                printf("c");
                            } else if(S_ISBLK(fs.st_mode)) {
                                printf("b");
                            } else if(S_ISFIFO(fs.st_mode)) {
                                printf("f");
                            } else if(S_ISLNK(fs.st_mode)) {
                                printf("l");
                            } else {
                                printf("s");
                            } 
                            if (fs.st_mode & S_IRUSR) {
                                printf("r");
                            } else {
                                printf("-");
                            }
                            if (fs.st_mode & S_IWUSR) {
                                printf("w");
                            } else {
                                printf("-");
                            }
                            if (fs.st_mode & S_IXUSR) {
                                printf("x");
                            } else {
                                printf("-");
                            }
                            if (fs.st_mode & S_IRGRP) {
                                printf("r");
                            } else {
                                printf("-");
                            }
                            if (fs.st_mode & S_IWGRP) {
                                printf("w");
                            } else {
                                printf("-");
                            }
                            if (fs.st_mode & S_IXGRP) {
                                printf("x");
                            } else {
                                printf("-");
                            }
                            if (fs.st_mode & S_IROTH) {
                                printf("r");
                            } else {
                                printf("-");
                            }        
                            if (fs.st_mode & S_IWOTH) {
                                printf("w");
                            } else {
                                printf("-");
                            }        
                            if (fs.st_mode & S_IXOTH) {
                                printf("x");
                            } else {
                                printf("-");
                            }
                            owner = getpwuid(fs.st_uid);
                            grp = getgrgid(fs.st_gid);
                            printf(" %12s%12s", owner->pw_name, grp->gr_name);
                            printf(" %12d", sz);
                            struct stat attr;
                            char cwd[512];
                            getcwd(cwd, 512);
                            strcat(cwd, filename);
                            stat(cwd, &attr);
                            char month[10];
                            char date[10];
                            char time[10]; 
                            strftime(date, 10, "%d", localtime(&attr.st_mtime));
                            strftime(month, 10, "%m", localtime(&attr.st_mtime));
                            strftime(time, 10, "%H:%M", localtime(&attr.st_mtime));
                            printf(" ");
                            if (strcmp(month, "01") == 0) {
                                printf("Jan");
                            } else if (strcmp(month, "02") == 0) {
                                printf("Feb");
                            } else if (strcmp(month, "03") == 0) {
                                printf("Mar");
                            } else if (strcmp(month, "04") == 0) {
                                printf("Apr");
                            } else if (strcmp(month, "05") == 0) {
                                printf("May");
                            } else if (strcmp(month, "06") == 0) {
                                printf("Jun");
                            } else if (strcmp(month, "07") == 0) {
                                printf("Jul");
                            } else if (strcmp(month, "08") == 0) {
                                printf("Aug");
                            } else if (strcmp(month, "09") == 0) {
                                printf("Sep");
                            } else if (strcmp(month, "10") == 0) {
                                printf("Oct");
                            } else if (strcmp(month, "11") == 0) {
                                printf("Nov");
                            } else if (strcmp(month, "12") == 0) {
                                printf("Dec");
                            }
                            printf(" %s", date);
                            printf(" %s", time);
                            printf(" \033[01;32m%s\n", filename);
                        }
                        closedir(dr);                   
                    } else {
                        // Pointer for directory entry
                        struct dirent *de;
                        //Used to open the directory
                        DIR *dr = opendir(".");   
                        char *filename;
                        struct passwd* owner;
                        struct group* grp;         
                        while ((de = readdir(dr)) != NULL) {
                            filename = de->d_name;
                            struct stat fs;
                            int r;
                            r = stat(filename, &fs);
                            if (r == -1) {
                                fprintf(stderr,"File error\n");
                                exit(1);
                            }
                            FILE* fptr = fopen(filename, "r");
                            fseek(fptr, 0L, SEEK_END);
                            int sz = ftell(fptr);
                            fclose(fptr);
                            // file permissions belong to the st_mode member
                            // The S_ISREG() macro tests for regular files
                            if (S_ISREG(fs.st_mode)) {
                                printf("-");
                            } else if(S_ISDIR(fs.st_mode)) {
                                printf("d");
                            } else if(S_ISCHR(fs.st_mode)) {
                                printf("c");
                            } else if(S_ISBLK(fs.st_mode)) {
                                printf("b");
                            } else if(S_ISFIFO(fs.st_mode)) {
                                printf("f");
                            } else if(S_ISLNK(fs.st_mode)) {
                                printf("l");
                            } else {
                                printf("s");
                            } 
                            if (fs.st_mode & S_IRUSR) {
                                printf("r");
                            } else {
                                printf("-");
                            }
                            if (fs.st_mode & S_IWUSR) {
                                printf("w");
                            } else {
                                printf("-");
                            }
                            if (fs.st_mode & S_IXUSR) {
                                printf("x");
                            } else {
                                printf("-");
                            }
                            if (fs.st_mode & S_IRGRP) {
                                printf("r");
                            } else {
                                printf("-");
                            }
                            if (fs.st_mode & S_IWGRP) {
                                printf("w");
                            } else {
                                printf("-");
                            }
                            if (fs.st_mode & S_IXGRP) {
                                printf("x");
                            } else {
                                printf("-");
                            }
                            if (fs.st_mode & S_IROTH) {
                                printf("r");
                            } else {
                                printf("-");
                            }        
                            if (fs.st_mode & S_IWOTH) {
                                printf("w");
                            } else {
                                printf("-");
                            }        
                            if (fs.st_mode & S_IXOTH) {
                                printf("x");
                            } else {
                                printf("-");
                            }
                            owner = getpwuid(fs.st_uid);
                            grp = getgrgid(fs.st_gid);
                            printf(" %12s%12s", owner->pw_name, grp->gr_name);
                            printf(" %12d", sz);
                            struct stat attr;
                            char cwd[512];
                            getcwd(cwd, 512);
                            strcat(cwd, filename);
                            stat(cwd, &attr);
                            char month[10];
                            char date[10];
                            char time[10]; 
                            strftime(date, 10, "%d", localtime(&attr.st_mtime));
                            strftime(month, 10, "%m", localtime(&attr.st_mtime));
                            strftime(time, 10, "%H:%M", localtime(&attr.st_mtime));
                            printf(" ");
                            if (strcmp(month, "01") == 0) {
                                printf("Jan");
                            } else if (strcmp(month, "02") == 0) {
                                printf("Feb");
                            } else if (strcmp(month, "03") == 0) {
                                printf("Mar");
                            } else if (strcmp(month, "04") == 0) {
                                printf("Apr");
                            } else if (strcmp(month, "05") == 0) {
                                printf("May");
                            } else if (strcmp(month, "06") == 0) {
                                printf("Jun");
                            } else if (strcmp(month, "07") == 0) {
                                printf("Jul");
                            } else if (strcmp(month, "08") == 0) {
                                printf("Aug");
                            } else if (strcmp(month, "09") == 0) {
                                printf("Sep");
                            } else if (strcmp(month, "10") == 0) {
                                printf("Oct");
                            } else if (strcmp(month, "11") == 0) {
                                printf("Nov");
                            } else if (strcmp(month, "12") == 0) {
                                printf("Dec");
                            }
                            printf(" %s", date);
                            printf(" %s", time);
                            printf(" \033[01;32m%s\n", filename);
                        }
                        closedir(dr);                
                    }
                } else {
                    // Pointer for directory entry
                    struct dirent *de;
                    //Used to open the directory
                    DIR *dr = opendir(tokenS);
                    while ((de = readdir(dr)) != NULL) {
                        printf("\033[01;32m%s\n", de->d_name);
                    }
                    closedir(dr);                
                }
            } else {
                // Pointer for directory entry
                struct dirent *de;
                //Used to open the directory
                DIR *dr = opendir(".");
                while ((de = readdir(dr)) != NULL) {
                    printf("\033[01;32m%s\n", de->d_name);
                }
                closedir(dr);
            }
        } else if (strcmp(tokenS, ".") == 0) {                        
            // Pointer for directory entry
            struct dirent *de;
            //Used to open the directory
            DIR *dr = opendir(".");
            while ((de = readdir(dr)) != NULL) {
                if ((strcmp(de->d_name,".") != 0) && (strcmp(de->d_name,"..") != 0)) {
                    printf("\033[01;32m%s\n", de->d_name);
                }
            }
            closedir(dr);
        } else if (strcmp(tokenS,"~") == 0) {                        
            // Pointer for directory entry
            struct dirent *de;
            //Used to open the directory
            DIR *dr = opendir(homeDirectory);
            while ((de = readdir(dr)) != NULL) {
                if ((strcmp(de->d_name,".") != 0) && (strcmp(de->d_name,"..") != 0)) {
                    printf("\033[01;32m%s\n", de->d_name);
                }
            }
            closedir(dr);
        } else if (strcmp(tokenS, "-al") == 0 || strcmp(tokenS, "-la") == 0) {                        
            // Pointer for directory entry
            struct dirent *de;
            //Used to open the directory
            DIR *dr = opendir(".");   
            char *filename;
            struct passwd* owner;
            struct group* grp;         
            while ((de = readdir(dr)) != NULL) {
                filename = de->d_name;
                struct stat fs;
                int r;
                r = stat(filename, &fs);
                if (r == -1) {
                    fprintf(stderr,"File error\n");
                    exit(1);
                }
                FILE* fptr = fopen(filename, "r");
                fseek(fptr, 0L, SEEK_END);
                int sz = ftell(fptr);
                fclose(fptr);
                // file permissions belong to the st_mode member
                // The S_ISREG() macro tests for regular files
                if (S_ISREG(fs.st_mode)) {
                    printf("-");
                } else if(S_ISDIR(fs.st_mode)) {
                    printf("d");
                } else if(S_ISCHR(fs.st_mode)) {
                    printf("c");
                } else if(S_ISBLK(fs.st_mode)) {
                    printf("b");
                } else if(S_ISFIFO(fs.st_mode)) {
                    printf("f");
                } else if(S_ISLNK(fs.st_mode)) {
                    printf("l");
                } else {
                    printf("s");
                } 
                if (fs.st_mode & S_IRUSR) {
                    printf("r");
                } else {
                    printf("-");
                }
                if (fs.st_mode & S_IWUSR) {
                    printf("w");
                } else {
                    printf("-");
                }
                if (fs.st_mode & S_IXUSR) {
                    printf("x");
                } else {
                    printf("-");
                }
                if (fs.st_mode & S_IRGRP) {
                    printf("r");
                } else {
                    printf("-");
                }
                if (fs.st_mode & S_IWGRP) {
                    printf("w");
                } else {
                    printf("-");
                }
                if (fs.st_mode & S_IXGRP) {
                    printf("x");
                } else {
                    printf("-");
                }
                if (fs.st_mode & S_IROTH) {
                    printf("r");
                } else {
                    printf("-");
                }        
                if (fs.st_mode & S_IWOTH) {
                    printf("w");
                } else {
                    printf("-");
                }        
                if (fs.st_mode & S_IXOTH) {
                    printf("x");
                } else {
                    printf("-");
                }
                owner = getpwuid(fs.st_uid);
                grp = getgrgid(fs.st_gid);
                printf(" %12s%12s", owner->pw_name, grp->gr_name);
                printf(" %12d", sz);
                struct stat attr;
                char cwd[512];
                getcwd(cwd, 512);
                strcat(cwd, filename);
                stat(cwd, &attr);
                char month[10];
                char date[10];
                char time[10]; 
                strftime(date, 10, "%d", localtime(&attr.st_mtime));
                strftime(month, 10, "%m", localtime(&attr.st_mtime));
                strftime(time, 10, "%H:%M", localtime(&attr.st_mtime));
                printf(" ");
                if (strcmp(month, "01") == 0) {
                    printf("Jan");
                } else if (strcmp(month, "02") == 0) {
                    printf("Feb");
                } else if (strcmp(month, "03") == 0) {
                    printf("Mar");
                } else if (strcmp(month, "04") == 0) {
                    printf("Apr");
                } else if (strcmp(month, "05") == 0) {
                    printf("May");
                } else if (strcmp(month, "06") == 0) {
                    printf("Jun");
                } else if (strcmp(month, "07") == 0) {
                    printf("Jul");
                } else if (strcmp(month, "08") == 0) {
                    printf("Aug");
                } else if (strcmp(month, "09") == 0) {
                    printf("Sep");
                } else if (strcmp(month, "10") == 0) {
                    printf("Oct");
                } else if (strcmp(month, "11") == 0) {
                    printf("Nov");
                } else if (strcmp(month, "12") == 0) {
                    printf("Dec");
                }
                printf(" %s", date);
                printf(" %s", time);
                printf(" \033[01;32m%s\n", filename);
            }
            closedir(dr);
        } else if (strcmp(tokenS, "-l") == 0) {  
            tokenS = strtok(NULL, " ");
            if (tokenS != NULL) {
                if (strcmp(tokenS, "-a") == 0) {
                    tokenS = strtok(NULL, " ");
                    if (tokenS != NULL) {
                        // Pointer for directory entry
                        struct dirent *de;
                        //Used to open the directory
                        DIR *dr = opendir(tokenS);   
                        char *filename;
                        struct passwd* owner;
                        struct group* grp;         
                        while ((de = readdir(dr)) != NULL) {
                            filename = de->d_name;
                            struct stat fs;
                            int r;
                            r = stat(filename, &fs);
                            if (r == -1) {
                                fprintf(stderr,"File error\n");
                                exit(1);
                            }
                            FILE* fptr = fopen(filename, "r");
                            fseek(fptr, 0L, SEEK_END);
                            int sz = ftell(fptr);
                            fclose(fptr);
                            // file permissions belong to the st_mode member
                            // The S_ISREG() macro tests for regular files
                            if (S_ISREG(fs.st_mode)) {
                                printf("-");
                            } else if(S_ISDIR(fs.st_mode)) {
                                printf("d");
                            } else if(S_ISCHR(fs.st_mode)) {
                                printf("c");
                            } else if(S_ISBLK(fs.st_mode)) {
                                printf("b");
                            } else if(S_ISFIFO(fs.st_mode)) {
                                printf("f");
                            } else if(S_ISLNK(fs.st_mode)) {
                                printf("l");
                            } else {
                                printf("s");
                            } 
                            if (fs.st_mode & S_IRUSR) {
                                printf("r");
                            } else {
                                printf("-");
                            }
                            if (fs.st_mode & S_IWUSR) {
                                printf("w");
                            } else {
                                printf("-");
                            }
                            if (fs.st_mode & S_IXUSR) {
                                printf("x");
                            } else {
                                printf("-");
                            }
                            if (fs.st_mode & S_IRGRP) {
                                printf("r");
                            } else {
                                printf("-");
                            }
                            if (fs.st_mode & S_IWGRP) {
                                printf("w");
                            } else {
                                printf("-");
                            }
                            if (fs.st_mode & S_IXGRP) {
                                printf("x");
                            } else {
                                printf("-");
                            }
                            if (fs.st_mode & S_IROTH) {
                                printf("r");
                            } else {
                                printf("-");
                            }        
                            if (fs.st_mode & S_IWOTH) {
                                printf("w");
                            } else {
                                printf("-");
                            }        
                            if (fs.st_mode & S_IXOTH) {
                                printf("x");
                            } else {
                                printf("-");
                            }
                            owner = getpwuid(fs.st_uid);
                            grp = getgrgid(fs.st_gid);
                            printf(" %12s%12s", owner->pw_name, grp->gr_name);
                            printf(" %12d", sz);
                            struct stat attr;
                            char cwd[512];
                            getcwd(cwd, 512);
                            strcat(cwd, filename);
                            stat(cwd, &attr);
                            char month[10];
                            char date[10];
                            char time[10]; 
                            strftime(date, 10, "%d", localtime(&attr.st_mtime));
                            strftime(month, 10, "%m", localtime(&attr.st_mtime));
                            strftime(time, 10, "%H:%M", localtime(&attr.st_mtime));
                            printf(" ");
                            if (strcmp(month, "01") == 0) {
                                printf("Jan");
                            } else if (strcmp(month, "02") == 0) {
                                printf("Feb");
                            } else if (strcmp(month, "03") == 0) {
                                printf("Mar");
                            } else if (strcmp(month, "04") == 0) {
                                printf("Apr");
                            } else if (strcmp(month, "05") == 0) {
                                printf("May");
                            } else if (strcmp(month, "06") == 0) {
                                printf("Jun");
                            } else if (strcmp(month, "07") == 0) {
                                printf("Jul");
                            } else if (strcmp(month, "08") == 0) {
                                printf("Aug");
                            } else if (strcmp(month, "09") == 0) {
                                printf("Sep");
                            } else if (strcmp(month, "10") == 0) {
                                printf("Oct");
                            } else if (strcmp(month, "11") == 0) {
                                printf("Nov");
                            } else if (strcmp(month, "12") == 0) {
                                printf("Dec");
                            }
                            printf(" %s", date);
                            printf(" %s", time);
                            printf(" \033[01;32m%s\n", filename);
                        }
                        closedir(dr);                   
                    } else {
                        // Pointer for directory entry
                        struct dirent *de;
                        //Used to open the directory
                        DIR *dr = opendir(".");   
                        char *filename;
                        struct passwd* owner;
                        struct group* grp;         
                        while ((de = readdir(dr)) != NULL) {
                            filename = de->d_name;
                            struct stat fs;
                            int r;
                            r = stat(filename, &fs);
                            if (r == -1) {
                                fprintf(stderr,"File error\n");
                                exit(1);
                            }
                            FILE* fptr = fopen(filename, "r");
                            fseek(fptr, 0L, SEEK_END);
                            int sz = ftell(fptr);
                            fclose(fptr);
                            // file permissions belong to the st_mode member
                            // The S_ISREG() macro tests for regular files
                            if (S_ISREG(fs.st_mode)) {
                                printf("-");
                            } else if(S_ISDIR(fs.st_mode)) {
                                printf("d");
                            } else if(S_ISCHR(fs.st_mode)) {
                                printf("c");
                            } else if(S_ISBLK(fs.st_mode)) {
                                printf("b");
                            } else if(S_ISFIFO(fs.st_mode)) {
                                printf("f");
                            } else if(S_ISLNK(fs.st_mode)) {
                                printf("l");
                            } else {
                                printf("s");
                            } 
                            if (fs.st_mode & S_IRUSR) {
                                printf("r");
                            } else {
                                printf("-");
                            }
                            if (fs.st_mode & S_IWUSR) {
                                printf("w");
                            } else {
                                printf("-");
                            }
                            if (fs.st_mode & S_IXUSR) {
                                printf("x");
                            } else {
                                printf("-");
                            }
                            if (fs.st_mode & S_IRGRP) {
                                printf("r");
                            } else {
                                printf("-");
                            }
                            if (fs.st_mode & S_IWGRP) {
                                printf("w");
                            } else {
                                printf("-");
                            }
                            if (fs.st_mode & S_IXGRP) {
                                printf("x");
                            } else {
                                printf("-");
                            }
                            if (fs.st_mode & S_IROTH) {
                                printf("r");
                            } else {
                                printf("-");
                            }        
                            if (fs.st_mode & S_IWOTH) {
                                printf("w");
                            } else {
                                printf("-");
                            }        
                            if (fs.st_mode & S_IXOTH) {
                                printf("x");
                            } else {
                                printf("-");
                            }
                            owner = getpwuid(fs.st_uid);
                            grp = getgrgid(fs.st_gid);
                            printf(" %12s%12s", owner->pw_name, grp->gr_name);
                            printf(" %12d", sz);
                            struct stat attr;
                            char cwd[512];
                            getcwd(cwd, 512);
                            strcat(cwd, filename);
                            stat(cwd, &attr);
                            char month[10];
                            char date[10];
                            char time[10]; 
                            strftime(date, 10, "%d", localtime(&attr.st_mtime));
                            strftime(month, 10, "%m", localtime(&attr.st_mtime));
                            strftime(time, 10, "%H:%M", localtime(&attr.st_mtime));
                            printf(" ");
                            if (strcmp(month, "01") == 0) {
                                printf("Jan");
                            } else if (strcmp(month, "02") == 0) {
                                printf("Feb");
                            } else if (strcmp(month, "03") == 0) {
                                printf("Mar");
                            } else if (strcmp(month, "04") == 0) {
                                printf("Apr");
                            } else if (strcmp(month, "05") == 0) {
                                printf("May");
                            } else if (strcmp(month, "06") == 0) {
                                printf("Jun");
                            } else if (strcmp(month, "07") == 0) {
                                printf("Jul");
                            } else if (strcmp(month, "08") == 0) {
                                printf("Aug");
                            } else if (strcmp(month, "09") == 0) {
                                printf("Sep");
                            } else if (strcmp(month, "10") == 0) {
                                printf("Oct");
                            } else if (strcmp(month, "11") == 0) {
                                printf("Nov");
                            } else if (strcmp(month, "12") == 0) {
                                printf("Dec");
                            }
                            printf(" %s", date);
                            printf(" %s", time);
                            printf(" \033[01;32m%s\n", filename);
                        }
                        closedir(dr);                
                    }
                } else {
                    // Pointer for directory entry
                    struct dirent *de;
                    //Used to open the directory
                    DIR *dr = opendir(tokenS);   
                    char *filename;
                    struct passwd* owner;
                    struct group* grp;         
                    while ((de = readdir(dr)) != NULL) {
                        if ((strcmp(de->d_name,".") != 0) && (strcmp(de->d_name,"..") != 0)) {
                            filename = de->d_name;
                            struct stat fs;
                            int r;
                            r = stat(filename, &fs);
                            if (r == -1) {
                                fprintf(stderr,"File error\n");
                                exit(1);
                            }
                            FILE* fptr = fopen(filename, "r");
                            fseek(fptr, 0L, SEEK_END);
                            int sz = ftell(fptr);
                            fclose(fptr);
                            // struct group *grp;
                            // struct passwd *pwd;
                            // grp = getgrgid(gid);
                            // pwd = getpwuid(uid);
                            // file permissions belong to the st_mode member
                            // The S_ISREG() macro tests for regular files
                            if (S_ISREG(fs.st_mode)) {
                                printf("-");
                            } else if(S_ISDIR(fs.st_mode)) {
                                printf("d");
                            } else if(S_ISCHR(fs.st_mode)) {
                                printf("c");
                            } else if(S_ISBLK(fs.st_mode)) {
                                printf("b");
                            } else if(S_ISFIFO(fs.st_mode)) {
                                printf("f");
                            } else if(S_ISLNK(fs.st_mode)) {
                                printf("l");
                            } else {
                                printf("s");
                            } 
                            if (fs.st_mode & S_IRUSR) {
                                printf("r");
                            } else {
                                printf("-");
                            }
                            if (fs.st_mode & S_IWUSR) {
                                printf("w");
                            } else {
                                printf("-");
                            }
                            if (fs.st_mode & S_IXUSR) {
                                printf("x");
                            } else {
                                printf("-");
                            }
                            if (fs.st_mode & S_IRGRP) {
                                printf("r");
                            } else {
                                printf("-");
                            }
                            if (fs.st_mode & S_IWGRP) {
                                printf("w");
                            } else {
                                printf("-");
                            }
                            if (fs.st_mode & S_IXGRP) {
                                printf("x");
                            } else {
                                printf("-");
                            }
                            if (fs.st_mode & S_IROTH) {
                                printf("r");
                            } else {
                                printf("-");
                            }        
                            if (fs.st_mode & S_IWOTH) {
                                printf("w");
                            } else {
                                printf("-");
                            }        
                            if (fs.st_mode & S_IXOTH) {
                                printf("x");
                            } else {
                                printf("-");
                            }
                            // printf(" %s", grp->gr_name);
                            // printf(" %s", pwd->pw_name);
                            owner = getpwuid(fs.st_uid);
                            grp = getgrgid(fs.st_gid);
                            printf(" %12s%12s", owner->pw_name, grp->gr_name);
                            printf(" %12d", sz);
                            struct stat attr;
                            char cwd[512];
                            getcwd(cwd, 512);
                            strcat(cwd, filename);
                            stat(cwd, &attr);
                            char month[10];
                            char date[10];
                            char time[10]; 
                            strftime(date, 10, "%d", localtime(&attr.st_mtime));
                            strftime(month, 10, "%m", localtime(&attr.st_mtime));
                            strftime(time, 10, "%H:%M", localtime(&attr.st_mtime));
                            printf(" ");
                            if (strcmp(month, "01") == 0) {
                                printf("Jan");
                            } else if (strcmp(month, "02") == 0) {
                                printf("Feb");
                            } else if (strcmp(month, "03") == 0) {
                                printf("Mar");
                            } else if (strcmp(month, "04") == 0) {
                                printf("Apr");
                            } else if (strcmp(month, "05") == 0) {
                                printf("May");
                            } else if (strcmp(month, "06") == 0) {
                                printf("Jun");
                            } else if (strcmp(month, "07") == 0) {
                                printf("Jul");
                            } else if (strcmp(month, "08") == 0) {
                                printf("Aug");
                            } else if (strcmp(month, "09") == 0) {
                                printf("Sep");
                            } else if (strcmp(month, "10") == 0) {
                                printf("Oct");
                            } else if (strcmp(month, "11") == 0) {
                                printf("Nov");
                            } else if (strcmp(month, "12") == 0) {
                                printf("Dec");
                            }
                            printf(" %s", date);
                            printf(" %s", time);
                            printf(" \033[01;32m%s\n", filename);
                        }
                    }
                    closedir(dr);                
                }
            } else {                   
                // Pointer for directory entry
                struct dirent *de;
                //Used to open the directory
                DIR *dr = opendir(".");   
                char *filename;
                struct passwd* owner;
                struct group* grp;         
                while ((de = readdir(dr)) != NULL) {
                    if ((strcmp(de->d_name,".") != 0) && (strcmp(de->d_name,"..") != 0)) {
                        filename = de->d_name;
                        struct stat fs;
                        int r;
                        r = stat(filename, &fs);
                        if (r == -1) {
                            fprintf(stderr,"File error\n");
                            exit(1);
                        }
                        FILE* fptr = fopen(filename, "r");
                        fseek(fptr, 0L, SEEK_END);
                        int sz = ftell(fptr);
                        fclose(fptr);
                        // struct group *grp;
                        // struct passwd *pwd;
                        // grp = getgrgid(gid);
                        // pwd = getpwuid(uid);
                        // file permissions belong to the st_mode member
                        // The S_ISREG() macro tests for regular files
                        if (S_ISREG(fs.st_mode)) {
                            printf("-");
                        } else if(S_ISDIR(fs.st_mode)) {
                            printf("d");
                        } else if(S_ISCHR(fs.st_mode)) {
                            printf("c");
                        } else if(S_ISBLK(fs.st_mode)) {
                            printf("b");
                        } else if(S_ISFIFO(fs.st_mode)) {
                            printf("f");
                        } else if(S_ISLNK(fs.st_mode)) {
                            printf("l");
                        } else {
                            printf("s");
                        } 
                        if (fs.st_mode & S_IRUSR) {
                            printf("r");
                        } else {
                            printf("-");
                        }
                        if (fs.st_mode & S_IWUSR) {
                            printf("w");
                        } else {
                            printf("-");
                        }
                        if (fs.st_mode & S_IXUSR) {
                            printf("x");
                        } else {
                            printf("-");
                        }
                        if (fs.st_mode & S_IRGRP) {
                            printf("r");
                        } else {
                            printf("-");
                        }
                        if (fs.st_mode & S_IWGRP) {
                            printf("w");
                        } else {
                            printf("-");
                        }
                        if (fs.st_mode & S_IXGRP) {
                            printf("x");
                        } else {
                            printf("-");
                        }
                        if (fs.st_mode & S_IROTH) {
                            printf("r");
                        } else {
                            printf("-");
                        }        
                        if (fs.st_mode & S_IWOTH) {
                            printf("w");
                        } else {
                            printf("-");
                        }        
                        if (fs.st_mode & S_IXOTH) {
                            printf("x");
                        } else {
                            printf("-");
                        }
                        // printf(" %s", grp->gr_name);
                        // printf(" %s", pwd->pw_name);
                        owner = getpwuid(fs.st_uid);
                        grp = getgrgid(fs.st_gid);
                        printf(" %12s%12s", owner->pw_name, grp->gr_name);
                        printf(" %12d", sz);
                        struct stat attr;
                        char cwd[512];
                        getcwd(cwd, 512);
                        strcat(cwd, filename);
                        stat(cwd, &attr);
                        char month[10];
                        char date[10];
                        char time[10]; 
                        strftime(date, 10, "%d", localtime(&attr.st_mtime));
                        strftime(month, 10, "%m", localtime(&attr.st_mtime));
                        strftime(time, 10, "%H:%M", localtime(&attr.st_mtime));
                        printf(" ");
                        if (strcmp(month, "01") == 0) {
                            printf("Jan");
                        } else if (strcmp(month, "02") == 0) {
                            printf("Feb");
                        } else if (strcmp(month, "03") == 0) {
                            printf("Mar");
                        } else if (strcmp(month, "04") == 0) {
                            printf("Apr");
                        } else if (strcmp(month, "05") == 0) {
                            printf("May");
                        } else if (strcmp(month, "06") == 0) {
                            printf("Jun");
                        } else if (strcmp(month, "07") == 0) {
                            printf("Jul");
                        } else if (strcmp(month, "08") == 0) {
                            printf("Aug");
                        } else if (strcmp(month, "09") == 0) {
                            printf("Sep");
                        } else if (strcmp(month, "10") == 0) {
                            printf("Oct");
                        } else if (strcmp(month, "11") == 0) {
                            printf("Nov");
                        } else if (strcmp(month, "12") == 0) {
                            printf("Dec");
                        }
                        printf(" %s", date);
                        printf(" %s", time);
                        printf(" \033[01;32m%s\n", filename);
                    }
                }
                closedir(dr);
            }
        }
    } else {
        // Pointer for directory entry
        struct dirent *de;
        //Used to open the directory
        DIR *dr = opendir(".");
        while ((de = readdir(dr)) != NULL) {
            if ((strcmp(de->d_name,".") != 0) && (strcmp(de->d_name,"..") != 0)) {
                printf("\033[01;32m%s\n", de->d_name);
            }
        }
        closedir(dr);
    }
}