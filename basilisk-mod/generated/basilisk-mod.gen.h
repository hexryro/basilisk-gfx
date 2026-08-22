
 /**
  MIT License
  
  Copyright (c) 2026 switch360hardflip <switch360hardflip@gmail.com>
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
  */ 

 /**
  This file was generated from basilisk-gfx.com

  It is not recommended to make changes to this file as it will be lost if
  the code is regenerated.
  */
        

#ifndef BASILISK_MOD_GEN_H
#define BASILISK_MOD_GEN_H

#include <basilisk-core.h>
#include <basilisk-gfx.h>

typedef struct bsmod_Callbacks bsmod_Callbacks;
typedef struct bsmod_TrackParams bsmod_TrackParams;
typedef struct bsmod_UnicodeBlockRange bsmod_UnicodeBlockRange;
typedef struct bsmod_QueueLoad bsmod_QueueLoad;
typedef struct bsmod_AtlasPacker bsmod_AtlasPacker;
typedef struct bsmod_GlyphInfo bsmod_GlyphInfo;
typedef struct bsmod_TextureInfo bsmod_TextureInfo;
typedef struct bsmod_Chunk bsmod_Chunk;
typedef struct bsmod_Package bsmod_Package;
typedef struct bsmod_Resource bsmod_Resource;
typedef struct bsmod_DraggingParams bsmod_DraggingParams;
typedef struct bsmod_GridClickParams bsmod_GridClickParams;
typedef struct bsmod_SideMenuTab bsmod_SideMenuTab;

typedef enum bsmod_RenderMode bsmod_RenderMode;
typedef enum bsmod_EditType bsmod_EditType;
typedef enum bsmod_DraggingType bsmod_DraggingType;
typedef enum bsmod_SideMenuTabId bsmod_SideMenuTabId;
typedef enum bsmod_UnicodeBlock bsmod_UnicodeBlock;

#define BSMODAPI                                                     \
    _declspec(dllexport)

#define BSMOD_CONTENT_PATH                                           \
    "content/bsmod.bpak"

#define BSMOD_CONFIG_PATH                                            \
    "project/bsmod_config.json"

#define BSMOD_FOREACH_PROC(X)                                        \
    X(PFN_void, >_loadFonts)

#define BSMOD_STRUCT_GEN(TYPE, FUNC, ...)                            \
    TYPE FUNC;

#define BSMOD_COUNT_GEN(TYPE, FUNC, ...)                             \
    +1

#define BSMOD_BPAK_CHUNK_SIZE                                        \
    100'000'000

#define BSMOD_DEFAULT_RADIUS                                         \
    5.0

#define BSMOD_TAB_BAR_HEIGHT                                         \
    20.0

#define BSMOD_GRID_SIDE_MENU_SPACE                                   \
    16.0

#define BSGFX_SIDE_MENU_WIDTH                                        \
    400

#define BSMOD_INPUT_HEIGHT                                           \
    16

#define BSMOD_UI_BASE_TEXT_MATERIAL                                  \
    $bsmod_grey_230

#define BSMOD_CONTEXT_MENU_BUTTON_HEIGHT                             \
    20

#define BSMOD_CONTEXT_MENU_PADDING                                   \
    4

#define BSMOD_HOOKS_PATH                                             \
    "project/bsmod_hooks.json"

#define BSMOD_IDS                                                    \
    &_bsmod_.selected_ids

#define BSMOD_TILE_IDS                                               \
    &_bsmod_.selected_tiles

typedef void (__stdcall* PFN_void)();
typedef unsigned char* (__stdcall* PFN_bsmod_getAtlasTextureData)(bsmod_AtlasPacker*, int);
typedef const char* (__stdcall* PFN_bsmod_GridMenu)(bs_List* widgets);
typedef void (__stdcall* PFN_bsmod_GridMenuCallback)(struct bsgfx_DebugMenuWidget*, int);
enum bsmod_RenderMode {
    BSMOD_RENDER_MODE_NORMAL,
    BSMOD_RENDER_MODE_LIGHT,
    BSMOD_RENDER_MODE_MONO,
    BSMOD_RENDER_MODE_LCD,
    BSMOD_RENDER_MODE_LCD_V,
    BSMOD_RENDER_MODE_SDF,
    BSMOD_RENDER_MODE_MSDF,
};

enum bsmod_EditType {
    BSMOD_EDIT_UNDEFINED,
    BSMOD_EDIT_POSITION,
    BSMOD_EDIT_ROTATION,
    BSMOD_EDIT_SCALE,
};

enum bsmod_DraggingType {
    BSMOD_DRAGGING_UNDEFINED,
    BSMOD_DRAGGING_TILE,
    BSMOD_DRAGGING_ATLAS,
    BSMOD_DRAGGING_TEXTURE,
    BSMOD_DRAGGING_PREFAB,
    BSMOD_DRAGGING_MATERIAL,
    BSMOD_DRAGGING_PRIMITIVE,
    BSMOD_DRAGGING_ITEM,
};

enum bsmod_SideMenuTabId {
    BSMOD_TAB_INSTANCE,
    BSMOD_TAB_MATERIAL,
    BSMOD_TAB_SETTINGS,
    BSMOD_TABS_COUNT,
};

