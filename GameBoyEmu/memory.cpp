#include "memory.h"
/*
Byte cartridge_rom_0[0x4000];		// 0x0000 - 0x3FFF
Byte cartridge_rom[128][0x4000];	// 0x4000 - 0x7FFF
Byte video_ram[2][0x2000];			// 0x8000 - 0x9FFF
Byte catridge_ram[4][0x2000];		// 0xA000 - 0xBFFF
Byte work_ram_0[0x1000];			// 0xC000 - 0xCFFF
Byte work_ram[7][0x1000];			// 0xD000 - 0xDFFF
// echo of work ram					// 0xE000 - 0xFDFF
Byte sprite_attribute_table[0x100];	// 0xFE00 - 0xFE9F
Byte unusable_area[0x60];			// 0xFEA0 - 0xFEFF
Byte io[0x80];						// 0xFF00 - 0xFF7F
Byte high_ram[0x80];				// 0xFF80 - 0xFFFE
Byte interupt_enable_reg;			// 0xFFFF
*/


GZ80::Memory::Memory()
{
	memset(cartridge_rom_0, 0, 0x4000);
	memset(cartridge_rom, 0, 0x4000*128);
	memset(video_ram, 0, 0x2000 * 2);
	memset(cartridge_ram, 0, 0x2000 * 4);
	memset(work_ram_0, 0, 0x1000);
	memset(work_ram, 0, 0x1000 * 7);
	memset(sprite_attribute_table, 0, 0x100);
	memset(unusable_area, 0, 0x60);
	memset(io, 0, 0x80);
	memset(high_ram, 0, 0x7F);
	interupt_enable_reg = 0;
}

GZ80::Byte GZ80::Memory::read_from_address(Word address)
{
	switch (address >> 12)
	{
		case 0x0:
		case 0x1:
		case 0x2:
		case 0x3:
			return cartridge_rom_0[address];
		case 0x4:
		case 0x5:
		case 0x6:
		case 0x7:
			return cartridge_rom[cartridge_rom_bank_select][address - 0x4000];
		case 0x8:
		case 0x9:
			return video_ram[video_ram_select][address - 0x8000];
		case 0xA:
		case 0xB:
			return cartridge_ram[cartridge_ram_bank_select][address - 0xA000];
		case 0xC:
			return work_ram_0[address - 0xC000];
		case 0xD:
			return work_ram[work_ram_select][address - 0xD000];
		case 0xE:
			return work_ram_0[address - 0xE000];
		case 0xF:
		{
			if (address < 0xFE00)
				return work_ram[work_ram_select][address - 0xF000];
			else if (address < 0xFEA0)
				return sprite_attribute_table[address - 0xFE00];
			else if (address < 0xFF00)
				throw "Unusable memory region specified";
			else if (address < 0xFF80)
				return io[address - 0xFF00];
			else if (address < 0xFFFF)
				return high_ram[address - 0xFF80];
			else
				return interupt_enable_reg;
		}
		default:
			throw "Invalid memory location";
	}

}

void GZ80::Memory::write_to_address(Word address, Byte value)
{
	switch (address >> 12)
	{
		case 0x0:
		case 0x1:
		case 0x2:
		case 0x3:
			cartridge_rom_0[address] = value;
			break;
		case 0x4:
		case 0x5:
		case 0x6:
		case 0x7:
			cartridge_rom[cartridge_rom_bank_select][address - 0x4000] = value;
			break;
		case 0x8:
		case 0x9:
			video_ram[video_ram_select][address - 0x8000] = value;
			break;
		case 0xA:
		case 0xB:
			cartridge_ram[cartridge_ram_bank_select][address - 0xA000] = value;
			break;
		case 0xC:
			work_ram_0[address - 0xC000] = value;
			break;
		case 0xD:
			work_ram[work_ram_select][address - 0xD000] = value;
			break;
		case 0xE:
			work_ram_0[address - 0xE000] = value;
			break;
		case 0xF:
		{
			if (address < 0xFE00)
				work_ram[work_ram_select][address - 0xF000] = value;
			else if (address < 0xFEA0)
				sprite_attribute_table[address - 0xFE00] = value;
			else if (address < 0xFF00)
				throw "Unusable memory region specified";
			else if (address < 0xFF80)
				io[address - 0xFF00] = value;
			else if (address < 0xFFFF)
				high_ram[address - 0xFF80] = value;
			else
				interupt_enable_reg = value;
		} break;
		default:
			throw "Invalid memory location";
	}
}

void GZ80::Memory::set_video_ram_bank(Byte bank_number)
{
	video_ram_select = bank_number;
}

void GZ80::Memory::set_cartridge_ram_bank(Byte bank_number)
{
	cartridge_ram_bank_select = bank_number;
}

void GZ80::Memory::set_cartridge_rom_bank(Byte bank_number)
{
	cartridge_rom_bank_select = bank_number;
}
void GZ80::Memory::set_work_ram_bank(Byte bank_number)
{
	work_ram_select = bank_number;
}