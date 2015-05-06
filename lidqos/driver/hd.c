#include <kernel/hd.h>

void hd_rw(u32 lba, u8 com, void *buf)
{
	u16 sects_to_access = 1;
	u8 s = 0;
	u16 try_times = 0x10;
	do
	{
		void *buf2 = buf;
		u8 lba0 = (u8) (lba & 0xff);
		u8 lba1 = (u8) (lba >> 8 & 0xff);
		u8 lba2 = (u8) (lba >> 16 & 0xff);
		u8 lba3 = (u8) (lba >> 24 & 0xf);
		lba3 |= 0xe0; // 1110 0000

		while (inb_p(HD_PORT_STATUS) < 0)
		{
		}

		while ((inb_p(HD_PORT_STATUS) & 0xc0) != 0x40)
		{
		}

		outb_p(sects_to_access, HD_PORT_SECT_COUNT);
		outb_p(lba0, HD_PORT_LBA0);
		outb_p(lba1, HD_PORT_LBA1);
		outb_p(lba2, HD_PORT_LBA2);
		outb_p(lba3, HD_PORT_LBA3);
		outb_p(com, HD_PORT_COMMAND);

		while (inb_p(HD_PORT_STATUS) < 0)
		{
		}

		while ((inb_p(HD_PORT_STATUS) & 0xc0) != 0x40)
		{
		}

		if (com == HD_READ)
		{
			insl(buf2, HD_PORT_DATA, sects_to_access << 7);
		}
		else if (com == HD_WRITE)
		{
			outsl(buf2, HD_PORT_DATA, sects_to_access << 7);
		}
		s = inb_p(HD_PORT_STATUS);
		if (((com == HD_READ) && (s != 0x50)) || ((com == HD_WRITE) && (s != 0x90)))
		{

		}

		if (try_times-- == 0)
		{
			break;
		}
	}
	while (((com == HD_READ) && (s != 0x50)) || ((com == HD_WRITE) && (s != 0x90)));
}

void install_swap()
{
	u8 bitmap[0x200];
	for (int i = 0; i < 0x200; i++)
	{
		bitmap[i] = 0;
	}
	//map大小为： 4G / 4096 / 8 = 0x20000
	u32 bitmap_size = 0x20000;
	for (u32 j = 0; j < bitmap_size / 0x200; j++)
	{
		hd_rw(j, HD_WRITE, bitmap);
	}
}

u32 swap_alloc_sec()
{
	u8 bitmap[0x200];
	//map大小为： 4G / 4096 / 8 = 0x20000
	u32 bitmap_size = 0x20000;
	for (u32 j = 0; j < bitmap_size / 0x200; j++)
	{
		hd_rw(j, HD_READ, bitmap);
		for (u32 k = 0; k < 0x200; k++)
		{
			for (u32 l = 0; l < 8; l++)
			{
				if (((bitmap[k] >> l) & 0x1) == 0)
				{
					bitmap[k] |= (0x1 << l);
					hd_rw(j, HD_WRITE, bitmap);
					return k * 8 + l;
				}
			}
		}
	}
	return 0xffffffff;
}

void swap_free_sec(u32 sec_no)
{
	u8 bitmap[0x200];
	u32 ind = sec_no / 8 / 0x200;
	hd_rw(ind, HD_READ, bitmap);
	bitmap[sec_no / 8] |= (0x1 << sec_no % 8);
	hd_rw(ind, HD_WRITE, bitmap);
}

u32 swap_alloc_page()
{
	u32 sec_no = swap_alloc_sec();
	return sec_no;
}

void swap_write_page(u32 sec_no, void *page_data)
{
	//计算物理扇区号
	sec_no *= 8;
	//跳过map所在扇区
	sec_no += 0x100;

	//写入8个扇区
	for (int i = 0; i < 8; i++)
	{
		hd_rw(sec_no + i, HD_WRITE, page_data);
		page_data += 0x200;
	}
}

void swap_read_page(u32 sec_no, void *page_data)
{
	//计算物理扇区号
	sec_no *= 8;
	//跳过map所在扇区
	sec_no += 0x100;

	//读出8个扇区
	for (int i = 0; i < 8; i++)
	{
		hd_rw(sec_no + i, HD_READ, page_data);
		page_data += 0x200;
	}
}