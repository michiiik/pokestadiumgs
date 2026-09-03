# Pokemon Stadium 2 (US)
A WIP decomp of Pokemon Stadium 2 (US/JP).

Current US decompilation progress, including a per-source-file breakdown, is
documented in [COVERAGE.md](COVERAGE.md).

It builds the following ROMs:

* pokestadiumgs-us.z64: `md5: 1561c75d11cedf356a8ddb1a4a5f9d5d`
* pokestadiumgs-jp.z64: `md5: a17aadcc962393d476edc321e59c504b`

Note: To use this repository, you must already have a rom for the game.

# Prerequisites

Under Debian / Ubuntu (which we recommend using), you can install them with the following commands:

```bash
sudo apt update
sudo apt install make git build-essential binutils-mips-linux-gnu python3 python3-pip python3-venv
```

**Please also ensure that the Python version installed is >3.7.**

The build process has a few python packages required that are located in `requirements.txt`.

To install them simply run in a terminal:

```bash
python3 -m pip install -r requirements.txt
```

# To use
1. Place the US Pokemon Stadium 2 (US/JP) rom into the repository's "/baseroms/VERSION/" folder as "baserom.z64". `VERSION` can be `us` or `jp`
2. Set up tools and extract the rom: `VERSION=us make init`
3. Re-assemble the rom: `make`

For contacts and other pret projects, see [pret.github.io](https://pret.github.io/).
