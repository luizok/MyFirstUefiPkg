#include <Uefi.h>
#include <Library/UefiLib.h>

#define BUFFER_SIZE 256

EFI_STATUS
EFIAPI
InputDriverMain (
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    
    EFI_STATUS Status = EFI_SUCCESS;
    // EFI_SIMPLE_TEXT_INPUT_PROTOCOL *TextIn = SystemTable->ConIn;
    EFI_INPUT_KEY Key;

    Print(L"Type something:\n\r");

    Status = SystemTable->ConIn->Reset(SystemTable->ConIn, FALSE);
    if(EFI_ERROR(Status))
        return Status;

    while(TRUE) {
        WaitForSingleEvent();
    }

    Print(L"String ScanCode = 0x%x\n\r", Key.ScanCode);
    Print(L"String Unicode  = 0x%x\n\r", Key.UnicodeChar);

    return EFI_SUCCESS;
}