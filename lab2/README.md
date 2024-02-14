In this lab we learn how to **Design a Nios II System**

- [Repo](https://github.com/Aaron-Zhao123/ELEC50009/tree/main/lab2)
- [Manual](https://github.com/Aaron-Zhao123/ELEC50009/blob/main/lab2/Hello_World_Lab_Manual_DE10_Lite.pdf)

### Task 1: Design

The _NIOS II_ is a _Soft Processor_, a processor designed to be implemented only with logic gates, so it can be run on an FPGA.
We can connect this processor to the peripherals themselves, and establish communications with the host PC.

First we need to use _Qsys_ (now called Quartus Platform Designer) to generate our hardware description.
This is a very slow and manual process, similar to wiring in System Verilog, but with a more visual interface.
Once you have added all the different peripherals, and specified their input and output ports, you make the connections between the different components and you assign the bases.

![Qsys Connections](content/Qsys%20Connections.png)

You can then generate your HDL.
The next step is to build the Top Level Design, in this case, our board `DE10_LITE_Golden_Top.v` , where `.v` describes Verilog Source Code.

Here, we just need to specify the connections to the peripherals, and give it the same name as our `.qsys` file:

```c
nyos_setup_v2 system (
		.button_external_connection_export(KEY[1:0]), // button_external_connection.export
		.clk_clk(MAX10_CLK1_50),                           //                        clk.clk
		.hex0_external_connection_export(HEX0),   //   hex0_external_connection.export
		.hex1_external_connection_export(HEX1),   //   hex1_external_connection.export
		.hex4_external_connection_export(HEX2),   //   hex4_external_connection.export
		.hex2_external_connection_export(HEX3),   //   hex2_external_connection.export
		.hex3_external_connection_export(HEX4),   //   hex3_external_connection.export
		.hex5_external_connection_export(HEX5),   //   hex5_external_connection.export
		.led_external_connection_export(LEDR[9:0]),    //    led_external_connection.export
		.reset_reset_n(1'b1),                     //                      reset.reset_n
		.switch_external_connection_export(SW[9:0])  // switch_external_connection.export
	);
```

Once we compile this, it will generate a set of files, of which we are interested in:

- `.sofcinfo` to generate our program.
- `.sof` to blast our board.

### Task2: Program

After blasting our board (_Tools -> Programmer_) we need to write the _C_ program that will be executed in the soft processor we just created.

For this we use _Tools -> Nios II Software build tools for Eclipse_. (Eclipse is just an IDE).

We open a new project, from _Hello World Small_ template.

We code this in _C_.
The `.sopcinfo` file contains all the details of our system (the peripherals I/O):

This way we can direcly access peripherals as if they were variables. You can find all the peripherals on the `system.h` file.

```c
BUTTON_BASE
LED_BASE
HEX0_BASE
```

Basic interactions are made using:

```C
variable = IOWR_ALTERA_AVALON_PIO_DATA(Location)
//gets the data from the specified Location and reads it into a variable

IOWR_ALTERA_AVALON_PIO_DATA(location, value) //writes the numeric Value to the given Location.
```

After we _Build Project_ we should get an `.elf` file.
If we have blasted the processor into the FPGA, we are ready to upload the `.elf` code and run it there.

_Run As -> Run Configurations_ and in _Target Connections_ you should refresh and get the board.

### Task3: Challenges

Make a something fun:

I made a game using the 2 HEX buttons:

You slide the aim to the left using button 0.
You shoot the target using button 1.

If you hit the target, your score will increase by 1 on the HEX display, and aiming will get increasingly more difficult.
Also, the target will move to a random location.

If you press buttons 0 and 1, the game will reset to it's initial state.

When coding this game, the main problems where related to having to execute the code with the soft processor, as I was not able to use external libraries to use functions like `delay()` or `sleep()` or `rand()`.

You can find the _C_ code in `lab2/content/Lab2Game.c`.

Aim and shoot + random target allocation:

![Video1](content/VID_20240213_145341-ezgif.com-video-to-gif-converter.gif)

Increasing speed with levels:

![Video2](content/ezgif.com-video-to-gif-converter%20(1).gif)

And reset:

![Video3](content/VID_20240213_145433-ezgif.com-video-to-gif-converter.gif
)
