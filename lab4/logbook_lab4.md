# Lab 4
## Task 1
> _UART communication with a host PC_

A design is provided (`lab4_task1.zip`) that allows a NIOSII to communicate with the host PC through a UART interface. The main difference of this design is the addition of **off-chip memory**, **extending the memory capacity** of the system.

Design in zip file:
![[lab4_design.png]]

The system also includes a ==PLL (Phase-Locked Loop)==.
![[pll_1.png]]
![[pll_2.png]]
- The PLL can **generate a signal whose phase is related to an input signal**. 
- Signals to/from off-chip memory exhibit considerable delays
	- Therefore a shifted version of the clock (phase shift) that drives the off-chip memory related to NIOS needs to be used
	- Allows the data a full clock cycle for registration.
- Note: For establishing UART communication between the host PC and NIOS, you typically do not need to add off-chip memory, this is just for example purposes.

There are two sides to the communication, the host side (`host.py`) and board side (`jtag-uart-test/software/task1/task1.c`). 
### Explanation of given code
<u>1. Host side code</u>
- sends signals to the board
- waits for a response
- processes the response

![[host_code.png]]

- The host program sends signals to the board, waits on a response and then processes the response. 
- The board side code polls the UART port for input. Board-Side Code (`jtag-uart-test/software/task1/task1.c`):
	- In this case, the host is simply printing the response from the board.
	- To see more interaction capabilities of the board, look at the DE_seven_segment_display.c file.

In this design, the NIOS processing is put into a slave mode, responding to commands sent out by the host.
- To enable this to work, the `hello_world_time_limited.sof` can be directly used to program the DE10-Lite board and will directly work for the code described below.

The board-side code performs the following steps:
1. Reads characters brought in
2. The running variable is used to keep the while loop running indefinitely until the QUITLETTER variable is sent along the JTAG/UART line.
4. Inside the while loop, `alt_getchar()` reads from the /dev/jtag_uart port by extracting a single character. This also stalls the processing until a new character is encountered.
5. After the first character is received the text buffer gets filled with the input a. The new character is checked if it is a quitting character and is added to the text buffer, incrementing the text index pointer.
6. After all operations with the character are done, the next character is read in, until a new line ‘\n’ character is encountered.
7. After reading in the input, the text is printed back out to the host terminal
    - A string is generated, being ended with the character 0x4. This character returns Ctrl+D up to the host to get the host terminal to terminate. This is important to ensure your host code can keep running.
    - The string is then printed to the host terminal.
    - The text buffer is finally emptied out so that it can be used for the next input. Most of the code for the rest of the course will be added inside the while loop between generate_text and `print_text` function as this is best place to react to the produced string and provide a response that will be passed back to the host.

Below is the task1.c code with each step highlighted out:
![[board_code.png]]

After building the code in Quartus and Eclipse, enter the command
`nios2-terminal.exe <<< hello` in the NIOS II terminal to see if the communication is working.

Output was:
![[nios_terminal_1.png]]

As expected, it detected the input hello, and counted 5 characters, exiting with Ctrl-D after the newline.

Next, I ran the host.py program.
![[nios_py_output.png]]

As seen above, it correctly detected the input sent by the host program; in this case, "test2".
![[input_host.png]]Most of the processing for the coursework will use variations of the perform_computation that will be used to send and receive data to and from the NIOS processor.
