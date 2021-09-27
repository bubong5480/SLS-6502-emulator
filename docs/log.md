# Project Log

You should use this file to document all your meetings and general progress/notes.

Each entry should have a date and assocaited notes eg.


## DATE: Mon Sept 13, 2021

### Notes
We could not meet since we don't exist as a group yet ... but hopefully soon ;-)
I am sure are project is going to be really cool!

### Progress

So far we have gotten nothing done

### Goals / Next steps

1. Meet each other and talk about what project we would like to do
2. Setup a meeting with the professor to chat about our project
3. Settle on the project
4. Starting writting up the proposal

## DATE: Mon Sept 27, 2021
### Meeting with professor

- WebAssembly as possible target, test it out

- Suggestions:
  1. Start with a simple loop for the FEL:
    - start with a simple cpu.c program and test fetch decode execute functions in loop
  2. Write a small z80/6502 assembly program (look for those CPUs manuals) for testing
  3. Hard code pc to some value,  and put one OPcode there in memory, to bootstrap our fetch
  4. Slowly build up the instruction set as you test out specific ROMs
  5. Consider memcpy on z80 page as an initial fixed program to test on
  6. Find a toolchain for the gameboy (assembler, or C compiler for it) so we could test our own program
  7. Start with a 8080 as a base - toolchains are easily accessible

- Things for cpu.c test program
  1. PC
  2. IR
  3. Address Buffer

- Kazojc 8080 datasheet, look it up
