#include <Uefi.h>
#include <Library/UefiLib.h>

EFI_STATUS
EFIAPI
PrintAppMain (
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    Print(L"A new UEFI has been loaded!! ;)\n");
    
    return EFI_SUCCESS;
}