enum bsmod_UnicodeBlock {
    BSMOD_UNICODE_BLOCK_NONE = 0,
    BSMOD_UNICODE_BLOCK_BASIC_LATIN = 1,
    BSMOD_UNICODE_BLOCK_LATIN_1_SUPPLEMENT = 2,
    BSMOD_UNICODE_BLOCK_LATIN_EXTENDED_A = 3,
    BSMOD_UNICODE_BLOCK_LATIN_EXTENDED_B = 4,
    BSMOD_UNICODE_BLOCK_IPA_EXTENSIONS = 5,
    BSMOD_UNICODE_BLOCK_SPACING_MODIFIER_LETTERS = 6,
    BSMOD_UNICODE_BLOCK_COMBINING_DIACRITICAL_MARKS = 7,
    BSMOD_UNICODE_BLOCK_GREEK = 8,
    BSMOD_UNICODE_BLOCK_CYRILLIC = 9,
    BSMOD_UNICODE_BLOCK_ARMENIAN = 10,
    BSMOD_UNICODE_BLOCK_HEBREW = 11,
    BSMOD_UNICODE_BLOCK_ARABIC = 12,
    BSMOD_UNICODE_BLOCK_SYRIAC = 13,
    BSMOD_UNICODE_BLOCK_THAANA = 14,
    BSMOD_UNICODE_BLOCK_DEVANAGARI = 15,
    BSMOD_UNICODE_BLOCK_BENGALI = 16,
    BSMOD_UNICODE_BLOCK_GURMUKHI = 17,
    BSMOD_UNICODE_BLOCK_GUJARATI = 18,
    BSMOD_UNICODE_BLOCK_ORIYA = 19,
    BSMOD_UNICODE_BLOCK_TAMIL = 20,
    BSMOD_UNICODE_BLOCK_TELUGU = 21,
    BSMOD_UNICODE_BLOCK_KANNADA = 22,
    BSMOD_UNICODE_BLOCK_MALAYALAM = 23,
    BSMOD_UNICODE_BLOCK_SINHALA = 24,
    BSMOD_UNICODE_BLOCK_THAI = 25,
    BSMOD_UNICODE_BLOCK_LAO = 26,
    BSMOD_UNICODE_BLOCK_TIBETAN = 27,
    BSMOD_UNICODE_BLOCK_MYANMAR = 28,
    BSMOD_UNICODE_BLOCK_GEORGIAN = 29,
    BSMOD_UNICODE_BLOCK_HANGUL_JAMO = 30,
    BSMOD_UNICODE_BLOCK_ETHIOPIC = 31,
    BSMOD_UNICODE_BLOCK_CHEROKEE = 32,
    BSMOD_UNICODE_BLOCK_UNIFIED_CANADIAN_ABORIGINAL_SYLLABICS = 33,
    BSMOD_UNICODE_BLOCK_OGHAM = 34,
    BSMOD_UNICODE_BLOCK_RUNIC = 35,
    BSMOD_UNICODE_BLOCK_KHMER = 36,
    BSMOD_UNICODE_BLOCK_MONGOLIAN = 37,
    BSMOD_UNICODE_BLOCK_LATIN_EXTENDED_ADDITIONAL = 38,
    BSMOD_UNICODE_BLOCK_GREEK_EXTENDED = 39,
    BSMOD_UNICODE_BLOCK_GENERAL_PUNCTUATION = 40,
    BSMOD_UNICODE_BLOCK_SUPERSCRIPTS_AND_SUBSCRIPTS = 41,
    BSMOD_UNICODE_BLOCK_CURRENCY_SYMBOLS = 42,
    BSMOD_UNICODE_BLOCK_COMBINING_MARKS_FOR_SYMBOLS = 43,
    BSMOD_UNICODE_BLOCK_LETTERLIKE_SYMBOLS = 44,
    BSMOD_UNICODE_BLOCK_NUMBER_FORMS = 45,
    BSMOD_UNICODE_BLOCK_ARROWS = 46,
    BSMOD_UNICODE_BLOCK_MATHEMATICAL_OPERATORS = 47,
    BSMOD_UNICODE_BLOCK_MISCELLANEOUS_TECHNICAL = 48,
    BSMOD_UNICODE_BLOCK_CONTROL_PICTURES = 49,
    BSMOD_UNICODE_BLOCK_OPTICAL_CHARACTER_RECOGNITION = 50,
    BSMOD_UNICODE_BLOCK_ENCLOSED_ALPHANUMERICS = 51,
    BSMOD_UNICODE_BLOCK_BOX_DRAWING = 52,
    BSMOD_UNICODE_BLOCK_BLOCK_ELEMENTS = 53,
    BSMOD_UNICODE_BLOCK_GEOMETRIC_SHAPES = 54,
    BSMOD_UNICODE_BLOCK_MISCELLANEOUS_SYMBOLS = 55,
    BSMOD_UNICODE_BLOCK_DINGBATS = 56,
    BSMOD_UNICODE_BLOCK_BRAILLE_PATTERNS = 57,
    BSMOD_UNICODE_BLOCK_CJK_RADICALS_SUPPLEMENT = 58,
    BSMOD_UNICODE_BLOCK_KANGXI_RADICALS = 59,
    BSMOD_UNICODE_BLOCK_IDEOGRAPHIC_DESCRIPTION_CHARACTERS = 60,
    BSMOD_UNICODE_BLOCK_CJK_SYMBOLS_AND_PUNCTUATION = 61,
    BSMOD_UNICODE_BLOCK_HIRAGANA = 62,
    BSMOD_UNICODE_BLOCK_KATAKANA = 63,
    BSMOD_UNICODE_BLOCK_BOPOMOFO = 64,
    BSMOD_UNICODE_BLOCK_HANGUL_COMPATIBILITY_JAMO = 65,
    BSMOD_UNICODE_BLOCK_KANBUN = 66,
    BSMOD_UNICODE_BLOCK_BOPOMOFO_EXTENDED = 67,
    BSMOD_UNICODE_BLOCK_ENCLOSED_CJK_LETTERS_AND_MONTHS = 68,
    BSMOD_UNICODE_BLOCK_CJK_COMPATIBILITY = 69,
    BSMOD_UNICODE_BLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_A = 70,
    BSMOD_UNICODE_BLOCK_CJK_UNIFIED_IDEOGRAPHS = 71,
    BSMOD_UNICODE_BLOCK_YI_SYLLABLES = 72,
    BSMOD_UNICODE_BLOCK_YI_RADICALS = 73,
    BSMOD_UNICODE_BLOCK_HANGUL_SYLLABLES = 74,
    BSMOD_UNICODE_BLOCK_HIGH_SURROGATES = 75,
    BSMOD_UNICODE_BLOCK_HIGH_PRIVATE_USE_SURROGATES = 76,
    BSMOD_UNICODE_BLOCK_LOW_SURROGATES = 77,
    BSMOD_UNICODE_BLOCK_PRIVATE_USE_AREA = 78,
    BSMOD_UNICODE_BLOCK_PRIVATE_USE = BSMOD_UNICODE_BLOCK_PRIVATE_USE_AREA,
    BSMOD_UNICODE_BLOCK_CJK_COMPATIBILITY_IDEOGRAPHS = 79,
    BSMOD_UNICODE_BLOCK_ALPHABETIC_PRESENTATION_FORMS = 80,
    BSMOD_UNICODE_BLOCK_ARABIC_PRESENTATION_FORMS_A = 81,
    BSMOD_UNICODE_BLOCK_COMBINING_HALF_MARKS = 82,
    BSMOD_UNICODE_BLOCK_CJK_COMPATIBILITY_FORMS = 83,
    BSMOD_UNICODE_BLOCK_SMALL_FORM_VARIANTS = 84,
    BSMOD_UNICODE_BLOCK_ARABIC_PRESENTATION_FORMS_B = 85,
    BSMOD_UNICODE_BLOCK_SPECIALS = 86,
    BSMOD_UNICODE_BLOCK_HALFWIDTH_AND_FULLWIDTH_FORMS = 87,
    BSMOD_UNICODE_BLOCK_OLD_ITALIC = 88,
    BSMOD_UNICODE_BLOCK_GOTHIC = 89,
    BSMOD_UNICODE_BLOCK_DESERET = 90,
    BSMOD_UNICODE_BLOCK_BYZANTINE_MUSICAL_SYMBOLS = 91,
    BSMOD_UNICODE_BLOCK_MUSICAL_SYMBOLS = 92,
    BSMOD_UNICODE_BLOCK_MATHEMATICAL_ALPHANUMERIC_SYMBOLS = 93,
    BSMOD_UNICODE_BLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_B = 94,
    BSMOD_UNICODE_BLOCK_CJK_COMPATIBILITY_IDEOGRAPHS_SUPPLEMENT = 95,
    BSMOD_UNICODE_BLOCK_TAGS = 96,
    BSMOD_UNICODE_BLOCK_CYRILLIC_SUPPLEMENT = 97,
    BSMOD_UNICODE_BLOCK_CYRILLIC_SUPPLEMENTARY = BSMOD_UNICODE_BLOCK_CYRILLIC_SUPPLEMENT,
    BSMOD_UNICODE_BLOCK_TAGALOG = 98,
    BSMOD_UNICODE_BLOCK_HANUNOO = 99,
    BSMOD_UNICODE_BLOCK_BUHID = 100,
    BSMOD_UNICODE_BLOCK_TAGBANWA = 101,
    BSMOD_UNICODE_BLOCK_MISCELLANEOUS_MATHEMATICAL_SYMBOLS_A = 102,
    BSMOD_UNICODE_BLOCK_SUPPLEMENTAL_ARROWS_A = 103,
    BSMOD_UNICODE_BLOCK_SUPPLEMENTAL_ARROWS_B = 104,
    BSMOD_UNICODE_BLOCK_MISCELLANEOUS_MATHEMATICAL_SYMBOLS_B = 105,
    BSMOD_UNICODE_BLOCK_SUPPLEMENTAL_MATHEMATICAL_OPERATORS = 106,
    BSMOD_UNICODE_BLOCK_KATAKANA_PHONETIC_EXTENSIONS = 107,
    BSMOD_UNICODE_BLOCK_VARIATION_SELECTORS = 108,
    BSMOD_UNICODE_BLOCK_SUPPLEMENTARY_PRIVATE_USE_AREA_A = 109,
    BSMOD_UNICODE_BLOCK_SUPPLEMENTARY_PRIVATE_USE_AREA_B = 110,
    BSMOD_UNICODE_BLOCK_LIMBU = 111,
    BSMOD_UNICODE_BLOCK_TAI_LE = 112,
    BSMOD_UNICODE_BLOCK_KHMER_SYMBOLS = 113,
    BSMOD_UNICODE_BLOCK_PHONETIC_EXTENSIONS = 114,
    BSMOD_UNICODE_BLOCK_MISCELLANEOUS_SYMBOLS_AND_ARROWS = 115,
    BSMOD_UNICODE_BLOCK_YIJING_HEXAGRAM_SYMBOLS = 116,
    BSMOD_UNICODE_BLOCK_LINEAR_B_SYLLABARY = 117,
    BSMOD_UNICODE_BLOCK_LINEAR_B_IDEOGRAMS = 118,
    BSMOD_UNICODE_BLOCK_AEGEAN_NUMBERS = 119,
    BSMOD_UNICODE_BLOCK_UGARITIC = 120,
    BSMOD_UNICODE_BLOCK_SHAVIAN = 121,
    BSMOD_UNICODE_BLOCK_OSMANYA = 122,
    BSMOD_UNICODE_BLOCK_CYPRIOT_SYLLABARY = 123,
    BSMOD_UNICODE_BLOCK_TAI_XUAN_JING_SYMBOLS = 124,
    BSMOD_UNICODE_BLOCK_VARIATION_SELECTORS_SUPPLEMENT = 125,
    BSMOD_UNICODE_BLOCK_ANCIENT_GREEK_MUSICAL_NOTATION = 126,
    BSMOD_UNICODE_BLOCK_ANCIENT_GREEK_NUMBERS = 127,
    BSMOD_UNICODE_BLOCK_ARABIC_SUPPLEMENT = 128,
    BSMOD_UNICODE_BLOCK_BUGINESE = 129,
    BSMOD_UNICODE_BLOCK_CJK_STROKES = 130,
    BSMOD_UNICODE_BLOCK_COMBINING_DIACRITICAL_MARKS_SUPPLEMENT = 131,
    BSMOD_UNICODE_BLOCK_COPTIC = 132,
    BSMOD_UNICODE_BLOCK_ETHIOPIC_EXTENDED = 133,
    BSMOD_UNICODE_BLOCK_ETHIOPIC_SUPPLEMENT = 134,
    BSMOD_UNICODE_BLOCK_GEORGIAN_SUPPLEMENT = 135,
    BSMOD_UNICODE_BLOCK_GLAGOLITIC = 136,
    BSMOD_UNICODE_BLOCK_KHAROSHTHI = 137,
    BSMOD_UNICODE_BLOCK_MODIFIER_TONE_LETTERS = 138,
    BSMOD_UNICODE_BLOCK_NEW_TAI_LUE = 139,
    BSMOD_UNICODE_BLOCK_OLD_PERSIAN = 140,
    BSMOD_UNICODE_BLOCK_PHONETIC_EXTENSIONS_SUPPLEMENT = 141,
    BSMOD_UNICODE_BLOCK_SUPPLEMENTAL_PUNCTUATION = 142,
    BSMOD_UNICODE_BLOCK_SYLOTI_NAGRI = 143,
    BSMOD_UNICODE_BLOCK_TIFINAGH = 144,
    BSMOD_UNICODE_BLOCK_VERTICAL_FORMS = 145,
    BSMOD_UNICODE_BLOCK_NKO = 146,
    BSMOD_UNICODE_BLOCK_BALINESE = 147,
    BSMOD_UNICODE_BLOCK_LATIN_EXTENDED_C = 148,
    BSMOD_UNICODE_BLOCK_LATIN_EXTENDED_D = 149,
    BSMOD_UNICODE_BLOCK_PHAGS_PA = 150,
    BSMOD_UNICODE_BLOCK_PHOENICIAN = 151,
    BSMOD_UNICODE_BLOCK_CUNEIFORM = 152,
    BSMOD_UNICODE_BLOCK_CUNEIFORM_NUMBERS_AND_PUNCTUATION = 153,
    BSMOD_UNICODE_BLOCK_COUNTING_ROD_NUMERALS = 154,
    BSMOD_UNICODE_BLOCK_SUNDANESE = 155,
    BSMOD_UNICODE_BLOCK_LEPCHA = 156,
    BSMOD_UNICODE_BLOCK_OL_CHIKI = 157,
    BSMOD_UNICODE_BLOCK_CYRILLIC_EXTENDED_A = 158,
    BSMOD_UNICODE_BLOCK_VAI = 159,
    BSMOD_UNICODE_BLOCK_CYRILLIC_EXTENDED_B = 160,
    BSMOD_UNICODE_BLOCK_SAURASHTRA = 161,
    BSMOD_UNICODE_BLOCK_KAYAH_LI = 162,
    BSMOD_UNICODE_BLOCK_REJANG = 163,
    BSMOD_UNICODE_BLOCK_CHAM = 164,
    BSMOD_UNICODE_BLOCK_ANCIENT_SYMBOLS = 165,
    BSMOD_UNICODE_BLOCK_PHAISTOS_DISC = 166,
    BSMOD_UNICODE_BLOCK_LYCIAN = 167,
    BSMOD_UNICODE_BLOCK_CARIAN = 168,
    BSMOD_UNICODE_BLOCK_LYDIAN = 169,
    BSMOD_UNICODE_BLOCK_MAHJONG_TILES = 170,
    BSMOD_UNICODE_BLOCK_DOMINO_TILES = 171,
    BSMOD_UNICODE_BLOCK_SAMARITAN = 172,
    BSMOD_UNICODE_BLOCK_UNIFIED_CANADIAN_ABORIGINAL_SYLLABICS_EXTENDED = 173,
    BSMOD_UNICODE_BLOCK_TAI_THAM = 174,
    BSMOD_UNICODE_BLOCK_VEDIC_EXTENSIONS = 175,
    BSMOD_UNICODE_BLOCK_LISU = 176,
    BSMOD_UNICODE_BLOCK_BAMUM = 177,
    BSMOD_UNICODE_BLOCK_COMMON_INDIC_NUMBER_FORMS = 178,
    BSMOD_UNICODE_BLOCK_DEVANAGARI_EXTENDED = 179,
    BSMOD_UNICODE_BLOCK_HANGUL_JAMO_EXTENDED_A = 180,
    BSMOD_UNICODE_BLOCK_JAVANESE = 181,
    BSMOD_UNICODE_BLOCK_MYANMAR_EXTENDED_A = 182,
    BSMOD_UNICODE_BLOCK_TAI_VIET = 183,
    BSMOD_UNICODE_BLOCK_MEETEI_MAYEK = 184,
    BSMOD_UNICODE_BLOCK_HANGUL_JAMO_EXTENDED_B = 185,
    BSMOD_UNICODE_BLOCK_IMPERIAL_ARAMAIC = 186,
    BSMOD_UNICODE_BLOCK_OLD_SOUTH_ARABIAN = 187,
    BSMOD_UNICODE_BLOCK_AVESTAN = 188,
    BSMOD_UNICODE_BLOCK_INSCRIPTIONAL_PARTHIAN = 189,
    BSMOD_UNICODE_BLOCK_INSCRIPTIONAL_PAHLAVI = 190,
    BSMOD_UNICODE_BLOCK_OLD_TURKIC = 191,
    BSMOD_UNICODE_BLOCK_RUMI_NUMERAL_SYMBOLS = 192,
    BSMOD_UNICODE_BLOCK_KAITHI = 193,
    BSMOD_UNICODE_BLOCK_EGYPTIAN_HIEROGLYPHS = 194,
    BSMOD_UNICODE_BLOCK_ENCLOSED_ALPHANUMERIC_SUPPLEMENT = 195,
    BSMOD_UNICODE_BLOCK_ENCLOSED_IDEOGRAPHIC_SUPPLEMENT = 196,
    BSMOD_UNICODE_BLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_C = 197,
    BSMOD_UNICODE_BLOCK_MANDAIC = 198,
    BSMOD_UNICODE_BLOCK_BATAK = 199,
    BSMOD_UNICODE_BLOCK_ETHIOPIC_EXTENDED_A = 200,
    BSMOD_UNICODE_BLOCK_BRAHMI = 201,
    BSMOD_UNICODE_BLOCK_BAMUM_SUPPLEMENT = 202,
    BSMOD_UNICODE_BLOCK_KANA_SUPPLEMENT = 203,
    BSMOD_UNICODE_BLOCK_PLAYING_CARDS = 204,
    BSMOD_UNICODE_BLOCK_MISCELLANEOUS_SYMBOLS_AND_PICTOGRAPHS = 205,
    BSMOD_UNICODE_BLOCK_EMOTICONS = 206,
    BSMOD_UNICODE_BLOCK_TRANSPORT_AND_MAP_SYMBOLS = 207,
    BSMOD_UNICODE_BLOCK_ALCHEMICAL_SYMBOLS = 208,
    BSMOD_UNICODE_BLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_D = 209,
    BSMOD_UNICODE_BLOCK_ARABIC_EXTENDED_A = 210,
    BSMOD_UNICODE_BLOCK_ARABIC_MATHEMATICAL_ALPHABETIC_SYMBOLS = 211,
    BSMOD_UNICODE_BLOCK_CHAKMA = 212,
    BSMOD_UNICODE_BLOCK_MEETEI_MAYEK_EXTENSIONS = 213,
    BSMOD_UNICODE_BLOCK_MEROITIC_CURSIVE = 214,
    BSMOD_UNICODE_BLOCK_MEROITIC_HIEROGLYPHS = 215,
    BSMOD_UNICODE_BLOCK_MIAO = 216,
    BSMOD_UNICODE_BLOCK_SHARADA = 217,
    BSMOD_UNICODE_BLOCK_SORA_SOMPENG = 218,
    BSMOD_UNICODE_BLOCK_SUNDANESE_SUPPLEMENT = 219,
    BSMOD_UNICODE_BLOCK_TAKRI = 220,
    BSMOD_UNICODE_BLOCK_BASSA_VAH = 221,
    BSMOD_UNICODE_BLOCK_CAUCASIAN_ALBANIAN = 222,
    BSMOD_UNICODE_BLOCK_COPTIC_EPACT_NUMBERS = 223,
    BSMOD_UNICODE_BLOCK_COMBINING_DIACRITICAL_MARKS_EXTENDED = 224,
    BSMOD_UNICODE_BLOCK_DUPLOYAN = 225,
    BSMOD_UNICODE_BLOCK_ELBASAN = 226,
    BSMOD_UNICODE_BLOCK_GEOMETRIC_SHAPES_EXTENDED = 227,
    BSMOD_UNICODE_BLOCK_GRANTHA = 228,
    BSMOD_UNICODE_BLOCK_KHOJKI = 229,
    BSMOD_UNICODE_BLOCK_KHUDAWADI = 230,
    BSMOD_UNICODE_BLOCK_LATIN_EXTENDED_E = 231,
    BSMOD_UNICODE_BLOCK_LINEAR_A = 232,
    BSMOD_UNICODE_BLOCK_MAHAJANI = 233,
    BSMOD_UNICODE_BLOCK_MANICHAEAN = 234,
    BSMOD_UNICODE_BLOCK_MENDE_KIKAKUI = 235,
    BSMOD_UNICODE_BLOCK_MODI = 236,
    BSMOD_UNICODE_BLOCK_MRO = 237,
    BSMOD_UNICODE_BLOCK_MYANMAR_EXTENDED_B = 238,
    BSMOD_UNICODE_BLOCK_NABATAEAN = 239,
    BSMOD_UNICODE_BLOCK_OLD_NORTH_ARABIAN = 240,
    BSMOD_UNICODE_BLOCK_OLD_PERMIC = 241,
    BSMOD_UNICODE_BLOCK_ORNAMENTAL_DINGBATS = 242,
    BSMOD_UNICODE_BLOCK_PAHAWH_HMONG = 243,
    BSMOD_UNICODE_BLOCK_PALMYRENE = 244,
    BSMOD_UNICODE_BLOCK_PAU_CIN_HAU = 245,
    BSMOD_UNICODE_BLOCK_PSALTER_PAHLAVI = 246,
    BSMOD_UNICODE_BLOCK_SHORTHAND_FORMAT_CONTROLS = 247,
    BSMOD_UNICODE_BLOCK_SIDDHAM = 248,
    BSMOD_UNICODE_BLOCK_SINHALA_ARCHAIC_NUMBERS = 249,
    BSMOD_UNICODE_BLOCK_SUPPLEMENTAL_ARROWS_C = 250,
    BSMOD_UNICODE_BLOCK_TIRHUTA = 251,
    BSMOD_UNICODE_BLOCK_WARANG_CITI = 252,
    BSMOD_UNICODE_BLOCK_AHOM = 253,
    BSMOD_UNICODE_BLOCK_ANATOLIAN_HIEROGLYPHS = 254,
    BSMOD_UNICODE_BLOCK_CHEROKEE_SUPPLEMENT = 255,
    BSMOD_UNICODE_BLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_E = 256,
    BSMOD_UNICODE_BLOCK_EARLY_DYNASTIC_CUNEIFORM = 257,
    BSMOD_UNICODE_BLOCK_HATRAN = 258,
    BSMOD_UNICODE_BLOCK_MULTANI = 259,
    BSMOD_UNICODE_BLOCK_OLD_HUNGARIAN = 260,
    BSMOD_UNICODE_BLOCK_SUPPLEMENTAL_SYMBOLS_AND_PICTOGRAPHS = 261,
    BSMOD_UNICODE_BLOCK_SUTTON_SIGNWRITING = 262,
    BSMOD_UNICODE_BLOCK_ADLAM = 263,
    BSMOD_UNICODE_BLOCK_BHAIKSUKI = 264,
    BSMOD_UNICODE_BLOCK_CYRILLIC_EXTENDED_C = 265,
    BSMOD_UNICODE_BLOCK_GLAGOLITIC_SUPPLEMENT = 266,
    BSMOD_UNICODE_BLOCK_IDEOGRAPHIC_SYMBOLS_AND_PUNCTUATION = 267,
    BSMOD_UNICODE_BLOCK_MARCHEN = 268,
    BSMOD_UNICODE_BLOCK_MONGOLIAN_SUPPLEMENT = 269,
    BSMOD_UNICODE_BLOCK_NEWA = 270,
    BSMOD_UNICODE_BLOCK_OSAGE = 271,
    BSMOD_UNICODE_BLOCK_TANGUT = 272,
    BSMOD_UNICODE_BLOCK_TANGUT_COMPONENTS = 273,
    BSMOD_UNICODE_BLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_F = 274,
    BSMOD_UNICODE_BLOCK_KANA_EXTENDED_A = 275,
    BSMOD_UNICODE_BLOCK_MASARAM_GONDI = 276,
    BSMOD_UNICODE_BLOCK_NUSHU = 277,
    BSMOD_UNICODE_BLOCK_SOYOMBO = 278,
    BSMOD_UNICODE_BLOCK_SYRIAC_SUPPLEMENT = 279,
    BSMOD_UNICODE_BLOCK_ZANABAZAR_SQUARE = 280,
    BSMOD_UNICODE_BLOCK_CHESS_SYMBOLS = 281,
    BSMOD_UNICODE_BLOCK_DOGRA = 282,
    BSMOD_UNICODE_BLOCK_GEORGIAN_EXTENDED = 283,
    BSMOD_UNICODE_BLOCK_GUNJALA_GONDI = 284,
    BSMOD_UNICODE_BLOCK_HANIFI_ROHINGYA = 285,
    BSMOD_UNICODE_BLOCK_INDIC_SIYAQ_NUMBERS = 286,
    BSMOD_UNICODE_BLOCK_MAKASAR = 287,
    BSMOD_UNICODE_BLOCK_MAYAN_NUMERALS = 288,
    BSMOD_UNICODE_BLOCK_MEDEFAIDRIN = 289,
    BSMOD_UNICODE_BLOCK_OLD_SOGDIAN = 290,
    BSMOD_UNICODE_BLOCK_SOGDIAN = 291,
    BSMOD_UNICODE_BLOCK_EGYPTIAN_HIEROGLYPH_FORMAT_CONTROLS = 292,
    BSMOD_UNICODE_BLOCK_ELYMAIC = 293,
    BSMOD_UNICODE_BLOCK_NANDINAGARI = 294,
    BSMOD_UNICODE_BLOCK_NYIAKENG_PUACHUE_HMONG = 295,
    BSMOD_UNICODE_BLOCK_OTTOMAN_SIYAQ_NUMBERS = 296,
    BSMOD_UNICODE_BLOCK_SMALL_KANA_EXTENSION = 297,
    BSMOD_UNICODE_BLOCK_SYMBOLS_AND_PICTOGRAPHS_EXTENDED_A = 298,
    BSMOD_UNICODE_BLOCK_TAMIL_SUPPLEMENT = 299,
    BSMOD_UNICODE_BLOCK_WANCHO = 300,
    BSMOD_UNICODE_BLOCK_CHORASMIAN = 301,
    BSMOD_UNICODE_BLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_G = 302,
    BSMOD_UNICODE_BLOCK_DIVES_AKURU = 303,
    BSMOD_UNICODE_BLOCK_KHITAN_SMALL_SCRIPT = 304,
    BSMOD_UNICODE_BLOCK_LISU_SUPPLEMENT = 305,
    BSMOD_UNICODE_BLOCK_SYMBOLS_FOR_LEGACY_COMPUTING = 306,
    BSMOD_UNICODE_BLOCK_TANGUT_SUPPLEMENT = 307,
    BSMOD_UNICODE_BLOCK_YEZIDI = 308,
    BSMOD_UNICODE_BLOCK_ARABIC_EXTENDED_B = 309,
    BSMOD_UNICODE_BLOCK_CYPRO_MINOAN = 310,
    BSMOD_UNICODE_BLOCK_ETHIOPIC_EXTENDED_B = 311,
    BSMOD_UNICODE_BLOCK_KANA_EXTENDED_B = 312,
    BSMOD_UNICODE_BLOCK_LATIN_EXTENDED_F = 313,
    BSMOD_UNICODE_BLOCK_LATIN_EXTENDED_G = 314,
    BSMOD_UNICODE_BLOCK_OLD_UYGHUR = 315,
    BSMOD_UNICODE_BLOCK_TANGSA = 316,
    BSMOD_UNICODE_BLOCK_TOTO = 317,
    BSMOD_UNICODE_BLOCK_UNIFIED_CANADIAN_ABORIGINAL_SYLLABICS_EXTENDED_A = 318,
    BSMOD_UNICODE_BLOCK_VITHKUQI = 319,
    BSMOD_UNICODE_BLOCK_ZNAMENNY_MUSICAL_NOTATION = 320,
    BSMOD_UNICODE_BLOCK_ARABIC_EXTENDED_C = 321,
    BSMOD_UNICODE_BLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_H = 322,
    BSMOD_UNICODE_BLOCK_CYRILLIC_EXTENDED_D = 323,
    BSMOD_UNICODE_BLOCK_DEVANAGARI_EXTENDED_A = 324,
    BSMOD_UNICODE_BLOCK_KAKTOVIK_NUMERALS = 325,
    BSMOD_UNICODE_BLOCK_KAWI = 326,
    BSMOD_UNICODE_BLOCK_NAG_MUNDARI = 327,
    BSMOD_UNICODE_BLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_I = 328,
    BSMOD_UNICODE_BLOCK_EGYPTIAN_HIEROGLYPHS_EXTENDED_A = 329,
    BSMOD_UNICODE_BLOCK_GARAY = 330,
    BSMOD_UNICODE_BLOCK_GURUNG_KHEMA = 331,
    BSMOD_UNICODE_BLOCK_KIRAT_RAI = 332,
    BSMOD_UNICODE_BLOCK_MYANMAR_EXTENDED_C = 333,
    BSMOD_UNICODE_BLOCK_OL_ONAL = 334,
    BSMOD_UNICODE_BLOCK_SUNUWAR = 335,
    BSMOD_UNICODE_BLOCK_SYMBOLS_FOR_LEGACY_COMPUTING_SUPPLEMENT = 336,
    BSMOD_UNICODE_BLOCK_TODHRI = 337,
    BSMOD_UNICODE_BLOCK_TULU_TIGALARI = 338,
    BSMOD_UNICODE_BLOCK_BERIA_ERFE = 339,
    BSMOD_UNICODE_BLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_J = 340,
    BSMOD_UNICODE_BLOCK_MISCELLANEOUS_SYMBOLS_SUPPLEMENT = 341,
    BSMOD_UNICODE_BLOCK_SHARADA_SUPPLEMENT = 342,
    BSMOD_UNICODE_BLOCK_SIDETIC = 343,
    BSMOD_UNICODE_BLOCK_TAI_YO = 344,
    BSMOD_UNICODE_BLOCK_TANGUT_COMPONENTS_SUPPLEMENT = 345,
    BSMOD_UNICODE_BLOCK_TOLONG_SIKI = 346,
    BSMOD_UNICODE_BLOCK_ARCHAIC_CUNEIFORM_NUMERALS = 347,
    BSMOD_UNICODE_BLOCK_BENGALI_SUPPLEMENT = 348,
    BSMOD_UNICODE_BLOCK_CHISOI = 349,
    BSMOD_UNICODE_BLOCK_JURCHEN = 350,
    BSMOD_UNICODE_BLOCK_JURCHEN_RADICALS = 351,
    BSMOD_UNICODE_BLOCK_MISCELLANEOUS_SYMBOLS_AND_ARROWS_EXTENDED = 352,
    BSMOD_UNICODE_BLOCK_MUSICAL_SYMBOLS_SUPPLEMENT = 353,
    BSMOD_UNICODE_BLOCK_SEAL = 354,
    BSMOD_UNICODE_BLOCK_COUNT = 355,
};

