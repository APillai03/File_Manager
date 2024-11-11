import tkinter as tk
import sys

def save(filename, text_edit):
    try:
        
        content = text_edit.get(1.0, tk.END)
        
      
        with open(filename, 'w') as file:
            file.write(content)
        
       
        print(f"File '{filename}' has been saved successfully.")
    except Exception as e:
        print(f"Error saving file: {e}")

def main():
    window = tk.Tk()
    window.title('Text Editor')

    window.rowconfigure(0, minsize=400)
    window.columnconfigure(1, minsize=500)

    text_edit = tk.Text(window, font='Helvetica 18')
    text_edit.grid(row=0, column=1)

    frame = tk.Frame(window, relief=tk.RAISED, bd=2)
    frame.grid(row=0, column=0, sticky='ns')

    filename = sys.argv[1]
    operation = sys.argv[2]
    file_content = "" 

    if operation == '2':  
        try:
            with open(filename, 'r') as file:
                file_content = file.read() 
                text_edit.insert(tk.END, file_content)
            window.title(f"{filename} - Editing")
        except Exception as e:
            print(f"Error opening file: {e}")
            return
    elif operation == '1':
        try:
            with open(filename, 'r') as file:
                file_content = file.read()  
                text_edit.insert(tk.END, file_content)
            window.title(f"{filename} - Editing")
        except Exception as e:
            print(f"Error opening file: {e}")
            return
        b1 = tk.Button(frame, text='Save', command=lambda: save(filename, text_edit))
        b1.grid(row=0, column=0, padx=5, pady=5, sticky='ew')

    window.mainloop()

main()
