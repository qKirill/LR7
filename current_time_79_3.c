#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEFAULT_LOG "timelog.log"

int main(int argc, char *argv[])
{
    const char *log_path = (argc > 1) ? argv[1] : DEFAULT_LOG;

    time_t now = time(NULL);
    if (now == (time_t)-1) {
        perror("time");
        return EXIT_FAILURE;
    }

    struct tm *tm_info = localtime(&now);
    if (tm_info == NULL) {
        perror("localtime");
        return EXIT_FAILURE;
    }

    char buf[64];
    if (strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm_info) == 0) {
        fprintf(stderr, "strftime: буфер замалий\n");
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(log_path, "a");
    if (fp == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    fprintf(fp, "[%s] Поточний час записано\n", buf);
    fclose(fp);

    printf("Запис додано до %s: %s\n", log_path, buf);
    return EXIT_SUCCESS;
}