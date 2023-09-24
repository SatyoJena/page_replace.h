# page_replace.h
- Simple page replacement algorithms and their implementations
- /test/ examples can be verified from `ch10.pdf` which has been gracefully provided by/at https://os-book.com/OS10/slide-dir/index.html
- Example `page_request_sequence` for Bélády's anomaly has been copied from https://stackoverflow.com/questions/4800285/cant-understand-beladys-anomaly

## Usage
- at line 4 of `page_replace.h`, QUEUE_SZ can be changed to 3, 4, or whatever you like.
- then recompile all C files.
### Windows
```console
$ recompileall.bat
$ FIFO.exe
```
or any other exe for that matter.

### Linux
```console
$ . ./recompileall.sh
$ ./FIFO
```
## TODO
- add functionality to change `QUEUE_SZ` with ease ([issue#1](https://github.com/SatyoJena/page_replace.h/issues/1))
