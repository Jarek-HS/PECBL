# PECBL
This is a posit format extension compiler based on llvm

## install 

- step 1 
```sh
git clone https://github.com/Jarek-HS/PECBL.git
```

- step 2 all of build build here
```sh
cd PECBL/
mkdir build
pwd 
```

## Build riscv toolchain
```sh
# toolchain
../riscv-gnu-toolchain/configure --prefix=$HOME/PECBL/build \
--enable-linux \
--enable-multilib \
--with-arch=rv64imac \
--with-abi=lp64 
```
