#ifndef T_RANGE_H
#define T_RANGE_H
/******************************************************************************
 *
 * Filename:          t_range.h
 *
 * Description:       This file contains predefined RANGE fixed point types.
 *
 * Global Functions Defined:
 *                    None
 * Static Functions Defined:
 *                    None
 * Inline Functions Defined:
 *                    None
 *
 * Forward Engine Management Systems
 *
 * Copyright 2000-2003, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     mt20u2#10/incl/t_range.h/1 %
 * %date_created:  Wed Mar 19 09:46:42 2008 %
 * %version:       1 %
 * %derived_by:    vzp48z %
 *
 *****************************************************************************/

/******************************************************************************
 *  Signed 1-Byte Range Fixed Point Types
 ******************************************************************************/

/* Res:   0.000030517578125         */
/* Range: [-1/256, 1/256)           */
typedef signed char                            T_B_RANGE_Nr256_r256;
#define V_B_RANGE_Nr256_r256(val)              (signed char )(val*32768)
#define S_B_RANGE_Nr256_r256                   15

/* Res:   0.000061035156250         */
/* Range: [-1/128, 1/128)           */
typedef signed char                            T_B_RANGE_Nr128_r128;
#define V_B_RANGE_Nr128_r128(val)              (signed char )(val*16384)
#define S_B_RANGE_Nr128_r128                   14

/* Res:   0.000122070312500         */
/* Range: [-1/64, 1/64)             */
typedef signed char                            T_B_RANGE_Nr64_r64;
#define V_B_RANGE_Nr64_r64(val)                (signed char )(val*8192)
#define S_B_RANGE_Nr64_r64                     13

/* Res:   0.000244140625000         */
/* Range: [-1/32, 1/32)             */
typedef signed char                            T_B_RANGE_Nr32_r32;
#define V_B_RANGE_Nr32_r32(val)                (signed char )(val*4096)
#define S_B_RANGE_Nr32_r32                     12

/* Res:   0.000488281250000         */
/* Range: [-1/16, 1/16)             */
typedef signed char                            T_B_RANGE_Nr16_r16;
#define V_B_RANGE_Nr16_r16(val)                (signed char )(val*2048)
#define S_B_RANGE_Nr16_r16                     11

/* Res:   0.000976562500000         */
/* Range: [-1/8, 1/8)               */
typedef signed char                            T_B_RANGE_Nr8_r8;
#define V_B_RANGE_Nr8_r8(val)                  (signed char )(val*1024)
#define S_B_RANGE_Nr8_r8                       10

/* Res:   0.001953125000000         */
/* Range: [-1/4, 1/4)               */
typedef signed char                            T_B_RANGE_Nr4_r4;
#define V_B_RANGE_Nr4_r4(val)                  (signed char )(val*512)
#define S_B_RANGE_Nr4_r4                       9

/* Res:   0.003906250000000         */
/* Range: [-1/2, 1/2)               */
typedef signed char                            T_B_RANGE_Nr2_r2;
#define V_B_RANGE_Nr2_r2(val)                  (signed char )(val*256)
#define S_B_RANGE_Nr2_r2                       8

/* Res:   0.007812500000000         */
/* Range: [-1, 1)                   */
typedef signed char                            T_B_RANGE_N1_1;
#define V_B_RANGE_N1_1(val)                    (signed char )(val*128)
#define S_B_RANGE_N1_1                         7

/* Res:   0.015625000000000         */
/* Range: [-2, 2)                   */
typedef signed char                            T_B_RANGE_N2_2;
#define V_B_RANGE_N2_2(val)                    (signed char )(val*64)
#define S_B_RANGE_N2_2                         6

/* Res:   0.031250000000000         */
/* Range: [-4, 4)                   */
typedef signed char                            T_B_RANGE_N4_4;
#define V_B_RANGE_N4_4(val)                    (signed char )(val*32)
#define S_B_RANGE_N4_4                         5

/* Res:   0.062500000000000         */
/* Range: [-8, 8)                   */
typedef signed char                            T_B_RANGE_N8_8;
#define V_B_RANGE_N8_8(val)                    (signed char )(val*16)
#define S_B_RANGE_N8_8                         4

/* Res:   0.125000000000000         */
/* Range: [-16, 16)                 */
typedef signed char                            T_B_RANGE_N16_16;
#define V_B_RANGE_N16_16(val)                  (signed char )(val*8)
#define S_B_RANGE_N16_16                       3

/* Res:   0.250000000000000         */
/* Range: [-32, 32)                 */
typedef signed char                            T_B_RANGE_N32_32;
#define V_B_RANGE_N32_32(val)                  (signed char )(val*4)
#define S_B_RANGE_N32_32                       2

/* Res:   0.500000000000000         */
/* Range: [-64, 64)                 */
typedef signed char                            T_B_RANGE_N64_64;
#define V_B_RANGE_N64_64(val)                  (signed char )(val*2)
#define S_B_RANGE_N64_64                       1

/* Res:   1.000000000000000         */
/* Range: [-128, 128)               */
typedef signed char                            T_B_RANGE_N128_128;
#define V_B_RANGE_N128_128(val)                (signed char )(val*1)
#define S_B_RANGE_N128_128                     0

/******************************************************************************
 *  Unsigned 1-Byte Range Fixed Point Types
 ******************************************************************************/

/* Res:   0.000015258789062         */
/* Range: [0, 1/256)                */
typedef unsigned char                          T_B_RANGE_0_r256;
#define V_B_RANGE_0_r256(val)                  (unsigned char )(val*65536)
#define S_B_RANGE_0_r256                       16

/* Res:   0.000030517578125         */
/* Range: [0, 1/128)                */
typedef unsigned char                          T_B_RANGE_0_r128;
#define V_B_RANGE_0_r128(val)                  (unsigned char )(val*32768)
#define S_B_RANGE_0_r128                       15

