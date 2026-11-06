# Linux Mmap Search

Search a regular file with a read-only memory mapping and report exact byte offsets.

[![Build and verify](https://github.com/netcodermike/linux-mmap-search/actions/workflows/verify.yml/badge.svg)](https://github.com/netcodermike/linux-mmap-search/actions/workflows/verify.yml)

**Language:** C · **Platform:** Linux · **App type:** Linux memory-mapped text search utility

First-release learning implementation, with explicit scope below. This is one independently runnable app, not a placeholder in a combined repository.

## Features

- Literal byte search
- Overlapping matches
- Line and byte positions
- Empty/binary file support

## Requirements

Linux, a C11 compiler, make, and Python 3 for real integration tests.

## Quick start

```sh
git clone https://github.com/netcodermike/linux-mmap-search.git
cd linux-mmap-search
make
./app LITERAL /path/to/file
```

Commands run from the repository root. Lines marked for a particular operating system apply only there. Language tools are prerequisites, not installed by the app. Close desktop windows normally; terminal/server apps stop with Ctrl+C unless their usage notes say otherwise.

## Example workflow

Run ./app ana a-file-containing-banana and inspect offsets 1 and 3. Test an empty file and a multiline file.

## Architecture, configuration, and data

main.c opens one regular file read-only, maps it MAP_PRIVATE/PROT_READ, compares a nonempty literal up to 4096 bytes at each offset, and counts newline boundaries. Output is 1-based line:0-based byte offset plus matches=N. The integration test checks overlaps, binary NULs, and empty input. No contents or mappings are written.

## Verification

Build with the quick-start command where needed, then run:

```sh
make test
```

Manual acceptance: Run ./app ana a-file-containing-banana and inspect offsets 1 and 3. Test an empty file and a multiline file. Also test malformed inputs and an unwritable output destination.

See [validation record](docs/VALIDATION.md) for observed checks and their limits. CI results verify only what the workflow runs; they do not establish native GUI correctness or production readiness.

## Limitations and next steps

No regex, Unicode normalization, case folding, directory recursion, parallelism, or replacement. Worst-case time is O(file size × literal length). Mapped reads can fault if a concurrent writer truncates the file; use stable files. A 32-bit process cannot map arbitrary large files.

## Troubleshooting

Use the exact platform/toolchain above. Preserve originals and use synthetic fixtures first. Errors are displayed in the UI or stderr. A headless machine can run the model tests but cannot verify native GUI/audio behavior. Output paths are chosen explicitly; keep backups of important data.

## Source map

- `main.c`
- `Makefile`
- `tests/integration.py`

## Development and license

Read [contributing](CONTRIBUTING.md) before changing the app, and [security/privacy](SECURITY.md) before supplying private data. Use synthetic fixtures for tests. No telemetry, paid API key, or account is required by the app itself. Dependencies, when present, are stated in Requirements.

[MIT license](LICENSE), copyright 2026 netcodermike.
