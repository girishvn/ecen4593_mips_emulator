//
// Created by Girish Narayanswamy on 4/23/17.
//

#include "Load_Insts.h"

/***********************************************************************************************************************

 program_image: initial array to hold program instructions

***********************************************************************************************************************/

#ifdef PROGRAM1
uint32_t program_image[] = {
        0x00000bb8,	//	$sp = 3000
        0x00000bb8,	//	$fp = 3000
        0x00000000,
        0x00000000,
        0x00000000,
        0x0000008c,	//	$pc = 140
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x18c00008,   // 	blez	a2,400854 <copy_array+0x24>
        0x00801025,   // 	move	v0,a0
        0x00063080,   // 	sll	a2,a2,0x2
        0x00862021,   // 	addu	a0,a0,a2
        0x8c430000,   // 	lw	v1,0(v0)
        0xaca30000,   // 	sw	v1,0(a1)
        0x24420004,   // 	addiu	v0,v0,4
        0x1444fffc,   // 	bne	v0,a0,400840 <copy_array+0x10>
        0x24a50004,   // 	addiu	a1,a1,4
        0x03e00008,   // 	jr	ra
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x1ca00018,   // 	bgtz	a1,4008c0 <bubble_sort+0x64>
        0x00005825,   // 	move	t3,zero
        0x03e00008,   // 	jr	ra
        0x00001025,   // 	move	v0,zero
        0x8c660000,   // 	lw	a2,0(v1)
        0x8c670004,   // 	lw	a3,4(v1)
        0x00e6402a,   // 	slt	t0,a3,a2
        0x11000004,   // 	beqz	t0,40088c <bubble_sort+0x30>
        0x00000000,   // 	nop
        0xac670000,   // 	sw	a3,0(v1)
        0xac660004,   // 	sw	a2,4(v1)
        0x240a0001,   // 	li	t2,1
        0x24630004,   // 	addiu	v1,v1,4
        0x1469fff6,   // 	bne	v1,t1,40086c <bubble_sort+0x10>
        0x00000000,   // 	nop
        0x004c1021,   // 	addu	v0,v0,t4
        0x10000002,   // 	b	4008a8 <bubble_sort+0x4c>
        0x00aa580a,   // 	movz	t3,a1,t2
        0x00a05825,   // 	move	t3,a1
        0x256b0001,   // 	addiu	t3,t3,1
        0x0165182a,   // 	slt	v1,t3,a1
        0x14600006,   // 	bnez	v1,4008cc <bubble_sort+0x70>
        0x01ab6023,   // 	subu	t4,t5,t3
        0x03e00008,   // 	jr	ra
        0x8c000820,		//0x00000000,   // 	nop
        0x00001025,   // 	move	v0,zero
        0x24adffff,   // 	addiu	t5,a1,-1
        0x01ab6023,   // 	subu	t4,t5,t3
        0x1980fff5,   // 	blez	t4,4008a4 <bubble_sort+0x48>
        0x00801825,   // 	move	v1,a0
        0x000c4880,   // 	sll	t1,t4,0x2
        0x00894821,   // 	addu	t1,a0,t1	0x8c190812,	//		flush memory location for testing
        0x1000ffe3,   // 	b	40086c <bubble_sort+0x10>
        0x00005025,   // 	move	t2,zero
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x28a20002,   // 	slti	v0,a1,2
        0x14400029,   // 	bnez	v0,400990 <insertion_sort+0xac>
        0x248e0004,   // 	addiu	t6,a0,4
        0x0080c025,   // 	move	t8,a0
        0x24190004,   // 	li	t9,4
        0x00001025,   // 	move	v0,zero
        0x10000016,   // 	b	400958 <insertion_sort+0x74>
        0x240f0001,   // 	li	t7,1
        0xac690000,   // 	sw	t1,0(v1)
        0x24420001,   // 	addiu	v0,v0,1
        0x104d000c,   // 	beq	v0,t5,400940 <insertion_sort+0x5c>
        0xacc80000,   // 	sw	t0,0(a2)
        0x006c1821,   // 	addu	v1,v1,t4
        0x00831821,   // 	addu	v1,a0,v1
        0x8ce8fffc,   // 	lw	t0,-4(a3)
        0x00cb3021,   // 	addu	a2,a2,t3
        0x24e7fffc,   // 	addiu	a3,a3,-4
        0x8ce9fffc,   // 	lw	t1,-4(a3)
        0x0109502a,   // 	slt	t2,t0,t1
        0x1540fff4,   // 	bnez	t2,400904 <insertion_sort+0x20>
        0x00863021,   // 	addu	a2,a0,a2
        0x10000003,   // 	b	400948 <insertion_sort+0x64>
        0x25ef0001,   // 	addiu	t7,t7,1
        0x01a01025,   // 	move	v0,t5
        0x25ef0001,   // 	addiu	t7,t7,1
        0x25ce0004,   // 	addiu	t6,t6,4
        0x27180004,   // 	addiu	t8,t8,4
        0x10af0010,   // 	beq	a1,t7,400994 <insertion_sort+0xb0>
        0x27390004,   // 	addiu	t9,t9,4
        0x19e0fffa,   // 	blez	t7,400944 <insertion_sort+0x60>
        0x01c01825,   // 	move	v1,t6
        0x8dc80000,   // 	lw	t0,0(t6)
        0x8f090000,   // 	lw	t1,0(t8)
        0x0109382a,   // 	slt	a3,t0,t1
        0x10e0fff5,   // 	beqz	a3,400944 <insertion_sort+0x60>
        0x03003025,   // 	move	a2,t8
        0x004f6821,   // 	addu	t5,v0,t7
        0x01c03825,   // 	move	a3,t6
        0x272cfffc,   // 	addiu	t4,t9,-4
        0x018e6023,   // 	subu	t4,t4,t6
        0x272bfff8,   // 	addiu	t3,t9,-8
        0x1000ffde,   // 	b	400904 <insertion_sort+0x20>
        0x01785823,   // 	subu	t3,t3,t8
        0x00001025,   // 	move	v0,zero
        0x03e00008,   // 	jr	ra
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x18c0000e,   // 	blez	a2,4009dc <check_result+0x3c>
        0x00801825,   // 	move	v1,a0
        0x00063080,   // 	sll	a2,a2,0x2
        0x00862021,   // 	addu	a0,a0,a2
        0x00001025,   // 	move	v0,zero
        0x24060001,   // 	li	a2,1
        0x8c670000,   // 	lw	a3,0(v1)
        0x8ca80000,   // 	lw	t0,0(a1)
        0x00e83826,   // 	xor	a3,a3,t0
        0x00c7100b,   // 	movn	v0,a2,a3
        0x24630004,   // 	addiu	v1,v1,4
        0x1464fffa,   // 	bne	v1,a0,4009b8 <check_result+0x18>
        0x24a50004,   // 	addiu	a1,a1,4
        0x03e00008,   // 	jr	ra
        0x00000000,   // 	nop
        0x03e00008,   // 	jr	ra
        0x00001025,   // 	move	v0,zero
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x27bdf7f8,   // 	addiu	sp,sp,-2056
        0xafbf0804,   // 	sw	ra,2052(sp)
        0xafb30800,   // 	sw	s3,2048(sp)
        0xafb207fc,   // 	sw	s2,2044(sp)
        0xafb107f8,   // 	sw	s1,2040(sp)
        0xafb007f4,   // 	sw	s0,2036(sp)
        0x8c420000,   // 	lw	v0,0(v0)
        0xafa207ec,   // 	sw	v0,2028(sp)
        0x240600fa,   // 	li	a2,250
        0x27b10404,   // 	addiu	s1,sp,1028
        0x02202825,   // 	move	a1,s1
        0x27b0001c,   // 	addiu	s0,sp,28
        0x02002025,   // 	move	a0,s0
        0x0c00000a,   // 	jal	10 <copy_array>
        0x00000000,   // 	nop
        0x240500fa,   // 	li	a1,250
        0x02002025,   // 	move	a0,s0
        0x0c00001e,   // 	jal	30 <bubble_sort>
        0x00000000,   // 	nop
        0x00409025,   // 	move	s2,v0
        0x240500fa,   // 	li	a1,250
        0x02202025,   // 	move	a0,s1
        0x0c000046,   // 	jal 70 <insertion_sort>
        0x00000000,   // 	nop
        0x00409825,   // 	move	s3,v0
        0x240600fa,   // 	li	a2,250
        0x02202825,   // 	move	a1,s1
        0x02002025,   // 	move	a0,s0
        0x0c000078,   // 	jal	120 <check_result>
        0x00000000,   // 	nop
        0x0240a020,	  // 	move $s32 to $s4 to be stored into result memory location
        0x0272902a,   // 	slt	s2,s3,s2
        0x16400003,   // 	bnez	s2,400a90 <main+0xac>
        0x3c03000f,   // 	lui	v1,0xf
        0x24634240,   // 	addiu	v1,v1,16960
        0x00431021,   // 	addu	v0,v0,v1
        0xac14001c,	  //	sw $s4, 28($zero)	store number of passes through bubble sort
        0xac130020,	  //	sw $s3, 32($zero) 	store number of passes through insertion sort
        0xac020024,	  //	sw $v0, 36($zero)	if 0, the two arrays are equal, 1 they are not equal
        0x8c0804b0,	  //	lw $t0, 1200($zero)	Using the data in memory location 300 to verify sort
        0xac080018,	  //	sw $t0, 24($zero)
        0x8c001018,	  //	flush cache to memory to view via memory
        0x8c00101c,	  //	flush cache to memory to view via memory
        0x8c001020,	  //	flush cache to memory to view via memory
        0x8c001024,	  //	flush cache to memory to view via memory
        0x00000000,	  //	nop
        0x00000000,	  //	nop
        0x00000000,	  //	nop
        0x00000000,	  //	nop
        0x00000008,   // 	jr	to PC = 0, indicating end of program
        0x00000000,	  //	nop
        0x00000000,	  //	nop
        0x00000000,	  //	nop
        0x00000000,	  //	nop
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x0a000000,
        0x00000d00,    // 	nop
        0x00b00000,    // 	nop
        0x000000e0,
        0x00030000,    // 	nop
        0x0f000000,    // 	nop
        0x0000f000,
        0xffffffff,
        0x0a0a0000,
        0x0f0f0f0f,
        0xf0f0f0f0,
        0x00010020,
        0xf0000000,
        0x0aa0bab0,
        0xa5a5a5a5,
        0x5a5a5a5a,
        0x0acccbaa,
        0x00000000,
        0xffffffff,
        0xf034a04a,
        0xaaaaaaaa,
        0xbbbbbbbb,
        0xcccccccc,
        0xdddddddd,
        0xeeeeeeee,
        0x99999999,
        0x88888888,
        0x77777777,
        0x66666666,
        0x55555555,
        0x44444444,
        0x33333333,
        0x22222222,
        0x11111111,
        0x00000001,
        0x00000010,
        0x00000100,
        0x00001000,
        0x00010000,
        0x00100000,
        0x01000000,
        0x10000000,
        0x00000002,
        0x00000020,
        0x00000200,
        0x00002000,
        0x00020000,
        0x00200000,
        0x02000000,
        0x20000000,
        0x00000003,
        0x00000030,
        0x00000300,
        0x00003000,
        0x00030000,
        0x00300000,
        0x03000000,
        0x30000000,
        0x00000004,
        0x00000040,
        0x00000400,
        0x00004000,
        0x00040000,
        0x00400000,
        0x04000000,
        0x40000000,
        0x00000005,
        0x00000050,
        0x00000500,
        0x00005000,
        0x00050000,
        0x00500000,
        0x05000000,
        0x50000000,
        0x00000006,
        0x00000060,
        0x00000600,
        0x00006000,
        0x00060000,
        0x00600000,
        0x06000000,
        0x60000000,
        0x00000007,
        0x00000070,
        0x00000700,
        0x00007000,
        0x00070000,
        0x00700000,
        0x07000000,
        0x70000000,
        0x00000008,
        0x00000080,
        0x00000800,
        0x00008000,
        0x00080000,
        0x00800000,
        0x08000000,
        0x80000000,
        0x00000009,
        0x00000090,
        0x00000900,
        0x00009000,
        0x00090000,
        0x00900000,
        0x09000000,
        0x90000000,
        0x0000000a,
        0x000000a0,
        0x00000a00,
        0x0000a000,
        0x000a0000,
        0x00a00000,
        0x0a000000,
        0xa0000000,
        0x0000000b,
        0x000000b0,
        0x00000b00,
        0x0000b000,
        0x000b0000,
        0x00b00000,
        0x0b000000,
        0xb0000000,
        0x0000000c,
        0x000000c0,
        0x00000c00,
        0x0000c000,
        0x000c0000,
        0x00c00000,
        0x0c000000,
        0xc0000000,
        0x0000000d,
        0x000000d0,
        0x00000d00,
        0x0000d000,
        0x000d0000,
        0x00d00000,
        0x0d000000,
        0xd0000000,
        0x0000000e,
        0x000000e0,
        0x00000e00,
        0x0000e000,
        0x000e0000,
        0x00e00000,
        0x0e000000,
        0xe0000000,
        0x0000000f,
        0x000000f0,
        0x00000f00,
        0x0000f000,
        0x000f0000,
        0x00f00000,
        0x0f000000,
        0xf0000000,
        0x00000011,
        0x00001100,
        0x00110000,
        0x22000000,
        0x00000022,
        0x00002200,
        0x00220000,
        0x22000000,
        0x00000033,
        0x00003300,
        0x00330000,
        0x33000000,
        0x00000044,
        0x00004400,
        0x00440000,
        0x44000000,
        0x00000055,
        0x00005500,
        0x00550000,
        0x55000000,
        0x00000066,
        0x00006600,
        0x00660000,
        0x66000000,
        0x00000077,
        0x00007700,
        0x00770000,
        0x77000000,
        0x00000088,
        0x00008800,
        0x00880000,
        0x88000000,
        0x00000099,
        0x00009900,
        0x00990000,
        0x99000000,
        0x000000aa,
        0x0000aa00,
        0x00aa0000,
        0xaa000000,
        0x000000bb,
        0x0000bb00,
        0x00bb0000,
        0xbb000000,
        0x000000cc,
        0x0000cc00,
        0x00cc0000,
        0xcc000000,
        0x000000dd,
        0x0000dd00,
        0x00dd0000,
        0xdd000000,
        0x000000ee,
        0x0000ee00,
        0x00ee0000,
        0xee000000,
        0x000000ff,
        0x0000ff00,
        0x00ff0000,
        0xff000000,
        0x00000101,
        0x00001010,
        0x00010100,
        0x00101000,
        0x01010000,
        0x30300000,
        0x00000303,
        0x00003030,
        0x00030300,
        0x00303000,
        0x03030000,
        0x30300000,
        0x00000202,
        0x00002020,
        0x00020200,
        0x00202000,
        0x02020000,
        0x20200000,
        0x00000505,
        0x00005050,
        0x00050500,
        0x00505000,
        0x05050000,
        0x50500000,
        0x00000606,
        0x00006060,
        0x00060600,
        0x00606000,
        0x06060000,
        0x60600000,
        0x00000f0f,
        0x0000f0f0,
        0x000f0f00,
        0x00f0f000,
        0x0f0f0000,
        0x0000e000}; //LOCATION 492 (last data filled in array)
