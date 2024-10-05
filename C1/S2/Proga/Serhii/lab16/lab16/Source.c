#include <stdio.h>
#include <Windows.h>
int main()
{
	SetConsoleOutputCP(1251);
	#if defined(__ANDROID__)
		printf("Android OS detected.\n");
	#elif defined(__gnu_linux__)
		printf("Linux OS detected.\n");
	#elif defined(__WIN32__) || defined(__WIN64__) || defined(_WIN16) || defined(_WIN32) || defined(_WIN64) || defined (__WINDOWS__)
		printf("Windows OS detected.\n");
	#elif defined (MSDOS) || defined (__MSDOS__) || defined(_MSDOS) || defined(__DOS__)
		printf("MSDOS detected.\.\n");
	#elif defined(macintosh) || defined(Macintosh) || defined(__APPLE__ && __MACH__)
		printf("Mac OS detected.\n");
	#elif defined(__unix__) || defined(__unix)
		printf("Unix-based OS detected.\n");
	#else
		printf("Unknown OS detected.\n");
	#endif

	#if defined(__BORLANDC__) || defined(__CODEGEARC__)
		printf("Borland C++ compiler detected.\n");
	#elif defined(__HP_cc) || defined(__HP_aCC)
		printf("HP compiler detected.\n");
	#elif defined(__INTEL_COMPILER) || defined(__ICC) || defined(__ECC) || defined(__ICl)
		printf("Intel compiler detected.");
	#elif defined _MSC_VER 
		printf("Microsoft Visual compiler detected.\n");
	#endif

	#if defined(_DEBUG) || defined(_DLL) // Defined as 1 when the /LDd, /MDd, or /MTd compiler option is set.
		printf("Отладка запущена корректно\n");
	#elif defined (__stdcall && __cdecl)
		printf("Stack frame is enabled.\n");
	#elif defined 
	#endif

	#if defined __cplusplus
		printf("Comiled as C++.\n");
	#elif defined __STDC__  
		printf("Comiled as C.\n");
	#elif defined __cplusplus_cli // Defined as the integer literal value 200406 when compiled as C++ and a /clr compiler option is set.
		printf("%d\n", __cplusplus_cli);
	#elif defined(_NATIVE_WCHAR_T_DEFINED) || defined(_WCHAR_T_DEFINED)
		printf("/Zc:wchar_t compiler option is set\n");
	#elif defined _M_FP_PRECISE // Defined as 1 if the /fp:precise compiler option is set.
		printf("/fp:precise compiler option is set\n");
	#else
		printf("not defined\n");
	#endif
		printf("Успешно выполнила свою работу функция \"%s\"\n", __FUNCTION__);
		system("pause");
}