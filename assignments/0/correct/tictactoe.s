	.data
	.align	2
	.globl	class_nameTab
	.globl	Main_protObj
	.globl	Int_protObj
	.globl	String_protObj
	.globl	bool_const0
	.globl	bool_const1
	.globl	_int_tag
	.globl	_bool_tag
	.globl	_string_tag
_int_tag:
	.word	2
_bool_tag:
	.word	3
_string_tag:
	.word	4
	.globl	_MemMgr_INITIALIZER
_MemMgr_INITIALIZER:
	.word	_NoGC_Init
	.globl	_MemMgr_COLLECTOR
_MemMgr_COLLECTOR:
	.word	_NoGC_Collect
	.globl	_MemMgr_TEST
_MemMgr_TEST:
	.word	0
	.word	-1
str_const25:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const0
	.byte	0	
	.align	2
	.word	-1
str_const24:
	.word	4
	.word	6
	.word	String_dispTab
	.word	int_const6
	.ascii	"Main"
	.byte	0	
	.align	2
	.word	-1
str_const23:
	.word	4
	.word	6
	.word	String_dispTab
	.word	int_const6
	.ascii	"Game"
	.byte	0	
	.align	2
	.word	-1
str_const22:
	.word	4
	.word	7
	.word	String_dispTab
	.word	int_const4
	.ascii	"TTTBoard"
	.byte	0	
	.align	2
	.word	-1
str_const21:
	.word	4
	.word	6
	.word	String_dispTab
	.word	int_const7
	.ascii	"String"
	.byte	0	
	.align	2
	.word	-1
str_const20:
	.word	4
	.word	6
	.word	String_dispTab
	.word	int_const6
	.ascii	"Bool"
	.byte	0	
	.align	2
	.word	-1
str_const19:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const2
	.ascii	"Int"
	.byte	0	
	.align	2
	.word	-1
str_const18:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"IO"
	.byte	0	
	.align	2
	.word	-1
str_const17:
	.word	4
	.word	6
	.word	String_dispTab
	.word	int_const7
	.ascii	"Object"
	.byte	0	
	.align	2
	.word	-1
str_const16:
	.word	4
	.word	8
	.word	String_dispTab
	.word	int_const8
	.ascii	"<basic class>"
	.byte	0	
	.align	2
	.word	-1
str_const15:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const3
	.ascii	"y"
	.byte	0	
	.align	2
	.word	-1
str_const14:
	.word	4
	.word	23
	.word	String_dispTab
	.word	int_const9
	.ascii	"Do you want to play another game? (y for yes, any other input to exit): "
	.byte	0	
	.align	2
	.word	-1
str_const13:
	.word	4
	.word	8
	.word	String_dispTab
	.word	int_const10
	.ascii	" won the game.\n"
	.byte	0	
	.align	2
	.word	-1
str_const12:
	.word	4
	.word	10
	.word	String_dispTab
	.word	int_const11
	.ascii	"Game ended in a draw\n"
	.byte	0	
	.align	2
	.word	-1
str_const11:
	.word	4
	.word	9
	.word	String_dispTab
	.word	int_const12
	.ascii	"Already occupied. "
	.byte	0	
	.align	2
	.word	-1
str_const10:
	.word	4
	.word	12
	.word	String_dispTab
	.word	int_const13
	.ascii	"Invalid row or column number. "
	.byte	0	
	.align	2
	.word	-1
str_const9:
	.word	4
	.word	18
	.word	String_dispTab
	.word	int_const14
	.ascii	" enter the row and column number for the move(1-3):\n"
	.byte	0	
	.align	2
	.word	-1
str_const8:
	.word	4
	.word	6
	.word	String_dispTab
	.word	int_const15
	.ascii	"Player "
	.byte	0	
	.align	2
	.word	-1
str_const7:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const3
	.ascii	"O"
	.byte	0	
	.align	2
	.word	-1
str_const6:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const3
	.ascii	"X"
	.byte	0	
	.align	2
	.word	-1
str_const5:
	.word	4
	.word	8
	.word	String_dispTab
	.word	int_const16
	.ascii	"tictactoe.cl"
	.byte	0	
	.align	2
	.word	-1
str_const4:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const2
	.ascii	"||\n"
	.byte	0	
	.align	2
	.word	-1
str_const3:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const3
	.ascii	"+"
	.byte	0	
	.align	2
	.word	-1
str_const2:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const3
	.ascii	" "
	.byte	0	
	.align	2
	.word	-1
str_const1:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const3
	.ascii	"-"
	.byte	0	
	.align	2
	.word	-1
str_const0:
	.word	4
	.word	7
	.word	String_dispTab
	.word	int_const5
	.ascii	"         "
	.byte	0	
	.align	2
	.word	-1
int_const16:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	12
	.word	-1
int_const15:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	7
	.word	-1
int_const14:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	52
	.word	-1
int_const13:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	30
	.word	-1
int_const12:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	18
	.word	-1
int_const11:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	21
	.word	-1
int_const10:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	15
	.word	-1
int_const9:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	72
	.word	-1
int_const8:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	13
	.word	-1
int_const7:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	6
	.word	-1
int_const6:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	4
	.word	-1
int_const5:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	9
	.word	-1
int_const4:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	8
	.word	-1
