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

		DIV = 0xFF04,	/* Divider Register (R/W)
						This register is incremented 16384
						(~16779 on SGB) times a second. Writing
						any value sets it to $00.*/

		TIME = 0xFF05,	/* Timer counter(R / W)
						This timer is incremented by a clock
						frequency specified by the TAC register
						($FF07).The timer generates an interrupt
						when it overflows. */

		TMA = 0xFF06,	/* Timer Modulo (R/W)
						When the TIMA overflows, this data will
						be loaded. */

		TAC = 0xFF07,	/* Timer Control (R/W)
						Bit 2 - Timer Stop
							0: Stop Timer
							1: Start Timer
						Bits 1+0 - Input Clock Select
							00: 4.096 KHz (~4.194 KHz SGB)
							01: 262.144 Khz (~268.4 KHz SGB)
							10: 65.536 KHz (~67.11 KHz SGB)
							11: 16.384 KHz (~16.78 KHz SGB) */

		IF = 0xFF0F,	/* Interrupt Flag (R/W)
						Bit 4: Transition from High to Low of Pin
							number P10-P13
						Bit 3: Serial I/O transfer complete
						Bit 2: Timer Overflow
						Bit 1: LCDC (see STAT)
						Bit 0: V-Blank */
		NR10 = 0xFF10,	/* Sound Mode 1 register,
						Sweep register (R/W)
						Bit 6-4 - Sweep Time
						Bit 3 - Sweep Increase/Decrease
							0: Addition (frequency increases)
							1: Subtraction (frequency decreases)
						Bit 2-0 - Number of sweep shift (n: 0-7)
						Sweep Time:
							000: sweep off - no freq change
							001: 7.8 ms (1/128Hz)
							010: 15.6 ms (2/128Hz)
							011: 23.4 ms (3/128Hz)
							100: 31.3 ms (4/128Hz)
							101: 39.1 ms (5/128Hz)
							110: 46.9 ms (6/128Hz)
							111: 54.7 ms (7/128Hz) */

		NR11 = 0xFF11,	/* Sound Mode 1 register, Sound length/Wave
						pattern duty (R/W)
						Only Bits 7-6 can be read.
							Bit 7-6 - Wave Pattern Duty
							Bit 5-0 - Sound length data (t1: 0-63) 
						Wave Duty: (default: 10)
							00: 12.5%	( _--------_--------_-------- )
							01: 25%		( __-------__-------__------- )
							10: 50%		( ____-----____-----____----- )
							11: 75%		( ______---______---______--- ) */

		NR12 = 0xFF12,	/* Sound Mode 1 register, Envelope (R/W)
						Bit 7-4 - Initial volume of envelope
						Bit 3 - Envelope UP/DOWN
							0: Attenuate
							1: Amplify
						Bit 2-0 - Number of envelope sweep
							(n: 0-7) (If zero, stop
							envelope operation.)
						Initial volume of envelope is from 0 to
						$F. Zero being no sound.
						Length of 1 step = n*(1/64) seconds */

		NR13 = 0xFF13,	/* Sound Mode 1 register, Frequency lo (W)
						Lower 8 bits of 11 bit frequency (x).
						Next 3 bit are in NR 14 ($FF14) */

		NR14 = 0xFF14,	/* Sound Mode 1 register, Frequency hi (R/W)
						Only Bit 6 can be read.
						Bit 7 - Initial (when set, sound
								restarts)
						Bit 6 - Counter/consecutive selection
						Bit 2-0 - Frequency's higher 3 bits (x)
						Frequency	= 4194304/(32*(2048-x)) Hz
									= 131072/(2048-x) Hz
						Counter/consecutive Selection
						0 = Regardless of the length data in
							NR11 sound can be produced
							consecutively.
						1 = Sound is generated during the time
							period set by the length data in
							NR11. After this period the sound 1
							ON flag (bit 0 of NR52) is reset. */

		NR21 = 0xFF16,	/* Sound Mode 2 register, Sound Length; Wave
						Pattern Duty (R/W) 
						Bit meanings same as Sound Mode 1 */

		NR22 = 0xFF17,	/* Sound Mode 2 register, envelope (R/W) 
						Bit meanings same as Sound Mode 2*/

		NR23 = 0xFF18,	/* Sound Mode 2 register, frequency
						lo data (W)
						Frequency's lower 8 bits of 11 bit data
						(x). Next 3 bits are in NR 24 ($FF19) */

		NR24 = 0xFF19,	/* Sound Mode 2 register, frequency
						hi data (R/W) */

		NR30 = 0xFF1A,	/* Sound Mode 3 register, Sound on/off (R/W)
						Only bit 7 can be read
						Bit 7 - Sound OFF
							0: Sound 3 output stop
							1: Sound 3 output OK */

		NR31 = 0x0FF1B,	/* Sound Mode 3 register, sound length (R/W)
						Bit 7-0 - Sound length (t1: 0 - 255)
						Sound Length = (256-t1)*(1/2) seconds */

		NR32 = 0xFF1C,	/* Sound Mode 3 register, Select output
						level (R/W)
						Only bits 6-5 can be read
						Bit 6-5 - Select output level
							00: Mute
							01: Produce Wave Pattern RAM
								Data as it is(4 bit length)
							10: Produce Wave Pattern RAM
								data shifted once to the
								RIGHT (1/2) (4 bit length)
							11: Produce Wave Pattern RAM
								data shifted twice to the
								RIGHT (1/4) (4 bit length)
						* - Wave Pattern RAM is located from $FF30-$FF3f. */

		NR33 = 0xFF1D,	/* Sound Mode 3 register, frequency's
						lower data (W)
						Lower 8 bits of an 11 bit frequency (x). */

		NR34 = 0xFF1E,	/* Sound Mode 3 register, frequency's
						higher data (R/W)
						Only bit 6 can be read. 
						Bit 7 - Initial (when set,sound restarts)
						Bit 6 - Counter/consecutive flag
						Bit 2-0 - Frequency's higher 3 bits (x).
						Frequency	= 4194304/(64*(2048-x)) Hz
									= 65536/(2048-x) Hz
						Counter/consecutive Selection
							0 = Regardless of the length data in
								NR31 sound can be produced
								consecutively.
							1 = Sound is generated during the time
								period set by the length data in
								NR31. After this period the sound 3
								ON flag (bit 2 of NR52) is reset. */
		
		NR41 = 0xFF20,	/* Sound Mode 4 register, sound length (R/W)
						Bit 5-0 - Sound length data (t1: 0-63)
						Sound Length = (64-t1)*(1/256) seconds */

		NR42 = 0xFF21,	/* Sound Mode 4 register, envelope (R/W)
						Bit 7-4 - Initial volume of envelope
						Bit 3 - Envelope UP/DOWN
							0: Attenuate
							1: Amplify
						Bit 2-0 - Number of envelope sweep
							(n: 0-7) (If zero, stop
							envelope operation.)
						Initial volume of envelope is from 0 to
						$F. Zero being no sound.
						Length of 1 step = n*(1/64) seconds */

		NR43 = 0xFF22,	/* Sound Mode 4 register, polynomial
						counter (R/W)
						Bit 7-4 - Selection of the shift clock
								frequency of the polynomial
								counter
						Bit 3 - Selection of the polynomial
								counter's step
						Bit 2-0 - Selection of the dividing ratio
								of frequencies:
									000: f * 1/2^3 * 2
									001: f * 1/2^3 * 1
									010: f * 1/2^3 * 1/2
									011: f * 1/2^3 * 1/3
									100: f * 1/2^3 * 1/4
									101: f * 1/2^3 * 1/5
									110: f * 1/2^3 * 1/6
									111: f * 1/2^3 * 1/7
									f = 4.194304 Mhz
						Selection of the polynomial counter step:
						0: 15 steps
						1: 7 steps
						Selection of the shift clock frequency of
						the polynomial counter:
						0000: dividing ratio of frequencies * 1/2
						0001: dividing ratio of frequencies * 1/2^2
						0010: dividing ratio of frequencies * 1/2^3
						0011: dividing ratio of frequencies * 1/2^4
						: :
						: :
						: :
						0101: dividing ratio of frequencies * 1/2^14
						1110: prohibited code
						1111: prohibited code */

		NR44 = 0xFF23,	/* Sound Mode 4 register,
						counter/consecutive; inital (R/W)
						Only bit 6 can be read.
						Bit 7 - Initial (when set, sound restarts)
						Bit 6 - Counter/consecutive selection
						Counter/consecutive Selection
							0 = Regardless of the length data in NR41
								sound can be produced consecutively.
							1 = Sound is generated during the time
								period set by the length data in NR41.
								After this period the sound 4 ON flag
								(bit 3 of NR52) is reset. */

		NR50 = 0xFF24,	/* Channel control / ON-OFF / Volume (R/W)
						Bit 7 - Vin->SO2 ON/OFF
						Bit 6-4 - SO2 output level (volume) (# 0-7)
						Bit 3 - Vin->SO1 ON/OFF
						Bit 2-0 - SO1 output level (volume) (# 0-7)
						Vin->SO1 (Vin->SO2)
						By synthesizing the sound from sound 1
						through 4, the voice input from Vin
						terminal is put out.
							0: no output
							1: output OK */

		NR51 = 0xFF25,	/* Selection of Sound output terminal (R/W)
						Bit 7 - Output sound 4 to SO2 terminal
						Bit 6 - Output sound 3 to SO2 terminal
						Bit 5 - Output sound 2 to SO2 terminal
						Bit 4 - Output sound 1 to SO2 terminal
						Bit 3 - Output sound 4 to SO1 terminal
						Bit 2 - Output sound 3 to SO1 terminal
						Bit 1 - Output sound 2 to SO1 terminal
						Bit 0 - Output sound 1 to SO1 terminal */

		NR52 = 0xFF26,	/* Sound on/off (R/W)
						Bit 7 - All sound on/off
								0: stop all sound circuits
								1: operate all sound circuits
						Bit 3 - Sound 4 ON flag
						Bit 2 - Sound 3 ON flag
						Bit 1 - Sound 2 ON flag
						Bit 0 - Sound 1 ON flag
						Bits 0 - 3 of this register are meant to
						be status bits to be read. Writing to
						these bits does NOT enable/disable
						sound.
						If your GB programs don't use sound then
						write $00 to this register to save 16%
						or more on GB power consumption. */

		WPRAM0 = 0xFF30;/* Waveform storage for arbitrary sound data
						This storage area holds 32 4-bit samples
						that are played back upper 4 bits first */
		

}