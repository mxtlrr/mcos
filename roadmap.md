# Roadmap of MCOS
MCOS' development has been scattered and chaotic at times.
This document's purpose is to prevent that, by giving developers
an outline of what needs to be accomplished.

The [issues tab](https://github.com/mxtlrr/mcos/issues) is also
a place in which an outline of what needs to be done can be found,
however the difference between the Issues tab and this document, is
that most of the *Issues* are bugs, and should be completed as soon
as possible.


### Phase 0: Baby Steps
- [ ] Video Library
	- [X] Pixels
	- [ ] Circles
	- [ ] Lines
	- [ ] Rectangles
- [X] Interrupts
	- [X] Exception handler
	- [X] Basic IRQ handler
- [ ] Memory Management
	- [ ] `kmalloc()`
	- [ ] `kfree()`
### Phase 1: User Usage
- [ ] Shell
	- [X] Keyboard input
- [ ] Other user input
	- [ ] PS/2 Mouse
		- [ ] LMB
		- [ ] RMB
### Phase 2: Drivers and Storage
- [ ] PCI
- [ ] ACPI
- [ ] Filesystem
	- [ ] VFS
	- [ ] FAT32 $^1$
### Phase 3: TODO/TBD
...

# Notes

$1$: This filesystem is probably going to be
swapped out for another one, however this has
not been decided yet.