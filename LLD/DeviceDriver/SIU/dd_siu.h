#ifndef DD_SIU_H
#define DD_SIU_H
//=============================================================================
//
//       COPYRIGHT, 2006, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:   dd_siu.h~kok_pt2#3:incl:tci_pt2#14 %
//
// created_by:       gzdmlz
//
// date_created:     Tue Jan 17 16:06:18 2006
//
// %derived_by:      nztnkh %
//
// %date_modified:   Wed Jun 29 13:00:05 2011 %
//
// %version:         kok_pt2#3 %
//
// ============================================================================
// @doc
//
// @module dd_siu.h | System Integration Unit
//
// The purpose of this module is to 
//
// <nl> Put a brief description here 
// brief description continued
// brief description continued
//
// @normal Copyright <cp> 2006, Delphi Technologies, Inc. All Rights reserved
//
// @topic SIU API Overview |  add some kind of overview here
//
// @end
//
// SPECIFICATION REVISION:
// MPC563X RM Reference Manual Revision 1.0 25 July 2008
//
// ============================================================================
// Configurable Development Software Module:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
//
//=============================================================================


//=============================================================================
//                                Includes
//=============================================================================

#include "hw_siu.h"
#include "dd_siu_hwinfo.h"
#include "dd_intc.h"

//=============================================================================
// @globalv SIU_T | SIU |
// The Register Memory Overlay of the System Integration Unit
// to provide software access and debug information.
//
// @end
//=============================================================================
#define SECTION_SIU_REGISTER
#include "section.h"
extern SIU_T SIU;
#define SECTION_END
#include "section.h"

