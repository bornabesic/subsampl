# subsampl

![OSS Lifecycle](https://img.shields.io/osslifecycle/bornabesic/subsampl?label=oss%20lifecycle%20%282023-03%29&style=flat-square)
![GitHub](https://img.shields.io/github/license/bornabesic/subsampl?style=flat-square)
![AppVeyor tests](https://img.shields.io/appveyor/ci/bornabesic/subsampl?style=flat-square)

Library for fast subsampling of large 3D point clouds

## [Changelog](CHANGELOG.md)

## Getting Started

### Installation (C++)

1. Clone the repository
   ```sh
   git clone --recursive https://github.com/bornabesic/subsampl.git
   cd subsampl
   ```

2. Build the library
   ```sh
   mkdir build && cd build
   cmake ..
   make
   ```

4. Install the library

   This step might require superuser privileges. However, the installation directory can be customized via [DESTDIR](https://www.gnu.org/software/make/manual/html_node/DESTDIR.html) variable.

   ```sh
   make install
   ```

### Installation (Python)

```sh
pip install git+https://github.com/bornabesic/subsampl.git
```

Please note that this still requires a C++ compiler to be present on the host system.

## Usage
The API is currently documented in [subsampl.hpp](include/subsampl/subsampl.hpp). Usage examples can be found in [examples](examples/) directory.

## Contributing

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also
simply open an issue with the tag `enhancement`.
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature-awesome`)
3. Commit your Changes (`git commit -m 'Add an amazing feature'`)
4. Push to the Branch (`git push origin feature-awesome`)
5. Open a Pull Request

## License

Distributed under the GPL-2.0 license. See [LICENSE](LICENSE) for more information.

## Contact

Borna Bešić - [@bornabesic](https://github.com/bornabesic)

Project Link: [https://github.com/bornabesic/subsampl](https://github.com/bornabesic/subsampl)
