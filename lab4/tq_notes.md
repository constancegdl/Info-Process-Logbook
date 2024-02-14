# Workflow 
## Step 1: Platform Designer

Insert all the components of the system and make the connections between them. 

1. Choose all modules from the IP catalog tab. 
2. Rename them 
3. Make appropriate connections between the components within Platform Designer
4. External connections that connect the FPGA device pins to the PCB (example we want the led externam connection to be available, so we can take it as a output and use the leds on the board)
5. Assign Base Addresses: System -> Assign Base Address
6. Double click on the cpu component and select the Vectors tab. Set the reset vector memory and exception vector memory both to onchip_memory.s1. 
7. Save design
8. Click on the button Generate HDL 
9. Click Finish once generation is complete 

## Step 2: Bind together your PD system with Verilog Code 

Top level entity has a **top.v** file. 

1. If using a NIOS II cpu, then we need to open the **nios_inst.v** as generated from PD and then copy the declaration into the top file, under REG/WIRE declarations.

2. In the Quartus main window, go to Project -> Add/Remove Files in project. Click the ... button and then navigate to the right directory. Add the **nios_setup.qsys** files generated from the PD. 

The (.qip) file contains the information for the NIOS II PD system that we created in the last step. The (.v) file connects the PD system we made to the inputs and outputs of our board.

3. Click apply once you have added the file. 

4. Compile Design 

5. Run the programmer to download the **.sof** file to the board

## Step 3: Software Design 
1. Launch Eclipse from Quartus. 

2. Right click ibn the area called Project Explorer and select New -> Nios II Application and BSP from Template.

BSP is the Board Support Package that contains the drivers for things like translating "printf" C commands to the appropriate instructions to write to the terminal.

3. Choose the **.sopcinfo** file and choose Hello World Small as template. 

The .sopcinfo file informs Eclipse on what your PD system contains. 

Add your project name. 

Click Finish.

4. Double click the hello_world_small.c file and then replace the code or write your own code. 

5. Click on Save and then click on Build Project,. There should be a **.elf** file once the project is built successfully. 

## Step 4: Programmer and Terminal

Tools -> programmer

1. Change hardware setup to USB-Blaster 
2. Click on Change file and 

> **[Important]**
>
> **How to download the `.elf` file to the FPGA board using Terminal**
> In lab 4 you will be required to download the `.elf` file to the FPGA board and interact with the board using the terminal. The following steps show you how to do this:
>
> 1. Go to files -> 'This PC' ->  'skee' -> intelFPGA -> 18.1 -> nios2eds -> nios II command shell. 
>
> Then execute the line below: This will set up the environment for you to use the NIOS II tools.
>
>     ```powershell 
>     Nios II Command Shell.bat
>     ```
>
> 2. Then make sure to copy and paste the lab file into the 'skee' directory, use `nios2-download` to download the file to the FPGA board.
>
>    ```powershell
>    nios2-download -g <your_elf_file_name>.elf
>    ```
>
> Now you should be able to see the output of your program on the terminal.

Replace the existing code with 