/* Res:   0.000061035156250         */
/* Range: [0, 1/64)                 */
typedef unsigned char                          T_B_RANGE_0_r64;
#define V_B_RANGE_0_r64(val)                   (unsigned char )(val*16384)
#define S_B_RANGE_0_r64                        14

/* Res:   0.000122070312500         */
/* Range: [0, 1/32)                 */
typedef unsigned char                          T_B_RANGE_0_r32;
#define V_B_RANGE_0_r32(val)                   (unsigned char )(val*8192)
#define S_B_RANGE_0_r32                        13

/* Res:   0.000244140625000         */
/* Range: [0, 1/16)                 */
typedef unsigned char                          T_B_RANGE_0_r16;
#define V_B_RANGE_0_r16(val)                   (unsigned char )(val*4096)
#define S_B_RANGE_0_r16                        12

/* Res:   0.000488281250000         */
/* Range: [0, 1/8)                  */
typedef unsigned char                          T_B_RANGE_0_r8;
#define V_B_RANGE_0_r8(val)                    (unsigned char )(val*2048)
#define S_B_RANGE_0_r8                         11

/* Res:   0.000976562500000         */
/* Range: [0, 1/4)                  */
typedef unsigned char                          T_B_RANGE_0_r4;
#define V_B_RANGE_0_r4(val)                    (unsigned char )(val*1024)
#define S_B_RANGE_0_r4                         10

/* Res:   0.001953125000000         */
/* Range: [0, 1/2)                  */
typedef unsigned char                          T_B_RANGE_0_r2;
#define V_B_RANGE_0_r2(val)                    (unsigned char )(val*512)
#define S_B_RANGE_0_r2                         9

/* Res:   0.003906250000000         */
/* Range: [0, 1)                    */
typedef unsigned char                          T_B_RANGE_0_1;
#define V_B_RANGE_0_1(val)                     (unsigned char )(val*256)
#define S_B_RANGE_0_1                          8

/* Res:   0.007812500000000         */
/* Range: [0, 2)                    */
typedef unsigned char                          T_B_RANGE_0_2;
#define V_B_RANGE_0_2(val)                     (unsigned char )(val*128)
#define S_B_RANGE_0_2                          7

/* Res:   0.015625000000000         */
/* Range: [0, 4)                    */
typedef unsigned char                          T_B_RANGE_0_4;
#define V_B_RANGE_0_4(val)                     (unsigned char )(val*64)
#define S_B_RANGE_0_4                          6

/* Res:   0.031250000000000         */
/* Range: [0, 8)                    */
typedef unsigned char                          T_B_RANGE_0_8;
#define V_B_RANGE_0_8(val)                     (unsigned char )(val*32)
#define S_B_RANGE_0_8                          5

/* Res:   0.062500000000000         */
/* Range: [0, 16)                   */
typedef unsigned char                          T_B_RANGE_0_16;
#define V_B_RANGE_0_16(val)                    (unsigned char )(val*16)
#define S_B_RANGE_0_16                         4

/* Res:   0.125000000000000         */
/* Range: [0, 32)                   */
typedef unsigned char                          T_B_RANGE_0_32;
#define V_B_RANGE_0_32(val)                    (unsigned char )(val*8)
#define S_B_RANGE_0_32                         3

/* Res:   0.250000000000000         */
/* Range: [0, 64)                   */
typedef unsigned char                          T_B_RANGE_0_64;
#define V_B_RANGE_0_64(val)                    (unsigned char )(val*4)
#define S_B_RANGE_0_64                         2

/* Res:   0.500000000000000         */
/* Range: [0, 128)                  */
typedef unsigned char                          T_B_RANGE_0_128;
#define V_B_RANGE_0_128(val)                   (unsigned char )(val*2)
#define S_B_RANGE_0_128                        1

/* Res:   1.000000000000000         */
/* Range: [0, 256)                  */
typedef unsigned char                          T_B_RANGE_0_256;
#define V_B_RANGE_0_256(val)                   (unsigned char )(val*1)
#define S_B_RANGE_0_256                        0

/******************************************************************************
 *  Signed 2-Byte Range Fixed Point Types
 ******************************************************************************/

/* Res:   0.000000119209290         */
/* Range: [-1/256, 1/256)           */
typedef signed short                           T_W_RANGE_Nr256_r256;
#define V_W_RANGE_Nr256_r256(val)              (signed short )(val*8388608)
#define S_W_RANGE_Nr256_r256                   23

/* Res:   0.000000238418579         */
/* Range: [-1/128, 1/128)           */
typedef signed short                           T_W_RANGE_Nr128_r128;
#define V_W_RANGE_Nr128_r128(val)              (signed short )(val*4194304)
#define S_W_RANGE_Nr128_r128                   22

/* Res:   0.000000476837158         */
/* Range: [-1/64, 1/64)             */
typedef signed short                           T_W_RANGE_Nr64_r64;
#define V_W_RANGE_Nr64_r64(val)                (signed short )(val*2097152)
#define S_W_RANGE_Nr64_r64                     21

/* Res:   0.000000953674316         */
/* Range: [-1/32, 1/32)             */
typedef signed short                           T_W_RANGE_Nr32_r32;
#define V_W_RANGE_Nr32_r32(val)                (signed short )(val*1048576)
#define S_W_RANGE_Nr32_r32                     20

/* Res:   0.000001907348633         */
/* Range: [-1/16, 1/16)             */
typedef signed short                           T_W_RANGE_Nr16_r16;
#define V_W_RANGE_Nr16_r16(val)                (signed short )(val*524288)
#define S_W_RANGE_Nr16_r16                     19

/* Res:   0.000003814697266         */
/* Range: [-1/8, 1/8)               */
typedef signed short                           T_W_RANGE_Nr8_r8;
#define V_W_RANGE_Nr8_r8(val)                  (signed short )(val*262144)
#define S_W_RANGE_Nr8_r8                       18

