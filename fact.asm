00 READ 99
01 READ 98
02	LOAD 99		; B1
03	JZ 12		; B2->A1	Check 0!
04	LOAD 97		; B3
05	JZ 16		; B4->C1	Check 97 = 0
06	SUB 98		; B5 		Acc--
07	JZ 14		; B6->A3	Check end
08	STORE 97	; B7
09	MUL 99		; B8
10	STORE 99	; B9
11	JUMP 04		; B10->B3
12	LOAD 98		; A1
13 	STORE 99	; A2
14	WRITE 99	; A3
15	HALT 00		; A4
16	LOAD 99		; C1
17	STORE 97	; C2
18	JUMP 06		; C3->B5