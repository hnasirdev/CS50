// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int total=0;
//prototype
node *newNode(void);

//implement these functions as cleverly as possible to make it work

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO

    int c;
    node_f=root;
    //parse through the word from text
    for(int i=0; i<strlen(word);i++){
        //check capitalisation
        if(word[i]>='A' && word[i]<='Z'){
            c=word[i]-'A';
        }
        else if(word[i]>='a' && word[i]<='z'){
            c=word[i]-'a';
        }
        else if(word[i]=='\''){
            c=26;
        }

        //check if that letter exists
        if(node_f->children[c]== NULL){
            return false;
        }
        else if(node_f->children[c]!= NULL){
            //is it end of word?
            if(i==(strlen(word)-1)){
                node_f=node_f->children[c];
                //is the word stored
                if((node_f->is_word) == true){
                    return true;
                }
                else{
                    return false;
                }
            }
            node_f=node_f->children[c];

        }


        else{
            //word not in dictionary so must be mispelled
            return false;
        }

    }
    node_f = root;
    return true;

}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO

    root = calloc(1, sizeof(node));
   // node* node_f;

    FILE *inptr1 = fopen(dictionary, "r");
    //char word [LENGTH + 1];
    if (inptr1 == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;
    }

    // get character as key from dictionary

    int c = fgetc(inptr1) - 'a';

   // if negative it must be apostrophe
    if(c+'a'=='\''){
        c=26; //give it the 27th space
    }

    //node_f points to root
    node_f = root;

    while((c+'a')!=EOF){

        while ((c+'a')!='\n'){
            //if that child node is null, calloc a new node for it
            if(!node_f->children[c]){
                //children now points to the new malloc node
                 node_f->children[c]=calloc(1, sizeof(node));
            }
            node_f= node_f->children[c];
            c=fgetc(inptr1)-'a';
            if(c+'a'== '\''){
                c=26;
            }

        }
         c=fgetc(inptr1)-'a';
         if(c+'a'=='\''){
             c=26;
         }
        node_f->is_word = true;
        total++;
        node_f = root;

    }

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO


    return total;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

   // node_f=root;
    for(int i =0; i<26; i++){
        if(node_f->children[i]!=NULL){
            node_f=node_f->children[i];
            unload();
        }
        else if(node_f->children[i]==NULL){
            i=26;
        }
    }
    free(node_f);
    free(root);


    return true;
}

node *newNode(void){

     node *pnode = NULL;

    pnode = (struct node *)malloc(sizeof(node));

    if(pnode){

        pnode->is_word = false;
        for(int i =0; i<27; i++){
            pnode->children[i]=NULL;
        }
    }
    return pnode;
}