int_const3:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	1
	.word	-1
int_const2:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	3
	.word	-1
int_const1:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	2
	.word	-1
int_const0:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	0
	.word	-1
bool_const0:
	.word	3
	.word	4
	.word	Bool_dispTab
	.word	0
	.word	-1
bool_const1:
	.word	3
	.word	4
	.word	Bool_dispTab
	.word	1
class_nameTab:
	.word	str_const17
	.word	str_const18
	.word	str_const19
	.word	str_const20
	.word	str_const21
	.word	str_const22
	.word	str_const23
	.word	str_const24
class_objTab:
	.word	Object_protObj
	.word	Object_init
	.word	IO_protObj
	.word	IO_init
	.word	Int_protObj
	.word	Int_init
	.word	Bool_protObj
	.word	Bool_init
	.word	String_protObj
	.word	String_init
	.word	TTTBoard_protObj
	.word	TTTBoard_init
	.word	Game_protObj
	.word	Game_init
	.word	Main_protObj
	.word	Main_init
Object_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
Main_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	Main.main
Game_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	Game.player_symbol
	.word	Game.new_game
	.word	Game.check_row
	.word	Game.check_column
	.word	Game.check_first_diagonal
	.word	Game.check_second_diagonal
	.word	Game.check
	.word	Game.start
TTTBoard_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	TTTBoard.init
	.word	TTTBoard.get
	.word	TTTBoard.set
	.word	TTTBoard.display
String_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	String.length
	.word	String.concat
	.word	String.substr
Bool_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
Int_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
IO_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	-1
Object_protObj:
	.word	0
	.word	3
	.word	Object_dispTab
	.word	-1
Main_protObj:
	.word	7
	.word	4
	.word	Main_dispTab
	.word	0
	.word	-1
Game_protObj:
	.word	6
	.word	9
	.word	Game_dispTab
	.word	0
	.word	0
	.word	bool_const0
	.word	int_const0
	.word	int_const0
	.word	str_const25
	.word	-1
TTTBoard_protObj:
	.word	5
	.word	4
	.word	TTTBoard_dispTab
	.word	str_const25
	.word	-1
String_protObj:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const0
	.word	0
	.word	-1
Bool_protObj:
	.word	3
	.word	4
	.word	Bool_dispTab
	.word	0
	.word	-1
Int_protObj:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	0
	.word	-1
IO_protObj:
	.word	1
	.word	3
	.word	IO_dispTab
	.globl	heap_start
heap_start:
	.word	0
	.text
	.globl	Main_init
	.globl	Int_init
	.globl	String_init
	.globl	Bool_init
	.globl	Main.main
