// SPDX-License-Identifier: GPL-2.0-or-later
/* Copyright (C) 2024 Toradex */

#include <init.h>
#include <asm/global_data.h>
#include <linux/errno.h>

#include "../common/tdx-cfg-block.h"

DECLARE_GLOBAL_DATA_PTR;

int board_init(void)
{
	return 0;
}

int board_phys_sdram_size(phys_size_t *size)
{
	if (!size)
		return -EINVAL;

	*size = get_ram_size((void *)PHYS_SDRAM, PHYS_SDRAM_SIZE + PHYS_SDRAM_2_SIZE);

	return 0;
}

#if IS_ENABLED(CONFIG_OF_LIBFDT) && IS_ENABLED(CONFIG_OF_BOARD_SETUP)
int ft_board_setup(void *blob, struct bd_info *bd)
{
	return ft_common_board_setup(blob, bd);
}
#endif
