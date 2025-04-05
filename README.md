# Harvard CS50x

[Harvard CS50x 2025](https://cs50.harvard.edu/x/2025)

The purpose of this repository is to perform all of the same puzzles and exercises assigned in the Harvard CS50X Introduction to Computer Science course.

The intent is not to write the *best* code, but to scale the quality of code with the class' topics. If the class doesn't teach tuples until week 2, I won't use them in week 1's exercises. Week 5's excercises would use all concepts taught in the class so far.

- Week 0 Scratch
- Week 1 C
- Week 2 Arrays
- Week 3 Algorithms
- Week 4 Memory
- Week 5 Data Structures
- Week 6 Python
- Week 7 SQL
- Week 8 HTML, CSS, JavaScript
- Week 9 Flask
- Week 10 The End

## Usage

### Requirements
- Be sure to have C compiler and dependencies installed:
    - On Debian `apt install build-essential`
    - On Fedora `dnf group install "C Development Tools and Libraries" "Development Tools"`
    - On Arch `pacman -S base-devel`
- All the code here should compile on any Linux-based system
    - The code contains GNU C specific features and may not compile on mac/pc
    - The code does **not** use the cs50 helpers ([cs50.h](https://github.com/cs50/libcs50))

### Example
1. Clone this repo:
`git clone https://github.com/mjstierman/cs50x.git`
1. Change in to the directory:
`cd cs50x`
1. Then change into the week's directory: `cd week_1`
1. Then change into the assignment directory: `cd mario-more`
1. Compile `make mario`
1. Run the program `./mario`
    ```bash
    $ ./mario
    How high should Mario jump (1-10)? 9
            #   #        
           ##   ##       
          ###   ###      
         ####   ####     
        #####   #####    
       ######   ######   
      #######   #######  
     ########   ######## 
    #########   #########
    ```