/* Res:   0.000007629394531         */
/* Range: [-1/4, 1/4)               */
typedef signed short                           T_W_RANGE_Nr4_r4;
#define V_W_RANGE_Nr4_r4(val)                  (signed short )(val*131072)
#define S_W_RANGE_Nr4_r4                       17

/* Res:   0.000015258789062         */
/* Range: [-1/2, 1/2)               */
typedef signed short                           T_W_RANGE_Nr2_r2;
#define V_W_RANGE_Nr2_r2(val)                  (signed short )(val*65536)
#define S_W_RANGE_Nr2_r2                       16

/* Res:   0.000030517578125         */
/* Range: [-1, 1)                   */
typedef signed short                           T_W_RANGE_N1_1;
#define V_W_RANGE_N1_1(val)                    (signed short )(val*32768)
#define S_W_RANGE_N1_1                         15

/* Res:   0.000061035156250         */
/* Range: [-2, 2)                   */
typedef signed short                           T_W_RANGE_N2_2;
#define V_W_RANGE_N2_2(val)                    (signed short )(val*16384)
#define S_W_RANGE_N2_2                         14

/* Res:   0.000122070312500         */
/* Range: [-4, 4)                   */
typedef signed short                           T_W_RANGE_N4_4;
#define V_W_RANGE_N4_4(val)                    (signed short )(val*8192)
#define S_W_RANGE_N4_4                         13

/* Res:   0.000244140625000         */
/* Range: [-8, 8)                   */
typedef signed short                           T_W_RANGE_N8_8;
#define V_W_RANGE_N8_8(val)                    (signed short )(val*4096)
#define S_W_RANGE_N8_8                         12

/* Res:   0.000488281250000         */
/* Range: [-16, 16)                 */
typedef signed short                           T_W_RANGE_N16_16;
#define V_W_RANGE_N16_16(val)                  (signed short )(val*2048)
#define S_W_RANGE_N16_16                       11

/* Res:   0.000976562500000         */
/* Range: [-32, 32)                 */
typedef signed short                           T_W_RANGE_N32_32;
#define V_W_RANGE_N32_32(val)                  (signed short )(val*1024)
#define S_W_RANGE_N32_32                       10

/* Res:   0.001953125000000         */
/* Range: [-64, 64)                 */
typedef signed short                           T_W_RANGE_N64_64;
#define V_W_RANGE_N64_64(val)                  (signed short )(val*512)
#define S_W_RANGE_N64_64                       9

/* Res:   0.003906250000000         */
/* Range: [-128, 128)               */
typedef signed short                           T_W_RANGE_N128_128;
#define V_W_RANGE_N128_128(val)                (signed short )(val*256)
#define S_W_RANGE_N128_128                     8

/* Res:   0.007812500000000         */
/* Range: [-256, 256)               */
typedef signed short                           T_W_RANGE_N256_256;
#define V_W_RANGE_N256_256(val)                (signed short )(val*128)
#define S_W_RANGE_N256_256                     7

/* Res:   0.015625000000000         */
/* Range: [-512, 512)               */
typedef signed short                           T_W_RANGE_N512_512;
#define V_W_RANGE_N512_512(val)                (signed short )(val*64)
#define S_W_RANGE_N512_512                     6

/* Res:   0.031250000000000         */
/* Range: [-1024, 1024)             */
typedef signed short                           T_W_RANGE_N1024_1024;
#define V_W_RANGE_N1024_1024(val)              (signed short )(val*32)
#define S_W_RANGE_N1024_1024                   5

/* Res:   0.062500000000000         */
/* Range: [-2048, 2048)             */
typedef signed short                           T_W_RANGE_N2048_2048;
#define V_W_RANGE_N2048_2048(val)              (signed short )(val*16)
#define S_W_RANGE_N2048_2048                   4

/* Res:   0.125000000000000         */
/* Range: [-4096, 4096)             */
typedef signed short                           T_W_RANGE_N4096_4096;
#define V_W_RANGE_N4096_4096(val)              (signed short )(val*8)
#define S_W_RANGE_N4096_4096                   3

/* Res:   0.250000000000000         */
/* Range: [-8192, 8192)             */
typedef signed short                           T_W_RANGE_N8192_8192;
#define V_W_RANGE_N8192_8192(val)              (signed short )(val*4)
#define S_W_RANGE_N8192_8192                   2

/* Res:   0.500000000000000         */
/* Range: [-16384, 16384)           */
typedef signed short                           T_W_RANGE_N16384_16384;
#define V_W_RANGE_N16384_16384(val)            (signed short )(val*2)
#define S_W_RANGE_N16384_16384                 1

/* Res:   1.000000000000000         */
/* Range: [-32768, 32768)           */
typedef signed short                           T_W_RANGE_N32768_32768;
#define V_W_RANGE_N32768_32768(val)            (signed short )(val*1)
#define S_W_RANGE_N32768_32768                 0

/******************************************************************************
 *  Unsigned 2-Byte Range Fixed Point Types
 ******************************************************************************/

/* Res:   0.000000059604645         */
/* Range: [0, 1/256)                */
typedef unsigned short                         T_W_RANGE_0_r256;
#define V_W_RANGE_0_r256(val)                  (unsigned short )(val*16777216)
#define S_W_RANGE_0_r256                       24

/* Res:   0.000000119209290         */
/* Range: [0, 1/128)                */
typedef unsigned short                         T_W_RANGE_0_r128;
#define V_W_RANGE_0_r128(val)                  (unsigned short )(val*8388608)
#define S_W_RANGE_0_r128                       23

/* Res:   0.000000238418579         */
/* Range: [0, 1/64)                 */
typedef unsigned short                         T_W_RANGE_0_r64;
#define V_W_RANGE_0_r64(val)                   (unsigned short )(val*4194304)
#define S_W_RANGE_0_r64                        22