// @enum SIU_GPIO_Channel_T | Defines the available Pins for the Port Configuration
typedef enum
{
   SIU_GPIO_CHANNEL_RESERVED_0,              //@emem GPIO Pin 0 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_1,              //@emem GPIO Pin 1 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_2,              //@emem GPIO Pin 2 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_3,              //@emem GPIO Pin 3 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_4,              //@emem GPIO Pin 4 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_5,              //@emem GPIO Pin 5 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_6,              //@emem GPIO Pin 6 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_7,              //@emem GPIO Pin 7 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_8,              //@emem GPIO Pin 8 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_9,              //@emem GPIO Pin 9 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_10,             //@emem GPIO Pin 10 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_11,             //@emem GPIO Pin 11 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_12,             //@emem GPIO Pin 12 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_13,             //@emem GPIO Pin 13 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_14,             //@emem GPIO Pin 14 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_15,             //@emem GPIO Pin 15 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_16,             //@emem GPIO Pin 16 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_17,             //@emem GPIO Pin 17 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_18,             //@emem GPIO Pin 18 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_19,             //@emem GPIO Pin 19 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_20,             //@emem GPIO Pin 20 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_21,             //@emem GPIO Pin 21 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_22,             //@emem GPIO Pin 22 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_23,             //@emem GPIO Pin 23 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_24,             //@emem GPIO Pin 24 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_25,             //@emem GPIO Pin 25 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_26,             //@emem GPIO Pin 26 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_27,             //@emem GPIO Pin 27 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_28,             //@emem GPIO Pin 28 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_29,             //@emem GPIO Pin 29 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_30,             //@emem GPIO Pin 30 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_31,             //@emem GPIO Pin 31 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_32,             //@emem GPIO Pin 32 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_33,             //@emem GPIO Pin 33 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_34,             //@emem GPIO Pin 34 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_35,             //@emem GPIO Pin 35 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_36,             //@emem GPIO Pin 36 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_37,             //@emem GPIO Pin 37 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_38,             //@emem GPIO Pin 38 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_39,             //@emem GPIO Pin 39 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_40,             //@emem GPIO Pin 40 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_41,             //@emem GPIO Pin 41 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_42,             //@emem GPIO Pin 42 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_43,             //@emem GPIO Pin 43 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_44,             //@emem GPIO Pin 44 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_45,             //@emem GPIO Pin 45 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_46,             //@emem GPIO Pin 46 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_47,             //@emem GPIO Pin 47 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_48,             //@emem GPIO Pin 48 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_49,             //@emem GPIO Pin 49 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_50,             //@emem GPIO Pin 50 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_51,             //@emem GPIO Pin 51 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_52,             //@emem GPIO Pin 52 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_53,             //@emem GPIO Pin 53 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_54,             //@emem GPIO Pin 54 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_55,             //@emem GPIO Pin 55 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_56,             //@emem GPIO Pin 56 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_57,             //@emem GPIO Pin 57 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_58,             //@emem GPIO Pin 58 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_59,             //@emem GPIO Pin 59 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_60,             //@emem GPIO Pin 60 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_61,             //@emem GPIO Pin 61 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_62,             //@emem GPIO Pin 62 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_63,             //@emem GPIO Pin 63 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_64,             //@emem GPIO Pin 64 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_65,             //@emem GPIO Pin 65 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_66,             //@emem GPIO Pin 66 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_67,             //@emem GPIO Pin 67 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_68,             //@emem GPIO Pin 68 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_69,             //@emem GPIO Pin 69 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_70,             //@emem GPIO Pin 70 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_71,             //@emem GPIO Pin 71 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_72,             //@emem GPIO Pin 72 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_73,             //@emem GPIO Pin 73 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_74,             //@emem GPIO Pin 74 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_75,             //@emem GPIO Pin 75 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_76,             //@emem GPIO Pin 76 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_77,             //@emem GPIO Pin 77 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_78,             //@emem GPIO Pin 78 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_79,             //@emem GPIO Pin 79 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_80,             //@emem GPIO Pin 80 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_81,             //@emem GPIO Pin 81 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_82,             //@emem GPIO Pin 82 RESERVED
   SIU_GPIO_CHANNEL_83,                      //@emem GPIO Pin 83
   SIU_GPIO_CHANNEL_84,                      //@emem GPIO Pin 84
   SIU_GPIO_CHANNEL_RESERVED_85,             //@emem GPIO Pin 85 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_86,             //@emem GPIO Pin 86 RESERVED
   SIU_GPIO_CHANNEL_87,                      //@emem GPIO Pin 87
   SIU_GPIO_CHANNEL_88,                      //@emem GPIO Pin 88
   SIU_GPIO_CHANNEL_89,                      //@emem GPIO Pin 89
   SIU_GPIO_CHANNEL_90,                      //@emem GPIO Pin 90
   SIU_GPIO_CHANNEL_91,                      //@emem GPIO Pin 91
   SIU_GPIO_CHANNEL_92,                      //@emem GPIO Pin 92
   SIU_GPIO_CHANNEL_RESERVED_93,             //@emem GPIO Pin 93 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_94,             //@emem GPIO Pin 94 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_95,             //@emem GPIO Pin 95 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_96,             //@emem GPIO Pin 96 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_97,             //@emem GPIO Pin 97 RESERVED
   SIU_GPIO_CHANNEL_98,                      //@emem GPIO Pin 98
   SIU_GPIO_CHANNEL_99,                      //@emem GPIO Pin 99
   SIU_GPIO_CHANNEL_RESERVED_100,            //@emem GPIO Pin 100 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_101,            //@emem GPIO Pin 101 RESERVED
   SIU_GPIO_CHANNEL_102,                     //@emem GPIO Pin 102
   SIU_GPIO_CHANNEL_103,                     //@emem GPIO Pin 103
   SIU_GPIO_CHANNEL_104,                     //@emem GPIO Pin 104
   SIU_GPIO_CHANNEL_105,                     //@emem GPIO Pin 105
   SIU_GPIO_CHANNEL_106,                     //@emem GPIO Pin 106
   SIU_GPIO_CHANNEL_107,                     //@emem GPIO Pin 107
   SIU_GPIO_CHANNEL_108,                     //@emem GPIO Pin 108
   SIU_GPIO_CHANNEL_109,                     //@emem GPIO Pin 109
   SIU_GPIO_CHANNEL_110,                     //@emem GPIO Pin 110
   SIU_GPIO_CHANNEL_RESERVED_111,            //@emem GPIO Pin 111 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_112,            //@emem GPIO Pin 112 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_113,            //@emem GPIO Pin 113 RESERVED
   SIU_GPIO_CHANNEL_114,                     //@emem GPIO Pin 114
   SIU_GPIO_CHANNEL_115,                     //@emem GPIO Pin 115
   SIU_GPIO_CHANNEL_116,                     //@emem GPIO Pin 116
   SIU_GPIO_CHANNEL_117,                     //@emem GPIO Pin 117
   SIU_GPIO_CHANNEL_118,                     //@emem GPIO Pin 118
   SIU_GPIO_CHANNEL_119,                     //@emem GPIO Pin 119
   SIU_GPIO_CHANNEL_120,                     //@emem GPIO Pin 120
   SIU_GPIO_CHANNEL_121,                     //@emem GPIO Pin 121
   SIU_GPIO_CHANNEL_122,                     //@emem GPIO Pin 122
   SIU_GPIO_CHANNEL_123,                     //@emem GPIO Pin 123
   SIU_GPIO_CHANNEL_124,                     //@emem GPIO Pin 124
   SIU_GPIO_CHANNEL_125,                     //@emem GPIO Pin 125
   SIU_GPIO_CHANNEL_126,                     //@emem GPIO Pin 126
   SIU_GPIO_CHANNEL_127,                     //@emem GPIO Pin 127
   SIU_GPIO_CHANNEL_128,                     //@emem GPIO Pin 128
   SIU_GPIO_CHANNEL_129,                     //@emem GPIO Pin 129
   SIU_GPIO_CHANNEL_130,                     //@emem GPIO Pin 130
   SIU_GPIO_CHANNEL_131,                     //@emem GPIO Pin 131
   SIU_GPIO_CHANNEL_132,                     //@emem GPIO Pin 132
   SIU_GPIO_CHANNEL_133,                     //@emem GPIO Pin 133
   SIU_GPIO_CHANNEL_134,                     //@emem GPIO Pin 134
   SIU_GPIO_CHANNEL_135,                     //@emem GPIO Pin 135
   SIU_GPIO_CHANNEL_136,                     //@emem GPIO Pin 136
   SIU_GPIO_CHANNEL_137,                     //@emem GPIO Pin 137
   SIU_GPIO_CHANNEL_138,                     //@emem GPIO Pin 138
   SIU_GPIO_CHANNEL_139,                     //@emem GPIO Pin 139
   SIU_GPIO_CHANNEL_140,                     //@emem GPIO Pin 140
   SIU_GPIO_CHANNEL_141,                     //@emem GPIO Pin 141
   SIU_GPIO_CHANNEL_142,                     //@emem GPIO Pin 142
   SIU_GPIO_CHANNEL_143,                     //@emem GPIO Pin 143
   SIU_GPIO_CHANNEL_144,                     //@emem GPIO Pin 144
   SIU_GPIO_CHANNEL_145,                     //@emem GPIO Pin 145
   SIU_GPIO_CHANNEL_RESERVED_146,            //@emem GPIO Pin 146 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_147,            //@emem GPIO Pin 147 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_148,            //@emem GPIO Pin 148 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_149,            //@emem GPIO Pin 149 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_150,            //@emem GPIO Pin 150 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_151,            //@emem GPIO Pin 151 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_152,            //@emem GPIO Pin 152 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_153,            //@emem GPIO Pin 153 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_154,            //@emem GPIO Pin 154 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_155,            //@emem GPIO Pin 155 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_156,            //@emem GPIO Pin 156 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_157,            //@emem GPIO Pin 157 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_158,            //@emem GPIO Pin 158 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_159,            //@emem GPIO Pin 159 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_160,            //@emem GPIO Pin 160 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_161,            //@emem GPIO Pin 161 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_162,            //@emem GPIO Pin 162 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_163,            //@emem GPIO Pin 163 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_164,            //@emem GPIO Pin 164 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_165,            //@emem GPIO Pin 165 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_166,            //@emem GPIO Pin 166 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_167,            //@emem GPIO Pin 167 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_168,            //@emem GPIO Pin 168 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_169,            //@emem GPIO Pin 169 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_170,            //@emem GPIO Pin 170 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_171,            //@emem GPIO Pin 171 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_172,            //@emem GPIO Pin 172 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_173,            //@emem GPIO Pin 173 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_174,            //@emem GPIO Pin 174 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_175,            //@emem GPIO Pin 175 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_176,            //@emem GPIO Pin 176 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_177,            //@emem GPIO Pin 177 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_178,            //@emem GPIO Pin 178 RESERVED
   SIU_GPIO_CHANNEL_179,                     //@emem GPIO Pin 179
   SIU_GPIO_CHANNEL_180,                     //@emem GPIO Pin 180
   SIU_GPIO_CHANNEL_181,                     //@emem GPIO Pin 181
   SIU_GPIO_CHANNEL_RESERVED_182,            //@emem GPIO Pin 182 RESERVED
   SIU_GPIO_CHANNEL_183,                     //@emem GPIO Pin 183
   SIU_GPIO_CHANNEL_RESERVED_184,            //@emem GPIO Pin 184 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_185,            //@emem GPIO Pin 185 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_186,            //@emem GPIO Pin 186 RESERVED
   SIU_GPIO_CHANNEL_187,                     //@emem GPIO Pin 187
   SIU_GPIO_CHANNEL_188,                     //@emem GPIO Pin 188
   SIU_GPIO_CHANNEL_189,                     //@emem GPIO Pin 189
   SIU_GPIO_CHANNEL_190,                     //@emem GPIO Pin 190
   SIU_GPIO_CHANNEL_191,                     //@emem GPIO Pin 191
   SIU_GPIO_CHANNEL_192,                     //@emem GPIO Pin 192
   SIU_GPIO_CHANNEL_193,                     //@emem GPIO Pin 193
   SIU_GPIO_CHANNEL_194,                     //@emem GPIO Pin 194
   SIU_GPIO_CHANNEL_RESERVED_195,            //@emem GPIO Pin 195 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_196,            //@emem GPIO Pin 196 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_197,            //@emem GPIO Pin 197 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_198,            //@emem GPIO Pin 198 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_199,            //@emem GPIO Pin 199 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_200,            //@emem GPIO Pin 200 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_201,            //@emem GPIO Pin 201 RESERVED
   SIU_GPIO_CHANNEL_202,                     //@emem GPIO Pin 202
   SIU_GPIO_CHANNEL_RESERVED_203,            //@emem GPIO Pin 203 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_204,            //@emem GPIO Pin 204 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_205,            //@emem GPIO Pin 205 RESERVED
   SIU_GPIO_CHANNEL_206,                     //@emem GPIO Pin 206
   SIU_GPIO_CHANNEL_207,                     //@emem GPIO Pin 207
   SIU_GPIO_CHANNEL_208,                     //@emem GPIO Pin 208
   SIU_GPIO_CHANNEL_RESERVED_209,            //@emem GPIO Pin 209 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_210,            //@emem GPIO Pin 210 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_211,            //@emem GPIO Pin 211 RESERVED
   SIU_GPIO_CHANNEL_212,                     //@emem GPIO Pin 212
   SIU_GPIO_CHANNEL_213,                     //@emem GPIO Pin 213
   SIU_GPIO_CHANNEL_RESERVED_214,            //@emem GPIO Pin 214 RESERVED
   SIU_GPIO_CHANNEL_215,                     //@emem GPIO Pin 215
   SIU_GPIO_CHANNEL_216,                     //@emem GPIO Pin 216
   SIU_GPIO_CHANNEL_217,                     //@emem GPIO Pin 217
   SIU_GPIO_CHANNEL_218,                     //@emem GPIO Pin 218
   SIU_GPIO_CHANNEL_219,                     //@emem GPIO Pin 219
   SIU_GPIO_CHANNEL_220,                     //@emem GPIO Pin 220
   SIU_GPIO_CHANNEL_221,                     //@emem GPIO Pin 221
   SIU_GPIO_CHANNEL_222,                     //@emem GPIO Pin 222
   SIU_GPIO_CHANNEL_223,                     //@emem GPIO Pin 223
   SIU_GPIO_CHANNEL_224,                     //@emem GPIO Pin 224
   SIU_GPIO_CHANNEL_225,                     //@emem GPIO Pin 225
   SIU_GPIO_CHANNEL_RESERVED_226,            //@emem GPIO Pin 226 RESERVED
   SIU_GPIO_CHANNEL_227,                     //@emem GPIO Pin 227
   SIU_GPIO_CHANNEL_228,                     //@emem GPIO Pin 228
   SIU_GPIO_CHANNEL_229,                     //@emem GPIO Pin 229
   SIU_GPIO_CHANNEL_230,                     //@emem GPIO Pin 230
   SIU_GPIO_CHANNEL_231,                     //@emem GPIO Pin 231
   SIU_GPIO_CHANNEL_232,                     //@emem GPIO Pin 232
   SIU_GPIO_CHANNEL_RESERVED_233,            //@emem GPIO Pin 233 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_234,            //@emem GPIO Pin 234 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_235,            //@emem GPIO Pin 235 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_236,            //@emem GPIO Pin 236 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_237,            //@emem GPIO Pin 237 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_238,            //@emem GPIO Pin 238 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_239,            //@emem GPIO Pin 239 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_240,            //@emem GPIO Pin 240 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_241,            //@emem GPIO Pin 241 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_242,            //@emem GPIO Pin 242 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_243,            //@emem GPIO Pin 243 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_244,            //@emem GPIO Pin 244 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_245,            //@emem GPIO Pin 245 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_246,            //@emem GPIO Pin 246 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_247,            //@emem GPIO Pin 247 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_248,            //@emem GPIO Pin 248 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_249,            //@emem GPIO Pin 249 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_250,            //@emem GPIO Pin 250 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_251,            //@emem GPIO Pin 251 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_252,            //@emem GPIO Pin 252 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_253,            //@emem GPIO Pin 253 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_254,            //@emem GPIO Pin 254 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_255,            //@emem GPIO Pin 255 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_256,            //@emem GPIO Pin 256 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_257,            //@emem GPIO Pin 257 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_258,            //@emem GPIO Pin 258 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_259,            //@emem GPIO Pin 259 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_260,            //@emem GPIO Pin 260 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_261,            //@emem GPIO Pin 261 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_262,            //@emem GPIO Pin 262 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_263,            //@emem GPIO Pin 263 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_264,            //@emem GPIO Pin 264 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_265,            //@emem GPIO Pin 265 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_266,            //@emem GPIO Pin 266 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_267,            //@emem GPIO Pin 267 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_268,            //@emem GPIO Pin 268 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_269,            //@emem GPIO Pin 269 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_270,            //@emem GPIO Pin 270 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_271,            //@emem GPIO Pin 271 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_272,            //@emem GPIO Pin 272 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_273,            //@emem GPIO Pin 273 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_274,            //@emem GPIO Pin 274 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_275,            //@emem GPIO Pin 275 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_276,            //@emem GPIO Pin 276 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_277,            //@emem GPIO Pin 277 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_278,            //@emem GPIO Pin 278 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_279,            //@emem GPIO Pin 279 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_280,            //@emem GPIO Pin 280 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_281,            //@emem GPIO Pin 281 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_282,            //@emem GPIO Pin 282 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_283,            //@emem GPIO Pin 283 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_284,            //@emem GPIO Pin 284 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_285,            //@emem GPIO Pin 285 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_286,            //@emem GPIO Pin 286 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_287,            //@emem GPIO Pin 287 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_288,            //@emem GPIO Pin 288 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_289,            //@emem GPIO Pin 289 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_290,            //@emem GPIO Pin 290 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_291,            //@emem GPIO Pin 291 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_292,            //@emem GPIO Pin 292 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_293,            //@emem GPIO Pin 293 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_294,            //@emem GPIO Pin 294 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_295,            //@emem GPIO Pin 295 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_296,            //@emem GPIO Pin 296 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_297,            //@emem GPIO Pin 297 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_298,            //@emem GPIO Pin 298 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_299,            //@emem GPIO Pin 299 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_300,            //@emem GPIO Pin 300 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_301,            //@emem GPIO Pin 301 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_302,            //@emem GPIO Pin 302 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_303,            //@emem GPIO Pin 303 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_304,            //@emem GPIO Pin 304 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_305,            //@emem GPIO Pin 305 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_306,            //@emem GPIO Pin 306 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_307,            //@emem GPIO Pin 307 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_308,            //@emem GPIO Pin 308 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_309,            //@emem GPIO Pin 309 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_310,            //@emem GPIO Pin 310 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_311,            //@emem GPIO Pin 311 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_312,            //@emem GPIO Pin 312 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_313,            //@emem GPIO Pin 313 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_314,            //@emem GPIO Pin 314 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_315,            //@emem GPIO Pin 315 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_316,            //@emem GPIO Pin 316 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_317,            //@emem GPIO Pin 317 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_318,            //@emem GPIO Pin 318 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_319,            //@emem GPIO Pin 319 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_320,            //@emem GPIO Pin 320 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_321,            //@emem GPIO Pin 321 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_322,            //@emem GPIO Pin 322 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_323,            //@emem GPIO Pin 323 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_324,            //@emem GPIO Pin 324 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_325,            //@emem GPIO Pin 325 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_326,            //@emem GPIO Pin 326 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_327,            //@emem GPIO Pin 327 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_328,            //@emem GPIO Pin 328 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_329,            //@emem GPIO Pin 329 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_330,            //@emem GPIO Pin 330 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_331,            //@emem GPIO Pin 331 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_332,            //@emem GPIO Pin 332 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_333,            //@emem GPIO Pin 333 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_334,            //@emem GPIO Pin 334 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_335,            //@emem GPIO Pin 335 RESERVED
   SIU_GPIO_CHANNEL_336,                     //@emem GPIO Pin 336
   SIU_GPIO_CHANNEL_RESERVED_337,            //@emem GPIO Pin 337 RESERVED
   SIU_GPIO_CHANNEL_338,                     //@emem GPIO Pin 338
   SIU_GPIO_CHANNEL_339,                     //@emem GPIO Pin 339
   SIU_GPIO_CHANNEL_340,                     //@emem GPIO Pin 340
   SIU_GPIO_CHANNEL_341,                     //@emem GPIO Pin 341
   SIU_GPIO_CHANNEL_342,                     //@emem GPIO Pin 342
   SIU_GPIO_CHANNEL_343,                     //@emem GPIO Pin 343
   SIU_GPIO_CHANNEL_344,                     //@emem GPIO Pin 344
   SIU_GPIO_CHANNEL_345,                     //@emem GPIO Pin 345
   SIU_GPIO_CHANNEL_RESERVED_346,            //@emem GPIO Pin 346 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_347,            //@emem GPIO Pin 347 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_348,            //@emem GPIO Pin 348 RESERVED
   SIU_GPIO_CHANNEL_RESERVED_349,            //@emem GPIO Pin 349 RESERVED
   SIU_GPIO_CHANNEL_350,                     //@emem GPIO Pin 350
   SIU_GPIO_CHANNEL_351,                     //@emem GPIO Pin 351
   SIU_GPIO_CHANNEL_352,                     //@emem GPIO Pin 352
   SIU_GPIO_CHANNEL_353,                     //@emem GPIO Pin 353
   SIU_GPIO_CHANNEL_354,                     //@emem GPIO Pin 354
   SIU_GPIO_CHANNEL_355,                     //@emem GPIO Pin 355
   SIU_GPIO_CHANNEL_356,                     //@emem GPIO Pin 356
   SIU_GPIO_CHANNEL_357,                     //@emem GPIO Pin 357
   SIU_GPIO_CHANNEL_358,                     //@emem GPIO Pin 358
   SIU_GPIO_CHANNEL_359,                     //@emem GPIO Pin 359
   SIU_GPIO_CHANNEL_360,                     //@emem GPIO Pin 360
   SIU_GPIO_CHANNEL_361,                     //@emem GPIO Pin 361
   SIU_GPIO_CHANNEL_362,                     //@emem GPIO Pin 362
   SIU_GPIO_CHANNEL_363,                     //@emem GPIO Pin 363
   SIU_GPIO_CHANNEL_364,                     //@emem GPIO Pin 364
   SIU_GPIO_CHANNEL_365,                     //@emem GPIO Pin 365
   SIU_GPIO_CHANNEL_366,                     //@emem GPIO Pin 366
   SIU_GPIO_CHANNEL_367,                     //@emem GPIO Pin 367
   SIU_GPIO_CHANNEL_368,                     //@emem GPIO Pin 368
   SIU_GPIO_CHANNEL_369,                     //@emem GPIO Pin 369
   SIU_GPIO_CHANNEL_370,                     //@emem GPIO Pin 370
   SIU_GPIO_CHANNEL_371,                     //@emem GPIO Pin 371
   SIU_GPIO_CHANNEL_372,                     //@emem GPIO Pin 372
   SIU_GPIO_CHANNEL_373,                     //@emem GPIO Pin 373
   SIU_GPIO_CHANNEL_374,                     //@emem GPIO Pin 374
   SIU_GPIO_CHANNEL_375,                     //@emem GPIO Pin 375
   SIU_GPIO_CHANNEL_376,                     //@emem GPIO Pin 376
   SIU_GPIO_CHANNEL_377,                     //@emem GPIO Pin 377
   SIU_GPIO_CHANNEL_378,                     //@emem GPIO Pin 378
   SIU_GPIO_CHANNEL_379,                     //@emem GPIO Pin 379
   SIU_GPIO_CHANNEL_380,                     //@emem GPIO Pin 380
   SIU_GPIO_CHANNEL_381,                     //@emem GPIO Pin 381
   SIU_GPIO_CHANNEL_382,                     //@emem GPIO Pin 382
   SIU_GPIO_CHANNEL_383,                     //@emem GPIO Pin 383
   SIU_GPIO_CHANNEL_384,                     //@emem GPIO Pin 384
   SIU_GPIO_CHANNEL_385,                     //@emem GPIO Pin 385
   SIU_GPIO_CHANNEL_386,                     //@emem GPIO Pin 386
   SIU_GPIO_CHANNEL_387,                     //@emem GPIO Pin 387
   SIU_GPIO_CHANNEL_388,                     //@emem GPIO Pin 388
   SIU_GPIO_CHANNEL_389,                     //@emem GPIO Pin 389
   SIU_GPIO_CHANNEL_390,                     //@emem GPIO Pin 390
   SIU_GPIO_CHANNEL_391,                     //@emem GPIO Pin 391
   SIU_GPIO_CHANNEL_392,                     //@emem GPIO Pin 392
   SIU_GPIO_CHANNEL_393,                     //@emem GPIO Pin 393
   SIU_GPIO_CHANNEL_394,                     //@emem GPIO Pin 394
   SIU_GPIO_CHANNEL_395,                     //@emem GPIO Pin 395
   SIU_GPIO_CHANNEL_396,                     //@emem GPIO Pin 396
   SIU_GPIO_CHANNEL_397,                     //@emem GPIO Pin 397
   SIU_GPIO_CHANNEL_398,                     //@emem GPIO Pin 398
   SIU_GPIO_CHANNEL_399,                     //@emem GPIO Pin 399	
   SIU_GPIO_CHANNEL_400,                     //@emem GPIO Pin 400
   SIU_GPIO_CHANNEL_401,                     //@emem GPIO Pin 401	
   SIU_GPIO_CHANNEL_402,                     //@emem GPIO Pin 402	
   SIU_GPIO_CHANNEL_403,                     //@emem GPIO Pin 403	
   SIU_GPIO_CHANNEL_404,                     //@emem GPIO Pin 404	
   SIU_GPIO_CHANNEL_405,                     //@emem GPIO Pin 405	
   SIU_GPIO_CHANNEL_406,                     //@emem GPIO Pin 406	
   SIU_GPIO_CHANNEL_407,                     //@emem GPIO Pin 407	
   SIU_GPIO_CHANNEL_408,                     //@emem GPIO Pin 408	
   SIU_GPIO_CHANNEL_409,                     //@emem GPIO Pin 409	
   SIU_GPIO_CHANNEL_410,                     //@emem GPIO Pin 410	
   SIU_GPIO_CHANNEL_411,                     //@emem GPIO Pin 411	
   SIU_GPIO_CHANNEL_412,                     //@emem GPIO Pin 412	
   SIU_GPIO_CHANNEL_413,                     //@emem GPIO Pin 413	   
   SIU_GPIO_CHANNEL_MAX                      //@emem Max Channel value

} SIU_GPIO_Channel_T;

