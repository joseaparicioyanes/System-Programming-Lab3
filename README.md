# System-Programming-Lab3
Write a C program to run on ocelot to read a text file and print it to the display. It should optionally find
the count of the number of words in the file, and/or find the number of occurrences of a substring,
and/or take all the words in the string and sort them lexicographically (ASCII order). You must use getopt
to parse the command line. There is no user input while this program is running.
Usage: mywords [-cs] [-f substring] filename
• The -c flag means to count the number of words in the file. A word would be a series of
characters separated by spaces or punctuation. A word could include a hyphen or a single
apostrophe.
• The -s option means to print the words in the file sorted by ASCII order.
• The -f option will find the number of occurrences of the given substring.
• You may have any number of the flags included or none of them.
• The order they should be run would be: -s first, -c second, and -f third.
• Output should be well formatted and easy to read.
The source file should have your name & PantherID, a description and it should have the affirmation of
originality included in a comment at the top.
Code should be nicely indented and commented.
Create a simple Makefile to compile your program into an executable called mywords.
• Create an ASCII file named testfile with the text: The boy is sitting right there.
• Test the program with the following commands:
o mywords -c -f he testfile
o mywords -s testfile
• Take a screenshot of the screen showing the output on ocelot. Name it FirstNameLastName.png
or .jpg.
Submit this assignment in the Canvas assignment dropbox for Lab 3. You should submit the source code
file, the screenshot and your Makefile compressed into a zip file named FirstNameLastNameL3.zip. The
Makefile should be called Makefile with no extension. I should be able to type make at the command
line to compile your program. Do not include any other files or folders in the zipfile. This applies even if
you are a Mac user.
If the program does not compile and do something useful when it runs it will not earn any credit.
