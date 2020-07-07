//
// external driver
// project started - 07/05/2020
//

#pragma warning (disable : 4100)

#include "driver.h"

NTSTATUS DriverEntry(PDRIVER_OBJECT _driver_object, PUNICODE_STRING _registry_path)
{
	UNREFERENCED_PARAMETER(_registry_path);

	printf("[external driver] - loading driver..");

	// function that will unload the driver
	_driver_object->DriverUnload = DriverExit;

	return STATUS_SUCCESS;
}

NTSTATUS DriverExit(PDRIVER_OBJECT _driver_object)
{
	UNREFERENCED_PARAMETER(_driver_object);

	printf("[external driver] - unloading driver..");

	return STATUS_SUCCESS;
}