//=============================================================================
// @globalv SIU_T | SIU |
// The Register Memory Overlay of the System Integration Unit (SIU) Subsystem
// to provide software access and debug information.
//
// @end
//=============================================================================

// @enum SIU_GPIO_Configuration_Width_T | Defines the number of bits used by each member of the configuration field
typedef enum
{
   SIU_GPIO_CONFIGURATION_WIDTH_POLARITY               =  1, // @emem      0  Active State
   SIU_GPIO_CONFIGURATION_WIDTH_INITIAL_OUTPUT_STATE   =  1, // @emem      1  Initial Output State
   SIU_GPIO_CONFIGURATION_WIDTH_PIN_ASSIGNMENT         =  4, // @emem [ 5: 2] Pin Assignment
   SIU_GPIO_CONFIGURATION_WIDTH_DATA_DIRECTION         =  2, // @emem [ 7: 6] Data Direction
   SIU_GPIO_CONFIGURATION_WIDTH_DRIVE_STRENGTH         =  2, // @emem [ 9: 8] Drive Strength Control
   SIU_GPIO_CONFIGURATION_WIDTH_OPEN_DRAIN             =  1, // @emem     10  Open Drain Control
   SIU_GPIO_CONFIGURATION_WIDTH_INPUT_HYSTERESIS       =  1, // @emem     11  Edge Characteristic Control
   SIU_GPIO_CONFIGURATION_WIDTH_SLEW_RATE              =  2, // @emem [13:12] Device Slew Rate
   SIU_GPIO_CONFIGURATION_WIDTH_PULL_UP_DOWN_ENABLE    =  1, // @emem     14  Pull Up Down Enable
   SIU_GPIO_CONFIGURATION_WIDTH_PULL_UP                =  1, // @emem     15  Pull up
   SIU_GPIO_CONFIGURATION_WIDTH_CHANNEL                =  9, // @emem [24:16] Channel
   SIU_GPIO_CONFIGURATION_WIDTH_IGNORE_INIT            =  1  // @emem  25 SIU Ignore Init
   
}  SIU_GPIO_Configuration_Width_T;

