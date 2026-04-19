# Rust Programming Language

# Foreword
The Rust programming language has come a long way in a few short years, from its creation and incubation by a small and nascent community of enthusiasts, to becoming one of the most loved and in-demand programming languages in the world. 
Looking back, it was inevitable that the power and promise of Rust would turn heads and gain a foothold in systems programming.
What was not inevitable was the global growth in interest and innovation that permeated through open source communities and catalyzed wide-scale adoption across industries.

At this point in time, it is easy to point to the wonderful features that Rust has to offer to explain this explosion in interest and adoption.
Who doesn’t want memory safety, and fast performance, and a friendly compiler, and great tooling, among a host of other wonderful features?
The Rust language you see today combines years of research in systems programming with the practical wisdom of a vibrant and passionate community. 
This language was designed with purpose and crafted with care, offering developers a tool that makes it easier to write safe, fast, and reliable code.

But what makes Rust truly special is its roots in empowering you, the user, to achieve your goals.
This is a language that wants you to succeed, and the principle of empowerment runs through the core of the community that builds, maintains, and advocates for this language.
Since the previous edition of this definitive text, Rust has further developed into a truly global and trusted language.
The Rust Project is now robustly supported by the Rust Foundation, which also invests in key initiatives to ensure that Rust is secure, stable, and sustainable.

This edition of The Rust Programming Language is a comprehensive update, reflecting the language’s evolution over the years and providing valuable new information.
But it is not just a guide to syntax and libraries—it’s an invitation to join a community that values quality, performance, and thoughtful design.
Whether you’re a seasoned developer looking to explore Rust for the first time or an experienced Rustacean looking to refine your skills, this edition offers something for everyone.

The Rust journey has been one of collaboration, learning, and iteration. The growth of the language and its ecosystem is a direct reflection of the vibrant, diverse community behind it.
The contributions of thousands of developers, from core language designers to casual contributors, are what make Rust such a unique and powerful tool.
By picking up this book, you’re not just learning a new programming language—you’re joining a movement to make software better, safer, and more enjoyable to work with.

Welcome to the Rust community!

- Bec Rumbul, Executive Director of the Rust Foundation

## 1. Getting Started
Let’s start your Rust journey!
There’s a lot to learn, but every journey starts somewhere.
In this chapter, we’ll discuss:

    1.1 Installing Rust on Linux, macOS, and Windows
    1.2 Writing a program that prints Hello, world!
    1.3 Using cargo, Rust’s package manager and build system

### 1.1 Installation
The first step is to install Rust. We’ll download Rust through rustup, a command line tool for managing Rust versions and associated tools.
You’ll need an internet connection for the download.

Note: If you prefer not to use rustup for some reason, please see the Other Rust Installation Methods page for more options.

The following steps install the latest stable version of the Rust compiler.
Rust’s stability guarantees ensure that all the examples in the book that compile will continue to compile with newer Rust versions.
The output might differ slightly between versions because Rust often improves error messages and warnings.
In other words, any newer, stable version of Rust you install using these steps should work as expected with the content of this book.

#### Command Line Notation
In this chapter and throughout the book, we’ll show some commands used in the terminal.
Lines that you should enter in a terminal all start with $.
You don’t need to type the $ character; it’s the command line prompt shown to indicate the start of each command.
Lines that don’t start with $ typically show the output of the previous command.
Additionally, PowerShell-specific examples will use > rather than $.

#### Installing rustup on Linux or macOS
If you’re using Linux or macOS, open a terminal and enter the following command:

$ curl --proto '=https' --tlsv1.2 https://sh.rustup.rs -sSf | sh

The command downloads a script and starts the installation of the rustup tool, which installs the latest stable version of Rust.
You might be prompted for your password. If the install is successful, the following line will appear:

Rust is installed now. Great!

You will also need a linker, which is a program that Rust uses to join its compiled outputs into one file.
It is likely you already have one.
If you get linker errors, you should install a C compiler, which will typically include a linker.
A C compiler is also useful because some common Rust packages depend on C code and will need a C compiler.

On macOS, you can get a C compiler by running:

$ xcode-select --install
Linux users should generally install GCC or Clang, according to their distribution’s documentation.
For example, if you use Ubuntu, you can install the build-essential package.

#### Installing rustup on Windows
On Windows, go to https://www.rust-lang.org/tools/install and follow the instructions for installing Rust. At some point in the installation, you’ll be prompted to install Visual Studio. This provides a linker and the native libraries needed to compile programs. If you need more help with this step, see https://rust-lang.github.io/rustup/installation/windows-msvc.html.

The rest of this book uses commands that work in both cmd.exe and PowerShell. If there are specific differences, we’ll explain which to use.
⭐
#### Troubleshooting
To check whether you have Rust installed correctly, open a shell and enter this line:

$ rustc --version

You should see the version number, commit hash, and commit date for the latest stable version that has been released, in the following format:

rustc x.y.z (abcabcabc yyyy-mm-dd)

If you see this information, you have installed Rust successfully!
If you don’t see this information, check that Rust is in your %PATH% system variable as follows.

In Windows CMD, use:

> echo %PATH%

In PowerShell, use:

> echo $env:Path

In Linux and macOS, use:

$ echo $PATH

If that’s all correct and Rust still isn’t working, there are a number of places you can get help.
Find out how to get in touch with other Rustaceans (a silly nickname we call ourselves) on the community page.

#### Updating and Uninstalling
Once Rust is installed via rustup, updating to a newly released version is easy.
From your shell, run the following update script:

$ rustup update

To uninstall Rust and rustup, run the following uninstall script from your shell:

$ rustup self uninstall

Reading the Local Documentation
The installation of Rust also includes a local copy of the documentation so that you can read it offline.
Run rustup doc to open the local documentation in your browser.

Any time a type or function is provided by the standard library and you’re not sure what it does or how to use it, use the application programming interface (API) documentation to find out!


#### Using Text Editors and IDEs
This book makes no assumptions about what tools you use to author Rust code.
Just about any text editor will get the job done!
However, many text editors and integrated development environments (IDEs) have built-in support for Rust.
You can always find a fairly current list of many editors and IDEs on the tools page on the Rust website.

#### Working Offline with This Book
In several examples, we will use Rust packages beyond the standard library.
To work through those examples, you will either need to have an internet connection or to have downloaded those dependencies ahead of time.
To download the dependencies ahead of time, you can run the following commands.
(We’ll explain what cargo is and what each of these commands does in detail later.)

$ cargo new get-dependencies
$ cd get-dependencies
$ cargo add rand@0.8.5 trpl@0.2.0

This will cache the downloads for these packages so you will not need to download them later.
Once you have run this command, you do not need to keep the get-dependencies folder.
If you have run this command, you can use the --offline flag with all cargo commands in the rest of the book to use these cached versions instead of attempting to use the network.
