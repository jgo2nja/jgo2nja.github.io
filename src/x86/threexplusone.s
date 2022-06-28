	;; James O'Connell jgo2nja
	;; Last Updated: 12 April 2022
	;; Optimization listed at their locations in code

	global threexplusone


	section .text

	
threexplusone:
	;; clear r10
	xor	r10, r10

collatz:
	;; Subroutine will terminatate when the result is one, or when the iterations are complete
	cmp	r10, rsi
	je	done
	cmp	rdi, 1
	je	done
	;; Perform division to check odd/even
	mov     eax, edi
	xor     rdx, rdx
	mov	rbx, 2
	idiv	rbx
	;; Check the remainder
	cmp	rdx, 0
	je	even
	jmp	odd


even:
	;; Optimization 1: Use bit shift instead of division
	;; Divide the even number by two
	shr	rdi, 1
	inc	r10
	;; Call the subroutine
	call	collatz
	;; Return
	jmp	done

odd:
	;; Optimization 2: Use bit shifts and addition instead of multiplication
	;; Multiply the odd number by 3, then add 1
	mov	r11, rdi
	shl	rdi, 1
	add     rdi, r11
	inc     rdi
	xor	r11, r11
	inc	r10
	;; Call the subroutine
	call	collatz
	;; Return
	jmp	done
	
done:
	;; Move ouput to appropriate register
	mov	rax, r10
	ret	
