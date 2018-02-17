#include <Windows.h>

typedef struct _LSA_UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR  Buffer;
} LSA_UNICODE_STRING, *PLSA_UNICODE_STRING, UNICODE_STRING, *PUNICODE_STRING;

typedef struct _OBJECT_ATTRIBUTES {
	ULONG           Length;
	HANDLE          RootDirectory;
	PUNICODE_STRING ObjectName;
	ULONG           Attributes;
	PVOID           SecurityDescriptor;
	PVOID           SecurityQualityOfService;
}  OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;

typedef struct _IO_STATUS_BLOCK {
	union {
		NTSTATUS Status;
		PVOID    Pointer;
	};
	ULONG_PTR Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

typedef NTSTATUS RtlInitUnicodeStringEx
(
	PUNICODE_STRING target,
	PCWSTR          source
);

extern "C" LONG __stdcall NtClose(
	_In_ HANDLE _Handle
);

extern "C" NTSTATUS __stdcall NtCreateFile(
	_Out_ PHANDLE FileHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_Out_ LPVOID IoStatusBlock,
	_In_opt_ PLARGE_INTEGER AllocationSize,
	_In_ ULONG FileAttributes,
	_In_ ULONG ShareAccess,
	_In_ ULONG CreateDisposition,
	_In_ ULONG CreateOptions,
	_In_reads_bytes_opt_(EaLength) PVOID EaBuffer,
	_In_ ULONG EaLength
);



int main() {
	
	RtlInitUnicodeStringEx* initUnicode = (RtlInitUnicodeStringEx*)GetProcAddress(GetModuleHandle(L"ntdll"), "RtlInitUnicodeStringEx");
	UNICODE_STRING un;
	initUnicode(&un, L"\\??\\C:\\file.txt");

	HANDLE hFile;
	OBJECT_ATTRIBUTES objA{};
	objA.Length = sizeof(OBJECT_ATTRIBUTES);
	objA.ObjectName = &un;
	_IO_STATUS_BLOCK IoStatusBlock{};
	auto status = NtCreateFile(&hFile, GENERIC_ALL, &objA, &IoStatusBlock, 0, 0, 0, CREATE_NEW, 0, 0, 0);

	NtClose(hFile);
}