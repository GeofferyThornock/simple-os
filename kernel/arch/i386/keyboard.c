#include <kernel/isr.h>
#include <kernel/pic.h>
#include <kernel/io.h>
#include <stdio.h>
#include <kernel/keyboard.h>
#include <stdlib.h>

/*
char scancode_list[128] = {
    0x00, // 0x00 - Invalid
    0x00, // 0x01 - Escape
    '1',  // 0x02 - 1
    '2',  // 0x03 - 2
    '3',  // 0x04 - 3
    '4',  // 0x05 - 4
    '5',  // 0x06 - 5
    '6',  // 0x07 - 6
    '7',  // 0x08 - 7
    '8',  // 0x09 - 8
    '9',  // 0x0A - 9
    '0',  // 0x0B - 0
    '-',  // 0x0C - Minus
    '=',  // 0x0D - Equals
    0x08, // 0x0E - Backspace
    0x09, // 0x0F - Tab
    'q',  // 0x10 - Q
    'w',  // 0x11 - W
    'e',  // 0x12 - E
    'r',  // 0x13 - R
    't',  // 0x14 - T
    'y',  // 0x15 - Y
    'u',  // 0x16 - U
    'i',  // 0x17 - I
    'o',  // 0x18 - O
    'p',  // 0x19 - P
    '[',  // 0x1A - Left bracket
    ']',  // 0x1B - Right bracket
    0x0D, // 0x1C - Enter
    0x00, // 0x1D - Left Ctrl
    'a',  // 0x1E - A
    's',  // 0x1F - S
    'd',  // 0x20 - D
    'f',  // 0x21 - F
    'g',  // 0x22 - G
    'h',  // 0x23 - H
    'j',  // 0x24 - J
    'k',  // 0x25 - K
    'l',  // 0x26 - L
    ';',  // 0x27 - Semicolon
    '\'', // 0x28 - Apostrophe
    '`',  // 0x29 - Grave accent
    0x00, // 0x2A - Left Shift
    '\\', // 0x2B - Backslash
    'z',  // 0x2C - Z
    'x',  // 0x2D - X
    'c',  // 0x2E - C
    'v',  // 0x2F - V
    'b',  // 0x30 - B
    'n',  // 0x31 - N
    'm',  // 0x32 - M
    ',',  // 0x33 - Comma
    '.',  // 0x34 - Period
    '/',  // 0x35 - Slash
    0x00, // 0x36 - Right Shift
    '*',  // 0x37 - Keypad *
    0x00, // 0x38 - Left Alt
    ' ',  // 0x39 - Space
    0x00, // 0x3A - Caps Lock
    0x00, // 0x3B - F1
    0x00, // 0x3C - F2
    0x00, // 0x3D - F3
    0x00, // 0x3E - F4
    0x00, // 0x3F - F5
    0x00, // 0x40 - F6
    0x00, // 0x41 - F7
    0x00, // 0x42 - F8
    0x00, // 0x43 - F9
    0x00, // 0x44 - F10
    0x00, // 0x45 - Num Lock
    0x00, // 0x46 - Scroll Lock
    '7',  // 0x47 - Keypad 7 / Home
    '8',  // 0x48 - Keypad 8 / Up
    '9',  // 0x49 - Keypad 9 / PgUp
    '-',  // 0x4A - Keypad -
    '4',  // 0x4B - Keypad 4 / Left
    '5',  // 0x4C - Keypad 5
    '6',  // 0x4D - Keypad 6 / Right
    '+',  // 0x4E - Keypad +
    '1',  // 0x4F - Keypad 1 / End
    '2',  // 0x50 - Keypad 2 / Down
    '3',  // 0x51 - Keypad 3 / PgDn
    '0',  // 0x52 - Keypad 0 / Insert
    '.',  // 0x53 - Keypad . / Delete
    0x00, // 0x54 - Alt-SysRq
    0x00, // 0x55 - Reserved
    0x00, // 0x56 - Non-US \ or |
    0x00, // 0x57 - F11
    0x00, // 0x58 - F12
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x59-0x60 - Reserved
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x61-0x68 - Reserved
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x69-0x70 - Reserved
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x71-0x78 - Reserved
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  // 0x79-0x80 - Reserved
};

char scancode_list_shift[128] = {
    0x00, // 0x00 - Invalid
    0x00, // 0x01 - Escape
    '!',  // 0x02 - 1 -> !
    '@',  // 0x03 - 2 -> @
    '#',  // 0x04 - 3 -> #
    '$',  // 0x05 - 4 -> $
    '%',  // 0x06 - 5 -> %
    '^',  // 0x07 - 6 -> ^
    '&',  // 0x08 - 7 -> &
    '*',  // 0x09 - 8 -> *
    '(',  // 0x0A - 9 -> (
    ')',  // 0x0B - 0 -> )
    '_',  // 0x0C - Minus -> _
    '+',  // 0x0D - Equals -> +
    0x08, // 0x0E - Backspace
    0x09, // 0x0F - Tab
    'Q',  // 0x10 - Q
    'W',  // 0x11 - W
    'E',  // 0x12 - E
    'R',  // 0x13 - R
    'T',  // 0x14 - T
    'Y',  // 0x15 - Y
    'U',  // 0x16 - U
    'I',  // 0x17 - I
    'O',  // 0x18 - O
    'P',  // 0x19 - P
    '{',  // 0x1A - Left bracket -> {
    '}',  // 0x1B - Right bracket -> }
    0x0D, // 0x1C - Enter
    0x00, // 0x1D - Left Ctrl
    'A',  // 0x1E - A
    'S',  // 0x1F - S
    'D',  // 0x20 - D
    'F',  // 0x21 - F
    'G',  // 0x22 - G
    'H',  // 0x23 - H
    'J',  // 0x24 - J
    'K',  // 0x25 - K
    'L',  // 0x26 - L
    ':',  // 0x27 - Semicolon -> :
    '"',  // 0x28 - Apostrophe -> "
    '~',  // 0x29 - Grave accent -> ~
    0x00, // 0x2A - Left Shift
    '|',  // 0x2B - Backslash -> |
    'Z',  // 0x2C - Z
    'X',  // 0x2D - X
    'C',  // 0x2E - C
    'V',  // 0x2F - V
    'B',  // 0x30 - B
    'N',  // 0x31 - N
    'M',  // 0x32 - M
    '<',  // 0x33 - Comma -> <
    '>',  // 0x34 - Period -> >
    '?',  // 0x35 - Slash -> ?
    0x00, // 0x36 - Right Shift
    '*',  // 0x37 - Keypad *
    0x00, // 0x38 - Left Alt
    ' ',  // 0x39 - Space
    0x00, // 0x3A - Caps Lock
    // F-keys and remaining entries same as unshifted
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x3B-0x44
    0x00, 0x00, // 0x45-0x46
    '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.', // 0x47-0x53
    // Rest are reserved/unused
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

*/


