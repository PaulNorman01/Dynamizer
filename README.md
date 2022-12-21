# Dynamizer
Reduce Dynamic Analysis Detection Rates With Built-In Unhooker, Anti Analysis Techniques, And String Obfuscator Modules. Makes Life Harder For Malware Analysts to Dissect Your Specimen.

Modules Were Selected Carefully To avoid Possible Conflicts With Your Codes So It Can Easily Be Integrated Inside Your Projects.

## Capabilities
- [x] String Obfuscation
- [x] Anti Step Over
- [x] Anti Software Breakpoint
- [x] Anti Hardware Breakpoint
- [x] .text CRC Check
- [x] Self Debugging Closse Handle
- [x] GenerateConsoleCtrlEvent()
- [x] Return Address Manipulation 
- [x] System DLL Unhooker
- [ ] Anti Sandbox -> Will Be Included In The Next Update

## Documentation

### General Usage
__Copy Both .hpp Files To Your Project Directory And Insert `#include "CommonIncludes.hpp"` In Your Main.cpp File.__

*You Are Not Forced To Use All of The Below Modules In Your Coding Project. Choose Any of The Followings That Suits You The Best.*

### Using Return Address Manipulator

``` 
void SomeFunction(SomeParameters)
{
  WALKER;  <------

  //Rest Of The Code...
}
```

### Using String Obfuscator

``` 
void SomeFunction(SomeParameters)
{
  std::cout << StringKrypt("12345!");  <------

  //Rest Of The Code...
}
```



__StringKrypt("") / StringKrypt(L"") Can Be Used In Functions Too!__

```
int main()
{
  if (strcmp((char*)hookedSectionHeader->Name, StringKrypt(".text")) == 0)
    //Do Something
  
  //Rest Of The Code
}
```

### Using Anti Debug Modules

``` 
BOOL SomeFunction(void)
{
	EventCtrlFunction();
	handleException();
	StopHardwareDebugger(thrd);
	AntiStep();
	
	//Rest Of The Code...
}
```
__StopHardwareDebugger(thrd) Requires A Handle To A Thread Of Your Choosing. You Can Easily Use Something Like ` HANDLE thrd = GetCurrentThread(); ` And Send Its value To The StopHardwareDebugger Function.__

### Using All Anti-Debug Modules In a Parallel Thread

```
int main(int argc, char *argv[])
{
	HANDLE thrd = GetCurrentThread();
	std::vector<std::thread> threads2;
	threads2.push_back(std::thread(GoThroughAllAnnoyers, thrd));
	Sleep(2000);
	
	//Rest Of The Code...
	//...
	//...
	//Joining Threads...
	
	for (auto& thread : threads2) {
		thread.join();
	}
	
	//Rest Of The Code...
}
```

### Using Unhooker

```
void SomeFunction()
{

	std::vector<const wchar_t*> dllsToUnhook
	{
		StringKrypt(L"ntdll.dll"),	<-------  Or Any Other System DLL Files.
		StringKrypt(L"kernel32.dll")	<--------
	};


	for (auto dll : dllsToUnhook)
	{
		UnhookDll(dll);
	}
	
	//Rest Of The Code...
}
```

### Using CRC Check
Follow The Below Steps To Get It Done.

1. Right Click On Your Project In Visual Studio, Select `Properties > Linker > General > Enable Incremental Linking` And Set It To `No`.

2. Choose Any Function That You Intend To Apply CRC Check On It. You Cannot Choose Main Function Though.

3. Insert The Following Code Right At The End Of That Function Block.
```
VOID DebuggeeFunctionEnd()
{
};
```

4. Navigate To The `void StopFunction()` Which Is located At The End of The `CommonIncludes.hpp` File. 

5. Replace `xxxxxxx` In `DWORD crc = CalcFuncCrc((PUCHAR)xxxxxxx, (PUCHAR)DebuggeeFunctionEnd);` With The Name Of The Function That You Are Intending To Protect.

6. Uncomment The `std::cout << "Here is my CRC: " << crc << std::endl;` Statement In The Same `StopFunction()`. Run The Program And Convert The Printed CRC To Hex.

7. Navigate To The Top Of The `CommonIncludes.hpp` File, Replace `0000` in `DWORD g_origCrc = 0x0000;` With Your Hexadecimal CRC And Comment The Above Line Again.

___In Order To Make The CRC Check More Effective, You Have To Run It Through A Parallel Thread Which Has Been Explained Already.___


## Credits

https://github.com/Barracudach

https://www.codeproject.com/script/Membership/View.aspx?mid=11520486