struct bsmod_Callbacks {
    PFN_void tick;
};

struct bsmod_TrackParams {
    char* path;
    char* package;
    char* prefix;
    union {
        struct {
            bool compile_references;
        };
    };
};

struct bsmod_UnicodeBlockRange {
    bs_U32 offset;
    bs_U32 count;
    bs_U32 size;
    bsmod_UnicodeBlock block;
    bool rasterize;
    bool keep_ttf;
};

struct bsmod_QueueLoad {
    bs_ResourceType type;
    char* path;
};

struct bsmod_AtlasPacker {
    bs_List info;
    bs_List rects;
};

struct bsmod_GlyphInfo {
    int page;
    unsigned int glyph_id;
};

struct bsmod_TextureInfo {
    char* name;
    PFN_bsmod_getAtlasTextureData get_data;
    void* param;
    unsigned char* data;
    int name_length;
    int category;
    int page;
};

struct bsmod_Chunk {
    bs_List bin;
    int id;
    bool has_changes;
};

struct bsmod_Package {
    bs_U64 name_hash;
    char* name;
    bs_U64 directory_hash;
    char* directory;
    char* path;
    bs_U64 path_hash;
    bs_List chunks;
    bs_List resources;
    bool has_changes;
    bool is_initialized;
};

struct bsmod_Resource {
    bs_U64 name_hash;
    bs_I32 chunk;
    bs_I32 offset;
    bs_I32 size;
    bs_I32 name_length;
    bs_I32 type;
    char* name;
    bool has_changes;
};