char scancode_list[128] = {
    0x00, // 0x00 - Invalid
    0x00, // 0x01 - Escape
    '1',  // 0x02 - 1
    '2',  // 0x03 - 2
    '3',  // 0x04 - 3
    '4',  // 0x05 - 4
    '5',  // 0x06 - 5
    '6',  // 0x07 - 6
    '7',  // 0x08 - 7
    '8',  // 0x09 - 8
    '9',  // 0x0A - 9
    '0',  // 0x0B - 0
    '[',  // 0x0C - Minus -> [ in Dvorak
    ']',  // 0x0D - Equals -> ] in Dvorak
    0x08, // 0x0E - Backspace
    0x09, // 0x0F - Tab
    '\'', // 0x10 - Q -> ' in Dvorak
    ',',  // 0x11 - W -> , in Dvorak
    '.',  // 0x12 - E -> . in Dvorak
    'p',  // 0x13 - R -> p in Dvorak
    'y',  // 0x14 - T -> y in Dvorak
    'f',  // 0x15 - Y -> f in Dvorak
    'g',  // 0x16 - U -> g in Dvorak
    'c',  // 0x17 - I -> c in Dvorak
    'r',  // 0x18 - O -> r in Dvorak
    'l',  // 0x19 - P -> l in Dvorak
    '/',  // 0x1A - Left bracket -> / in Dvorak
    '=',  // 0x1B - Right bracket -> = in Dvorak
    0x0D, // 0x1C - Enter
    0x00, // 0x1D - Left Ctrl
    'a',  // 0x1E - A -> a in Dvorak (same)
    'o',  // 0x1F - S -> o in Dvorak
    'e',  // 0x20 - D -> e in Dvorak
    'u',  // 0x21 - F -> u in Dvorak
    'i',  // 0x22 - G -> i in Dvorak
    'd',  // 0x23 - H -> d in Dvorak
    'h',  // 0x24 - J -> h in Dvorak
    't',  // 0x25 - K -> t in Dvorak
    'n',  // 0x26 - L -> n in Dvorak
    's',  // 0x27 - Semicolon -> s in Dvorak
    '-',  // 0x28 - Apostrophe -> - in Dvorak
    '`',  // 0x29 - Grave accent (same)
    0x00, // 0x2A - Left Shift
    '\\', // 0x2B - Backslash (same)
    ';',  // 0x2C - Z -> ; in Dvorak
    'q',  // 0x2D - X -> q in Dvorak
    'j',  // 0x2E - C -> j in Dvorak
    'k',  // 0x2F - V -> k in Dvorak
    'x',  // 0x30 - B -> x in Dvorak
    'b',  // 0x31 - N -> b in Dvorak
    'm',  // 0x32 - M -> m in Dvorak (same)
    'w',  // 0x33 - Comma -> w in Dvorak
    'v',  // 0x34 - Period -> v in Dvorak
    'z',  // 0x35 - Slash -> z in Dvorak
    0x00, // 0x36 - Right Shift
    '*',  // 0x37 - Keypad *
    0x00, // 0x38 - Left Alt
    ' ',  // 0x39 - Space
    0x00, // 0x3A - Caps Lock
    0x00, // 0x3B - F1
    0x00, // 0x3C - F2
    0x00, // 0x3D - F3
    0x00, // 0x3E - F4
    0x00, // 0x3F - F5
    0x00, // 0x40 - F6
    0x00, // 0x41 - F7
    0x00, // 0x42 - F8
    0x00, // 0x43 - F9
    0x00, // 0x44 - F10
    0x00, // 0x45 - Num Lock
    0x00, // 0x46 - Scroll Lock
    '7',  // 0x47 - Keypad 7 / Home
    '8',  // 0x48 - Keypad 8 / Up
    '9',  // 0x49 - Keypad 9 / PgUp
    '-',  // 0x4A - Keypad -
    '4',  // 0x4B - Keypad 4 / Left
    '5',  // 0x4C - Keypad 5
    '6',  // 0x4D - Keypad 6 / Right
    '+',  // 0x4E - Keypad +
    '1',  // 0x4F - Keypad 1 / End
    '2',  // 0x50 - Keypad 2 / Down
    '3',  // 0x51 - Keypad 3 / PgDn
    '0',  // 0x52 - Keypad 0 / Insert
    '.',  // 0x53 - Keypad . / Delete
    0x00, // 0x54 - Alt-SysRq
    0x00, // 0x55 - Reserved
    0x00, // 0x56 - Non-US \ or |
    0x00, // 0x57 - F11
    0x00, // 0x58 - F12
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x59-0x60 - Reserved
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x61-0x68 - Reserved
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x69-0x70 - Reserved
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x71-0x78 - Reserved
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  // 0x79-0x80 - Reserved
};

