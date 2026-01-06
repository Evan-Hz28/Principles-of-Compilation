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
	.word	4
_bool_tag:
	.word	5
_string_tag:
	.word	6
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
str_const33:
	.word	6
	.word	5
	.word	String_dispTab
	.word	int_const1
	.byte	0	
	.align	2
	.word	-1
str_const32:
	.word	6
	.word	6
	.word	String_dispTab
	.word	int_const2
	.ascii	"Main"
	.byte	0	
	.align	2
	.word	-1
str_const31:
	.word	6
	.word	6
	.word	String_dispTab
	.word	int_const3
	.ascii	"Stack"
	.byte	0	
	.align	2
	.word	-1
str_const30:
	.word	6
	.word	7
	.word	String_dispTab
	.word	int_const4
	.ascii	"StackNode"
	.byte	0	
	.align	2
	.word	-1
str_const29:
	.word	6
	.word	6
	.word	String_dispTab
	.word	int_const5
	.ascii	"String"
	.byte	0	
	.align	2
	.word	-1
str_const28:
	.word	6
	.word	6
	.word	String_dispTab
	.word	int_const2
	.ascii	"Bool"
	.byte	0	
	.align	2
	.word	-1
str_const27:
	.word	6
	.word	5
	.word	String_dispTab
	.word	int_const6
	.ascii	"Int"
	.byte	0	
	.align	2
	.word	-1
str_const26:
	.word	6
	.word	5
	.word	String_dispTab
	.word	int_const7
	.ascii	"IO"
	.byte	0	
	.align	2
	.word	-1
str_const25:
	.word	6
	.word	7
	.word	String_dispTab
	.word	int_const8
	.ascii	"_prim_slot"
	.byte	0	
	.align	2
	.word	-1
str_const24:
	.word	6
	.word	7
	.word	String_dispTab
	.word	int_const4
	.ascii	"SELF_TYPE"
	.byte	0	
	.align	2
	.word	-1
str_const23:
	.word	6
	.word	7
	.word	String_dispTab
	.word	int_const4
	.ascii	"_no_class"
	.byte	0	
	.align	2
	.word	-1
str_const22:
	.word	6
	.word	8
	.word	String_dispTab
	.word	int_const9
	.ascii	"<basic class>"
	.byte	0	
	.align	2
	.word	-1
str_const21:
	.word	6
	.word	12
	.word	String_dispTab
	.word	int_const10
	.ascii	"This line will not be reached.\n"
	.byte	0	
	.align	2
	.word	-1
str_const20:
	.word	6
	.word	15
	.word	String_dispTab
	.word	int_const11
	.ascii	"Now trying to pop from an empty stack...\n"
	.byte	0	
	.align	2
	.word	-1
str_const19:
	.word	6
	.word	11
	.word	String_dispTab
	.word	int_const12
	.ascii	"Popping all elements...\n"
	.byte	0	
	.align	2
	.word	-1
str_const18:
	.word	6
	.word	10
	.word	String_dispTab
	.word	int_const13
	.ascii	"Popping an element...\n"
	.byte	0	
	.align	2
	.word	-1
str_const17:
	.word	6
	.word	5
	.word	String_dispTab
	.word	int_const7
	.ascii	"\n\n"
	.byte	0	
	.align	2
	.word	-1
str_const16:
	.word	6
	.word	6
	.word	String_dispTab
	.word	int_const5
	.ascii	"Object"
	.byte	0	
	.align	2
	.word	-1
str_const15:
	.word	6
	.word	10
	.word	String_dispTab
	.word	int_const14
	.ascii	"Peeking top element: "
	.byte	0	
	.align	2
	.word	-1
str_const14:
	.word	6
	.word	5
	.word	String_dispTab
	.word	int_const6
	.ascii	"Bob"
	.byte	0	
	.align	2
	.word	-1
str_const13:
	.word	6
	.word	6
	.word	String_dispTab
	.word	int_const3
	.ascii	"Alice"
	.byte	0	
	.align	2
	.word	-1
str_const12:
	.word	6
	.word	12
	.word	String_dispTab
	.word	int_const10
	.ascii	"Pushing 'Alice', 100, 'Bob'...\n"
	.byte	0	
	.align	2
	.word	-1
str_const11:
	.word	6
	.word	5
	.word	String_dispTab
	.word	int_const6
	.ascii	"No\n"
	.byte	0	
	.align	2
	.word	-1
str_const10:
	.word	6
	.word	6
	.word	String_dispTab
	.word	int_const2
	.ascii	"Yes\n"
	.byte	0	
	.align	2
	.word	-1
