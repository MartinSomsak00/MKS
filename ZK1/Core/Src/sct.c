// sct.c

#include "main.h"
#include "sct.h"

static const uint32_t reg_values[10] = {
// 7-segment display patterns for digits 0-9
		0b0111000000000111 << 16, // 0
		0b0100000000000001 << 16, // 1
		0b0011000000001011 << 16, // 2
		0b0110000000001011 << 16, // 3
		0b0100000000001101 << 16, // 4
		0b0110000000001110 << 16, // 5
		0b0111000000001110 << 16, // 6
		0b0100000000000011 << 16, // 7
		0b0111000000001111 << 16, // 8
		0b0110000000001111 << 16  // 9
};

void sct_init(void) {
	sct_led(0);
}

void sct_led(uint32_t value) {
	for (uint32_t i = 0; i < 32; i++) {
		HAL_GPIO_WritePin(SCT_SDI_GPIO_Port, SCT_SDI_Pin, (value >> i) & 1);
		HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 1);
		HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 0);
	}
		HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin, 1);
		HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin, 0);
}

void sct_value(uint8_t value) {
	uint32_t reg = 0;

	// Check if the value is within the valid range (0-9)
	if (value <= 9) {
		// Display the 7-segment pattern for the value
		reg |= reg_values[value];
	}

	sct_led(reg);
}
