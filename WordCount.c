#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

int countChars(FILE *file) {
    int count = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        count++;
    }
    // 重置文件指针到文件开始
    fseek(file, 0, SEEK_SET);
    return count;
}

int countWords(FILE *file) {
    int count = 0;
    int ch;
    bool inWord = false;
    while ((ch = fgetc(file)) != EOF) {
        if (isspace(ch) || ch == ',') {
            if (inWord) {
                count++;
                inWord = false;
            }
        } else {
            inWord = true;
        }
    }
    // 如果文件以非空格结尾，需要计算最后一个单词
    if (inWord) {
        count++;
    }
    // 重置文件指针到文件开始
    fseek(file, 0, SEEK_SET);
    return count;
}
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s [-c|-w] <file_name>\n", argv[0]);
        return 1;
    }

    char *param = argv[1];
    char *filename = argv[2];
    FILE *file = fopen(filename, "r");

    if (!file) {
        perror("Error opening file");
        return 1;
    }

    int result = 0;
    if (strcmp(param, "-c") == 0) {
        result = countChars(file);
        printf("字符数：%d\n", result);
    } else if (strcmp(param, "-w") == 0) {
        result = countWords(file);
        printf("单词数：%d\n", result);
    } else {
        printf("Invalid parameter. Use '-c' for character count or '-w' for word count.\n");
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}