/* Res:   0.000000476837158         */
/* Range: [0, 1/32)                 */
typedef unsigned short                         T_W_RANGE_0_r32;
#define V_W_RANGE_0_r32(val)                   (unsigned short )(val*2097152)
#define S_W_RANGE_0_r32                        21

/* Res:   0.000000953674316         */
/* Range: [0, 1/16)                 */
typedef unsigned short                         T_W_RANGE_0_r16;
#define V_W_RANGE_0_r16(val)                   (unsigned short )(val*1048576)
#define S_W_RANGE_0_r16                        20

/* Res:   0.000001907348633         */
/* Range: [0, 1/8)                  */
typedef unsigned short                         T_W_RANGE_0_r8;
#define V_W_RANGE_0_r8(val)                    (unsigned short )(val*524288)
#define S_W_RANGE_0_r8                         19

/* Res:   0.000003814697266         */
/* Range: [0, 1/4)                  */
typedef unsigned short                         T_W_RANGE_0_r4;
#define V_W_RANGE_0_r4(val)                    (unsigned short )(val*262144)
#define S_W_RANGE_0_r4                         18

/* Res:   0.000007629394531         */
/* Range: [0, 1/2)                  */
typedef unsigned short                         T_W_RANGE_0_r2;
#define V_W_RANGE_0_r2(val)                    (unsigned short )(val*131072)
#define S_W_RANGE_0_r2                         17

/* Res:   0.000015258789062         */
/* Range: [0, 1)                    */
typedef unsigned short                         T_W_RANGE_0_1;
#define V_W_RANGE_0_1(val)                     (unsigned short )(val*65536)
#define S_W_RANGE_0_1                          16

/* Res:   0.000030517578125         */
/* Range: [0, 2)                    */
typedef unsigned short                         T_W_RANGE_0_2;
#define V_W_RANGE_0_2(val)                     (unsigned short )(val*32768)
#define S_W_RANGE_0_2                          15

/* Res:   0.000061035156250         */
/* Range: [0, 4)                    */
typedef unsigned short                         T_W_RANGE_0_4;
#define V_W_RANGE_0_4(val)                     (unsigned short )(val*16384)
#define S_W_RANGE_0_4                          14

/* Res:   0.000122070312500         */
/* Range: [0, 8)                    */
typedef unsigned short                         T_W_RANGE_0_8;
#define V_W_RANGE_0_8(val)                     (unsigned short )(val*8192)
#define S_W_RANGE_0_8                          13

/* Res:   0.000244140625000         */
/* Range: [0, 16)                   */
typedef unsigned short                         T_W_RANGE_0_16;
#define V_W_RANGE_0_16(val)                    (unsigned short )(val*4096)
#define S_W_RANGE_0_16                         12

/* Res:   0.000488281250000         */
/* Range: [0, 32)                   */
typedef unsigned short                         T_W_RANGE_0_32;
#define V_W_RANGE_0_32(val)                    (unsigned short )(val*2048)
#define S_W_RANGE_0_32                         11

/* Res:   0.000976562500000         */
/* Range: [0, 64)                   */
typedef unsigned short                         T_W_RANGE_0_64;
#define V_W_RANGE_0_64(val)                    (unsigned short )(val*1024)
#define S_W_RANGE_0_64                         10

/* Res:   0.001953125000000         */
/* Range: [0, 128)                  */
typedef unsigned short                         T_W_RANGE_0_128;
#define V_W_RANGE_0_128(val)                   (unsigned short )(val*512)
#define S_W_RANGE_0_128                        9

/* Res:   0.003906250000000         */
/* Range: [0, 256)                  */
typedef unsigned short                         T_W_RANGE_0_256;
#define V_W_RANGE_0_256(val)                   (unsigned short )(val*256)
#define S_W_RANGE_0_256                        8

/* Res:   0.007812500000000         */
/* Range: [0, 512)                  */
typedef unsigned short                         T_W_RANGE_0_512;
#define V_W_RANGE_0_512(val)                   (unsigned short )(val*128)
#define S_W_RANGE_0_512                        7

/* Res:   0.015625000000000         */
/* Range: [0, 1024)                 */
typedef unsigned short                         T_W_RANGE_0_1024;
#define V_W_RANGE_0_1024(val)                  (unsigned short )(val*64)
#define S_W_RANGE_0_1024                       6

/* Res:   0.031250000000000         */
/* Range: [0, 2048)                 */
typedef unsigned short                         T_W_RANGE_0_2048;
#define V_W_RANGE_0_2048(val)                  (unsigned short )(val*32)
#define S_W_RANGE_0_2048                       5

/* Res:   0.062500000000000         */
/* Range: [0, 4096)                 */
typedef unsigned short                         T_W_RANGE_0_4096;
#define V_W_RANGE_0_4096(val)                  (unsigned short )(val*16)
#define S_W_RANGE_0_4096                       4

/* Res:   0.125000000000000         */
/* Range: [0, 8192)                 */
typedef unsigned short                         T_W_RANGE_0_8192;
#define V_W_RANGE_0_8192(val)                  (unsigned short )(val*8)
#define S_W_RANGE_0_8192                       3

/* Res:   0.250000000000000         */
/* Range: [0, 16384)                */
typedef unsigned short                         T_W_RANGE_0_16384;
#define V_W_RANGE_0_16384(val)                 (unsigned short )(val*4)
#define S_W_RANGE_0_16384                      2

/* Res:   0.500000000000000         */
/* Range: [0, 32768)                */
typedef unsigned short                         T_W_RANGE_0_32768;
#define V_W_RANGE_0_32768(val)                 (unsigned short )(val*2)
#define S_W_RANGE_0_32768                      1

/* Res:   1.000000000000000         */
/* Range: [0, 65536)                */
typedef unsigned short                         T_W_RANGE_0_65536;
#define V_W_RANGE_0_65536(val)                 (unsigned short )(val*1)
#define S_W_RANGE_0_65536                      0

