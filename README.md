# mcos
Simple IA32 kernel.

# Compilation
You can compile MCOS for yourself. To do this, you must first
grab a copy of `i386-elf-*`, via the shell script provided at
[`cross-compile.sh`](./cross-compile.sh).

Once you've obtained that, you must then get a couple other
dependencies:
- nasm
- mtools
- xorriso

After all this, run this in a terminal:

`make || make`$^{[1]}$

This gives you the `myos.iso` file, this is the latest build
of MCOS.

## Notes
$[1]$: The first run will error out due to the Makefile not
being able to find the `./bin` directory, because it gets
created after it tries to find it. The second run (hence
the `|| make`) does not error out.

# Screenshot
*8 Feb 2022*

![](https://media.discordapp.net/attachments/1073075895146909716/1073075895281143868/image.png)

# Roadmap
[*Main Article: roadmap.md*](./roadmap.md)