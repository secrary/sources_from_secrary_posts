.code

NtClose  PROC
	mov r10, rcx;
	mov eax, 15;
	syscall;
	ret;
NtClose  ENDP

NtCreateFile PROC
	mov r10, rcx;
	mov eax, 85;
	syscall;
	ret;
NtCreateFile ENDP
 
END