#include"header.h"

void initialize_block(block*b,int argc)
{
   char u = 'A';
   for(int i=0;i<26;i++)
   {
     b->upper[i] = u++;
     b->list[i] = NULL;
   }
}

bool open_file(int argc,char*argv[])
{
    FILE*fptr;
    for(int i=1;i<argc;i++)
    {
       fptr = fopen (argv[i],"r");
       if(fptr==NULL)
       {
        printf("error in opening file\n");
        return false;
       }
       fclose(fptr);
    }
    return true;
}
node* create_node(char*temp,char*filename)
{
   node*newnode = malloc(sizeof(node));
   newnode->next =NULL;
   int size = strlen(temp);
   newnode->word = malloc((size+1)*sizeof(char));
   strcpy(newnode->word,temp);
   newnode->File =  malloc(sizeof(file_d));
   newnode->File->count = 1;
   size = strlen(filename);
   newnode->File->file_name = malloc(((size+1)*sizeof(char)));
   strcpy(newnode->File->file_name,filename);
   newnode->File->next = NULL;
   return newnode;
}

file_d* create_file_block(char*file_name)
{
    file_d*newnode = malloc(sizeof(file_d));
    newnode->count = 1;
    int size = strlen(file_name);
    newnode->file_name = malloc((size+1)*sizeof(char));
    strcpy(newnode->file_name,file_name);
    newnode->next=NULL;
    return newnode;
}

void add_to_block(block*b,char*word)
{
    char first_character = *word;
       //printf("add_to_block : %s\n",word);

    for(int i=0;i<26;i++)
    { //printf("%d",i);
        if(b->upper[i]==first_character||b->upper[i]+32==first_character)
        {
            if(b->list[i]==NULL)
            {
                b->list[i] = create_node(word,b->crrent_file_name);
                return; //changed here
            }
            else{
                node*temp = b->list[i],*prev;
                while(temp!=NULL)
                {
                    if(strcmp(temp->word,word)==0)
                    {
                        file_d*file = temp->File;
                        while(file->next!=NULL)
                        {
                            if(strcmp(file->file_name,b->crrent_file_name)==0)
                            { 
                                file->count++;
                                return;
                            }
                            file = file->next;
                        }
                        if(strcmp(file->file_name,b->crrent_file_name)==0)
                        {   
                            file->count++;
                            return;
                        }
                        else{
                            file->next = create_file_block(b->crrent_file_name);
                            return;
                        }

                    }
                    else if(strcmp(temp->word,word)>0)
                    {
                        node*newnode = create_node(word,b->crrent_file_name);
                        if(temp==b->list[i])
                        {
                            b->list[i] = newnode;
                            newnode->next = temp;
                            return;
                        }
                        else{
                           prev->next = newnode;
                           newnode->next = temp;
                           return;
                        }
                    }
                    prev = temp;
                    temp = temp->next;
                }
                prev->next = create_node(word,b->crrent_file_name);
                //printf("akshayyyyyyyyyyyyyyyyyyy");
                return;
            }
        }
    }
}

void find_add(block*b,char* arr,int size)
{
    int flag=0;
    char temp[100];  //to store words
    int k=0;
    for(int i=0;i<size;i++)
    {
        if(arr[i]!=' '&&arr[i]!='\n'&&arr[i]!=','&&arr[i]!='.')
        {
          temp[k++]= arr[i];
          flag=1;
        }
        else if(flag==1)
        {
           temp[k]='\0';
           //printf("finf_add->%s\n",temp);
           add_to_block(b,temp);
           k=0;
           flag=0;
        }
    }
    temp[k]='\0';
    add_to_block(b,temp);
}

void read_find(block*b,FILE*fptr)
{
    char arr[1024];
    int size;
    while((size=fread(arr,1,1024,fptr))>0)
    {
      find_add(b,arr,size);
    }
}

bool open_file_read(block*b,int argc,char*argv[])
{
   // printf("aksjay\n");
    FILE*fptr;
     int flag=0;
    for(int i = 1; i < argc; i++)
    {
        flag=1;
        strcpy(b->crrent_file_name,argv[i]);
         if(check_file_already_present(b,argc,argv)==false){
            fptr = fopen(argv[i],"r");
            read_find(b,fptr);
            fclose(fptr);
         }
         else{
           // printf("vishnu");
            modify_database(b);
           // printf("anjana\n");
            fptr = fopen(argv[i],"r");
            read_find(b,fptr);
            fclose(fptr);
         }
    }
    if(flag==0)
    {
        printf("\n\n      user hasnt entered any file\n\n");
        return false ;
    }
    printf("\nfiles opened and read & created table successfully \n\n");
}

