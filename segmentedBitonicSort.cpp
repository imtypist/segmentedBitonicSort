// 8.17 10:00 AM start
#include <iostream>
using namespace std;
#include <cmath>
void segmentedBitonicSort(float* data, int* seg_id, int* seg_start, int n, int m);

int main(){
    float data[12]={0.8,-1,sqrt(-1.f),0.5,100,2324,-1,sqrt(-1.f),sqrt(-1.f),0,-1,0};
    int seg_id[12]={0,0,0,0,1,1,1,1,1,1,2,2};
    int n=12;
    int m=3;
    int seg_start[4]={0,4,10,12};
    segmentedBitonicSort(data, seg_id, seg_start, n, m);
    for(int i = 0;i < n;i++){
        cout << data[i] << " ";
    }
    cout << endl;
    return 0;
}

void segmentedBitonicSort(float* data, int* seg_id, int* seg_start, int n, int m){
    if(n <= 0 || m <= 0 || m > n || seg_start[m] != n || seg_id[n-1] != (m-1) || seg_id[0] != 0)   return;
    float a[100000];
    for(int i = 0;i < m;i++){ // m segments to loop
        float* seg = data + seg_start[i]; // this segment's start address
        int len = seg_start[i+1] - seg_start[i]; // length of this segment
        if(len == 0) return;
        float MAXN = seg[0];
        for(int k = 1;k < len;k++){
            if(MAXN != MAXN || seg[k] > MAXN){
                MAXN = seg[k]; // get the max number of list
            }
        }
        int N = 1;
        while(N < len)  N = N << 1; // make clen be power of 2
        //float* a = new float[N];
        if(N > 100000) return;
        for(int j = 0;j < len;j++) a[j] = seg[j];
        for(int j = len;j < N;j++) a[j] = MAXN;
        for (int k = 2;k <= N;k = 2*k) {
            for (int j = k>>1;j > 0;j = j>>1) {
                for (int p = 0;p < N;p++) {
                    int pxj = p ^ j;
                    if (pxj > p) {
                        // NAN => a[x] != a[x]
                        if (((p&k) == 0) && ((a[pxj] != a[pxj]) || (a[p] > a[pxj]))){
                            float t = a[pxj];
                            a[pxj] = a[p];
                            a[p] = t;
                        }
                        if (((p&k) != 0) && ((a[p] != a[p]) || (a[p] < a[pxj]))){
                            float t = a[pxj];
                            a[pxj] = a[p];
                            a[p] = t;
                        }
                    }
                }
            }
        }
        for(int j = 0;j < len;j++){
            seg[j] = a[j];
        }
        //delete[] a;
    }
}
