LIBRARY Buttons;
{!INFO
MODULENAME = 'Buttons'
VERSION = '1'
AUTHOR = 'Master Of Puppets'
DESCRIPTION = 'DLL ��� ���������� ����� ������ � ����� 3'
}

USES
	Windows,
	Era in '..\..\Era\Era.pas';

CONST
(* HookCode constants *)
C_HOOKTYPE_JUMP = FALSE;
C_HOOKTYPE_CALL = TRUE;
C_OPCODE_JUMP = $E9;
C_OPCODE_CALL = $E8;
C_UNIHOOK_SIZE = 5;
C_MOP_DLLNAME = 'Buttons.dll';

(* ������� *)
C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER = $77D3D7; //������� ��������������� ������ � ����� (Address: STRING); CDECL;


VAR
	hButtons:              Windows.THandle; // ���������� ����������
	Temp:                  INTEGER; //������������� ��������� ����������
	Counter:               INTEGER; //������� � ������
	PointerOfButtonsTable: INTEGER; //������������ ��� �������� ��������� �� ����������� ���������
	NumberOfStrings:       INTEGER;


EXPORTS
  PointerOfButtonsTable NAME 'ButtonsTable',
  NumberOfStrings       NAME 'NumButtons';


PROCEDURE ADVBUTTONS; ASSEMBLER;
ASM
	MOV EAX, [EDI+$50]
  	LEA ECX, [EDI+$48]
  	LEA EDX, [EBP-$20]
  	MOV BYTE [EBP-4], 0
  	PUSH EDX
  	PUSH 1
  	PUSH EAX
  	MOV DWORD [EBP-$20], $12
	MOV EAX, $404230
	CALL EAX
	PUSHAD
	MOV DWORD [Counter], 0 //������� ����� ������
@@LoopButtons:
  CMP NumberOfStrings, 0
  JE @@End
	MOV ECX, [PointerOfButtonsTable]
	MOV EAX, [Counter]
	MOV ECX, [ECX+EAX]

	PUSH DWORD [ECX] //������ �������. ��� ������� ���������� - ���������� �� 4
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	TEST EAX, EAX //�������� �� ������ ����� �����������
	JNZ @@NoAdvMap
	LEA ECX, [EBP-$20]
	PUSH ECX
	PUSH 1
	PUSH DWORD [ESI+08]
	MOV ECX, ESI
	MOV [EBP-$20], EDI
	MOV EAX, $5FE2D0
	CALL EAX
	PUSH $68
	MOV EAX, $617492
	CALL EAX
	ADD ESP, 4
	MOV [EBP-$20], EAX
	MOV BYTE [EBP-4], $0
	PUSH 2
	PUSH EBX
	PUSH EBX
	PUSH 1
	PUSH EBX
	MOV [Temp], EAX
//��� ������
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+8]
//ID
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+4]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	PUSH EAX
//Y-size
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+24]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	PUSH EAX
//X-size
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+20]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	PUSH EAX
//Y-position
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+16]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	PUSH EAX
//X-position
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+12]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	PUSH EAX
	MOV ECX, [Temp]
	MOV EAX, $455BD0
	CALL EAX
	MOV EDI, EAX
//������� �������
	MOV ECX, [PointerOfButtonsTable]
	MOV EAX, [Counter]
	MOV ECX, [ECX+EAX]

	PUSH DWORD [ECX+36]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	MOV DWORD [EBP-$20], EAX
	LEA ECX, [EDI+$48]
	LEA EDX, [EBP-$20]
	MOV BYTE [EBP-4], $0
	PUSH EDX
	PUSH 1
	PUSH DWORD [EDI+$50]
	MOV EAX, $404230
	CALL EAX
@@NoAdvMap:
	ADD DWORD [Counter], 4
  PUSH EAX
  MOV EAX, NumberOfStrings
  SHL EAX, 2
	CMP DWORD [Counter], EAX
  POP EAX
	JL @@LoopButtons
@@End:
	MOV [Temp], EDI
	POPAD
	MOV EDI, [Temp]
	PUSH $401B2A
END; // .PROCEDURE ADVBUTTONS

PROCEDURE ADVBUTTONS_HINTS_1; ASSEMBLER;
ASM
	PUSHAD
	MOV EDI, EAX
	MOV [Counter], 0
