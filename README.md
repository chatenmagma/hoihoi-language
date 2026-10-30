# Hoihoi language

> A language programming to using cluster and set without number logic

# Installation and depencies

You need install the jar antlr4 into /opt/antlr/antlr.jar. And the lib for C language into /usr/local/lib

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
./build/hoihoi <file in .hoi>
```
