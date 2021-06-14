//
// AHHH Programming Language Interpreter
// by: Kyle Morgenstein
// kyle.morgenstein@gmail.com
// www.kylemorgenstein.com
//
// License: GPL v3.0
// Heavily inspired by COW (by BigZaphod)
// The structure for the interpreter was also borrowed from COW
// Feel free to edit/use/distribute, but please don't sell AHHH or any derivative work
// If you use AHHH, attribution would be cool too, I suppose
//
#include <string>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <iostream>

typedef std::vector<int> mem;
mem program;
mem memory;
mem::iterator memory_position;
mem::iterator program_position;

int register1_value;
int register2_value;

bool register1_has_value = false;
bool register2_has_value = false;

void quit(bool error)
{
    if (error) {
        printf("Error!/n");
        exit(1);
    }
#ifndef NO_GREETINGS
    printf("\nDone.\n");
#endif
    exit(0);
}

bool exec(int instruction)
{
    switch (instruction) {
    // hhhh
    case 0: {
        if (program_position == program.begin())
            quit(true);
        
        program_position--;
        int level = 1;
        
        while (level > 0) {
            if (program_position == program.begin())
                break;

            program_position--;

            if (*program_position == 0)
                level++;
            else if (*program_position == 15)
                level--;
        }
        
        if (level != 0)
            quit(true);

        return exec(*program_position);
    }
    // hhhH
    case 1: {
        memory_position++;
        if (memory_position == memory.end()) {
            memory.push_back(0);
            memory_position = memory.end();
            memory_position--;
        }
        break;
    }
    // hhHh
    case 2: {
        if (memory_position == memory.begin())
            quit(true);
        else
            memory_position--;
        break;
    }
    // hhHH
    case 3: {
        printf("%d\n", *memory_position);
        break;
    }
    // hHhh
    case 4: {
        if (register1_has_value) {
            *memory_position = register1_value;
            register1_value = 0;
        }
        else
            register1_value = *memory_position;
        register1_has_value = !register1_has_value;
        break;
    }
    // hHhH
    case 5: {
        if (register2_has_value) {
            *memory_position = register2_value;
            register2_value = 0;
        }
        else
            register2_value = *memory_position;
        register2_has_value = !register2_has_value;
        break;
    }
    // hHHh
    case 6: {
        register1_value += *memory_position;
        register1_has_value = true;
        break;
    }
    // hHHH
    case 7: {
        register2_value += *memory_position;
        register2_has_value = true;
        break;
    }
    // Hhhh
    case 8: {
        if (*memory_position != 0)
            printf("%c", *memory_position);
        else {
            *memory_position = getchar();
            while (getchar() != '\n');
        }
        break;
    }
    // HhhH
    case 9: {
        (*memory_position)++;
        break;
    }
    // HhHh
    case 10: {
        (*memory_position)--;
        break;
    }
    // HhHH
    case 11: {
        char buffer[100];
        int c = 0;
        int buffer_size = sizeof(buffer) - 1;
        while (c < buffer_size) {
            buffer[c] = getchar();
            c++;
            buffer[c] = 0;

            if (buffer[c - 1] == '\n')
                break;
        }

        if (c == sizeof(buffer))
            while (getchar() != '\n');

        *memory_position = atoi(buffer);
        break;
    }
    // HHhh
    case 12: {
        *memory_position = 0;
        break;
    }
    // HHhH
    case 13: {
        *memory_position *= 2;
        break;
    }
    // HHHh
    case 14: {
        *memory_position *= *memory_position;
        break;
    }
    // HHHH
    case 15: {
        if (*memory_position == 0) {
            int level = 1;
            int prev = 0;
            program_position++; // have to skip past next command when looking for next hhhh.
            if (program_position == program.end())
                break;
            while (level > 0) {
                prev = *program_position;
                program_position++;

                if (program_position == program.end())
                    break;

                if (*program_position == 15)
                    level++;
                else if (*program_position == 0) // look for hhhh command.
                {
                    level--;
                    if (prev == 15)
                        level--;
                }
            }
            if (level != 0)
                quit(true);
        }
        break;
    }
    // hhh!
    case 16: {
        printf("\n");
        break;
    }
    default:
        quit(false);
    };

    program_position++;
    return true;
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("\nUsage: %s main.ahhh\n\n", argv[0]);
        exit(1);
    }

    FILE* f = fopen(argv[1], "rb");

    if (f == NULL) {
        printf("Cannot open source file [%s].\n", argv[1]);
        exit(1);
    }

    std::string buffer = "";
    bool reading = false;
    int counter = 0;

    std::string comm[] = {
        "hhhh", "hhhH", "hhHh", "hhHH",
        "hHhh", "hHhH", "hHHh", "hHHH",
        "Hhhh", "HhhH", "HhHh", "HhHH",
        "HHhh", "HHhH", "HHHh", "HHHH",
        "hhh!"
    };

    while (!feof(f)) {
        bool found = false;
        buffer += fgetc(f);

        if (buffer == "AHHH")
            reading = found = true;

        else if (reading) {
            for (int i = 0; i < 17; i++) {
                if (buffer == comm[i]) {
                    program.push_back(i);
                    found = true;
                }
            }
        }
        else if (counter > 4) {
            printf("\nSyntax Error: program must begin with 'AHHH'\n\n");
            exit(1);
        }
        else
            counter++;

        if (found) {
            buffer = "";
            found = false;
        }
        else if (buffer.size() > 3) {
            buffer = buffer.substr(1, 4);
        }
    }

    fclose(f);

#ifndef NO_GREETINGS
    printf("\nAHHHHHHHHHHHH!\n\nExecuting [%s]...\n\n", argv[1]);
#endif

    // init main memory.
    memory.push_back(0);
    memory_position = memory.begin();
    program_position = program.begin();

    while (program_position != program.end())
        if (!exec(*program_position))
            break;

    quit(false);

    return 0;
}