@@LoopButtons:
  CMP NumberOfStrings, 0
  JE @@End
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	TEST EAX, EAX //�������� �� ������ ����� �����������
	JNZ @@Inc
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+4]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	CMP EAX, EDI //�������� �� ��� �� ID
	JNZ @@Inc
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	MOV ECX, [ECX+32]
	MOV [Temp], ECX
	POPAD
	MOV EBX, [Temp]
	PUSH $40319B
	RET
@@Inc:
	ADD DWORD [Counter], 4
	PUSH EAX
  MOV EAX, NumberOfStrings
  SHL EAX, 2
	CMP DWORD [Counter], EAX
  POP EAX
	JL @@LoopButtons
@@End:
	POPAD
	CMP EAX, $2B
	JG @@default
	PUSH $40307A
	RET
@@default:
	PUSH $40317A
END; // .ADVBUTTONS_HINTS_1

PROCEDURE ADVBUTTONS_HINTS_2; ASSEMBLER;
ASM
	MOV EAX, [EBX+8]
	LEA ECX, [EAX-$F]
	PUSHAD
	MOV EDI, EAX
	MOV DWORD [Counter], 0
@@LoopButtons:
  CMP NumberOfStrings, 0
  JE @@End
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	TEST EAX, EAX //�������� �� ������ ����� �����������
	JNZ @@Inc
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+4]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	CMP EAX, EDI //�������� �� ��� �� ID
	JNZ @@Inc
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	MOV ECX, [ECX+28]
	MOV [Temp], ECX
	POPAD
	MOV ESI, [Temp]
	PUSH $402F87
	RET
@@Inc:
	ADD DWORD [Counter], 4
	PUSH EAX
  MOV EAX, NumberOfStrings
  SHL EAX, 2
	CMP DWORD [Counter], EAX
  POP EAX
	JL @@LoopButtons
@@End:
	POPAD
	PUSH $402E8F
END; // .ADVBUTTONS_HINTS_2

PROCEDURE ADVBUTTONS_PlayersColors; ASSEMBLER;
ASM
	PUSHAD
	MOV DWORD [Counter], 0
@@LoopButtons:
  CMP NumberOfStrings, 0
  JE @@End
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	TEST EAX, EAX
	JNZ @@INC
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+4]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	PUSH EAX
	MOV EAX, [$6992B8]
	MOV ECX, [EAX+$44]
	MOV EAX, $5FF5B0
	CALL EAX
	TEST EAX,EAX
	JE @@INC
	PUSH ESI
	MOV ECX,EAX
	MOV EAX, $4566C0
	CALL EAX
@@INC:
	ADD DWORD [Counter], 4
	PUSH EAX
  MOV EAX, NumberOfStrings
  SHL EAX, 2
	CMP DWORD [Counter], EAX
  POP EAX
	JL @@LoopButtons
@@End:
	POPAD
	MOV AL, [EBP+8]
	TEST AL, AL
	PUSH $40408D
END; // .ADVBUTTONS_PlayersColors

PROCEDURE TOWNBUTTONS; ASSEMBLER;
ASM
	MOV [Temp], EAX
	PUSHAD
	MOV DWORD [Counter], 0
@@LoopButtons:
  CMP NumberOfStrings, 0
  JE @@End
	PUSHAD
	MOV ECX, [PointerOfButtonsTable]
	MOV EAX, [Counter]
	MOV ECX, [ECX+EAX]

	PUSH DWORD [ECX]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	CMP EAX, 1
	POPAD
	JNZ @@INC
	LEA ECX, [EBP-$24]
	MOV [EBP-4], BL
	PUSH ECX
	MOV ECX, ESI
	MOV [EBP-$24],EAX
	MOV EAX, $54C900
	CALL EAX
	PUSH $68
	MOV EAX, $617492
	CALL EAX
	ADD ESP,4
	MOV [EBP-$24],EAX
	MOV BYTE [EBP-$4], $42
	PUSH 2
	PUSH 0
	PUSH 0
	PUSH 1
	PUSH 0
	MOV EDI, EAX
