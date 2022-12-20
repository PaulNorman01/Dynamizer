#pragma once

#include <iostream>
#include <Windows.h>
#include <intrin.h>
#include <Windows.h>
#include <TlHelp32.h>
#include <DbgHelp.h>
#include <stdio.h>
#include <Intrin.h> 
#include <Winternl.h>
#include <thread>
#include <Iphlpapi.h>
#include <pathcch.h>
#include <bcrypt.h>
#include <Lmcons.h>
#include <strsafe.h>
#include <tlhelp32.h>
#include <comdef.h>
#include <sddl.h>
#include <wil/resource.h>
#include <psapi.h>
#include <aclapi.h>
#include <type_traits>
#include <vector>
#include <string>


#pragma comment(lib, "dbghelp.lib")

bool g_bDebugged{ false };
std::atomic<bool> g_bCtlCCatched{ false };



static LONG WINAPI CtrlEventExeptionHandler(PEXCEPTION_POINTERS pExceptionInfo)
{
    if (pExceptionInfo->ExceptionRecord->ExceptionCode == DBG_CONTROL_C)
    {
        g_bDebugged = true;
        g_bCtlCCatched.store(true);
    }
    return EXCEPTION_CONTINUE_EXECUTION;
}


static BOOL WINAPI CtrlHandler(DWORD fdwCtrlType)
{
    switch (fdwCtrlType)
    {
    case CTRL_C_EVENT:
        g_bCtlCCatched.store(true);
        return TRUE;
    default:
        return FALSE;
    }
}


void EventCtrlFunction(void)
{
    PVOID hVeh = nullptr;
    BOOL bCtrlHadnlerSet = FALSE;

    __try
    {
        hVeh = AddVectoredExceptionHandler(TRUE, CtrlEventExeptionHandler);
        if (!hVeh)
            __leave;

        bCtrlHadnlerSet = SetConsoleCtrlHandler(CtrlHandler, TRUE);
        if (!bCtrlHadnlerSet)
            __leave;

        GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0);
        while (!g_bCtlCCatched.load())
            ;
    }
    __finally
    {
        if (bCtrlHadnlerSet)
            SetConsoleCtrlHandler(CtrlHandler, FALSE);

        if (hVeh)
            RemoveVectoredExceptionHandler(hVeh);
    }

    if (g_bDebugged)
        exit(0);
}


void AntiStep(void)
{

    PVOID pRetAddress = _ReturnAddress();
    BYTE uByte;
    if (FALSE != Toolhelp32ReadProcessMemory(GetCurrentProcessId(), _ReturnAddress(), &uByte, sizeof(BYTE), NULL))
    {
        if (uByte == 0xCC)
            ExitProcess(0);
    }
}


void handleException(void)
{
    //invalid handle
    HANDLE h_invalid = (HANDLE)0xDEADBEEF;

    __try
    {
        CloseHandle(h_invalid);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        exit(0);
    }
}


void StopHardwareDebugger(HANDLE thrd)
{
    CONTEXT ctx = {};
    ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;
    if (GetThreadContext(thrd, &ctx))
    {
        if (ctx.Dr0 != 0 || ctx.Dr1 != 0 || ctx.Dr2 != 0 || ctx.Dr3 != 0)
        {
            std::cout << "Hardware BP Detected!" << std::endl;
            Sleep(3000);
            exit(-1);
        }
    }
}
