# Radio Telescope

This repository holds code and files related to the 2022 EMU Design III class designing a radio telescope. More details to be added later.

## Python Virtual Environment
In order to manage packages and dependencies, all python programming should be done in a virtual environment. When the repository is download, run `python3 -m venv /.venv`. Then, every time you want to program in Python, first run `source /.venv/bin/activate` (Linux) or `.venv\Scripts\activate.bat` (Windows) and `pip install -r requirements.txt` to make sure your virtual environment has all the necessary packages installed.

If you install a package (eg `pip install pygame`) then run `pip freeze > requirements.txt` before committing to the repository so that everybody else is able to have all the dependencies downloaded.

[More info on venv here](https://frankcorso.dev/setting-up-python-environment-venv-requirements.html)