//��� ������
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+8]
//ID
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+4]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	PUSH EAX
//Y-size
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+24]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	PUSH EAX
//X-size
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+20]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	PUSH EAX
//Y-position
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+16]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	PUSH EAX
//X-position
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+12]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	PUSH EAX
	MOV ECX, EDI
	MOV EAX, $455BD0
	CALL EAX
	MOV [Temp], EAX
@@INC:
	ADD DWORD [Counter], 4
	PUSH EAX
  MOV EAX, NumberOfStrings
  SHL EAX, 2
	CMP DWORD [Counter], EAX
  POP EAX
	JL @@LoopButtons
@@End:
	POPAD
	MOV EAX, [Temp]
	MOV [EBP-$24],EAX
	LEA EAX, [EBP-$24]
	PUSH $5C5C49
END; // .TOWNBUTTONS

PROCEDURE TOWNBUTTONS_HINTS_1; ASSEMBLER;
ASM
	MOV EDX,-2
	PUSHAD
	MOV DWORD [Counter], 0
@@LoopButtons:
  CMP NumberOfStrings, 0
  JE @@End
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	CMP EAX, 1 //�������� �� ������ ������
	JNZ @@Inc
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+4]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	CMP EAX, EDI //�������� �� ��� �� ID
	JNZ @@Inc
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	MOV ECX, [ECX+32]
	MOV [Temp], ECX
	POPAD
	MOV EDI, [Temp]
	LEA EDX, [EBX+$144]
	PUSH $5C82B8
	RET
@@Inc:
	ADD DWORD [Counter], 4
	PUSH EAX
  MOV EAX, NumberOfStrings
  SHL EAX, 2
	CMP DWORD [Counter], EAX
  POP EAX
	JL @@LoopButtons
@@End:
	POPAD
	PUSH $5C7C08
END; // .TOWNBUTTONS_HINTS_1

PROCEDURE TOWNBUTTONS_HINTS_2; ASSEMBLER;
ASM
	PUSHAD
	MOV DWORD [Counter], 0
@@LoopButtons:
  CMP NumberOfStrings, 0
  JE @@End
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	CMP EAX, 1 //�������� �� ������ ������
	JNZ @@Inc
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+4]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	CMP EAX, EDI //�������� �� ��� �� ID
	JNZ @@Inc
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	MOV ECX, [ECX+28]
	MOV [Temp], ECX
	POPAD
	PUSH 0
	CMP BYTE [EBP+$3C],$0E
	JNZ @@LeftClick
	PUSH 4
	JMP @@RightClick
@@LeftClick:
	PUSH 1
@@RightClick:
	PUSH DWORD [Temp]
	MOV EAX, $70FB63
	CALL EAX
	ADD ESP, $0C
	PUSH $5D4617
	RET
@@Inc:
	ADD DWORD [Counter], 4
	PUSH EAX
  MOV EAX, NumberOfStrings
  SHL EAX, 2
	CMP DWORD [Counter], EAX
  POP EAX
	JL @@LoopButtons
@@End:
	POPAD
	MOV EAX, $70C198
	CALL EAX
	PUSH $5D38B2
END; // .TOWNBUTTONS_HINTS_2

PROCEDURE HEROSCREENBUTTONS; ASSEMBLER;
ASM
  MOV [Temp], EAX
	PUSHAD
	MOV DWORD [Counter], 0
@@LoopButtons:
  CMP NumberOfStrings, 0
  JE @@End
	PUSHAD
	MOV ECX, [PointerOfButtonsTable]
	MOV EAX, [Counter]
	MOV ECX, [ECX+EAX]

	PUSH DWORD [ECX]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	CMP EAX, 2 //�������� �� ������ �����
	POPAD
	JNZ @@INC
	LEA ECX, [EBP-$20]
	MOV [EBP-4], BL
	PUSH ECX
	MOV ECX, ESI
	MOV [EBP-$20],EAX
	MOV EAX, $54C900
	CALL EAX
	PUSH $68
	MOV EAX, $617492
	CALL EAX
	ADD ESP,4
	MOV [EBP-$1C],EAX
	MOV BYTE [EBP-$4], $84
	PUSH 2
	PUSH $20
	PUSH 0
	PUSH 1
	PUSH 0
	MOV EDI, EAX
