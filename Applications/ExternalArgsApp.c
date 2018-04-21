#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/EfiShellParameters.h>
#include <Library/SortLib.h> 


UINTN LowerThanEquals(
    UINTN *x,
    UINTN *y
)
{
    return *x <= *y ? -1 : 1;
}

UINTN CharToInt(
    IN CHAR16 Char
)
{
    switch(Char)
    {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
    }
    
    return -1;
}

UINTN GetMax(
    IN UINTN *Vector,
    IN UINTN VectorSize
)
{
    UINTN Max = Vector[0];
    UINTN Index;
    
    for(Index=1; Index < VectorSize; Index++)
        Max = Vector[Index] > Max ? Vector[Index] : Max;
        
    return Max;
}

UINTN pow(
    IN UINTN Number,
    IN UINTN Exp
)
{
    if(Exp == 0)
        return 1;
    
    UINTN Value = 1;
    UINTN Index;
    for(Index=0; Index < Exp; Index++)
        Value *= Number;
    
    return Value;
}

UINTN GetNumberValue(
    IN CHAR16 *Number
)
{
    UINTN Size = StrLen(Number);
    UINTN Index;
    UINTN Value = 0;

    for(Index=0; Index < Size; Index++)
        Value += CharToInt(Number[Index]) * pow(10, Size-1-Index);
    
    return Value;
}

VOID PrintVector(
    IN UINTN *Vector,
    IN UINTN VectorSize
)
{
    UINTN Index;
    Print(L"v = (");
    for(Index=0; Index < VectorSize; Index++) 
        Print(L"%d, ", Vector[Index]);

    Print(L")\n\r");

    return;
}

EFI_STATUS
EFIAPI
ExternalArgsAppMain (
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_SHELL_PARAMETERS_PROTOCOL *EfiShellParametersProtocol = NULL;
    EFI_STATUS Status = gBS->OpenProtocol (
                                ImageHandle,
                                &gEfiShellParametersProtocolGuid,
                                (VOID **) &EfiShellParametersProtocol,
                                ImageHandle,
                                NULL,
                                EFI_OPEN_PROTOCOL_GET_PROTOCOL);

    UINTN Argc = EfiShellParametersProtocol->Argc;
    CHAR16 **Argv = EfiShellParametersProtocol->Argv;
    
    UINTN Numbers[Argc-1];
    UINTN Index;
    
    for(Index=1; Index < Argc; Index++)
        Numbers[Index-1] = GetNumberValue(Argv[Index]);

    PrintVector(Numbers, Argc-1);
    PerformQuickSort(Numbers, Argc-1, sizeof(UINTN), (SORT_COMPARE) LowerThanEquals);
    PrintVector(Numbers, Argc-1);

    UINTN sum = GetMax(Numbers, Argc-1) + Numbers[(UINTN) (Argc-1)/2];
    Print(L"max(v) + Md(v) = max(v) + v'(%d) = ", (UINTN) (Argc-1)/2);
    Print(L"%d + %d = %d\n\r", GetMax(Numbers, Argc-1), Numbers[(UINTN) (Argc-1)/2], sum);

    return Status;
}
