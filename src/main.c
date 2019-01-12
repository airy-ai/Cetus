#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

static const char* CRAWL_RESULT_FILE = "result.json";
// static const char* LOOKUP_FILE = "lookup.json";

int main()
{
    printf("%s", "Starting Lookup...\n");

    FILE* stream = fopen(CRAWL_RESULT_FILE, "r");
    if (stream == NULL) {
        perror("File doesn't exist\n");
        exit(EXIT_FAILURE);
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t nread;
    while ((nread = getline(&line, &len, stream)) != -1) {
        // fwrite(line, (size_t)nread, 1, stdout);
        char *out = NULL;
        cJSON *json = NULL;
        const cJSON *itunesId = NULL;

        json = cJSON_Parse(line);
        if (!json) {
            printf("Error before: [%s]\n", cJSON_GetErrorPtr());
        }
        else {
            // cJSON_AddStringToObject(json, "Hello", "World!");
            out = cJSON_Print(json);
            itunesId = cJSON_GetObjectItemCaseSensitive(json, "itunesId");
            if (cJSON_IsString(itunesId) && (itunesId->valuestring != NULL))
            {
                printf("%s\n", itunesId->valuestring);
            }
            cJSON_Delete(json);
            // printf("%s\n", out);
            free(out);
        }
    }

if (line) { free(line); }
fclose(stream);
    exit(EXIT_SUCCESS);
}
