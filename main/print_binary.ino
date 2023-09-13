void printBinaryByte(byte value)  {
  for (byte mask = 0x80; mask; mask >>= 1)  {
    u8g.print((mask & value) ? '1' : '0');
  }
}
