#include <basilisk-gfx.h>

static int bs_sizeIndex(int x) {
	switch (x)
	{
	case 4:   return 0;
	case 6:   return 1;
	case 8:   return 2;
	case 9:   return 3;
	case 10:  return 4;
	case 11:  return 5;
	case 12:  return 6;
	case 13:  return 7;
	case 14:  return 8;
	case 16:  return 9;
	case 18:  return 10;
	case 20:  return 11;
	case 22:  return 12;
	case 24:  return 13;
	case 28:  return 14;
	case 32:  return 15;
	case 36:  return 16;
	case 40:  return 17;
	case 48:  return 18;
	case 56:  return 19;
	case 64:  return 20;
	case 72:  return 21;
	case 144: return 22;
	}

	return 0;
}

typedef struct {
	int subtype;
} bsgfx_FontCollection;

void bsgfx_fontCollection(bs_Object* object) {

}