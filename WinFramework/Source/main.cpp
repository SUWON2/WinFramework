// ����� ���Ǹ� ���� �ܼ�â�� ���ϴ�.
#if defined(DEBUG) | defined(_DEBUG)
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <crtdbg.h>

#include "Core.h"
#include "Defined.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR szCmdLine, _In_ int nCmdShow)
{
	// �޸� ������ �˻��մϴ�.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// _CrtSetBreakAlloc(0); // �޸� ������ �߻��� ��ġ�� �̵��ϱ� ���� �뵵�� ���Ǵ� �Լ��Դϴ�.
#endif

	Core* core = new Core();
	core->Run(hInstance);

	RELEASE(core);

	return 0;
}