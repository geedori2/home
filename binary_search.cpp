/* searching algorithms
 1. Initialize
 2. Search (using a specific key (e.g., name, ��))
 3. Insert
 4. Delete
 5. Join (optional)
 6. Sort (optional)
*/

//strcmp (const char*str1, const char*str2) 
//1)���: str1�� str2���� ���������� ����, ù��° ���ڿ��� str1>str2
//2)0:���� 3)����:str1<str2

/*binary search-> �̹� ���ĵ� �����Ϳ� ���*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//data type�� int *a���� char *a�� �ٲٸ� ��
int _int_bi_search(int key, int* a, int N) { //keyã�����ϴ� ����.
	int mid;
	int left = 0;
	int right = N - 1;
	while (right >= left) {
		mid = (right + left) / 2;
		if (key == a[mid])return mid;
		if (key < a[mid]) {
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}
	return -1; //ã�� �������� �ε��� ��ȯ
}

int bi_search(int key, char* a, int N) { //keyã�����ϴ� ����.
	int mid;
	int left = 1;
	int right = N;
	while (right >= left) {
		mid = (right + left) / 2;
		if (key == a[mid])return mid;
		if (key < a[mid]) {
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}
	
	return -1; //ã�� �������� �ε��� ��ȯ
}

//���� input������ ū �������� �ɸ��µ� ���� ū z�� ��� ���ܰ� �߻���.
int bi_insert(int key, char* a, int* N) { //���� *N
	int p = 0;
	int i;
	while (key > a[p] && p < *N) {
		p++;
	}
	(*N)++;
	for (i = *N; i > p; i--) {
		a[i] = a[i - 1]; // a[*N]=a[*N -1]
	}
	if (key == 'Z') {
		p = p + 1;
	}
	a[p] = key;


	return p; // ���ĵ� ��Ģ�� ���߾� ������ ���� & �ε��� ��ȯ
}

//�迭 ù �� blank�� �س��ƾ� �������, �ƴϸ� �׳� ��ĭ�� ������ ������(A�������)
//SEARCH�� �ε��� 0���� N���� �� Ž����.


int bi_delete(int key, char* a, int* N) {
	int B;
	int i;
	if (*N > 0) {
		B = bi_search(key, a, *N);
		printf("1�� del �� B %d \n", B);
		if (B < 0) {
			return -1;
		}
		for (i =B + 1; i <= *N; i++) {
			a[i - 1] = a[i]; //�� ���� �ٷ� �տ� copy
		}	
		a[*N] = ' ';
		(*N)--;
		a[0] = ' ';
		
		return B;
	}

	return -1;
}

//char heap sort
void downheap(char* a, int N, int k) {	// ������ ���� �Ʒ��� ����  (���ڿ������͸� char* a, ���������͸� int* a)
	int i, v;
	v = a[k];				// v �� root���� ���� (���� k=1)
	while (k <= N / 2) {		// k�� internal node �������� Ŀ���� �ݺ��� ����
		i = k << 1;			// i = 2*k, �� i���� k����� ���� �ڽ�
		if (i < N && a[i] < a[i + 1]) i++;			// ���� ������ �ڽ��� �� ũ�� ������ �ڽ��� i���� ����
		if (v >= a[i]) break;						// v��, �� root���� �ڽİ����� ũ�� ����
		a[k] = a[i];		// �θ𰪿� �ڽİ� ����, �� �ڽİ��� ���� �ø�
		k = i;				// k���(�θ���)�� i���(�ڽĳ��)�� �������� �ݺ�
	}
	a[k] = v;				// �ݺ����� ���� ��ġ�� k��忡 ó�� ���� root�� ����
}

void heap_sort_bottom(char* a, int N) {		 // N�� ������ ����, a�� �� �ּ�, bottom up ��� (���ڿ������͸� char* a, ���������͸� int* a)
	int k, t;
	for (k = N / 2; k > 0; k--) downheap(a, N, k);		// ��� internal node �� ���Ͽ� downheap ����

	while (N > 1) {				// ������ ���̰� 1���ϰ� �Ǹ� ����
		t = a[1];
		a[1] = a[N];
		a[N] = t;				// ���� �Ʒ��� �ִ� ����(������) ���� ���� �ִ� ���(ū��)�� ��ü
		downheap(a, --N, 1);	//	��ü�� ���� ū���� ���ΰ� �ٽ� ���� --> �������� ������ �ȴ�
	}
}

void print_str(char* a, int N) {
	for (int i = 1; i <= N; i++) {
		printf(" %c ", a[i]);
	}
	printf("\n=======================\n");
}
//<= >=
void main() {
	char str[20] = "TOSORTALGORITHM";
	int size = 15;
	char cpy[20] = { 0 };
	cpy[0] = ' ';

	for (int i = 0; i < size; i++)cpy[i + 1] = str[i];

	//conduct sorting
	heap_sort_bottom(cpy, size);
	print_str(cpy, size);

	int p = bi_search('S', cpy, size);
	printf("Find your key at %d (value %c) \n", p, cpy[p]);

	p = bi_insert('N', cpy, &size);
	printf("%s\n", cpy);
	p = bi_insert('Z', cpy, &size);
	printf("%s\n", cpy);

	p = bi_search('A', cpy, size);
	printf("%d\n", p);
	p = bi_delete('A', cpy, &size);
	printf("%d\n", p);
	print_str(cpy, size);
	printf("%s\n", cpy);

	p = bi_search('M', cpy, size);
	printf("%d\n", p);
	p = bi_delete('M', cpy, &size);
	printf("%d\n", p);
	print_str(cpy, size);
	printf("%s\n", cpy);
}
//uneven distribution�϶� ����
//mid point : mid=l+ (float)(key-a[l])*(r-l)/(a[r]-a[l]);