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


## DATE: Mon Sept 30, 2021

### Notes
Met today to discuss what the project would entail. 

For now, we are awaiting the manuals on the SLS6502 machines.

In the meantime, some of us will be familiraizing ourselves with web assembly, and we will create a framework c file that would give a good outline of how we should implement the simulator. 

## DATE: Sun Oct 3, 2021

### Notes

Preliminary Makefile and 6502.c file created and pushed to master. 

### Progress

For prototype of the SLS6502
CPU is a struct with fields as registers. Memory is a char pointer; an array. Main currently does the following: initializes space for memory and cpu, continually switch/case, case 0xEA -> the 'no op" case

## DATE: Sun Oct 17, 2021

### Notes

Progress into 6502 program, discussion into the structure and organization of the CPU. Op codes and addressing mode implementation being started. Upon investigation of the manual and "cheat sheet," the introduction of addressing modes came up. Addressing modes are how and where the operation works. Further knowledge needs to be confirmed but this introduces more op codes because each addressing mode has its own op code. Flags were also introduced, plan is to make the status register a 8 bit integer, with masking as the mechanism to turn them on and off.

### Progress

LDA with the immediate and absolute addressing mode implemented in an addressing mode branch. Preliminary organization of op codes will stay switch cases at the moment.

### Goals

1. Someone still needs to print hello world in web assembly
2. Question op codes and addressing modes with Appavoo
3. Make some testing using binary images

### Goals

1. Speak with Appavoo about merging and git in general
2. Get the manuals
3. Someone needs to print hello world in web assembly




