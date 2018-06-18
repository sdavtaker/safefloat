# safefloat
Safe Float library intended to be included in Boost.org

##Installation
* The library is headers only.
* It is enough to put the include directory in the path the compiler looks up for them.

##Requirements
* Boost.Test (To run the tests)
* A compiler with C++17 support

##Building steps
The library is headers-only, it does not require anything else than just adding the files to the include_path. 

The library comes with all the files required to easily build examples, documentation and tests using boostbuild or cmake.
* Using boostbuild, just run the b2 command in the root folder.
* Using cmake follow normal the steps required to use your preferred generator.

##Documentation
For more details, a prebuild version of the last version of the manual is available in the following site [Safefloat manual](https://sdavtaker.github.io/safefloat/doc/html/index.html)
