static inline int64_t neg_cpp(int64_t a) {
    return -a;
}
static inline int64_t neg_cast(int64_t a) {
    return (int64_t)(-((uint64_t)a));
}
static inline int64_t neg_alg(int64_t a) {
    return (int64_t)(~((uint64_t)a) + 1);
}

static inline uint64_t uiadd64(uint64_t lhs, uint64_t rhs) {
    uint32_t res_hi,
    res_lo;
    uint32_t lhs_hi,
    lhs_lo,
    rhs_hi,
    rhs_lo;
    
    lhs_hi = lhs >> 32;
    lhs_lo = lhs & 0xffffffff;
    rhs_hi = rhs >> 32;
    rhs_lo = rhs & 0xffffffff;
    
    res_lo = lhs_lo + rhs_lo;
    res_hi = lhs_hi + rhs_hi;
    
    if (res_lo < lhs_lo || res_lo < rhs_lo) {
        res_hi++;
    }
    
    return ((int64_t)(res_hi)) << 32 | res_lo;
}

static inline int64_t iadd64(int64_t lhs, int64_t rhs)
{
    return (int64_t)(uiadd64((uint64_t)lhs, (uint64_t)rhs));
}

// use 32-bit math to multiply 16-bit numbers and get overflow
static inline uint16_t mul_16(uint16_t a, uint16_t b, uint16_t *overflow) {
    uint32_t res = (uint32_t)(a) * (uint32_t)(b);
    
    *overflow = (uint16_t)(res >> 16);
    return (uint16_t)res;
}

static inline uint16_t sum_16(uint16_t a, uint16_t b, uint16_t *overflow) {
    uint32_t res = (uint32_t)(a) + (uint32_t)(b);
    
    *overflow = (uint16_t)(res >> 16);
    return (uint16_t)res;
}

static inline uint16_t sum_5_16(uint16_t a, uint16_t b, uint16_t c, uint16_t d, uint16_t e, uint16_t *overflow) {
    uint32_t res = (uint32_t)(a) + (uint32_t)(b) + (uint32_t)(c) + (uint32_t)(d) + (uint32_t)(e);
    
    *overflow = (uint16_t)(res >> 16);
    return (uint16_t)res;
}

// implementing this algorithm: http://i.imgur.com/GPyYz5h.jpg
static inline int64_t mul_alg(int64_t a, int64_t b)
{
    // convert to positive
    int64_t res;
    int16_t neg = 1;
    if (a < 0) {
        neg *= -1;
        a = -a;
    }
    if (b < 0) {
        neg *= -1;
        b = -b;
    }
    
    // extract 16 bits out of each
    uint16_t A[4], B[4];
    A[3] = (uint16_t)(a >> 48); A[2] = (uint16_t)(a >> 32); A[1] = (uint16_t)(a >> 16); A[0] = (uint16_t)(a);
    B[3] = (uint16_t)(b >> 48); B[2] = (uint16_t)(b >> 32); B[1] = (uint16_t)(b >> 16); B[0] = (uint16_t)(b);
    
    // store results in a 4x5 table, rows by columns. 1 extra col for overflow logic
    uint16_t F[4][5];
    memset(F, 0, sizeof(F));
    
    // start multiplying it out, the long way
    for (uint8_t row=0; row < 4; row++) {
        for (uint8_t col=row; col < 4; col++) {
            // multiply, store remainder in next cell
            uint16_t rem, mul_res;
            mul_res = mul_16(A[col - row], B[row], &F[row][col + 1]);
            
            // add to current cell (= remainder from previous cell), keep track of remainder
            F[row][col] = sum_16(F[row][col], mul_res, &rem);
            
            // add sum remainder to mul remainder to next cell, remainder now should always be 0
            F[row][col + 1] = sum_16(F[row][col + 1], rem, &rem);
        }
    }
    
    // now sum the intermediate values into the result
    uint16_t R[5]; // 1 extra to simplify logic
    memset(R, 0, sizeof(R));
    for (uint8_t col=0; col < 4; col++) {
        R[col] = sum_5_16(R[col], F[0][col], F[1][col], F[2][col], F[3][col], &R[col + 1]);
    }
    
    // convert back into a 64-bit number
    res = (int64_t)(uiadd64(
                            uiadd64((uint64_t)(R[0]), ((uint64_t)(R[1]) << 16)),
                            uiadd64(((uint64_t)(R[2]) << 32), ((uint64_t)(R[3]) << 48))));
    
    // re-negate if needed
    res *= neg;
    
    return res;
}
static inline int64_t mul_alg_F28(int64_t a, int64_t b){
    return ((mul_alg(a,b))>>28);
}
static inline int64_t mul_alg_F22(int64_t a, int64_t b){
    return ((mul_alg(a,b))>>22);
}
static inline int64_t mul_alg_F54(int64_t a, int64_t b){
    return ((mul_alg(a,b))>>54);
}

