#ifndef HEADER_H
#define HEADER_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>


typedef struct file
{
    char*file_name;
    int count;
    struct file*next;
}file_d;

typedef struct node
{
    struct node*next;
    char* word;
    file_d* File;
}node;

typedef struct block
{
    int index[26];
    char upper[26];
    node* list[26];
    char crrent_file_name[30];
    char**file_names;// last added not used
    int no_files;//not used
}block;

block c;

void validate(int*argc,char**argv);

void shift(char**arr,int left,int right);

void initialize_block(block*b,int argc);

bool open_file(int argc,char*argv[]);

bool check_file_already_present(block*b,int argc,char*argv[]);

void delete_file(block*b,int identifier);

bool open_file_read(block*b,int argc,char*argv[]);

node* create_node(char*temp,char*filename);

file_d* create_file_block(char*file_name);

void add_to_block(block*b,char*word);

void find_add(block*b,char* arr,int size);

void read_find(block*b,FILE*fptr);

bool open_file_read(block*b,int argc,char*argv[]);

void display(block*b);

void max_occurance(file_d*file);

void min_occurance(file_d*file);

void all_occurance(file_d*file);

void search(block*b);

void write_in_file(block*b);

void read_from_table(block*b);

void add_another_file(block*b);

void modify_database(block*b);

#endif
