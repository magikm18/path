/***************************************************************************
* Copyright (c) 2016 Nicholas Mertin <nickmertin@gmail.com>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the
* Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>

int main(int argc, char **argv) {
    opterr = 0;
    int result = 0;
    char *p = malloc(4096);
    strcpy(p, getenv("PATH"));
    bool _a = false, _q = false, _v = false;
    while ((result = getopt(argc, argv, "ad:hqv")) != -1) {
        switch (result) {
            case 'a':
                _a = true;
                break;
            case 'd':
                strcat(p, ":");
                strcat(p, optarg);
                break;
            case 'h':
                printf("Usage: path [option] [--] command\n\n  -a\n\tshow all possible results (instead of just the first result, which is the default behaviour\n  -d /path/to/directory\n\tinclude the specified path in the search\n  -q\n\tquiet mode (never post 'not found' line)\n  -h\n\tshow this help\n  -v\n\tverbose mode (list every directory that is searched and show if a search fails)\n");
                return 0;
            case 'q':
                _q = true;
                break;
            case 'v':
                _v = true;
                break;
            case '?':
                fprintf(stderr, isprint(optopt) ? "Unknown option: '%c'\n" : "Unknown option character: %hhd\n", (char)optopt);
                return 1;
        }
    }
    if (optind == argc) {
        fputs("Missing command name\n", stderr);
        return 1;
    }
    char *n = argv[optind];
    DIR *d;
    struct dirent *dir;
    bool found = false;
    while (p[0]) {
        size_t i = 0;
        for (; p[i] && p[i] != ':'; ++i);
        p[i] = 0;
        if (d = opendir(p)) {
            if (_v)
                printf("Checking '%s'...\n", p);
            while (dir = readdir(d)) {
                if ((dir->d_type == DT_LNK || dir->d_type == DT_REG) && !strcmp(dir->d_name, n)) {
                    found = true;
                    printf(_v ? "Found: %s/%s\n" : "%s/%s\n", p, n);
                    if (!_a)
                        return 0;
                }
            }
            closedir(d);
        }
        else if (_v)
            printf("Failed to open directory '%s'\n", p);
        p += i + 1;
    }
    if (!found && !_q)
        printf("Not found: '%s'\n", n);
    return 0;
}
