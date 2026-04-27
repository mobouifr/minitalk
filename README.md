*This project has been created as part of the 42 curriculum by mobouifr.*

<div align="center">

# MINITALK

### A client/server messenger that transmits text one bit at a time using `SIGUSR1` and `SIGUSR2`.

![C](https://img.shields.io/badge/Language-C-blue?style=for-the-badge)
![UNIX Signals](https://img.shields.io/badge/IPC-UNIX%20Signals-orange?style=for-the-badge)
![42 Norm](https://img.shields.io/badge/Standard-42%20Norm-2f9e44?style=for-the-badge)

</div>

## What is this?

`minitalk` is a tiny inter-process communication project in C: one executable (`client`) sends a string to another executable (`server`) without sockets, pipes, or shared memory.

The message is encoded bit-by-bit. For each bit, the client sends one UNIX signal (`SIGUSR1` for `0`, `SIGUSR2` for `1`). The server reconstructs bytes from incoming signals and prints the decoded text to standard output.

Technically, this project is a strong exercise in low-level communication, bit manipulation, signal handling, process IDs, and synchronization trade-offs when the transport layer does not queue pending signals reliably.

> Build a protocol from almost nothing: just two processes, two signals, and precise timing.

## How it works

The client shifts each character from bit 7 down to bit 0, then sends one signal per bit:

```text
Character 'A' (65) -> 01000001
bit 7 6 5 4 3 2 1 0
sig  1 2 1 1 1 1 1 2   (1=SIGUSR1, 2=SIGUSR2)
```

On the server side, each received signal updates a static byte-in-progress and a bit counter. After 8 signals, the server writes the resulting byte. A `\0` terminator from the client ends the message and triggers a newline.

## Features

| Feature | Status | Notes |
|---|---|---|
| Mandatory `server` binary | ✓ | Prints its PID, receives `SIGUSR1`/`SIGUSR2`, reconstructs bytes, writes message to stdout. |
| Mandatory `client` binary | ✓ | Takes `PID` and `string`, encodes each char into 8 signals, sends `\0` terminator. |
| Sequential messages without restart | ✓ | Server loop stays alive and can receive multiple messages over time. |
| Bonus targets in Makefile | ✓ | `make bonus` builds `client_bonus` and `server_bonus`. |
| Message acknowledgment (bonus subject) | — | No server-to-client acknowledgment signal is implemented in code. |
| Unicode support (bonus subject) | — | No multi-byte Unicode protocol/handling is implemented in code. |

<details>
<summary>Raw technical notes</summary>

- Server uses `signal()` handlers and an infinite busy loop (`while (1) ;`).
- Client delays between signals with `usleep(200)`.
- Input error message used by client/server: `BAD INPUT`.
- Verified platform from this audit: Linux.

</details>

## Controls

Not applicable for this project (no graphical window, no key handling).

## Map / Config format

Not applicable for this project (no map or scene/config parser files in the repository).

## Project structure

```text
minitalk/
├── Makefile        ← Builds mandatory and bonus executables
├── client.c        ← Mandatory client: parses PID/string and sends encoded signals
├── server.c        ← Mandatory server: prints PID and decodes incoming signals
├── client_bonus.c  ← Bonus client target source (same signaling behavior here)
└── server_bonus.c  ← Bonus server target source (same decoding behavior here)
```

## Getting started

### Build

```bash
make
```

### Run

```bash
./server
./client <server_pid> "Your message"
```

### Bonus build

```bash
make bonus
```

<div align="center">

| Rule | What it does |
|---|---|
| `make` / `make all` | Build `client` and `server` |
| `make bonus` | Build `client_bonus` and `server_bonus` |
| `make clean` | Remove object files |
| `make fclean` | Remove objects and all executables |
| `make re` | Full rebuild (`fclean` then `all`) |

</div>

<details>
<summary>Build flags and toolchain</summary>

```bash
CC=cc
CFLAGS=-Wall -Wextra -Werror
```

</details>

## Resources

- UNIX signals overview: `man 7 signal`
- Installing signal handlers: `man 2 signal`, `man 2 sigaction`
- Sending signals to another process: `man 2 kill`
- Process IDs: `man 2 getpid`
- 42 Norm overview: [https://github.com/42School/norminette](https://github.com/42School/norminette)
