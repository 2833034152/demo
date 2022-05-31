/*
用C++读取游戏的进程PID，改写了游戏的执行步骤，相当于hook行为。通过分配1000字节的内存，
在里面进行操作：找到人物对象的地址，将攻击或者被攻击函数里面的血量清零，最后再调回原来游戏执行现场。
从而使人物血量无敌，不影响野怪对象。
*/
#include <iostream>
#include <Windows.h>
using namespace std;
int main() {
    DWORD pid;         //进程id
    HANDLE hprocess;   //该进程的句柄
linput:
    cout << "请输入游戏id: " << endl;
    cin >> pid;
    hprocess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);

    if (hprocess) {
        //分配到的新地址
        LPVOID lCode = VirtualAllocEx(hprocess, NULL, 1000, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

        if (lCode) {
            char data[]{
                0x81, 0xFE,					//cmp esi
                    0x00, 0x00, 0x00, 0x00,		//4cef08
                    0x75, 0x02,					//跳2个字节
                    0x31, 0xFF,					//xor edi , edi
                    0x8b, 0xD0,					//mov eax, eax
                    0x29, 0xFA,					//sub edx, ecx
                    0x39, 0xCA,					//cmp edx, ecx
                    0xE9,						//jmp lCode + 10
                    0x00, 0x00, 0x00, 0x00
            };

            int jmpCodeReturn = 0x41FD67 - ((int)lCode + 0x10) - 5;
            int* nCode = (int*)(data + 0x11);
            nCode[0] = jmpCodeReturn;
            nCode = (int*)(data + 0x02);
            nCode[0] = 0x4CEF08;           //人物角色的首地址

            WriteProcessMemory(hprocess, lCode, data, 0x21, NULL);

            char E9Code[]{ 0xE9, 0x00,0x00,0x00,0x00, 0x90 };
            jmpCodeReturn = (int)lCode - 0x41FD61 - 0x5;
            nCode = (int*)(E9Code + 0x1);
            nCode[0] = jmpCodeReturn;

            DWORD dPro = 0;
            VirtualAllocEx(hprocess, (LPVOID)0x41FD61, 6, PAGE_EXECUTE_READWRITE, dPro);
            WriteProcessMemory(hprocess, (LPVOID)0x41FD61, E9Code, 0x6, NULL);
        }
        else {
            cout << "alloc failed" << endl;
        }
    }
    else goto linput;

}
