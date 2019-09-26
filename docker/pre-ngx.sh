#yum update -y
yum provides '*/applydeltarpm'
yum install deltarpm -y

yum -y install git gcc gcc-c++ libstdc++-devel make cmake \
               readline readline-devel openssl* zlib* gd* \
               uuid uuid-devel libuuid-devel wget pcre* libcurl* \
               libtool unzip openldap-clients openldap-devel --skip-broken

wget http://www.lua.org/ftp/lua-5.1.5.tar.gz
tar -xvf lua-5.1.5.tar.gz

wget http://bitop.luajit.org/download/LuaBitOp-1.0.2.tar.gz
tar -xvf LuaBitOp-1.0.2.tar.gz

wget https://www.kyne.com.au/~mark/software/download/lua-cjson-2.1.0.tar.gz
tar -xvf lua-cjson-2.1.0.tar.gz

wget http://luajit.org/download/LuaJIT-2.0.3.tar.gz
tar -xvf LuaJIT-2.0.3.tar.gz

wget http://files.luaforge.net/releases/luasocket/luasocket/luasocket-2.0.2/luasocket-2.0.2.tar.gz
tar -xvf luasocket-2.0.2.tar.gz

wget https://git.zx2c4.com/lualdap/snapshot/lualdap-1.2.0.tar.xz
tar -xvf lualdap-1.2.0.tar.xz

wget http://nginx.org/download/nginx-1.12.2.tar.gz
tar -xvf nginx-1.12.2.tar.gz

cd /usr/local/src/nginx-1.12.2
mkdir -p src/ext
cd src/ext
wget https://github.com/openresty/lua-nginx-module/archive/v0.10.12.tar.gz
tar -xvf v0.10.12.tar.gz
mv lua-nginx-module-0.10.12 lua-nginx-module
git clone https://github.com/openresty/headers-more-nginx-module.git

cd /usr/local/src

cd lua-5.1.5
make clean
make linux && make install

cd src
gcc -O2 -Wall -DLUA_USE_LINUX  lapi.c lcode.c ldebug.c ldo.c ldump.c lfunc.c lgc.c llex.c lmem.c lobject.c lopcodes.c lparser.c lstate.c lstring.c ltable.c ltm.c lundump.c lvm.c lzio.c lauxlib.c lbaselib.c ldblib.c liolib.c lmathlib.c loslib.c ltablib.c lstrlib.c loadlib.c linit.c  -fPIC -shared -o liblua.so

mkdir -p /usr/local/nginx/lua/lib/lua/5.1/
mv -f liblua.so /usr/local/nginx/lua/lib/lua/5.1/
cd /usr/local/src


cd LuaBitOp-1.0.2
make clean && make
mv bit.so /usr/local/nginx/lua/lib/lua/5.1/
cd /usr/local/src


cd lua-cjson-2.1.0
make clean && make && make install
mv cjson.so /usr/local/nginx/lua/lib/lua/5.1/
cd /usr/local/src


cd luasocket-2.0.2
make clean && make && make install
cd /usr/local/src


cd lua-uuid
make clean && make && make install
mv luuid.so /usr/local/nginx/lua/lib/lua/5.1/
cd /usr/local/src


cd LuaJIT-2.0.3
make clean && make CCDEBUG=-g -B -j8 && make install
ln -s /usr/local/lib/libluajit-5.1.so.2 /lib64/libluajit-5.1.so.2
cd /usr/local/src


cd lualdap-1.2.0
make clean && make
mv lualdap.so /usr/local/nginx/lua/lib/lua/5.1/
cd /usr/local/src