//��� ������
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+8]
//ID
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+4]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	PUSH EAX
//Y-size
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+24]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	PUSH EAX
//X-size
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+20]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	PUSH EAX
//Y-position
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+16]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	PUSH EAX
//X-position
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+12]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	PUSH EAX
	MOV ECX, EDI
	MOV EAX, $455BD0
	CALL EAX
	MOV [Temp], EAX
@@INC:
	ADD DWORD [Counter], 4
	PUSH EAX
  MOV EAX, NumberOfStrings
  SHL EAX, 2
	CMP DWORD [Counter], EAX
  POP EAX
	JL @@LoopButtons
@@End:
	POPAD
	MOV EAX, [Temp]
  	LEA ECX, [EBP-$20]
  	MOV [EBP-4], BL
	PUSH $4DF7B8
END; // .HEROSCREENBUTTONS

PROCEDURE HEROSCREENBUTTONS_HINTS_1; ASSEMBLER;
ASM
	PUSH ESI
	MOV EAX, [EAX+8]
	PUSH EDI
	PUSHAD
	MOV DWORD [Counter], 0
	MOV EDI, EAX
@@LoopButtons:
  CMP NumberOfStrings, 0
  JE @@End
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	CMP EAX, 2 //�������� �� ������ �����
	JNZ @@Inc
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+4]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	CMP EAX, EDI //�������� �� ��� �� ID
	JNZ @@Inc
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	MOV ECX, [ECX+32]
	MOV [Temp], ECX
	POPAD
	MOV EDI, [Temp]
	PUSH $4DBEC0
	RET
@@Inc:
	ADD DWORD [Counter], 4
	PUSH EAX
  MOV EAX, NumberOfStrings
  SHL EAX, 2
	CMP DWORD [Counter], EAX
  POP EAX
	JL @@LoopButtons
@@End:
	POPAD
	PUSH $4DB8F2
END; // .HEROSCREENBUTTONS_HINTS_1

PROCEDURE HEROSCREENBUTTONS_HINTS_2; ASSEMBLER;
ASM
	MOV EAX, [ESI+8]
  	LEA ECX, [EAX-2]
	TEST BL,BL
	JE @@NOClick
	PUSHAD
	MOV EDI, EAX
	MOV DWORD [Counter], 0
@@LoopButtons:
  CMP NumberOfStrings, 0
  JE @@End
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	CMP EAX, 2 //�������� �� ������ ������ �����
	JNZ @@Inc
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+4]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	CMP EAX, EDI //�������� �� ��� �� ID
	JNZ @@Inc
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	MOV ECX, [ECX+28]
	MOV [Temp], ECX
	POPAD
	PUSH 0
	PUSH -1
	MOV ECX, [Temp]
	PUSH $4DE689
	RET
@@Inc:
	ADD DWORD [Counter], 4
	PUSH EAX
  MOV EAX, NumberOfStrings
  SHL EAX, 2
	CMP DWORD [Counter], EAX
  POP EAX
	JL @@LoopButtons
@@End:
	POPAD
@@NOClick:
	PUSH $4DD83F
END; // .HEROSCREENBUTTONS_HINTS_2


PROCEDURE HEROMETTINGSCREENBUTTONS; ASSEMBLER;
ASM
  MOV Temp, EAX
	PUSHAD
	MOV DWORD [Counter], 0
@@LoopButtons:
  CMP NumberOfStrings, 0
  JE @@End
	PUSHAD
	MOV ECX, [PointerOfButtonsTable]
	MOV EAX, [Counter]
	MOV ECX, [ECX+EAX]

	PUSH DWORD [ECX]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	CMP EAX, 3 //�������� �� ������ ������ ������
	POPAD
	JNZ @@INC
	LEA ECX, [EBP+8]
	MOV [EBP-4], BL
	MOV [EBP+8], EAX
	PUSH ECX
	PUSH 1
	PUSH DWORD [ESI+8]
	MOV ECX, ESI
	MOV EAX, $5FE2D0
	CALL EAX
	PUSH $68
	MOV EAX, $617492
	CALL EAX
	ADD ESP,4
	MOV [EBP-$20],EAX
	MOV BYTE [EBP-$4], $A0
	PUSH EDI
	PUSH EBX
	PUSH EBX
	PUSH 1
	PUSH EBX
	MOV EDI, EAX