void display(block*b)
{
    for(int i =0;i<26;i++)
    {
        printf("\n\n%c\n\n",b->upper[i]);
        if(b->list[i]!=NULL)
        {
            node*temp = b->list[i];
            while(temp!=NULL)
            {
                printf("%s : ",temp->word);
                file_d*file = temp->File;
                while(file!=NULL)
                {
                    printf("%s(%d) ",file->file_name,file->count);
                    file =file->next;
                    if(file!=NULL)
                    printf(", ");
                }
                printf("\n");
                temp = temp->next;
            }
        }
        else{
            printf("no word exist under this\n");
        }
    }
    printf("\n");
}
void max_occurance(file_d*file)
{
    int max=0;
    char file_name[30];
    int count = 0;
    while(file!=NULL)
    {
       if(max<file->count)
       {
           strcpy(file_name ,file->file_name);
           count = file->count;
       }
       file = file->next;
    }
    printf("file name : %s  \ncount = %d\n",file_name,count);

}

void min_occurance(file_d*file)
{
    int min = file->count;
    char file_name[30];
    int count;
    file = file->next;
    while(file!=NULL)
    {
        if(min>file->count)
        {
           strcpy(file_name ,file->file_name);
           count = file->count;
        }
       file = file->next;     
    }
      printf("file name : %s  \ncount = %d\n",file_name,count);
}

void all_occurance(file_d*file)
{
    while(file!=NULL)
    {
        printf("file name : %s count = %d\n",file->file_name,file->count);
    }
}
void search(block*b)
{
    printf("enter the word u want to search : ");
    char word[100];
    scanf("%s",word);
    for(int i=0;i<26;i++)
    {
       if(*word==b->upper[i]||*word==b->upper[i]+32)
       {
        node*temp = b->list[i];
        while(temp!=NULL)
        {
            if(strcmp(temp->word,word)==0)
            {
                int option;
                printf("1.max occurance in which file\n2.min occurance in which file\n3.all details\nenter : ");
                scanf("%d",&option);
                switch(option)
                {
                    case 1 : max_occurance(temp->File);return ;
                    case 2 : min_occurance(temp->File);return;
                    case 3 : all_occurance(temp->File);return;
                }
            }
        }
       }
    }
}

void write_in_file(block*b)
{   
     FILE*fptr = fopen("hash.txt","w");
     if(fptr==NULL)
     {
        printf("file open failed\n");
        return;
     }
     for(int i=0;i<26;i++)
     {
        if(b->list!=NULL){
         fprintf(fptr,"%c\n",b->upper[i]);
      node*temp = b->list[i];
      while(temp!=NULL)
      {
        fprintf(fptr,"%s : ",temp->word);
        file_d*file = temp->File;
        while(file!=NULL)
        {
            fprintf(fptr,"%s-%d  ",file->file_name,file->count);
            file=file->next;
        }
        temp =temp->next;
        fprintf(fptr,"\n");
      }
     }
     }
     fclose(fptr);
}

void read_from_table(block*b)
{
    int count=0;
    FILE*fptr = fopen("hash.txt","r");
    char ch ;
    int k=0;
    char arr[100];
    int i=0;
    char temp[100];//to store words
    file_d*file;
    while((ch=fgetc(fptr))!=EOF)
    {
        if(ch!='\n'&&ch!=' '&&ch!=':'&&ch!='-')
        {
           arr[k++]=ch;
          //printf("%c",ch);
        }
        else if(b->upper[i]==arr[k-1])
        {
            i++;
            k=0;
           continue;
        }
        else{
            //printf("akshayvfbn");
            if(k==0||arr[0]==':')
            {
                k=0;
                  continue;
            }
           
             arr[k]='\0';
             //printf("\n%s",arr);
             if(strstr(arr,".txt")==NULL&&(arr[0]<48||arr[0]>58))
             {
                strcpy(temp,arr);
                //printf("\ntemp->%s",temp);
               
             }
            else if(strstr(arr,".txt")!=NULL)
            {
              // printf("\nanjana->%s         %s\n",temp,arr);
                strcpy(b->crrent_file_name ,arr);
                add_to_block(b,temp);                              //t)emp contains word
              node*word_node=b->list[i-1];
              //printf("i->%d\n",i-1);
              //printf("%s",b->list[i-1]->word);
              while(word_node->next!=NULL)
              {
                word_node=word_node->next;
              }
              file = word_node->File;
              //printf()
            }
            else
            {
               // printf("count->%d",atoi(arr));
               while(file->next!=NULL)
               {
                file=file->next;
               }
               file->count = atoi(arr);
              // printf("count : %d\n",file->count);
            }
           
            k=0;
            //printf("%s\n",arr);
        }
    }
    fclose(fptr);
    for(int i=0;i<26;i++)
    {
          if(b->list[i]==NULL)
          count++;
    }
    if(count==26)
    {
        printf("\n\n         data base is empty           \n\n");
        return;
    }
}

