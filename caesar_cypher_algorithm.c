/*
 *  Program:    Caesar Cypher (Rotary Encryption) encryption and decryption algorithm
 *  Made by:    Ransomware3301 (https://www.github.com/ransomware3301) 
 *  Date:       11/11/2023
 * 
 *  Generic Use Format:     caesar [MODE] [DATA] [KEY]
 * 
 *      -   MODE:   encrypt (e) or decrypt (d) the DATA string
 *      -   DATA:   a string of text
 *      -   KEY:    the rotation offset for encrypting or decrypting DATA
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DECRYPT 0
#define ENCRYPT 1
#define ALPHA_DIM 26

typedef int BOOL;


void show_usage(void);
BOOL is_lowercase_alpha(char);
BOOL is_uppercase_alpha(char);
char * caesar_algorithm(int, char *, int);


int main(int argc, char *argv[])
{

    if( argc == 4 ) 
    {
        if( *(argv[1]) == 'd' || *(argv[1]) == 'D')
        {
            printf("\n%s \n\n --- (DECRYPTED) --- \n\n%s\n\n", 
                    argv[2], 
                    caesar_algorithm(DECRYPT, argv[2], atoi(argv[3]))
                    );
        }
        else if( *(argv[1]) == 'e' || *(argv[1]) == 'E')
        {
            printf("\n%s \n\n --- (ENCRYPTED) --- \n\n%s\n\n", 
                    argv[2], 
                    caesar_algorithm(ENCRYPT, argv[2], atoi(argv[3]))
                    );
        }
    }
    else
    {
        show_usage();
    }

    return 0;
}


void show_usage(void)
{
    printf("\nUsage of \"caesar\"\n");
    printf("\n\n caesar [MODE] [DATA] [KEY]\n\n");
    printf("\n - MODE = encrypt (e) or decrypt (d) the DATA string\n");
    printf(" - DATA = a string of text\n");
    printf(" - KEY = the rotation offset for encrypting or decrypting DATA\n\n");
}


BOOL is_lowercase_alpha(char c)
{
    return (( c >= 97 ) && ( c <= 122 ));
}


BOOL is_uppercase_alpha(char c)
{
    return (( c >= 65 ) && ( c <= 90 ));
}


char * caesar_algorithm(int mode, char *data, int key)
{
    int i, offset;
    int data_len;
    char c;
    char *res;


    data_len = strlen(data);
    res = NULL;


    if( data_len )
    {
        offset = key % ALPHA_DIM;

        if(( res = (char*)malloc(sizeof(char) * (data_len + 1)) ))
        {
            if( mode == DECRYPT )
            {
                for( i = 0; i < data_len; i++ )
                {
                    if( is_lowercase_alpha(*(data + i)) )
                    {
                        c = (*(data + i)) - offset;
                        if( !is_lowercase_alpha(c) )
                        {
                            c += ALPHA_DIM;
                        }
                        *(res + i) = c;
                    }
                    else if( is_uppercase_alpha(*(data + i)) )
                    {
                        c = (*(data + i)) - offset;
                        if( !is_uppercase_alpha(c) )
                        {
                            c += ALPHA_DIM;
                        }
                        *(res + i) = c;
                    }
                    else
                    {
                        *(res + i) = *(data + i);
                    }
                }
            }
            else if( mode == ENCRYPT )
            {
                for( i = 0; i < data_len; i++ )
                {
                    if( is_lowercase_alpha(*(data + i)) )
                    {
                        c = (*(data + i)) + offset;
                        if( !is_lowercase_alpha(c) )
                        {
                            c -= ALPHA_DIM;
                        }
                        *(res + i) = c;
                    }
                    else if( is_uppercase_alpha(*(data + i)) )
                    {
                        c = (*(data + i)) + offset;
                        if( !is_uppercase_alpha(c) )
                        {
                            c -= ALPHA_DIM;
                        }
                        *(res + i) = c;
                    }
                    else
                    {
                        *(res + i) = *(data + i);
                    }
                }
            }

            *(res + data_len) = '\0';
        }
        else
        {   
            printf("[caesar_algorithm] ERROR: Memory allocation unsuccessful\n");
        }
    }

    return res;
}
