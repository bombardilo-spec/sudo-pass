#include <iostream>
#include <cuda_runtime.h>

using namespace std;

// -------- KERNEL FUNCTION --------
__global__ void add(int *A, int *B, int *C, int n) {

    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < n) {
        C[i] = A[i] + B[i];
    }
}

// -------- MAIN --------
int main() {

    int n = 10;
    int size = n * sizeof(int);

    int A[10], B[10], C[10];
    int *d_A, *d_B, *d_C;

    // initialize arrays
    for (int i = 0; i < n; i++) {
        A[i] = i;
        B[i] = i * 2;
    }

    // allocate GPU memory
    cudaMalloc(&d_A, size);
    cudaMalloc(&d_B, size);
    cudaMalloc(&d_C, size);

    // copy data to GPU
    cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);

    // launch kernel
    add<<<1, 10>>>(d_A, d_B, d_C, n);

    // copy result back
    cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);

    // print result
    cout << "Result: ";
    for (int i = 0; i < n; i++) {
        cout << C[i] << " ";
    }

    cout << endl;

    // free memory
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}