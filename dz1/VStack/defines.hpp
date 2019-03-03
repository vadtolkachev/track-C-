#pragma once

#define S_DOUBLE


#ifdef S_INT
typedef int data_t;
#endif

#ifdef S_DOUBLE
typedef double data_t;
#endif

const int SUCCESS = 1;
const int STACK_OK = 0;
const int CANARY1_ERR = -1;
const int CANARY2_ERR = -2;
const int CANARY3_ERR = -3;
const int CANARY4_ERR = -4;
const int SIZE_ERR = -5;
const int CAPACITY_ERR = -6;
const int POISON_ERR = -7;
const int SUM1_ERR = -8;
const int SUM2_ERR = -9;


const int ALLOC_ERR = -11;
const int NULLPTR_ERR = -12;
const int EMPTY_ERR = -13;
const int INF_ERR = -14;

const int READ_ERR = -15;
const int WRITE_ERR = -16;
const int OPEN_ERR = -17;
const int CLOSE_ERR = -18;
const int PARSE_ERR = -19;
const int TYPE_ERR = -20;
const int OVERFLOW_ERR = -21;
const int NOTNULLPTR_ERR = -22;


const int S_BUF = 2;

const int NORM_F = 10;
const int HEX_F = 16;
const int SUM1_F = 17;
const int SUM2_F = 18;


const data_t POISON1 = 666;
const data_t POISON2 = 667;
const data_t POISON3 = 668;

#ifdef S_INT
const data_t CANARY3 = 0xDEADBEEF;
const data_t CANARY4 = 0xBEDABEDA;
#endif

#ifdef S_DOUBLE
const unsigned long LCANARY3 = 0xDEADBEEFDEADBEEF;
const unsigned long LCANARY4 = 0xBEDABEDABEDABEDA;
const double CANARY3 = *reinterpret_cast<const double *>(&LCANARY3);
const double CANARY4 = *reinterpret_cast<const double *>(&LCANARY4);
#endif

const char GREEN[] = "\033[1;32m";
const char RED[] = "\033[1;31m";
const char WHITE[] = "\033[1;37m";
const char NORM[] = "\033[0m";