#endif

#ifdef PROGRAM2
uint32_t program_image[] = {
        0x00000898,	// $sp = 2200
        0x00000898,	// $fp = 2200
        0x00000320,	// data segment pointer used by the program
        0x00000000,
        0x00000000,
        0x00000078,	// $pc = 120
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x80a70000,   // 	lb	a3,0(a1)                                                                         PC = 10
        0x10e0001e,   // 	beqz	a3,4008b0 <ceasar_encrypt+0x80>
        0x24a50001,   // 	addiu	a1,a1,1
        0x30e200ff,   // 	andi	v0,a3,0xff
        0x2443ff9f,   // 	addiu	v1,v0,-97
        0x306300ff,   // 	andi	v1,v1,0xff
        0x2c63001a,   // 	sltiu	v1,v1,26
        0x10600009,   // 	beqz	v1,400874 <ceasar_encrypt+0x44>
        0x2443ffbf,   // 	addiu	v1,v0,-65
        0x00441021,   // 	addu	v0,v0,a0
        0x304200ff,   // 	andi	v0,v0,0xff                                                                   PC = 20
        0x7c023c20,   // 	seb	a3,v0
        0x28e3007b,   // 	slti	v1,a3,123
        0x1460000d,   // 	bnez	v1,40089c <ceasar_encrypt+0x6c>
        0x2442ffe6,   // 	addiu	v0,v0,-26
        0x1000000b,   // 	b	40089c <ceasar_encrypt+0x6c>
        0x7c023c20,   // 	seb	a3,v0
        0x306300ff,   // 	andi	v1,v1,0xff
        0x2c63001a,   // 	sltiu	v1,v1,26
        0x10600007,   // 	beqz	v1,40089c <ceasar_encrypt+0x6c>
        0x00441021,   // 	addu	v0,v0,a0                                                                     PC = 30
        0x304300ff,   // 	andi	v1,v0,0xff
        0x7c033c20,   // 	seb	a3,v1
        0x28e2005b,   // 	slti	v0,a3,91
        0x14400002,   // 	bnez	v0,40089c <ceasar_encrypt+0x6c>
        0x2463ffe6,   // 	addiu	v1,v1,-26
        0x7c033c20,   // 	seb	a3,v1
        0xa0c70000,   // 	sb	a3,0(a2)
        0x80a70000,   // 	lb	a3,0(a1)
        0x24c60001,   // 	addiu	a2,a2,1
        0x14e0ffe4,   // 	bnez	a3,40083c <ceasar_encrypt+0xc>                                               PC = 40
        0x24a50001,   // 	addiu	a1,a1,1
        0x03e00008,   // 	jr	ra
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x80a70000,   // 	lb	a3,0(a1)                                                                         PC = 50
        0x10e0001e,   // 	beqz	a3,400938 <ceasar_decrypt+0x80>
        0x24a50001,   // 	addiu	a1,a1,1
        0x30e200ff,   // 	andi	v0,a3,0xff
        0x2443ff9f,   // 	addiu	v1,v0,-97
        0x306300ff,   // 	andi	v1,v1,0xff
        0x2c63001a,   // 	sltiu	v1,v1,26
        0x10600009,   // 	beqz	v1,4008fc <ceasar_decrypt+0x44>
        0x2443ffbf,   // 	addiu	v1,v0,-65
        0x00441023,   // 	subu	v0,v0,a0
        0x304200ff,   // 	andi	v0,v0,0xff                                                                   PC = 60
        0x7c023c20,   // 	seb	a3,v0
        0x28e30061,   // 	slti	v1,a3,97
        0x1060000d,   // 	beqz	v1,400924 <ceasar_decrypt+0x6c>
        0x2442001a,   // 	addiu	v0,v0,26
        0x1000000b,   // 	b	400924 <ceasar_decrypt+0x6c>
        0x7c023c20,   // 	seb	a3,v0
        0x306300ff,   // 	andi	v1,v1,0xff
        0x2c63001a,   // 	sltiu	v1,v1,26
        0x10600007,   // 	beqz	v1,400924 <ceasar_decrypt+0x6c>
        0x00441023,   // 	subu	v0,v0,a0                                                                     PC = 70
        0x304300ff,   // 	andi	v1,v0,0xff
        0x7c033c20,   // 	seb	a3,v1
        0x28e20041,   // 	slti	v0,a3,65
        0x10400002,   // 	beqz	v0,400924 <ceasar_decrypt+0x6c>
        0x2463001a,   // 	addiu	v1,v1,26
        0x7c033c20,   // 	seb	a3,v1
        0xa0c70000,   // 	sb	a3,0(a2)
        0x80a70000,   // 	lb	a3,0(a1)
        0x24c60001,   // 	addiu	a2,a2,1
        0x14e0ffe4,   // 	bnez	a3,4008c4 <ceasar_decrypt+0xc>                                               PC = 80
        0x24a50001,   // 	addiu	a1,a1,1
        0x03e00008,   // 	jr	ra
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x80860000,   // 	lb	a2,0(a0)                                                                         PC = 90
        0x10c0000f,   // 	beqz	a2,400984 <compare_string+0x44>
        0x00a04025,   // 	move	t0,a1
        0x24840001,   // 	addiu	a0,a0,1
        0x00003825,   // 	move	a3,zero
        0x24020001,   // 	li	v0,1
        0x81030000,   // 	lb	v1,0(t0)
        0x00661826,   // 	xor	v1,v1,a2
        0x0003100b,   // 	movn	v0,zero,v1
        0x24e70001,   // 	addiu	a3,a3,1
        0x00e01825,   // 	move	v1,a3                                                                       PC = 100
        0x80860000,   // 	lb	a2,0(a0)
        0x25080001,   // 	addiu	t0,t0,1
        0x14c0fff8,   // 	bnez	a2,400958 <compare_string+0x18>
        0x24840001,   // 	addiu	a0,a0,1
        0x10000004,   // 	b	400990 <compare_string+0x50>
        0x00a32821,   // 	addu	a1,a1,v1
        0x00001825,   // 	move	v1,zero
        0x24020001,   // 	li	v0,1
        0x00a32821,   // 	addu	a1,a1,v1
        0x80a30000,   // 	lb	v1,0(a1)                                                                        PC = 110
        0x03e00008,   // 	jr	ra
        0x0003100b,   // 	movn	v0,zero,v1
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x27bdfc50,   // 	addiu	sp,sp,-944                                                                  PC = 120
        0xafbf03ac,   // 	sw	ra,940(sp)
        0xafb203a8,   // 	sw	s2,936(sp)
        0xafb103a4,   // 	sw	s1,932(sp)
        0xafb003a0,   // 	sw	s0,928(sp)
        0x8e020000,   // 	lw	v0,0(s0)
        0xafa2039c,   // 	sw	v0,924(sp)
        0x27b20144,   // 	addiu	s2,sp,324
        0x02403025,   // 	move	a2,s2
        0x3c020000,   // 	lui	v0,0x00
        0x8c050008,	  //	lw $a1, 8($zero)	0x8c450008,   // 	lw	a1,8(v0)                                PC = 130
        0x24040005,   // 	li	a0,5
        0x0c00000a,   // 	jal	10 <ceasar_encrypt>
        0x00000000,   // 	nop
        0x27b10270,   // 	addiu	s1,sp,624
        0x02203025,   // 	move	a2,s1
        0x02402825,   // 	move	a1,s2
        0x24040005,   // 	li	a0,5
        0x0c000032,   // 	jal	50 <ceasar_decrypt>
        0x00000000,   // 	nop
        0x02202825,   // 	move	a1,s1                                                                       PC = 140
        0x8c040008,	  //	lw $a0, 8($zero) 0x27a40018,   // 	addiu	a0,sp,24
        0x0c00005a,   // 	jal	90 <compare_string>
        0x00000000,   // 	nop
        0x8fa4039c,   // 	lw	a0,924(sp)
        0x8e030000,   // 	lw	v1,0(s0)
        0x10830004,   // 	beq	a0,v1,400a34 <main+0x98>
        0x8fbf03ac,   // 	lw	ra,940(sp)
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop                                                                                 PC = 150
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x8c080384,   // 	lw $t0, 900($zero)
        0x8c090690,   // 	lw $t1, 1680($zero)
        0x8c0a07bc,   // 	lw $t2, 1980($zero)
        0xac08001c,   // 	sw $t0, 28($zero)                                                                   PC = 160
        0xac090020,   // 	sw $t1, 32($zero)
        0xac0a0024,   // 	sw $t2, 36($zero)
        0xac020018,   // 	sw $v0, 24($zero)
        0x8c08041c,   // 	lw $t0, 1052($zero)
        0x8c090420,   // 	lw $t1, 1056($zero)
        0x8c0a0424,   // 	lw $t2, 1060($zero)
        0x8c080418,   // 	lw $t0, 1048($zero)
        0x8fb203a8,   // 	lw	s2,936(sp)
        0x8fb103a4,   // 	lw	s1,932(sp)
        0x8fb003a0,   // 	lw	s0,928(sp)                                                                      PC = 170
        0x00000008,   // 	jr	to PC = $zero to end program
        0x27bd03b0,   // 	addiu	sp,sp,944
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop                                                                                 PC = 180
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x00000000,   // 	nop
        0x44757269,   // 	Duri
        0x6e672061,   // 	ng a
        0x20666577,   // 	 few
        0x20646179,   // 	 day
        0x73206861,   // 	s ha
        0x6c74206e,   // 	lt n
        0x65617220,   // 	ear
        0x5665736f,   // 	Veso
        0x6e74696f,   // 	ntio
        0x20666f72,   // 	 for
        0x20746865,   // 	 the
        0x2070726f,   // 	 pro
        0x76697369,   // 	visi
        0x6f6e206f,   // 	on o
        0x6620636f,   // 	f co
        0x726e2061,   // 	rn a
        0x6e64206f,   // 	nd o
        0x74686572,   // 	ther
        0x20737570,   // 	 sup
        0x706c6965,   // 	plie
        0x73206120,   // 	s a
        0x70616e69,   // 	pani
        0x63206172,   // 	c ar
        0x6f736520,   // 	ose
        0x66726f6d,   // 	from
        0x20696e71,   // 	 inq
        0x75697269,   // 	uiri
        0x6573206d,   // 	es m
        0x61646520,   // 	ade
        0x6279206f,   // 	by o
        0x75722074,   // 	ur t
        0x726f6f70,   // 	roop
        0x7320616e,   // 	s an
        0x64207265,   // 	d re
        0x6d61726b,   // 	mark
        0x73207574,   // 	s ut
        0x74657265,   // 	tere
        0x64206279,   // 	d by
        0x20476175,   // 	 Gau
        0x6c732061,   // 	ls a
        0x6e642074,   // 	nd t
        0x72616465,   // 	rade
        0x72732077,   // 	rs w
        0x686f2061,   // 	ho a
        0x66666972,   // 	ffir
        0x6d656420,   // 	med
        0x74686174,   // 	that
        0x20746865,   // 	 the
        0x20476572,   // 	 Ger
        0x6d616e73,   // 	mans
        0x20776572,   // 	 wer
        0x65206d65,   // 	e me
        0x6e206f66,   // 	n of
        0x2061206d,   // 	 a m
        0x69676874,   // 	ight
        0x79206672,   // 	y fr
        0x616d6520,   // 	ame
        0x616e6420,   // 	and
        0x616e2069,   // 	an i
        0x6e637265,   // 	ncre
        0x6469626c,   // 	dibl
        0x65207661,   // 	e va
        0x6c6f7572,   // 	lour
        0x20616e64,   // 	and
        0x20736b69,   // 	ski
        0x6c6c2061,   // 	ll a
        0x74206172,   // 	t ar
        0x6d73204a,   // 	ms J
        0x756c6975,   // 	uliu
        0x73204361,   // 	s Ca
        0x65736172,   // 	esar
        0x00000000   // 	nop
};

