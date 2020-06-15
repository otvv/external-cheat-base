//
// external driver
// project started - 07/05/2020
//

#pragma once

#include <ntifs.h>
#include <windef.h>

#define printf(...) DbgPrintEx(DPFLTR_SYSTEM_ID, DPFLTR_ERROR_LEVEL, __VA_ARGS__);

NTSTATUS DriverEntry(PDRIVER_OBJECT _driver_object, PUNICODE_STRING _registry_path);
NTSTATUS DriverExit(PDRIVER_OBJECT _driver_object);
