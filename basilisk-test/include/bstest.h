#ifndef BSTEST_H
#define BSTEST_H

#define BSTESTAPI _declspec(dllexport)
#define BSTEST_CONTENT_PATH "project/basilisk-test/bstest"

#include <bs_objects.h>
#include <bsmod_bpak.h>

typedef struct {
	int x;
} bstest_TestData;

extern int _bstest_package;

static inline int bstest_loadPackage() {
	bsmod_iniPackage(BSTEST_CONTENT_PATH);
	_bstest_package = bs_loadPackage(BSTEST_CONTENT_PATH);

	return _bstest_package;
}

#endif