//��� ������
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+8]
//ID
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+4]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	PUSH EAX
//Y-size
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+24]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	PUSH EAX
//X-size
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+20]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	PUSH EAX
//Y-position
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+16]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	PUSH EAX
//X-position
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+12]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	PUSH EAX
	MOV ECX, EDI
	MOV EAX, $455BD0
	CALL EAX
	MOV [Temp], EAX
@@INC:
	ADD DWORD [Counter], 4
	PUSH EAX
  MOV EAX, NumberOfStrings
  SHL EAX, 2
	CMP DWORD [Counter], EAX
  POP EAX
	JL @@LoopButtons
@@End:
	POPAD
	MOV EAX, [Temp]
	LEA ECX, [EBP+8]
	MOV [EBP-4], BL
	PUSH $5AE054
END; // .HEROMETTINGSCREENBUTTONS

PROCEDURE HEROMETTINGSCREENBUTTONS_HINTS_1; ASSEMBLER;
ASM
	PUSHAD
	MOV DWORD [Counter], 0
	LEA EDI, [EAX+1]
@@LoopButtons:
  CMP NumberOfStrings, 0
  JE @@End
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	CMP EAX, 3 //�������� �� ������ ������ ������
	JNZ @@Inc
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+4]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	CMP EAX, EDI //�������� �� ��� �� ID
	JNZ @@Inc
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	MOV ECX, [ECX+32]
	MOV [Temp], ECX
	POPAD
	MOV EDI, [Temp]
	PUSH $5B0F20
	RET
@@Inc:
	ADD DWORD [Counter], 4
	PUSH EAX
  MOV EAX, NumberOfStrings
  SHL EAX, 2
	CMP DWORD [Counter], EAX
  POP EAX
	JL @@LoopButtons
@@End:
	POPAD
	CMP EAX,$D6
	PUSH $5B0BE4
END; // .HEROMETTINGSCREENBUTTONS_HINTS_1

PROCEDURE HEROMETTINGSCREENBUTTONS_HINTS_2; ASSEMBLER;
ASM
	PUSHAD
	INC ESI
	MOV DWORD [Counter], 0
@@LoopButtons:
  CMP NumberOfStrings, 0
  JE @@End
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	CMP EAX, 3 //�������� �� ������ ������ ������
	JNZ @@Inc
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+4]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	CMP EAX, ESI //�������� �� ��� �� ID
	JNZ @@Inc
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	MOV ECX, [ECX+28]
	MOV [Temp], ECX
	POPAD
	XOR ESI, ESI
	MOV ECX, [Temp]
 	MOV AL, [EBP-4]
	TEST AL,AL
	JNZ @@OK
	PUSH $5B091A
	RET
@@OK:
	PUSH 0
	PUSH -1
	PUSH $5B08E8
	RET
@@Inc:
	ADD DWORD [Counter], 4
	PUSH EAX
  MOV EAX, NumberOfStrings
  SHL EAX, 2
	CMP DWORD [Counter], EAX
  POP EAX
	JL @@LoopButtons
@@End:
	POPAD
	PUSH $5B091A
END; // .HEROMETTINGSCREENBUTTONS_HINTS_2

PROCEDURE HEROMETTINGSCREENBUTTONS_TRIGGER; ASSEMBLER;
ASM
 	MOV EAX, [EAX+8]
	PUSHAD
	MOV DWORD [$91DA3C],0
	MOV [$91DA38],EAX
	PUSH 66666
	MOV EAX, $74CE30
	CALL EAX
	ADD ESP,4
	POPAD
	CMP DWORD [$91DA3C], 1
	JNZ @@OK
	PUSH $5B165C
	RET
@@OK:
	CMP EAX, $65
	PUSH $5B13F2
END; // .HEROMETTINGSCREENBUTTONS_TRIGGER

PROCEDURE COMBATBUTTONS; ASSEMBLER;
ASM
	PUSHAD
