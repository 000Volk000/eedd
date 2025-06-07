#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Description: Script to run unit tests con compilación automática
# Author: Francisco José Madrid Cuevas <fjmadrid@uco.es>
# Date: 2025-01-29
# Updated: 2025-06-08

import sys
import os
import subprocess
import glob
import argparse

__version__ = "2.0.0"  # Versión actualizada


def is_executable(file_path):
    if os.name == "nt":
        file_path += ".exe"
    return os.path.isfile(file_path) and os.access(file_path, os.X_OK)


def is_directory(file_path):
    return os.path.isdir(file_path)


def is_file(file_path):
    return os.path.isfile(file_path)


def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)


def compile_project(build_dir="build"):
    """Compila el proyecto usando make en el directorio build/"""
    if not os.path.isdir(build_dir):
        eprint(f"Error: Directorio {build_dir} no encontrado")
        return False

    original_dir = os.getcwd()
    try:
        os.chdir(build_dir)
        result = subprocess.run(
            ["make"],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            encoding="utf-8",
        )
        if result.returncode != 0:
            eprint("Error en compilación:")
            eprint(result.stderr)
            return False
        print("Compilación exitosa")
        return True
    except Exception as e:
        eprint(f"Error durante la compilación: {str(e)}")
        return False
    finally:
        os.chdir(original_dir)


if __name__ == "__main__":
    for value in range(0, 100):
        print("")

    parser = argparse.ArgumentParser(
        description=f"Run unit tests con compilación automática ({__version__})"
    )
    parser.add_argument(
        "test_program", type=str, help="Test program (ej: test_cdarray)"
    )
    parser.add_argument(
        "test", type=str, help="Test file or folder (ej: 01_tests_cdarray)"
    )

    args = parser.parse_args(sys.argv[1:])

    # PASO 1: Compilar el proyecto
    print("=" * 50)
    print("Compilando proyecto en build/...")
    if not compile_project():
        eprint("Compilación fallida, abortando tests")
        sys.exit(1)

    # PASO 2: Construir ruta completa al ejecutable
    test_program_path = os.path.join("build", args.test_program)
    if not is_executable(test_program_path):
        eprint(f"Error: Programa de tests no encontrado en {test_program_path}")
        sys.exit(1)

    # PASO 3: Procesar tests
    if not is_file(args.test) and not is_directory(args.test):
        eprint("Error: Archivo o directorio de tests no encontrado")
        sys.exit(1)

    tests = []
    if is_directory(args.test):
        tests = sorted(glob.glob(os.path.join(args.test, "??")))
    else:
        tests.append(args.test)

    correct_count = 0
    print("\n" + "=" * 50)
    print(f"Iniciando {len(tests)} tests...\n")

    for test in tests:
        print("Test: " + test + " ... ", end="", flush=True)
        try:
            output = subprocess.run(
                [test_program_path, test],
                capture_output=True,
                text=True,
                encoding="utf-8",
                timeout=30,
            )

            if output.returncode != 0:
                print(f"\033[31mERROR (código {output.returncode})\033[0m")
                print("  Salida de error:")
                print("  " + output.stderr.strip().replace("\n", "\n  "))
            else:
                expected_file = test + ".a"
                if not os.path.isfile(expected_file):
                    print("\033[33mFALLO (archivo .a no encontrado)\033[0m")
                else:
                    with open(expected_file, encoding="utf-8") as f:
                        expected_output = f.read()

                    if output.stdout != expected_output:
                        print("\033[31mFALLO (diferencias en salida)\033[0m")
                        print("  Salida esperada vs obtenida:")
                        print("  [" + expected_output + "]")
                        print("  [" + output.stdout + "]")
                    else:
                        print("\033[32mÉXITO\033[0m")
                        correct_count += 1

        except subprocess.TimeoutExpired:
            print("\033[31mTIMEOUT (más de 30s)\033[0m")
        except Exception as e:
            print(f"\033[31mERROR: {str(e)}\033[0m")

    # Resumen final
    print("\n" + "=" * 50)
    print(f"RESULTADO: {correct_count}/{len(tests)} tests pasados")
    print("=" * 50 + "\n")

    if correct_count == len(tests):
        sys.exit(0)
    else:
        sys.exit(1)
