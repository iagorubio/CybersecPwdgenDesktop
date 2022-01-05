# CybersecPwdgenDesktop


CybersecPwdgenDesktop is a Qt dialog application, made for a cyber security course, that generates pseudo random passwords.

![App Screenshot](/screenshot.png?raw=true "Cybersec Pwdgen Desktop")

## Installation
Right now there is no provided installer.

If you have qt5 installed in your system make a build folder and use qmake to create a Makefile suited for it from the root git directory.

```bash
git clone https://github.com/iagorubio/CybersecPwdgenDesktop.git
mkdir build
qmake ../CybersecPwdgenDesktop
make
```

If you can't find qmake in your system you can use QtCreator to build the project, opening the provided .pro file, or look for it on your system, usually in /usr/share/qt5/wrappers on Linux/OsX or in QT's installation directory on Windows.


## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.
## Web version

There is a javascript version available on a separate repository to embed it in your webpage or use locally in your browser.

## License
[MIT](https://choosealicense.com/licenses/mit/)
