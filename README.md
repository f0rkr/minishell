# minishell

Coding a *shell* from scratch using low level C was one of the most powerfull project I made, constructing all those building block of a shell from parsing commands
through forking process creation and synchronisation, managing pipes and executing it. ✨

<img src="https://images.amcnetworks.com/ifccenter.com/wp-content/uploads/2020/01/ghost-in-the-shell-1280.jpg">

it's called wesh shell. aka ``Wesh a sat``

## Options created

Minishell runs executables from an absolute, relative or environment PATH (``/bin/ls`` or ``ls``), including arguments or options. ``'`` and ``"`` work the same as bash.

You can separate commands with ``;``, as well as use redirections ``>`` ``>>`` ``<`` and pipes ``|``.

Environment variables are handled, like ``$HOME``, including the return code ``$?``.

Finally, you can use ``Ctrl-C`` to interrupt and ``Ctrl-\`` to quit a program, as well as ``Ctrl-D`` to throw an EOF, same as in bash.

A few of the functions are "built-in", meaning we don't call the executable, we re-coded them directly. It's the case for ``echo``, ``pwd``, ``cd``, ``env``, ``export``, ``unset`` and ``exit``.

You can use arrow keys to edit commands and iterate through last executed ones (``history``). *managed with [termcap](https://man7.org/linux/man-pages/man5/termcap.5.html)*

# How to run it

```shell
f0rkr@shell$ make
f0rkr@shell$ ./minishell
wsh :: /Users/f0rkr/Documents/minishell » wesh a sat
```

# Teammate 
  - [f0rkr](https://github.com/f0rkr)

# Resources

https://www.gnu.org/software/bash/manual/bash.html