#endif

#ifdef PROGRAMLOADOPT
uint32_t program_image[] = {4000,4000,0,0,0,50,0,0,0,0,
        0x00001025,     // 	move	v0,zero    <load_arrays>:                                                    PC = 10
        0x24060064,     // 	li	a2,100
        0x8c830000,     // 	lw	v1,0(a0)
        0x00621821,     // 	addu	v1,v1,v0
        0xac830000,     // 	sw	v1,0(a0)
        0x8ca30000,     // 	lw	v1,0(a1)
        0x00621821,     // 	addu	v1,v1,v0
        0xaca30000,     // 	sw	v1,0(a1)
        0x24420001,     // 	addiu	v0,v0,1
        0x24840004,     // 	addiu	a0,a0,4
        0x1446fff7,     // 	bne	v0,a2,400838 <load_arrays+0x8>                                                   PC = 20
        0x24a50004,     // 	addiu	a1,a1,4
        0x8d090f90,		//lw $t1, 3576($t0)
        0xad090018,		//sw $t1, 24($t0)
        0x8d080418,		//lw $t0, 1048($t0)
        0x03e00008,     // 	jr	ra
        0xac030018,     // 	sw v1, 24($zer0)
        0x00000000,     // 	nop
        0x00000000,     // 	nop
        0x00000000,     // 	nop
        0x00801825,    //  	move	v1,a0		<check_result>:                                                  PC = 30
        0x24870190,    // 	addiu	a3,a0,400
        0x00001025,    // 	move	v0,zero
        0x24080001,    // 	li	t0,1
        0x8c640000,    // 	lw	a0,0(v1)
        0x8ca60000,    // 	lw	a2,0(a1)
        0x00862026,    // 	xor	a0,a0,a2
        0x0104100b,    // 	movn	v0,t0,a0
        0x24630004,    // 	addiu	v1,v1,4
        0x1467fffa,    // 	bne	v1,a3,400878 <check_result+0x10>
        0x24a50004,    // 	addiu	a1,a1,4                                                                      PC = 40
        0xac02001c,		//sw $v0, 28($zero)
        0x8c18041c,		//lw $t8, 1052($zero)
        0xac030020,		//sw $v1, 32($zero)
        0x8c180420,		//lw $t8, 1056($zero)
        0x03e00008,    // 	jr	ra
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x00000000,    // 	nop
        0x27bdfcb0,    // 	addiu	sp,sp,-848   <main>:                                                           PC=50   BEGINNING OF THE PROGRAM
        0xafbf034c,    // 	sw	ra,844(sp)
        0xafb20348,    // 	sw	s2,840(sp)
        0xafb10344,    // 	sw	s1,836(sp)
        0xafb00340,    // 	sw	s0,832(sp)
//		0x3c1c0042,    // 	lui	gp,0x42
//		0x279c9010,    // 	addiu	gp,gp,-28656
//		0xafbc0010,    // 	sw	gp,16(sp)
//		0x8f928050,    // 	lw	s2,-32688(gp)
//		0x8e420000,    // 	lw	v0,0(s2)
        0xafa2033c,    // 	sw	v0,828(sp)
        0x27b101ac,    // 	addiu	s1,sp,428
        0x02202825,    // 	move	a1,s1
        0x27b0001c,    // 	addiu	s0,sp,28
        0x02002025,    // 	move	a0,s0
        0x0c00000a,    // 	jal	10 <load_arrays>                                                                   PC=60
        0x00000000,    // 	nop
//		0x8fbc0010,    // 	lw	gp,16(sp)
        0x02202825,    // 	move	a1,s1
        0x02002025,    // 	move	a0,s0
        0x0c00001e,    // 	jal	30 <check_result>
        0x00000000,    // 	nop
//		0x8fbc0010,    // 	lw	gp,16(sp)
        0x8fa4033c,    // 	lw	a0,828(sp)
        0x8e430000,    // 	lw	v1,0(s2)
        0x10830004,    // 	beq	a0,v1,400914 <main+0x78>
        0x8fbf034c,    // 	lw	ra,844(sp)
//		0x8f99804c,    // 	lw	t9,-32692(gp)
//		0x0320f809,    // 	jalr	t9
        0x00000000,    // 	nop                                                                                    PC=70
        0x8fb20348,    // 	lw	s2,840(sp)
        0x8fb10344,    // 	lw	s1,836(sp)
        0x8fb00340,    // 	lw	s0,832(sp)
        0x00000008,    // 	jr	$zero
        0x00000000,	   //
        0x00000000};   //                                                                                          PC=76
