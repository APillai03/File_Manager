# File Manager Project

This project is a simple File Manager implemented with a client-server model. It uses `server.c` for the server-side functionality and `client.py` for the client-side interface. Ensure you have all dependencies installed before running.

## Documentation

For detailed documentation, [View the full documentation](https://apillai03.github.io/Certificates/OS.pdf).

## Prerequisites

- Install `tkinter` before running the project on Linux.
- Ensure you have `gcc` installed for compiling the server code.
- Python 3 is required to run the client script.

## How to Run the File Manager

Follow these steps to set up and run the project:

1. **Clone the Repository**
   ```bash
   git clone https://github.com/APillai03/File_Manager
   cd File_Manager```

2. **Compile the Server**
    ```bash
   gcc server.c -o server
   ./server
   ```
3. **Run the Client (another terminal)**
    ```bash
    python3 client.py
   ```