/******************************************************************************
 *  Signed 4-Byte Range Fixed Point Types
 ******************************************************************************/

/* Res:   0.000000000001819         */
/* Range: [-1/256, 1/256)           */
typedef signed long                            T_L_RANGE_Nr256_r256;
#define V_L_RANGE_Nr256_r256(val)              (signed long )(val*549755813888)
#define S_L_RANGE_Nr256_r256                   39

/* Res:   0.000000000003638         */
/* Range: [-1/128, 1/128)           */
typedef signed long                            T_L_RANGE_Nr128_r128;
#define V_L_RANGE_Nr128_r128(val)              (signed long )(val*274877906944)
#define S_L_RANGE_Nr128_r128                   38

/* Res:   0.000000000007276         */
/* Range: [-1/64, 1/64)             */
typedef signed long                            T_L_RANGE_Nr64_r64;
#define V_L_RANGE_Nr64_r64(val)                (signed long )(val*137438953472)
#define S_L_RANGE_Nr64_r64                     37

/* Res:   0.000000000014552         */
/* Range: [-1/32, 1/32)             */
typedef signed long                            T_L_RANGE_Nr32_r32;
#define V_L_RANGE_Nr32_r32(val)                (signed long )(val*68719476736)
#define S_L_RANGE_Nr32_r32                     36

/* Res:   0.000000000029104         */
/* Range: [-1/16, 1/16)             */
typedef signed long                            T_L_RANGE_Nr16_r16;
#define V_L_RANGE_Nr16_r16(val)                (signed long )(val*34359738368)
#define S_L_RANGE_Nr16_r16                     35

/* Res:   0.000000000058208         */
/* Range: [-1/8, 1/8)               */
typedef signed long                            T_L_RANGE_Nr8_r8;
#define V_L_RANGE_Nr8_r8(val)                  (signed long )(val*17179869184)
#define S_L_RANGE_Nr8_r8                       34

/* Res:   0.000000000116415         */
/* Range: [-1/4, 1/4)               */
typedef signed long                            T_L_RANGE_Nr4_r4;
#define V_L_RANGE_Nr4_r4(val)                  (signed long )(val*8589934592)
#define S_L_RANGE_Nr4_r4                       33

/* Res:   0.000000000232831         */
/* Range: [-1/2, 1/2)               */
typedef signed long                            T_L_RANGE_Nr2_r2;
#define V_L_RANGE_Nr2_r2(val)                  (signed long )(val*4294967296)
#define S_L_RANGE_Nr2_r2                       32

/* Res:   0.000000000465661         */
/* Range: [-1, 1)                   */
typedef signed long                            T_L_RANGE_N1_1;
#define V_L_RANGE_N1_1(val)                    (signed long )(val*2147483648)
#define S_L_RANGE_N1_1                         31

/* Res:   0.000000000931323         */
/* Range: [-2, 2)                   */
typedef signed long                            T_L_RANGE_N2_2;
#define V_L_RANGE_N2_2(val)                    (signed long )(val*1073741824)
#define S_L_RANGE_N2_2                         30

/* Res:   0.000000001862645         */
/* Range: [-4, 4)                   */
typedef signed long                            T_L_RANGE_N4_4;
#define V_L_RANGE_N4_4(val)                    (signed long )(val*536870912)
#define S_L_RANGE_N4_4                         29

/* Res:   0.000000003725290         */
/* Range: [-8, 8)                   */
typedef signed long                            T_L_RANGE_N8_8;
#define V_L_RANGE_N8_8(val)                    (signed long )(val*268435456)
#define S_L_RANGE_N8_8                         28

/* Res:   0.000000007450581         */
/* Range: [-16, 16)                 */
typedef signed long                            T_L_RANGE_N16_16;
#define V_L_RANGE_N16_16(val)                  (signed long )(val*134217728)
#define S_L_RANGE_N16_16                       27

/* Res:   0.000000014901161         */
/* Range: [-32, 32)                 */
typedef signed long                            T_L_RANGE_N32_32;
#define V_L_RANGE_N32_32(val)                  (signed long )(val*67108864)
#define S_L_RANGE_N32_32                       26

/* Res:   0.000000029802322         */
/* Range: [-64, 64)                 */
typedef signed long                            T_L_RANGE_N64_64;
#define V_L_RANGE_N64_64(val)                  (signed long )(val*33554432)
#define S_L_RANGE_N64_64                       25

/* Res:   0.000000059604645         */
/* Range: [-128, 128)               */
typedef signed long                            T_L_RANGE_N128_128;
#define V_L_RANGE_N128_128(val)                (signed long )(val*16777216)
#define S_L_RANGE_N128_128                     24

/* Res:   0.000000119209290         */
/* Range: [-256, 256)               */
typedef signed long                            T_L_RANGE_N256_256;
#define V_L_RANGE_N256_256(val)                (signed long )(val*8388608)
#define S_L_RANGE_N256_256                     23

/* Res:   0.000000238418579         */
/* Range: [-512, 512)               */
typedef signed long                            T_L_RANGE_N512_512;
#define V_L_RANGE_N512_512(val)                (signed long )(val*4194304)
#define S_L_RANGE_N512_512                     22

/* Res:   0.000000476837158         */
/* Range: [-1024, 1024)             */
typedef signed long                            T_L_RANGE_N1024_1024;
#define V_L_RANGE_N1024_1024(val)              (signed long )(val*2097152)
#define S_L_RANGE_N1024_1024                   21

/* Res:   0.000000953674316         */
/* Range: [-2048, 2048)             */
typedef signed long                            T_L_RANGE_N2048_2048;
#define V_L_RANGE_N2048_2048(val)              (signed long )(val*1048576)
#define S_L_RANGE_N2048_2048                   20

/* Res:   0.000001907348633         */
/* Range: [-4096, 4096)             */
typedef signed long                            T_L_RANGE_N4096_4096;
#define V_L_RANGE_N4096_4096(val)              (signed long )(val*524288)
#define S_L_RANGE_N4096_4096                   19

