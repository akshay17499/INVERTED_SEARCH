#include"header.h"
block c;
int main(int argc,char*argv[])
{
    block b;
    int option;
    validate(&argc,argv);
    initialize_block(&b,argc);
    //check_file_already_present(&b,argc,argv);
    printf(" \n\n\n                   INVERTED SEARCH     \n\n\n");
    read_from_table(&b);
    while(1){
    printf("1.open & read file\n2.display data base\n3.search in database\n4.add another file\n5.delete file\n6.Save & exit\n");
    printf("enter option : ");
    scanf("%d",&option);
    switch(option)
    {
        case 1 : check_file_already_present(&b,argc,argv);
                 open_file_read(&b,argc,argv);break;
        case 2 : display(&b); break;
        case 3 : search(&b);break;
        case 4 : add_another_file(&b);break;
        case 5 : delete_file(&b,0);break;
        case 6 : write_in_file(&b);
                 return 0;
    }
    }
}
void validate(int*argc,char**argv)
{
    for(int i = 1;i < *argc;i++)
    {
        printf("%s\n",argv[i]);
        if(strstr(argv[i],".txt")==NULL)
        {
             shift(argv,i,*argc);
             *argc -= 1;
             i--;
            continue;
        }
        else{
            FILE*fptr = fopen(argv[i],"r");
            if(fptr==NULL)
            { 
                fclose(fptr);
                shift(argv,i,*argc);
                i--;
                *argc -= 1;
                continue;
            }
            else{
                  fseek(fptr,0,SEEK_END);
                    if(ftell(fptr)==0)
                     {
                       shift(argv,i,*argc);
                       i--;
                        *argc -= 1;
                         fclose(fptr);
                         continue; 
                     }
            }
            fclose(fptr);
        }
    }
}

void shift(char**arr,int left,int right)
{
    for(int i=left;i<right-1;i++)
    {
        arr[i]=arr[i+1];
    }
}
