Label0:
	MOV AH, a
	MOV AL, b
	MOV BH, c
	ADD AL, BH
	CMP AH, AL
	JGE Label1
	MOV AH, a
	MOV AL, c
	SUB AH, AL
	MOV a, AH
Label1:
	MOV AH, b
	MOV AL, c
	MUL AH, AL
	MOV c, AH
