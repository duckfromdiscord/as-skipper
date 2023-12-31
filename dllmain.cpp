#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <chrono>
#include <thread>
#include <stdexcept>

#include <string>
#include <sstream>

void skip() {
	// WILL NOT WORK without this line
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));


	// Instructions by Dylan - https://web.archive.org/web/20190911112730/http://www.audio-surf.com/forum/index.php/topic,2885.0.html
	HWND hwndTargetWin = FindWindowA(NULL, "Audiosurf");

	/*std::stringstream ss{};
	ss << hwndTargetWin;
	MessageBoxA(nullptr, ss.str().c_str(), "Audiosurf hWnd", MB_OK | MB_ICONERROR);*/
	// if the above returns 0000000, increase sleep time and try again


	std::string str = "ascommand quickstartregisterwindow wtfamisupposedtoputhere";
	COPYDATASTRUCT cds;
	cds.cbData = strlen(str.c_str()) + 1;
	cds.lpData = (void*)str.c_str();

	SendMessage(hwndTargetWin, WM_COPYDATA, 0, (LPARAM)&cds);
}

uint32_t __stdcall init(void* args)
{

	skip();

	while (true)
		std::this_thread::sleep_for(std::chrono::milliseconds(50));

	return 0;
}

BOOL WINAPI DllMain(HMODULE handle, DWORD reason, LPVOID reserved)
{

	
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(handle);

		
		if (const auto thread = (HANDLE)_beginthreadex(nullptr, 0, &init, nullptr, 0, nullptr))
		{
			//CloseHandle(thread);
			return 1;
		}
	}

	return 0;
}