/* Res:   0.000003814697266         */
/* Range: [-8192, 8192)             */
typedef signed long                            T_L_RANGE_N8192_8192;
#define V_L_RANGE_N8192_8192(val)              (signed long )(val*262144)
#define S_L_RANGE_N8192_8192                   18

/* Res:   0.000007629394531         */
/* Range: [-16384, 16384)           */
typedef signed long                            T_L_RANGE_N16384_16384;
#define V_L_RANGE_N16384_16384(val)            (signed long )(val*131072)
#define S_L_RANGE_N16384_16384                 17

/* Res:   0.000015258789062         */
/* Range: [-32768, 32768)           */
typedef signed long                            T_L_RANGE_N32768_32768;
#define V_L_RANGE_N32768_32768(val)            (signed long )(val*65536)
#define S_L_RANGE_N32768_32768                 16

/* Res:   0.000030517578125         */
/* Range: [-65536, 65536)           */
typedef signed long                            T_L_RANGE_N65536_65536;
#define V_L_RANGE_N65536_65536(val)            (signed long )(val*32768)
#define S_L_RANGE_N65536_65536                 15

/* Res:   0.000061035156250         */
/* Range: [-131072, 131072)         */
typedef signed long                            T_L_RANGE_N131072_131072;
#define V_L_RANGE_N131072_131072(val)          (signed long )(val*16384)
#define S_L_RANGE_N131072_131072               14

/* Res:   0.000122070312500         */
/* Range: [-262144, 262144)         */
typedef signed long                            T_L_RANGE_N262144_262144;
#define V_L_RANGE_N262144_262144(val)          (signed long )(val*8192)
#define S_L_RANGE_N262144_262144               13

/* Res:   0.000244140625000         */
/* Range: [-524288, 524288)         */
typedef signed long                            T_L_RANGE_N524288_524288;
#define V_L_RANGE_N524288_524288(val)          (signed long )(val*4096)
#define S_L_RANGE_N524288_524288               12

/* Res:   0.000488281250000         */
/* Range: [-1048576, 1048576)       */
typedef signed long                            T_L_RANGE_N1048576_1048576;
#define V_L_RANGE_N1048576_1048576(val)        (signed long )(val*2048)
#define S_L_RANGE_N1048576_1048576             11

/* Res:   0.000976562500000         */
/* Range: [-2097152, 2097152)       */
typedef signed long                            T_L_RANGE_N2097152_2097152;
#define V_L_RANGE_N2097152_2097152(val)        (signed long )(val*1024)
#define S_L_RANGE_N2097152_2097152             10

/* Res:   0.001953125000000         */
/* Range: [-4194304, 4194304)       */
typedef signed long                            T_L_RANGE_N4194304_4194304;
#define V_L_RANGE_N4194304_4194304(val)        (signed long )(val*512)
#define S_L_RANGE_N4194304_4194304             9

/* Res:   0.003906250000000         */
/* Range: [-8388608, 8388608)       */
typedef signed long                            T_L_RANGE_N8388608_8388608;
#define V_L_RANGE_N8388608_8388608(val)        (signed long )(val*256)
#define S_L_RANGE_N8388608_8388608             8

/* Res:   0.007812500000000         */
/* Range: [-16777216, 16777216)     */
typedef signed long                            T_L_RANGE_N16777216_16777216;
#define V_L_RANGE_N16777216_16777216(val)      (signed long )(val*128)
#define S_L_RANGE_N16777216_16777216           7

/* Res:   0.015625000000000         */
/* Range: [-33554432, 33554432)     */
typedef signed long                            T_L_RANGE_N33554432_33554432;
#define V_L_RANGE_N33554432_33554432(val)      (signed long )(val*64)
#define S_L_RANGE_N33554432_33554432           6

/* Res:   0.031250000000000         */
/* Range: [-67108864, 67108864)     */
typedef signed long                            T_L_RANGE_N67108864_67108864;
#define V_L_RANGE_N67108864_67108864(val)      (signed long )(val*32)
#define S_L_RANGE_N67108864_67108864           5

/* Res:   0.062500000000000         */
/* Range: [-134217728, 134217728)   */
typedef signed long                            T_L_RANGE_N134217728_134217728;
#define V_L_RANGE_N134217728_134217728(val)    (signed long )(val*16)
#define S_L_RANGE_N134217728_134217728         4

/* Res:   0.125000000000000         */
/* Range: [-268435456, 268435456)   */
typedef signed long                            T_L_RANGE_N268435456_268435456;
#define V_L_RANGE_N268435456_268435456(val)    (signed long )(val*8)
#define S_L_RANGE_N268435456_268435456         3

/* Res:   0.250000000000000         */
/* Range: [-536870912, 536870912)   */
typedef signed long                            T_L_RANGE_N536870912_536870912;
#define V_L_RANGE_N536870912_536870912(val)    (signed long )(val*4)
#define S_L_RANGE_N536870912_536870912         2

/* Res:   0.500000000000000         */
/* Range: [-1073741824, 1073741824) */
typedef signed long                            T_L_RANGE_N1073741824_1073741824;
#define V_L_RANGE_N1073741824_1073741824(val)  (signed long )(val*2)
#define S_L_RANGE_N1073741824_1073741824       1

/* Res:   1.000000000000000         */
/* Range: [-2147483648, 2147483648) */
typedef signed long                            T_L_RANGE_N2147483648_2147483648;
#define V_L_RANGE_N2147483648_2147483648(val)  (signed long )(val*1)
#define S_L_RANGE_N2147483648_2147483648       0

/******************************************************************************
 *  Unsigned 4-Byte Range Fixed Point Types
 ******************************************************************************/