#endif

#ifdef PROGRAMLOADUNOPT
//un-optimzed program

unsigned int program_image[] = {4000,4000,0,0,0,120,0,0,0,0,
		0x27bdfff0,    // addiu	sp,sp,-16 <load_arrays>
		0xafbe000c,    // sw	s8,12(sp)
		0x03a0f025,    // move	s8,sp
		0xafc40010,    // sw	a0,16(s8)
		0xafc50014,    // sw	a1,20(s8)
		0xafc00004,    // sw	zero,4(s8)
		0x1000001c,    // b	4008bc <load_arrays+0x8c>
		0x00000000,    // nop
		0x8fc20004,    // lw	v0,4(s8)
		0x00021080,    // sll	v0,v0,0x2
		0x8fc30010,    // lw	v1,16(s8)
		0x00621021,    // addu	v0,v1,v0
		0x8fc30004,    // lw	v1,4(s8)
		0x00031880,    // sll	v1,v1,0x2
		0x8fc40010,    // lw	a0,16(s8)
		0x00831821,    // addu	v1,a0,v1
		0x8c640000,    // lw	a0,0(v1)
		0x8fc30004,    // lw	v1,4(s8)
		0x00831821,    // addu	v1,a0,v1
		0xac430000,    // sw	v1,0(v0)
		0x8fc20004,    // lw	v0,4(s8)
		0x00021080,    // sll	v0,v0,0x2
		0x8fc30014,    // lw	v1,20(s8)
		0x00621021,    // addu	v0,v1,v0
		0x8fc30004,    // lw	v1,4(s8)
		0x00031880,    // sll	v1,v1,0x2
		0x8fc40014,    // lw	a0,20(s8)
		0x00831821,    // addu	v1,a0,v1
		0x8c640000,    // lw	a0,0(v1)
		0x8fc30004,    // lw	v1,4(s8)
		0x00831821,    // addu	v1,a0,v1
		0xac430000,    // sw	v1,0(v0)
		0x8fc20004,    // lw	v0,4(s8)
		0x24420001,    // addiu	v0,v0,1
		0xafc20004,    // sw	v0,4(s8)
		0x8fc20004,    // lw	v0,4(s8)
		0x28420064,    // slti	v0,v0,100
		0x1440ffe2,    // bnez	v0,400850 <load_arrays+0x20>
		0x00000000,    // nop
		0x00000000,    // nop
		0x03c0e825,    // move	sp,s8
		0x8fbe000c,    // lw	s8,12(sp)
		0x27bd0010,    // addiu	sp,sp,16
		0x03e00008,    // jr	ra
		0x00000000,    // nop
		0x00000000,    // nop
		0x00000000,    // nop
		0x00000000,    // nop
		0x00000000,    // nop
		0x00000000,    // nop
		0x27bdffe8,    // 	addiu	sp,sp,-24 <check_result>
		0xafbe0014,    // sw	s8,20(sp)
		0x03a0f025,    // move	s8,sp
		0xafc40018,    // sw	a0,24(s8)
		0xafc5001c,    // sw	a1,28(s8)
		0xafc00000,    // sw	zero,0(s8)
		0xafc00008,    // sw	zero,8(s8)
		0x1000001d,    // b	400978 <check_result+0x94>
		0x00000000,    // nop
		0x8fc20008,    // lw	v0,8(s8)
		0x00021080,    // sll	v0,v0,0x2
		0x8fc30018,    // lw	v1,24(s8)
		0x00621021,    // addu	v0,v1,v0
		0x8c430000,    // lw	v1,0(v0)
		0x8fc20008,    // lw	v0,8(s8)
		0x00021080,    // sll	v0,v0,0x2
		0x8fc4001c,    // lw	a0,28(s8)
		0x00821021,    // addu	v0,a0,v0
		0x8c420000,    // lw	v0,0(v0)
		0x00621026,    // xor	v0,v1,v0
		0xafc2000c,    // sw	v0,12(s8)
		0x8fc2000c,    // lw	v0,12(s8)
		0x10400003,    // beqz	v0,40094c <check_result+0x68>
		0x00000000,    // nop
		0x24020001,    // li	v0,1
		0xafc20000,    // sw	v0,0(s8)
		0x8fc20008,    // lw	v0,8(s8)
		0x00021080,    // sll	v0,v0,0x2
		0x8fc30018,    // lw	v1,24(s8)
		0x00621021,    // addu	v0,v1,v0
		0x8c420000,    // lw	v0,0(v0)
		0x8fc30004,    // lw	v1,4(s8)
		0x00621021,    // addu	v0,v1,v0
		0xafc20004,    // sw	v0,4(s8)
		0x8fc20008,    // lw	v0,8(s8)
		0x24420001,    // addiu	v0,v0,1
		0xafc20008,    // sw	v0,8(s8)
		0x8fc20008,    // lw	v0,8(s8)
		0x28420064,    // slti	v0,v0,100
		0x1440ffe1,    // bnez	v0,400908 <check_result+0x24>
		0x00000000,    // nop
		0x8fc20000,    // lw	v0,0(s8)
		0x14400003,    // bnez	v0,40099c <check_result+0xb8>
		0x00000000,    // nop
		0x8fc20004,    // lw	v0,4(s8)
		0xafc20000,    // sw	v0,0(s8)
		0x00000000,    // nop
		0x03c0e825,    // move	sp,s8
		0x8fbe0014,    // lw	s8,20(sp)
		0x27bd0018,    // addiu	sp,sp,24
		0x03e00008,    // jr	ra
		0x00000000,    // nop
		0x00000000,    // nop
		0x00000000,    // nop
		0x00000000,    // nop
		0x00000000,    // nop
		0x00000000,    // nop
		0x00000000,    // nop
		0x00000000,    // nop
		0x00000000,    // nop
		0x27bdfcb8,    // addiu	sp,sp,-840 <main>
		0xafbf0344,    // sw	ra,836(sp)
		0xafbe0340,    // sw	s8,832(sp)
		0x03a0f025,    // move	s8,sp
//		0x3c1c0042,    // lui	gp,0x42
//		0x279c9010,    // addiu	gp,gp,-28656
//		0xafbc0010,    // sw	gp,16(sp)
//		0x8f828050,    // lw	v0,-32688(gp)
//		0x8c420000,    // lw	v0,0(v0)
//		0xafc2033c,    // sw	v0,828(s8)
		0x27c301ac,    // addiu	v1,s8,428
		0x27c2001c,    // addiu	v0,s8,28
		0x00602825,    // move	a1,v1
		0x00402025,    // move	a0,v0
		0x0c00000a,    // jal	10 <load_arrays>
		0x00000000,    // nop
//		0x8fdc0010,    // lw	gp,16(s8)
		0x27c301ac,    // addiu	v1,s8,428
		0x27c2001c,    // addiu	v0,s8,28
		0x00602825,    // move	a1,v1
		0x00402025,    // move	a0,v0
		0x0c00003c,    // jal	60 <check_result>
		0x00000000,    // nop
//		0x8fdc0010,    // lw	gp,16(s8)
		0x00000000,    // nop
//		0x8f828050,    // lw	v0,-32688(gp)
//		0x8fc3033c,    // lw	v1,828(s8)
//		0x8c420000,    // lw	v0,0(v0)
//		0x10620005,    // beq	v1,v0,400a3c <main+0x88>
		0x00000000,    // nop
//		0x8f82804c,    // lw	v0,-32692(gp)
//		0x0040c825,    // move	t9,v0
//		0x0320f809,    // jalr	t9
		0x00000000,    // nop
		0x03c0e825,    // move	sp,s8
		0x8fbf0344,    // lw	ra,836(sp)
		0x8fbe0340,    // lw	s8,832(sp)
		0x27bd0348,    // addiu	sp,sp,840
		0x00004020,		// add $t0, $zero, $zero
		0x8d090c44,		// lw $t1, 3140($t0)
		0xad090020,		// 2w $t1, 32($t0)
		0x8d080420,		//lw $t0, 1056($t0)
		0x8d090c4c,		// lw $t1, 3148($t0)
		0xad09001c,		// sw $t1, 28($t0)
		0x8d08041c,		//lw $t0, 1054($t0)
		0x8d090f90,		//lw $t1, 3984($t0)
		0xad090018,		//sw $t1, 24($t0)
		0x8d080418,		//lw $t0, 1048($t0)
		0x00000000,    // nop
		0x00000000,    // nop
		0x00000000,    // nop
		0x00000000,    // nop
		0x00000000,    // nop
		0x00000000,    // nop
		0x00000000,    // nop
		0x00000000,    // nop
		0x00000008,    // jr	$zero
		0x00000000,    // nop
		0x00000000,    // nop
		0x00000000,    // nop
		0x00000000,    // nop
		0x00000000};    // nop
#endif

const int inst_memory_size = sizeof(program_image) / sizeof(program_image[0]); //define size of program image
int32_t memory[1200] = {0}; //size of memory


/***********************************************************************************************************************

 FUNCTION NAME: Initialize_Simulation_Memory

 DESCRIPTION: Copies instruction machine code from program image to memory array (Adapted from Professor Graham's code)

 INPUTS: void

 OUTPUTS: void

***********************************************************************************************************************/

void Initialize_Simulation_Memory(void){

    for (int i=0; i < inst_memory_size; i++){

        memory[i] = program_image[i]; //push program_image into memory

    }
}

