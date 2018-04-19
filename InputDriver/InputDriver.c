#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>

#define BUFFER_SIZE 16

EFI_STATUS
ReadInputString(
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL *ConsoleIn,
    CHAR16 **StrBuff
)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_INPUT_KEY Key;
    UINTN Index, Count;
    *StrBuff = AllocateZeroPool(BUFFER_SIZE * sizeof(CHAR16));

    Index = 0;
    do {
        gBS->WaitForEvent(1, &ConsoleIn->WaitForKey, &Count);
        Status = ConsoleIn->ReadKeyStroke(ConsoleIn, &Key);

        Print(L"Status code: %d\n", Status);

        (*StrBuff)[Index] = Key.UnicodeChar;

        Print(L"String is = %s\n\n\r", *StrBuff);

    }while((*StrBuff)[Index++] != SCAN_F3 && Index < BUFFER_SIZE-1);
    (*StrBuff)[Index] = '\0';

    return Status;
}

EFI_STATUS
EFIAPI
InputDriverMain (
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    
    EFI_STATUS Status = EFI_SUCCESS;
    CHAR16 *StrBuffer = NULL;

    Print(L"Type something:\n\r");
    Status = ReadInputString(gST->ConIn, &StrBuffer);
    Print(L"Final String = %s\n\r", StrBuffer);

    return EFI_SUCCESS;
}