// @enum SIU_GPIO_Configuration_Position_T | Defines the position of each member in the configuration field
typedef enum
{
   SIU_GPIO_CONFIGURATION_POSITION_POLARITY              =  0, // @emem      0  Active State
   SIU_GPIO_CONFIGURATION_POSITION_INITIAL_OUTPUT_STATE  =  1, // @emem      1  Initial Output State
   SIU_GPIO_CONFIGURATION_POSITION_PIN_ASSIGNMENT        =  2, // @emem [ 5: 2] Pin Assignment
   SIU_GPIO_CONFIGURATION_POSITION_DATA_DIRECTION        =  6, // @emem [ 7: 6] Data Direction
   SIU_GPIO_CONFIGURATION_POSITION_DRIVE_STRENGTH        =  8, // @emem [ 9: 8] Drive Strength Control
   SIU_GPIO_CONFIGURATION_POSITION_OPEN_DRAIN            = 10, // @emem     10  Open Drain Control
   SIU_GPIO_CONFIGURATION_POSITION_INPUT_HYSTERESIS      = 11, // @emem     11  Edge Characteristic Control
   SIU_GPIO_CONFIGURATION_POSITION_SLEW_RATE             = 12, // @emem [13:12] Device Slew Rate
   SIU_GPIO_CONFIGURATION_POSITION_PULL_UP_DOWN_ENABLE   = 14, // @emem     14  Pull Up Down Enable
   SIU_GPIO_CONFIGURATION_POSITION_PULL_UP               = 15, // @emem     15  Pull up
   SIU_GPIO_CONFIGURATION_POSITION_CHANNEL               = 16, // @emem [24:16] Channel
   SIU_GPIO_CONFIGURATION_POSITION_IGNORE_INIT           = 25  // @emem  25 SIU Ignore Init
   
}  SIU_GPIO_Configuration_Position_T;

// @enum SIU_Configuration_Width_T | Defines 
typedef enum
{
   SIU_CONFIGURATION_WIDTH_CHANNEL                       =  3   // @emem [  2:0 ] Channel
   
}  SIU_Configuration_Width_T;

// @enum SIU_Configuration_Position_T | Defines
typedef enum
{
   SIU_CONFIGURATION_POSITION_CHANNEL                     = 0    // @emem [  2:0 ] Channel
   
}  SIU_Configuration_Position_T;

// @enum SIU_IRQ_Configuration_Width_T | Defines the number of
//       bits used by each member of the configuration field
typedef enum
{
   SIU_IRQ_CONFIGURATION_WIDTH_INPUT              =  5, // @emem [30:26] SIU IRQ  Input 
   SIU_IRQ_CONFIGURATION_WIDTH_TYPE               =  1, // @emem  5 SIU IRQ type
   SIU_IRQ_CONFIGURATION_WIDTH_EDGE_TYPE          =  2  // @emem  31  SIU IRQ edge type

}  SIU_IRQ_Configuration_Width_T;

// @enum SIU_IRQ_Configuration_Position_T | Defines the position of
//       each member in the configuration field
typedef enum
{
   SIU_IRQ_CONFIGURATION_POSITION_INPUT             = 26,  // @emem [30:26] SIU IRQ  Input 
   SIU_IRQ_CONFIGURATION_POSITION_TYPE              = 5,   // @emem  5 SIU IRQ type
   SIU_IRQ_CONFIGURATION_POSITION_EDGE_TYPE         = 31   // @emem  31  SIU IRQ edge type  comment: NEED TO BE MODIFIED

}  SIU_IRQ_Configuration_Position_T;

//=============================================================================
//  @enum SIU_DSPI_Configuration_Width_T | Defines the number of
//       bits used by each member of the configuration field
typedef enum
{
   SIU_DSPI_CONFIGURATION_WIDTH_SINSEL              = 2, // @emem [1:0] SIU DSPI Data Input select
   SIU_DSPI_CONFIGURATION_WIDTH_SSSSEL              = 2, // @emem [3:2] SIU DSPI Slave select input
   SIU_DSPI_CONFIGURATION_WIDTH_SCKSEL              = 2, // @emem [5 4] SIU DSPI Clock input select
   SIU_DSPI_CONFIGURATION_WIDTH_TRIGSEL             = 2  // @emem [7:6] SIU DSPI Trigger input select

}  SIU_DSPI_Configuration_Width_T;

// @enum SIU_DSPI_Configuration_Position_T | Defines the position of
//       each member in the configuration field
typedef enum
{
   SIU_DSPI_CONFIGURATION_POSITION_SINSEL           = 0, // @emem [1:0] SIU DSPI Data Input select 
   SIU_DSPI_CONFIGURATION_POSITION_SSSSEL           = 2, // @emem [3:2] SIU DSPI Slave select input
   SIU_DSPI_CONFIGURATION_POSITION_SCKSEL           = 4, // @emem [5 4] SIU DSPI Clock input select
   SIU_DSPI_CONFIGURATION_POSITION_TRIGSEL          = 6  // @emem [7:6] SIU DSPI Trigger input select

}  SIU_DSPI_Configuration_Position_T;

//=============================================================================
//  @enum SIU_IMUX_Select_Configuration_Width_T | Defines the multiplexing
// of eTPU channels

