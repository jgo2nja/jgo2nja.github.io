	;; Creator: James O'Connell jgo2nja
	;; Last Updated: 14 April 2022



	global binarySearch



	section .text


binarySearch:
	;; r10 is used to store the mid value
	xor	r10, r10
	;; if the front and end are not in order, the target is a failure
	cmp	rsi, rdx
	jg	fail

	;; find mid value and store it in r10
	mov     r10, rsi
	add	r10, rdx

	shr	r10, 1
	;; use 32 bit register for int comparison
	;; index in 4 byte increments for 32 bit integers
	mov	ebx, [rdi+4*r10]
	cmp	ebx, ecx
	;; branch if statements
	jl	smaller
	jg	bigger
	je	success
	
smaller:
	;; change the low value
	mov	rsi, r10
	inc	rsi
	jmp	binarySearch

bigger:	
	;; change the high value
	mov	rdx, r10	
	dec	rdx
	jmp	binarySearch

success:
	;; upon success, return index
	mov	rax, r10
	ret

fail:
	;; return sentinel value
	mov	rax, -1
	ret
