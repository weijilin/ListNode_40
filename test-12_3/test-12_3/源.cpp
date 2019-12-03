#include<stdio.h>
#include<stdlib.h>
int doublefind(int a[], int left, int right, int k) {
	int mid = 0;
	while (left <=right) {
		mid =  (right + left) / 2;
		if (a[mid] < k)
			left=mid + 1;

		else if (a[mid] > k)
			right=mid - 1;
		
		else 
			return mid;
	}

	return -1;
}
int main() {
	int a[] = { 1,2,3,4,5,6,7,8,9,12 };
	int left = 0;
	int right = sizeof(a) / sizeof(0) - 1;
	int k = 91;
	int r = doublefind(a, left, right, k);
	//cout << r << endl;
	printf("%d", r);
	system("pause");
	return 0;
}