typedef enum
{
   SIU_IMUX_CONFIGURATION_WIDTH_ESEL5              = 1,  // @emem 0 SIU IMUX select 5
   SIU_IMUX_CONFIGURATION_WIDTH_ESEL4              = 1,  // @emem 1 SIU IMUX select 4
   SIU_IMUX_CONFIGURATION_WIDTH_ESEL3              = 1,  // @emem 2 SIU IMUX select 3
   SIU_IMUX_CONFIGURATION_WIDTH_ESEL2              = 1,  // @emem 3 SIU IMUX select 2
   SIU_IMUX_CONFIGURATION_WIDTH_ESEL1              = 1,  // @emem 4 SIU IMUX select 1
   SIU_IMUX_CONFIGURATION_WIDTH_ESEL0              = 1   // @emem 5 SIU IMUX select 0

}  SIU_IMUX_Select_Configuration_Width_T;

// @enum SIU_IMUX_Configuration_Position_T | Defines the multiplexing
// of eTPU channels

typedef enum
{
   SIU_IMUX_CONFIGURATION_POSITION_ESEL5          = 0, // @emem 0 SIU IMUX select 5
   SIU_IMUX_CONFIGURATION_POSITION_ESEL4          = 1, // @emem 1 SIU IMUX select 4
   SIU_IMUX_CONFIGURATION_POSITION_ESEL3          = 2, // @emem 2 SIU IMUX select 3
   SIU_IMUX_CONFIGURATION_POSITION_ESEL2          = 3, // @emem 3 SIU IMUX select 2
   SIU_IMUX_CONFIGURATION_POSITION_ESEL1          = 4, // @emem 4 SIU IMUX select 1
   SIU_IMUX_CONFIGURATION_POSITION_ESEL0          = 5  // @emem 5 SIU IMUX select 0


}  SIU_IMUX_Configuration_Position_T;


//=============================================================================

// @enum SIU_Channel_T | Defines 
typedef enum
{
   SIU_TIMER_WATCH_DOG,               // @emem Number 0
   SIU_TIMER_WATCH_DOG_BUS_MONITOR,   // @emem Number 1
   SIU_TIMER_PERIODIC_INTERRUPT,      // @emem Number 2
   SIU_TIMER_TBC_TBL,                 // @emem Number 3
   SIU_TIMER_TBC_TBU,                 // @emem Number 4
   SIU_TIMER_DECREMENTER,             // @emem Number 7
   SIU_TIMER_REAL_TIME_CLOCK,         // @emem Number 8
   SIU_TIMER_MAX                      // @emem Number 9

}  SIU_Timer_T;

// @enum SIU_GPIO_Data_Direction_T | Defines the direction type for configuring the port
typedef enum
{
   SIU_GPIO_BUFFER_IN_DISABLED,  // @emem Buffer in Disabled
   SIU_GPIO_BUFFER_IN_ENABLED      // @emem Buffer in Enabled

} SIU_GPIO_Data_Direction_IN_T;


// @enum SIU_GPIO_Data_Direction_T | Defines the direction type for configuring the port
typedef enum
{
   SIU_GPIO_BUFFER_OUT_DISABLED,  // @emem Buffer in Disabled
   SIU_GPIO_BUFFER_OUT_ENABLED      // @emem Buffer in Enabled

} SIU_GPIO_Data_Direction_OUT_T;

// @enum SIU_GPIO_Pull_Up_T | Defines whether the channel pulled up or down
typedef enum
{
   SIU_GPIO_PULL_DOWN,   // @emem
   SIU_GPIO_PULL_UP      // @emem

} SIU_GPIO_Pull_Up_T;

// @enum SIU_GPIO_Pull_Up_Down_Enable_T | Defines the Pull Up/Down Enable State for the Channel
typedef enum
{
   SIU_GPIO_PULL_UP_Down_DISABLED,    // @emem 
   SIU_GPIO_PULL_UP_Down_ENABLED      // @emem

} SIU_GPIO_Pull_Up_Down_Enable_T;

// MOVE TO DD
// @enum SIU_GPIO_Pin_Assignment_T | Defines whether the alternate use of the channel is enabled.
typedef enum
{
   SIU_GPIO_PIN_ASSIGNMENT_GPIO,              // emem GPIO
   SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0,         // emem Primary Function
   SIU_GPIO_PIN_ASSIGNMENT_ALTERNATE_1,       // emem Alternate Function 1 
   SIU_GPIO_PIN_ASSIGNMENT_RESERVED_0,         // enum Reserved
   SIU_GPIO_PIN_ASSIGNMENT_ALTERNATE_2,       // emem Alternate Function 2
   SIU_PIN_ASSIGNMENT_RESERVED_1,             // @emem Reserved
   SIU_PIN_ASSIGNMENT_RESERVED_2,             // @emem Reserved
   SIU_PIN_ASSIGNMENT_RESERVED_3,             // @emem Reserved
   SIU_PIN_ASSIGNMENT_ALTERNATE_3             // @emem Alternate Function 3

} SIU_GPIO_Pin_Assignment_T;

// @enum SIU_GPIO_Drive_Strength_T | Defines 
typedef enum
{
   SIU_GPIO_DRIVE_STRENGTH_10pF,   // @emem
   SIU_GPIO_DRIVE_STRENGTH_20pF,   // @emem
   SIU_GPIO_DRIVE_STRENGTH_30pF,   // @emem
   SIU_GPIO_DRIVE_STRENGTH_50pF    // @emem

} SIU_GPIO_Drive_Strength_T;

// @enum SIU_GPIO_Initial_Output_State_T | Defines the initial output state for the channel
typedef enum
{
   SIU_GPIO_LOW,   // @emem
   SIU_GPIO_HIGH   // @emem

} SIU_GPIO_Initial_Output_State_T;

// @enum SIU_GPIO_Input_Hysteresis_T | Defines the input hysteresis for the Channel
typedef enum
{
   SIU_GPIO_INPUT_HYSTERESIS_DISABLED,  // @emem
   SIU_GPIO_INPUT_HYSTERESIS_ENABLED    // @emem

} SIU_GPIO_Input_Hysteresis_T;

// @enum SIU_GPIO_Open_Drain_T | Defines the open drain mode for the channel.
typedef enum
{
   SIU_GPIO_OPEN_DRAIN_DISABLED, // @emem
   SIU_GPIO_OPEN_DRAIN_ENABLED   // @emem

} SIU_GPIO_Open_Drain_T;

// @enum SIU_GPIO_Slew_Rate_Control_T | Defines the Characteristic of the input for the channel
typedef enum
{
   SIU_GPIO_SLEW_RATE_MINIMUM,   // @emem
   SIU_GPIO_SLEW_RATE_MEDIMUM,   // @emem
   SIU_GPIO_SLEW_RATE_RESERVED,  // @emem
   SIU_GPIO_SLEW_RATE_MAXIMUM    // @emem

} SIU_GPIO_Slew_Rate_T;

typedef enum
{
   SIU_IRQ_0,
   SIU_IRQ_1_RESERVED,
   SIU_IRQ_2_RESERVED,
   SIU_IRQ_3,
   SIU_IRQ_4,
   SIU_IRQ_5_RESERVED,
   SIU_IRQ_6_RESERVED,
   SIU_IRQ_7_RESERVED,
   SIU_IRQ_8,
   SIU_IRQ_9,
   SIU_IRQ_10,
   SIU_IRQ_11,
   SIU_IRQ_12,
   SIU_IRQ_13,
   SIU_IRQ_14,
   SIU_IRQ_15,
   SIU_IRQ_MAX,
   SIU_IRQ_SWT = 23,
   SIU_IRQ_NMI = 31


} SIU_IRQ_T;


//=============================================================================
//  Enumeration: eQADC trigger input select 5
//
//   TSEL5[1:0]  Meaning of Value
//  ===========  ============================================================
//           00  eTSEL5
//           01  ETPUA26 channel
//           10  EMIOS12 channel
//           11  ETRIG1pin
//=============================================================================
typedef enum SIU_ETISR_TSEL5_Tag
{
   SIU_ETISR_TSEL5_eTSEL5,
   SIU_ETISR_TSEL5_ETPUA26,
   SIU_ETISR_TSEL5_EMIOS12,
   SIU_ETISR_TSEL5_ETRIG1

}  SIU_ETISR_TSEL5_T;

//=============================================================================
//  Enumeration: eQADC trigger input select 4
//
//   TSEL4[1:0]  Meaning of Value
//  ===========  ============================================================
//           00  eTSEL4
//           01  ETPUA27 channel
//           10  EMIOS13 channel
//           11  ETRIG0pin
//=============================================================================
typedef enum SIU_ETISR_TSEL4_Tag
{
   SIU_ETISR_TSEL4_eTSEL4,
   SIU_ETISR_TSEL4_ETPUA27,
   SIU_ETISR_TSEL4_EMIOS13,
   SIU_ETISR_TSEL4_ETRIG0

}  SIU_ETISR_TSEL4_T;