/* Res:   0.000000000000909         */
/* Range: [0, 1/256)                */
typedef unsigned long                          T_L_RANGE_0_r256;
#define V_L_RANGE_0_r256(val)                  (unsigned long )(val*1099511627776)
#define S_L_RANGE_0_r256                       40

/* Res:   0.000000000001819         */
/* Range: [0, 1/128)                */
typedef unsigned long                          T_L_RANGE_0_r128;
#define V_L_RANGE_0_r128(val)                  (unsigned long )(val*549755813888)
#define S_L_RANGE_0_r128                       39

/* Res:   0.000000000003638         */
/* Range: [0, 1/64)                 */
typedef unsigned long                          T_L_RANGE_0_r64;
#define V_L_RANGE_0_r64(val)                   (unsigned long )(val*274877906944)
#define S_L_RANGE_0_r64                        38

/* Res:   0.000000000007276         */
/* Range: [0, 1/32)                 */
typedef unsigned long                          T_L_RANGE_0_r32;
#define V_L_RANGE_0_r32(val)                   (unsigned long )(val*137438953472)
#define S_L_RANGE_0_r32                        37

/* Res:   0.000000000014552         */
/* Range: [0, 1/16)                 */
typedef unsigned long                          T_L_RANGE_0_r16;
#define V_L_RANGE_0_r16(val)                   (unsigned long )(val*68719476736)
#define S_L_RANGE_0_r16                        36

/* Res:   0.000000000029104         */
/* Range: [0, 1/8)                  */
typedef unsigned long                          T_L_RANGE_0_r8;
#define V_L_RANGE_0_r8(val)                    (unsigned long )(val*34359738368)
#define S_L_RANGE_0_r8                         35

/* Res:   0.000000000058208         */
/* Range: [0, 1/4)                  */
typedef unsigned long                          T_L_RANGE_0_r4;
#define V_L_RANGE_0_r4(val)                    (unsigned long )(val*17179869184)
#define S_L_RANGE_0_r4                         34

/* Res:   0.000000000116415         */
/* Range: [0, 1/2)                  */
typedef unsigned long                          T_L_RANGE_0_r2;
#define V_L_RANGE_0_r2(val)                    (unsigned long )(val*8589934592)
#define S_L_RANGE_0_r2                         33

/* Res:   0.000000000232831         */
/* Range: [0, 1)                    */
typedef unsigned long                          T_L_RANGE_0_1;
#define V_L_RANGE_0_1(val)                     (unsigned long )(val*4294967296)
#define S_L_RANGE_0_1                          32

/* Res:   0.000000000465661         */
/* Range: [0, 2)                    */
typedef unsigned long                          T_L_RANGE_0_2;
#define V_L_RANGE_0_2(val)                     (unsigned long )(val*2147483648)
#define S_L_RANGE_0_2                          31

/* Res:   0.000000000931323         */
/* Range: [0, 4)                    */
typedef unsigned long                          T_L_RANGE_0_4;
#define V_L_RANGE_0_4(val)                     (unsigned long )(val*1073741824)
#define S_L_RANGE_0_4                          30

/* Res:   0.000000001862645         */
/* Range: [0, 8)                    */
typedef unsigned long                          T_L_RANGE_0_8;
#define V_L_RANGE_0_8(val)                     (unsigned long )(val*536870912)
#define S_L_RANGE_0_8                          29

/* Res:   0.000000003725290         */
/* Range: [0, 16)                   */
typedef unsigned long                          T_L_RANGE_0_16;
#define V_L_RANGE_0_16(val)                    (unsigned long )(val*268435456)
#define S_L_RANGE_0_16                         28

/* Res:   0.000000007450581         */
/* Range: [0, 32)                   */
typedef unsigned long                          T_L_RANGE_0_32;
#define V_L_RANGE_0_32(val)                    (unsigned long )(val*134217728)
#define S_L_RANGE_0_32                         27

/* Res:   0.000000014901161         */
/* Range: [0, 64)                   */
typedef unsigned long                          T_L_RANGE_0_64;
#define V_L_RANGE_0_64(val)                    (unsigned long )(val*67108864)
#define S_L_RANGE_0_64                         26

/* Res:   0.000000029802322         */
/* Range: [0, 128)                  */
typedef unsigned long                          T_L_RANGE_0_128;
#define V_L_RANGE_0_128(val)                   (unsigned long )(val*33554432)
#define S_L_RANGE_0_128                        25

/* Res:   0.000000059604645         */
/* Range: [0, 256)                  */
typedef unsigned long                          T_L_RANGE_0_256;
#define V_L_RANGE_0_256(val)                   (unsigned long )(val*16777216)
#define S_L_RANGE_0_256                        24

/* Res:   0.000000119209290         */
/* Range: [0, 512)                  */
typedef unsigned long                          T_L_RANGE_0_512;
#define V_L_RANGE_0_512(val)                   (unsigned long )(val*8388608)
#define S_L_RANGE_0_512                        23

/* Res:   0.000000238418579         */
/* Range: [0, 1024)                 */
typedef unsigned long                          T_L_RANGE_0_1024;
#define V_L_RANGE_0_1024(val)                  (unsigned long )(val*4194304)
#define S_L_RANGE_0_1024                       22

/* Res:   0.000000476837158         */
/* Range: [0, 2048)                 */
typedef unsigned long                          T_L_RANGE_0_2048;
#define V_L_RANGE_0_2048(val)                  (unsigned long )(val*2097152)
#define S_L_RANGE_0_2048                       21

/* Res:   0.000000953674316         */
/* Range: [0, 4096)                 */
typedef unsigned long                          T_L_RANGE_0_4096;
#define V_L_RANGE_0_4096(val)                  (unsigned long )(val*1048576)
#define S_L_RANGE_0_4096                       20

/* Res:   0.000001907348633         */
/* Range: [0, 8192)                 */
typedef unsigned long                          T_L_RANGE_0_8192;
#define V_L_RANGE_0_8192(val)                  (unsigned long )(val*524288)
#define S_L_RANGE_0_8192                       19

