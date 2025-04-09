# `iny` — is INPUT available, yes?

> A tiny, zero-libc utility to check if stdin has data **without consuming it**.
> Perfect for shell scripts and pipelines

by jaggz.h {who is at} gmail.com
2025-04-09

## Why?

Sometimes you want to peek at stdin to see if there's any data — **without** slurping it up and leaving nothing for the next command.

Other tools check for 'readiness', but are not actually reporting data availability.

What's worse is that other tools (I'm talking to you, `select`), and their wrappers in other languages (like Perl's`IO::Select`), are arguably a bit deceptive — they tell you a file descriptor is *ready*, but that could just mean *EOF*. And you have to read a bunch of their wonderful (true) manpages to see they don't have the capability to actually tell you whether **DATA IS READY** or not.

**It turns out `poll()` can do it with its `POLLIN` flag.**

This is where `iny` comes in:
- Uses `poll()` directly via syscall
- Does **not** consume input
- Exits 0 if data is ready to read
- Exits 1 if there's nothing (yet)

Also — thanks to some ChatGPT-powered wizardry — there's an ultra-tiny version that:
    Requires no libc
    Is fully static
    Weighs in at just 8k (on my system)

(There's a dynamically linked version too if you prefer that.)

## Issues
    - NONE [that I know of]
    - Except I didn't make an installer. (I just build and symlink its binaries to my ~/bin.)

## Usage

## Let `cat` eat only if there's input for it.
```bash
$ echo hello | { ./iny && cat || echo "No input available for cat"; }
hello
```

## While we were sleeping...
```bash
$ sleep 5; ./iny && echo "Yup, you typed while we were sleeping."
lkdjflkdjf
Yup, you typed while we were sleeping.
```

## Checking if input is there before doing a `read`:
```bash
$ echo abcd | { if ./iny; then read -n1 letter && echo "We got at least a letter: $letter"; else echo "Nothing was available when we checked."; fi; }
We got at least a letter: a
```

