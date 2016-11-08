#ifndef HEADER_H
#define HEADER_H
typedef struct str
{
	int ex;
	int kof;
	str* next;
} polinom_, *polinom;

polinom Sum();
polinom Product();
int ReadFile(polinom* list);
int GetNumberOfElements(polinom root);
int Sort(polinom p, polinom* sortedPolinom);
polinom* ListToArray(polinom root);
polinom ArrayToList(polinom* array, polinom root, int c);
int Compare(const void* A, const void* B);
#endif