void add_another_file(block*b)
{
    printf("enter another file name : ");
    char file_name[40];
    scanf("%s",file_name);
    char*ptr[]={"./a.exe",file_name}; 
    strcpy(b->crrent_file_name,file_name);
    FILE*fptr = fopen(file_name,"r");
    if(fptr==NULL)
    {
        printf(" file not present in folder\n");
        fclose(fptr);
        return;
    }
    if(strstr(ptr[1],".txt")==NULL)
    {
        printf("file entered is not .txt file\n");
        return;
    }
    if(check_file_already_present(b,2,ptr)==true)
    {
        printf("file already present\n");
        return;
    }
    read_find(b,fptr);
    fclose(fptr);
}

bool check_file_already_present(block*b,int argc,char*argv[])
{
    FILE*fptr1 = fopen("file_table.txt","a+");
    char file_name[40];
    char ch;
    int i=0;
    int count_arr[argc+1];
    for(int j=0;j<argc+1;j++)
    count_arr[j]=j;
    int j=1;
    int flag=1;
    fseek(fptr1,0,SEEK_SET);
      //printf("vishnu\n");
    while((ch=fgetc(fptr1))!=EOF)
    {
        if(ch!='\n'&&ch!=EOF)
        {
          file_name[i++] = ch;
        }
        else{
         file_name[i] = '\0';
         i=0;
         for(int k=1;k<argc;k++)
         {
            if(strcmp(file_name,argv[k])==0)
            {
                fclose(fptr1);
                return true;
            }
            if(flag==1)
            count_arr[j++]=k;
         }
         flag=0;
        }   
    }
  
    if(flag==1)
    j=argc;
    for(int k=1;k<j;k++)
    {
        fprintf(fptr1,"%s\n",argv[count_arr[k]]);
        //printf("%s",argv[count_arr[k]]);
    }
    fclose(fptr1);
    return false;
    
}

void delete_file(block*b,int identifier)
{

   FILE*fptr = fopen("file_table.txt","r");
   if(fptr==NULL)
   printf("failed to open file\n");
   char**files = malloc(100*sizeof(char*));
   char f_name[40];
   char ch;
   int i=0;
   int k=0;
   while((ch=fgetc(fptr))!=EOF)
   {
    if(ch!='\n'&&ch!=EOF)
    {
        f_name[i++]=ch;
    }
    else{
        f_name[i]='\0';
        i=0;
        int size = strlen(f_name);
        *(files+k) = malloc((size+1)*sizeof(char));
        strcpy(*(files+k++),f_name);
       // printf("%s",*(files+k-1));
    }
   }
   fclose(fptr);
   fptr = fopen("file_table.txt","w");
   if(fptr==NULL)
   {
    printf("failed to open file\n");
    return;
   }
   if(identifier==0)
   {
      for(i=0;i<k;i++)
      {
       printf("%d. %s\n",i+1,*(files+i));
      }
      int n;
      printf("enter the file u want to delete : ");
      scanf("%d",&n);
      for(int i=0;i<k;i++)
      {
         if((i+1)!=n)
         {
           fprintf(fptr,"%s\n",*(files+i));
         }
      }
       strcpy(b->crrent_file_name,*(files+n-1));
   }
   else if(identifier==1)
   {
   }
   modify_database(b); 
   fclose(fptr);  
}

void modify_database(block*b)
{
    node*temp ,*prev;
   //printf("%s",b->crrent_file_name);
   for(int i=0;i<26;i++)
   {
      temp = b->list[i];
      while(temp!=NULL)
      {
        file_d* file = temp->File,*prev_file=NULL;
 
        while(file!=NULL)
        {
            if(strcmp(file->file_name,b->crrent_file_name)==0)
            {
                if(file==temp->File)
                {
                    temp->File=file->next;
                    free(file);
                    break;
                }
                else{
                    prev_file->next = file->next;
                    break;
                }
            }
            prev_file=file;
            file = file->next;
        }
        if(temp->File==NULL)
        {
          if(temp==b->list[i])
          {
            b->list[i]=temp->next;
            free(temp);
          }
          else{
            prev->next=temp->next;
            free(temp);
          }

        }
        prev = temp;
        temp=temp->next;
      }
   }
}
