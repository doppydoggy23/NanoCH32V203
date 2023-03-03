
.equ LCD_WIDTH, 240
.equ LCD_HEIGHT, 240

.section .text
.globl updateBall
.align 4

#extern void updateBall(int *ballXPos, int *ballYPos, int ballWidth, int ballHeight, int *ballXDispp, int *ballYDispp);
# a0= pointer to ball X pos, a1=pointer to YPos, a2=ballWidth, a3=ballHeight, a4=pointer to Horiz. disp., a5=pointer to vert. disp.
updateBall:
	lw t0, 0(a0) # check if ball X Pos is zero
	bgtz t0, updateBallnoX0
	li t0, 1 # if it is, change Horiz. Disp. to 1
	sw t0, 0(a4)
updateBallnoX0:
	lw t0, 0(a1) # check if ball Y Pos is zero
	bgtz t0, updateBallnoY0
	li t0, 1 # if it is, change Vert. Disp. to 1
	sw t0, 0(a5)
updateBallnoY0:
	lw t0, 0(a0) # check for right screen border
	add t0, t0, a2
	li t1, LCD_WIDTH
	blt t0, t1, updateBallnoLCDW
	li t0, -1 # if it is hit, change horiz. displacement to -1
	sw t0, 0(a4)
updateBallnoLCDW:
	lw t0, 0(a1) # check for bottom screen border
	add t0, t0, a3
	li t1, LCD_HEIGHT
	blt t0, t1, updateBallnoLCDH
	li t0, -1 # if it is hit, change vertical disp. to -1
	sw t0, 0(a5)
updateBallnoLCDH:
	lw t0, 0(a0) # update ball X and Y pos according to displacements
	lw t1, 0(a4)
	add t0, t0, t1
	sw t0, 0(a0)
	;
	lw t0, 0(a1)
	lw t1, 0(a5)
	add t0, t0, t1
	sw t0, 0(a1)
exitupdateBall:
	ret
