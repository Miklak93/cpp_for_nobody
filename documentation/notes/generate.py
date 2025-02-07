#!/usr/bin/env python3

import subprocess
import argparse
import os

def compile_latex(input="main.tex", output="notes"):
    if not input.endswith(".tex"):
        print("Error: Input file must be a .tex file.")
        return

    if not os.path.exists(input):
        print(f"Error: File '{input}' not found.")
        return

    command = [
        "pdflatex",
        "-shell-escape",
        f"-jobname={output}",
        input
    ]

    try:
        subprocess.run(command, check=True)
        print(f"PDF successfully generated: {output}.pdf")
    except subprocess.CalledProcessError as e:
        print("Error: LaTeX compilation failed.")
        print(e)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Compile a LaTeX file to a PDF with a custom filename.")
    parser.add_argument("input", nargs='?', default="main.tex", help="Path to the .tex file (default: main.tex)")
    parser.add_argument("output", nargs='?', default="notes", help="Desired name for the output PDF (without .pdf extension, default: notes)")

    args = parser.parse_args()
    compile_latex(args.input, args.output)