//=============================================================================
//  Enumeration: eQADC trigger input select 3
//
//   TSEL3[1:0]  Meaning of Value
//  ===========  ============================================================
//           00  eTSEL3
//           01  ETPUA28 channel
//           10  EMIOS14 channel
//           11  ETRIG1pin
//=============================================================================
typedef enum SIU_ETISR_TSEL3_Tag
{
   SIU_ETISR_TSEL3_eTSEL3,
   SIU_ETISR_TSEL3_ETPUA28,
   SIU_ETISR_TSEL3_EMIOS14,
   SIU_ETISR_TSEL3_ETRIG1

}  SIU_ETISR_TSEL3_T;

//=============================================================================
//  Enumeration: eQADC trigger input select 2
//
//   TSEL2[1:0]  Meaning of Value
//  ===========  ============================================================
//           00  eTSEL2
//           01  ETPUA29 channel
//           10  EMIOS15 channel
//           11  ETRIG0pin
//=============================================================================
typedef enum SIU_ETISR_TSEL2_Tag
{
   SIU_ETISR_TSEL2_eTSEL2,
   SIU_ETISR_TSEL2_ETPUA29,
   SIU_ETISR_TSEL2_EMIOS15,
   SIU_ETISR_TSEL2_ETRIG0

}  SIU_ETISR_TSEL2_T;

//=============================================================================
//  Enumeration: eQADC trigger input select 1
//
//   TSEL1[1:0]  Meaning of Value
//  ===========  ============================================================
//           00  eTSEL1
//           01  ETPUA31 channel
//           10  EMIOS11 channel
//           11  ETRIG1pin
//=============================================================================
typedef enum SIU_ETISR_TSEL1_Tag
{
   SIU_ETISR_TSEL1_eTSEL1,
   SIU_ETISR_TSEL1_ETPUA31,
   SIU_ETISR_TSEL1_EMIOS11,
   SIU_ETISR_TSEL1_ETRIG1

}  SIU_ETISR_TSEL1_T;

//=============================================================================
//  Enumeration: eQADC trigger input select 0
//
//   TSEL0[1:0]  Meaning of Value
//  ===========  ============================================================
//           00  eTSEL0
//           01  ETPUA30 channel
//           10  EMIOS10 channel
//           11  ETRIG0 pin
//=============================================================================
typedef enum SIU_ETISR_TSEL0_Tag
{
   SIU_ETISR_TSEL0_eTSEL0,
   SIU_ETISR_TSEL0_ETPUA30,
   SIU_ETISR_TSEL0_EMIOS10,
   SIU_ETISR_TSEL0_ETRIG0

}  SIU_ETISR_TSEL0_T;

//=============================================================================
//  Enumeration: External bus division factor
//
//  EBDF[1:0]  Meaning of Value
//  =========  ==============================================================
//          0  Divide by 1
//          1  Divide by 2
//          2  Reserved
//          3  Divide by 4
//=============================================================================
typedef enum SIU_ECCR_EBDF_Tag
{
   SIU_ECCR_EBDF_DIV_BY_1,
   SIU_ECCR_EBDF_DIV_BY_2,
   SIU_ECCR_EBDF_RESERVED,
   SIU_ECCR_EBDF_DIV_BY_4

} SIU_ECCR_EBDF_T;

//=============================================================================
//  Enumeration: Engineering clock (ENGCLK) source select
//
//  ECSS[1]  Meaning of Value
//  =========  ==============================================================
//          0  The system clock is the source of the ENGCLK.
//          1  The external clock is the source of the ENGCLK
//=============================================================================
typedef enum SIU_ECCR_ECSS_Tag
{
   SIU_ECCR_ECSS_SYSTEM_CLK,
   SIU_ECCR_ECSS_EXTERNAL_CLK

} SIU_ECCR_ECSS_T;

//=============================================================================
//  Enumeration: System Clock Divide
//
//  SYSCLKDIV[1:0]  Meaning of Value
//  =========  ==============================================================
//          00  System Clock Divide by 2
//          01  System Clock Divide by 4
//          10  System Clock Divide by 8
//          11  System Clock Divide by 16
//=============================================================================
typedef enum SIU_SYSDIV_SYSCLKDIV_Tag
{
   SIU_SYSDIV_SYS_CLOCK_DIV_BY_2,
   SIU_SYSDIV_SYS_CLOCK_DIV_BY_4,
   SIU_SYSDIV_SYS_CLOCK_DIV_BY_8,
   SIU_SYSDIV_SYS_CLOCK_DIV_BY_16

} SIU_SYSDIV_SYSCLKDIV_T;

//=============================================================================
//  Enumeration: FlexCAN 2:1 mode
//
//  CAN2:1[1]  Meaning of Value
//  =========  ==============================================================
//          0  1:1 mode for FlexCAN.(FlexCAN runs at the system frequency)
//          1  2:1 mode for FlexCAN(FlexCAN runs at half the system frequency)
//=============================================================================
typedef enum SIU_SYSDIV_FLEXCAN_CLOCK_Tag
{
   SIU_SYSDIV_FLEXCAN_EQU_SYSTEM_FREQ,
   SIU_SYSDIV_FLEXCAN_HALF_SYSTEM_FREQ

} SIU_SYSDIV_FLEXCAN_CLOCK_T;

//=============================================================================
//  Enumeration: BYPASS
//
//  BYPASS[1]  Bypass bit.Meaning of Value
//  =========  ==============================================================
//          0  system clock divider is not bypassed
//          1  1 = system clock divider is bypassed
//=============================================================================
typedef enum SIU_SYSDIV_BYPASS_Tag
{
   SIU_SYSDIV_SYS_CLOCK_DIVIDER_NOT_BYPASS,
   SIU_SYSDIV_SYS_CLOCK_DIVIDER_BYPASS

} SIU_SYSDIV_BYPASS_T;

//=============================================================================
//  Enumeration: External IRQ input select
//
//   ESEL[1:0]   Meaning of Value
//  ===========  ============================================================
//           00  IRQ pin
//           01  DSPI_B Peripheral Chip select
//           10  DSPI_C Peripheral Chip select
//           11  DSPI_D Peripheral Chip select - Reserved
//=============================================================================
typedef enum SIU_EIISR_ESEL_Tag
{
   SIU_EIISR_ESEL_IRQ_PIN,
   SIU_EIISR_ESEL_DSPI_B,
   SIU_EIISR_ESEL_DSPI_C,
   SIU_EIISR_ESEL_DSPI_D_RESERVED

}  SIU_EIISR_ESEL_T;
//=============================================================================
//  Enumeration: DSPI_X data input select.
//
//  SINSELX[1:0] Meaning of Value
//  ===========  ============================================================
//           00  SINX pin
//           01  Reserved
//           10  SOUTY
//           11  Reserved

// X=C, Y=B
// X=B, Y=C

//=============================================================================
typedef enum SIU_DISR_SINSELX_Tag
{
   SIU_DISR_SINSELX_SINX,
   SIU_DISR_SINSELX_RESERVED_1,
   SIU_DISR_SINSELX_SOUTY,
   SIU_DISR_SINSELX_RESERVED_2

}  SIU_DISR_SINSELX_T;

//=============================================================================
//  Enumeration: DSPI_X slave select input select.
//
//   SSSELX[1:0] Meaning of Value
//  ===========  ============================================================
//           00  PCSX0 pin
//           01  Reserved
//           10  PCSY0
//           11  Reserved
//=============================================================================

typedef enum SIU_DISR_SSSELX_Tag
{
   SIU_DISR_SSSELX_PCSX0,
   SIU_DISR_SSSELX_RESERVED_1,
   SIU_DISR_SSSELX_PCSY0,
   SIU_DISR_SSSELX_RESERVED_2

}  SIU_DISR_SSSELX_T;

//=============================================================================
//  Enumeration: DSPI_X clock input select.
//
//  SCKSELX[1:0] Meaning of Value
//  ===========  ============================================================
//           00  SCKX pin
//           01  Reserved
//           10  SCKY
//           11  Reserved
//=============================================================================
typedef enum SIU_DISR_SCKSELX_Tag
{
   SIU_DISR_SCKSELX_SCKX,
   SIU_DISR_SCKSELX_RESERVED_1,
   SIU_DISR_SCKSELX_SCKY,
   SIU_DISR_SCKSELX_RESERVED_2

}  SIU_DISR_SCKSELX_T;

//=============================================================================
//  Enumeration: DSPI_X trigger input select.
//
// TRIGSELX[1:0] Meaning of Value
//  ===========  ============================================================
//           00  Reserved
//           01  Reserved
//           10  PCSY4
//           11  Reserved
//=============================================================================
typedef enum SIU_DISR_TRIGSELX_Tag
{
   SIU_DISR_TRIGSELX_RESERVED_1,
   SIU_DISR_TRIGSELX_RESERVED_2,
   SIU_DISR_TRIGSELX_PCSY4,
   SIU_DISR_TRIGSELX_RESERVED_3

}  SIU_DISR_TRIGSELX_T;

