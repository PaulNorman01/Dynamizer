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
&emsp;EventCtrlFunction();
	handleException();
	StopHardwareDebugger(thrd);
	AntiStep();
}
```