str_const9:
	.word	6
	.word	9
	.word	String_dispTab
	.word	int_const15
	.ascii	"Is stack empty? "
	.byte	0	
	.align	2
	.word	-1
str_const8:
	.word	6
	.word	10
	.word	String_dispTab
	.word	int_const16
	.ascii	"--- Stack Demo ---\n\n"
	.byte	0	
	.align	2
	.word	-1
str_const7:
	.word	6
	.word	11
	.word	String_dispTab
	.word	int_const17
	.ascii	"---- Bottom of Stack ----\n"
	.byte	0	
	.align	2
	.word	-1
str_const6:
	.word	6
	.word	9
	.word	String_dispTab
	.word	int_const18
	.ascii	"Unprintable Object\n"
	.byte	0	
	.align	2
	.word	-1
str_const5:
	.word	6
	.word	5
	.word	String_dispTab
	.word	int_const19
	.ascii	"\n"
	.byte	0	
	.align	2
	.word	-1
str_const4:
	.word	6
	.word	10
	.word	String_dispTab
	.word	int_const20
	.ascii	"---- Top of Stack ----\n"
	.byte	0	
	.align	2
	.word	-1
str_const3:
	.word	6
	.word	9
	.word	String_dispTab
	.word	int_const15
	.ascii	"Stack is empty.\n"
	.byte	0	
	.align	2
	.word	-1
str_const2:
	.word	6
	.word	13
	.word	String_dispTab
	.word	int_const21
	.ascii	"Error: pop from an empty stack.\n"
	.byte	0	
	.align	2
	.word	-1
str_const1:
	.word	6
	.word	13
	.word	String_dispTab
	.word	int_const22
	.ascii	"Error: peek from an empty stack.\n"
	.byte	0	
	.align	2
	.word	-1
str_const0:
	.word	6
	.word	7
	.word	String_dispTab
	.word	int_const23
	.ascii	"stack.cl"
	.byte	0	
	.align	2
	.word	-1
int_const23:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	8
	.word	-1
int_const22:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	33
	.word	-1
int_const21:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	32
	.word	-1
int_const20:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	23
	.word	-1
int_const19:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	1
	.word	-1
int_const18:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	19
	.word	-1
int_const17:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	26
	.word	-1
int_const16:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	20
	.word	-1
int_const15:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	16
	.word	-1
int_const14:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	21
	.word	-1
int_const13:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	22
	.word	-1
int_const12:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	24
	.word	-1
int_const11:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	41
	.word	-1
int_const10:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	31
	.word	-1
int_const9:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	13
	.word	-1
int_const8:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	10
	.word	-1
int_const7:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	2
	.word	-1
int_const6:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	3
	.word	-1
int_const5:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	6
	.word	-1
int_const4:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	9
	.word	-1
int_const3:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	5
	.word	-1
int_const2:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	4
	.word	-1
int_const1:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	0
	.word	-1
int_const0:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	100
	.word	-1
bool_const0:
	.word	5
	.word	4
	.word	Bool_dispTab
	.word	0
	.word	-1
bool_const1:
	.word	5
	.word	4
	.word	Bool_dispTab
	.word	1
class_nameTab:
	.word	str_const16
	.word	str_const26
	.word	str_const31
	.word	str_const32
	.word	str_const27
	.word	str_const28
	.word	str_const29
	.word	str_const30
class_objTab:
	.word	Object_protObj
	.word	Object_init
	.word	IO_protObj
	.word	IO_init
	.word	Stack_protObj
	.word	Stack_init
	.word	Main_protObj
	.word	Main_init
	.word	Int_protObj
	.word	Int_init
	.word	Bool_protObj
	.word	Bool_init
	.word	String_protObj
	.word	String_init
	.word	StackNode_protObj
	.word	StackNode_init
Object_dispTab:
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
Int_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
Bool_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
String_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	String.length
	.word	String.concat
	.word	String.substr
StackNode_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	StackNode.init
	.word	StackNode.getItem
	.word	StackNode.getNext
Stack_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	Stack.isEmpty
	.word	Stack.push
	.word	Stack.peek
	.word	Stack.pop
	.word	Stack.print
Main_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	Main.main
	.word	-1
Object_protObj:
	.word	0	# class tag
	.word	3	# size
	.word	Object_dispTab
	.word	-1
IO_protObj:
	.word	1	# class tag
	.word	3	# size
	.word	IO_dispTab
	.word	-1
Int_protObj:
	.word	4	# class tag
	.word	4	# size
	.word	Int_dispTab
	.word	0
	.word	-1
Bool_protObj:
	.word	5	# class tag
	.word	4	# size
	.word	Bool_dispTab
	.word	0
	.word	-1
