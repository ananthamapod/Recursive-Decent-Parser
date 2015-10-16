/*
 *********************************************
 *  314 Principles of Programming Languages  *
 *  Fall 2014                                *
 *********************************************
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "InstrUtils.h"
#include "Utils.h"

#define EMPTY_FIELD 0xFFFFF

int main()
{
	Instruction *head;
	Instruction *instr1, *instr2, *instr3;
	int opt_flag, opt_calc;


	head = ReadInstructionList(stdin);

        /* ---  FIRST: ALGEBRAIC SIMPLIFICATION PASS --- */

	if (!head) {
		ERROR("No instructions\n");
		exit(EXIT_FAILURE);
	}

	/* YOUR CODE GOES HERE */
	instr1 = head;
	instr2 = head->next;
	while(instr2) {
		instr3 = instr2->next;
		if(instr3) {
			switch(instr3->opcode) {
				case ADD:
					if((instr1->opcode == LOADI||instr1->opcode == LOAD)&&(instr2->opcode == LOADI||instr2->opcode == LOAD)) {
						if((instr1->field1 == instr3->field2||instr1->field1 == instr3->field3)&&(instr2->field1 == instr3->field2||instr2->field1 == instr3->field3)) {
							if(instr1->field2 == 0||instr2->field2 == 0) {
								instr3->opcode = LOADI;
								if(instr1->field2 == 0) {
									instr3->field2 = instr2->field2;
								} else {
									instr3->field2 = instr1->field2;
								}
								instr3->field3 = EMPTY_FIELD;
								if(instr1->prev) {
									(instr1->prev)->next = instr3;
									instr3->prev = instr1->prev;
									free(instr1);
									free(instr2);
									instr1 = instr3;
									instr2 = instr3->next;
									continue;
								} else {
									head = instr3;
									instr3->prev = NULL;
									free(instr1);
									free(instr2);
									instr1 = instr3;
									instr2 = instr3->next;
									continue;
								}
							}
						}
					}
					break;
				case SUB:
					if((instr1->opcode == LOADI||instr1->opcode == LOAD)&&(instr2->opcode == LOADI||instr2->opcode == LOAD)) {
						if((instr1->field1 == instr3->field3)&&(instr2->field1 == instr3->field2)) {
							if(instr1->field2 == 0) {
								instr3->opcode = LOADI;
								instr3->field2 = instr2->field2;
								instr3->field3 = EMPTY_FIELD;
								if(instr1->prev) {
									(instr1->prev)->next = instr3;
									instr3->prev = instr1->prev;
									free(instr1);
									free(instr2);
									instr1 = instr3;
									instr2 = instr3->next;
									continue;
								} else {
									head = instr3;
									instr3->prev = NULL;
									free(instr1);
									free(instr2);
									instr1 = instr3;
									instr2 = instr3->next;
									continue;
								}
							}
						} else if((instr1->field1 == instr3->field2)&&(instr2->field1 == instr3->field3)) {
							if(instr2->field2 == 0) {
								instr3->opcode = LOADI;
								instr3->field2 = instr1->field2;
								instr3->field3 = EMPTY_FIELD;
								if(instr1->prev) {
									(instr1->prev)->next = instr3;
									instr3->prev = instr1->prev;
									free(instr1);
									free(instr2);
									instr1 = instr3;
									instr2 = instr3->next;
									continue;
								} else {
									head = instr3;
									instr3->prev = NULL;
									free(instr1);
									free(instr2);
									instr1 = instr3;
									instr2 = instr3->next;
									continue;
								}
							}	
						}
					} else if(instr3->field2 == instr3->field3) {
						instr3->opcode = LOADI;
						instr3->field2 = 0;
						instr3->field3 = EMPTY_FIELD;
					}
					break;
				case MUL:
					if((instr1->opcode == LOADI||instr1->opcode == LOAD)&&(instr2->opcode == LOADI||instr2->opcode == LOAD)) {
						if((instr1->field1 == instr3->field2||instr1->field1 == instr3->field3)&&(instr2->field1 == instr3->field2||instr2->field1 == instr3->field3)) {
							if(instr1->field2 == 0||instr2->field2 == 0) {
								instr3->opcode = LOADI;
								instr3->field2 = 0;
								instr3->field3 = EMPTY_FIELD;
								if(instr1->prev) {
									(instr1->prev)->next = instr3;
									instr3->prev = instr1->prev;
									free(instr1);
									free(instr2);
									instr1 = instr3;
									instr2 = instr3->next;
									continue;
								} else {
									head = instr3;
									instr3->prev = NULL;
									free(instr1);
									free(instr2);
									instr1 = instr3;
									instr2 = instr3->next;
									continue;
								}
							} else if(instr1->field2 == 1||instr2->field2 == 1) {
								instr3->opcode = LOADI;
								if(instr1->field2 == 1) {
									instr3->field2 = instr2->field2;
								} else {
									instr3->field2 = instr1->field2;
								}
								instr3->field3 = EMPTY_FIELD;
								if(instr1->prev) {
									(instr1->prev)->next = instr3;
									instr3->prev = instr1->prev;
									free(instr1);
									free(instr2);
									instr1 = instr3;
									instr2 = instr3->next;
									continue;
								} else {
									head = instr3;
									instr3->prev = NULL;
									free(instr1);
									free(instr2);
									instr1 = instr3;
									instr2 = instr3->next;
									continue;
								}
							}
						}
					}
				default:
					;
			}
		}
		instr1 = instr2;
		instr2 = instr3;
	}
	
        /* --- SECOND: CONSTANT FOLDING PASS --- */

	if (!head) {
		ERROR("No instructions\n");
		exit(EXIT_FAILURE);
	}

	/* YOUR CODE GOES HERE */
	instr1 = head;
	instr2 = head->next;
	while(instr2) {
		instr3 = instr2->next;
		if(instr3) {
			if(instr1->opcode == LOADI && instr2->opcode == LOADI) {
				if((instr1->field1 == instr3->field2||instr1->field1 == instr3->field3)&&(instr2->field1 == instr3->field2||instr2->field1 == instr3->field3)) {
					int result;
					switch(instr3->opcode) {
						case ADD:
							result = instr1->field2 + instr2->field2;
							break;
						case SUB:
							result = instr1->field2 - instr2->field2;
							break;
						case MUL:
							result = instr1->field2 * instr2->field2;
							break;
						default:
							instr1 = instr2;
							instr2 = instr3;
							continue;
					}
					instr3->opcode = LOADI;
					instr3->field2 = result;
					if(instr1->prev) {
						(instr1->prev)->next = instr3;
						instr3->prev = instr1->prev;
						free(instr1);
						free(instr2);
						instr1 = instr3;
						instr2 = instr3->next;
						continue;
					} else {
						head = instr3;
						instr3->prev = NULL;
						free(instr1);
						free(instr2);
						instr1 = instr3;
						instr2 = instr3->next;
						continue;
					}
				}
			}
		}
		instr1 = instr2;
		instr2 = instr3;
	}

	PrintInstructionList(stdout, head);
	DestroyInstructionList(head);
	return EXIT_SUCCESS;
}
