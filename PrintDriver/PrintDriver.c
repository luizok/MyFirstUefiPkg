#include <Uefi.h>
#include <Library/UefiLib.h>

EFI_STATUS
EFIAPI
MyDriverEntryPoint (
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE        *SystemTable
)
{
    Print(L"A new UEFI driver has been loaded!! ;)\n");
    
    return EFI_SUCCESS;
}
