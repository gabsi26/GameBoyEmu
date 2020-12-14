#pragma once
#include <cstdint>

namespace GZ80
{
	using Word = uint16_t;
	static constexpr Word
		P1 = 0xFF00,	/* P1: Register for reading joy pad info and determining system type
						Bit 7 - Not used
						Bit 6 - Not used
						Bit 5 - P15 out port
						Bit 4 - P14 out port
						Bit 3 - P13 in port
						Bit 2 - P12 in port
						Bit 1 - P11 in port
						Bit 0 - P10 in port */
		SB = 0xFF01,	// Serial transfer data 
		SC = 0xFF02,	/* SIO control
						Bit 7 - Transfer Start Flag
							0: Non transfer
							1: Start transfer
						Bit 0 - Shift Clock
							0: External Clock (500KHz Max.)
							1: Internal Clock (8192Hz) */
		DIV = 0xFF04;	/* Divider Register (R/W)
						This register is incremented 16384
						(~16779 on SGB) times a second. Writing
						any value sets it to $00.*/
}