String_protObj:
	.word	6	# class tag
	.word	5	# size
	.word	String_dispTab
	.word	int_const1
	.word	0
	.word	-1
StackNode_protObj:
	.word	7	# class tag
	.word	5	# size
	.word	StackNode_dispTab
	.word	0
	.word	0
	.word	-1
Stack_protObj:
	.word	2	# class tag
	.word	4	# size
	.word	Stack_dispTab
	.word	0
	.word	-1
Main_protObj:
	.word	3	# class tag
	.word	3	# size
	.word	Main_dispTab
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
StackNode_init:
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
Stack_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	IO_init
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
	jal	IO_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
StackNode.init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$a0 16($fp)
	sw	$a0 12($s0)
	lw	$a0 12($fp)
	sw	$a0 16($s0)
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	addiu	$sp $sp 8
	jr	$ra	
StackNode.getItem:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$a0 12($s0)
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	addiu	$sp $sp 0
	jr	$ra	
StackNode.getNext:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$a0 16($s0)
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	addiu	$sp $sp 0
	jr	$ra	
Stack.isEmpty:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$a0 12($s0)
	move	$t1 $a0
	la	$a0 bool_const1
	beqz	$t1 label0
	la	$a0 bool_const0
label0:
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	addiu	$sp $sp 0
	jr	$ra	
Stack.push:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$a0 12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 StackNode_protObj
	jal	Object.copy
	jal	StackNode_init
	bne	$a0 $zero label1
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label1:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 4($sp)
	sw	$a0 12($s0)
	addiu	$sp $sp 4
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	addiu	$sp $sp 4
	jr	$ra	
Stack.peek:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	move	$a0 $s0
	bne	$a0 $zero label2
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label2:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr		$t1
	lw	$t1 12($a0)
	beq	$t1 $zero label3
	la	$a0 str_const1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label5
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label5:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	move	$a0 $s0
	bne	$a0 $zero label6
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label6:
	lw	$t1 8($a0)
	lw	$t1 0($t1)
	jalr		$t1
	la	$a0 Object_protObj
	jal	Object.copy
	jal	Object_init
	b	label4
label3:
	lw	$a0 12($s0)
	bne	$a0 $zero label7
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label7:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
label4:
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	addiu	$sp $sp 0
	jr	$ra	
Stack.pop:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	move	$a0 $s0
	bne	$a0 $zero label8
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label8:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr		$t1
	lw	$t1 12($a0)
	beq	$t1 $zero label9
	la	$a0 str_const2
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label11
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label11:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	move	$a0 $s0
	bne	$a0 $zero label12
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label12:
	lw	$t1 8($a0)
	lw	$t1 0($t1)
	jalr		$t1
	la	$a0 Object_protObj
	jal	Object.copy
	jal	Object_init
	b	label10
label9:
	lw	$a0 12($s0)
	bne	$a0 $zero label13
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label13:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($s0)
	bne	$a0 $zero label14
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label14:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr		$t1
	sw	$a0 12($s0)
	lw	$a0 4($sp)
	addiu	$sp $sp 4
label10:
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	addiu	$sp $sp 0
	jr	$ra	