struct bsmod_DraggingParams {
    int t;
};

struct bsmod_GridClickParams {
    int atlas_id;
};

struct bsmod_SideMenuTab {
    const char* name;
    bsgfx_AtlasCache* (*cache)();
    void (*push_widgets)(bs_List*, bs_vec2);
    void (*on_click)(bsmod_GridClickParams);
};

 /**
  @return void
  */
BSMODAPI void
bsmod_enableValidation();

 /**
  @return void
  */
BSMODAPI void
bsmod_disableValidation();

 /**
  @return const int*
  */
BSMODAPI const int*
bsmod_subtypes();

 /**
  @return bsmod_Callbacks*
  */
BSMODAPI bsmod_Callbacks*
bsmod_callbacks();

 /**
  @return void
  */
BSMODAPI void
bsmod_copyHoveringDataToBuffer();

 /**
  @return bs_Queue*
  */
BSMODAPI bs_Queue*
bsmod_onQueue();

 /**
  @return void
  */
BSMODAPI void
bsmod_onIni();

 /**
  @return void
  */
BSMODAPI void
bsmod_onLateIni();

 /**
  @param range
  @return void
  */
BSMODAPI void
bsmod_onCreateQuadSubtypes(
    bs_Range range);

 /**
  @return void
  */
BSMODAPI void
bsmod_onLoad();

 /**
  @return void
  */