Object_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Main_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Object_init
	la	$a0 Game_protObj
	jal	Object.copy
	jal	Game_init
	sw	$a0 12($s0)
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Game_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Object_init
	la	$a0 IO_protObj
	jal	Object.copy
	jal	IO_init
	sw	$a0 12($s0)
	la	$a0 TTTBoard_protObj
	jal	Object.copy
	jal	TTTBoard_init
	sw	$a0 16($s0)
	la	$a0 bool_const1
	sw	$a0 20($s0)
	la	$a0 int_const3
	sw	$a0 28($s0)
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
TTTBoard_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Object_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
String_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Object_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Bool_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Object_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Int_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Object_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
IO_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Object_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Main.main:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$a0 12($s0)
	bne	$a0 $zero label0
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label0:
	lw	$t1 8($a0)
	lw	$t1 40($t1)
	jalr		$t1
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Game.player_symbol:
	addiu	$sp $sp -16
	sw	$fp 16($sp)
	sw	$s0 12($sp)
	sw	$ra 8($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$s1 16($fp)
	la	$t2 int_const3
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label3
	la	$a1 bool_const0
	jal	equality_test
label3:
	lw	$t1 12($a0)
	beqz	$t1 label1
	la	$a0 str_const6
	b	label2
label1:
	la	$a0 str_const7
label2:
	lw	$fp 16($sp)
	lw	$s0 12($sp)
	lw	$ra 8($sp)
	addiu	$sp $sp 20
	jr	$ra	
Game.new_game:
	addiu	$sp $sp -44
	sw	$fp 44($sp)
	sw	$s0 40($sp)
	sw	$ra 36($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$a0 16($s0)
	bne	$a0 $zero label4
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label4:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	lw	$a0 28($s0)
	sw	$a0 24($s0)
	la	$s1 bool_const0
	la	$s2 int_const0
	la	$s3 int_const0
	la	$s4 int_const0
	la	$s5 bool_const0
label5:
	lw	$t1 12($s1)
	la	$a0 bool_const1
	beqz	$t1 label7
	la	$a0 bool_const0
label7:
	lw	$t1 12($a0)
	beq	$t1 $zero label6
	lw	$a0 12($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 16($s0)
	sw	$s1 0($fp)
	sw	$s2 4($fp)
	sw	$s3 8($fp)
	sw	$s4 12($fp)
	sw	$s5 16($fp)
	bne	$a0 $zero label8
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label8:
	lw	$t1 8($a0)
	lw	$t1 24($t1)
	jalr		$t1
	lw	$s1 0($fp)
	lw	$s2 4($fp)
	lw	$s3 8($fp)
	lw	$s4 12($fp)
	lw	$s5 16($fp)
	lw	$a0 24($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	sw	$s1 0($fp)
	sw	$s2 4($fp)
	sw	$s3 8($fp)
	sw	$s4 12($fp)
	sw	$s5 16($fp)
	bne	$a0 $zero label9
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label9:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	lw	$s1 0($fp)
	lw	$s2 4($fp)
	lw	$s3 8($fp)
	lw	$s4 12($fp)
	lw	$s5 16($fp)
	sw	$a0 32($s0)
	la	$s6 bool_const0
	la	$a0 str_const25
	sw	$a0 24($fp)
label10:
	lw	$t1 12($s6)
	la	$a0 bool_const1
	beqz	$t1 label12
	la	$a0 bool_const0
label12:
	lw	$t1 12($a0)
	beq	$t1 $zero label11
	la	$a0 str_const9
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 32($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const8
	sw	$s1 0($fp)
	sw	$s2 4($fp)
	sw	$s3 8($fp)
	sw	$s4 12($fp)
	sw	$s5 16($fp)
	sw	$s6 20($fp)
	bne	$a0 $zero label13
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label13:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	lw	$s1 0($fp)
	lw	$s2 4($fp)
	lw	$s3 8($fp)
	lw	$s4 12($fp)
	lw	$s5 16($fp)
	lw	$s6 20($fp)
	sw	$s1 0($fp)
	sw	$s2 4($fp)
	sw	$s3 8($fp)
	sw	$s4 12($fp)
	sw	$s5 16($fp)
	sw	$s6 20($fp)
	bne	$a0 $zero label14
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label14:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	lw	$s1 0($fp)
	lw	$s2 4($fp)
	lw	$s3 8($fp)
	lw	$s4 12($fp)
	lw	$s5 16($fp)
	lw	$s6 20($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($s0)
	sw	$s1 0($fp)
	sw	$s2 4($fp)
	sw	$s3 8($fp)
	sw	$s4 12($fp)
	sw	$s5 16($fp)
	sw	$s6 20($fp)
	bne	$a0 $zero label15
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label15:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	lw	$s1 0($fp)
	lw	$s2 4($fp)
	lw	$s3 8($fp)
	lw	$s4 12($fp)
	lw	$s5 16($fp)
	lw	$s6 20($fp)
	lw	$a0 12($s0)
	sw	$s1 0($fp)
	sw	$s2 4($fp)
	sw	$s3 8($fp)
	sw	$s4 12($fp)
	sw	$s5 16($fp)
	sw	$s6 20($fp)
	bne	$a0 $zero label16
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label16:
	lw	$t1 8($a0)
	lw	$t1 24($t1)
	jalr		$t1
	lw	$s1 0($fp)
	lw	$s2 4($fp)
	lw	$s3 8($fp)
	lw	$s4 12($fp)
	lw	$s5 16($fp)
	lw	$s6 20($fp)
	sw	$a0 28($fp)
	la	$a0 int_const3
	jal	Object.copy
	lw	$t1 28($fp)
	lw	$t2 12($a0)
	lw	$t1 12($t1)
	sub	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s3 $a0
	lw	$a0 12($s0)
	sw	$s1 0($fp)
	sw	$s2 4($fp)
	sw	$s3 8($fp)
	sw	$s4 12($fp)
	sw	$s5 16($fp)
	sw	$s6 20($fp)
	bne	$a0 $zero label17
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label17:
	lw	$t1 8($a0)
	lw	$t1 24($t1)
	jalr		$t1
	lw	$s1 0($fp)
	lw	$s2 4($fp)
	lw	$s3 8($fp)
	lw	$s4 12($fp)
	lw	$s5 16($fp)
	lw	$s6 20($fp)
	sw	$a0 28($fp)
	la	$a0 int_const3
	jal	Object.copy
	lw	$t1 28($fp)
	lw	$t2 12($a0)
	lw	$t1 12($t1)
	sub	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s4 $a0
	sw	$s3 0($sp)
	addiu	$sp $sp -4
	sw	$s4 0($sp)
	addiu	$sp $sp -4
	lw	$a0 32($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 16($s0)
	sw	$s1 0($fp)
	sw	$s2 4($fp)
	sw	$s3 8($fp)
	sw	$s4 12($fp)
	sw	$s5 16($fp)
	sw	$s6 20($fp)
	bne	$a0 $zero label18
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label18:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr		$t1
	lw	$s1 0($fp)
	lw	$s2 4($fp)
	lw	$s3 8($fp)
	lw	$s4 12($fp)
	lw	$s5 16($fp)
	lw	$s6 20($fp)
	sw	$a0 24($fp)
	lw	$a0 24($fp)
	sw	$a0 28($fp)
	la	$t2 str_const1
	lw	$t1 28($fp)
	la	$a0 bool_const1
	beq	$t1 $t2 label21
	la	$a1 bool_const0
	jal	equality_test
label21:
	lw	$t1 12($a0)
	beqz	$t1 label19
	la	$a0 str_const10
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($s0)
	sw	$s1 0($fp)
	sw	$s2 4($fp)
	sw	$s3 8($fp)
	sw	$s4 12($fp)
	sw	$s5 16($fp)
	sw	$s6 20($fp)
	bne	$a0 $zero label22
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label22:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	lw	$s1 0($fp)
	lw	$s2 4($fp)
	lw	$s3 8($fp)
	lw	$s4 12($fp)
	lw	$s5 16($fp)
	lw	$s6 20($fp)
	b	label20
label19:
	lw	$a0 24($fp)
	sw	$a0 28($fp)
	la	$t2 str_const3
	lw	$t1 28($fp)
	la	$a0 bool_const1
	beq	$t1 $t2 label25
	la	$a1 bool_const0
	jal	equality_test
label25:
	lw	$t1 12($a0)
	beqz	$t1 label23
	la	$a0 str_const11
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($s0)
	sw	$s1 0($fp)
	sw	$s2 4($fp)
	sw	$s3 8($fp)
	sw	$s4 12($fp)
	sw	$s5 16($fp)
	sw	$s6 20($fp)
	bne	$a0 $zero label26
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label26:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	lw	$s1 0($fp)
	lw	$s2 4($fp)
	lw	$s3 8($fp)
	lw	$s4 12($fp)
	lw	$s5 16($fp)
	lw	$s6 20($fp)
	b	label24
label23:
	la	$s6 bool_const1
	move	$a0 $s6
label24:
label20:
	b	label10
label11:
	move	$a0 $zero
	move	$s6 $s2
	la	$a0 int_const3
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s6)
	add	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s2 $a0
	sw	$s3 0($sp)
	addiu	$sp $sp -4
	sw	$s4 0($sp)
	addiu	$sp $sp -4
	lw	$a0 32($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	sw	$s1 0($fp)
	sw	$s2 4($fp)
	sw	$s3 8($fp)
	sw	$s4 12($fp)
	sw	$s5 16($fp)
	bne	$a0 $zero label27
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label27:
	lw	$t1 8($a0)
	lw	$t1 36($t1)
	jalr		$t1
	lw	$s1 0($fp)
	lw	$s2 4($fp)
	lw	$s3 8($fp)
	lw	$s4 12($fp)
	lw	$s5 16($fp)
	move	$s1 $a0
	lw	$t1 12($s1)
	la	$a0 bool_const1
	beqz	$t1 label30
	la	$a0 bool_const0
label30:
	lw	$t1 12($a0)
	beqz	$t1 label28
	move	$s6 $s2
	la	$t2 int_const5
	move	$t1 $s6
	la	$a0 bool_const1
	beq	$t1 $t2 label33
	la	$a1 bool_const0
	jal	equality_test
label33:
	lw	$t1 12($a0)
	beqz	$t1 label31
	la	$s5 bool_const1
	move	$s1 $s5
	move	$a0 $s5
	b	label32
label31:
	la	$a0 int_const0
label32:
	b	label29
label28:
	la	$a0 int_const0
label29:
	lw	$s6 24($s0)
	la	$a0 int_const3
	jal	Object.copy
	lw	$t1 12($a0)
	neg	$t1 $t1
	sw	$t1 12($a0)
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s6)
	mul	$t1 $t1 $t2
	sw	$t1 12($a0)
	sw	$a0 24($s0)
	b	label5
label6:
	move	$a0 $zero
	lw	$a0 12($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 16($s0)
	sw	$s1 0($fp)
	sw	$s2 4($fp)
	sw	$s3 8($fp)
	sw	$s4 12($fp)
	sw	$s5 16($fp)
	bne	$a0 $zero label34
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label34:
	lw	$t1 8($a0)
	lw	$t1 24($t1)
	jalr		$t1
	lw	$s1 0($fp)
	lw	$s2 4($fp)
	lw	$s3 8($fp)
	lw	$s4 12($fp)
	lw	$s5 16($fp)
	lw	$t1 12($s5)
	beqz	$t1 label35
	la	$a0 str_const12
	b	label36
label35:
	la	$a0 str_const13
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 32($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const8
	sw	$s1 0($fp)
	sw	$s2 4($fp)
	sw	$s3 8($fp)
	sw	$s4 12($fp)
	sw	$s5 16($fp)
	bne	$a0 $zero label37
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label37:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	lw	$s1 0($fp)
	lw	$s2 4($fp)
	lw	$s3 8($fp)
	lw	$s4 12($fp)
	lw	$s5 16($fp)
	sw	$s1 0($fp)
	sw	$s2 4($fp)
	sw	$s3 8($fp)
	sw	$s4 12($fp)
	sw	$s5 16($fp)
	bne	$a0 $zero label38
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label38:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	lw	$s1 0($fp)
	lw	$s2 4($fp)
	lw	$s3 8($fp)
	lw	$s4 12($fp)
	lw	$s5 16($fp)
label36:
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($s0)
	sw	$s1 0($fp)
	sw	$s2 4($fp)
	sw	$s3 8($fp)
	sw	$s4 12($fp)
	sw	$s5 16($fp)
	bne	$a0 $zero label39
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label39:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	lw	$s1 0($fp)
	lw	$s2 4($fp)
	lw	$s3 8($fp)
	lw	$s4 12($fp)
	lw	$s5 16($fp)
	lw	$fp 44($sp)
	lw	$s0 40($sp)
	lw	$ra 36($sp)
	addiu	$sp $sp 44
	jr	$ra	
Game.check_row:
	addiu	$sp $sp -16
	sw	$fp 16($sp)
	sw	$s0 12($sp)
	sw	$ra 8($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$a0 20($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 16($s0)
	bne	$a0 $zero label44
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label44:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	move	$s1 $a0
	lw	$t2 16($fp)
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label43
	la	$a1 bool_const0
	jal	equality_test
label43:
	lw	$t1 12($a0)
	la	$a0 bool_const1
	beqz	$t1 label42
	la	$a0 bool_const0
label42:
	lw	$t1 12($a0)
	beqz	$t1 label40
	la	$a0 bool_const0
	b	label41
label40:
	lw	$a0 20($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const3
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 16($s0)
	bne	$a0 $zero label49
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label49:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	move	$s1 $a0
	lw	$t2 16($fp)
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label48
	la	$a1 bool_const0
	jal	equality_test
label48:
	lw	$t1 12($a0)
	la	$a0 bool_const1
	beqz	$t1 label47
	la	$a0 bool_const0
label47:
	lw	$t1 12($a0)
	beqz	$t1 label45
	la	$a0 bool_const0
	b	label46
label45:
	lw	$a0 20($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 16($s0)
	bne	$a0 $zero label54
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label54:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	move	$s1 $a0
	lw	$t2 16($fp)
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label53
	la	$a1 bool_const0
	jal	equality_test
label53:
	lw	$t1 12($a0)
	la	$a0 bool_const1
	beqz	$t1 label52
	la	$a0 bool_const0
label52:
	lw	$t1 12($a0)
	beqz	$t1 label50
	la	$a0 bool_const0
	b	label51
label50:
	la	$a0 bool_const1
label51:
label46:
label41:
	lw	$fp 16($sp)
	lw	$s0 12($sp)
	lw	$ra 8($sp)
	addiu	$sp $sp 24
	jr	$ra	
Game.check_column:
	addiu	$sp $sp -16
	sw	$fp 16($sp)
	sw	$s0 12($sp)
	sw	$ra 8($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	la	$a0 int_const0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 20($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 16($s0)
	bne	$a0 $zero label59
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label59:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	move	$s1 $a0
	lw	$t2 16($fp)
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label58
	la	$a1 bool_const0
	jal	equality_test
label58:
	lw	$t1 12($a0)
	la	$a0 bool_const1
	beqz	$t1 label57
	la	$a0 bool_const0
label57:
	lw	$t1 12($a0)
	beqz	$t1 label55
	la	$a0 bool_const0
	b	label56
label55:
	la	$a0 int_const3
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 20($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 16($s0)
	bne	$a0 $zero label64
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label64:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	move	$s1 $a0
	lw	$t2 16($fp)
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label63
	la	$a1 bool_const0
	jal	equality_test
label63:
	lw	$t1 12($a0)
	la	$a0 bool_const1
	beqz	$t1 label62
	la	$a0 bool_const0
label62:
	lw	$t1 12($a0)
	beqz	$t1 label60
	la	$a0 bool_const0
	b	label61
label60:
	la	$a0 int_const1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 20($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 16($s0)
	bne	$a0 $zero label69
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label69:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	move	$s1 $a0
	lw	$t2 16($fp)
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label68
	la	$a1 bool_const0
	jal	equality_test
label68:
	lw	$t1 12($a0)
	la	$a0 bool_const1
	beqz	$t1 label67
	la	$a0 bool_const0
label67:
	lw	$t1 12($a0)
	beqz	$t1 label65
	la	$a0 bool_const0
	b	label66
label65:
	la	$a0 bool_const1
label66:
label61:
label56:
	lw	$fp 16($sp)
	lw	$s0 12($sp)
	lw	$ra 8($sp)
	addiu	$sp $sp 24
	jr	$ra	
Game.check_first_diagonal:
	addiu	$sp $sp -16
	sw	$fp 16($sp)
	sw	$s0 12($sp)
	sw	$ra 8($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	la	$a0 int_const0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 16($s0)
	bne	$a0 $zero label74
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label74:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	move	$s1 $a0
	lw	$t2 16($fp)
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label73
	la	$a1 bool_const0
	jal	equality_test
label73:
	lw	$t1 12($a0)
	la	$a0 bool_const1
	beqz	$t1 label72
	la	$a0 bool_const0
label72:
	lw	$t1 12($a0)
	beqz	$t1 label70
	la	$a0 bool_const0
	b	label71
label70:
	la	$a0 int_const3
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const3
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 16($s0)
	bne	$a0 $zero label79
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label79:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	move	$s1 $a0
	lw	$t2 16($fp)
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label78
	la	$a1 bool_const0
	jal	equality_test
label78:
	lw	$t1 12($a0)
	la	$a0 bool_const1
	beqz	$t1 label77
	la	$a0 bool_const0
label77:
	lw	$t1 12($a0)
	beqz	$t1 label75
	la	$a0 bool_const0
	b	label76
label75:
	la	$a0 int_const1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 16($s0)
	bne	$a0 $zero label84
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label84:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	move	$s1 $a0
	lw	$t2 16($fp)
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label83
	la	$a1 bool_const0
	jal	equality_test
label83:
	lw	$t1 12($a0)
	la	$a0 bool_const1
	beqz	$t1 label82
	la	$a0 bool_const0
label82:
	lw	$t1 12($a0)
	beqz	$t1 label80
	la	$a0 bool_const0
	b	label81
label80:
	la	$a0 bool_const1
label81:
label76:
label71:
	lw	$fp 16($sp)
	lw	$s0 12($sp)
	lw	$ra 8($sp)
	addiu	$sp $sp 20
	jr	$ra	
Game.check_second_diagonal:
	addiu	$sp $sp -16
	sw	$fp 16($sp)
	sw	$s0 12($sp)
	sw	$ra 8($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	la	$a0 int_const0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 16($s0)
	bne	$a0 $zero label89
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label89:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	move	$s1 $a0
	lw	$t2 16($fp)
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label88
	la	$a1 bool_const0
	jal	equality_test
label88:
	lw	$t1 12($a0)
	la	$a0 bool_const1
	beqz	$t1 label87
	la	$a0 bool_const0
label87:
	lw	$t1 12($a0)
	beqz	$t1 label85
	la	$a0 bool_const0
	b	label86
label85:
	la	$a0 int_const3
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const3
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 16($s0)
	bne	$a0 $zero label94
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label94:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	move	$s1 $a0
	lw	$t2 16($fp)
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label93
	la	$a1 bool_const0
	jal	equality_test
label93:
	lw	$t1 12($a0)
	la	$a0 bool_const1
	beqz	$t1 label92
	la	$a0 bool_const0
label92:
	lw	$t1 12($a0)
	beqz	$t1 label90
	la	$a0 bool_const0
	b	label91
label90:
	la	$a0 int_const1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 16($s0)
	bne	$a0 $zero label99
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label99:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	move	$s1 $a0
	lw	$t2 16($fp)
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label98
	la	$a1 bool_const0
	jal	equality_test
label98:
	lw	$t1 12($a0)
	la	$a0 bool_const1
	beqz	$t1 label97
	la	$a0 bool_const0
label97:
	lw	$t1 12($a0)
	beqz	$t1 label95
	la	$a0 bool_const0
	b	label96
label95:
	la	$a0 bool_const1
label96:
label91:
label86:
	lw	$fp 16($sp)
	lw	$s0 12($sp)
	lw	$ra 8($sp)
	addiu	$sp $sp 20
	jr	$ra	
Game.check:
	addiu	$sp $sp -24
	sw	$fp 24($sp)
	sw	$s0 20($sp)
	sw	$ra 16($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	la	$s1 bool_const0
	la	$s2 int_const0
	lw	$a0 32($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 24($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	sw	$s1 0($fp)
	sw	$s2 4($fp)
	bne	$a0 $zero label100
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label100:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr		$t1
	lw	$s1 0($fp)
	lw	$s2 4($fp)
	move	$s1 $a0
	lw	$t1 12($s1)
	la	$a0 bool_const1
	beqz	$t1 label103
	la	$a0 bool_const0
label103:
	lw	$t1 12($a0)
	beqz	$t1 label101
	lw	$a0 28($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 24($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	sw	$s1 0($fp)
	sw	$s2 4($fp)
	bne	$a0 $zero label104
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label104:
	lw	$t1 8($a0)
	lw	$t1 24($t1)
	jalr		$t1
	lw	$s1 0($fp)
	lw	$s2 4($fp)
	move	$s1 $a0
	b	label102
label101:
	la	$a0 int_const0
label102:
	lw	$t1 12($s1)
	la	$a0 bool_const1
	beqz	$t1 label107
	la	$a0 bool_const0
label107:
	lw	$t1 12($a0)
	beqz	$t1 label105
	lw	$s3 32($fp)
	lw	$t2 28($fp)
	move	$t1 $s3
	la	$a0 bool_const1
	beq	$t1 $t2 label110
	la	$a1 bool_const0
	jal	equality_test
label110:
	lw	$t1 12($a0)
	beqz	$t1 label108
	lw	$a0 24($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	sw	$s1 0($fp)
	sw	$s2 4($fp)
	bne	$a0 $zero label111
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label111:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr		$t1
	lw	$s1 0($fp)
	lw	$s2 4($fp)
	move	$s1 $a0
	b	label109
label108:
	la	$a0 int_const0
label109:
	b	label106
label105:
	la	$a0 int_const0
label106:
	lw	$t1 12($s1)
	la	$a0 bool_const1
	beqz	$t1 label114
	la	$a0 bool_const0
label114:
	lw	$t1 12($a0)
	beqz	$t1 label112
	lw	$s3 32($fp)
	lw	$a0 28($fp)
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s3)
	add	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s3 $a0
	la	$t2 int_const1
	move	$t1 $s3
	la	$a0 bool_const1
	beq	$t1 $t2 label117
	la	$a1 bool_const0
	jal	equality_test
label117:
	lw	$t1 12($a0)
	beqz	$t1 label115
	lw	$a0 24($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	sw	$s1 0($fp)
	sw	$s2 4($fp)
	bne	$a0 $zero label118
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label118:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	lw	$s1 0($fp)
	lw	$s2 4($fp)
	move	$s1 $a0
	b	label116
label115:
	la	$a0 int_const0
label116:
	b	label113
label112:
	la	$a0 int_const0
label113:
	move	$a0 $s1
	lw	$fp 24($sp)
	lw	$s0 20($sp)
	lw	$ra 16($sp)
	addiu	$sp $sp 36
	jr	$ra	
Game.start:
	addiu	$sp $sp -16
	sw	$fp 16($sp)
	sw	$s0 12($sp)
	sw	$ra 8($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
label119:
	lw	$a0 20($s0)
	lw	$t1 12($a0)
	beq	$t1 $zero label120
	move	$a0 $s0
	bne	$a0 $zero label121
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label121:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	la	$a0 str_const14
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($s0)
	bne	$a0 $zero label122
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label122:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	lw	$a0 12($s0)
	bne	$a0 $zero label124
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label124:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr		$t1
	move	$s1 $a0
	la	$t2 str_const15
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label123
	la	$a1 bool_const0
	jal	equality_test
label123:
	sw	$a0 20($s0)
	lw	$s1 28($s0)
	la	$a0 int_const3
	jal	Object.copy
	lw	$t1 12($a0)
	neg	$t1 $t1
	sw	$t1 12($a0)
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s1)
	mul	$t1 $t1 $t2
	sw	$t1 12($a0)
	sw	$a0 28($s0)
	b	label119
label120:
	move	$a0 $zero
	lw	$fp 16($sp)
	lw	$s0 12($sp)
	lw	$ra 8($sp)
	addiu	$sp $sp 16
	jr	$ra	
TTTBoard.init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	la	$a0 str_const0
	sw	$a0 12($s0)
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
TTTBoard.get:
	addiu	$sp $sp -16
	sw	$fp 16($sp)
	sw	$s0 12($sp)
	sw	$ra 8($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$s1 20($fp)
	la	$a0 int_const0
	lw	$t1 12($s1)
	lw	$t2 12($a0)
	la	$a0 bool_const1
	blt	$t1 $t2 label127
	la	$a0 bool_const0
label127:
	lw	$t1 12($a0)
	beqz	$t1 label125
	la	$a0 str_const1
	b	label126
label125:
	la	$s1 int_const1
	lw	$a0 20($fp)
	lw	$t1 12($s1)
	lw	$t2 12($a0)
	la	$a0 bool_const1
	blt	$t1 $t2 label130
	la	$a0 bool_const0
label130:
	lw	$t1 12($a0)
	beqz	$t1 label128
	la	$a0 str_const1
	b	label129
label128:
	lw	$s1 16($fp)
	la	$a0 int_const0
	lw	$t1 12($s1)
	lw	$t2 12($a0)
	la	$a0 bool_const1
	blt	$t1 $t2 label133
	la	$a0 bool_const0
label133:
	lw	$t1 12($a0)
	beqz	$t1 label131
	la	$a0 str_const1
	b	label132
label131:
	la	$s1 int_const1
	lw	$a0 16($fp)
	lw	$t1 12($s1)
	lw	$t2 12($a0)
	la	$a0 bool_const1
	blt	$t1 $t2 label136
	la	$a0 bool_const0
label136:
	lw	$t1 12($a0)
	beqz	$t1 label134
	la	$a0 str_const1
	b	label135
label134:
	lw	$s1 20($fp)
	la	$a0 int_const2
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s1)
	mul	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s1 $a0
	lw	$a0 16($fp)
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s1)
	add	$t1 $t1 $t2
	sw	$t1 12($a0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const3
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($s0)
	bne	$a0 $zero label137
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label137:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr		$t1
label135:
label132:
label129:
label126:
	lw	$fp 16($sp)
	lw	$s0 12($sp)
	lw	$ra 8($sp)
	addiu	$sp $sp 24
	jr	$ra	
TTTBoard.set:
	addiu	$sp $sp -20
	sw	$fp 20($sp)
	sw	$s0 16($sp)
	sw	$ra 12($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$a0 20($fp)
	bne	$a0 $zero label142
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label142:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	move	$s1 $a0
	la	$t2 int_const3
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label141
	la	$a1 bool_const0
	jal	equality_test
label141:
	lw	$t1 12($a0)
	la	$a0 bool_const1
	beqz	$t1 label140
	la	$a0 bool_const0
label140:
	lw	$t1 12($a0)
	beqz	$t1 label138
	la	$a0 str_const1
	b	label139
label138:
	lw	$s1 28($fp)
	la	$a0 int_const0
	lw	$t1 12($s1)
	lw	$t2 12($a0)
	la	$a0 bool_const1
	blt	$t1 $t2 label145
	la	$a0 bool_const0
label145:
	lw	$t1 12($a0)
	beqz	$t1 label143
	la	$a0 str_const1
	b	label144
label143:
	la	$s1 int_const1
	lw	$a0 28($fp)
	lw	$t1 12($s1)
	lw	$t2 12($a0)
	la	$a0 bool_const1
	blt	$t1 $t2 label148
	la	$a0 bool_const0
label148:
	lw	$t1 12($a0)
	beqz	$t1 label146
	la	$a0 str_const1
	b	label147
label146:
	lw	$s1 24($fp)
	la	$a0 int_const0
	lw	$t1 12($s1)
	lw	$t2 12($a0)
	la	$a0 bool_const1
	blt	$t1 $t2 label151
	la	$a0 bool_const0
label151:
	lw	$t1 12($a0)
	beqz	$t1 label149
	la	$a0 str_const1
	b	label150
label149:
	la	$s1 int_const1
	lw	$a0 24($fp)
	lw	$t1 12($s1)
	lw	$t2 12($a0)
	la	$a0 bool_const1
	blt	$t1 $t2 label154
	la	$a0 bool_const0
label154:
	lw	$t1 12($a0)
	beqz	$t1 label152
	la	$a0 str_const1
	b	label153
label152:
	lw	$s1 28($fp)
	la	$a0 int_const2
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s1)
	mul	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s1 $a0
	lw	$a0 24($fp)
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s1)
	add	$t1 $t1 $t2
	sw	$t1 12($a0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const3
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($s0)
	bne	$a0 $zero label159
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label159:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr		$t1
	move	$s1 $a0
	la	$t2 str_const2
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label158
	la	$a1 bool_const0
	jal	equality_test
label158:
	lw	$t1 12($a0)
	la	$a0 bool_const1
	beqz	$t1 label157
	la	$a0 bool_const0
label157:
	lw	$t1 12($a0)
	beqz	$t1 label155
	la	$a0 str_const3
	b	label156
label155:
	lw	$s1 28($fp)
	la	$a0 int_const2
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s1)
	mul	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s1 $a0
	lw	$a0 24($fp)
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s1)
	add	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s1 $a0
	la	$a0 int_const3
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s1)
	add	$t1 $t1 $t2
	sw	$t1 12($a0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$s1 int_const4
	lw	$s2 28($fp)
	la	$a0 int_const2
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s2)
	mul	$t1 $t1 $t2
	sw	$t1 12($a0)
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s1)
	sub	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s1 $a0
	lw	$a0 24($fp)
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s1)
	sub	$t1 $t1 $t2
	sw	$t1 12($a0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($s0)
	bne	$a0 $zero label160
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label160:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr		$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 20($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$s1 28($fp)
	la	$a0 int_const2
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s1)
	mul	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s1 $a0
	lw	$a0 24($fp)
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s1)
	add	$t1 $t1 $t2
	sw	$t1 12($a0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($s0)
	bne	$a0 $zero label161
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label161:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr		$t1
	bne	$a0 $zero label162
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label162:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	bne	$a0 $zero label163
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label163:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	sw	$a0 12($s0)
label156:
label153:
label150:
label147:
label144:
label139:
	lw	$fp 20($sp)
	lw	$s0 16($sp)
	lw	$ra 12($sp)
	addiu	$sp $sp 32
	jr	$ra	
TTTBoard.display:
	addiu	$sp $sp -28
	sw	$fp 28($sp)
	sw	$s0 24($sp)
	sw	$ra 20($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	la	$s1 int_const0
	la	$s2 int_const0
	la	$s3 str_const4
label164:
	move	$s4 $s1
	la	$a0 int_const2
	lw	$t1 12($s4)
	lw	$t2 12($a0)
	la	$a0 bool_const1
	blt	$t1 $t2 label166
	la	$a0 bool_const0
label166:
	lw	$t1 12($a0)
	beq	$t1 $zero label165
	la	$s2 int_const0
label167:
	move	$s4 $s2
	la	$a0 int_const2
	lw	$t1 12($s4)
	lw	$t2 12($a0)
	la	$a0 bool_const1
	blt	$t1 $t2 label169
	la	$a0 bool_const0
label169:
	lw	$t1 12($a0)
	beq	$t1 $zero label168
	sw	$s2 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const3
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s3
	sw	$s1 0($fp)
	sw	$s2 4($fp)
	sw	$s3 8($fp)
	bne	$a0 $zero label170
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label170:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr		$t1
	lw	$s1 0($fp)
	lw	$s2 4($fp)
	lw	$s3 8($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$s4 $s1
	la	$a0 int_const2
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s4)
	mul	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s4 $a0
	move	$a0 $s2
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s4)
	add	$t1 $t1 $t2
	sw	$t1 12($a0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const3
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($s0)
	sw	$s1 0($fp)
	sw	$s2 4($fp)
	sw	$s3 8($fp)
	bne	$a0 $zero label171
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label171:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr		$t1
	lw	$s1 0($fp)
	lw	$s2 4($fp)
	lw	$s3 8($fp)
	sw	$s1 0($fp)
	sw	$s2 4($fp)
	sw	$s3 8($fp)
	bne	$a0 $zero label172
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label172:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	lw	$s1 0($fp)
	lw	$s2 4($fp)
	lw	$s3 8($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 28($fp)
	sw	$s1 0($fp)
	sw	$s2 4($fp)
	sw	$s3 8($fp)
	bne	$a0 $zero label173
	la	$a0 str_const5
	li	$t1 1
	jal	_dispatch_abort
label173:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	lw	$s1 0($fp)
	lw	$s2 4($fp)
	lw	$s3 8($fp)
	move	$s4 $s2
	la	$a0 int_const3
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s4)
	add	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s2 $a0
	b	label167
label168:
	move	$a0 $zero
	move	$s4 $s1
	la	$a0 int_const3
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s4)
	add	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s1 $a0
	b	label164
label165:
	move	$a0 $zero
	lw	$fp 28($sp)
	lw	$s0 24($sp)
	lw	$ra 20($sp)
	addiu	$sp $sp 32
	jr	$ra	