//=============================================================================
//  Enumeration: eQADC_A Ccmmand FIFO 0 Trigger Source
//=============================================================================
typedef enum SIU_ISEL3_eTSEL0_Tag
{
   SIU_ISEL3_eTSEL0_GPIO206_eTRIG0,
   SIU_ISEL3_eTSEL0_RTI_TRIGGER,
   SIU_ISEL3_eTSEL0_PIT0_TRIGGER,
   SIU_ISEL3_eTSEL0_PIT1_TRIGGER,
   SIU_ISEL3_eTSEL0_PIT2_TRIGGER,
   SIU_ISEL3_eTSEL0_PIT3_TRIGGER,
   SIU_ISEL3_eTSEL0_RESERVED0,
   SIU_ISEL3_eTSEL0_eTRIG3,
   SIU_ISEL3_eTSEL0_eTPU30_PIT0,
   SIU_ISEL3_eTSEL0_eTPUA30_PIT1,
   SIU_ISEL3_eTSEL0_RESERVED1,
   SIU_ISEL3_eTSEL0_RESERVED2,
   SIU_ISEL3_eTSEL0_eTPUA28,
   SIU_ISEL3_eTSEL0_eTPUB29,
   SIU_ISEL3_eTSEL0_eTPUB30,
   SIU_ISEL3_eTSEL0_eTPUB31,
   SIU_ISEL3_eTSEL0_RESERVED3,
   SIU_ISEL3_eTSEL0_RESERVED4,
   SIU_ISEL3_eTSEL0_RESERVED5,
   SIU_ISEL3_eTSEL0_RESERVED6,
   SIU_ISEL3_eTSEL0_eMIOS10_PIT2,
   SIU_ISEL3_eTSEL0_eMIOS10_PIT3,
   SIU_ISEL3_eTSEL0_RESERVED7,
   SIU_ISEL3_eTSEL0_RESERVED8,
   SIU_ISEL3_eTSEL0_RESERVED9,
   SIU_ISEL3_eTSEL0_RESERVED10,
   SIU_ISEL3_eTSEL0_RESERVED11,
   SIU_ISEL3_eTSEL0_RESERVED12,
   SIU_ISEL3_eTSEL0_RESERVED13,
   SIU_ISEL3_eTSEL0_RESERVED14,
   SIU_ISEL3_eTSEL0_RESERVED15,
   SIU_ISEL3_eTSEL0_eMIOS23

}  SIU_ISEL3_eTSEL0_T;

//=============================================================================
//  Enumeration: eQADC_A Ccmmand FIFO 1 Trigger Source
//=============================================================================
typedef enum SIU_ISEL3_eTSEL1_Tag
{
   SIU_ISEL3_eTSEL1_GPIO207_eTRIG1,
   SIU_ISEL3_eTSEL1_RTI_TRIGGER,
   SIU_ISEL3_eTSEL1_PIT0_TRIGGER,
   SIU_ISEL3_eTSEL1_PIT1_TRIGGER,
   SIU_ISEL3_eTSEL1_PIT2_TRIGGER,
   SIU_ISEL3_eTSEL1_PIT3_TRIGGER,
   SIU_ISEL3_eTSEL1_RESERVED0,
   SIU_ISEL3_eTSEL1_PLLREF_eTRIG2,
   SIU_ISEL3_eTSEL1_eTPU31_PIT0,
   SIU_ISEL3_eTSEL1_eTPU31_PIT1,
   SIU_ISEL3_eTSEL1_RESERVED1,
   SIU_ISEL3_eTSEL1_RESERVED2,
   SIU_ISEL3_eTSEL1_eTPUB28,
   SIU_ISEL3_eTSEL1_eTPUB29,
   SIU_ISEL3_eTSEL1_eTPUB30,
   SIU_ISEL3_eTSEL1_eTPUB31,
   SIU_ISEL3_eTSEL1_RESERVED3,
   SIU_ISEL3_eTSEL1_RESERVED4,
   SIU_ISEL3_eTSEL1_RESERVED5,
   SIU_ISEL3_eTSEL1_RESERVED6,
   SIU_ISEL3_eTSEL1_eMIOS11_PIT2,
   SIU_ISEL3_eTSEL1_eMIOS11_PIT3,
   SIU_ISEL3_eTSEL1_RESERVED7,
   SIU_ISEL3_eTSEL1_RESERVED8,
   SIU_ISEL3_eTSEL1_RESERVED9,
   SIU_ISEL3_eTSEL1_RESERVED10,
   SIU_ISEL3_eTSEL1_RESERVED11,
   SIU_ISEL3_eTSEL1_RESERVED12,
   SIU_ISEL3_eTSEL1_RESERVED13,
   SIU_ISEL3_eTSEL1_RESERVED14,
   SIU_ISEL3_eTSEL1_RESERVED15,
   SIU_ISEL3_eTSEL1_eMIOS23

}  SIU_ISEL3_eTSEL1_T;

//=============================================================================
//  Enumeration: eQADC_A Ccmmand FIFO 2 Trigger Source
//=============================================================================
typedef enum SIU_ISEL3_eTSEL2_Tag
{
   SIU_ISEL3_eTSEL2_GPIO206_eTRIG0,
   SIU_ISEL3_eTSEL2_RTI_TRIGGER,
   SIU_ISEL3_eTSEL2_PIT0_TRIGGER,
   SIU_ISEL3_eTSEL2_PIT1_TRIGGER,
   SIU_ISEL3_eTSEL2_PIT2_TRIGGER,
   SIU_ISEL3_eTSEL2_PIT3_TRIGGER,
   SIU_ISEL3_eTSEL2_RESERVED0,
   SIU_ISEL3_eTSEL2_eTRIG3,
   SIU_ISEL3_eTSEL2_eTPU30_PIT0,
   SIU_ISEL3_eTSEL2_eTPU30_PIT1,
   SIU_ISEL3_eTSEL2_RESERVED1,
   SIU_ISEL3_eTSEL2_RESERVED2,
   SIU_ISEL3_eTSEL2_eTPUB28,
   SIU_ISEL3_eTSEL2_eTPUB29,
   SIU_ISEL3_eTSEL2_eTPUB30,
   SIU_ISEL3_eTSEL2_eTPUB31,
   SIU_ISEL3_eTSEL2_RESERVED3,
   SIU_ISEL3_eTSEL2_RESERVED4,
   SIU_ISEL3_eTSEL2_RESERVED5,
   SIU_ISEL3_eTSEL2_RESERVED6,
   SIU_ISEL3_eTSEL2_eMIOS10_PIT2,
   SIU_ISEL3_eTSEL2_eMIOS10_PIT3,
   SIU_ISEL3_eTSEL2_RESERVED7,
   SIU_ISEL3_eTSEL2_RESERVED8,
   SIU_ISEL3_eTSEL2_RESERVED9,
   SIU_ISEL3_eTSEL2_RESERVED10,
   SIU_ISEL3_eTSEL2_RESERVED11,
   SIU_ISEL3_eTSEL2_RESERVED12,
   SIU_ISEL3_eTSEL2_RESERVED13,
   SIU_ISEL3_eTSEL2_RESERVED14,
   SIU_ISEL3_eTSEL2_RESERVED15,
   SIU_ISEL3_eTSEL2_eMIOS23

}  SIU_ISEL3_eTSEL2_T;

//=============================================================================
//  Enumeration: eQADC_A Ccmmand FIFO 3 Trigger Source
//=============================================================================
typedef enum SIU_ISEL3_eTSEL3_Tag
{
   SIU_ISEL3_eTSEL3_GPIO207_eTRIG1,
   SIU_ISEL3_eTSEL3_RTI_TRIGGER,
   SIU_ISEL3_eTSEL3_PIT0_TRIGGER,
   SIU_ISEL3_eTSEL3_PIT1_TRIGGER,
   SIU_ISEL3_eTSEL3_PIT2_TRIGGER,
   SIU_ISEL3_eTSEL3_PIT3_TRIGGER,
   SIU_ISEL3_eTSEL3_RESERVED0,
   SIU_ISEL3_eTSEL3_PLLREF_eTRIG2,
   SIU_ISEL3_eTSEL3_eTPU30_PIT0,
   SIU_ISEL3_eTSEL3_eTPU30_PIT1,
   SIU_ISEL3_eTSEL3_RESERVED1,
   SIU_ISEL3_eTSEL3_RESERVED2,
   SIU_ISEL3_eTSEL3_eTPUB28,
   SIU_ISEL3_eTSEL3_eTPUB29,
   SIU_ISEL3_eTSEL3_eTPUB30,
   SIU_ISEL3_eTSEL3_eTPUB31,
   SIU_ISEL3_eTSEL3_RESERVED3,
   SIU_ISEL3_eTSEL3_RESERVED4,
   SIU_ISEL3_eTSEL3_RESERVED5,
   SIU_ISEL3_eTSEL3_RESERVED6,
   SIU_ISEL3_eTSEL3_eMIOS10_PIT2,
   SIU_ISEL3_eTSEL3_eMIOS10_PIT3,
   SIU_ISEL3_eTSEL3_RESERVED7,
   SIU_ISEL3_eTSEL3_RESERVED8,
   SIU_ISEL3_eTSEL3_RESERVED9,
   SIU_ISEL3_eTSEL3_RESERVED10,
   SIU_ISEL3_eTSEL3_RESERVED11,
   SIU_ISEL3_eTSEL3_RESERVED12,
   SIU_ISEL3_eTSEL3_RESERVED13,
   SIU_ISEL3_eTSEL3_RESERVED14,
   SIU_ISEL3_eTSEL3_RESERVED15,
   SIU_ISEL3_eTSEL3_eMIOS23

}  SIU_ISEL3_eTSEL3_T;