BSMODAPI void
bsmod_bindAtlases();

 /**
  @return void
  */
BSMODAPI void
bsmod_onGfxRender();

 /**
  @return void
  */
BSMODAPI void
bsmod_onTick();

 /**
  @param type_id
  @param id
  @return void
  */
BSMODAPI void
bsmod_onMap(
    bsgfx_TypeId type_id,
    int id);

 /**
  @return void
  */
BSMODAPI void
bsmod_beginTrackChanges();

 /**
  @return void
  */
BSMODAPI void
bsmod_tickTracker();

 /**
  @return void
  */
BSMODAPI void
bsmod_onTrack();

 /**
  @param params
  @return void
  */
BSMODAPI void
bsmod_onCompileShader(
    bsmod_TrackParams params);

 /**
  @param params
  @return void
  */
BSMODAPI void
bsmod_onConvertFont(
    bsmod_TrackParams params);

 /**
  @param params
  @return void
  */
BSMODAPI void
bsmod_onPackAtlas(
    bsmod_TrackParams params);

 /**
  @param params
  @return void
  */
BSMODAPI void
bsmod_onPackModels(
    bsmod_TrackParams params);

 /**
  @param params
  @return void
  */
BSMODAPI void
bsmod_onPackBinary(
    bsmod_TrackParams params);

 /**
  @param params
  @return void
  */