//��� ��������� � ���������� ������
  	mov edx,[$6A6A14]
  	mov eax,[$6A6A10]
	PUSH 1
	PUSH EDX
	PUSH EAX
	MOV ECX, EBX
	MOV BYTE [EBP-4],0
	MOV EAX, $5FEE00
  	CALL EAX
	MOV EDX,[EBX+$50]
        LEA EDI,[EBX+$48]
  	LEA ECX,[EBP+$0C]
  	MOV DWORD [ebp+$0C],$20
	PUSH ECX
	PUSH 1
	PUSH EDX
	MOV ECX, EDI
	MOV EAX, $404230
	CALL EAX

  MOV ECX,[EDI+$8]
  LEA EAX,[EBP+$0C]
  PUSH EAX
  PUSH 1
  PUSH ECX
  MOV ECX,EDI
  MOV [EBP+$0C],$39
  MOV EAX, $404230
	CALL EAX

  MOV [Temp], EBX
	MOV DWORD [Counter], 0
@@LoopButtons:
  CMP NumberOfStrings, 0
  JE @@End
	MOV ECX, [PointerOfButtonsTable]
	MOV EAX, [Counter]
	MOV ECX, [ECX+EAX]

	PUSH DWORD [ECX]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	CMP EAX, 4 //�������� �� ������ �����
	JNZ @@INC

	MOV EAX,[ESI+8]
  	LEA ECX,[ebp+$0C]
	PUSH ECX
	PUSH 1
	PUSH EAX
	MOV ECX, ESI
	MOV [ebp+$0C],EBX
	MOV EAX, $5FE2D0
	CALL EAX
	PUSH $68
	MOV EAX, $617492
	CALL EAX
	ADD ESP, 4
	MOV [ebp+$0C],EAX
	MOV BYTE [EBP-4],0
	PUSH 2
	PUSH 0
	PUSH 0
	PUSH 1
	PUSH 0
	MOV EDI, EAX
//��� ������
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+8]
//ID
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+4]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	PUSH EAX
//Y-size
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+24]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	PUSH EAX
//X-size
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+20]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	PUSH EAX
//Y-position
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+16]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	PUSH EAX
//X-position
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+12]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	PUSH EAX
	MOV ECX, EDI
	MOV EAX, $455BD0
	CALL EAX
	MOV [Temp], EAX
	MOV EBX, EAX
//��������� ��� ���
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	MOV EDX, [ECX+28]
//��������� ��� ��������� ����
	MOV ECX, [PointerOfButtonsTable]
	MOV EAX, [Counter]
	MOV ECX, [ECX+EAX]

	MOV EAX, [ECX+32]
	MOV EAX, EAX
	PUSH 1
	PUSH EDX
	PUSH EAX
	MOV ECX, EBX
	MOV BYTE [EBP-4],0
	MOV EAX, $5FEE00
  	CALL EAX
//������� �������
	MOV EDX,[EBX+$50]
        LEA EDI,[EBX+$48]
  	LEA ECX,[EBP+$0C]
	PUSH ECX
	PUSH 1
	PUSH EDX
	MOV ECX, [PointerOfButtonsTable]
	MOV EAX, [Counter]
	MOV ECX, [ECX+EAX]

	PUSH DWORD [ECX+36]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	MOV DWORD [ebp+$0C],EAX
	MOV ECX, EDI
	MOV EAX, $404230
	CALL EAX
	MOV [Temp], EBX
@@INC:
	ADD DWORD [Counter], 4
	PUSH EAX
  MOV EAX, NumberOfStrings
  SHL EAX, 2
	CMP DWORD [Counter], EAX
  POP EAX
	JL @@LoopButtons
@@End:
	POPAD
	MOV EBX, [Temp]
	PUSH $46B63D //13
END; // .COMBATBUTTONS


PROCEDURE COMBATBUTTONS_HINTS_2; ASSEMBLER;
ASM
	MOV EAX,[EAX+8]
	PUSHAD
	MOV ESI, EAX
	MOV DWORD [Counter], 0
@@LoopButtons:
  CMP NumberOfStrings, 0
  JE @@End
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	CMP EAX, 4 //�������� �� ������ ������ �����
	JNZ @@Inc
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	PUSH DWORD [ECX+4]
	MOV EAX, C_FUNC_ZVS_CONVERTION_STRING_TO_INTEGER
	CALL EAX
	ADD ESP, 4
	CMP EAX, ESI //�������� �� ��� �� ID
	JNZ @@Inc
	MOV ECX, [PointerOfButtonsTable]
	MOV EDX, [Counter]
	MOV ECX, [ECX+EDX]

	MOV ECX, [ECX+28]
	MOV [Temp], ECX
	POPAD
	PUSH ESI
	MOV ESI, [Temp]
	PUSH $4725D2
	RET
