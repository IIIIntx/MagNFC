/*
 * GENERATED FILE - DO NOT EDIT
 * Copyright 2008-2013 Code Red Technologies Ltd,
 * Copyright 2013-2025 NXP
 * Generated linker script file for Generic-M0plus
 * Created from memory.ldt by FMCreateLinkMemory
 * Using Freemarker v2.3.30
 * MCUXpresso IDE v11.10.0 [Build 3148] [2024-07-03] on 2025年6月23日 下午4:16:35
 */

MEMORY
{
  /* Define each memory region */
  Flash_00 (rx) : ORIGIN = 0x0, LENGTH = 0x7800 /* 30K bytes (alias Flash) */  
  RamLoc (rwx) : ORIGIN = 0x10000000, LENGTH = 0x1ff0 /* 8176 bytes (alias RAM) */  
}

  /* Define a symbol for the top of each memory region */
  __base_Flash_00 = 0x0  ; /* Flash_00 */  
  __base_Flash = 0x0 ; /* Flash */  
  __top_Flash_00 = 0x0 + 0x7800 ; /* 30K bytes */  
  __top_Flash = 0x0 + 0x7800 ; /* 30K bytes */  
  __base_RamLoc = 0x10000000  ; /* RamLoc */  
  __base_RAM = 0x10000000 ; /* RAM */  
  __top_RamLoc = 0x10000000 + 0x1ff0 ; /* 8176 bytes */  
  __top_RAM = 0x10000000 + 0x1ff0 ; /* 8176 bytes */  