BSMODAPI void
bsmod_onPackTextureArray(
    bsmod_TrackParams params);

 /**
  @param render_mode
  @param package_name
  @param ttf_path
  @param blocks
  @param blocks_count
  @param pt_sizes
  @param pt_sizes_count
  @param resource_name
  @param resource_name_length
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_packFont(
    bsmod_RenderMode render_mode[],
    char* package_name,
    char* ttf_path,
    bsmod_UnicodeBlockRange blocks[],
    int blocks_count,
    int pt_sizes[],
    int pt_sizes_count,
    char* resource_name,
    int resource_name_length);

 /**
  @param packer
  @param data
  @param get_data
  @param param
  @param width
  @param height
  @param category
  @param name
  @return bsmod_TextureInfo*
  */
BSMODAPI bsmod_TextureInfo*
bsmod_packAtlasTexture(
    bsmod_AtlasPacker* packer,
    unsigned char* data,
    PFN_bsmod_getAtlasTextureData get_data,
    void* param,
    int width,
    int height,
    int category,
    char* name);

 /**
  @param packer
  @param data
  @param get_data
  @param param
  @param width
  @param height
  @param category
  @param name
  @param name_length
  @return bsmod_TextureInfo*
  */
BSMODAPI bsmod_TextureInfo*
bsmod_packAtlasTextureN(
    bsmod_AtlasPacker* packer,
    unsigned char* data,
    PFN_bsmod_getAtlasTextureData get_data,
    void* param,
    int width,
    int height,
    int category,
    char* name,
    int name_length);

 /**
  @param packer
  @param data
  @param get_data
  @param param
  @param width
  @param height
  @param category
  @param format
  @param args
  @return bsmod_TextureInfo*
  */
