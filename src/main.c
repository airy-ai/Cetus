/*
MIT License

Copyright (c) 2019 Varun

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
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
