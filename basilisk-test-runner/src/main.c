#include <bstest.h>
#include <bs_log.h>
#include <bsgfx.h>

#include <windows.h>
#include <stdio.h>

typedef void(* PFN_bstest_func)();

static void bstest_ini() {
    bs_args()->send_bugs = false;

    HMODULE hmodule = LoadLibrary("basilisk-test.dll");
    if (!hmodule) {
        DWORD code = GetLastError();
        printf("Failed to load basilisk-test.dll, GetLastError returned %d\n", code);
        return 1;
    }

    unsigned char* base = hmodule;

    IMAGE_DOS_HEADER* dos = base;
    IMAGE_NT_HEADERS* nt = base + dos->e_lfanew;

    IMAGE_DATA_DIRECTORY data = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];

    if (data.VirtualAddress == 0) {
        printf("No tests found\n");
        FreeLibrary(hmodule);
        return;
    }

    IMAGE_EXPORT_DIRECTORY* directory = base + data.VirtualAddress;
    DWORD* names = base + directory->AddressOfNames;

    WORD* ordinals = base + directory->AddressOfNameOrdinals;
    DWORD* functions = base + directory->AddressOfFunctions;

    for (DWORD i = 0; i < directory->NumberOfNames; i++) {
        const char* name = base + names[i];
        WORD ordinal = ordinals[i];

        PFN_bstest_func func = base + functions[ordinal];

        func((bstest_TestData) {
            0
        });
    }

    FreeLibrary(hmodule);
}

int main(int argc, char* argv[]) {
    bsgfx_Callbacks* callbacks = bsgfx_callbacks();
    callbacks->ini = bstest_ini;
    bsgfx_ini("basilisk-test", 1920, 1080, 0, NULL);

	return 0;
}