//=============================================================================
//  Enumeration: eQADC_A Ccmmand FIFO 4 Trigger Source
//=============================================================================
typedef enum SIU_ISEL3_eTSEL4_Tag
{
   SIU_ISEL3_eTSEL4_GPIO206_eTRIG0,
   SIU_ISEL3_eTSEL4_RTI_TRIGGER,
   SIU_ISEL3_eTSEL4_PIT0_TRIGGER,
   SIU_ISEL3_eTSEL4_PIT1_TRIGGER,
   SIU_ISEL3_eTSEL4_PIT2_TRIGGER,
   SIU_ISEL3_eTSEL4_PIT3_TRIGGER,
   SIU_ISEL3_eTSEL4_RESERVED0,
   SIU_ISEL3_eTSEL4_eTRIG3,
   SIU_ISEL3_eTSEL4_eTPU30_PIT0,
   SIU_ISEL3_eTSEL4_eTPU30_PIT1,
   SIU_ISEL3_eTSEL4_RESERVED1,
   SIU_ISEL3_eTSEL4_RESERVED2,
   SIU_ISEL3_eTSEL4_eTPUB28,
   SIU_ISEL3_eTSEL4_eTPUB29,
   SIU_ISEL3_eTSEL4_eTPUB30,
   SIU_ISEL3_eTSEL4_eTPUB31,
   SIU_ISEL3_eTSEL4_RESERVED3,
   SIU_ISEL3_eTSEL4_RESERVED4,
   SIU_ISEL3_eTSEL4_RESERVED5,
   SIU_ISEL3_eTSEL4_RESERVED6,
   SIU_ISEL3_eTSEL4_eMIOS10_PIT2,
   SIU_ISEL3_eTSEL4_eMIOS10_PIT3,
   SIU_ISEL3_eTSEL4_RESERVED7,
   SIU_ISEL3_eTSEL4_RESERVED8,
   SIU_ISEL3_eTSEL4_RESERVED9,
   SIU_ISEL3_eTSEL4_RESERVED10,
   SIU_ISEL3_eTSEL4_RESERVED11,
   SIU_ISEL3_eTSEL4_RESERVED12,
   SIU_ISEL3_eTSEL4_RESERVED13,
   SIU_ISEL3_eTSEL4_RESERVED14,
   SIU_ISEL3_eTSEL4_RESERVED15,
   SIU_ISEL3_eTSEL4_eMIOS23

}  SIU_ISEL3_eTSEL4_T;

//=============================================================================
//  Enumeration: eQADC_A Ccmmand FIFO 5 Trigger Source
//=============================================================================
typedef enum SIU_ISEL3_eTSEL5_Tag
{
   SIU_ISEL3_eTSEL5_GPIO207_eTRIG1,
   SIU_ISEL3_eTSEL5_RTI_TRIGGER,
   SIU_ISEL3_eTSEL5_PIT0_TRIGGER,
   SIU_ISEL3_eTSEL5_PIT1_TRIGGER,
   SIU_ISEL3_eTSEL5_PIT2_TRIGGER,
   SIU_ISEL3_eTSEL5_PIT3_TRIGGER,
   SIU_ISEL3_eTSEL5_RESERVED0,
   SIU_ISEL3_eTSEL5_PLLREF_eTRIG2,
   SIU_ISEL3_eTSEL5_eTPU30_PIT0,
   SIU_ISEL3_eTSEL5_eTPU30_PIT1,
   SIU_ISEL3_eTSEL5_RESERVED1,
   SIU_ISEL3_eTSEL5_RESERVED2,
   SIU_ISEL3_eTSEL5_eTPUB28,
   SIU_ISEL3_eTSEL5_eTPUB29,
   SIU_ISEL3_eTSEL5_eTPUB30,
   SIU_ISEL3_eTSEL5_eTPUB31,
   SIU_ISEL3_eTSEL5_RESERVED3,
   SIU_ISEL3_eTSEL5_RESERVED4,
   SIU_ISEL3_eTSEL5_RESERVED5,
   SIU_ISEL3_eTSEL5_RESERVED6,
   SIU_ISEL3_eTSEL5_eMIOS10_PIT2,
   SIU_ISEL3_eTSEL5_eMIOS10_PIT3,
   SIU_ISEL3_eTSEL5_RESERVED7,
   SIU_ISEL3_eTSEL5_RESERVED8,
   SIU_ISEL3_eTSEL5_RESERVED9,
   SIU_ISEL3_eTSEL5_RESERVED10,
   SIU_ISEL3_eTSEL5_RESERVED11,
   SIU_ISEL3_eTSEL5_RESERVED12,
   SIU_ISEL3_eTSEL5_RESERVED13,
   SIU_ISEL3_eTSEL5_RESERVED14,
   SIU_ISEL3_eTSEL5_RESERVED15,
   SIU_ISEL3_eTSEL5_eMIOS23

}  SIU_ISEL3_eTSEL5_T;

//=============================================================================
//  Enumeration: ISEL8 IMUX select register 8
//
// TRIGSELD[1:0] Meaning of Value
//  ===========  ============================================================
//           0 DSPI_B
//           1 eTPU channel
//=============================================================================
typedef enum SIU_ISEL8_eTPU_Tag
{
   SIU_DSPIB_DESERIALIZED_OUTPUT,
   SIU_ETPU_CHANNEL

} SIU_ISEL8_eTPU_T;

//=============================================================================
//  Enumeration: Mux Select Register 9 (SIU_ISEL9)
//=============================================================================
typedef enum SIU_ISEL9_eTSEL0A_Tag
{
   SIU_ISEL9_eTSEL0A_RESERVED0,
   SIU_ISEL9_eTSEL0A_RTI_TRIGGER,
   SIU_ISEL9_eTSEL0A_PIT0_TRIGGER,
   SIU_ISEL9_eTSEL0A_PIT1_TRIGGER,
   SIU_ISEL9_eTSEL0A_PIT2_TRIGGER,
   SIU_ISEL9_eTSEL0A_PIT3_TRIGGER,
   SIU_ISEL9_eTSEL0A_RESERVED1,
   SIU_ISEL9_eTSEL0A_RESERVED2,
   SIU_ISEL9_eTSEL0A_eTPU30_PIT0,
   SIU_ISEL9_eTSEL0A_eTPU30_PIT1,
   SIU_ISEL9_eTSEL0A_RESERVED3,
   SIU_ISEL9_eTSEL0A_RESERVED4,
   SIU_ISEL9_eTSEL0A_eTPUB28,
   SIU_ISEL9_eTSEL0A_eTPUB29,
   SIU_ISEL9_eTSEL0A_eTPUB30,
   SIU_ISEL9_eTSEL0A_eTPUB31,
   SIU_ISEL9_eTSEL0A_RESERVED5,
   SIU_ISEL9_eTSEL0A_RESERVED6,
   SIU_ISEL9_eTSEL0A_RESERVED7,
   SIU_ISEL9_eTSEL0A_RESERVED8,
   SIU_ISEL9_eTSEL0A_eMIOS10_PIT2,
   SIU_ISEL9_eTSEL0A_eMIOS10_PIT3,
   SIU_ISEL9_eTSEL0A_RESERVED9,
   SIU_ISEL9_eTSEL0A_RESERVED10,
   SIU_ISEL9_eTSEL0A_RESERVED11,
   SIU_ISEL9_eTSEL0A_RESERVED12,
   SIU_ISEL9_eTSEL0A_RESERVED13,
   SIU_ISEL9_eTSEL0A_RESERVED14,
   SIU_ISEL9_eTSEL0A_RESERVED15,
   SIU_ISEL9_eTSEL0A_RESERVED16,
   SIU_ISEL9_eTSEL0A_RESERVED17,
   SIU_ISEL9_eTSEL0A_eMIOS23

}  SIU_ISEL9_eTSEL0A_T;

//=============================================================================
//  Enumeration: HLT Halt Register
//
// Halt_operation Meaning of Value
//  ===========  ============================================================
//           0 Normal mode
//           1 Stop mode 
//=============================================================================
typedef enum SIU_HLT_MOUDLE_OPERATION_Tag
{
   SIU_MODULE_NORMAL_MODE,
   SIU_MODULE_STOP_MODE

} SIU_HLT_MODULE_OPERATION_T;


//=============================================================================
//  Enumeration: Chip Configuration Register
//
// Meaning of Value
//  ===========  ============================================================
//           0 Calibration_supression_Disable
//           1 Calibration_supression_Enable
//=============================================================================
typedef enum SIU_CCR_CRSE_Tag
{
   SIU_CALIB_REFLECTION_SUPRESSION_DISABLE,
   SIU_CALIB_REFLECTION_SUPRESSION_ENABLE

} SIU_CCR_CRSE_T;



#endif // DD_SIU_H

