#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*
* 	这里将 demo_c.c 里面直接输出文件内容改成用一个 char** 保存字符串数组
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

void readData(const char* path, char** new_data, int* size) {

	FILE* fp = NULL;
	fp = fopen(path, "r");
	char* buff = (char*)malloc(sizeof(char) * 255);
	while (fgets(buff, 255, fp) != NULL) {
		new_data[*size] = buff;
		buff = (char*)malloc(sizeof(char) * 255);
		// 注意下面括号不可省略，* 优先级高于自加
		(*size)++;
	}
}

int main() {
	const char* path = "a.txt";
	const char* data[255] = { "hello", "world", "hahahaha" };

	int size = 0;
	char** new_data = (char**)malloc(sizeof(char*) * 255);
	writeData(path, data, 3);
	readData(path, new_data, &size);

	for (int i = 0; i < size; i++) printf("%s", new_data[i]);
}