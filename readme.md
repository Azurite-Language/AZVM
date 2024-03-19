# AZVM
Azurite Virtual Machine, interpreter for Azurite Bytecode.

## Usage
Place the bytecode named as "output.byte" in the same folder as the interpreter and run the interpreter (`./main`).

# Detailed Information
The virtual machine is stack based. The operations push and pop values from the stack.
The ISA contains a data stack as well as a callstack.
The data stack is used to store values and the callstack is used to store the return addresses of function calls.

## Instruction Set
### Overview
The instructions have a fixed lenght of 16 bytes.
`| Opcode (4 bytes) | Operand 1 (4 bytes) | Operand 2 (4 bytes) | Modifier (4 bytes) |`
#### Modifiers format
```
  31                                       4          2          0
 +-----------------------------------------+----------+----------+
 |             unused                      | OP2_Mode | OP1_Mode |
 +-----------------------------------------+----------+----------+
 ```

`OP1_Mode`: 
* 0b00: The operand is at the top of the stack, and will be popped.
* 0b01: `Operand 1` is a offset to the callstack's base pointer.
* 0b10: `Operand 1` is the absolute position of the value.

`OP2_Mode`: 
* 0x00: The operand is at the top of the stack, and will be popped.
* 0x01: `Operand 1` is a offset to the callstack's base pointer.
* 0x02: `Operand 1` is the absolute position of the value.

#### Push Order
The operation `a + b` will be pushed in the following order:

    +-----+ Lowest address
    |  a  |  |
    |  b  |  v
    +-----+ Highest address

When performing the operation, the second operand will be popped first.

### Instructions

#### PUSH (0x01)
Push the value of `Operand 1` onto the stack.

#### POP (0x02)
Pop the value from the stack and discard it.