// Alternative array for shifted characters (when Shift is pressed) - Dvorak Layout
char scancode_shifted[128] = {
    0x00, // 0x00 - Invalid
    0x00, // 0x01 - Escape
    '!',  // 0x02 - 1 -> !
    '@',  // 0x03 - 2 -> @
    '#',  // 0x04 - 3 -> #
    '$',  // 0x05 - 4 -> $
    '%',  // 0x06 - 5 -> %
    '^',  // 0x07 - 6 -> ^
    '&',  // 0x08 - 7 -> &
    '*',  // 0x09 - 8 -> *
    '(',  // 0x0A - 9 -> (
    ')',  // 0x0B - 0 -> )
    '{',  // 0x0C - Minus -> { in Dvorak (shifted [)
    '}',  // 0x0D - Equals -> } in Dvorak (shifted ])
    0x08, // 0x0E - Backspace
    0x09, // 0x0F - Tab
    '"',  // 0x10 - Q -> " in Dvorak (shifted ')
    '<',  // 0x11 - W -> < in Dvorak (shifted ,)
    '>',  // 0x12 - E -> > in Dvorak (shifted .)
    'P',  // 0x13 - R -> P in Dvorak
    'Y',  // 0x14 - T -> Y in Dvorak
    'F',  // 0x15 - Y -> F in Dvorak
    'G',  // 0x16 - U -> G in Dvorak
    'C',  // 0x17 - I -> C in Dvorak
    'R',  // 0x18 - O -> R in Dvorak
    'L',  // 0x19 - P -> L in Dvorak
    '?',  // 0x1A - Left bracket -> ? in Dvorak (shifted /)
    '+',  // 0x1B - Right bracket -> + in Dvorak (shifted =)
    0x0D, // 0x1C - Enter
    0x00, // 0x1D - Left Ctrl
    'A',  // 0x1E - A -> A in Dvorak (same)
    'O',  // 0x1F - S -> O in Dvorak
    'E',  // 0x20 - D -> E in Dvorak
    'U',  // 0x21 - F -> U in Dvorak
    'I',  // 0x22 - G -> I in Dvorak
    'D',  // 0x23 - H -> D in Dvorak
    'H',  // 0x24 - J -> H in Dvorak
    'T',  // 0x25 - K -> T in Dvorak
    'N',  // 0x26 - L -> N in Dvorak
    'S',  // 0x27 - Semicolon -> S in Dvorak
    '_',  // 0x28 - Apostrophe -> _ in Dvorak (shifted -)
    '~',  // 0x29 - Grave accent -> ~
    0x00, // 0x2A - Left Shift
    '|',  // 0x2B - Backslash -> |
    ':',  // 0x2C - Z -> : in Dvorak (shifted ;)
    'Q',  // 0x2D - X -> Q in Dvorak
    'J',  // 0x2E - C -> J in Dvorak
    'K',  // 0x2F - V -> K in Dvorak
    'X',  // 0x30 - B -> X in Dvorak
    'B',  // 0x31 - N -> B in Dvorak
    'M',  // 0x32 - M -> M in Dvorak (same)
    'W',  // 0x33 - Comma -> W in Dvorak
    'V',  // 0x34 - Period -> V in Dvorak
    'Z',  // 0x35 - Slash -> Z in Dvorak
    0x00, // 0x36 - Right Shift
    '*',  // 0x37 - Keypad *
    0x00, // 0x38 - Left Alt
    ' ',  // 0x39 - Space
    0x00, // 0x3A - Caps Lock
    // F-keys and remaining entries same as unshifted
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x3B-0x44
    0x00, 0x00, // 0x45-0x46
    '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.', // 0x47-0x53
    // Rest are reserved/unused
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


char kb_buffer[256];
int kb_write_buf_pntr = 0;
int kb_read_buf_pntr = 0;
bool shifted = 0;


void keyboard_callback(){
    PIC_sendEOI(IRQ1);

    // Ox2A left shift

    int k = inb(0x60);

    if((k & 128) == 128){
        if (k == 0xAA){
            shifted = 0;
        }
    }else{
        if(shifted){
            if(scancode_list[k] == 0x0D){
                kb_buffer[kb_read_buf_pntr] = '\n';
                kb_read_buf_pntr++;
            }else{
                kb_buffer[kb_read_buf_pntr] = scancode_shifted[k];
                kb_read_buf_pntr++;
            }
        } else{
            if(scancode_list[k] == 0x0D){
                kb_buffer[kb_read_buf_pntr] = '\n';
                kb_read_buf_pntr++;
            }else if (k == 0x2A){
                shifted = 1;
            }else{
                kb_buffer[kb_read_buf_pntr] = scancode_list[k];
                kb_read_buf_pntr++;
            }
        }
    }
    kb_buf_read();
}

void kb_buf_read(){
    while(kb_write_buf_pntr < kb_read_buf_pntr){
        printf("%c", kb_buffer[kb_write_buf_pntr]);
        kb_write_buf_pntr++;
    }
}


void init_kb(){
    register_interrupt_handler(IRQ1, &keyboard_callback);

    outb(0xED, 1); // setting caps lock LED to on to test
}