/* Res:   0.000003814697266         */
/* Range: [0, 16384)                */
typedef unsigned long                          T_L_RANGE_0_16384;
#define V_L_RANGE_0_16384(val)                 (unsigned long )(val*262144)
#define S_L_RANGE_0_16384                      18

/* Res:   0.000007629394531         */
/* Range: [0, 32768)                */
typedef unsigned long                          T_L_RANGE_0_32768;
#define V_L_RANGE_0_32768(val)                 (unsigned long )(val*131072)
#define S_L_RANGE_0_32768                      17

/* Res:   0.000015258789062         */
/* Range: [0, 65536)                */
typedef unsigned long                          T_L_RANGE_0_65536;
#define V_L_RANGE_0_65536(val)                 (unsigned long )(val*65536)
#define S_L_RANGE_0_65536                      16

/* Res:   0.000030517578125         */
/* Range: [0, 131072)               */
typedef unsigned long                          T_L_RANGE_0_131072;
#define V_L_RANGE_0_131072(val)                (unsigned long )(val*32768)
#define S_L_RANGE_0_131072                     15

/* Res:   0.000061035156250         */
/* Range: [0, 262144)               */
typedef unsigned long                          T_L_RANGE_0_262144;
#define V_L_RANGE_0_262144(val)                (unsigned long )(val*16384)
#define S_L_RANGE_0_262144                     14

/* Res:   0.000122070312500         */
/* Range: [0, 524288)               */
typedef unsigned long                          T_L_RANGE_0_524288;
#define V_L_RANGE_0_524288(val)                (unsigned long )(val*8192)
#define S_L_RANGE_0_524288                     13

/* Res:   0.000244140625000         */
/* Range: [0, 1048576)              */
typedef unsigned long                          T_L_RANGE_0_1048576;
#define V_L_RANGE_0_1048576(val)               (unsigned long )(val*4096)
#define S_L_RANGE_0_1048576                    12

/* Res:   0.000488281250000         */
/* Range: [0, 2097152)              */
typedef unsigned long                          T_L_RANGE_0_2097152;
#define V_L_RANGE_0_2097152(val)               (unsigned long )(val*2048)
#define S_L_RANGE_0_2097152                    11

/* Res:   0.000976562500000         */
/* Range: [0, 4194304)              */
typedef unsigned long                          T_L_RANGE_0_4194304;
#define V_L_RANGE_0_4194304(val)               (unsigned long )(val*1024)
#define S_L_RANGE_0_4194304                    10

/* Res:   0.001953125000000         */
/* Range: [0, 8388608)              */
typedef unsigned long                          T_L_RANGE_0_8388608;
#define V_L_RANGE_0_8388608(val)               (unsigned long )(val*512)
#define S_L_RANGE_0_8388608                    9

/* Res:   0.003906250000000         */
/* Range: [0, 16777216)             */
typedef unsigned long                          T_L_RANGE_0_16777216;
#define V_L_RANGE_0_16777216(val)              (unsigned long )(val*256)
#define S_L_RANGE_0_16777216                   8

/* Res:   0.007812500000000         */
/* Range: [0, 33554432)             */
typedef unsigned long                          T_L_RANGE_0_33554432;
#define V_L_RANGE_0_33554432(val)              (unsigned long )(val*128)
#define S_L_RANGE_0_33554432                   7

/* Res:   0.015625000000000         */
/* Range: [0, 67108864)             */
typedef unsigned long                          T_L_RANGE_0_67108864;
#define V_L_RANGE_0_67108864(val)              (unsigned long )(val*64)
#define S_L_RANGE_0_67108864                   6

/* Res:   0.031250000000000         */
/* Range: [0, 134217728)            */
typedef unsigned long                          T_L_RANGE_0_134217728;
#define V_L_RANGE_0_134217728(val)             (unsigned long )(val*32)
#define S_L_RANGE_0_134217728                  5

/* Res:   0.062500000000000         */
/* Range: [0, 268435456)            */
typedef unsigned long                          T_L_RANGE_0_268435456;
#define V_L_RANGE_0_268435456(val)             (unsigned long )(val*16)
#define S_L_RANGE_0_268435456                  4

/* Res:   0.125000000000000         */
/* Range: [0, 536870912)            */
typedef unsigned long                          T_L_RANGE_0_536870912;
#define V_L_RANGE_0_536870912(val)             (unsigned long )(val*8)
#define S_L_RANGE_0_536870912                  3

/* Res:   0.250000000000000         */
/* Range: [0, 1073741824)           */
typedef unsigned long                          T_L_RANGE_0_1073741824;
#define V_L_RANGE_0_1073741824(val)            (unsigned long )(val*4)
#define S_L_RANGE_0_1073741824                 2

/* Res:   0.500000000000000         */
/* Range: [0, 2147483648)           */
typedef unsigned long                          T_L_RANGE_0_2147483648;
#define V_L_RANGE_0_2147483648(val)            (unsigned long )(val*2)
#define S_L_RANGE_0_2147483648                 1

/* Res:   1.000000000000000         */
/* Range: [0, 4294967296)           */
typedef unsigned long                          T_L_RANGE_0_4294967296;
#define V_L_RANGE_0_4294967296(val)            (unsigned long )(val*1)
#define S_L_RANGE_0_4294967296                 0

#endif /* T_RANGE_H */

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1.1   020304 gps 1637 Oil Pressure & Temperature Estimation.
*                       Created file.
* 1.2   020717 gps 1970 VCPS : Additional Diagnostics.
*                       Removed not needed keyword "int"
*                        from all type definitions.
* 3     021030 gps 2218 VCPS : VE Tables Size Change from 2 to 1 Byte.
*                       Added "reciprocal types".
* 4     030319 gps 2226 VCPS : Cam Bounding.
*                       Corrected T_L_RANGE_0_X type definitions.
*
******************************************************************************/
