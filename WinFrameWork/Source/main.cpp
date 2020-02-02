// 디버깅 편의를 위해 콘솔창을 띄웁니다.
#if defined(DEBUG) | defined(_DEBUG)
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <crtdbg.h>

#include "Core.h"
#include "Defined.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR szCmdLine, _In_ int nCmdShow)
{
	// 메모리 누수를 검사합니다.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// _CrtSetBreakAlloc(0); // HACK: 메모리 누수가 발생한 위치로 이동하기 위한 용도로 사용되는 함수입니다.
#endif

	Core* core = new Core();
	core->Run(hInstance);

	RELEASE(core);

	return 0;
}