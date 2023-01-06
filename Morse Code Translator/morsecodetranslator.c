/***
 * Morse code translator 
 * 
 * Takes the text to be translated as an argument from the command to run the executable 
 * "./execname -m 'message to translate'"
 * 
 * Joshua Snyder 
*/

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define STR_ERROR_ARGS              "You must provide a message to be translated!\n./execname -m \"message to be translated\""
#define STR_COMMAND_FORMAT          "./execname -m \"message to be translated\""
#define STR_TRANSLATION_COMPLETE    "Translation complete with"
#define STR_UNKNOWNS                "unknown characters"

#define INT_MAP_SIZE                37

typedef struct {
    char key;
    char *value;
} map_pair;

typedef struct {
    char *value;
    int found; 
} lookup_return_values;

/***
 * Populate the map with ascii values mapped to their corresponding morse code string 
 * @param map
*/
void populate_keys(map_pair *map) 
{
    map[0].key = 'A'; map[0].value = ".-   ";

    map[1].key = 'B'; map[1].value = "-...   ";

    map[2].key = 'C'; map[2].value = "-.-.   ";

    map[3].key = 'D'; map[3].value = "-..   ";

    map[4].key = 'E'; map[4].value = ".   ";

    map[5].key = 'F'; map[5].value = "..-.   ";

    map[6].key = 'G'; map[6].value = "--.   ";

    map[7].key = 'H'; map[7].value = "....   ";

    map[8].key = 'I'; map[8].value = "..   ";

    map[9].key = 'J'; map[9].value = ".---   ";

    map[10].key = 'K'; map[10].value = "-.-   ";

    map[11].key = 'L'; map[11].value = ".-..   ";

    map[12].key = 'M'; map[12].value = "--   ";

    map[13].key = 'N'; map[13].value = "-.   ";

    map[14].key = 'O'; map[14].value = "---   ";

    map[15].key = 'P'; map[15].value = ".--.   ";

    map[16].key = 'Q'; map[16].value = "--.-   ";

    map[17].key = 'R'; map[17].value = ".-.   ";

    map[18].key = 'S'; map[18].value = "...   ";

    map[19].key = 'T'; map[19].value = "-   ";

    map[20].key = 'U'; map[20].value = "..-   ";

    map[21].key = 'V'; map[21].value = "...-   ";

    map[22].key = 'W'; map[22].value = ".--   ";

    map[23].key = 'X'; map[23].value = "-..-   ";

    map[24].key = 'Y'; map[24].value = "-.--   ";

    map[25].key = 'Z'; map[25].value = "--..   ";

    map[26].key = '1'; map[26].value = ".----   ";
    
    map[27].key = '2'; map[27].value = "..---   ";

    map[28].key = '3'; map[28].value = "...--   ";

    map[29].key = '4'; map[29].value = "....-   ";

    map[30].key = '5'; map[30].value = ".....   ";

    map[31].key = '6'; map[31].value = "-....   ";
    
    map[32].key = '7'; map[32].value = "--...   ";

    map[33].key = '8'; map[33].value = "---..   ";

    map[34].key = '9'; map[34].value = "----.";

    map[35].key = '0'; map[35].value = "-----";

    map[36].key = ' '; map[36].value = "       ";
}

/***
 * Get the value in the map based on the key provided. Exits with error message if failure occurs. 
 * @param key
 * @param map
 * @return value 
*/
lookup_return_values get_value(char key, map_pair *map)
{
    lookup_return_values vals = { " ", 0 };

    for (int i = 0; i < INT_MAP_SIZE; i++) {
        if (map[i].key == key) {
             vals.value = map[i].value;
             vals.found = 1;

             return vals;
        }
    }

    return vals;
}

/***
 * Translate the message by finding the matching morse code value with the map 
 * @param msg_to_translate
 * @param map
*/
void translate_message(char *msg_to_translate, map_pair *map) 
{
    printf("Translating %s ...\n", msg_to_translate);

    int len = strlen(msg_to_translate);
    
    int unknown_count = 0;
    lookup_return_values vals;

    for (int i = 0; i < len; i++) {
        vals = get_value(msg_to_translate[i], map);
        if (!vals.found) {
            unknown_count++;

        } else {
            printf("%s", vals.value);
        }
    }

    printf("\n%s %i %s\n", STR_TRANSLATION_COMPLETE, unknown_count, STR_UNKNOWNS);
}

/***
 * Get the message to be translated from the arguments of the input command. Exits with error message if failure occurs. 
 * @param argc
 * @param argv
 * @return message
*/
char* get_message_from_args(int argc, char **argv) {
    char *msg_to_translate;

    int opt;
    while ((opt = getopt(argc, argv, "hm:")) != -1) {
        switch (opt) {
            case 'h':
                printf("%s\n", STR_COMMAND_FORMAT);
                break;

            case 'm':
                msg_to_translate = (char*) malloc(sizeof(char) * strlen(optarg));
                strcpy(msg_to_translate, optarg);
                break;

            default:
                process_error(STR_ERROR_ARGS);
                break;
        }
    }

    return msg_to_translate;
}

int main(int argc, char **argv) 
{
    // Check to make sure the user entered a message to translate 
    if (argc < 2) {
        process_error(STR_ERROR_ARGS);
    }

    // Get the message to translate from the input
    char *msg_to_translate = get_message_from_args(argc, argv);

    // Initialize and populate the map 
    map_pair map[INT_MAP_SIZE];
    populate_keys(map);

    // Translate and output the message 
    translate_message(msg_to_translate, map);

    // Free allocated memory 
    free(msg_to_translate);

    return 0;
}