Stack.print:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	move	$a0 $s0
	bne	$a0 $zero label15
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label15:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr		$t1
	lw	$t1 12($a0)
	beq	$t1 $zero label16
	la	$a0 str_const3
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label18
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label18:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	b	label17
label16:
	la	$a0 str_const4
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label19
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label19:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	lw	$a0 12($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
label20:
	lw	$a0 4($sp)
	move	$t1 $a0
	la	$a0 bool_const1
	beqz	$t1 label22
	la	$a0 bool_const0
label22:
	lw	$t1 12($a0)
	la	$a0 bool_const1
	beqz	$t1 label23
	la	$a0 bool_const0
label23:
	lw	$t1 12($a0)
	beq	$t1 $zero label21
	lw	$a0 4($sp)
	bne	$a0 $zero label24
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label24:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	bne	$a0 $zero label25
	la	$a0 str_const0
	li	$t1 1
	jal	_case_abort2
label25:
	lw	$t1 0($a0)
	blt	$t1 6 label27
	bgt	$t1 6 label27
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 4($sp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label28
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label28:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	la	$a0 str_const5
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label29
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label29:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	addiu	$sp $sp 4
	b	label26
label27:
	blt	$t1 4 label30
	bgt	$t1 4 label30
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 4($sp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label31
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label31:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	la	$a0 str_const5
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label32
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label32:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	addiu	$sp $sp 4
	b	label26
label30:
	blt	$t1 0 label33
	bgt	$t1 7 label33
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const6
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label34
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label34:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	addiu	$sp $sp 4
	b	label26
label33:
	jal	_case_abort
label26:
	lw	$a0 4($sp)
	bne	$a0 $zero label35
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label35:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr		$t1
	sw	$a0 4($sp)
	b	label20
label21:
	move	$a0 $zero
	addiu	$sp $sp 4
	la	$a0 str_const7
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label36
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label36:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
label17:
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	addiu	$sp $sp 0
	jr	$ra	
Main.main:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	la	$a0 Stack_protObj
	jal	Object.copy
	jal	Stack_init
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const8
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label37
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label37:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	la	$a0 str_const9
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label38
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label38:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	lw	$a0 4($sp)
	bne	$a0 $zero label39
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label39:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr		$t1
	lw	$t1 12($a0)
	beq	$t1 $zero label40
	la	$a0 str_const10
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label42
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label42:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	b	label41
label40:
	la	$a0 str_const11
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label43
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label43:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
label41:
	lw	$a0 4($sp)
	bne	$a0 $zero label44
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label44:
	lw	$t1 8($a0)
	lw	$t1 44($t1)
	jalr		$t1
	la	$a0 str_const5
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label45
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label45:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	la	$a0 str_const12
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label46
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label46:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	la	$a0 str_const13
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 8($sp)
	bne	$a0 $zero label47
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label47:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	la	$a0 int_const0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 8($sp)
	bne	$a0 $zero label48
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label48:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	la	$a0 str_const14
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 8($sp)
	bne	$a0 $zero label49
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label49:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	lw	$a0 4($sp)
	bne	$a0 $zero label50
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label50:
	lw	$t1 8($a0)
	lw	$t1 44($t1)
	jalr		$t1
	la	$a0 str_const5
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label51
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label51:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	la	$a0 str_const15
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label52
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label52:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	lw	$a0 4($sp)
	bne	$a0 $zero label53
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label53:
	lw	$t1 8($a0)
	lw	$t1 36($t1)
	jalr		$t1
	bne	$a0 $zero label54
	la	$a0 str_const0
	li	$t1 1
	jal	_case_abort2
label54:
	lw	$t1 0($a0)
	blt	$t1 6 label56
	bgt	$t1 6 label56
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 4($sp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label57
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label57:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	addiu	$sp $sp 4
	b	label55
label56:
	blt	$t1 4 label58
	bgt	$t1 4 label58
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 4($sp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label59
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label59:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	addiu	$sp $sp 4
	b	label55
label58:
	blt	$t1 0 label60
	bgt	$t1 7 label60
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const16
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label61
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label61:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	addiu	$sp $sp 4
	b	label55
label60:
	jal	_case_abort
label55:
	la	$a0 str_const17
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label62
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label62:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	la	$a0 str_const18
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label63
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label63:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	lw	$a0 4($sp)
	bne	$a0 $zero label64
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label64:
	lw	$t1 8($a0)
	lw	$t1 40($t1)
	jalr		$t1
	lw	$a0 4($sp)
	bne	$a0 $zero label65
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label65:
	lw	$t1 8($a0)
	lw	$t1 44($t1)
	jalr		$t1
	la	$a0 str_const5
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label66
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label66:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	la	$a0 str_const9
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label67
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label67:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	lw	$a0 4($sp)
	bne	$a0 $zero label68
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label68:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr		$t1
	lw	$t1 12($a0)
	beq	$t1 $zero label69
	la	$a0 str_const10
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label71
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label71:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	b	label70
label69:
	la	$a0 str_const11
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label72
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label72:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
label70:
	la	$a0 str_const5
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label73
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label73:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	la	$a0 str_const19
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label74
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label74:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	lw	$a0 4($sp)
	bne	$a0 $zero label75
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label75:
	lw	$t1 8($a0)
	lw	$t1 40($t1)
	jalr		$t1
	lw	$a0 4($sp)
	bne	$a0 $zero label76
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label76:
	lw	$t1 8($a0)
	lw	$t1 40($t1)
	jalr		$t1
	lw	$a0 4($sp)
	bne	$a0 $zero label77
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label77:
	lw	$t1 8($a0)
	lw	$t1 44($t1)
	jalr		$t1
	la	$a0 str_const5
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label78
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label78:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	la	$a0 str_const20
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label79
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label79:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	lw	$a0 4($sp)
	bne	$a0 $zero label80
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label80:
	lw	$t1 8($a0)
	lw	$t1 40($t1)
	jalr		$t1
	la	$a0 str_const21
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label81
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label81:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	addiu	$sp $sp 4
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	addiu	$sp $sp 0
	jr	$ra	
