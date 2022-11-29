#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*
*	文件指针 FILE* fp = fopen(const char* path)
*	使用 fputs(const char* string, FILE* fp) 写入文件
*	使用 fgets(char* buff, charcount, FILE* fp) 读取一行到 buff
*/


void writeData(const char* path, const char** data, int size) {
	FILE* fp = NULL;
	fp = fopen(path, "w+");

	char* s = NULL;
	for (int i = 0; i < size; i++) {
		s = data[i];
		fputs(s, fp);
		fputs("\n", fp);
	}
	fclose(fp);
}

void readData(const char* path) {
	FILE* fp = NULL;
	fp = fopen(path, "r");
	char* buff = (char*)malloc(sizeof(char) * 255);
	int i = 0;
	while (fgets(buff, 255, fp) != NULL) {
		printf("%s", buff);
	}
}

int main() {
	const char* path = "a.txt";
	const char* data[255] = { "hello", "world" };

	//printf("%s", data[1]);

	writeData(path, &data, 2);
	readData(path);

}