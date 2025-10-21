/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/

// NOTE: golden standard code

#include "Instruction.h"

void add_reg_assm(void) {
	// Checking that the op code matches
	// strcmp(string1, string2) return 0 if they match
	if (strcmp(OP_CODE, "ADD") != 0) {
		// If the op code doesnt match, this isnt the correct command
		state = WRONG_COMMAND;
		return;
	}

	if (checkParams(REGISTER, REGISTER, REGISTER, EMPTY) == EXIT_FAILURE)
		return;

	setBits_easy(
		PART_LITERAL, "000000",
		PART_REGISTER, PARAM2.value,
		PART_REGISTER, PARAM3.value,
		PART_REGISTER, PARAM1.value,
		PART_LITERAL, "00000100000"
	);

	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void add_reg_bin(void) {
	// Check if the op code bits match
	// check_bits(start_bit, bit_string) returns 0 if the bit_string matches
	//  any x will be skipped
	// If the manual shows (0), then the value of that bit doesnt matter
	if (checkBits(31, "000000") != 0 || checkBits(5, "100000") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// If the op code bits match, then the rest can be read as correctly

	/*
		Finding values in the binary
	*/
	// getBits(start_bit, width)
	uint32_t Rd = getBits(15, 5);
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);


	/*
		Setting Instuciton values
	*/

	setOp("ADD");
	//setCond_num(cond);
	//setParam(param_num, param_type, param_value)
	setParam(1, REGISTER, Rd); //destination
	setParam(2, REGISTER, Rs); //first source register operand
	setParam(3, REGISTER, Rt); //second source register operand


	// tell the system the decoding is done
	state = COMPLETE_DECODE;
}