BSMODAPI bsmod_TextureInfo*
bsmod_packAtlasTextureV(
    bsmod_AtlasPacker* packer,
    unsigned char* data,
    PFN_bsmod_getAtlasTextureData get_data,
    void* param,
    int width,
    int height,
    int category,
    char* format,
    va_list args);

 /**
  @param packer
  @param data
  @param get_data
  @param param
  @param width
  @param height
  @param category
  @param format
  @param ...
  @return bsmod_TextureInfo*
  */
BSMODAPI bsmod_TextureInfo*
bsmod_packAtlasTextureF(
    bsmod_AtlasPacker* packer,
    unsigned char* data,
    PFN_bsmod_getAtlasTextureData get_data,
    void* param,
    int width,
    int height,
    int category,
    char* format,
     ...);

 /**
  @param packer
  @return void
  */
BSMODAPI void
bsmod_destroyAtlasPacker(
    bsmod_AtlasPacker* packer);

 /**
  @param packer
  @param width
  @param height
  @param channels_count
  @param package
  @param resource_name
  @param allow_paging
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_packAtlas(
    bsmod_AtlasPacker* packer,
    int width,
    int height,
    int channels_count,
    char* package,
    char* resource_name,
    bool allow_paging);

 /**
  @return bsmod_AtlasPacker
  */
BSMODAPI bsmod_AtlasPacker
bsmod_createAtlasPacker();

 /**
  @param directory_name
  @param package_name
  @param resource_name
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_packImageDirectory(
    char* directory_name,
    char* package_name,
    char* resource_name);

 /**
  @param scroll
  @param out
  @return void
  */
BSMODAPI void
bsmod_scrollbar(
    const int* scroll,
    bsgfx_Scrollbar* out);

 /**
  @param width
  @param indent
  @param out
  @return void
  */
BSMODAPI void
bsmod_dividerWidget(
    float width,
    int indent,
    bsgfx_Widget* out);

 /**
  @param cache
  @param align_height
  @param offset
  @param advance_flags
  @param out
  @return void
  */
BSMODAPI void
bsmod_iconWidget(
    const bsgfx_AtlasCache* cache,
    float align_height,
    bs_vec3 offset,
    bs_U32 advance_flags,
    bsgfx_Widget* out);

 /**
  @return bs_List*
  */
BSMODAPI bs_List*
bsmod_packages();

 /**
  @param path
  @return bsmod_Package*
  */
BSMODAPI bsmod_Package*
bsmod_queryPackage(
    const char* path);

 /**
  @param path
  @return bsmod_Package*
  */
BSMODAPI bsmod_Package*
bsmod_ensurePackage(
    const char* path);

 /**
  @param package
  @param type
  @param name
  @return bsmod_Resource*
  */
BSMODAPI bsmod_Resource*
bsmod_queryResource(
    bsmod_Package* package,
    bs_ResourceType type,
    const char* name);

 /**
  @param type
  @param package_id
  @param name
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_loadResource(
    int type,
    int package_id,
    char* name);

 /**
  @param package_id
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_iniPackage(
    int package_id);

 /**
  @param type
  @param data
  @param data_size
  @param package_name
  @param resource_name
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_packResource(
    bs_ResourceType type,
    unsigned char* data,
    size_t data_size,
    const char* package_name,
    char* resource_name);

 /**
  @param type
  @param data
  @param data_size
  @param package_name
  @param resource_name
  @param resource_name_length
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_packResourceN(
    bs_ResourceType type,
    unsigned char* data,
    size_t data_size,
    const char* package_name,
    char* resource_name,
    int resource_name_length);

 /**
  @param type
  @param data
  @param data_size
  @param package_name
  @param format
  @param args
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_packResourceV(
    bs_ResourceType type,
    unsigned char* data,
    size_t data_size,
    const char* package_name,
    char* format,
    va_list args);

 /**
  @param type
  @param data
  @param data_size
  @param package_name
  @param format
  @param ...
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_packResourceF(
    bs_ResourceType type,
    unsigned char* data,
    size_t data_size,
    const char* package_name,
    char* format,
     ...);

 /**
  @param path
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_savePackage(
    char* path);

 /**
  @param path
  @param path_length
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_savePackageN(
    char* path,
    int path_length);

 /**
  @param format
  @param args
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_savePackageV(
    char* format,
    va_list args);

 /**
  @param format
  @param ...
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_savePackageF(
    char* format,
     ...);

 /**
  @return void
  */
BSMODAPI void
bsmod_loadShaderReferences();

 /**
  @return void
  */
BSMODAPI void
bsmod_updateShaderReferences();

 /**
  @return void
  */
BSMODAPI void
bsmod_iniCompiler();

 /**
  @param path
  @param name
  @param package
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_compileShader(
    char* path,
    char* name,
    char* package);

 /**
  @param package
  @param name
  @param callback
  @return void
  */
BSMODAPI void
bsmod_queueRasterize(
    const char* package,
    const char* name,
    bs_Callback callback);

 /**
  @return void
  */
BSMODAPI void
bsmod_pollRasterizer();

 /**
  @param render_size
  @param output_size
  @return void
  */
BSMODAPI void
bsmod_beginRasterize(
    bs_ivec2 render_size,
    bs_ivec2 output_size);

 /**
  @param queue
  @return void
  */
BSMODAPI void
bsmod_endRasterize(
    bs_Queue* queue);

 /**
  @param queue
  @param pipeline_hash
  @param subtype
  @param instance_offset
  @param instance_count
  @param category
  @param name
  @param width
  @param height
  @param push_constant_size
  @param push_constant
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_rasterizeInstance(
    bs_Queue* queue,
    bs_PipelineHash pipeline_hash,
    bsgfx_InstanceSubtype* subtype,
    int instance_offset,
    int instance_count,
    int category,
    char* name,
    int width,
    int height,
    size_t push_constant_size,
    unsigned char* push_constant);

 /**
  @return void
  */
BSMODAPI void
bsmod_instanceTransform();

 /**
  @return void
  */
BSMODAPI void
bsmod_selectHoveringTypes();

 /**
  @param plural
  @return bsgfx_TypeId
  */
BSMODAPI bsgfx_TypeId
bsmod_queryType(
    const char* plural);

 /**
  @param type_id
  @param id
  @return void
  */
BSMODAPI void
bsmod_delete(
    bsgfx_TypeId type_id,
    int id);

 /**
  @param type_id
  @return void
  */
BSMODAPI void
bsmod_deleteSelected(
    bsgfx_TypeId type_id);

 /**
  @param id
  @param value
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_saveType(
    bsgfx_TypeId id,
    char* value);

 /**
  @param id
  @param value
  @param value_length
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_saveTypeN(
    bsgfx_TypeId id,
    char* value,
    int value_length);

 /**
  @param id
  @param format
  @param args
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_saveTypeV(
    bsgfx_TypeId id,
    char* format,
    va_list args);

 /**
  @param id
  @param format
  @param ...
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_saveTypeF(
    bsgfx_TypeId id,
    char* format,
     ...);

 /**
  @param id
  @param data
  @return void*
  */
