//
// external driver
// project started - 07/05/2020
//

#include <ntifs.h>
#include <windef.h>
#include <ntstrsafe.h>

#define printf(...) DbgPrintEx(DPFLTR_SYSTEM_ID, DPFLTR_ERROR_LEVEL, __VA_ARGS__);

UNICODE_STRING g_Dev = { 0 };
UNICODE_STRING g_Sym = { 0 };
PDEVICE_OBJECT g_Device = NULL;

NTSTATUS IoCreate(PDEVICE_OBJECT _device_object, PIRP _irp)
{
	// fix for unreferenced parameter
	UNREFERENCED_PARAMETER(_device_object);

	_irp->IoStatus.Status = STATUS_SUCCESS;
	_irp->IoStatus.Information = 0;

	// finish request
	IoCompleteRequest(_irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}

NTSTATUS IoClose(PDEVICE_OBJECT _device_object, PIRP _irp)
{
	// fix for unreferenced parameter
	UNREFERENCED_PARAMETER(_device_object);

	_irp->IoStatus.Status = STATUS_SUCCESS;
	_irp->IoStatus.Information = 0;

	// finish request
	IoCompleteRequest(_irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}

NTSTATUS IoControl(PDEVICE_OBJECT _device_object, PIRP _irp)
{
	NTSTATUS ntStatus = STATUS_SUCCESS;
	
	// get rid of these
	UNREFERENCED_PARAMETER(_device_object);
	UNREFERENCED_PARAMETER(_irp); 

	_irp->IoStatus.Status = ntStatus;
	_irp->IoStatus.Information = 0;

	// finish request
	IoCompleteRequest(_irp, IO_NO_INCREMENT);

	return ntStatus;
}

NTSTATUS DriverExit(PDRIVER_OBJECT _driver_object)
{
	printf("[external driver] - unloading driver..")

	// delete symbolic link
	IoDeleteSymbolicLink(&g_Sym);

	// delete driver object
	IoDeleteDevice(_driver_object->DeviceObject);

	printf("[external driver] - driver unloaded.")

	return STATUS_SUCCESS;
}

NTSTATUS DriverEntry(PDRIVER_OBJECT _driver_object, PUNICODE_STRING _registry_path)
{
	printf("[external driver] - loading driver..");

	// lets name our driver
	RtlInitUnicodeString(&g_Dev, L"\\Device\\USBDriverExternal"); // TODO: figure out a name for this? maybe make a random string each time the user compiles this
	RtlInitUnicodeString(&g_Sym, L"\\DosDevices\\USBDriverExternal"); // needs to be the same name as the above

	// create driver object
	IoCreateDevice(_driver_object, 0, &g_Dev, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &g_Device);

	// create symbolic link
	IoCreateUnprotectedSymbolicLink(&g_Sym, &g_Dev);

	// set driver "callbacks" (routines)
	_driver_object->MajorFunction[IRP_MJ_CREATE] = IoCreate;
	_driver_object->MajorFunction[IRP_MJ_CLOSE] = IoClose;
	_driver_object->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IoControl;
	_driver_object->DriverUnload = DriverExit;

	// debug purposes only
	printf("[external driver] - object created.")

	// set some flags
	g_Device->Flags |= DO_DIRECT_IO;
	g_Device->Flags &= ~DO_DEVICE_INITIALIZING;

	// debug purposes only
	printf("[external driver] - driver loaded.")

	// fix for unreferenced parameter
	UNREFERENCED_PARAMETER(_registry_path);

	return STATUS_SUCCESS;
}