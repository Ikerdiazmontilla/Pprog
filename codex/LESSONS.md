# LESSONS

## 2026-02-23T10:56:39+01:00
- What failed: Reading `codex/tmp/enunciado2.txt` failed once (`No such file or directory`).
- Why it failed: The extraction and read steps were launched in parallel, so the read started before the output file existed.
- Prevention rule: Do not parallelize dependent file-generation and file-read commands; run them sequentially.

## 2026-02-23T10:57:08+01:00
- What failed: A first attempt to append lessons with a shell heredoc produced malformed text and shell errors.
- Why it failed: Markdown backticks were interpreted by the shell due an unquoted heredoc delimiter.
- Prevention rule: Use single-quoted heredoc delimiters (`<<'EOF'`) when writing markdown from shell scripts.

## 2026-03-16T00:00:00+01:00
- What failed: A smoke test was launched in parallel with `make` and a second compile pass, so `./castle` was still unavailable when the test started.
- Why it failed: Build, alternate compile checks and executable runs were treated as independent steps even though they share the same output files.
- Prevention rule: Do not parallelize build commands with smoke tests or with other compile commands that touch the same artifacts.

## 2026-03-16T00:00:00+01:00
- What failed: Installing `openpyxl` with `python3 -m pip install --user openpyxl` failed.
- Why it failed: The system Python is PEP 668 externally managed and blocks direct package installation.
- Prevention rule: When a Python dependency is missing in this environment, create a temporary virtual environment under `codex/tmp/` and install the package there.

## 2026-03-16T00:00:00+01:00
- What failed: A sanitizer build using `make ... LDFLAGS='-fsanitize=address'` failed to link `-lscreen`.
- Why it failed: Overriding `LDFLAGS` removed the repository's local library search path `-L.` from the final link step.
- Prevention rule: When overriding linker flags in this repo, preserve `-L.` or append new flags instead of replacing the whole variable.

## 2026-03-16T00:00:00+01:00
- What failed: An ASan smoke test aborted with `strncpy-param-overlap` inside `command_set_argument`.
- Why it failed: `game_set_last_command` can copy an argument from the same `Command` object back into itself, and `strncpy` is undefined on overlapping memory ranges.
- Prevention rule: When a setter may receive pointers into its own storage, copy through a temporary buffer or use an overlap-safe strategy, and keep a regression test for the self-copy case.
