# Week 5: Data Structures

### Midterm!

The culmination of the past 5 weeks of theory and practice. The two assignments will use everything we've learned so far.

## Inheritance
The was pretty simple practice. Some recursive actions to drive the concept home. Nothing crazy here.

## Speller
This one took a couple of days to get to a running state.

### Install and use debuggers
[GDB](https://developers.redhat.com/articles/the-gdb-developers-gnu-debugger-tutorial-part-1-getting-started-with-the-debugger) and [coredumpctl](https://www.man7.org/linux/man-pages/man1/coredumpctl.1.html) were great for debugging the program and really accellerated the process. Make sure that the development libraries are installed on your system:
```bash
# Fedora / Red Hat / .rpm
$ sudo dnf group install development-tools

# Debian / Ubuntu / .deb
$ sudo apt install build-essential

# Arch Linux
$ sudo pacman -S base-devel
```

### Identifying the segfault
As easy as:
```bash
# Fedora 42
$ ./speller dictionaries/small texts/aca.txt
[1]    183238 segmentation fault (core dumped)  ./speller dictionaries/small texts/aca.txt
$ coredumpctl dump --output 183238.dump
$ gdb speller --core 183238.dump
```
Then analyze the output -- it will state exactly where the segfault occurred in the source code, including the input that triggered the segfault.

```bash
Program terminated with signal SIGSEGV, Segmentation fault.
#0  0x0000000000400ca1 in check (word=0x7fff3ceb2350 "Congress") at dictionary.c:39
39                  *little_word[i] = tolower(word[i]);
```
### Fix the code on the identified line.

So in this case, some character in the `word` "`Congress`" failed to get copied into `char *little_word` as `congress` like it was supposed to. That will need to be corrected.

### Lather, rinse, repeat.

Keep going until there are no more issues. You can use these discoveries to help create unit tests later on.

## Results:
Well, its not the fastest (with a 26-length hash table), but it ran:
```bash
WORDS MISSPELLED:     17062
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        376904
TIME IN load:         9.80
TIME IN check:        114.03
TIME IN size:         0.02
TIME IN unload:       0.02
TIME IN TOTAL:        123.86
```

Versus the included cs50 binary:
```bash
WORDS MISSPELLED:     17062
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        376904
TIME IN load:         0.04
TIME IN check:        0.53
TIME IN size:         0.00
TIME IN unload:       0.02
TIME IN TOTAL:        0.59
```

The program is functioning as intended, with all results returning correctly. While there is always room for improvement -- adjustments can be made through algorithm optimization and hash size -- I'm happy that the spell checker works effectively.