BSMODAPI void*
bsmod_add(
    bsgfx_TypeId id,
    void* data);

 /**
  @param list
  @param type
  @param id
  @return bool
  */
BSMODAPI bool
bsmod_isSelected(
    bs_List* list,
    bsgfx_TypeId type,
    int id);

 /**
  @param list
  @param type
  @param id
  @return void
  */
BSMODAPI void
bsmod_select(
    bs_List* list,
    bsgfx_TypeId type,
    int id);

 /**
  @return void
  */
BSMODAPI void
bsmod_deselectAll();

 /**
  @param list
  @param first
  @param count
  @return void
  */
BSMODAPI void
bsmod_deselectRange(
    bs_List* list,
    int first,
    int count);

 /**
  @param list
  @param id
  @return void
  */
BSMODAPI void
bsmod_deselectIndex(
    bs_List* list,
    int id);

 /**
  @param list
  @param id
  @return void
  */
BSMODAPI void
bsmod_deselect(
    bs_List* list,
    int id);

 /**
  @param list
  @return int
  */
BSMODAPI int
bsmod_firstSelectedId(
    bs_List* list);

 /**
  @param list
  @return int
  */
BSMODAPI int
bsmod_lastSelectedId(
    bs_List* list);

 /**
  @param type_id
  @param id
  @return void*
  */
BSMODAPI void*
bsmod_removeFlexible(
    bsgfx_TypeId type_id,
    int id);

 /**
  @param type_id
  @param id
  @param data
  @return void*
  */
BSMODAPI void*
bsmod_addFlexible(
    bsgfx_TypeId type_id,
    int id,
    void* data);

 /**
  @return void
  */
BSMODAPI void
bsmod_readHoveringOutputs();

 /**
  @return void
  */
BSMODAPI void
bsmod_readHoveringInstanceData();

 /**
  @return void
  */
BSMODAPI void
bsmod_readHoveringVertex();

 /**
  @return void
  */
BSMODAPI void
bsmod_editSelectedType();

 /**
  @param package_id
  @return void
  */
BSMODAPI void
bsmod_ensureTypeVersionsAreUpToDate(
    int package_id);

 /**
  @return void
  */
BSMODAPI void
bsmod_renderBillboards();

 /**
  @return void
  */
BSMODAPI void
bsmod_instanceUI();

 /**
  @param widgets
  @param name
  @param offset
  @param width
  @param v
  @param n
  @return void
  */
BSMODAPI void
bsmod_pushVecNWidget(
    bs_List* widgets,
    const char* name,
    bs_vec3 offset,
    float width,
    float* v,
    int n);

 /**
  @param widgets
  @param value
  @param offset
  @param width
  @param name_padding
  @param skip_advance
  @param is_last
  @param has_buttons
  @param name
  @return void
  */
BSMODAPI void
bsmod_pushInputWidget(
    bs_List* widgets,
    void* value,
    bs_vec3 offset,
    float width,
    int name_padding,
    bool skip_advance,
    bool is_last,
    bool has_buttons,
    const char* name);

 /**
  @param position
  @param size
  @return void
  */
BSMODAPI void
bsmod_instanceTileContextMenu(
    bs_vec3 position,
    bs_vec2 size);

 /**
  @param widgets
  @param position
  @param size
  @return void
  */
BSMODAPI void
bsmod_instanceContextMenu(
    bs_List* widgets,
    bs_vec3 position,
    bs_vec2 size);

 /**
  @param widgets
  @param menu_size
  @param icon_offset
  @param icon
  @param name
  @param indent
  @param action
  @param expandable
  @return void
  */
BSMODAPI void
bsmod_pushContextMenuButton(
    bs_List* widgets,
    bs_vec2 menu_size,
    bs_vec3 icon_offset,
    bsgfx_AtlasCache* icon,
    const char* name,
    int indent,
    PFN_bsgfx_ButtonWidgetCallback action,
    bool expandable);

 /**
  @param position
  @param dimensions
  @return void
  */
BSMODAPI void
bsmod_instanceGridMenu(
    bs_vec3 position,
    bs_vec2 dimensions);

 /**
  @return void
  */
BSMODAPI void
bsmod_instanceLightBillboards();

 /**
  @param widgets
  @param background_size
  @return void
  */
BSMODAPI void
bsmod_pushMaterialWidgets(
    bs_List* widgets,
    bs_vec2 background_size);

 /**
  @param params
  @return void
  */
BSMODAPI void
bsmod_onDragMaterial(
    bsmod_DraggingParams params);

 /**
  @param params
  @return void
  */
BSMODAPI void
bsmod_onClickMaterialMenu(
    bsmod_GridClickParams params);

 /**
  @return void
  */
BSMODAPI void
bsmod_rasterizeMaterialIcons();

 /**
  @param widgets
  @param background_size
  @return void
  */
BSMODAPI void
bsmod_pushPrefabMenuWidgets(
    bs_List* widgets,
    bs_vec2 background_size);

 /**
  @param widget
  @param position
  @param id
  @param hovering
  @return bool
  */
BSMODAPI bool
bsmod_instancePrefabPreview(
    bsgfx_Widget* widget,
    bs_vec2* position,
    int id,
    bool hovering);

 /**
  @param params
  @return void
  */
BSMODAPI void
bsmod_onDragPrefab(
    bsmod_DraggingParams params);

 /**
  @return void
  */
BSMODAPI void
bsmod_rasterizePrefabIcons();

 /**
  @param widget
  @param position
  @param id
  @param hovering
  @return bool
  */
BSMODAPI bool
bsmod_instancePrimitivePreview(
    bsgfx_Widget* widget,
    bs_vec2* position,
    int id,
    bool hovering);

 /**
  @param params
  @return void
  */
BSMODAPI void
bsmod_onDragPrimitive(
    bsmod_DraggingParams params);

 /**
  @return void
  */
BSMODAPI void
bsmod_rasterizePrimitiveIcons();

 /**
  @param id
  @param params
  @return void
  */
BSMODAPI void
bsmod_setSideMenuTab(
    int id,
    bsmod_GridClickParams params);

 /**
  @param position
  @param dimensions
  @return void
  */
BSMODAPI void
bsmod_instanceSideMenu(
    bs_vec3 position,
    bs_vec2 dimensions);

 /**
  @param widgets
  @param background_size
  @return void
  */
BSMODAPI void
bsmod_pushTileMenuWidgets(
    bs_List* widgets,
    bs_vec2 background_size);

 /**
  @param widget
  @param position
  @param id
  @param hovering
  @return bool
  */
BSMODAPI bool
bsmod_instanceTilePreview(
    bsgfx_Widget* widget,
    bs_vec2* position,
    int id,
    bool hovering);

 /**
  @param params
  @return void
  */
BSMODAPI void
bsmod_onDragTile(
    bsmod_DraggingParams params);

BSMODAPI extern bsmod_Callbacks _bsmod_callbacks_;
BSMODAPI extern bs_Json _bsmod_config_;
BSMODAPI extern bool _bsmod_instance_grid_menu_;
BSMODAPI extern bs_String* _bsmod_search_input_;
BSMODAPI extern bsmod_SideMenuTab _bsmod_side_menu_tabs_[BSMOD_TABS_COUNT];

#endif
