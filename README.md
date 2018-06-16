
TextDecorator
=============

`TextDecorator` is a tiny, header-only C++ tool making it trivially easy to print colored text, <b>bold</b> text, <b>colored bold</b> text... the possibilities are endless!


Usage example
=============

```
#include "TextDecorator.h"

...

TextDecorator::TextDecorator TD;

std::cout << TD.red("Here's some red text, ")
          << TD.bold("this text is bold, ")
          << TD.decorate("and this is HYPER", TextDecorator::Blue|
                                              TextDecorator::Bold|
                                              TextDecorator::Inverse)
          << std::endl;
```

<b>Note:</b> A terminal's colors are determined by its color scheme (e.g. I use the "light" version of "solarized"). The `TD.red()` command might not print <i>red</i> text for you. You will probably need to adjust the [color names](TextDecorator.h#L55) or (alternatively) the [color codes](TextDecorator.h#L77).


How it works
============

```
This is a short tutorial on the ANSI escape codes used here:

Escape sequences begin with the ESC character. This is an unprintable
ASCII character, so it has to be directly encoded by its number. The
numeric code for ESC is 27 in decimal, or 0x1b in hexadecimal, and so
the first step is to output
   \x1b
into the stream. Following the ESC character, a "[" (opening square
bracket) is expected, called the CSI or "Control Sequence Introducer".
Luckily, this is a printable character:
   [
The stream is now ready to receive the actual formatting command(s).

These commands are numbers. There may be zero or more of these SGR or
"Select Graphic Rendition" parameters. The ones used here include:
   1           (bold)
   4           (underline)
   7           (inverse display; swaps background and foreground colors)
   30-37       (text color; there are "standard" colors, but a terminal
                emulator is free to redefine them so your TextDecorator
                might not actually print "red" text using the "Red"
                color option.)
   0 or empty  (reset; all attributes off)
If more than one is used, the individual options are separated by ";"
(semicolon). For example, the code for "red normal" text is:
   31
Combining multiple commands for "bold underlined green" text yields:
   1;4;32

The code sequence is finalized by a single "m" which specifies that all
preceding codes should be interpreted as SGR parameters:
   m


After choosing a formatting using these commands, all following text
entered into the stream will be formatted accordingly. In the end,
the formatting should be reset to "nothing" by sending the special "all
attributes off" parameter (0 or empty).

-----------------------------------------------------------------------

EXAMPLE: Printing "Hello World" in bold red text:
 
      Start formatting╮       Text       ╭Reset formatting
                      │         │        │
                 ╭────┴───╮╭────┴────╮╭──┴─╮
   std::cout << "\x1b[1;31mHello World\x1b[m";
                 ╰┬─╯│││╰┤│           ╰┬─╯││
                  │  │││ ││            │  ││
               ESC╯  │││ ││           ESC │╰SGR terminator
                  CSI╯││ ││              CSI
                      ││ │╰SGR terminator
              SGR:bold╯│ ╰SGR:red
                       │
                   separator

-----------------------------------------------------------------------
```

See e.g. "ANSI escape code" on Wikipedia for much more information.


