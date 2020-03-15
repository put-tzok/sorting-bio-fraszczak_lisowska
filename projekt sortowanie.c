#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

unsigned int ns[] = {1000,2000,3000,4000,5000,6000,8000,10000,15000,20000,25000,30000,35000,40000};

void fill_increasing(int *t, unsigned int n) {
    int i;
    for (i = 0; i < n; i++) {
        t[i] = i;
    }
}

void fill_decreasing(int *t, unsigned int n) {
    int i;
    for (i = 0; i<n; i++) {
        t[i]= -i;
    }
}

void fill_vshape(int *t, unsigned int n) {
       int j,k;
j=0;
k=n-1;
for(int i=0;i<n;i++){
if(i%2==0){
  t[j]=n-1-i;
  j++;
}
if(i%2==1){
  t[k]=n-1-i;
  k--;
}
}}



void swap(int *i, int *j)
{
    int temp = *i;
    *i = *j;
	*j = temp;
}

void selection_sort(int *t, unsigned int n)
{
    int i, j, x;

    for (i = 0; i < n-1; i++)
    {
       x = i;
        for (j = i+1; j < n; j++)
          if (t[j] < t[x])
            x = j;
        swap(&t[x], &t[i]);
    }
}


void insertion_sort(int *t, unsigned int n) {

int x, j, i;
	for(j=1; j<n; j++)
        {
	int	x = t[j];
	int	i = j-1;
		while( t[i]>x && i>=0 )
            {
            t[i+1] = t[i];
            i--;
            }
		t[i+1] = x;
		}
}





int partition(int *t , int p, int r){
  int x=t[r];//x-pivot
  int i=(p-1);
  for(int j=p; j<=r-1;j++){

    if(t[j]<=x){
      i++;
      swap(&t[i],&t[j]);
    }}

  swap(&t[i+1],&t[r]);
    return (i+1);

}


 int random_partitin (int *t,int p, int r){
int x=rand()%r+p;
swap(&t[x],&t[r]);
return partition (t,p,r);

 }

 int quick__sort(int *t, int p, int r){
if(p<r){
int q=partition(t,p,r);
quick__sort(t,p,q-1);
quick__sort(t,q+1,r);

}}


void quick_sort(int *t, unsigned int n)
{
	quick__sort(t, 0, n-1);
}

void heap_sort(int *t, unsigned int n) {

    int *h = malloc(n * sizeof(*h));
    memset(h, 0, n);
    int parent, left, right, argmin, index,size,i=0;

    while( i < n){
            index = i;
        h[i] = t[i];
        while(1){
            if(0<index){
                parent = (index - 1) / 2;
                if(h[index] < h[parent]){
                        swap(&h[index],&h[parent]);

                }
            }else
                break;
            index = parent;
        }
        size = i + 1;
        i++;
    }


i=0;
   while(i < n){
        index = 0;
   size--;
        t[i] = h[0];

        h[0] = h[size];

        while(1){
            left = index * 2 + 1;
            right = index * 2 + 2;
            if(left >= size){
                break;
            }
            if((right >= size) || (h[left] < h[right])){
                argmin = left;
            }else{
                argmin = right;
            }
            if(h[argmin] < h[index]){
                swap(&h[argmin],&h[index]);

            }
            index = argmin;
        }
    i++;
    }}
void fill_random(int *t, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        t[i] = rand();
    }
}
void is_random(int *t, unsigned int n) {
    return;
}

void is_increasing(int *t, unsigned int n) {
    int i;
    for (i = 1; i < n; i++) {
        assert(t[i] > t[i - 1]);
    }
}

void is_decreasing(int *t, unsigned int n) {
    int i;
    for (i = 1; i < n; i++) {
        assert(t[i] < t[i - 1]);
    }
}

void is_vshape(int *t, unsigned int n) {
    int *begin = t;
    int *end = t + n - 1;

    while (end - begin > 1) {
        assert(*begin > *end);
        begin++;
        assert(*end > *begin);
        end--;
    }
}

void is_sorted(int *t, unsigned int n) {
    int i;
    for (i = 1; i < n; i++) {
        assert(t[i] >= t[i - 1]);
    }
}




void (*fill_functions[])(int *, unsigned int) = { fill_random, fill_increasing, fill_decreasing, fill_vshape };
void (*check_functions[])(int *, unsigned int) = { is_random, is_increasing, is_decreasing, is_vshape };
void (*sort_functions[])(int *, unsigned int) = { selection_sort, insertion_sort, quick_sort, heap_sort };

char *fill_names[] = { "Random", "Increasing", "Decreasing", "V_shape" };
char *sort_names[] = { "SelectionSort", "InsertionSort", "QuickSort", "HeapSort" };

int main() {
	FILE *fp=fopen("dane.txt", "w");
    int i,j,k;
    for (i = 0; i < sizeof(sort_functions) / sizeof(*sort_functions) ; i++) {
    void(*sort)(int *, unsigned int) = sort_functions[i];

        for (j = 0; j < sizeof(fill_functions) / sizeof(*fill_functions); j++) {
            void (*fill)(int *, unsigned int) = fill_functions[j];
            void (*check)(int *, unsigned int) = check_functions[j];

	            for (k = 0; k < sizeof(ns) / sizeof(*ns); k++) {

	                unsigned int n = ns[k];
	                int *t = malloc(n * sizeof(*t));

	                fill(t, n);
	                check(t, n);
	                clock_t begin = clock();
	                sort(t, n);
	                clock_t end = clock();
	                is_sorted(t, n);
	                printf("%s\t%s\t%u\t%f\n", sort_names[i], fill_names[j], n, (double)(end - begin) / (double)CLOCKS_PER_SEC);
	                fprintf(fp, "%s\t%s\t%u\t%f\n", sort_names[i], fill_names[j], n, (double)(end - begin) / (double)CLOCKS_PER_SEC);

	                free(t);
	            }
        }
   }
   fclose(fp);
    return 0;
}
