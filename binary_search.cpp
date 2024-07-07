/* searching algorithms
 1. Initialize
 2. Search (using a specific key (e.g., name, …))
 3. Insert
 4. Delete
 5. Join (optional)
 6. Sort (optional)
*/

//strcmp (const char*str1, const char*str2) 
//1)양수: str1이 str2보다 사전순으로 나중, 첫번째 문자에서 str1>str2
//2)0:동일 3)음수:str1<str2

/*binary search-> 이미 정렬된 데이터에 사용*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//data type만 int *a에서 char *a로 바꾸면 됨
int _int_bi_search(int key, int* a, int N) { //key찾고자하는 값임.
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
	return -1; //찾은 데이터의 인덱스 반환
}

int bi_search(int key, char* a, int N) { //key찾고자하는 값임.
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
	
	return -1; //찾은 데이터의 인덱스 반환
}

//원래 input값보다 큰 값ㅇ에서 걸리는데 가장 큰 z의 경우 예외가 발생함.
int bi_insert(int key, char* a, int* N) { //길이 *N
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


	return p; // 정렬된 규칙에 맞추어 데이터 삽입 & 인덱스 반환
}

//배열 첫 값 blank로 해놓아야 정상수행, 아니면 그냥 한칸씩 앞으로 땡겨짐(A삭제경우)
//SEARCH는 인덱스 0부터 N까지 다 탐색함.


int bi_delete(int key, char* a, int* N) {
	int B;
	int i;
	if (*N > 0) {
		B = bi_search(key, a, *N);
		printf("1차 del 속 B %d \n", B);
		if (B < 0) {
			return -1;
		}
		for (i =B + 1; i <= *N; i++) {
			a[i - 1] = a[i]; //뒷 값을 바로 앞에 copy
		}	
		a[*N] = ' ';
		(*N)--;
		a[0] = ' ';
		
		return B;
	}

	return -1;
}

//char heap sort
void downheap(char* a, int N, int k) {	// 위에서 부터 아래로 정렬  (문자열데이터면 char* a, 정수데이터면 int* a)
	int i, v;
	v = a[k];				// v 에 root값을 저장 (보통 k=1)
	while (k <= N / 2) {		// k가 internal node 개수보다 커지면 반복문 종료
		i = k << 1;			// i = 2*k, 즉 i노드는 k노드의 왼쪽 자식
		if (i < N && a[i] < a[i + 1]) i++;			// 만약 오른쪽 자식이 더 크면 오른쪽 자식을 i노드로 설정
		if (v >= a[i]) break;						// v값, 즉 root값이 자식값보다 크면 종료
		a[k] = a[i];		// 부모값에 자식값 넣음, 즉 자식값을 위로 올림
		k = i;				// k노드(부모노드)가 i노드(자식노드)로 내려가며 반복
	}
	a[k] = v;				// 반복문이 끝난 위치에 k노드에 처음 받은 root값 저장
}

void heap_sort_bottom(char* a, int N) {		 // N은 데이터 길이, a는 힙 주소, bottom up 방식 (문자열데이터면 char* a, 정수데이터면 int* a)
	int k, t;
	for (k = N / 2; k > 0; k--) downheap(a, N, k);		// 모든 internal node 에 대하여 downheap 정렬

	while (N > 1) {				// 데이터 길이가 1이하가 되면 종료
		t = a[1];
		a[1] = a[N];
		a[N] = t;				// 가장 아래에 있는 노드와(작은값) 가장 위에 있는 노드(큰값)을 교체
		downheap(a, --N, 1);	//	교체가 끝난 큰값은 놔두고 다시 정렬 --> 오름차순 정렬이 된다
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
//uneven distribution일때 유리
//mid point : mid=l+ (float)(key-a[l])*(r-l)/(a[r]-a[l]);