//
// Created by zgd on 2023/6/7.
//

#include <iostream>
#include <vector>

/**
 * 单精度矩阵乘法：SGEMM。
 *
 * 实现C = A * B，其中A形状是M*K，B是K*N，C是M*N。
 * 采用3层循环实现。
 */
void SGEMM(const float *A, const float *B, float *C,
           size_t M, size_t N, size_t K) {

    for (size_t i = 0; i < M; i++) {
        for (size_t j = 0; j < N; j++) {
            float sum = 0.0;
            for (size_t s = 0; s < K; s++) {
                sum += (*(A + i * K + s)) * (*(B + s * N + j));
            }
            *(C + i * N + j) = sum;
        }
    }
}

void TestSGEMM(size_t K) {
    std::vector<float> A(K * K , 1.0);
    std::vector<float> B(K * K, 2.0);
    std::vector<float> C(K * K, 0.0);
    SGEMM(A.data(), B.data(), C.data(), K, K, K);
}

int main() {
    TestSGEMM(100);

    TestSGEMM(200);

    TestSGEMM(300);

    TestSGEMM(500);

    TestSGEMM(700);

    TestSGEMM(900);
}