@@Inc:
	ADD DWORD [Counter], 4
	PUSH EAX
  MOV EAX, NumberOfStrings
  SHL EAX, 2
	CMP DWORD [Counter], EAX
  POP EAX
	JL @@LoopButtons
@@End:
	POPAD
	TEST EAX, EAX
	PUSH $47259C
END; // .COMBATBUTTONS_HINTS_HINTS_2

procedure OnAfterWoG (Event: Era.PEvent); stdcall;
begin
	hButtons:=Windows.GetModuleHandle(C_MOP_DLLNAME);
	Windows.DisableThreadLibraryCalls(hButtons);
	Era.Hook(Ptr($401B0D), @ADVBUTTONS,                       nil, 0, Era.HOOKTYPE_JUMP); //��������� ������ ����� �����������
	Era.Hook(Ptr($403071), @ADVBUTTONS_HINTS_1,               nil, 0, Era.HOOKTYPE_JUMP); //��������� � ������� ����� ����������� ��� ��������� ����
	Era.Hook(Ptr($402E89), @ADVBUTTONS_HINTS_2,               nil, 0, Era.HOOKTYPE_JUMP); //��������� � ������� ����� ����������� ��� ���
	Era.Hook(Ptr($404088), @ADVBUTTONS_PlayersColors,         nil, 0, Era.HOOKTYPE_JUMP); //����������� ������ ����� ����������� � ����� ������
	Era.Hook(Ptr($5C5C43), @TOWNBUTTONS,                      nil, 0, Era.HOOKTYPE_JUMP); //��������� ������ ������
	Era.Hook(Ptr($5C7C03), @TOWNBUTTONS_HINTS_1,              nil, 0, Era.HOOKTYPE_JUMP); //��������� � ������� ������ ��� ��������� ����
	Era.Hook(Ptr($5D38AD), @TOWNBUTTONS_HINTS_2,              nil, 0, Era.HOOKTYPE_JUMP); //��������� � ������� ������ ��� ������
	Era.Hook(Ptr($4DF7B2), @HEROSCREENBUTTONS,                nil, 0, Era.HOOKTYPE_JUMP); //��������� ������ ������ �����
	Era.Hook(Ptr($4DB8ED), @HEROSCREENBUTTONS_HINTS_1,        nil, 0, Era.HOOKTYPE_JUMP); //��������� � ������ ����� ��� ��������� ����
	Era.Hook(Ptr($4DD839), @HEROSCREENBUTTONS_HINTS_2,        nil, 0, Era.HOOKTYPE_JUMP); //��������� � ������ ����� ��� ���
	Era.Hook(Ptr($5AE04E), @HEROMETTINGSCREENBUTTONS,         nil, 0, Era.HOOKTYPE_JUMP); //��������� ������ ������ ������ ������
	Era.Hook(Ptr($5B0BDF), @HEROMETTINGSCREENBUTTONS_HINTS_1, nil, 0, Era.HOOKTYPE_JUMP); //��������� � ������� ������ ������ ������ ��� ��������� ����
	Era.Hook(Ptr($5B0902), @HEROMETTINGSCREENBUTTONS_HINTS_2, nil, 0, Era.HOOKTYPE_JUMP); //��������� � ������� ������ ������ ��� ���
	Era.Hook(Ptr($46B608), @COMBATBUTTONS,                    nil, 0, Era.HOOKTYPE_JUMP); //������ �����
	Era.Hook(Ptr($472597), @COMBATBUTTONS_HINTS_2,            nil, 0, Era.HOOKTYPE_JUMP); //��������� � ������� ����� ��� ���
	//HookCode(POINTER($5B13EC), @HEROMETTINGSCREENBUTTONS_TRIGGER, C_HOOKTYPE_JUMP); //��������� �������� �� ������� ������ � ������ ������ ������: x1 - ����� ������� ������, x2 - ��������� ����������� �������: 1 - ��, ������ - ���
end;

BEGIN
	Era.RegisterHandler(OnAfterWoG, 'OnAfterWoG');
END.