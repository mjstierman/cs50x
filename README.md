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

## Text Companions
For a number of reasons, I find reading long-form information on paper to be much easier than on a screen. I wanted to use a Lecture:Text model for this class. To that end, I discovered a few books that followed the class along excellently.

### A Common-Sense Guide to Data Structures and Algorithms, Second Edition
From the [Pragmatic Programmer's collection](https://pragprog.com/titles/jwdsal2/a-common-sense-guide-to-data-structures-and-algorithms-second-edition/).

This book almost perfectly follows the first 5 weeks of class. If you start reading it early, during Week 0, and read ~4 chapters a week, you'll be ahead of the class. 

This is a _rough_ mapping of weeks:chapters. I did futz with the mapping to try to keep the chapters more evenly spaced.
- Week 1: Chapters 1, 2
- Week 2: Chapters 3, 4, 5, 6, 7
- Week 3: Chapters 8, 9, 10
- Week 4: Chapters 11, 12, 13
- Week 5: Chapters 14, 15, 16, 17

Chapters 18, 19, 20 deal with graph theory and digs deeper into optimization. Highly suggested reading.

### Python Crash Course, 3rd Edition
From [No Starch Press](https://nostarch.com/python-crash-course-3rd-edition).

I suggest this book over some of the other (excellent) Python books because it too covers some extra niceties like setting up your dev environment, troubleshooting skills, datatypes, list, and other "computer sciencey" topics in brief. I had already read this book prior to starting CS50, and pulled it back out to augment and quickly complete Week 6.

In Week 9, the class covers Flask, which is a Python-based backend Web server platform. The book covers Django, which is similiar enough. Django is also used for the `CS50 Web` class variant.

- Week 6: Chapters 1, 2, 3, 5, 7, 8
- Week 9: Chapters 18, 19, 20 

### Week 7: Databases
This one is next. Will update when complete and have found a good companion text.

### HTML, CSS, JavaScript
These are unique as the nature of the Web is that it moves very quickly. HTML/CSS are not technically programming languages per se, and JavaScript is constantly evolving. To augment the class, I've heard that [The Odin Project](https://www.theodinproject.com/) is a great resource for those wanting to dive into Web development, though I haven't used it myself.

## Usage

### Requirements
- Be sure to have C compiler and dependencies installed:
    ```bash
    # Fedora / Red Hat / .rpm
    $ sudo dnf group install development-tools c-development

    # Debian / Ubuntu / .deb
    $ sudo apt install build-essential

    # Arch Linux
    $ sudo pacman -S base-devel
    ```
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

